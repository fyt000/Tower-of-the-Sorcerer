"""Explicit exclusions for isolated original-machine comparisons.

Skipped behavior is not verified behavior. Unknown targets and extracted
gameplay writes fail closed. Source scanning is triage, not alias analysis.
"""
from pathlib import Path
import argparse
import json
import re
import sys

ROOT = Path(__file__).resolve().parents[2]
SOURCE = ROOT / "reference/original/decompiled"
PRESENTATION_SOURCE = ROOT / "reference/original/presentation/decompiled"

# Reviewed RTL/VCL call sites outside the exported gameplay corpus. This
# records the boundary, not a proof that arbitrary invocations can be ignored.
RUNTIME = {
    0x402710, 0x402C34, 0x4034DC, 0x4034FC, 0x40352C, 0x403658, 0x40369C,
    0x403710, 0x40414D, 0x4041F0, 0x404254, 0x4042B8, 0x40458D, 0x4045A4,
    0x405B6C, 0x40923C, 0x4102F0, 0x410378, 0x413098, 0x4130B8, 0x4130D8, 0x4130F8,
    0x413500, 0x41353C, 0x4135A4, 0x4135D4, 0x413CB8, 0x417E44, 0x419E4C,
    0x41A530, 0x41A5B8, 0x41C1E8, 0x41D718, 0x41DAD8, 0x421A54, 0x4237DC, 0x42C150, 0x42C454,
    0x42CEC8, 0x42CF78, 0x430F20, 0x431188, 0x431C8C,
}
EXCLUSIONS = {
    0x41C160: "Picture assignment/cloning and change notification. Recovered runtime source; bitmap state and Windows callbacks are excluded, not proven inert.",
    0x443648: "Hero sprite compositor: reads floor/hero position and writes bitmap/scratch state. Recovered source and assembly reviewed; pixels, allocator results and virtual graphic calls are excluded.",
    0x4433A4: "Standing pose: rendering coordinates and scratch operands excluded.",
    0x443808: "Walking pose: rendering scratch operands excluded.",
    0x44B6F4: "Enemy name string: no direct hero/map/monster/queue write.",
    0x44B78C: "Enemy information panel: rendering coordinates and strings excluded.",
    0x44BED8: "Key icon refresh: reads key counts, writes rendering scratch and control visibility.",
    0x44BC0C: "Timer/control gating: command production compared separately; Flight entry checks controls.",
    0x44CB34: "Status text rendering: text layout/string allocation excluded.",
    0x44CCD8: "Inventory/equipment bitmap refresh: rendering scratch and control visibility excluded.",
    0x450758: "Disables controls and keyboard gate: player entry tests must cover modal/busy guards.",
    0x450880: "Re-enables controls from inventory: eligibility excluded from isolated builder results.",
    0x454C10: "Animation classifier writes rendering scratch; followed by Flight redraw checks.",
    0x47C2BC: "Music playback via device/VCL: music_track calculation followed separately.",
}
INDIRECT = {
    f"dword ptr [{register} + {offset}]"
    for register, offset in (("ebx", "0xc"), ("edi", "0xc"), ("esi", "0xc"),
                             ("ecx", "0x28"), ("ecx", "0x2c"), ("edx", "0x1c"),
                             ("edx", "0x20"), ("edx", "0x38"), ("edx", "0x80"))
}
PROTECTED_WRITE = re.compile(
    r"(?:original_hero|original_maps|original_monsters|event_stack|event_cursor|dialogue_continue_stage).*?\s=(?!=)")


def check_skipped_calls(calls):
    rows, unreviewed, effectful = [], [], []
    for call in sorted(calls):
        row = dict(target=call)
        if not re.fullmatch(r"0x[0-9a-f]+", call):
            row["classification"] = "reviewed-indirect-exclusion" if call in INDIRECT else "unreviewed"
            row["limits"] = "Text/bitmap/control virtual calls at reviewed sites; target identity remains unresolved."
            if call not in INDIRECT:
                unreviewed.append(call)
        else:
            address = int(call, 16)
            files = list(PRESENTATION_SOURCE.glob(f"{address:08x}_*.c")) or list(SOURCE.glob(f"{address:08x}_*.c"))
            writes = []
            if files:
                row["source"] = str(files[0].relative_to(ROOT))
                writes = [dict(line=i, text=line.strip()) for i, line in
                          enumerate(files[0].read_text(encoding="utf-8").splitlines(), 1)
                          if PROTECTED_WRITE.search(line)]
            row["protected_writes"] = writes
            if writes:
                row["classification"] = "effectful-skip"
                effectful.append(call)
            elif address in EXCLUSIONS:
                row["classification"] = "reviewed-extracted-exclusion"
                row["reason"] = EXCLUSIONS[address]
            elif address in RUNTIME:
                row["classification"] = "reviewed-runtime-exclusion"
                row["limits"] = "Outside exported gameplay corpus; excluded RTL/VCL behavior and return values are not fidelity evidence."
            else:
                row["classification"] = "unreviewed"
                unreviewed.append(call)
        rows.append(row)
    return dict(calls=rows, unreviewed_calls=unreviewed, effectful_skips=effectful,
                limits="Direct named writes scanned. Aliased pointers, indirect target identity, "
                       "and transitive effects require manual review before adding exclusions.")


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--reports", type=Path, default=ROOT / "build/cpp/reports")
    parser.add_argument("--self-test", action="store_true")
    args = parser.parse_args()
    if args.self_test:
        critical = check_skipped_calls(["0x442c38", "0x449e18", "0xdeadbeef", "dword ptr [eax + 0x88]"])
        assert critical["effectful_skips"] == ["0x442c38", "0x449e18"]
        assert critical["unreviewed_calls"] == ["0xdeadbeef", "dword ptr [eax + 0x88]"]
        reviewed = check_skipped_calls(["0x41353c", "0x4433a4"])
        assert not reviewed["effectful_skips"] and not reviewed["unreviewed_calls"]
        print("Boundary guard rejects known gameplay writes and unknown direct/indirect calls")
        return 0
    reports = {}
    for path in sorted(args.reports.glob("*report.json")):
        if path.name == "boundary-report.json":
            continue
        data = json.loads(path.read_text(encoding="utf-8"))
        reports[path.name] = check_skipped_calls(data.get("skipped_original_calls", []))
    output = args.reports / "boundary-report.json"
    output.write_text(json.dumps(reports, indent=2)+"\n", encoding="utf-8")
    bad = {name: {key: value[key] for key in ("unreviewed_calls", "effectful_skips")}
           for name, value in reports.items() if value["unreviewed_calls"] or value["effectful_skips"]}
    print(json.dumps(dict(reports=len(reports), unresolved=bad, output=str(output)), indent=2))
    return bool(bad)


if __name__ == "__main__":
    sys.exit(main())
