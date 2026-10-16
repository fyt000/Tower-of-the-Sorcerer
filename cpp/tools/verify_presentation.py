"""Compare original Orb numeric rows and review UI entry/close sequences.

Numeric comparisons execute 0x44F26C -> 0x44FF0C -> 0x45031C, recording
the actual integer-to-string arguments. UI-only assertions retain original
memory between callbacks and report their separate scope. No real app runs.
"""
from pathlib import Path
import argparse
import hashlib
import json
import struct
import subprocess
import sys

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))
from original_event_probe import pe, probe
from review_original_presentation import inventory
from differential import HASH
from comparison_boundary import check_skipped_calls

HERO = 0x4B8688
CONTROL_BASE = 0x210000
ENTRY = {4: 0x48201C, 5: 0x482128, 6: 0x482234, 7: 0x482340,
         8: 0x48244C, 9: 0x482558, 11: 0x482664, 12: 0x482770, 13: 0x48287C}


def controls():
    manifest = json.loads((ROOT / "reference/original/presentation/ui-manifest.json").read_text())
    form = next(form for form in manifest["forms"] if form["class_name"] == "TTSW10")
    return [(0x200000 + int(field["offset"], 16), CONTROL_BASE + int(field["offset"], 16) * 16)
            for field in form["fields"] if field["offset"] != "0x254"]


def tile(row):
    return 61 + row * 2 if row < 18 else 104 if row == 18 else 122 if row == 19 else 93 + row * 2


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--probe", type=Path, default=ROOT / "build/cpp/vs/Release/tsw_probe.exe")
    args = parser.parse_args()
    if hashlib.sha256(pe.__data__).hexdigest() != HASH:
        raise RuntimeError("Original hash mismatch")
    coverage = inventory()
    if coverage["missing_event_exports"] or coverage["missing_published_exports"] or coverage["failed_recovered_exports"]:
        raise RuntimeError("UI event/method/runtime recovery is incomplete")
    process = subprocess.Popen([str(args.probe)], stdin=subprocess.PIPE, stdout=subprocess.PIPE, text=True)
    failures, skipped, sites, groups, samples = [], set(), set(), {}, []
    ui_evidence = []

    def cpp(lines):
        process.stdin.write("\n".join(lines) + "\n")
        process.stdin.flush()
        result = json.loads(process.stdout.readline())
        if "error" in result:
            raise RuntimeError(result)
        return result

    def record(result):
        skipped.update(result["calls"])
        sites.update((entry["site"], entry["target"]) for entry in result["skipped_call_sites"])

    count = 0
    image = pe.get_memory_mapped_image()
    for row in range(33):
        hp, attack, defense, _ = struct.unpack_from("<4I", image, 0x89910 + 16 * row)
        for cycle in (0, 43):
            scale = cycle + 1
            # Include defense threshold, a many-round fight, and zero incoming damage.
            for excess, hero_defense in ((0, 0), (scale, attack * scale), (5 * scale, 0), (100 * scale, 20 * scale)):
                hero_attack = defense * scale + excess
                for bonus in (0, 1):
                    original = probe(0x44F26C, 1, globals=controls() + [
                        (0x48C55C, row), (0x48C5B0, 1), (HERO + 4, hero_attack),
                        (HERO + 8, hero_defense), (HERO + 636, cycle),
                        (HERO + 80, bonus), (HERO + 108, bonus)],
                        follow_calls=[0x44FF0C, 0x45031C],
                        watch_globals=[0x48C564, 0x48C568, 0x48C56C], observe_arguments=[0x405B6C])
                    record(original)
                    actual = cpp(["original", f"set attack {hero_attack}", f"set defense {hero_defense}",
                                  f"set cycle {cycle}", f"item 3 {bonus}", f"item 10 {bonus}",
                                  f"orb_forecast {tile(row)}"])
                    numbers = [call["eax"] for call in original["call_arguments"]]
                    expected = dict(penetrates=original["watched_globals"]["0x48c564"] == 0,
                                    damage=original["watched_globals"]["0x48c568"],
                                    hits=original["watched_globals"]["0x48c56c"])
                    diff = []
                    if numbers[:3] != [hp * scale, attack * scale, defense * scale]:
                        diff.append(dict(displayed_stats=numbers[:3]))
                    if actual["penetrates"] != expected["penetrates"]:
                        diff.append(dict(penetrates=actual))
                    if expected["penetrates"] and (actual["damage"] != expected["damage"] or actual["hits"] != expected["hits"] or numbers[3:] != [expected["damage"]]):
                        diff.append(dict(original=expected, cpp=actual, numeric_strings=numbers))
                    if diff:
                        failures.append(dict(row=row, cycle=cycle, attack=hero_attack, bonus=bonus, differences=diff))
                    if row in (12, 13, 17, 19) and excess == 100 * scale and cycle == 0:
                        samples.append(dict(row=row, attack=hero_attack, bonus=bonus, original=expected, cpp=actual))
                    count += 1
    groups["orb-row-numeric-comparisons"] = count
    print(f"Compared {count} original Orb numeric rows", flush=True)

    # Do not combine these original-only gate checks with the differential count.
    # They establish the original controls that the desktop smoke tests must enforce.
    for item, entry in ENTRY.items():
        opened = probe(entry, 1, globals=controls() + [(HERO + 68 + 4 * item, 1)],
                       follow_calls=[0x450758], return_state=True, observe_controls=True)
        record(opened)
        for offset in (0x334, 0x338):  # GameLoad1 / GameSave1, recovered field table.
            enabled = opened["control_enables"].get(hex(CONTROL_BASE + offset * 16))
            if enabled is not False:
                failures.append(dict(item=item, gate=hex(offset), enabled=enabled))
        selected = struct.unpack_from("<I", opened["state"][0x48C550], 0x24)[0]
        if selected != item + 1:
            failures.append(dict(item=item, selected=selected))
        closed = probe(0x450B78, 1, state=opened["state"], follow_calls=[0x450880],
                       return_state=True, observe_controls=True)
        record(closed)
        if opened["state"][HERO] != closed["state"][HERO] or opened["state"][0x4B8934] != closed["state"][0x4B8934]:
            failures.append(dict(item=item, close="changed hero/maps"))
        ui_evidence.append(dict(item=item, open=hex(entry), close="0x450b78", selected=selected,
                                file_controls_disabled=True, close_preserves_hero_and_maps=True))
    print("Reviewed nine item open/cancel chains and their native-file gates", flush=True)

    # The idle timer writes save words. Show its guards and saturation rather than
    # treating them as ordinary gameplay-equivalence cases.
    timer_evidence = []
    for floor, position, offset in ((15, 60, 608), (35, 71, 612)):
        for counter in (0, 1, 2):
            for animated in (0, 1):
                result = probe(0x443120, floor, position % 11, position // 11,
                               changes=[(floor, position % 11, position // 11, 6)],
                               globals=controls() + [(HERO + offset, counter), (HERO + 48, animated)],
                               follow_calls=[0x4548A0, 0x454A58],
                               watch_globals=[HERO + offset], observe_effects=True)
                record(result)
                actual = result["watched_globals"][hex(HERO + offset)]
                expected = counter + int(counter < 2 and animated == 0)
                if actual != expected:
                    failures.append(dict(timer_floor=floor, expected=expected, actual=actual))
                timer_evidence.append(dict(floor=floor, offset=offset, before=counter, movement_flag=animated,
                                           after=actual, writes=result["effect_writes"]))
    death_evidence = []
    for answer in (6, 7):  # Delphi modal results mrYes / mrNo.
        result = probe(0x449E18, 1, globals=controls() + [(0x48C5A4, 10), (0x48C5C8, 93),
                       (HERO, 0), (HERO + 668, 0)], follow_calls=[0x44BC0C, 0x450758],
                       call_returns={0x42CEC8: answer}, observe_effects=True, observe_controls=True)
        record(result)
        started = "0x44bc0c" in result["followed_calls"]
        load_enabled = result["control_enables"].get(hex(CONTROL_BASE + 0x334 * 16))
        if started != (answer == 6) or (answer == 7 and load_enabled is not True):
            failures.append(dict(death_answer=answer, started=started, load_enabled=load_enabled))
        death_evidence.append(dict(answer=answer, event_timer_started=started, load_enabled=load_enabled,
                                   modeled_returns=result["modeled_returns"]))
    process.stdin.close()
    if process.wait() != 0:
        raise RuntimeError("C++ probe failed")
    boundary = check_skipped_calls(skipped)
    report = dict(original_sha256=HASH, cpp_probe_sha256=hashlib.sha256(args.probe.read_bytes()).hexdigest(),
                  scenarios=count, passed=count - sum("row" in failure for failure in failures),
                  groups=groups, failures=failures, samples=samples,
                  original_only_ui_chains=ui_evidence, original_only_timer_probes=timer_evidence,
                  original_only_death_choices=death_evidence,
                  event_coverage={key: coverage[key] for key in ("form_count", "component_count", "event_bindings", "published_methods", "recovered_entries", "missing_event_exports")},
                  skipped_original_calls=sorted(skipped),
                  skipped_call_sites=[dict(site=site, target=target) for site, target in sorted(sites)],
                  boundary_audit=boundary,
                  limits="528 numeric row comparisons, nine original item open/cancel chains, twelve original timer probes, and two original death-prompt branches with explicit modeled replies. UI assertions are original-only, paired with desktop dispatch smoke checks. Bitmap/string calls and Windows event delivery are skipped. Idle save counters are explicitly observed; no legacy wall-clock equivalence is claimed.")
    output = ROOT / "build/cpp/reports/ui-sequence-report.json"
    output.parent.mkdir(parents=True, exist_ok=True)
    output.write_text(json.dumps(report, indent=2) + "\n", encoding="utf-8")
    print(json.dumps(dict(passed=report["passed"], scenarios=count, failures=failures,
                          unresolved_calls=boundary["unreviewed_calls"], effectful_skips=boundary["effectful_skips"]), indent=2))
    return bool(failures or boundary["unreviewed_calls"] or boundary["effectful_skips"])


if __name__ == "__main__":
    sys.exit(main())
