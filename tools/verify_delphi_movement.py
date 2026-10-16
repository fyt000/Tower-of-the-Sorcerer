"""Execute original and recovered movement, hazard and animation callees.

Only the existing named VCL observer boundary is modeled; game callees run.
This compares ordered effects and state, not Windows timer delivery.
"""
import argparse
import copy
import hashlib
import itertools
import json
from pathlib import Path

import pefile

from verify_delphi_flight import FlightRunner
from verify_delphi_graphics import ROOT, WORK, ORIGINAL_HASH, digest, first_difference


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--candidate", type=Path, default=WORK / "game/Tower.exe")
    parser.add_argument("--check", action="store_true")
    args = parser.parse_args()
    original_path = ROOT / "build/research/TSW.exe"
    if digest(original_path) != ORIGINAL_HASH:
        raise ValueError("Original executable changed")
    entries = dict(yusyaidou=0x443808, idou=0x44C04C, madoushi1=0x44C464, mazyutu1=0x44C5C4)
    storage = dict(ContactIndex=(0x48C584, 4))
    old = FlightRunner(pefile.PE(str(original_path)), original=True, extra_game=entries, extra_storage=storage)
    new = FlightRunner(pefile.PE(str(args.candidate)), map_path=args.candidate.with_suffix(".map"), extra_game=entries, extra_storage=storage)
    ready = {}
    for scale, runner in itertools.product((0, 1), (old, new)):
        runner.seed(scale)
        runner.run("syokidata0")
        ready[scale, runner.original] = dict(
            objects=bytes(runner.u.mem_read(0x600000, 0x200000)),
            globals={name: bytes(runner.u.mem_read(at, runner.spec[name][1])) for name, at in runner.storage.items()},
            models=copy.deepcopy((runner.bitmap_objects, runner.canvas_objects, runner.list_counts)),
            next_bitmap=runner.next_bitmap, next_string=runner.next_string)

    def seed(scale, floor, x, y, shield, cycle):
        for runner in (old, new):
            prepared = ready[scale, runner.original]
            runner.u.mem_write(0x600000, prepared["objects"])
            for name, raw in prepared["globals"].items():
                runner.u.mem_write(runner.storage[name], raw)
            runner.bitmap_objects, runner.canvas_objects, runner.list_counts = copy.deepcopy(prepared["models"])
            runner.next_bitmap, runner.next_string = prepared["next_bitmap"], prepared["next_string"]
            runner.texts.clear()
            for offset, value in ((16, floor), (24, x), (28, y), (164, shield), (636, cycle)):
                runner.write32(runner.storage["Hero"] + offset, value)
            runner.u.mem_write(runner.storage["Maps"] + floor * 123, bytes([6]) * 123)
            if floor == 47:
                runner.u.mem_write(runner.storage["Maps"] + floor * 123 + 123, b"\x06")
            runner.u.mem_write(runner.storage["EventStack"], bytes([0xA5]) * 3072)
            runner.write32(runner.storage["EventCursor"], 0)
            runner.run("mhyouji")
            runner.run("yusyahyouji1")

    cases = []
    transcript = hashlib.sha256()

    def compare(method, inputs):
        expected, actual = old.run(method), new.run(method)
        a, b = old.state(), new.state()
        difference = first_difference(expected, actual)
        state_differences = [name for name in a if a[name] != b[name]]
        row = dict(method=method, inputs=inputs, passed=difference is None and not state_differences,
                   original_effects=len(expected), candidate_effects=len(actual),
                   first_difference=difference, state_differences=state_differences)
        cases.append(row)
        transcript.update(json.dumps([method, inputs, expected, actual, a, b], sort_keys=True).encode())
        if not row["passed"]:
            raise ValueError(json.dumps(row, indent=2))

    # Independent scratch/neighbor values expose the rewritten pose/retreat bug.
    for scale, tile, floor, position, offset, shield, cycle in itertools.product(
            (0, 1), (110, 111, 112), (1, 47), ((5, 5), (0, 9), (0, 0), (10, 10)),
            (-22, -2, 2, 22), (0, 1), (0, 43)):
        seed(scale, floor, *position, shield, cycle)
        for runner in (old, new):
            for name, value in (("TileClass", tile), ("Damage", offset), ("ScratchIndex", 17),
                                ("NeighborIndex", 29), ("NeighborY", 99)):
                runner.write32(runner.storage[name], value)
        compare("mazyutu1", dict(scale=scale, tile=tile, floor=floor, position=position,
                                offset=offset, shield=shield, cycle=cycle))
    print("Magician state/queue comparisons", len(cases), "passed", flush=True)

    for scale, facing, speed, hazard, shield in itertools.product(
            (0, 1), range(1, 5), ("low", "middle", "high"), ("none", "magician", "pincer"), (0, 1)):
        seed(scale, 47, 5, 5, shield, 0)
        delta = {1: 11, 2: -1, 3: 1, 4: -11}[facing]
        destination = 60 + delta
        for runner in (old, new):
            runner.write32(runner.storage["Hero"] + 352, facing)
            runner.write32(runner.storage["ContactIndex"], destination)
            runner.u.mem_write(runner.components["High1"] + 0x28, bytes([speed == "high"]))
            runner.u.mem_write(runner.components["Middle1"] + 0x28, bytes([speed == "middle"]))
            if hazard == "magician":
                runner.u.mem_write(runner.storage["Maps"] + 47 * 123 + destination + 3, b"\x97")
            elif hazard == "pincer":
                for offset in (-1, 1):
                    runner.u.mem_write(runner.storage["Maps"] + 47 * 123 + destination + offset + 2, b"\x5d")
        compare("idou", dict(scale=scale, facing=facing, speed=speed, hazard=hazard, shield=shield))
    result = dict(original_sha256=ORIGINAL_HASH, candidate_sha256=digest(args.candidate),
                  comparisons=len(cases), cases=cases, fixture_transcript_sha256=transcript.hexdigest(),
                  passed=True, limits="Game callees execute; VCL drawing and timer calls use explicit observers. This is not strict byte equivalence or a Windows scheduling proof.")
    output = args.candidate.parent / "movement-comparison-report.json" if args.candidate != WORK / "game/Tower.exe" else WORK / "reports/movement-comparison-report.json"
    content = json.dumps(result, indent=2) + "\n"
    if args.check:
        if output.read_text() != content:
            raise ValueError("Stale movement comparison report")
    else:
        output.write_text(content)
    print("Movement/hazard comparisons", len(cases), "passed", flush=True)


if __name__ == "__main__":
    main()
