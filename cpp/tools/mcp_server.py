"""Stable stdio MCP bridge with transactional C++ worker hot reload (standard library only)."""
import argparse
import json
import math
import os
from pathlib import Path
from queue import Empty, Queue
import signal
import subprocess
import sys
from tempfile import TemporaryDirectory
from threading import Thread
import time

from mcp_deployment import DEFAULT_MANIFEST, read_deployment, validate_worker_executable


MAX_REQUEST_BYTES = 8 * 1024 * 1024
MAX_REPLY_BYTES = 128 * 1024 * 1024
RUNTIME_TOOL = {
    "name": "mcp_runtime",
    "description": "Read bridge/worker process IDs, active deployment, session continuation/recovery status "
                   "and the last hot reload outcome.",
    "inputSchema": {"type": "object", "properties": {}, "additionalProperties": False},
    "annotations": {"readOnlyHint": True, "openWorldHint": False},
}
RECOVERY_TOOLS = ("new_game", "load_game", "replay_game")
OBSERVATION_TOOLS = ("game_state", "inspect_tile", "plan_path")


class WorkerRpcError(RuntimeError):
    def __init__(self, error):
        super().__init__(error.get("message", "Worker request failed"))
        self.data = error.get("data")


def default_initialization():
    return {"protocolVersion": "2025-11-25", "capabilities": {},
            "clientInfo": {"name": "tsw-python-bridge", "version": "1"}}


def encode(value):
    return json.dumps(value, ensure_ascii=False, allow_nan=False, separators=(",", ":"))


def decode(value):
    def invalid_constant(constant):
        raise ValueError(f"Invalid JSON constant {constant}")
    return json.loads(value, parse_constant=invalid_constant)


def write(message):
    sys.stdout.write(encode(message) + "\n")
    sys.stdout.flush()


class Worker:
    """One serialized RPC stream, with independent pipe drains and bounded writes/reads."""
    def __init__(self, deployment, options, timeout, notification=None):
        validate_worker_executable(deployment.executable)
        self.deployment = deployment
        self.timeout = timeout
        self.notification = notification
        self.failure = None
        self.next_id = 0
        self.outbound, self.replies = Queue(), Queue()
        self.process = subprocess.Popen(
            [deployment.executable, "mcp", "--runtime-bridge", *options],
            stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE,
            creationflags=getattr(subprocess, "CREATE_NO_WINDOW", 0))
        self.threads = [Thread(target=target, daemon=True) for target in
                        (self._read, self._write, self._stderr)]
        for thread in self.threads:
            thread.start()

    def _fail(self, message):
        if self.failure is None:
            self.failure = str(message)
            self.replies.put(RuntimeError(self.failure))

    def _write(self):
        try:
            while True:
                message = self.outbound.get()
                if message is None:
                    self.process.stdin.close()
                    return
                self.process.stdin.write((encode(message) + "\n").encode("utf-8"))
                self.process.stdin.flush()
        except (OSError, ValueError) as error:
            self._fail(f"Cannot write to MCP worker: {error}")

    def _read(self):
        try:
            while True:
                line = self.process.stdout.readline(MAX_REPLY_BYTES + 2)
                if not line:
                    self._fail("MCP worker exited or closed stdout; live session unavailable")
                    return
                if len(line) > MAX_REPLY_BYTES:
                    raise ValueError("Worker response exceeds 128 MiB")
                reply = decode(line)
                if not isinstance(reply, dict) or reply.get("jsonrpc") != "2.0":
                    raise ValueError("Invalid worker JSON-RPC envelope")
                self.replies.put(reply)
        except (OSError, ValueError, UnicodeError, RecursionError) as error:
            self._fail(f"Invalid MCP worker response: {error}")

    def _stderr(self):
        try:
            while True:
                data = self.process.stderr.read1(4096)
                if not data:
                    return
                text = data.decode("utf-8", errors="replace")
                sys.stderr.write(text)
                sys.stderr.flush()
        except (OSError, ValueError):
            pass

    @property
    def running(self):
        return self.failure is None and self.process.poll() is None

    def request(self, method, params=None):
        if not self.running:
            raise RuntimeError(self.failure or "MCP worker is no longer running; live session unavailable")
        self.next_id += 1
        identifier = f"bridge-{self.next_id}"
        self.outbound.put({"jsonrpc": "2.0", "id": identifier, "method": method,
                           "params": {} if params is None else params})
        deadline = time.monotonic() + self.timeout
        while True:
            try:
                reply = self.replies.get(timeout=max(0, deadline - time.monotonic()))
            except Empty as error:
                message = (f"MCP worker timed out during {method}; request was not retried, "
                           "and action commit status may be unknown")
                self._fail(message)
                try:
                    self.process.kill()
                except ProcessLookupError:
                    pass
                raise RuntimeError(message) from error
            if isinstance(reply, Exception):
                raise reply
            if "id" not in reply and isinstance(reply.get("method"), str):
                if self.notification:
                    self.notification(reply)
                continue
            if reply.get("id") != identifier or ("result" in reply) == ("error" in reply):
                self._fail("Unexpected worker response ID or result")
                raise RuntimeError(self.failure)
            return reply

    def required(self, method, params=None):
        reply = self.request(method, params)
        if "error" in reply:
            raise WorkerRpcError(reply["error"])
        return reply["result"]

    def notify(self, method, params=None):
        if self.running:
            message = {"jsonrpc": "2.0", "method": method}
            if params is not None:
                message["params"] = params
            self.outbound.put(message)

    def prepare(self, initialization):
        self.initialization = self.required("initialize", initialization)
        if (not isinstance(self.initialization, dict) or
                not isinstance(self.initialization.get("protocolVersion"), str) or
                not isinstance(self.initialization.get("capabilities"), dict) or
                not isinstance(self.initialization.get("serverInfo"), dict)):
            raise RuntimeError("Worker did not supply a valid initialization result")
        self.notify("notifications/initialized")
        catalog = self.required("tools/list")
        if (not isinstance(catalog, dict) or not isinstance(catalog.get("tools"), list) or
                not catalog["tools"] or any(not isinstance(tool, dict) or
                not isinstance(tool.get("name"), str) or not tool["name"] or
                tool["name"] == RUNTIME_TOOL["name"] or not isinstance(tool.get("inputSchema"), dict)
                for tool in catalog["tools"])):
            raise RuntimeError("Worker did not supply a valid native tool catalog")
        if len({tool["name"] for tool in catalog["tools"]}) != len(catalog["tools"]):
            raise RuntimeError("Worker supplied duplicate tool names")
        self.catalog = catalog["tools"]

    def close(self):
        # Queue EOF instead of taking the stdin lock while a writer might be blocked.
        self.outbound.put(None)
        try:
            self.process.wait(timeout=1.5)
        except subprocess.TimeoutExpired:
            try:
                self.process.terminate()
            except ProcessLookupError:
                pass
            try:
                self.process.wait(timeout=1)
            except subprocess.TimeoutExpired:
                try:
                    self.process.kill()
                except ProcessLookupError:
                    pass
                self.process.wait(timeout=1)
        for thread in self.threads:
            thread.join(timeout=1)
        for stream in (self.process.stdin, self.process.stdout, self.process.stderr):
            stream.close()


class Bridge:
    def __init__(self, manifest, options, startup_load, timeout, emit=write):
        self.manifest = manifest
        self.options, self.startup_load = options, startup_load
        self.timeout, self.emit = timeout, emit
        self.active = self.candidate = None
        self.initialized = self.ready = False
        self.initialization = default_initialization()
        self.blocked = None
        self.last_reload = None
        self.session_continuable = True
        self.directory = TemporaryDirectory(prefix="tsw-mcp-session-")
        self.checkpoint = Path(self.directory.name) / "worker.json"

    def _notification(self, reply):
        if self.ready and reply.get("method") != "notifications/tools/list_changed":
            self.emit(reply)

    def _worker(self, deployment):
        # Candidate notifications are hidden until activation succeeds.
        return Worker(deployment, self.options, self.timeout)

    def initialize(self, params):
        if (not isinstance(params.get("protocolVersion"), str) or
                not isinstance(params.get("capabilities"), dict) or
                not isinstance(params.get("clientInfo"), dict) or
                any(not isinstance(params["clientInfo"].get(key), str) for key in ("name", "version"))):
            return {"code": -32602, "message": "Invalid initialization parameters"}, None
        self.candidate = self._worker(read_deployment(self.manifest))
        try:
            self.candidate.prepare(params)
            if self.startup_load:
                # JSON carries Unicode paths without the Windows narrow argv conversion.
                loaded = self.candidate.required("tools/call", {"name": "load_game",
                                                 "arguments": self.startup_load})
                if loaded.get("isError"):
                    raise RuntimeError(loaded["content"][0]["text"])
        except Exception:
            self.candidate.close()
            self.candidate = None
            raise
        self.active, self.candidate = self.candidate, None
        self.active.notification = self._notification
        self.initialization = {**params, "protocolVersion": self.active.initialization["protocolVersion"]}
        self.initialized = True
        self.startup_load = None
        result = dict(self.active.initialization)
        result["capabilities"] = dict(result.get("capabilities", {}))
        result["capabilities"]["tools"] = {"listChanged": True}
        return None, result

    def reload(self):
        try:
            requested = read_deployment(self.manifest)
        except (OSError, ValueError) as error:
            self.last_reload = {"status": "unchanged", "previous": self.active.deployment.json(),
                                "error": f"Cannot read deployment manifest: {error}",
                                "session_lost": not self.active.running}
            return self.last_reload
        if (requested.activation == self.active.deployment.activation or
                self.blocked is not None and requested.activation == self.blocked.activation):
            return None
        previous = self.active.deployment.json()
        reset_reason = None
        try:
            self.active.required("runtime/checkpoint", {"path": str(self.checkpoint)})
            self.candidate = self._worker(requested)
            self.candidate.prepare(self.initialization)
            if self.candidate.initialization["protocolVersion"] != self.initialization["protocolVersion"]:
                raise RuntimeError("Candidate changed the negotiated MCP protocol version")
            try:
                restored = self.candidate.required("runtime/restore", {"path": str(self.checkpoint)})
                if restored.get("restored") is not True:
                    raise RuntimeError("Candidate did not confirm session restoration")
            except WorkerRpcError as error:
                if (not isinstance(error.data, dict) or
                        error.data.get("kind") != "session_incompatible" or
                        error.data.get("session_continuable") is not False):
                    raise
                # The candidate is healthy, but this session cannot migrate. Use
                # its untouched initial session and require explicit recovery.
                reset_reason = str(error)
        except (OSError, ValueError, RuntimeError) as error:
            if self.candidate:
                self.candidate.close()
                self.candidate = None
            self.blocked = requested
            self.last_reload = {"status": "failed", "previous": previous, "requested": requested.json(),
                                "error": str(error), "session_lost": not self.active.running}
            recovery = "live session unavailable" if self.last_reload["session_lost"] else "previous worker retained"
            raise RuntimeError(f"Runtime reload failed; {recovery}: {error}") from error
        finally:
            self.checkpoint.unlink(missing_ok=True)
        # Only preparation failures roll back. After this commit the candidate is
        # the active session, including while we retire the old process.
        old = self.active
        changed = old.catalog != self.candidate.catalog
        self.active, self.candidate = self.candidate, None
        self.active.notification = self._notification
        self.blocked = None
        self.last_reload = {"status": "succeeded", "previous": previous, "current": requested.json(),
                            "session_restored": True, "tools_changed": changed}
        if reset_reason is not None:
            self.session_continuable = False
            self.last_reload.update(status="reset", session_restored=False, session_lost=True,
                                    session_continuable=False, reason=reset_reason,
                                    recovery_tools=list(RECOVERY_TOOLS))
        old.close()
        if self.ready and changed:
            self.emit({"jsonrpc": "2.0", "method": "notifications/tools/list_changed"})
        return self.last_reload

    def runtime(self):
        return {"bridge_pid": os.getpid(), "worker_pid": self.active.process.pid,
                "worker_running": self.active.running, "worker_error": self.active.failure,
                "session_continuable": self.session_continuable and self.active.running,
                "recovery_required": not self.session_continuable,
                "recovery_tools": list(RECOVERY_TOOLS) if not self.session_continuable else [],
                "current": self.active.deployment.json(), "last_reload": self.last_reload}

    @staticmethod
    def error(identifier, code, message, data=None):
        error = {"code": code, "message": message}
        if data is not None:
            error["data"] = data
        return {"jsonrpc": "2.0", "id": identifier, "error": error}

    def handle(self, request):
        if not isinstance(request, dict) or request.get("jsonrpc") != "2.0":
            return self.error(None, -32600, "Invalid Request")
        identifier = request.get("id")
        if "id" in request and not (isinstance(identifier, str) or
                type(identifier) is int and -(2**63) <= identifier < 2**64):
            return self.error(None, -32600, "Invalid Request ID")
        if "method" not in request and ("result" in request or "error" in request):
            return None
        method = request.get("method")
        if not isinstance(method, str):
            return self.error(identifier, -32600, "Invalid Request")
        params = request.get("params", {})
        if "id" not in request:
            if method == "notifications/initialized" and self.initialized and isinstance(params, dict):
                self.ready = True
            elif self.ready and isinstance(params, dict) and not method.startswith("runtime/"):
                self.active.notify(method, params)
            return None
        if not isinstance(params, dict):
            return self.error(identifier, -32602, "params must be an object")
        if method.startswith("runtime/"):
            return self.error(identifier, -32601, "Method not found")
        try:
            if method == "initialize":
                if self.initialized:
                    return self.error(identifier, -32600, "Already initialized")
                error, result = self.initialize(params)
                if error:
                    return self.error(identifier, error["code"], error["message"])
                return {"jsonrpc": "2.0", "id": identifier, "result": result}
            if not self.ready:
                if method == "ping":
                    return {"jsonrpc": "2.0", "id": identifier, "result": {}}
                return self.error(identifier, -32000, "Initialize and send notifications/initialized first")
            runtime = method == "tools/call" and params.get("name") == RUNTIME_TOOL["name"]
            try:
                reloaded = self.reload()
            except RuntimeError:
                if not runtime:
                    raise
                reloaded = self.last_reload
            if runtime:
                if params.get("arguments", {}) != {}:
                    return self.error(identifier, -32602, "mcp_runtime takes no arguments")
                value = self.runtime()
                reply = {"result": {"content": [{"type": "text", "text": encode(value)}],
                                    "structuredContent": value, "isError": False}}
            else:
                name = params.get("name") if method == "tools/call" else None
                native_new_game = (name == "game_action" and
                                   isinstance(params.get("arguments"), dict) and
                                   params["arguments"].get("action") == {"type": "new_game"})
                recovery = name in RECOVERY_TOOLS or native_new_game
                if (not self.session_continuable and method == "tools/call" and
                        name not in OBSERVATION_TOOLS and not recovery):
                    return self.error(identifier, -32003,
                                      "The update is active, but the previous session cannot continue. "
                                      "Call new_game, load_game or replay_game before gameplay.",
                                      {"session_continuable": False,
                                       "recovery_tools": list(RECOVERY_TOOLS),
                                       "runtime_reload": self.last_reload})
                reply = self.active.request(method, params)
                if (recovery and "result" in reply and
                        not reply["result"].get("isError", False)):
                    self.session_continuable = True
                if method == "tools/list" and "result" in reply:
                    reply["result"]["tools"] = [*reply["result"]["tools"], RUNTIME_TOOL]
            reply["jsonrpc"], reply["id"] = "2.0", identifier
            if reloaded is not None and isinstance(reply.get("result"), dict):
                result = reply["result"]
                result["_meta"] = {**result.get("_meta", {}), "runtime_reload": reloaded}
            if not self.session_continuable and isinstance(reply.get("result"), dict):
                result = reply["result"]
                result["_meta"] = {**result.get("_meta", {}), "session_continuable": False,
                                   "recovery_tools": list(RECOVERY_TOOLS)}
            return reply
        except (OSError, ValueError, RuntimeError) as error:
            return self.error(identifier, -32000, str(error), {"runtime_reload": self.last_reload})

    def close(self):
        try:
            for worker in (self.candidate, self.active):
                if worker:
                    worker.close()
        finally:
            self.directory.cleanup()


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--manifest", type=Path, default=os.environ.get("TSW_MCP_CURRENT", DEFAULT_MANIFEST))
    parser.add_argument("--developer", action="store_true")
    parser.add_argument("--load", "--save", dest="load", type=Path)
    parser.add_argument("--checkpoint", action="store_true")
    parser.add_argument("--timeout-ms", type=float, default=os.environ.get("TSW_MCP_TIMEOUT_MS", 15000))
    args = parser.parse_args()
    if args.checkpoint and args.load is None:
        parser.error("--checkpoint requires --load FILE")
    if not math.isfinite(args.timeout_ms) or args.timeout_ms <= 0:
        parser.error("--timeout-ms must be positive and finite")
    sys.stdin.reconfigure(encoding="utf-8")
    sys.stdout.reconfigure(encoding="utf-8", newline="\n")
    options = ["--developer"] if args.developer else []
    startup = {"path": str(args.load.resolve()), "kind": "checkpoint" if args.checkpoint else "slot"} if args.load else None
    bridge = Bridge(args.manifest, options, startup, args.timeout_ms / 1000)

    def stop(signum, frame):
        raise KeyboardInterrupt
    signal.signal(signal.SIGTERM, stop)
    try:
        # Requests, activations and actions all run in this single ordered queue.
        while True:
            line = sys.stdin.buffer.readline(MAX_REQUEST_BYTES + 2)
            if not line:
                break
            if len(line) > MAX_REQUEST_BYTES:
                write(bridge.error(None, -32600, "Request exceeds 8 MiB"))
                while line and not line.endswith(b"\n"):
                    line = sys.stdin.buffer.readline(MAX_REQUEST_BYTES + 2)
                continue
            if not line.strip():
                continue
            try:
                reply = bridge.handle(decode(line.decode("utf-8")))
            except (ValueError, UnicodeError, RecursionError):
                reply = bridge.error(None, -32700, "Parse error")
            if reply is not None:
                write(reply)
    except (KeyboardInterrupt, BrokenPipeError):
        pass
    finally:
        bridge.close()


if __name__ == "__main__":
    main()
