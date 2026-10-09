"""Build isolated Delphi-2 probes with base and explicitly selected update DCUs.

This never launches TSW.exe. The generated recovery DLL is read as PE bytes
by the comparison tool, never loaded natively. Borland inputs stay in build/.
Requires tools/prepare_delphi2_reference.py to have prepared the toolchain.
"""
from pathlib import Path
import argparse
import hashlib
import json
import os
import shutil
import subprocess

ROOT = Path(__file__).resolve().parents[1]


def digest(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()


def stage(source, destination):
    raw = source.read_bytes()
    # Delphi 2's source reader requires CRLF; keep tracked sources unchanged.
    destination.write_bytes(raw.replace(b"\r\n", b"\n").replace(b"\n", b"\r\n"))
    return dict(source=str(source.relative_to(ROOT)).replace("\\", "/"),
                source_sha256=digest(source), staged_sha256=digest(destination))


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--toolchain", type=Path, default=ROOT / "build/research/delphi2")
    parser.add_argument("--no-run", action="store_true")
    args = parser.parse_args()
    toolchain = args.toolchain.resolve()
    compiler = toolchain / "base/bin/DCC32.EXE"
    media = json.loads((toolchain / "media-manifest.json").read_text())
    # Reject altered extracted inputs, including the separate update units.
    for record in [r for r in media["files"] if "extracted_path" in r] + media["updates"]:
        path = toolchain / record.get("extracted_path", record["path"])
        if not path.exists() or digest(path) != record["sha256"]:
            raise ValueError(f"Toolchain input changed: {path}")
    variants = {
        "base": [],
        "forms-update": ["FORMS.dcu"],
        "system-update": ["SYSTEM.DCU"],
        "all-updates": [p.name for p in sorted((toolchain / "updates").glob("*.dcu"))],
    }
    report = dict(schema_version=1, compiler_sha256=digest(compiler),
                  media_manifest_sha256=digest(toolchain / "media-manifest.json"),
                  variants={}, recovery={})
    for name, updates in variants.items():
        work = toolchain / ("probe-" + name)
        work.mkdir(exist_ok=True)
        record = dict(updates=updates, inputs=[])
        record["inputs"].append(stage(ROOT / "reference/delphi2/probes/RuntimeProbe.dpr", work / "RuntimeProbe.dpr"))
        lib = work / "override"
        lib.mkdir(exist_ok=True)
        if set(p.name for p in lib.iterdir()) - set(updates):
            raise ValueError("Unexpected stale override unit")
        for update in updates:
            shutil.copyfile(toolchain / "updates" / update, lib / update)
        unit_path = "override;..\\base\\lib" if updates else "..\\base\\lib"
        command = [str(compiler), "-B", "-U" + unit_path, "-GD", "RuntimeProbe.dpr"]
        result = subprocess.run(command, cwd=work, capture_output=True, timeout=30)
        log = result.stdout + result.stderr
        (work / "compile.log").write_bytes(log)
        record["compile"] = dict(exit_code=result.returncode, arguments=command[1:],
                                 log_sha256=digest(work / "compile.log"))
        if result.returncode == 0:
            for file in ("RuntimeProbe.exe", "RuntimeProbe.map"):
                record[file] = dict(sha256=digest(work / file), bytes=(work / file).stat().st_size)
            if not args.no_run:
                flags = subprocess.CREATE_NO_WINDOW if os.name == "nt" else 0
                result = subprocess.run([str(work / "RuntimeProbe.exe")], cwd=work,
                                        capture_output=True, timeout=10, creationflags=flags)
                (work / "native.log").write_bytes(result.stdout + result.stderr)
                record["native"] = dict(exit_code=result.returncode,
                                         observations=[json.loads(line) for line in result.stdout.decode("cp1252").splitlines() if line.strip()],
                                         log_sha256=digest(work / "native.log"))
        report["variants"][name] = record
        print(name, "compile", record["compile"]["exit_code"],
              "native", record.get("native", {}).get("exit_code"), flush=True)
    work = toolchain / "recovery-probe"
    work.mkdir(exist_ok=True)
    record = report["recovery"]
    record["inputs"] = [stage(ROOT / source, work / Path(source).name) for source in
                        ("reference/delphi2/probes/RecoveryProbe.dpr",
                         "reference/delphi2/recovered/RecoveredNeighbor.pas")]
    command = [str(compiler), "-B", "-U..\\base\\lib", "-GD", "RecoveryProbe.dpr"]
    result = subprocess.run(command, cwd=work, capture_output=True, timeout=30)
    (work / "compile.log").write_bytes(result.stdout + result.stderr)
    record["compile"] = dict(exit_code=result.returncode, arguments=command[1:],
                             log_sha256=digest(work / "compile.log"))
    if result.returncode == 0:
        for name in ("RecoveryProbe.dll", "RecoveryProbe.map"):
            record[name] = dict(sha256=digest(work / name), bytes=(work / name).stat().st_size)
    (toolchain / "build-report.json").write_text(json.dumps(report, indent=2) + "\n", encoding="utf-8")
    failures = [name for name, record in report["variants"].items()
                if record["compile"]["exit_code"] or
                ("native" in record and (record["native"]["exit_code"] or
                 any(not o["passed"] for o in record["native"]["observations"] if "passed" in o)))]
    if report["recovery"]["compile"]["exit_code"] or failures:
        raise SystemExit(f"Probe compilation/execution failed: {failures}; inspect retained logs")


if __name__ == "__main__":
    main()
