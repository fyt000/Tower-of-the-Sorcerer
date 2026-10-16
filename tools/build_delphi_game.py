"""Build the reconstructed native Delphi project and isolated comparison DLL.

Uses the already-extracted compiler; never runs an installer or the original
game. Original DFM resources are copied exactly. Borland inputs and binaries
remain under ignored build/. Native smoke execution is opt-in with --smoke.
"""
from pathlib import Path
import argparse
import hashlib
import json
import os
import shutil
import struct
import subprocess
import tempfile
import time

import pefile

from build_delphi2_reference import stage
from recovery_evidence import ROOT, ORIGINAL_HASH, digest
from reconstruct_delphi_project import generated, output_path
from review_delphi2_media import validate_media
from verify_delphi_entry import compare_entry

WORK = ROOT / "build/delphi-game"


def smoke_game_instance(artifact, directory):
    cases, children = [], []
    output = []

    def wait_until(condition, message):
        deadline = time.monotonic() + 5
        while not condition():
            if time.monotonic() >= deadline:
                raise RuntimeError(message)
            time.sleep(0.01)

    def start_owner(label, window_class, cwd):
        ready, release = fixtures / f"{label}.ready", fixtures / f"{label}.release"
        arguments = [str(artifact), "--owner", window_class, str(ready), str(release)]
        child = subprocess.Popen(arguments, cwd=cwd, stdout=subprocess.PIPE,
                                 stderr=subprocess.STDOUT, creationflags=subprocess.CREATE_NO_WINDOW)
        children.append(child)
        wait_until(lambda: ready.exists() or child.poll() is not None, f"{label}: window creation timed out")
        if not ready.exists() or child.poll() is not None:
            raise RuntimeError(f"{label}: expected fixture window, exit {child.poll()}")
        return child, release

    def finish(child, release):
        release.write_text("release\n", encoding="ascii")
        result = child.wait(timeout=5)
        if result != 0:
            raise RuntimeError(f"Expected clean release, exit {result}")

    def check(executable, label, cwd, existing):
        warning = fixtures / f"{label}.warning"
        result = subprocess.run([str(executable), "--check", str(warning)], cwd=cwd,
                                capture_output=True, timeout=5,
                                creationflags=subprocess.CREATE_NO_WINDOW)
        expected = 2 if existing else 0
        if result.returncode != expected or warning.exists() != existing:
            detail = (result.stdout + result.stderr).decode("cp1252", errors="replace").strip()
            raise RuntimeError(f"{label}: expected exit {expected}/warning {existing}, "
                               f"got {result.returncode}/warning {warning.exists()}: {detail}")

    def passed(name):
        cases.append(dict(name=name, native_exit=0))
        output.append(f"PASS {name}")

    # Fixture owners do not run the entry guard; challengers check their hidden
    # top-level windows and dismiss only their own exact warning dialog.
    with tempfile.TemporaryDirectory(prefix="fixtures-", dir=directory) as temporary:
        fixtures = Path(temporary).resolve()
        other_cwd = fixtures / "other-cwd"
        other_cwd.mkdir()
        try:
            available = subprocess.run([str(artifact), "--available"], cwd=directory,
                                       capture_output=True, timeout=5,
                                       creationflags=subprocess.CREATE_NO_WINDOW)
            if available.returncode != 0:
                raise RuntimeError("Close the running TTSW10 game window before instance smoke tests")
            owner, release = start_owner("owner", "game", directory)
            check(artifact, "other-cwd", other_cwd, existing=True)
            passed("same executable across working directories")

            copy = fixtures / "InstanceCopy.exe"
            shutil.copyfile(artifact, copy)
            check(copy, "copy", other_cwd, existing=True)
            passed("copied and renamed executable is also blocked")

            alias = fixtures / "InstanceAlias.exe"
            os.link(artifact, alias)
            check(alias, "alias", other_cwd, existing=True)
            passed("hard-link executable alias")

            finish(owner, release)
            check(artifact, "after-release", directory, existing=False)
            passed("startup after clean exit")

            owner, release = start_owner("termination-owner", "game", directory)
            owner.terminate()
            owner.wait(timeout=5)
            check(artifact, "after-termination", directory, existing=False)
            passed("startup after process termination")

            owner, release = start_owner("unrelated-owner", "unrelated", directory)
            check(artifact, "unrelated", directory, existing=False)
            finish(owner, release)
            passed("same title with unrelated window class is allowed")
        except Exception as error:
            cases.append(dict(name="instance enforcement", native_exit=1))
            output.append(f"FAIL {error}")
        finally:
            for child in children:
                if child.poll() is None:
                    child.terminate()
                stdout, _ = child.communicate(timeout=5)
                if stdout:
                    output.append(stdout.decode("cp1252", errors="replace").strip())
    log = directory / "native.log"
    log.write_text("\n".join(output) + "\n", encoding="utf-8")
    return dict(native_exit=max(case["native_exit"] for case in cases), native_cases=cases,
                native_output=log.read_text(encoding="utf-8"), native_log_sha256=digest(log))


def resource_id(value):
    if isinstance(value, int):
        return struct.pack("<HH", 0xFFFF, value)
    return str(value).encode("utf-16le") + b"\0\0"


def resource_record(kind, name, lang, raw, flags=0x1030):
    header = resource_id(kind) + resource_id(name)
    header += bytes((-len(header)) % 4)
    header += struct.pack("<IHHII", 0, flags, lang, 0, 0)
    return struct.pack("<II", len(raw), len(header) + 8) + header + raw + bytes((-len(raw)) % 4)


def resources(original):
    raw = resource_record(0, 0, 0, b"", flags=0)
    records = []
    for kind in original.DIRECTORY_ENTRY_RESOURCE.entries:
        if kind.id != 10:
            continue
        for name in kind.directory.entries:
            for language in name.directory.entries:
                data = language.data.struct
                blob = original.get_data(data.OffsetToData, data.Size)
                if not blob.startswith(b"TPF0"):
                    continue
                raw += resource_record(10, str(name.name), language.id, blob)
                records.append(dict(name=str(name.name), language=language.id,
                                    bytes=len(blob), sha256=hashlib.sha256(blob).hexdigest()))
    if len(records) != 5:
        raise ValueError("Original form resource inventory changed")
    # The statically initialized monster table is game content, not code.
    blob = original.get_data(0x489910 - original.OPTIONAL_HEADER.ImageBase, 528)
    raw += resource_record(10, "MONSTER_STATS", 0, blob)
    content_records = [dict(name="MONSTER_STATS", language=0, bytes=len(blob),
                            sha256=hashlib.sha256(blob).hexdigest())]
    # Original constant table traverses the 121 map cells in a fixed order.
    blob = original.get_data(0x489B20 - original.OPTIONAL_HEADER.ImageBase, 121)
    raw += resource_record(10, "RENDER_ORDER", 0, blob)
    content_records.append(dict(name="RENDER_ORDER", language=0, bytes=len(blob),
                                sha256=hashlib.sha256(blob).hexdigest()))
    icons = []
    calendar = []
    for kind in original.DIRECTORY_ENTRY_RESOURCE.entries:
        if kind.id not in (3, 14):
            continue
        for name in kind.directory.entries:
            for language in name.directory.entries:
                data = language.data.struct
                blob = original.get_data(data.OffsetToData, data.Size)
                identifier = str(name.name) if name.name is not None else name.id
                raw += resource_record(kind.id, identifier, language.id, blob)
                icons.append(dict(kind=kind.id, name=identifier, language=language.id,
                                  bytes=len(blob), sha256=hashlib.sha256(blob).hexdigest()))
    # Japanese RTL weekday/era tables, absent from the English compiler's RTL.
    # Preserve their original payloads; this does not add Japanese RTL code.
    for kind in original.DIRECTORY_ENTRY_RESOURCE.entries:
        if kind.id != 6:
            continue
        for name in kind.directory.entries:
            if name.id not in (4073, 4074):
                continue
            for language in name.directory.entries:
                data = language.data.struct
                blob = original.get_data(data.OffsetToData, data.Size)
                raw += resource_record(6, name.id, language.id, blob)
                calendar.append(dict(kind=6, name=name.id, language=language.id,
                                     bytes=len(blob), sha256=hashlib.sha256(blob).hexdigest()))
    if {(r["name"], r["language"], r["bytes"]) for r in calendar} != {(4073, 0, 120), (4074, 0, 128)}:
        raise ValueError("Original Japanese calendar resource inventory changed")
    (WORK / "GameResources.res").write_bytes(raw)
    return records, content_records, icons, calendar


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--smoke", action="store_true")
    parser.add_argument("--audio-smoke", action="store_true",
                        help="Run audio checks when audio code/assets/configuration changed")
    parser.add_argument("--assets", type=Path, default=Path(r"D:\Program Files (x86)\Tower of the Sorcerer"))
    args = parser.parse_args()
    for name, content in generated().items():
        if output_path(name).read_text(encoding="utf-8") != content:
            raise ValueError("Regenerate stale Delphi source: " + name)
    toolchain = ROOT / "build/research/delphi2"
    validate_media(toolchain)
    original_path = ROOT / "build/research/TSW.exe"
    if digest(original_path) != ORIGINAL_HASH:
        raise ValueError("Original executable changed")
    WORK.mkdir(parents=True, exist_ok=True)
    (WORK / "reports").mkdir(exist_ok=True)
    inputs = []
    source_root = ROOT / "delphi"
    for path in sorted(source_root.rglob("*")):
        if path.suffix.lower() not in (".pas", ".dpr", ".inc"):
            continue
        relative = path.relative_to(source_root)
        target = WORK / relative
        target.parent.mkdir(parents=True, exist_ok=True)
        inputs.append(stage(path, target))
    compiler = toolchain / "base/bin/DCC32.EXE"
    lib = os.path.relpath(toolchain / "base/lib", WORK)
    form_resources, content_resources, icons, calendar = resources(pefile.PE(str(original_path)))
    report = dict(schema_version=1, original_sha256=ORIGINAL_HASH, compiler_sha256=digest(compiler),
                  inputs=inputs, original_form_resources=form_resources,
                  original_content_resources=content_resources, original_icon_resources=icons,
                  original_calendar_resources=calendar, builds={})
    if args.smoke:
        report["graphics_assets"] = [dict(path=str(path.resolve()), sha256=digest(path))
            for folder in ("Data", "Data3") for name in ("center.bmp", "left.bmp", "leftr.bmp", "right.bmp", "rightr.bmp", "title05.bmp", "title05R.bmp", "chtable.oz", "chtableb.oz", "key.oz")
            for path in (args.assets / folder / name,)]
    projects = [("game", "Tower.dpr", False), ("emulator", "tests/CoreProbe.dpr", True),
                ("core-probe", "tests/CoreProbe.dpr", False)]
    if (WORK / "tests/FormSmoke.dpr").exists():
        projects.append(("smoke", "tests/FormSmoke.dpr", False))
    if (WORK / "tests/GraphicsSmoke.dpr").exists():
        projects.append(("graphics", "tests/GraphicsSmoke.dpr", False))
    if (WORK / "tests/StartupIOSmoke.dpr").exists():
        projects.append(("startup-io", "tests/StartupIOSmoke.dpr", False))
    if (WORK / "tests/UISmoke.dpr").exists():
        projects.append(("ui", "tests/UISmoke.dpr", False))
    if (WORK / "tests/RuntimeSmoke.dpr").exists():
        projects.append(("runtime", "tests/RuntimeSmoke.dpr", False))
    if (WORK / "tests/PersistenceSmoke.dpr").exists():
        projects.append(("persistence", "tests/PersistenceSmoke.dpr", False))
    if (WORK / "tests/AudioSmoke.dpr").exists():
        projects.append(("audio", "tests/AudioSmoke.dpr", False))
    if (WORK / "tests/RankingSmoke.dpr").exists():
        projects.append(("ranking", "tests/RankingSmoke.dpr", False))
    if (WORK / "tests/InstanceSmoke.dpr").exists():
        projects.append(("instance", "tests/InstanceSmoke.dpr", False))
    for name, project, absolute in projects:
        dest = WORK / name
        dest.mkdir(exist_ok=True)
        command = [str(compiler), "-B", "-GD", "-U" + lib + ";src", "-Isrc;src\\generated", "-E" + name, "-N" + name]
        if absolute:
            command.append("-DEMULATOR_ADDRESSES")
        command.append(project.replace("/", "\\"))
        result = subprocess.run(command, cwd=WORK, capture_output=True, timeout=30)
        (dest / "compile.log").write_bytes(result.stdout + result.stderr)
        extension = ".dll" if "Probe" in project else ".exe"
        artifact = dest / (Path(project).stem + extension)
        record = dict(arguments=command[1:], compile_exit=result.returncode,
                      compile_log_sha256=digest(dest / "compile.log"))
        report["builds"][name] = record
        print(name, "compile", result.returncode, flush=True)
        if result.returncode:
            print((result.stdout + result.stderr).decode("cp1252", errors="replace"))
            break
        record.update(artifact=str(artifact.relative_to(ROOT)).replace("\\", "/"),
                      artifact_sha256=digest(artifact), map_sha256=digest(artifact.with_suffix(".map")))
        if name == "game" and args.smoke:
            entry = compare_entry(artifact, artifact.with_suffix(".map"))
            record["entry_comparison"] = entry
            (WORK / "reports/entry-comparison.json").write_text(
                json.dumps(entry, indent=2) + "\n", encoding="utf-8")
            print("Program entry comparison", len(entry["cases"]), "cases passed", flush=True)
        if name == "instance" and args.smoke:
            record.update(smoke_game_instance(artifact.resolve(), dest.resolve()))
            print("Single-instance smoke exit", record["native_exit"], flush=True)
            if record["native_exit"]:
                print(record["native_output"])
        if (name in ("persistence", "ranking") and args.smoke) or (name == "audio" and args.audio_smoke):
            fixtures = dest / "fixtures"
            fixtures.mkdir(exist_ok=True)
            arguments = ([str(fixtures.resolve()), str(args.assets.resolve())]
                         if name in ("persistence", "ranking") else [str(args.assets.resolve())])
            result = subprocess.run([str(artifact), *arguments], cwd=dest,
                                    capture_output=True, timeout=60,
                                    creationflags=subprocess.CREATE_NO_WINDOW)
            log = dest / "native.log"
            log.write_bytes(result.stdout + result.stderr)
            record.update(native_exit=result.returncode, native_output=result.stdout.decode("cp1252"),
                          native_log_sha256=digest(log))
            print("Native", name, "smoke exit", result.returncode, flush=True)
            if result.returncode:
                print(record["native_output"][-3000:])
        if name == "runtime" and args.smoke:
            fixtures = dest / "fixtures"
            fixtures.mkdir(exist_ok=True)
            result = subprocess.run([str(artifact), str(args.assets.resolve()), str(fixtures.resolve())],
                                    cwd=dest, capture_output=True, timeout=60,
                                    creationflags=subprocess.CREATE_NO_WINDOW)
            log = dest / "native.log"
            log.write_bytes(result.stdout + result.stderr)
            record.update(native_exit=result.returncode, native_output=result.stdout.decode("cp1252"),
                          native_log_sha256=digest(log))
            print("Native runtime smoke exit", result.returncode, flush=True)
            if result.returncode:
                print(record["native_output"][-3000:])
        if name == "smoke" and args.smoke:
            result = subprocess.run([str(artifact)], cwd=dest, capture_output=True, timeout=30,
                                    creationflags=subprocess.CREATE_NO_WINDOW)
            (dest / "native.log").write_bytes(result.stdout + result.stderr)
            record.update(native_exit=result.returncode, native_output=result.stdout.decode("cp1252"),
                          native_log_sha256=digest(dest / "native.log"))
            observations = record["native_output"].splitlines()
            print("Native smoke exit", result.returncode, "observation lines", len([s for s in observations if s.strip()]))
            if result.returncode:
                print(record["native_output"][-2000:])
        if name == "graphics" and args.smoke:
            record["native_cases"] = []
            for scale, cycle in ((0, 0), (0, 43), (1, 0), (1, 43)):
                output = dest / f"scale{scale}-cycle{cycle}"
                output.mkdir(exist_ok=True)
                result = subprocess.run([str(artifact), str(args.assets.resolve()), str(output), str(scale), str(cycle)],
                                        cwd=dest, capture_output=True, timeout=30,
                                        creationflags=subprocess.CREATE_NO_WINDOW)
                log = output / "native.log"
                log.write_bytes(result.stdout + result.stderr)
                case = dict(scale=scale, cycle=cycle, native_exit=result.returncode,
                            output=str(output.relative_to(ROOT)).replace("\\", "/"),
                            native_output=result.stdout.decode("cp1252"), native_log_sha256=digest(log),
                            bitmaps={p.name: digest(p) for p in sorted(output.glob("*.bmp"))})
                record["native_cases"].append(case)
                print("Graphics smoke", scale, cycle, "exit", result.returncode, flush=True)
                if result.returncode:
                    record["native_exit"] = result.returncode
                    print(case["native_output"][-2000:])
                    break
        if name == "startup-io" and args.smoke:
            fixtures = dest / "fixtures"
            fixtures.mkdir(exist_ok=True)
            result = subprocess.run([str(artifact), str(fixtures.resolve())], cwd=dest, capture_output=True,
                                    timeout=30, creationflags=subprocess.CREATE_NO_WINDOW)
            (dest / "native.log").write_bytes(result.stdout + result.stderr)
            record.update(native_exit=result.returncode, native_output=result.stdout.decode("cp1252"),
                          native_log_sha256=digest(dest / "native.log"),
                          fixtures={p.name: digest(p) for p in sorted(fixtures.glob("*")) if p.is_file()})
            print("Startup I/O boundary smoke exit", result.returncode, flush=True)
            if result.returncode:
                print(record["native_output"][-2000:])
        if name == "ui" and args.smoke:
            output = dest / "captures"
            output.mkdir(exist_ok=True)
            # Clear only generated bitmap artifacts in this verified test directory,
            # so skipped screen captures cannot retain stale/occluded images.
            if not output.resolve().is_relative_to(WORK.resolve()):
                raise ValueError("UI capture directory escaped build workspace")
            for bitmap in output.glob("*.bmp"):
                bitmap.unlink()
            result = subprocess.run([str(artifact), str(args.assets.resolve()), str(output.resolve())],
                                    cwd=dest, capture_output=True, timeout=30,
                                    creationflags=subprocess.CREATE_NO_WINDOW)
            log = output / "native.log"
            log.write_bytes(result.stdout + result.stderr)
            record.update(native_exit=result.returncode, output=str(output.relative_to(ROOT)).replace("\\", "/"),
                          native_output=result.stdout.decode("cp1252"), native_log_sha256=digest(log),
                          bitmaps={p.name: digest(p) for p in sorted(output.glob("*.bmp"))})
            print("Native UI smoke exit", result.returncode, "captures", len(record["bitmaps"]), flush=True)
            if result.returncode:
                print(record["native_output"][-2000:])
    (WORK / "build-report.json").write_text(json.dumps(report, indent=2) + "\n", encoding="utf-8")
    if len(report["builds"]) != len(projects) or any(r["compile_exit"] or r.get("native_exit", 0) for r in report["builds"].values()):
        raise SystemExit("Delphi project build/smoke failed; retained logs")


if __name__ == "__main__":
    main()
