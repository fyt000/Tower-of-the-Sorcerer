"""Publish immutable C++ MCP workers after a native migration smoke test."""
import argparse
from dataclasses import asdict, dataclass
from datetime import datetime, timezone
import hashlib
import json
import os
from pathlib import Path
import platform
import shutil
import struct
from tempfile import TemporaryDirectory
import uuid


ROOT = Path(__file__).resolve().parents[2]
DEFAULT_MANIFEST = ROOT / "build/cpp/dist/mcp/current.json"


def validate_worker_executable(executable):
    if os.name != "nt":
        return
    # CreateProcess can open a modal 16-bit loader dialog for malformed images.
    # Check the PE/COFF header before asking Windows to run a console worker.
    # https://learn.microsoft.com/en-us/windows/win32/debug/pe-format
    executable = Path(executable)
    with executable.open("rb") as stream:
        size = os.fstat(stream.fileno()).st_size
        dos = stream.read(64)
        if len(dos) != 64 or dos[:2] != b"MZ":
            raise ValueError(f"Worker is not a native Windows PE executable: {executable}")
        offset = struct.unpack_from("<I", dos, 0x3C)[0]
        if offset < 64 or offset > size - 24:
            raise ValueError(f"Invalid Windows worker PE header: {executable}")
        stream.seek(offset)
        header = stream.read(24)
        if len(header) != 24 or header[:4] != b"PE\0\0":
            raise ValueError(f"Worker is not a native Windows PE executable: {executable}")
        machine, sections = struct.unpack_from("<HH", header, 4)
        optional_size, flags = struct.unpack_from("<HH", header, 20)
        if not 1 <= sections <= 96 or optional_size < 96 or not flags & 0x2 or flags & 0x2000:
            raise ValueError(f"Invalid Windows worker executable headers: {executable}")
        if offset + 24 + optional_size + sections * 40 > size:
            raise ValueError(f"Truncated Windows worker executable: {executable}")
        optional = stream.read(optional_size)
        if len(optional) != optional_size:
            raise ValueError(f"Truncated Windows worker executable: {executable}")
        magic = struct.unpack_from("<H", optional)[0]
        if magic not in (0x10B, 0x20B) or (magic == 0x20B and optional_size < 112):
            raise ValueError(f"Unsupported Windows worker image format: {executable}")
        if struct.unpack_from("<H", optional, 68)[0] != 3:
            raise ValueError(f"Windows worker must be a console executable: {executable}")
        host = platform.machine().lower()
        supported = {0x14C, 0x8664}
        if host in ("arm64", "aarch64"):
            supported |= {0xAA64, 0xA641, 0xA64E}
        elif host in ("x86", "i386", "i686"):
            supported = {0x14C}
        if machine not in supported:
            raise ValueError(f"Unsupported Windows worker architecture: {executable}")


@dataclass(frozen=True)
class Deployment:
    version: str
    activation: str
    executable: str

    def json(self):
        return asdict(self)


def read_deployment(manifest):
    manifest = Path(manifest).resolve()
    value = json.loads(manifest.read_text(encoding="utf-8"))
    if not isinstance(value, dict):
        raise ValueError("Deployment manifest must be an object")
    for key in ("version", "activation", "executable"):
        if not isinstance(value.get(key), str) or not value[key] or "\0" in value[key]:
            raise ValueError(f"Manifest requires a nonempty {key}")
    executable = Path(value["executable"])
    if not executable.is_absolute():
        executable = manifest.parent / executable
    return Deployment(value["version"], value["activation"], str(executable.resolve()))


def deploy_mcp(binary, manifest=DEFAULT_MANIFEST, timeout=15):
    # Import here so the bridge can use manifest utilities without an import cycle.
    from mcp_server import Worker, default_initialization

    binary, manifest = Path(binary).resolve(), Path(manifest).resolve()
    fingerprint = hashlib.sha256(binary.read_bytes()).hexdigest()
    activation = uuid.uuid4().hex
    timestamp = datetime.now(timezone.utc).strftime("%Y-%m-%dT%H-%M-%S-%fZ")
    version = f"{timestamp}-{fingerprint[:12]}-{activation[:8]}"
    directory = manifest.parent / "versions" / version
    directory.mkdir(parents=True, exist_ok=False)
    executable = directory / ("tsw_cli.exe" if os.name == "nt" else "tsw_cli")
    temporary = manifest.with_name(f"{manifest.name}.{activation}.tmp")
    worker = None
    published = False
    try:
        shutil.copy2(binary, executable)
        validate_worker_executable(executable)
        selected = Deployment(version, activation, str(executable))
        with TemporaryDirectory(prefix="tsw-mcp-probe-") as folder:
            worker = Worker(selected, [], timeout)
            worker.prepare(default_initialization())
            checkpoint = str(Path(folder) / "checkpoint.json")
            saved = worker.required("runtime/checkpoint", {"path": checkpoint})
            restored = worker.required("runtime/restore", {"path": checkpoint})
            if saved.get("version") != 1 or restored.get("restored") is not True:
                raise RuntimeError("Worker did not confirm checkpoint/restore compatibility")
            worker.close()
            worker = None
        deployment = Deployment(version, activation, executable.relative_to(manifest.parent).as_posix())
        temporary.write_text(json.dumps(deployment.json(), indent=2) + "\n", encoding="utf-8")
        # Readers see the complete old manifest or the complete new manifest.
        os.replace(temporary, manifest)
        published = True
        return deployment
    finally:
        if worker is not None:
            worker.close()
        temporary.unlink(missing_ok=True)
        if not published:
            if directory.resolve().parent != (manifest.parent / "versions").resolve():
                raise RuntimeError("Refusing to remove a failed publication outside its versions directory")
            shutil.rmtree(directory)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("binary", type=Path, help="Built tsw_cli executable")
    parser.add_argument("--manifest", type=Path, default=DEFAULT_MANIFEST)
    args = parser.parse_args()
    deployment = deploy_mcp(args.binary, args.manifest)
    print(f"Published MCP worker {deployment.version}. Bridges reload before their next request.")


if __name__ == "__main__":
    main()
