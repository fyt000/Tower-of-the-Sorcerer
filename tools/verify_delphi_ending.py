"""Compare capture/ending renderer instructions through observed VCL effects."""
import argparse
import copy
import hashlib
import itertools
import json
from pathlib import Path
import re
import struct

import pefile
from unicorn.x86_const import UC_X86_REG_EAX, UC_X86_REG_EDX, UC_X86_REG_ECX

from verify_delphi_ui import UIRunner
from verify_delphi_graphics import ROOT, WORK, ORIGINAL_HASH, digest, first_difference
from delphi_routine_layout import trace_layout


def media_properties(pe):
    """Authenticate the fields and setters from each executable's own RTTI."""
    raw = pe.get_memory_mapped_image()
    marker = b"\x07\x0cTMediaPlayer"
    hits = [m.start() for m in re.finditer(re.escape(marker), raw)]
    if len(hits) != 1:
        raise ValueError("Ambiguous media-player RTTI")
    cursor = hits[0] + len(marker) + 10
    cursor += 1 + raw[cursor]
    count = struct.unpack_from("<H", raw, cursor)[0]
    cursor += 2
    result = {}
    for _ in range(count):
        length = raw[cursor + 26]
        name = raw[cursor + 27:cursor + 27 + length].decode("ascii")
        result[name] = struct.unpack_from("<3I", raw, cursor + 4)
        cursor += 27 + length
    return result


class EndingRunner(UIRunner):
    def __init__(self, pe, **kwargs):
        super().__init__(pe, include_prefixes=False, extra_game={"openning9": 0x482E60},
                         extra_boundaries={0x42C464: "TTimer.SetInterval", 0x41A784: "TCanvas.StretchDraw",
                                           0x431C8C: "TMediaPlayer.SetDeviceType", 0x430F20: "TMediaPlayer.Open",
                                           0x431C5C: "TMediaPlayer.SetNotify", 0x431250: "TMediaPlayer.Play"}, **kwargs)
        props = media_properties(pe)
        self.media_file_offset = 0x20C if self.original else 0x208
        if props["FileName"][:2] != (0xFF000000 | self.media_file_offset,) * 2:
            raise ValueError("Unreviewed media filename field")
        for prop, method in (("DeviceType", "SetDeviceType"),):
            if self.boundaries.get(props[prop][1]) != "TMediaPlayer." + method:
                raise ValueError("Unreviewed media setter")
        notify = next(at for at, name in self.boundaries.items() if name == "TMediaPlayer.SetNotify")
        # Notify is public, not published: authenticate its complete setter.
        shift = 0 if self.original else 4
        setter = (b"\x3a\x90" + struct.pack("<I", 0x1E1 - shift) + b"\x74\x06\x88\x90"
                  + struct.pack("<I", 0x1E1 - shift) + b"\xc6\x80"
                  + struct.pack("<I", 0x1E3 - shift) + b"\x01\xc3")
        if pe.get_data(notify - pe.OPTIONAL_HEADER.ImageBase, len(setter)) != setter:
            raise ValueError("Unreviewed Notify setter")
        self.media_name = ""
        if self.original:
            reviewed = json.loads((ROOT / "delphi/routine-boundaries.json").read_text())["reviewed_routines"]
            stop = next(int(r["successor"], 16) for r in reviewed if int(r["entry"], 16) == 0x482E60)
            self.allowed.update(at for at, _ in trace_layout(pe, 0x482E60, stop)["records"])

    def put_string(self, destination, raw):
        if destination == self.components["MediaPlayer5"] + self.media_file_offset:
            self.media_name = raw.decode("cp1252")
            self.trace.append(["media_filename", self.media_name])
        super().put_string(destination, raw)

    def observe(self, name):
        a, d, c = (self.u.reg_read(r) for r in (UC_X86_REG_EAX, UC_X86_REG_EDX, UC_X86_REG_ECX))
        if name == "TTimer.SetInterval":
            self.trace.append(["timer_interval", self.object_name(a), d])
            self.write32(a + 0x24, d)
        elif name == "TCanvas.StretchDraw":
            self.trace.append(["stretch_draw", self.object_name(a),
                               list(struct.unpack("<4i", self.u.mem_read(d, 16))), self.object_name(c)])
        elif name.startswith("TMediaPlayer."):
            if name.endswith(("SetDeviceType", "SetNotify")):
                self.trace.append(["media", self.object_name(a), name, d & 255])
            else:
                self.trace.append(["media", self.object_name(a), name, self.media_name])
        else:
            super().observe(name)
            return
        self.ret()

    def state(self):
        result = super().state()
        # Bitmap addresses are allocator details; compare their identity and size.
        for key in ("MapBitmap1", "MapBitmap2", "WorkBitmap1", "WorkBitmap2", "WorkBitmap3", "FrameBitmap"):
            result[key] = self.bitmap_objects[self.read32(self.storage[key])].copy()
        result["intervals"] = [self.read32(self.components[n] + 0x24) for n in ("Timer1", "Timer2")]
        result["bounds"] = {n: [self.read32(p + o) for o in (0x24, 0x28, 0x2C, 0x30)]
                            for n, p in self.components.items()}
        result["media_filename"] = self.media_name
        return result


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--candidate", type=Path, default=WORK / "game/Tower.exe")
    parser.add_argument("--check", action="store_true")
    args = parser.parse_args()
    original_path = ROOT / "build/research/TSW.exe"
    if digest(original_path) != ORIGINAL_HASH:
        raise ValueError("Original executable changed")
    old = EndingRunner(pefile.PE(str(original_path)), original=True)
    new = EndingRunner(pefile.PE(str(args.candidate)), map_path=args.candidate.with_suffix(".map"))
    ready = {}
    model_names = ("bitmap_objects", "canvas_objects", "list_counts", "font_sizes", "control_properties",
                   "menu_checks", "names", "free_bitmap_slots", "bitmap_serial", "next_bitmap", "next_string")
    for scale, runner in itertools.product((0, 1), (old, new)):
        runner.seed(scale)
        runner.run("syokidata0")
        ready[scale, runner.original] = dict(
            objects=bytes(runner.u.mem_read(0x600000, 0x200000)),
            globals={n: bytes(runner.u.mem_read(p, runner.spec[n][1])) for n, p in runner.storage.items()},
            models={n: copy.deepcopy(getattr(runner, n)) for n in model_names})

    def seed(scale, speed, cycle, mouse, music):
        for runner in (old, new):
            prepared = ready[scale, runner.original]
            runner.u.mem_write(0x600000, prepared["objects"])
            for name, raw in prepared["globals"].items():
                runner.u.mem_write(runner.storage[name], raw)
            for name, model in prepared["models"].items():
                setattr(runner, name, copy.deepcopy(model))
            runner.texts.clear()
            runner.media_name = ""
            runner.u.mem_write(runner.storage["GameOptions"] + 3, bytes([speed]))
            runner.write32(runner.storage["Hero"] + 636, cycle)
            runner.u.mem_write(runner.components["MouseControl1"] + 0x28, bytes([mouse]))
            runner.u.mem_write(runner.components["BGMON1"] + 0x28, bytes([music]))
            runner.write32(runner.storage["EventCursor"], 7)
            runner.trace.clear()

    cases, transcript = [], hashlib.sha256()
    frames = {0: (232, 233, 246, 247, 248), 2: (232, 246, 247, 248),
              1: (0, 1, 399, 400, 499, 500), 4: (0, 1, 99, 199, 399, 400),
              5: (1, 200, 399, 400, 500), 6: tuple(range(19)),
              7: (0,), 8: (0,), 3: (0,), -1: (0,), 9: (0,)}
    for scale, speed, cycle, mouse, music in itertools.product((0, 1), (1, 2, 3), (0, 43), (0, 1), (0, 1)):
        seed(scale, speed, cycle, mouse, music)
        for mode, steps in frames.items():
            for frame in steps:
                for runner in (old, new):
                    runner.u.mem_write(runner.storage["EventStack"] + 6 * 6,
                                       struct.pack("<6h", 0, mode, 0, 11, 6, frame))
                expected, actual = old.run("openning9"), new.run("openning9")
                a, b = old.state(), new.state()
                difference = first_difference(expected, actual)
                state_differences = [name for name in a if a[name] != b[name]]
                inputs = dict(scale=scale, speed=speed, cycle=cycle, mouse=mouse, music=music, mode=mode, frame=frame)
                row = dict(inputs=inputs, passed=difference is None and not state_differences,
                           original_effects=len(expected), candidate_effects=len(actual),
                           first_difference=difference, state_differences=state_differences)
                cases.append(row)
                transcript.update(json.dumps([inputs, expected, actual, a, b], sort_keys=True).encode())
                if not row["passed"]:
                    raise ValueError(json.dumps(row, indent=2))
    result = dict(original_sha256=ORIGINAL_HASH, candidate_sha256=digest(args.candidate),
                  comparisons=len(cases), cases=cases, fixture_transcript_sha256=transcript.hexdigest(),
                  passed=True, limits="Game callees execute. VCL drawing, controls and media use explicit observers; this does not measure display pixels, audible playback or timer delivery.")
    output = (WORK / "reports/ending-comparison-report.json" if args.candidate == WORK / "game/Tower.exe"
              else args.candidate.parent / "ending-comparison-report.json")
    content = json.dumps(result, indent=2) + "\n"
    if args.check:
        if output.read_text() != content:
            raise ValueError("Stale ending comparison report")
    else:
        output.write_text(content)
    print("Capture/ending state/drawing comparisons", len(cases), "passed", flush=True)


if __name__ == "__main__":
    main()
