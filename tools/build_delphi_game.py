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

import pefile

from build_delphi2_reference import digest, stage
from reconstruct_delphi_project import generated, OUT
from review_delphi2_media import validate_media
from verify_delphi2_reference import ORIGINAL_HASH

ROOT = Path(__file__).resolve().parents[1]
WORK = ROOT / "build/delphi-game"


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
    raw += resource_record(10, "ORIGINAL_MONSTERS", 0, blob)
    content_records = [dict(name="ORIGINAL_MONSTERS", language=0, bytes=len(blob),
                            sha256=hashlib.sha256(blob).hexdigest())]
    # Original constant table traverses the 121 map cells in a fixed order.
    blob = original.get_data(0x489B20 - original.OPTIONAL_HEADER.ImageBase, 121)
    raw += resource_record(10, "ORIGINAL_RENDER_ORDER", 0, blob)
    content_records.append(dict(name="ORIGINAL_RENDER_ORDER", language=0, bytes=len(blob),
                                sha256=hashlib.sha256(blob).hexdigest()))
    icons = []
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
    (WORK / "OriginalResources.res").write_bytes(raw)
    return records, content_records, icons


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--smoke", action="store_true")
    parser.add_argument("--assets", type=Path, default=Path(r"D:\Program Files (x86)\Tower of the Sorcerer"))
    args = parser.parse_args()
    for name, content in generated().items():
        if (OUT / name).read_text(encoding="utf-8") != content:
            raise ValueError("Regenerate stale Delphi source: " + name)
    toolchain = ROOT / "build/research/delphi2"
    validate_media(toolchain)
    original_path = ROOT / "build/research/TSW.exe"
    if digest(original_path) != ORIGINAL_HASH:
        raise ValueError("Original executable changed")
    WORK.mkdir(parents=True, exist_ok=True)
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
    form_resources, content_resources, icons = resources(pefile.PE(str(original_path)))
    report = dict(schema_version=1, original_sha256=ORIGINAL_HASH, compiler_sha256=digest(compiler),
                  inputs=inputs, original_form_resources=form_resources,
                  original_content_resources=content_resources, original_icon_resources=icons, builds={})
    if args.smoke:
        report["graphics_assets"] = [dict(path=str(path.resolve()), sha256=digest(path))
            for folder in ("Data", "Data3") for name in ("center.bmp", "left.bmp", "leftr.bmp", "right.bmp", "rightr.bmp", "title05.bmp", "title05R.bmp", "chtable.oz", "chtableb.oz", "key.oz")
            for path in (args.assets / folder / name,)]
    projects = [("native", "Tower.dpr", False), ("emulator", "tests/CoreRecoveryProbe.dpr", True),
                ("native-core", "tests/CoreRecoveryProbe.dpr", False)]
    if (WORK / "tests/FormSmoke.dpr").exists():
        projects.append(("smoke", "tests/FormSmoke.dpr", False))
    if (WORK / "tests/GraphicsSmoke.dpr").exists():
        projects.append(("graphics", "tests/GraphicsSmoke.dpr", False))
    if (WORK / "tests/StartupIOSmoke.dpr").exists():
        projects.append(("startup-io", "tests/StartupIOSmoke.dpr", False))
    if (WORK / "tests/UISmoke.dpr").exists():
        projects.append(("ui", "tests/UISmoke.dpr", False))
    for name, project, absolute in projects:
        dest = WORK / name
        dest.mkdir(exist_ok=True)
        command = [str(compiler), "-B", "-GD", "-U" + lib + ";src", "-Isrc;src\\generated", "-E" + name, "-N" + name]
        if absolute:
            command.append("-DORIGINAL_ADDRESSES")
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
