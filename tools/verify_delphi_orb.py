"""Execute the original and recovered Hero's Orb open/row/close bodies.

Game callees execute; existing VCL observers compare ordered effects and state.
This does not establish full-window pixel equality or Windows focus delivery.
"""
import argparse
import copy
import hashlib
import itertools
import json
from pathlib import Path

import pefile

from verify_delphi_ui import UIRunner
from verify_delphi_graphics import ROOT, WORK, ORIGINAL_HASH, digest, first_difference
from delphi_routine_layout import trace_layout


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--candidate", type=Path, default=WORK / "game/Tower.exe")
    parser.add_argument("--check", action="store_true")
    args = parser.parse_args()
    original_path = ROOT / "build/research/TSW.exe"
    if digest(original_path) != ORIGINAL_HASH:
        raise ValueError("Original executable changed")
    entries = dict(img6work=0x480F60, yousya=0x44F26C, Button36Click=0x4503EC,
                   obudameiji=0x44FF0C, damecount=0x45031C)
    storage = dict(OrbRow=(0x48C5B0, 4), OrbEnemies=(0x489908, 7),
                   RemainingHP=(0x48C5B4, 4), DamageText=(0x4B8678, 4))
    old = UIRunner(pefile.PE(str(original_path)), original=True,
                   extra_game=entries, extra_storage=storage)
    new = UIRunner(pefile.PE(str(args.candidate)), map_path=args.candidate.with_suffix(".map"),
                   include_prefixes=False, extra_game=entries, extra_storage=storage)
    for runner in (old, new):
        runner.string_globals.add("DamageText")
    # Decode the reviewed full boundaries, including finally continuations
    # omitted by the original decompiler's export.
    reviewed = {int(row["entry"], 16): int(row["successor"], 16) for row in
                json.loads((ROOT / "delphi/routine-boundaries.json").read_text())["reviewed_routines"]}
    for at in entries.values():
        old.allowed.update(address for address, raw in trace_layout(old.pe, at, reviewed[at])["records"])
    ready = {}
    for scale, runner in itertools.product((0, 1), (old, new)):
        runner.seed(scale)
        runner.write32(runner.components["Button36"], runner.button_vmt)
        runner.run("syokidata0")
        ready[scale, runner.original] = dict(
            objects=bytes(runner.u.mem_read(0x600000, 0x200000)),
            globals={name: bytes(runner.u.mem_read(at, runner.spec[name][1])) for name, at in runner.storage.items()},
            models=copy.deepcopy((runner.bitmap_objects, runner.canvas_objects, runner.list_counts,
                                  runner.font_sizes, runner.control_properties, runner.menu_checks)),
            next_bitmap=runner.next_bitmap, next_string=runner.next_string,
            bitmap_serial=runner.bitmap_serial)

    def seed(scale, floor, orb, cycle=0, attack=1000):
        for runner in (old, new):
            prepared = ready[scale, runner.original]
            runner.u.mem_write(0x600000, prepared["objects"])
            for name, raw in prepared["globals"].items():
                runner.u.mem_write(runner.storage[name], raw)
            (runner.bitmap_objects, runner.canvas_objects, runner.list_counts,
             runner.font_sizes, runner.control_properties, runner.menu_checks) = copy.deepcopy(prepared["models"])
            runner.next_bitmap, runner.next_string = prepared["next_bitmap"], prepared["next_string"]
            runner.bitmap_serial = prepared["bitmap_serial"]
            runner.texts.clear()
            for offset, value in ((16, floor), (68, orb), (636, cycle), (4, attack), (8, 100)):
                runner.write32(runner.storage["Hero"] + offset, value)
            runner.trace.clear()

    cases, transcript = [], hashlib.sha256()

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

    # Every original floor, both resolutions, every ownership gate. Close and
    # reopen without reseeding so stale controls, row bytes and timers are visible.
    for scale, floor, orb in itertools.product((0, 1), range(1, 51), (0, 1, 2)):
        seed(scale, floor, orb)
        inputs = dict(scale=scale, floor=floor, orb=orb)
        compare("img6work", inputs)
        if orb == 1:
            compare("Button36Click", inputs)
            compare("img6work", inputs | dict(reopened=True))
            compare("Button36Click", inputs | dict(reopened=True))
    print("Orb campaign-floor sequences", len(cases), "passed", flush=True)

    # Synthetic maps cover every tile, alternating frames, the seven-row cap,
    # empty floors, and the octopus/dragon body tiles that are not Orb entries.
    fixtures = [[], [61, 62] * 50, list(range(61, 96)), list(range(96, 133)),
                list(range(133, 159)), [122, 104, 61, 63, 65, 67, 69, 71, 73]]
    fixtures += [[tile] for tile in range(256)]
    for scale, tiles in itertools.product((0, 1), fixtures):
        seed(scale, 1, 1)
        for runner in (old, new):
            runner.u.mem_write(runner.storage["Maps"] + 123 + 2, bytes(tiles + [6] * (121 - len(tiles))))
        compare("img6work", dict(scale=scale, tiles=tiles))
        compare("Button36Click", dict(scale=scale, tiles=tiles))

    # All seven row branches, including original row-six spacing; damage uses
    # the real recursive calculator and retains the Orb's Cross/Slayer policy.
    for row, enemy, cycle, attack in itertools.product(range(1, 8), range(33), (0, 3), (10, 1000)):
        seed(0, 1, 1, cycle, attack)
        for runner in (old, new):
            runner.write32(runner.storage["OrbRow"], row)
            runner.u.mem_write(runner.storage["OrbEnemies"], bytes([255]) * 7)
            runner.write32(runner.storage["NeighborIndex"], enemy)
        compare("yousya", dict(row=row, enemy=enemy, cycle=cycle, attack=attack))
    result = dict(original_sha256=ORIGINAL_HASH, candidate_sha256=digest(args.candidate),
                  comparisons=len(cases), cases=cases, fixture_transcript_sha256=transcript.hexdigest(),
                  passed=True, limits="Game callees execute; VCL controls, strings, drawing and focus use explicit observers. This is not strict byte equivalence or full-window pixel equality.")
    output = args.candidate.parent / "orb-comparison-report.json" if args.candidate != WORK / "game/Tower.exe" else WORK / "reports/orb-comparison-report.json"
    content = json.dumps(result, indent=2) + "\n"
    if args.check:
        if output.read_text() != content:
            raise ValueError("Stale Orb comparison report")
    else:
        output.write_text(content)
    print("Orb state/drawing comparisons", len(cases), "passed", flush=True)


if __name__ == "__main__":
    main()
