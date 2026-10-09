"""Run the retained original comparisons and require reviewed skip boundaries.

Requires the pinned original EXE and pefile/capstone/unicorn. Reports are
regenerated against one compiled probe; a passing subset is not a full audit.
"""
from pathlib import Path
import argparse
import hashlib
import json
import subprocess
import sys

ROOT = Path(__file__).resolve().parents[2]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--probe", type=Path, default=ROOT / "build/cpp/vs/Release/tsw_probe.exe")
    args = parser.parse_args()
    digest = hashlib.sha256(args.probe.read_bytes()).hexdigest()
    reports = {}
    result = subprocess.run([sys.executable, str(ROOT / "tools/review_whole_program.py"), "--check"], cwd=ROOT)
    if result.returncode:
        return result.returncode
    result = subprocess.run([sys.executable, str(ROOT / "tools/review_original_presentation.py"), "--check"], cwd=ROOT)
    if result.returncode:
        return result.returncode
    suites = (("differential.py", "differential"), ("verify_interactions.py", "interaction"),
              ("verify_callbacks.py", "callback"), ("verify_items.py", "item"),
              ("verify_saves.py", "save"), ("verify_quirks.py", "quirk"), ("verify_flight.py", "flight"),
              ("verify_presentation.py", "ui-sequence"))
    for script, name in suites:
        print(f"Running {script}", flush=True)
        result = subprocess.run([sys.executable, str(Path(__file__).with_name(script)),
                                 "--probe", str(args.probe)], cwd=ROOT)
        if result.returncode:
            return result.returncode
        if hashlib.sha256(args.probe.read_bytes()).hexdigest() != digest:
            raise RuntimeError("Compiled probe changed during verification")
        path = ROOT / f"build/cpp/reports/{name}-report.json"
        reports[path.name] = hashlib.sha256(path.read_bytes()).hexdigest()
    result = subprocess.run([sys.executable, str(Path(__file__).with_name("comparison_boundary.py"))],
                            cwd=ROOT)
    if result.returncode:
        return result.returncode
    manifest = dict(cpp_probe_sha256=digest, reports=reports,
                    whole_program_inventory_sha256=hashlib.sha256((ROOT / "reference/original/whole-program/ledger.json").read_bytes()).hexdigest(),
                    presentation_inventory_sha256=hashlib.sha256((ROOT / "reference/original/presentation/effect-inventory.json").read_bytes()).hexdigest(),
                    boundary_policy_sha256=hashlib.sha256(Path(__file__).with_name("comparison_boundary.py").read_bytes()).hexdigest())
    (ROOT / "build/cpp/reports/original-suite.json").write_text(json.dumps(manifest, indent=2)+"\n", encoding="utf-8")
    print("All retained original comparisons and boundary checks passed against one compiled probe")
    return 0


if __name__ == "__main__":
    sys.exit(main())
