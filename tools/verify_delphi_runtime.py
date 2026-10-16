"""Retain native gameplay/persistence/audio evidence without claiming full parity.

Run build_delphi_game.py --smoke first. Add --audio-smoke when changes affect
audio. Native fixture assertions execute real Pascal and VCL bodies; the scene
comparison separately executes the pinned original machine code in Unicorn.
"""
import argparse
import json

from recovery_evidence import ROOT, digest

WORK = ROOT / "build/delphi-game"
REPORT = ROOT / "build/delphi-game/reports/runtime-verification-report.json"


def evidence():
    build = json.loads((WORK / "build-report.json").read_text())
    for row in build["inputs"]:
        if digest(ROOT / row["source"]) != row["source_sha256"]:
            raise ValueError("Rebuild changed source: " + row["source"])
    inventory = json.loads((ROOT / "build/delphi-game/reports/method-inventory.json").read_text())
    if inventory["missing_methods"] or not inventory["complete_published_coverage"]:
        raise ValueError("A published method still has an unrecovered body")
    runs = {}
    for name in ("runtime", "persistence", "ranking"):
        row = build["builds"][name]
        if row["compile_exit"] or row.get("native_exit", -1):
            raise ValueError("Native check did not pass: " + name)
        if digest(ROOT / row["artifact"]) != row["artifact_sha256"]:
            raise ValueError("Rebuild changed native artifact: " + name)
        if digest(WORK / name / "native.log") != row["native_log_sha256"]:
            raise ValueError("Native log changed: " + name)
        observations = [json.loads(line) for line in row["native_output"].splitlines()
                        if line.strip().startswith("{")]
        if not observations:
            raise ValueError("No native observations: " + name)
        if name == "runtime":
            checks = [item for item in observations if "check" in item]
            if not checks or any(item.get("passed") is not True for item in checks):
                raise ValueError("Runtime assertions failed")
            if observations[-1].get("runtime_checks") != len(checks):
                raise ValueError("Runtime assertion count differs")
        runs[name] = dict(artifact=row["artifact"], sha256=row["artifact_sha256"],
                          native_log_sha256=row["native_log_sha256"], observations=observations)
    audio = build["builds"].get("audio", {})
    if "native_exit" in audio:
        if audio["native_exit"] or audio["compile_exit"]:
            raise ValueError("Native audio checks failed")
        if digest(ROOT / audio["artifact"]) != audio["artifact_sha256"]:
            raise ValueError("Rebuild changed audio artifact")
        if digest(WORK / "audio/native.log") != audio["native_log_sha256"]:
            raise ValueError("Native audio log changed")
        observations = [json.loads(line) for line in audio["native_output"].splitlines()
                        if line.strip().startswith("{")]
        if not observations or observations[-1].get("audio") != "passed":
            raise ValueError("Missing native audio evidence")
        runs["audio"] = dict(artifact=audio["artifact"], sha256=audio["artifact_sha256"],
                             native_log_sha256=audio["native_log_sha256"], observations=observations)
    return dict(schema_version=1, original_sha256=build["original_sha256"],
                published_methods=inventory["published_methods"],
                implemented_methods=inventory["implemented_methods"], missing_methods=0,
                source_inputs=build["inputs"], native_runs=runs,
                full_game_recovered=False, pixel_equivalence_established=False,
                limits=["The fixture game executes hidden native VCL controls and manually delivers input/timer callbacks.",
                        "Ending execution and scene queue comparison are seeded scenarios, not an unmodified natural campaign playthrough.",
                        "All published methods have source bodies; exhaustive equivalence of the new bodies, Windows event timing and raster transitions remains unproven.",
                        "Unavailable audio devices or assets are counted and handled without aborting gameplay."])


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--check", action="store_true")
    args = parser.parse_args()
    report = evidence()
    if args.check:
        if json.loads(REPORT.read_text()) != report:
            raise ValueError("Stale native runtime verification report")
    else:
        REPORT.write_text(json.dumps(report, indent=2) + "\n", encoding="utf-8")
    total = report["native_runs"]["runtime"]["observations"][-1]["runtime_checks"]
    print(f"230 implemented methods; {total} native runtime assertions; persistence passed; "
          f"audio {'passed' if 'audio' in report['native_runs'] else 'not run'}")


if __name__ == "__main__":
    main()
