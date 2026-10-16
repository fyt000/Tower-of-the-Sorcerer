"""Execute original and compiled dialogue/merchant/fairy bodies at VCL boundaries."""
import argparse
import copy
import hashlib
import itertools
import json
from pathlib import Path
import struct

import pefile
from unicorn.x86_const import UC_X86_REG_EAX, UC_X86_REG_EDX, UC_X86_REG_ECX, UC_X86_REG_ESP

from verify_delphi_ui import UIRunner
from verify_delphi_graphics import ROOT, WORK, ORIGINAL_HASH, digest, first_difference, symbols, data_symbols
from verify_delphi_ending import media_properties
from delphi_routine_layout import trace_layout


GAME = dict(syounin=0x449014, zyouout=0x449E18, Button1Click=0x44DA10,
            Button2Click=0x44E1CC, yousei=0x478F0C, stackwork=0x4526C0,
            timer2timer=0x45265C, timerin=0x47F5A8, soundplay=0x47C2BC,
            Button38Click=0x450BA0, mmmes=0x451C20, matokwork=0x451B98,
            yukiwork=0x451D3C, toroad2=0x44BC34, doorstackin=0x4660D0, soundcheck=0x47C8F8,
            taisen2=0x47F7D4, dameiji2=0x48028C, damei3=0x4802FC, ydamei3=0x480340,
            taisen=0x44A480, ydameiji=0x450288, ydameiji2=0x4502D0, ydamecount=0x4503A8,
            yusyaidou=0x443808, idou=0x44C04C, madoushi1=0x44C464, mazyutu1=0x44C5C4,
            dameiji=0x450064, damecount=0x45031C, damecount2=0x450360)
STATE = dict(DialogueSpeech=(0x48C5C8, 2), DialogueStage=(0x48C5A4, 4),
             ShopMode=(0x48C5CC, 2), MerchantTradeWord=(0x48C598, 4),
             MerchantClueWord=(0x48C59C, 4), GameplayHintIndex=(0x48C5A0, 4),
             GameplayShopCost=(0x48C594, 4), EventPaused=(0x48C5C0, 4),
             BattleHP=(0x48C5BC, 4), SettingsFile=(0x48C600, 332), IOPath=(0x48C5D4, 4))
STATE["ContactIndex"] = (0x48C584, 4)
STATE["RemainingHP"] = (0x48C5B4, 4)
BOUNDARIES = {0x4135A4: "TControl.GetText", 0x4237DC: "TForm.ShowModal",
              0x42CEC8: "MessageDlg", 0x431188: "TMediaPlayer.Close",
              0x431250: "TMediaPlayer.Play", 0x430F20: "TMediaPlayer.Open",
              0x42C464: "TTimer.SetInterval", 0x40414D: "@Assign", 0x40458D: "@ResetFile",
              0x4041F0: "@BlockRead", 0x404254: "@BlockWrite", 0x4042B8: "@Close",
              0x4045A4: "@RewritFile", 0x402710: "@_IOTest", 0x42CF78: "ShowMessage",
              0x431C8C: "TMediaPlayer.SetDeviceType", 0x431C5C: "TMediaPlayer.SetNotify"}


class DialogueRunner(UIRunner):
    def __init__(self, pe, extra_game=None, extra_storage=None, **kwargs):
        game = {**GAME, **(extra_game or {})}
        super().__init__(pe, include_prefixes=False, extra_game=game,
                         extra_storage={**STATE, **(extra_storage or {})}, extra_boundaries=BOUNDARIES, **kwargs)
        self.string_globals.add("IOPath")
        self.media_offset = 0x20C if self.original else 0x208
        assert media_properties(pe)["FileName"][:2] == (0xFF000000 | self.media_offset,) * 2
        assert self.boundaries[media_properties(pe)["DeviceType"][1]] == "TMediaPlayer.SetDeviceType"
        if self.original:
            bounds = json.loads((ROOT / "delphi/routine-boundaries.json").read_text())["reviewed_routines"]
            stops = {int(r["entry"], 16): int(r["successor"], 16) for r in bounds}
            for at in game.values():
                self.allowed.update(at for at, _ in trace_layout(pe, at, stops[at])["records"])
        self.answer = 6
        self.ranking_bytes = bytes(288)
        self.files = {}

    def seed(self, *args, **kwargs):
        super().seed(*args, **kwargs)
        for name, pointer in self.components.items():
            if name.startswith("Button"):
                self.write32(pointer, self.button_vmt)
                self.u.mem_write(pointer + 0x38, b"\1")
        self.write32(self.components["RichEdit1"] + (0x140 if self.original else 0x13C), 0x60A400)
        self.write32(0x60A400, 0x60A800)
        self.write32(0x60A800 + 0x38, 0x60A000)  # TStrings.Clear virtual slot.
        self.files = {}

    def step(self, u, at, size, data):
        if at == 0x605000:
            index = u.reg_read(UC_X86_REG_EDX)
            if index not in (0, 1):
                raise ValueError("Unexpected Memo12 line")
            self.put_string(u.reg_read(UC_X86_REG_ECX), b"X:\\saves" if index == 0 else b"X:\\original")
            self.ret()
        elif at == 0x60A000:
            assert u.reg_read(UC_X86_REG_EAX) == 0x60A400
            self.texts["RichEdit1"] = ""
            self.trace.append(["clear_lines", "RichEdit1"])
            self.ret()
        else:
            super().step(u, at, size, data)

    def put_string(self, destination, raw):
        for name, pointer in self.components.items():
            if name.startswith("MediaPlayer") and destination == pointer + self.media_offset:
                self.trace.append(["media_filename", name, raw.decode("cp1252")])
        super().put_string(destination, raw)

    def observe(self, name):
        a, d, c, sp = (self.u.reg_read(r) for r in (UC_X86_REG_EAX, UC_X86_REG_EDX,
                                                   UC_X86_REG_ECX, UC_X86_REG_ESP))
        if name == "TControl.GetText":
            self.put_string(d, self.texts.get(self.object_name(a), "").encode("cp1252"))
        elif name == "TForm.ShowModal":
            self.trace.append(["ranking_modal"])
            self.ret(value=1)
            return
        elif name == "MessageDlg":
            self.trace.append(["message_dialog", self.string(a).decode("cp1252"), d & 255, c & 0xFFFF,
                               self.read32(sp + 4), self.answer])
            self.ret(4, value=self.answer)
            return
        elif name == "ShowMessage":
            self.trace.append(["message", self.string(a).decode("cp1252")])
        elif name.startswith("TMediaPlayer."):
            self.trace.append(["media", self.object_name(a), name] +
                              ([d & 255] if name.endswith(("SetDeviceType", "SetNotify")) else []))
        elif name == "TTimer.SetInterval":
            self.trace.append(["timer_interval", self.object_name(a), d])
            self.write32(a + 0x24, d)
        elif name == "@Assign":
            assert a == self.storage["SettingsFile"]
            self.path = self.string(d).decode("cp1252")
            self.trace.append(["assign", self.path])
        elif name in ("@ResetFile", "@RewritFile"):
            self.trace.append([name, self.path, d])
            if name == "@RewritFile":
                self.files[self.path] = b""
        elif name == "@BlockRead":
            assert c == 288 and self.read32(sp + 4) == 0
            self.u.mem_write(d, self.ranking_bytes)
            self.trace.append(["read", self.path, c])
            self.ret(4)
            return
        elif name == "@BlockWrite":
            assert self.read32(sp + 4) == 0
            raw = bytes(self.u.mem_read(d, c))
            self.files[self.path] += raw
            self.trace.append(["write_file", self.path, c, hashlib.sha256(raw).hexdigest()])
            self.ret(4)
            return
        elif name == "@Close":
            self.trace.append(["close", self.path])
        elif name == "@_IOTest":
            pass
        else:
            super().observe(name)
            return
        self.ret()


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--candidate", type=Path, default=WORK / "game/Tower.exe")
    parser.add_argument("--check", action="store_true")
    parser.add_argument("--skip-audio", action="store_true", help="Skip dedicated music and sound-opcode cases")
    args = parser.parse_args()
    original = ROOT / "build/research/TSW.exe"
    assert digest(original) == ORIGINAL_HASH
    old = DialogueRunner(pefile.PE(str(original)), original=True)
    new = DialogueRunner(pefile.PE(str(args.candidate)), map_path=args.candidate.with_suffix(".map"))
    ready = {}
    models = ("bitmap_objects", "canvas_objects", "list_counts", "font_sizes", "control_properties",
              "menu_checks", "names", "free_bitmap_slots", "bitmap_serial", "next_bitmap", "next_string")
    for scale, runner in itertools.product((0, 1), (old, new)):
        runner.seed(scale)
        runner.run("syokidata0")
        ready[scale, runner.original] = dict(objects=bytes(runner.u.mem_read(0x600000, 0x200000)),
            globals={n: bytes(runner.u.mem_read(p, runner.spec[n][1])) for n, p in runner.storage.items()},
            models={n: copy.deepcopy(getattr(runner, n)) for n in models})

    def seed(scale=0, hero=None, state=None):
        for runner in (old, new):
            prepared = ready[scale, runner.original]
            runner.u.mem_write(0x600000, prepared["objects"])
            for n, raw in prepared["globals"].items():
                runner.u.mem_write(runner.storage[n], raw)
            for n, value in prepared["models"].items():
                setattr(runner, n, copy.deepcopy(value))
            for offset, value in (hero or {}).items():
                runner.write32(runner.storage["Hero"] + offset, value)
            for n, value in (state or {}).items():
                runner.u.mem_write(runner.storage[n], value.to_bytes(runner.spec[n][1], "little", signed=True))
            runner.texts = {"RichEdit1": "prepared ranking"}
            runner.files = {}
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
        transcript.update(json.dumps([inputs, expected], sort_keys=True).encode())
        if not row["passed"]:
            raise ValueError(row)

    for scale, floor, x, trade, clue, orb in itertools.product((0, 1), (2, 6, 7, 12, 15, 28, 31, 38, 39, 45, 47), (1, 9), (0, 1), (0, 1, 2), (0, 1)):
        # Repeatable merchants do not enter the completed-trade branch.
        if floor == 28 and trade or floor == 12 and x == 9 and trade:
            continue
        seed(scale, {16: floor, 24: x, 72: orb, **{i * 4: trade for i in range(42, 54)},
                     **{i * 4: clue for i in range(54, 66)}})
        compare("syounin", [scale, floor, x, trade, clue, orb])
        if trade == 0:
            compare("Button2Click", ["accept", scale, floor, x, orb])
    for scale, cycle, floor in itertools.product((0, 1), (0, 1, 43), (4, 12, 32, 46)):
        seed(scale, {16: floor, 44: 3, 636: cycle}, {"ShopMode": 1})
        compare("Button2Click", ["altar", scale, cycle, floor])
    for floor, x, gold, keys in itertools.product((2, 6, 7, 12, 15, 28, 31, 38, 39, 45, 47), (1, 9), (0, 50, 10000), (0, 2)):
        seed(hero={16: floor, 24: x, 12: gold, 32: keys})
        compare("syounin", ["purchase", floor, x, gold, keys])
        compare("Button2Click", ["purchase", floor, x, gold, keys])
    for scale, speech, automatic, answer in itertools.product((0, 1), (1, 5, 16, 17, 22, 24, 40, 47, 55, 61, 93), (0, 1), (6, 7)):
        seed(scale, {668: automatic}, {"DialogueStage": speech + 10, "DialogueSpeech": speech})
        old.answer = new.answer = answer
        compare("zyouout", [scale, speech, automatic, answer])
    for stage, cycle in itertools.product([0, 1, 11, 12, 13, 14, 15, 16, 17, 19, 21, 26, 32, 34, 50, 57, 67, 71, 72, 103, 274], (0, 1)):
        seed(hero={636: cycle}, state={"DialogueStage": stage, "EventPaused": 1})
        compare("Button1Click", [stage, cycle])
    for floor, cycle, hp, visits in itertools.product((10, 20, 25, 40, 49), (0, 1, 43), (1, 1000, 10000, 100000), (0, 3)):
        seed(hero={16: floor, 636: cycle, 0: hp, 56: visits}, state={"EventCursor": 4})
        # Invalid checksums exercise the original fallback table in each category.
        old.ranking_bytes = new.ranking_bytes = struct.pack("<72i", *range(72))
        compare("yousei", [floor, cycle, hp, visits])
    for opcode, a, b in [(0, 0, 0), (1, 1, 0), (1, 7, 0), (2, 5, 0), (4, 0, 0), (5, 0, 0),
                         (6, 60, 6), (7, 200, 0), (8, 0, 0), (9, 60, 183), (10, 21, 0),
                         (14, 60, 183), (16, -500, 0), (17, 60, 6), (18, 0, 0),
                         (19, 0, 0), (20, 35, 1), (21, 0, 1), (21, 1, 121)]:
        if args.skip_audio and opcode == 1:
            continue
        for scale, cycle, monster in itertools.product((0, 1), (0, 43), (0, 12, 17, 19)):
            seed(scale, {636: cycle, 80: 1, 108: 1, 356: 1},
                 {"EventCursor": 4, "EventPaused": 1, "MonsterIndex": monster, "BattleHP": 10000})
            for runner in (old, new):
                runner.u.mem_write(runner.storage["EventStack"] + 18, struct.pack("<6h", 0, 6, 184, opcode, a, b))
            compare("stackwork", [opcode, a, b, scale, cycle, monster])
    for cursor, paused in itertools.product(range(4), (0, 1)):
        seed(state={"EventCursor": cursor, "EventPaused": paused})
        compare("timer2timer", [cursor, paused])
    for track in (() if args.skip_audio else range(-1, 23)):
        seed(hero={360: track})
        for runner in (old, new):
            runner.put_string(runner.components["MediaPlayer5"] + runner.media_offset, b"previous.mid")
        compare("soundplay", [track])
    for scale, item, position, tile, music in itertools.product(
            (0, 1), (5, 6, 7, 8, 9, 10, 12, 13, 14), (0, 60, 120), (6, 8, 13, 61), (0, 5)):
        seed(scale, {0: 1000, 4: 20, 8: 30, 16: 2, 24: position % 11, 28: position // 11,
                     80: 1, 84: 1, 88: 1, 92: 3, 100: 1, 104: 1, 108: 1, 116: 1, 120: 1,
                     360: music, 352: 1}, {"GameplayItemChoice": item, "EventCursor": 4, "EventPaused": 1})
        for runner in (old, new):
            runner.u.mem_write(runner.storage["Maps"], bytes([6]) * 6273)
            for cell in (0, 1, 11, 49, 59, 61, 71, 109, 119, 120):
                runner.u.mem_write(runner.storage["Maps"] + 2 * 123 + cell + 2, bytes([tile]))
            for floor in (1, 3):
                runner.u.mem_write(runner.storage["Maps"] + floor * 123 + position + 2, bytes([tile]))
            # Sparse doors keep the complete expanded queue inside this fixture's observed span.
            if item == 13:
                for cell in (0, 60, 120):
                    runner.u.mem_write(runner.storage["Maps"] + 2 * 123 + cell + 2, b"\1")
        compare("Button38Click", [scale, item, position, tile, music])
    for scale, hp, attack, defense, cycle, target, enemy in itertools.product(
            (0, 1), (1, 15, 1000), (20, 23), (10, 30), (0, 1), (49, 71), (0, 12, 26)):
        seed(scale, {0: hp, 4: attack * (cycle + 1), 8: defense * (cycle + 1), 16: 1,
                     24: 5, 28: 5, 352: 1, 636: cycle, 80: 1, 124: 1},
             {"EventCursor": 4, "ContactIndex": 60})
        for runner in (old, new):
            runner.u.mem_write(runner.storage["Maps"], bytes([6]) * 6273)
            runner.u.mem_write(runner.storage["Monsters"] + enemy * 16, struct.pack("<4i", 30, 25, 10, 123))
            tile = 61 + enemy * 2 if enemy < 18 else 133 + (enemy - 20) * 2
            runner.u.mem_write(runner.storage["Maps"] + 123 + target + 2, bytes([tile]))
            runner.u.mem_write(runner.storage["EventStack"] + 5 * 6, struct.pack("<3H", 11, 10, target))
        compare("taisen2", [scale, hp, attack, defense, cycle, target, enemy])
    for scale, hp, attack, defense, cycle, enemy, bonus in itertools.product(
            (0, 1), (1, 15, 1000), (10, 20), (10, 30), (0, 1), (0, 12, 17, 18, 19, 26), (0, 1)):
        seed(scale, {0: hp, 4: attack * (cycle + 1), 8: defense * (cycle + 1), 16: 1,
                     24: 5, 28: 5, 352: 1, 636: cycle, 80: bonus, 108: bonus, 124: bonus},
             {"EventCursor": 4, "ContactIndex": 49})
        for runner in (old, new):
            runner.u.mem_write(runner.storage["Maps"], bytes([6]) * 6273)
            runner.u.mem_write(runner.storage["Monsters"] + enemy * 16, struct.pack("<4i", 30, 25, 10, 123))
            tile = {18: 104, 19: 122}.get(enemy, 61 + enemy * 2 if enemy < 18 else 133 + (enemy - 20) * 2)
            runner.u.mem_write(runner.storage["Maps"] + 123 + 49 + 2, bytes([tile]))
        compare("taisen", [scale, hp, attack, defense, cycle, enemy, bonus])
    for tile, bonus in itertools.product(range(97, 106), (0, 1)):
        seed(hero={0: 1000, 4: 20, 8: 10, 16: 1, 24: 5, 28: 5, 352: 1, 124: bonus},
             state={"EventCursor": 4, "ContactIndex": 49})
        for runner in (old, new):
            runner.u.mem_write(runner.storage["Maps"], bytes([6]) * 6273)
            runner.u.mem_write(runner.storage["Monsters"] + 18 * 16, struct.pack("<4i", 30, 25, 10, 123))
            runner.u.mem_write(runner.storage["Maps"] + 123 + 49 + 2, bytes([tile]))
        compare("taisen", ["octopus", tile, bonus])
    result = dict(original_sha256=ORIGINAL_HASH, candidate_sha256=digest(args.candidate),
                  comparisons=len(cases), passed=True, transcript_sha256=transcript.hexdigest(), cases=cases)
    output = WORK / "reports/dialogue-report.json"
    serialized = json.dumps(result, indent=2) + "\n"
    if args.check:
        if not output.exists() or output.read_text() != serialized:
            raise SystemExit("Dialogue report is stale; rerun without --check")
    else:
        output.parent.mkdir(parents=True, exist_ok=True)
        output.write_text(serialized)
    print(json.dumps({k: v for k, v in result.items() if k != "cases"}))


if __name__ == "__main__":
    main()
