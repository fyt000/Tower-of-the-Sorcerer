"""Compare Flight entry and actual open/preview/confirm chains with pinned x86.

Original memory is carried between callbacks. No direction/stair flags are
invented between stages. VCL enable calls are observed with inert controls;
rendering and device calls are skipped. No live campaign or original app runs.
"""
from pathlib import Path
import argparse
import hashlib
import json
import subprocess
import sys

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))
from original_event_probe import RAW, pe, probe
from differential import HASH
from comparison_boundary import check_skipped_calls

HERO = 0x4B8688
FOLLOW = [0x44C9F0, 0x442C38, 0x454C10, 0x442F80, 0x443050,
          0x47C8F8, 0x450758, 0x41353C, 0x410378]
WATCH = [HERO + offset for offset in (48, 632, 664, 352, 360)]
WATCH += [HERO + 68 + 4 * i for i in range(15)]
CONTROLS = [(0x200000 + offset, 0x210000 + offset * 16)
            for offset in range(0, 0x500, 4) if offset != 0x254]


class Cpp:
    def __init__(self, executable):
        self.process = subprocess.Popen([str(executable)], stdin=subprocess.PIPE,
                                        stdout=subprocess.PIPE, text=True)

    def send(self, lines):
        self.process.stdin.write("\n".join(lines) + "\n")
        self.process.stdin.flush()

    def read(self):
        result = json.loads(self.process.stdout.readline())
        if "error" in result:
            raise RuntimeError(result)
        return result

    def start(self, floor, highest, x, y, changes=(), owned=1):
        self.send(["original", f"set floor {floor}", f"set highest {highest}",
                   f"set x {x}", f"set y {y}", "set facing 4",
                   "set flight_direction 2", "set highest_stair 1", f"item 2 {owned}"] +
                  [f"tile {f} {ty * 11 + tx} {tile}" for f, tx, ty, tile in changes])

    def action(self, kind, **values):
        self.send(["input " + json.dumps(dict(type=kind, **values)), "snapshot"])
        return self.read()["accepted"], self.read()

    def close(self):
        self.process.stdin.close()
        if self.process.wait() != 0:
            raise RuntimeError("C++ probe failed")


def original(address, floor, highest, x, y, changes=(), owned=1, state=None):
    values = [] if state else [(HERO + 20, highest), (HERO + 76, owned),
                              (HERO + 632, 2), (HERO + 664, 1), (HERO + 352, 4),
                              *CONTROLS]
    return probe(address, floor, x, y, changes, globals=values,
                 follow_calls=FOLLOW, watch_globals=WATCH, include_presentation=True,
                 state=state, return_state=True, observe_controls=True)


def differences(expected, actual, preview=False):
    result = []
    for slot in (*range(12), 14, 15, 16):
        if preview and slot == 4:
            continue  # Selector floor is separate from physical hero floor in C++.
        if expected["stat_slots"][slot] != actual["hero"][slot]:
            result.append(dict(slot=slot, original=expected["stat_slots"][slot],
                               cpp=actual["hero"][slot]))
    for i, offset in enumerate((632, 664, 352)):
        value = expected["watched_globals"][hex(HERO + offset)]
        if value != actual["flight"][i]:
            result.append(dict(flight=i, original=value, cpp=actual["flight"][i]))
    for i, value in enumerate(actual["items"]):
        if value != expected["watched_globals"][hex(HERO + 68 + 4 * i)]:
            result.append(dict(item=i))
    maps = expected["state"][0x4B8934]
    if actual["maps"] != [list(maps[f * 123 + 2:(f + 1) * 123]) for f in range(51)]:
        result.append(dict(maps="mismatch"))
    if expected["queue"] != actual["queue"]:
        result.append(dict(queue=dict(original=expected["queue"], cpp=actual["queue"])))
    return result


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--probe", type=Path, default=ROOT / "build/cpp/vs/Release/tsw_probe.exe")
    args = parser.parse_args()
    if hashlib.sha256(pe.__data__).hexdigest() != HASH:
        raise RuntimeError("Original image hash mismatch")
    cpp = Cpp(args.probe)
    failures, skipped, groups = [], set(), {}
    stages = 0

    def compare(name, expected, actual, accepted, selector, preview=False):
        nonlocal stages
        stages += 1
        skipped.update(expected["calls"])
        diff = differences(expected, actual, preview)
        if bool(accepted) != (selector >= 0):
            diff.append(dict(accepted=accepted, expected=selector >= 0))
        if actual["selector"] != selector:
            diff.append(dict(selector=actual["selector"], expected=selector))
        if diff:
            failures.append(dict(scenario=name, differences=diff))

    # All cardinal edge coordinates, no diagonal or flat-array wrap eligibility.
    room = [(1, i % 11, i // 11, 6) for i in range(121)]
    for x in range(11):
        for y in range(11):
            for dx, dy in ((0, -1), (-1, 0), (1, 0), (0, 1), (1, 1)):
                tx, ty = x + dx, y + dy
                changes = room + ([(1, tx, ty, 11)] if 0 <= tx < 11 and 0 <= ty < 11 else [])
                cpp.start(1, 2, x, y, changes)
                expected = original(0x481E80, 1, 2, x, y, changes)
                opened = expected["watched_globals"][hex(HERO + 48)] == 1
                accepted, actual = cpp.action("flight_open")
                compare(f"entry/bounds/{x}/{y}/{dx}/{dy}", expected, actual, accepted,
                        1 if opened else -1)
    groups["entry-bounds"] = 121 * 5
    print("Checked all Flight entry coordinates and diagonal controls", flush=True)

    # Every tile byte in each scan position, with a north stair control.
    for dx, dy in ((0, -1), (-1, 0), (1, 0), (0, 1)):
        for tile in range(256):
            changes = room + [(1, 5, 4, 11), (1, 5 + dx, 5 + dy, tile)]
            cpp.start(1, 2, 5, 5, changes)
            expected = original(0x481E80, 1, 2, 5, 5, changes)
            opened = expected["watched_globals"][hex(HERO + 48)] == 1
            accepted, actual = cpp.action("flight_open")
            compare(f"entry/priority/{dx}/{dy}/{tile}", expected, actual, accepted,
                    1 if opened else -1)
    groups["entry-tile-priority"] = 4 * 256
    for owned in (0, 1, 2):
        cpp.start(1, 2, 5, 5, room + [(1, 5, 4, 11)], owned)
        expected = original(0x481E80, 1, 2, 5, 5, room + [(1, 5, 4, 11)], owned)
        accepted, actual = cpp.action("flight_open")
        compare(f"entry/possession/{owned}", expected, actual, accepted, 1 if owned == 1 else -1)
    groups["entry-possession"] = 3
    print("Checked tile priority and possession gates", flush=True)

    routes = [(10, 10, ["down", "up"]), (15, 15, ["down", "up"]),
              (19, 19, ["down", "up"]), (14, 15, ["up"]),
              (34, 45, ["up", "down"]), (43, 45, ["up", "down", "up"]),
              (1, 2, ["down", "up", "up"]), (29, 29, ["down"])]
    for floor, highest, steps in routes:
        landing = RAW[floor * 123]
        x, y = landing % 11, landing // 11
        cpp.start(floor, highest, x, y)
        expected = original(0x481E80, floor, highest, x, y)
        accepted, actual = cpp.action("flight_open")
        compare(f"route/{floor}/{highest}/open", expected, actual, accepted, floor)
        # Observe the real disable routine, including Hero and Wisdom Orbs.
        for offset in (0x1DC, 0x1EC, 0x254, 0x25C, 0x260, 0x264, 0x268,
                       0x26C, 0x270, 0x278, 0x27C, 0x280):
            control = 0x201000 if offset == 0x254 else 0x210000 + offset * 16
            if expected["control_enables"].get(hex(control)) is not False:
                failures.append(dict(scenario="modal-disable", control=hex(offset)))
        for n, step in enumerate(steps):
            prior = expected["stat_slots"][4]
            expected = original(0x44ED94 if step == "up" else 0x44ED1C,
                                prior, highest, x, y, state=expected["state"])
            selected = expected["stat_slots"][4]
            accepted, actual = cpp.action("flight_" + step)
            # Boundary refusal is valid and keeps the selector open.
            diff = differences(expected, actual, preview=True)
            if bool(accepted) != (selected != prior) or actual["selector"] != selected:
                diff.append(dict(accepted=accepted, selected=actual["selector"], expected=selected))
            skipped.update(expected["calls"])
            stages += 1
            if diff:
                failures.append(dict(scenario=f"route/{floor}/{highest}/{n}/{step}", differences=diff))
        expected = original(0x44EAF4, expected["stat_slots"][4], highest, x, y,
                            state=expected["state"])
        accepted, actual = cpp.action("flight_confirm")
        diff = differences(expected, actual)
        skipped.update(expected["calls"])
        stages += 1
        if not accepted or actual["selector"] != -1:
            diff.append(dict(confirm="refused or selector remains open"))
        if diff:
            failures.append(dict(scenario=f"route/{floor}/{highest}/confirm", differences=diff))
        groups["complete-selector-routes"] = groups.get("complete-selector-routes", 0) + 1

    # Direct destinations must use the same entry and monotonically previewed route.
    for floor, highest, destination in ((10, 10, 9), (9, 10, 10), (14, 15, 15),
                                         (34, 45, 45), (43, 45, 45), (19, 19, 19)):
        landing = RAW[floor * 123]
        x, y = landing % 11, landing // 11
        cpp.start(floor, highest, x, y)
        expected = original(0x481E80, floor, highest, x, y)
        skipped.update(expected["calls"])
        while expected["stat_slots"][4] != destination:
            selected = expected["stat_slots"][4]
            expected = original(0x44ED94 if destination > selected else 0x44ED1C,
                                selected, highest, x, y, state=expected["state"])
            skipped.update(expected["calls"])
        expected = original(0x44EAF4, destination, highest, x, y, state=expected["state"])
        accepted, actual = cpp.action("use_item", item="flying_orb", floor=destination)
        diff = differences(expected, actual)
        skipped.update(expected["calls"])
        stages += 1
        if not accepted or actual["selector"] != -1:
            diff.append(dict(direct="refused or selector opened"))
        if diff:
            failures.append(dict(scenario=f"direct/{floor}/{highest}/{destination}", differences=diff))
    groups["complete-direct-routes"] = 6
    cpp.close()
    boundary = check_skipped_calls(skipped)
    report = dict(original_sha256=HASH, cpp_probe_sha256=hashlib.sha256(args.probe.read_bytes()).hexdigest(),
                  scenarios=stages, compared_stages=stages, groups=groups, failures=failures, passed=stages-len(failures),
                  followed_original_calls=[hex(a) for a in FOLLOW], skipped_original_calls=sorted(skipped),
                  boundary_audit=boundary,
                  limits="Original machine memory carried across Flight entry/preview/confirm. "
                         "Preview floor separated from physical hero floor in C++. VCL control enables "
                         "observed with inert controls; rendering/device calls skipped. Command playback, "
                         "full Windows UI, and a natural 50-floor run are not established by this test.")
    output = ROOT / "build/cpp/reports/flight-report.json"
    output.parent.mkdir(parents=True, exist_ok=True)
    output.write_text(json.dumps(report, indent=2)+"\n", encoding="utf-8")
    print(f"{report['passed']}/{stages} stages matched; {len(failures)} failures; {output}")
    print(json.dumps(failures[:6], indent=2))
    return bool(failures or boundary["unreviewed_calls"] or boundary["effectful_skips"])


if __name__ == "__main__":
    sys.exit(main())
