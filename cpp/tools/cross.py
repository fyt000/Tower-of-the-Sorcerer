"""Build, serve and check the Android/WebAssembly game. Each subcommand has --help."""
from __future__ import annotations

import argparse
from functools import partial
from http.server import SimpleHTTPRequestHandler, ThreadingHTTPServer
import os
from pathlib import Path
import shutil
import subprocess
import sys
import zipfile

ROOT = Path(__file__).resolve().parents[2]
SITE = ROOT / "build/cpp/web/site"


def run(command, *, env=None, cwd=ROOT):
    subprocess.run([str(part) for part in command], cwd=cwd, env=env, check=True)


def directory(value, label):
    if not value:
        raise ValueError(f"Set {label} or supply its command-line option; see --help")
    path = Path(value).expanduser().resolve()
    if not path.is_dir():
        raise ValueError(f"{label} directory does not exist: {path}")
    return path


def cmake_command(args, env):
    command = args.cmake
    if not command:
        sdk = env.get("ANDROID_HOME", env.get("ANDROID_SDK_ROOT", ""))
        candidate = Path(sdk) / "cmake/4.1.2/bin" / ("cmake.exe" if os.name == "nt" else "cmake")
        command = str(candidate) if sdk and candidate.is_file() else "cmake"
    resolved = shutil.which(str(command))
    if not resolved:
        raise ValueError(f"CMake was not found: {command}")
    env["PATH"] = str(Path(resolved).parent) + os.pathsep + env.get("PATH", "")
    return resolved


def build_environment(args):
    env = os.environ.copy()
    vcpkg = directory(args.vcpkg or env.get("VCPKG_ROOT"), "VCPKG_ROOT")
    if not (vcpkg / "scripts/buildsystems/vcpkg.cmake").is_file():
        raise ValueError(f"Not a vcpkg checkout: {vcpkg}")
    env["VCPKG_ROOT"] = vcpkg.as_posix()
    return env


def assets(args):
    if args.install:
        run([sys.executable, "-m", "pip", "install", "pillow", "pefile"])
    source = directory(args.source, "original game")
    run([sys.executable, "tools/extract_original.py", "--source", source])
    run([sys.executable, "cpp/tools/extract_ui.py", "--exe", source / "TSW.exe"])


def web(args):
    env = build_environment(args)
    emsdk = directory(args.emsdk or env.get("EMSDK"), "EMSDK")
    emscripten = emsdk / "upstream/emscripten"
    if not (emscripten / "cmake/Modules/Platform/Emscripten.cmake").is_file():
        raise ValueError("Activate an Emscripten SDK first (tested: 5.0.1)")
    env.update(EMSDK=emsdk.as_posix(), EMSCRIPTEN_ROOT=emscripten.as_posix(),
               EM_CONFIG=(emsdk / ".emscripten").as_posix())
    node_dirs = [p for p in (emsdk / "node").glob("*/bin") if p.is_dir()]
    env["PATH"] = os.pathsep.join([str(emscripten), *(str(p) for p in node_dirs), env.get("PATH", "")])
    cmake = cmake_command(args, env)
    command = [cmake, "--preset", "web"]
    if args.assets:
        command.append(f"-DTSW_PORTABLE_ASSETS={Path(args.assets).resolve().as_posix()}")
    run(command, cwd=ROOT / "cpp", env=env)
    run([cmake, "--build", "--preset", "web", "-j", args.jobs], cwd=ROOT / "cpp", env=env)
    archive = SITE.parent / "tower-of-the-sorcerer-web.zip"
    with zipfile.ZipFile(archive, "w", zipfile.ZIP_DEFLATED) as output:
        for file in sorted(SITE.rglob("*")):
            if file.is_file():
                output.write(file, file.relative_to(SITE))
    print(f"Web build: {SITE}\nArchive: {archive}")


def android(args):
    env = build_environment(args)
    sdk = directory(args.sdk or env.get("ANDROID_HOME") or env.get("ANDROID_SDK_ROOT"), "ANDROID_HOME")
    env["ANDROID_HOME"] = sdk.as_posix()
    env["ANDROID_NDK_HOME"] = (sdk / "ndk/30.0.14904198").as_posix()
    if args.jdk:
        env["JAVA_HOME"] = str(directory(args.jdk, "JAVA_HOME"))
        env["PATH"] = str(Path(env["JAVA_HOME"]) / "bin") + os.pathsep + env.get("PATH", "")
    if args.socket_dir:
        path = directory(args.socket_dir, "socket")
        env["JAVA_TOOL_OPTIONS"] = (env.get("JAVA_TOOL_OPTIONS", "") +
                                    f" -Djdk.net.unixdomain.tmpdir={path.as_posix()}").strip()
    cmake_command(args, env)
    gradle = ROOT / "cpp/android/gradlew"
    command = [str(gradle.with_suffix(".bat"))] if os.name == "nt" else ["bash", str(gradle)]
    variant = "release" if args.release else "debug"
    command += ["-p", gradle.parent, f":app:assemble{variant.title()}",
                f"-PandroidAbi={args.abi}", f"-Ppython={sys.executable}", "--console=plain"]
    if args.assets:
        command.append(f"-PassetsDir={Path(args.assets).resolve()}")
    run(command, env=env)
    name = f"app-{variant}{'-unsigned' if args.release else ''}.apk"
    source = ROOT / "cpp/android/app/build/outputs/apk" / variant / name
    abi = "arm64" if args.abi == "arm64-v8a" else args.abi
    destination = ROOT / "build/android/artifacts" / f"tower-of-the-sorcerer-{abi}-{variant}{'-unsigned' if args.release else ''}.apk"
    destination.parent.mkdir(parents=True, exist_ok=True)
    shutil.copyfile(source, destination)
    print(f"APK: {destination}")


def serve(args):
    if not (SITE / "index.html").is_file():
        raise ValueError("Build the web game first: python cpp/tools/cross.py web")
    with ThreadingHTTPServer((args.host, args.port), partial(SimpleHTTPRequestHandler, directory=str(SITE))) as server:
        print(f"Serving {SITE} at http://{args.host}:{server.server_port}; Ctrl+C stops the server", flush=True)
        server.serve_forever()


def check_web(args):
    dependencies = ROOT / "build/browser-tests"
    env = os.environ.copy()
    if args.install:
        run(["npm.cmd" if os.name == "nt" else "npm", "install", "--prefix", dependencies,
             "--no-audit", "--no-fund", "playwright@1.64.1"])
        run(["node", dependencies / "node_modules/playwright/cli.js", "install", "chromium"])
    if not (dependencies / "node_modules/playwright").is_dir():
        raise ValueError("Install the browser test runtime: python cpp/tools/cross.py check-web --install")
    env["NODE_PATH"] = str(dependencies / "node_modules") + os.pathsep + env.get("NODE_PATH", "")
    run(["node", "--test", "cpp/tests/web_storage_tests.cjs", "cpp/tests/web_fonts_tests.cjs"], env=env)
    run(["node", "cpp/tools/check_web.cjs"], env=env)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    commands = parser.add_subparsers(dest="command", required=True)
    media = commands.add_parser("assets", help="extract media from the original installation")
    media.add_argument("--source", required=True)
    media.add_argument("--install", action="store_true", help="install Pillow and pefile first")
    media.set_defaults(function=assets)
    for name, function in [("web", web), ("android", android)]:
        build = commands.add_parser(name, help=f"build and package the {name} game")
        build.add_argument("--vcpkg", help="vcpkg checkout; defaults to VCPKG_ROOT")
        build.add_argument("--cmake", help="CMake executable; defaults to Android SDK CMake, then PATH")
        build.add_argument("--assets", help="extracted media directory; defaults to build/assets")
        if name == "web":
            build.add_argument("--emsdk", help="activated SDK; defaults to EMSDK")
            build.add_argument("--jobs", type=int, default=6)
        else:
            build.add_argument("--sdk", help="Android SDK; defaults to ANDROID_HOME")
            build.add_argument("--jdk", help="JDK 17 directory; defaults to JAVA_HOME")
            build.add_argument("--abi", choices=["arm64-v8a", "x86_64"], default="arm64-v8a")
            build.add_argument("--release", action="store_true", help="produce an unsigned release APK")
            build.add_argument("--socket-dir", help="short existing directory for the Windows JDK loopback workaround")
        build.set_defaults(function=function)
    server = commands.add_parser("serve", help="serve the web build over HTTP")
    server.add_argument("--host", default="127.0.0.1")
    server.add_argument("--port", type=int, default=8000)
    server.set_defaults(function=serve)
    check = commands.add_parser("check-web", help="run storage and desktop/mobile Chromium checks")
    check.add_argument("--install", action="store_true", help="install pinned Playwright and Chromium first")
    check.set_defaults(function=check_web)
    args = parser.parse_args()
    try:
        args.function(args)
    except (ValueError, OSError, subprocess.CalledProcessError) as error:
        parser.exit(1, f"{error}\n")
    except KeyboardInterrupt:
        pass


if __name__ == "__main__":
    main()
