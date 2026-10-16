"""Capture/check Delphi builds without allowing code, data or layout drift.

Unlike compare_delphi_routines.py (original Japanese build versus recovery),
this compares two builds of the recovery itself. Only the four-byte timestamps
in corresponding PE resource-directory headers may differ. No relocation,
padding, instruction or resource-payload bytes are normalized.
"""
import argparse
import hashlib
import json
from pathlib import Path
import shutil

import pefile

from recovery_evidence import ROOT

WORK = ROOT / "build/delphi-game"


def sha(raw):
    return hashlib.sha256(raw).hexdigest()


def resource_timestamps(raw):
    """Locate actual IMAGE_RESOURCE_DIRECTORY.TimeDateStamp fields."""
    pe = pefile.PE(data=raw)
    fields = {}

    def visit(directory, identity):
        offset = directory.struct.get_field_absolute_offset("TimeDateStamp")
        fields[identity] = offset
        for entry in directory.entries:
            if hasattr(entry, "directory"):
                key = ("name", str(entry.name)) if entry.name is not None else ("id", entry.id)
                visit(entry.directory, identity + (key,))

    if hasattr(pe, "DIRECTORY_ENTRY_RESOURCE"):
        visit(pe.DIRECTORY_ENTRY_RESOURCE, ())
    pe.close()
    return fields


def compare_images(before, after):
    old_fields, new_fields = resource_timestamps(before), resource_timestamps(after)
    same_directories = old_fields == new_fields
    allowed = {offset + byte for offset in old_fields.values() for byte in range(4)} if same_directories else set()
    differences = [i for i in range(min(len(before), len(after))) if before[i] != after[i]]
    unexpected = [i for i in differences if i not in allowed]
    passed = same_directories and len(before) == len(after) and not unexpected
    return dict(passed=passed, before_sha256=sha(before), after_sha256=sha(after),
                before_bytes=len(before), after_bytes=len(after), exact_bytes_equal=before == after,
                resource_directory_layout_equal=same_directories,
                resource_timestamp_fields=len(old_fields),
                differing_timestamp_bytes=sum(i in allowed for i in differences),
                unexpected_differing_bytes=len(unexpected), first_unexpected_offsets=unexpected[:16])


def validate_build_inputs(report, work):
    for record in report["inputs"]:
        source = ROOT / record["source"]
        staged = work / Path(record["source"]).relative_to("delphi")
        if sha(source.read_bytes()) != record["source_sha256"]:
            raise ValueError("Source changed since build: " + record["source"])
        if sha(staged.read_bytes()) != record["staged_sha256"]:
            raise ValueError("Staged source changed since build: " + record["source"])


def capture(baseline, work=WORK):
    # Never replace a baseline with a candidate accidentally.
    baseline.mkdir(parents=True, exist_ok=False)
    report = json.loads((work / "build-report.json").read_text())
    validate_build_inputs(report, work)
    artifacts = []
    for name, record in report["builds"].items():
        if record["compile_exit"]:
            raise ValueError("Unsuccessful baseline build: " + name)
        path = ROOT / record["artifact"]
        raw = path.read_bytes()
        if sha(raw) != record["artifact_sha256"]:
            raise ValueError("Stale baseline build: " + name)
        relative = path.relative_to(work)
        target = baseline / relative
        target.parent.mkdir(parents=True, exist_ok=True)
        shutil.copyfile(path, target)
        artifacts.append(dict(name=name, path=relative.as_posix(), sha256=sha(raw)))
    manifest = dict(compiler_sha256=report["compiler_sha256"], inputs=report["inputs"], artifacts=artifacts)
    (baseline / "manifest.json").write_text(json.dumps(manifest, indent=2) + "\n")
    print(f"Captured {len(artifacts)} Delphi artifacts in {baseline}")


def check(baseline, work=WORK):
    manifest = json.loads((baseline / "manifest.json").read_text())
    build = json.loads((work / "build-report.json").read_text())
    validate_build_inputs(build, work)
    if build["compiler_sha256"] != manifest["compiler_sha256"]:
        raise ValueError("Candidate compiler differs from baseline")
    if set(build["builds"]) != {row["name"] for row in manifest["artifacts"]}:
        raise ValueError("Candidate artifact inventory differs from baseline")
    results = []
    for row in manifest["artifacts"]:
        before = (baseline / row["path"]).read_bytes()
        after = (work / row["path"]).read_bytes()
        current = build["builds"][row["name"]]
        if sha(before) != row["sha256"] or current["compile_exit"] or sha(after) != current["artifact_sha256"]:
            raise ValueError("Stale or unsuccessful comparison input: " + row["name"])
        results.append(dict(name=row["name"], **compare_images(before, after)))
    report = dict(passed=all(row["passed"] for row in results), baseline=str(baseline), artifacts=results,
                  allowed_difference="Corresponding PE resource-directory TimeDateStamp fields only")
    output = work / "reports/constant-cleanup-comparison.json"
    output.write_text(json.dumps(report, indent=2) + "\n")
    for row in results:
        print(row["name"], "PASS" if row["passed"] else "FAIL",
              "unexpected bytes", row["unexpected_differing_bytes"],
              "timestamp bytes", row["differing_timestamp_bytes"])
    if not report["passed"]:
        raise SystemExit("Delphi build drift; see " + str(output))


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("command", choices=("capture", "check"))
    parser.add_argument("baseline", type=Path)
    args = parser.parse_args()
    (capture if args.command == "capture" else check)(args.baseline.resolve())


if __name__ == "__main__":
    main()
