"""Real-process checks for C++ publication, Python hot reload, rollback and worker cleanup."""
import argparse
import ctypes
import faulthandler
import json
import os
from pathlib import Path
from queue import Empty, Queue
import shutil
import struct
import subprocess
import sys
from tempfile import TemporaryDirectory
from threading import Thread
import time
from unittest.mock import patch
import uuid

from mcp_deployment import Deployment, deploy_mcp
from mcp_server import RUNTIME_TOOL, Worker, default_initialization


class Client:
    def __init__(self, command, cwd=None):
        self.process = subprocess.Popen(command, cwd=cwd, stdin=subprocess.PIPE,
                                        stdout=subprocess.PIPE, stderr=subprocess.PIPE,
                                        text=True, encoding="utf-8",
                                        creationflags=getattr(subprocess, "CREATE_NO_WINDOW", 0))
        self.replies = Queue()
        self.notifications, self.errors = [], []
        self.next_id = 0
        self.workers = set()
        self.threads = [Thread(target=self.read, daemon=True), Thread(target=self.read_errors, daemon=True)]
        for thread in self.threads:
            thread.start()

    def read(self):
        for line in self.process.stdout:
            self.replies.put(json.loads(line))
        self.replies.put(None)

    def read_errors(self):
        self.errors.extend(self.process.stderr)

    def send(self, request):
        self.process.stdin.write(json.dumps(request) + "\n")
        self.process.stdin.flush()

    def receive(self, identifier):
        while True:
            try:
                reply = self.replies.get(timeout=15)
            except Empty as error:
                raise AssertionError("Bridge response timeout: " + "".join(self.errors)) from error
            assert reply is not None, "Bridge closed stdout: " + "".join(self.errors)
            if "id" not in reply:
                self.notifications.append(reply)
                continue
            assert reply.get("id") == identifier, reply
            return reply

    def rpc(self, method, params=None):
        self.next_id += 1
        self.send({"jsonrpc": "2.0", "id": self.next_id, "method": method,
                   "params": {} if params is None else params})
        return self.receive(self.next_id)

    def initialize(self):
        reply = self.rpc("initialize", default_initialization())
        assert "result" in reply, reply
        self.send({"jsonrpc": "2.0", "method": "notifications/initialized"})
        return reply["result"]

    def call(self, name, **arguments):
        if name in ('game_state', 'game_action', 'new_game', 'load_game', 'replay_game', 'simulate_actions'):
            arguments.setdefault('detail', 'full')
        return self.rpc("tools/call", {"name": name, "arguments": arguments})

    def tool(self, name, **arguments):
        reply = self.call(name, **arguments)
        assert "result" in reply and not reply["result"].get("isError"), reply
        result = reply["result"]
        assert json.loads(result["content"][0]["text"]) == result["structuredContent"], reply
        return result["structuredContent"]

    def runtime(self):
        value = self.tool("mcp_runtime")
        self.workers.add(value["worker_pid"])
        assert value["bridge_pid"] == self.process.pid, value
        return value

    def close(self):
        self.process.stdin.close()
        try:
            self.process.wait(timeout=10)
        except subprocess.TimeoutExpired:
            self.process.kill()
            raise AssertionError("Bridge did not stop on EOF")
        for thread in self.threads:
            thread.join(timeout=2)
        self.process.stdout.close()
        self.process.stderr.close()
        assert self.process.returncode == 0, "".join(self.errors)
        for pid in self.workers:
            assert not alive(pid), f"Worker {pid} leaked after bridge EOF"


def alive(pid):
    if os.name == "nt":
        kernel = ctypes.WinDLL("kernel32", use_last_error=True)
        kernel.OpenProcess.argtypes = [ctypes.c_ulong, ctypes.c_bool, ctypes.c_ulong]
        kernel.OpenProcess.restype = ctypes.c_void_p
        kernel.WaitForSingleObject.argtypes = [ctypes.c_void_p, ctypes.c_ulong]
        kernel.CloseHandle.argtypes = [ctypes.c_void_p]
        handle = kernel.OpenProcess(0x100000, False, pid)
        if not handle:
            return False
        try:
            return kernel.WaitForSingleObject(handle, 0) == 258
        finally:
            kernel.CloseHandle(handle)
    try:
        os.kill(pid, 0)
        return True
    except ProcessLookupError:
        return False


def activate(manifest, executable, version="fixture", activation=None):
    value = {"version": version, "activation": activation or uuid.uuid4().hex,
             "executable": str(executable)}
    temporary = manifest.with_suffix(".tmp")
    temporary.write_text(json.dumps(value), encoding="utf-8")
    os.replace(temporary, manifest)
    return value


def bridge(manifest, *options):
    script = Path(__file__).with_name("mcp_server.py")
    client = Client([sys.executable, str(script), "--manifest", str(manifest), *options], cwd=manifest.parent)
    initialized = client.initialize()
    assert initialized["capabilities"]["tools"]["listChanged"] is True
    return client


def fake_worker(folder, catalog, mode):
    # Python itself is the fixture executable: the bridge launches `python mcp ...`.
    # No descendant process is needed, so crash/timeout fixtures cannot leak a child.
    fixture = {"catalog": catalog, "mode": mode, "marker": str(folder / "attempts.txt")}
    (folder / "fixture.json").write_text(json.dumps(fixture), encoding="utf-8")
    (folder / "mcp").write_text('''import json, sys, time
from pathlib import Path
fixture = json.loads(Path("fixture.json").read_text(encoding="utf-8"))
if fixture["mode"] == "catalog":
    sys.stderr.write("diagnostic " * 12000 + "\\n")
    sys.stderr.flush()
for line in sys.stdin:
    request = json.loads(line)
    if "id" not in request:
        continue
    method, mode = request["method"], fixture["mode"]
    reply = {"jsonrpc": "2.0", "id": request["id"], "result": {}}
    if method == "initialize":
        reply["result"] = {"protocolVersion": "2025-11-25", "capabilities": {"tools": {}},
                           "serverInfo": {"name": "fixture", "version": "1"}}
    elif method == "tools/list":
        tools = list(fixture["catalog"])
        if mode == "catalog":
            tools.append({"name": "fixture_tool", "inputSchema": {"type": "object"}})
        reply["result"] = {"tools": tools}
    elif method == "runtime/restore":
        if mode == "reject":
            reply.pop("result")
            reply["error"] = {"code": -32602, "message": "incompatible fixture snapshot version"}
        else:
            reply["result"] = {"restored": True, "version": 1}
    elif method == "tools/call" and request["params"]["name"] == "game_action":
        with open(fixture["marker"], "a", encoding="utf-8") as marker:
            marker.write("action\\n")
        if mode == "timeout":
            time.sleep(30)
        if mode == "crash":
            sys.exit(7)
    print(json.dumps(reply), flush=True)
''', encoding="utf-8")


def check_transfer(cli, folder):
    manifest = folder / "current.json"
    deploy_mcp(cli, manifest)
    client = bridge(manifest, "--developer")
    native = Client([str(cli), "mcp", "--developer"])
    try:
        native.initialize()
        assert client.rpc("initialize", default_initialization())["error"]["code"] == -32600
        expected_catalog = native.rpc("tools/list")["result"]["tools"]
        catalog = client.rpc("tools/list")["result"]["tools"]
        assert catalog == [*expected_catalog, RUNTIME_TOOL]
        assert client.rpc("resources/list")["result"] == native.rpc("resources/list")["result"]
        initial = client.tool("game_state")
        assert initial == native.tool("game_state")
        first = client.runtime()
        state = client.tool("game_action", action={"type": "move", "direction": "up"})
        checkpoint = client.tool("save_game")["checkpoint"]
        history = client.tool("export_replay")
        deploy_mcp(cli, manifest)
        reply = client.call("game_state")
        assert reply["result"]["structuredContent"] == state, reply
        assert reply["result"]["_meta"]["runtime_reload"]["status"] == "succeeded"
        second = client.runtime()
        assert first["worker_pid"] != second["worker_pid"] and second["worker_running"]
        assert not alive(first["worker_pid"])
        assert client.notifications == [], client.notifications
        assert client.tool("export_replay") == history
        client.tool("game_action", action={"type": "move", "direction": "left"})
        assert client.tool("load_game", checkpoint=checkpoint) == state
        assert client.tool("save_game")["checkpoint"] == "checkpoint-2"
        # Two pipelined mutations on a new activation each execute exactly once.
        deploy_mcp(cli, manifest)
        start_id = client.next_id
        for i in (1, 2):
            client.send({"jsonrpc": "2.0", "id": start_id + i, "method": "tools/call",
                         "params": {"name": "game_action", "arguments": {
                             "action": {"type": "move", "direction": "left" if i == 1 else "right"}}}})
        client.next_id += 2
        replies = [client.receive(start_id + i)["result"]["structuredContent"] for i in (1, 2)]
        assert [r["steps"] for r in replies] == [state["steps"] + 1, state["steps"] + 2]
        assert replies[-1]["hero"]["x"] == state["hero"]["x"]
        assert client.tool("export_replay")["inputs"] == history["inputs"] + 2
        client.runtime()
        for method in ("runtime/checkpoint", "runtime/restore"):
            assert client.rpc(method, {"path": str(folder / "private.json")})["error"]["code"] == -32601
        assert not (folder / "private.json").exists()
        # A rejected binary must leave the old manifest and version directory intact.
        before = manifest.read_bytes()
        versions = set((folder / "versions").iterdir())
        bad = folder / "bad.exe"
        bad.write_bytes(b"This is not an executable")
        try:
            deploy_mcp(bad, manifest, timeout=1)
            raise AssertionError("Bad publication succeeded")
        except (OSError, ValueError, RuntimeError):
            pass
        assert manifest.read_bytes() == before
        assert set((folder / "versions").iterdir()) == versions
        assert not list(folder.glob("current.json.*.tmp"))
        if os.name == "nt":
            # The invalid image must be refused before any CreateProcess call.
            with patch("mcp_server.subprocess.Popen") as launch:
                try:
                    deploy_mcp(bad, manifest)
                    raise AssertionError("Invalid PE image was accepted")
                except ValueError as error:
                    assert "native Windows PE" in str(error)
                launch.assert_not_called()
        class IncompatibleProbe:
            closed = False

            def __init__(self, selected, options, timeout):
                assert selected.executable != str(cli)

            def prepare(self, initialization):
                pass

            def required(self, method, params):
                if method == "runtime/restore":
                    raise RuntimeError("incompatible probe restore")
                return {"version": 1}

            def close(self):
                IncompatibleProbe.closed = True

        with patch("mcp_server.Worker", IncompatibleProbe):
            try:
                deploy_mcp(cli, manifest)
                raise AssertionError("Incompatible publication succeeded")
            except RuntimeError as error:
                assert "incompatible probe restore" in str(error)
        assert IncompatibleProbe.closed and manifest.read_bytes() == before
        assert set((folder / "versions").iterdir()) == versions
    finally:
        native.close()
        client.close()


def check_lifecycle(cli, folder):
    manifest = folder / "current.json"
    deploy_mcp(cli, manifest)
    client = Client([sys.executable, str(Path(__file__).with_name("mcp_server.py")),
                     "--manifest", str(manifest)])
    try:
        assert client.rpc("ping")["result"] == {}
        assert client.rpc("tools/list")["error"]["code"] == -32000
        for line, code in (("NaN\n", -32700), ("[]\n", -32600),
                           ('{"jsonrpc":"2.0","id":true,"method":"ping"}\n', -32600)):
            client.process.stdin.write(line)
            client.process.stdin.flush()
            assert client.receive(None)["error"]["code"] == code
        invalid = default_initialization()
        invalid["clientInfo"] = {}
        assert client.rpc("initialize", invalid)["error"]["code"] == -32602
        assert "result" in client.rpc("initialize", default_initialization())
        assert client.rpc("tools/list")["error"]["code"] == -32000
        client.send({"jsonrpc": "2.0", "method": "notifications/initialized"})
        for identifier in (9007199254740993, "public-string-id"):
            client.send({"jsonrpc": "2.0", "id": identifier, "method": "ping"})
            assert client.receive(identifier)["result"] == {}
        client.runtime()
    finally:
        client.close()


def check_windows_headers(cli, folder):
    if os.name != "nt":
        return
    image = cli.read_bytes()
    offset = struct.unpack_from("<I", image, 0x3C)[0]
    path = folder / "invalid.exe"
    for problem in range(5):
        invalid = bytearray(image)
        if problem == 0:
            invalid = bytearray(b"Not an executable")
        elif problem == 1:
            invalid[offset:offset + 4] = b"NE\0\0"  # Legacy Windows image, not PE.
        elif problem == 2:
            struct.pack_into("<I", invalid, 0x3C, len(invalid) + 100)
        elif problem == 3:
            struct.pack_into("<H", invalid, offset + 24 + 68, 2)  # GUI subsystem.
        else:
            invalid = invalid[:offset + 25]
        path.write_bytes(invalid)
        with patch("mcp_server.subprocess.Popen") as launch:
            try:
                Worker(Deployment("invalid", "guard", str(path)), [], 1)
                raise AssertionError(f"Invalid Windows image {problem} was accepted")
            except ValueError:
                pass
            launch.assert_not_called()


def check_rollback(cli, folder):
    manifest = folder / "current.json"
    deploy_mcp(cli, manifest)
    client = bridge(manifest)
    try:
        state = client.tool("game_action", action={"type": "move", "direction": "up"})
        first = client.runtime()
        assert not state["save_unlocked"]  # Migration must work without the Hero Orb.
        manifest.write_text("{bad json", encoding="utf-8")
        reply = client.call("game_state")
        assert reply["result"]["structuredContent"] == state
        assert "Cannot read" in reply["result"]["_meta"]["runtime_reload"]["error"]
        missing = folder / ("missing.exe" if os.name == "nt" else "missing")
        broken = activate(manifest, missing)
        failed = client.call("game_action", action={"type": "move", "direction": "left"})
        assert "previous worker retained" in failed["error"]["message"], failed
        runtime = client.runtime()
        assert runtime["worker_pid"] == first["worker_pid"] and runtime["worker_running"]
        assert runtime["last_reload"]["status"] == "failed"
        assert client.tool("game_state") == state
        shutil.copy2(cli, missing)
        # Fixing the executable without a new activation must not retry the failed candidate.
        assert client.runtime()["worker_pid"] == first["worker_pid"]
        activate(manifest, cli, version="metadata-only", activation=broken["activation"])
        assert client.runtime()["worker_pid"] == first["worker_pid"]
        activate(manifest, missing, broken["version"])
        assert client.tool("game_state") == state
        assert client.runtime()["worker_pid"] != first["worker_pid"]
        catalog = client.rpc("tools/list")["result"]["tools"][:-1]
        fake_worker(folder, catalog, "reject")
        activate(manifest, sys.executable)
        failed = client.call("game_action", action={"type": "move", "direction": "left"})
        assert "incompatible fixture" in failed["error"]["message"], failed
        assert client.tool("game_state") == state
        assert not client.runtime()["last_reload"]["session_lost"]
        if os.name == "nt":
            invalid = folder / "invalid.exe"
            invalid.write_bytes(b"This is not a native executable")
            activate(manifest, invalid)
            failed = client.call("game_state")
            assert "native Windows PE" in failed["error"]["message"], failed
            assert client.tool("game_state") == state
            assert client.runtime()["worker_running"]
        fake_worker(folder, catalog, "catalog")
        activate(manifest, sys.executable)
        assert client.rpc("tools/list")["result"]["tools"][-2]["name"] == "fixture_tool"
        assert client.notifications == [{"jsonrpc": "2.0", "method": "notifications/tools/list_changed"}]
        assert client.runtime()["last_reload"]["tools_changed"]
    finally:
        client.close()


def make_startup(cli, folder):
    native = Client([str(cli), "mcp", "--developer", "--runtime-bridge"])
    try:
        native.initialize()
        path = folder / "fixture-state.json"
        assert "result" in native.rpc("runtime/checkpoint", {"path": str(path)})
        value = json.loads(path.read_text(encoding="utf-8"))
        hero = value["session"]["game"]["hero"]
        hero.update(x=5, y=5, gold=100, highest_floor=5)
        hero["items"][0] = hero["items"][2] = 1
        floor = value["session"]["game"]["floors"][1]
        floor["tiles"] = [6] * 121
        floor["tiles"][4 * 11 + 5] = 16
        floor["tiles"][5 * 11 + 4] = 11
        path.write_text(json.dumps(value), encoding="utf-8")
        reply = native.rpc("runtime/restore", {"path": str(path)})
        assert "result" in reply, reply
        save = folder / "启动存档.dat"
        native.tool("save_game", path=str(save), kind="checkpoint")
        return save
    finally:
        native.close()


def check_startup_and_shops(cli, folder):
    save = make_startup(cli, folder)
    manifest = folder / "current.json"
    deploy_mcp(cli, manifest)
    client = bridge(manifest, "--load", str(save), "--checkpoint")
    try:
        assert client.tool("game_state")["hero"]["gold"] == 100
        first = client.runtime()
        save.unlink()
        Path(str(save) + ".replay.jsonl").unlink()
        shop = client.tool("game_action", action={"type": "move", "direction": "up"})
        checkpoint = client.tool("save_game")["checkpoint"]
        assert shop["phase"] == "shop"
        deploy_mcp(cli, manifest)
        assert client.tool("game_state") == shop
        assert client.runtime()["worker_pid"] != first["worker_pid"]
        bought = client.tool("game_action", action={"type": "choose", "choice": "attack"})
        assert bought["hero"]["gold"] == 80 and bought["hero"]["attack"] == 102
        client.tool("game_action", action={"type": "flight_open"})
        preview = client.tool("game_action", action={"type": "flight_up"})
        assert preview["flight"] == 2
        deploy_mcp(cli, manifest)
        assert client.tool("game_state") == preview
        client.runtime()
        assert client.tool("load_game", checkpoint=checkpoint) == shop
        again = client.tool("game_action", action={"type": "choose", "choice": "attack"})
        assert again == bought
    finally:
        client.close()


def check_failure(cli, folder, mode):
    manifest = folder / "current.json"
    deploy_mcp(cli, manifest)
    client = bridge(manifest, "--timeout-ms", "500")
    try:
        catalog = client.rpc("tools/list")["result"]["tools"][:-1]
        fake_worker(folder, catalog, mode)
        activate(manifest, sys.executable)
        client.rpc("tools/list")
        pid = client.runtime()["worker_pid"]
        failed = client.call("game_action", action={"type": "move", "direction": "up"})
        assert "error" in failed, failed
        if mode == "timeout":
            assert "not retried" in failed["error"]["message"] and "commit status" in failed["error"]["message"]
        assert (folder / "attempts.txt").read_text(encoding="utf-8") == "action\n"
        runtime = client.runtime()
        assert runtime["worker_pid"] == pid and not runtime["worker_running"]
        assert runtime["worker_error"]
        assert "error" in client.call("game_action", action={"type": "move", "direction": "up"})
        assert (folder / "attempts.txt").read_text(encoding="utf-8") == "action\n"
        deploy_mcp(cli, manifest)
        assert "error" in client.call("game_state")
        assert client.runtime()["last_reload"]["session_lost"]
    finally:
        client.close()


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--cli", type=Path, required=True)
    args = parser.parse_args()
    cli = args.cli.resolve()
    # Include thread stacks if an integration check stalls before CTest's deadline.
    faulthandler.dump_traceback_later(30, repeat=True)
    with TemporaryDirectory(prefix="tsw-mcp-reload-check-") as temporary:
        root = Path(temporary)
        for name, check in (("windows-headers", check_windows_headers), ("lifecycle", check_lifecycle),
                            ("transfer", check_transfer), ("rollback", check_rollback),
                            ("startup-shops-flight", check_startup_and_shops),
                            ("timeout", lambda cli, folder: check_failure(cli, folder, "timeout")),
                            ("crash", lambda cli, folder: check_failure(cli, folder, "crash"))):
            folder = root / name
            folder.mkdir()
            check(cli, folder)
            print(f"Passed Python MCP {name}", flush=True)
    faulthandler.cancel_dump_traceback_later()


if __name__ == "__main__":
    main()
