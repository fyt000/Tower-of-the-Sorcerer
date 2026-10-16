"""Execute original and recovered door frames, including their game callees."""
import argparse
import copy
import hashlib
import itertools
import json
from pathlib import Path
import struct

import pefile
from unicorn.x86_const import UC_X86_REG_EAX, UC_X86_REG_EDX

from verify_delphi_graphics import ROOT, WORK, ORIGINAL_HASH, digest, first_difference
from verify_delphi_flight import FlightRunner


class DoorRunner(FlightRunner):
    def __init__(self, pe, **kwargs):
        super().__init__(pe, extra_game={"dooropen": 0x4770E0, "timerin": 0x47F5A8,
                                  "speedhigh": 0x47F47C, "speedmiddle": 0x47F4E0,
                                  "speedlow": 0x47F544},
                         extra_boundaries={0x42C464: "TTimer.SetInterval",
                                     0x4102F0: "TMenuItem.SetChecked"}, **kwargs)

    def observe(self, name):
        a, d = self.u.reg_read(UC_X86_REG_EAX), self.u.reg_read(UC_X86_REG_EDX)
        if name == "TTimer.SetInterval":
            self.trace.append(["timer_interval", self.object_name(a), d])
            self.write32(a + 0x24, d)
        elif name == "TMenuItem.SetChecked":
            self.trace.append(["menu_checked", self.object_name(a), d & 255])
            self.u.mem_write(a + 0x28, bytes([d & 255]))
        else:
            super().observe(name)
            return
        self.ret()

    def state(self):
        return super().state() | dict(
            timer_intervals=[self.read32(self.components[name] + 0x24)
                             for name in ("Timer1", "Timer2", "Timer3")],
            speed_checks=[bytes(self.u.mem_read(self.components[name] + 0x28, 1)).hex()
                          for name in ("High1", "Middle1", "Low1")],
            bitmap_sizes={v["name"]: [v["width"], v["height"]]
                          for v in self.bitmap_objects.values()})


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--candidate", type=Path, default=WORK / "game/Tower.exe")
    parser.add_argument("--check", action="store_true")
    args = parser.parse_args()
    original_path = ROOT / "build/research/TSW.exe"
    if digest(original_path) != ORIGINAL_HASH:
        raise ValueError("Original executable changed")
    old = DoorRunner(pefile.PE(str(original_path)), original=True)
    new = DoorRunner(pefile.PE(str(args.candidate)), map_path=args.candidate.with_suffix(".map"))
    prepared = {}
    for scale, runner in itertools.product((0, 1), (old, new)):
        runner.seed(scale)
        runner.run("syokidata0")
        prepared[scale, runner.original] = dict(
            objects=bytes(runner.u.mem_read(0x600000, 0x200000)),
            globals={name: bytes(runner.u.mem_read(at, runner.spec[name][1]))
                     for name, at in runner.storage.items()},
            models=copy.deepcopy((runner.bitmap_objects, runner.canvas_objects, runner.list_counts)))

    def seed(scale, checks, cell, mode):
        for runner in (old, new):
            saved = prepared[scale, runner.original]
            runner.u.mem_write(0x600000, saved["objects"])
            for name, raw in saved["globals"].items():
                runner.u.mem_write(runner.storage[name], raw)
            runner.bitmap_objects, runner.canvas_objects, runner.list_counts = copy.deepcopy(saved["models"])
            runner.write32(runner.storage["Hero"] + 16, 1)
            runner.write32(runner.storage["EventCursor"], 7)
            runner.u.mem_write(runner.storage["EventStack"] + 7 * 6, struct.pack("<hhh", 13, cell, mode))
            for i, name in enumerate(("High1", "Middle1", "Low1")):
                runner.u.mem_write(runner.components[name] + 0x28, bytes([(checks >> i) & 1]))
            for name in ("Timer1", "Timer2", "Timer3"):
                runner.write32(runner.components[name] + 0x24, 777)
            runner.trace.clear()

    cases, transcript = [], hashlib.sha256()

    def compare(inputs):
        expected, actual = old.run("dooropen"), new.run("dooropen")
        a, b = old.state(), new.state()
        difference = first_difference(expected, actual)
        state_differences = [name for name in a if a[name] != b[name]]
        row = dict(inputs=inputs, passed=difference is None and not state_differences,
                   original_effects=len(expected), candidate_effects=len(actual),
                   first_difference=difference, state_differences=state_differences)
        cases.append(row)
        transcript.update(json.dumps([inputs, expected, actual, a, b], sort_keys=True).encode())
        if not row["passed"]:
            raise ValueError(json.dumps(row, indent=2))

    # Consecutive frames expose map writes and restored speed without reseeding.
    for scale, checks, cell, mode in itertools.product((0, 1), (1, 2, 4), (0, 60, 120), range(1, 13)):
        seed(scale, checks, cell, mode)
        for frame in range(17):
            for runner in (old, new):
                runner.u.mem_write(runner.storage["EventStack"] + 6 * 6, struct.pack("<hhh", 0, 0, frame))
            compare(dict(scale=scale, speed_checks=checks, cell=cell, mode=mode, frame=frame))
    # Exercise the original switch default and all speed-menu combinations.
    for scale, checks, mode in itertools.product((0, 1), range(8), (-1, 0, 1, 6, 8, 12, 13, 32767)):
        seed(scale, checks, 60, mode)
        for runner in (old, new):
            runner.u.mem_write(runner.storage["EventStack"] + 6 * 6, struct.pack("<hhh", 0, 0, 16))
        compare(dict(scale=scale, speed_checks=checks, cell=60, mode=mode, frame=16))
    result = dict(original_sha256=ORIGINAL_HASH, candidate_sha256=digest(args.candidate),
                  comparisons=len(cases), cases=cases, fixture_transcript_sha256=transcript.hexdigest(),
                  passed=True, limits="Game callees execute. VCL drawing and timer setters use explicit observers; this does not measure Windows timer delivery or establish strict byte equivalence.")
    output = (WORK / "reports/door-comparison-report.json" if args.candidate == WORK / "game/Tower.exe"
              else args.candidate.parent / "door-comparison-report.json")
    content = json.dumps(result, indent=2) + "\n"
    if args.check:
        if output.read_text() != content:
            raise ValueError("Stale door comparison report")
    else:
        output.write_text(content)
    print("Door state/drawing comparisons", len(cases), "passed", flush=True)


if __name__ == "__main__":
    main()
