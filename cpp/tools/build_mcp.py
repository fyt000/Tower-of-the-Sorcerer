"""Build the C++ CLI and publish an immutable worker for running Python MCP bridges."""
import argparse
import os
from pathlib import Path
import shutil
import subprocess

from mcp_deployment import DEFAULT_MANIFEST, ROOT, deploy_mcp


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--build-dir", type=Path, default=ROOT / "build/cpp/vs" if os.name == "nt"
                        else ROOT / "build/cpp/core", help="Already configured CMake build directory")
    parser.add_argument("--config", default="Release")
    parser.add_argument("--cmake", default=shutil.which("cmake") or "cmake")
    parser.add_argument("--manifest", type=Path, default=DEFAULT_MANIFEST)
    args = parser.parse_args()
    build_dir = args.build_dir.resolve()
    subprocess.run([args.cmake, "--build", str(build_dir), "--config", args.config,
                    "--target", "tsw_cli", "--parallel"], check=True,
                   creationflags=getattr(subprocess, "CREATE_NO_WINDOW", 0))
    name = "tsw_cli.exe" if os.name == "nt" else "tsw_cli"
    binary = build_dir / args.config / name
    if not binary.is_file():
        binary = build_dir / name
    deployment = deploy_mcp(binary, args.manifest)
    print(f"Published MCP worker {deployment.version}. Bridges reload before their next request.")


if __name__ == "__main__":
    main()
