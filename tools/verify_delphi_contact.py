"""Compare full original tile interactions and old-man dialogue at VCL boundaries."""
import argparse
import copy
import hashlib
import itertools
import json
from pathlib import Path
import struct

import pefile

from verify_delphi_dialogue import DialogueRunner, ROOT, WORK, ORIGINAL_HASH, digest, first_difference


GAME = dict(handan=0x444490, roujin=0x449708, mevent=0x46397C, ichicheck=0x46CB1C,
            touzoku=0x465900, kaidanwork=0x442DC8, doorcheck=0x47BEAC,
            madoushilivework=0x461EF4, zenolivework=0x461A0C)
STATE = dict(EventStack=(0x48C74C, 1200 * 6))


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--candidate", type=Path, default=WORK / "game/Tower.exe")
    parser.add_argument("--check", action="store_true")
    args = parser.parse_args()
    original = ROOT / "build/research/TSW.exe"
    assert digest(original) == ORIGINAL_HASH
    old = DialogueRunner(pefile.PE(str(original)), original=True, extra_game=GAME, extra_storage=STATE)
    new = DialogueRunner(pefile.PE(str(args.candidate)), map_path=args.candidate.with_suffix(".map"),
                         extra_game=GAME, extra_storage=STATE)
    ready = {}
    models = ("bitmap_objects", "canvas_objects", "list_counts", "font_sizes", "control_properties",
              "menu_checks", "names", "free_bitmap_slots", "bitmap_serial", "next_bitmap", "next_string")
    for scale, runner in itertools.product((0, 1), (old, new)):
        runner.seed(scale)
        runner.run("syokidata0")
        ready[scale, runner.original] = dict(objects=bytes(runner.u.mem_read(0x600000, 0x200000)),
            globals={n: bytes(runner.u.mem_read(p, runner.spec[n][1])) for n, p in runner.storage.items()},
            models={n: copy.deepcopy(getattr(runner, n)) for n in models})

    def seed(scale=0, floor=1, tile=6, target=49, hero=None, state=None):
        for runner in (old, new):
            prepared = ready[scale, runner.original]
            runner.u.mem_write(0x600000, prepared["objects"])
            for n, raw in prepared["globals"].items():
                runner.u.mem_write(runner.storage[n], raw)
            for n, value in prepared["models"].items():
                setattr(runner, n, copy.deepcopy(value))
            values = {0: 1000, 4: 100, 8: 100, 16: floor, 24: 5, 28: 5, 352: 4, 360: 0, **(hero or {})}
            for offset, value in values.items():
                runner.write32(runner.storage["Hero"] + offset, value)
            values = {"EventCursor": 4, "ContactIndex": target, "NeighborIndex": 66, **(state or {})}
            for n, value in values.items():
                runner.u.mem_write(runner.storage[n], value.to_bytes(runner.spec[n][1], "little", signed=True))
            runner.u.mem_write(runner.storage["Maps"], bytes([6]) * 6273)
            for f in range(51):
                runner.u.mem_write(runner.storage["Maps"] + f * 123, bytes([60, 60]))
            runner.u.mem_write(runner.storage["Maps"] + floor * 123 + target + 2, bytes([tile]))
            runner.u.mem_write(runner.storage["EventStack"], bytes([0xA5]) * STATE["EventStack"][1])
            runner.u.mem_write(runner.storage["Monsters"], struct.pack("<4i", 30, 25, 10, 123) * 33)
            runner.ranking_bytes = struct.pack("<72i", *range(72))
            runner.files = {}
            runner.texts = {}
            runner.trace.clear()

    cases, transcript = [], hashlib.sha256()

    def compare(method, inputs):
        expected, actual = old.run(method), new.run(method)
        a, b = old.state(), new.state()
        difference = first_difference(expected, actual)
        state_diff = [n for n in a if a[n] != b[n]]
        row = dict(method=method, inputs=inputs, passed=difference is None and not state_diff,
                   first_difference=difference, state_differences=state_diff)
        cases.append(row)
        transcript.update(json.dumps([method, inputs, expected, a], sort_keys=True).encode())
        if not row["passed"]:
            raise ValueError(row)

    floors = (2, 3, 4, 6, 16, 18, 21, 23, 27, 31, 33, 36, 37, 39, 42, 45, 46, 48)
    for scale, floor, x, clue, gift, orb in itertools.product((0, 1), floors, (1, 9), (0, 1, 2), (0, 1), (0, 1)):
        seed(scale, floor, 25, hero={24: x, 72: orb, 392: gift, 436: gift,
                                   **{i * 4: clue for i in range(66, 84)}})
        compare("roujin", [scale, floor, x, clue, gift, orb])
    # Pickup text, singular/plural point gains, item flags and timing.
    for scale, tile, floor, cycle in itertools.product((0, 1), range(29, 61), (1, 11, 31), (0, 1)):
        seed(scale, floor, tile, hero={636: cycle})
        compare("handan", ["pickup", scale, tile, floor, cycle])
    for scale, tile, keys in itertools.product((0, 1), (1, 2, 3, 9), (0, 1, 2)):
        seed(scale, tile=tile, hero={32: keys, 36: keys, 40: keys})
        compare("handan", ["door", scale, tile, keys])
    for floor, target, revealed in itertools.product((12, 16, 19, 41), (10, 120, 27, 20, 60), (0, 1)):
        seed(floor=floor, tile=10, target=target)
        for runner in (old, new):
            runner.u.mem_write(runner.storage["Maps"] + 41 * 123 + 14, bytes([6 if revealed else 8]))
        compare("handan", ["hidden", floor, target, revealed])
    for scale, tile, floor, music, seen in itertools.product(
            (0, 1), (11, 12), (20, 25, 29, 31, 40, 41, 43, 45, 49), (0, 5), (0, 1)):
        seed(scale, floor, tile, target=70, hero={20: 29, 360: music, 620: seen, 524: seen})
        for runner in (old, new):
            for f, cell in ((20, 51), (25, 73), (40, 62), (49, 18)):
                runner.u.mem_write(runner.storage["Maps"] + f * 123 + cell, b"\x17")
        compare("handan", ["stairs", scale, tile, floor, music, seen])
    for scale, visits, music in itertools.product((0, 1), (0, 1, 12), (0, 5, 13)):
        seed(scale, tile=16, hero={44: visits, 360: music})
        compare("handan", ["altar", scale, visits, music])
    for tile, floor in ((6, 1), (7, 3), (19, 6), (21, 2), (23, 10), (25, 3), (27, 24),
                        (61, 1), (91, 49), (91, 50), (104, 35), (122, 35), (145, 49)):
        for scale, cycle in itertools.product((0, 1), (0, 1)):
            seed(scale, floor, tile, hero={636: cycle})
            compare("handan", ["dispatch", scale, tile, floor, cycle])
    result = dict(original_sha256=ORIGINAL_HASH, candidate_sha256=digest(args.candidate),
                  comparisons=len(cases), passed=True, transcript_sha256=transcript.hexdigest(), cases=cases)
    output = WORK / "reports/contact-report.json"
    serialized = json.dumps(result, indent=2) + "\n"
    if args.check:
        if not output.exists() or output.read_text() != serialized:
            raise SystemExit("Contact report is stale; rerun without --check")
    else:
        output.parent.mkdir(parents=True, exist_ok=True)
        output.write_text(serialized)
    print(json.dumps({k: v for k, v in result.items() if k != "cases"}))


if __name__ == "__main__":
    main()
