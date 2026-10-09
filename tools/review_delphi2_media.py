"""Compare additional user-supplied Delphi media without installing the IDE.

Builds only private framework EXEs and emulator-only recovery DLLs. All Borland
inputs and compiled binaries remain under build/research. --check verifies the
retained builds and regenerates the evidence without rerunning native programs.
"""
from pathlib import Path
import argparse
import hashlib
import json
import os
import subprocess
import zipfile

import pefile

from build_delphi2_reference import stage
from verify_delphi2_reference import (
    ROOT, ORIGINAL_HASH, RUNTIME, digest, framework_cases, gameplay_comparison,
    instructions, normalized, original_span, symbols,
)

MEDIA = {
    "desktop7z": ("Borland Delphi Desktop 2.0(1).7z", "desktop7z/Borland Delphi Desktop 2.0/DATA.Z"),
    "desktopiso": ("2.0 Desktop_Borland_Delphi_2.iso", "desktopiso/DATA.Z"),
    "english7z": ("Borland Delphi for Windows 32.ver.2.0.English.7z", "english7z/Delphi2/DATA.Z"),
    "system201": ("System.dcu.ver.2.01.English.zip", "system201/SYSTEM.DCU"),
}


def describe(path):
    return dict(path=str(path.resolve()), bytes=path.stat().st_size, sha256=digest(path))


def validate_media(path):
    manifest = json.loads((path / "media-manifest.json").read_text())
    for record in manifest["files"] + manifest["updates"]:
        name = record.get("extracted_path")
        if not name and record in manifest["updates"]:
            name = record["path"]
        if name and digest(path / name) != record["sha256"]:
            raise ValueError(f"Altered baseline input: {name}")
    payload = Path(manifest["media_path"]) / "DATA.Z"
    if digest(payload) != manifest["payload_sha256"]:
        raise ValueError("Altered baseline archive payload")
    if digest(Path(manifest["archive"]["path"])) != manifest["archive"]["sha256"]:
        raise ValueError("Altered supplied archive")
    return manifest


def build_probes(desktop, system):
    compiler = desktop / "base/bin/DCC32.EXE"
    build = dict(compiler=describe(compiler), manifest=describe(desktop / "media-manifest.json"),
                 system201=describe(system), variants={}, recovery={})
    for name in ("base", "system201"):
        work = desktop / ("media-probe-" + name)
        work.mkdir(exist_ok=True)
        inputs = [stage(ROOT / "reference/delphi2/probes/RuntimeProbe.dpr", work / "RuntimeProbe.dpr")]
        override = work / "override"
        override.mkdir(exist_ok=True)
        expected = {"SYSTEM.DCU"} if name == "system201" else set()
        if set(p.name.upper() for p in override.iterdir()) - expected:
            raise ValueError("Unexpected probe override input")
        if name == "system201":
            (override / "SYSTEM.DCU").write_bytes(system.read_bytes())
        command = [str(compiler), "-B", "-Uoverride;..\\base\\lib", "-GD", "RuntimeProbe.dpr"]
        result = subprocess.run(command, cwd=work, capture_output=True, timeout=30)
        (work / "compile.log").write_bytes(result.stdout + result.stderr)
        record = dict(inputs=inputs, arguments=command[1:], compile_exit=result.returncode,
                      compile_log=describe(work / "compile.log"))
        build["variants"][name] = record
        if result.returncode:
            raise ValueError(f"Probe compilation failed: {work}")
        record["artifacts"] = [describe(work / f) for f in ("RuntimeProbe.exe", "RuntimeProbe.map")]
        result = subprocess.run([str(work / "RuntimeProbe.exe")], cwd=work, capture_output=True,
                                timeout=10, creationflags=subprocess.CREATE_NO_WINDOW if os.name == "nt" else 0)
        (work / "native.log").write_bytes(result.stdout + result.stderr)
        record["native_exit"] = result.returncode
        record["native_log"] = describe(work / "native.log")
        record["observations"] = [json.loads(line) for line in result.stdout.decode("cp1252").splitlines() if line.strip()]
        if result.returncode or any(not o["passed"] for o in record["observations"] if "passed" in o):
            raise ValueError(f"Native probe failed: {work}")
        print(name, "compiled; native checks", sum("passed" in o for o in record["observations"]), flush=True)
    work = desktop / "media-recovery-probe"
    work.mkdir(exist_ok=True)
    record = build["recovery"]
    record["inputs"] = [stage(ROOT / name, work / Path(name).name) for name in
                        ("reference/delphi2/probes/RecoveryProbe.dpr", "reference/delphi2/recovered/RecoveredNeighbor.pas")]
    command = [str(compiler), "-B", "-U..\\base\\lib", "-GD", "RecoveryProbe.dpr"]
    result = subprocess.run(command, cwd=work, capture_output=True, timeout=30)
    (work / "compile.log").write_bytes(result.stdout + result.stderr)
    record.update(arguments=command[1:], compile_exit=result.returncode,
                  compile_log=describe(work / "compile.log"))
    if result.returncode:
        raise ValueError("Recovery probe failed to compile")
    record["artifacts"] = [describe(work / f) for f in ("RecoveryProbe.dll", "RecoveryProbe.map")]
    (desktop / "media-build-report.json").write_text(json.dumps(build, indent=2) + "\n", encoding="utf-8")
    return build


def validate_build(desktop, build):
    for record in (build["compiler"], build["manifest"], build["system201"]):
        if digest(Path(record["path"])) != record["sha256"]:
            raise ValueError("Build input changed")
    for name, record in [*build["variants"].items(), ("recovery", build["recovery"])]:
        work = desktop / ("media-recovery-probe" if name == "recovery" else "media-probe-" + name)
        for source in record["inputs"]:
            if digest(ROOT / source["source"]) != source["source_sha256"] or digest(work / Path(source["source"]).name) != source["staged_sha256"]:
                raise ValueError("Pascal probe source changed")
        for artifact in record["artifacts"] + [record["compile_log"]] + ([record["native_log"]] if "native_log" in record else []):
            if digest(Path(artifact["path"])) != artifact["sha256"]:
                raise ValueError("Probe artifact changed")
        if name == "system201" and digest(work / "override/SYSTEM.DCU") != build["system201"]["sha256"]:
            raise ValueError("System overlay changed")
        if "native_log" in record:
            observations = [json.loads(line) for line in Path(record["native_log"]["path"]).read_text(encoding="cp1252").splitlines() if line.strip()]
            if observations != record["observations"]:
                raise ValueError("Native log differs from retained observations")


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--downloads", type=Path, default=Path("D:/Downloads"))
    parser.add_argument("--check", action="store_true")
    args = parser.parse_args()
    media = ROOT / "build/research/delphi2-additional-media"
    desktop = ROOT / "build/research/delphi2-desktop"
    client = ROOT / "build/research/delphi2"
    manifests = {"desktop": validate_media(desktop), "client_server": validate_media(client)}
    report = dict(schema_version=1, original_sha256=ORIGINAL_HASH, supplied_media={})
    for name, (archive, payload) in MEDIA.items():
        report["supplied_media"][name] = dict(archive=describe(args.downloads / archive), payload=describe(media / payload))
    system = media / MEDIA["system201"][1]
    with zipfile.ZipFile(args.downloads / MEDIA["system201"][0]) as archive:
        if archive.read("SYSTEM.DCU") != system.read_bytes() or archive.read("README.TXT") != (system.parent / "README.TXT").read_bytes():
            raise ValueError("2.01 extraction differs from ZIP input")
    report["system201_readme"] = describe(system.parent / "README.TXT")
    report["desktop_payloads_identical"] = len({report["supplied_media"][k]["payload"]["sha256"] for k in ("desktop7z", "desktopiso", "english7z")}) == 1
    report["system201_identical_to_previous_update"] = digest(system) == digest(client / "updates/SYSTEM.DCU")
    report["baseline_key_files"] = {}
    for name, manifest in manifests.items():
        report["baseline_key_files"][name] = [r for r in manifest["files"] if "extracted_path" in r and
            Path(r["path"]).name.upper() in {"DCC32.EXE", "SYSTEM.DCU", "CONTROLS.DCU", "FORMS.DCU", "STDCTRLS.DCU", "EXTCTRLS.DCU", "IMM.PAS"}]
    build = json.loads((desktop / "media-build-report.json").read_text()) if args.check else build_probes(desktop, system)
    validate_build(desktop, build)
    report["build_report"] = describe(desktop / "media-build-report.json")
    original_path = ROOT / "build/research/TSW.exe"
    if digest(original_path) != ORIGINAL_HASH:
        raise ValueError("Original EXE differs from pin")
    original = pefile.PE(str(original_path))
    inventory_path = ROOT / "reference/original/whole-program/structural-inventory.json"
    inventory = json.loads(inventory_path.read_text())
    sizes = {c["name"]: c["instance_size"] for c in inventory["classes"]}
    report["variants"] = {}
    for name, built in build["variants"].items():
        work = desktop / ("media-probe-" + name)
        pe = pefile.PE(str(work / "RuntimeProbe.exe"))
        entries = symbols(pe, work / "RuntimeProbe.map")
        record = dict(exe=describe(work / "RuntimeProbe.exe"),
                      code_sha256=hashlib.sha256(pe.sections[0].get_data()).hexdigest(),
                      native_observations=built["observations"], native_exit=built["native_exit"],
                      framework_cases=framework_cases(pe, entries), runtime_shapes=[])
        record["layouts"] = [dict(class_name=o["name"].split(".")[0], original=sizes[o["name"].split(".")[0]], compiled=o["value"])
                             for o in built["observations"] if "passed" not in o]
        for symbol, address in RUNTIME.items():
            size = original_span(address)
            a, ma = normalized(original, instructions(original, address, size))
            item = dict(symbol=symbol, original_address=f"0x{address:08x}", compiled_address=f"0x{entries[symbol]:08x}",
                        bytes=size, original_masked_operands=ma)
            try:
                b, mb = normalized(pe, instructions(pe, entries[symbol], size))
                item.update(normalized_shape_match=a == b, compiled_masked_operands=mb)
            except ValueError as error:
                item.update(normalized_shape_match=False, decode_error=str(error))
            record["runtime_shapes"].append(item)
        report["variants"][name] = record
    report["reconstruction"] = gameplay_comparison(original, pefile.PE(str(desktop / "media-recovery-probe/RecoveryProbe.dll")))
    report["ime_evidence"] = dict(inventory=describe(inventory_path),
        original_enum=next(t for t in inventory["referenced_types"] if t["name"] == "TImeMode"),
        original_properties=[dict(class_name=c["name"], property=p) for c in inventory["classes"] for p in c["properties"]
                             if p["name"] in ("ImeMode", "OnKeyDown", "OnEnter") and c["name"] in ("TForm", "TButton")],
        constructor_initialization="0x00414424: byte [Self+$D4] := 0",
        control_methods=["0x00415DA4 reads byte [Self+$D4] and calls 0x0040EE88",
                         "0x00415DBC tests byte [Self+$D4] against 1 and calls 0x0040EE6C"],
        ime_dispatcher="0x0040EE88", dynamic_api_initializer="0x0040EFA0",
        english_controls_source_contains_ime_mode="ImeMode" in (client / "base/source/VCL/CONTROLS.PAS").read_text(encoding="cp1252"),
        conclusion="Original has an IME field and executable IME interactions absent from supplied English Controls source; exact library release remains unverified.")
    report["status"] = dict(
        native_framework_checks_passed=all(r["native_exit"] == 0 and all(o["passed"] for o in r["native_observations"] if "passed" in o) for r in report["variants"].values()),
        framework_fixtures_passed=all(c["passed"] for r in report["variants"].values() for c in r["framework_cases"]),
        gameplay_reconstruction_passed=report["reconstruction"]["passed"],
        complete_runtime_baseline_accepted=False, full_pascal_game_recovered=False,
        additional_cpp_gameplay_discrepancy_demonstrated=False)
    report["limits"] = ["Three repackaged Desktop payloads constitute one additional baseline.",
        "2.01 ZIP provenance is its contents, not authentication of the archive label.",
        "IME layout explains the offset shift; it does not identify the precise Delphi release or validate a rebuilt VCL.",
        "Selected runtime shapes mask addresses and external transfers; callee equivalence is not established.",
        "No original game process, campaign or game screenshot comparison was run."]
    target = ROOT / "reference/delphi2/media-review.json"
    text = json.dumps(report, indent=2) + "\n"
    if args.check:
        if target.read_text(encoding="utf-8") != text:
            raise ValueError("Stale additional-media report")
    else:
        target.write_text(text, encoding="utf-8")
    for name, record in report["variants"].items():
        print(name, "shapes", sum(r["normalized_shape_match"] for r in record["runtime_shapes"]), "/", len(RUNTIME),
              "layouts", [(r["class_name"], r["compiled"], r["original"]) for r in record["layouts"]])
    print("Reconstruction", report["reconstruction"]["literal_byte_match"], report["reconstruction"]["cases"], "cases")
    if not all(report["status"][k] for k in ("native_framework_checks_passed", "framework_fixtures_passed", "gameplay_reconstruction_passed")):
        raise SystemExit("Measured comparison failed; inspect report")


if __name__ == "__main__":
    main()
