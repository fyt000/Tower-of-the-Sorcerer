"""Compare real Flight opener/preview/confirmation sequences and UI requests.

Game callees execute. VCL controls, strings, focus and timer setters have named
observer boundaries. The queue is compared but its dispatcher is not recovered;
BGM-enabled and actual Windows focus/timer delivery are outside this scope.
"""
import argparse
import copy
import hashlib
import itertools
import json

import pefile
from unicorn.x86_const import UC_X86_REG_EAX, UC_X86_REG_EDX, UC_X86_REG_ECX

from verify_delphi_graphics import (ROOT, WORK, ORIGINAL_HASH, digest, class_vmt,
                                   GraphicsRunner, GAME, GLOBALS, BOUNDARIES, first_difference)

FLIGHT_GAME = {**GAME, "monswork": 0x44B6F4, "monshyouji": 0x44B78C, "disp": 0x44CB34,
               "img4work": 0x481E80, "Button8Click": 0x44ED94, "Button9Click": 0x44ED1C,
               "Button10Click": 0x44EAF4, "itemdel": 0x450758, "itemlive": 0x450880,
               "timer2on": 0x44BC0C, "mmes": 0x44C9F0,
               "kaidanupcheck": 0x442F80, "kaidandowncheck": 0x443050}
FLIGHT_STATE = {**GLOBALS, "Monsters": (0x489910, 528), "MonsterIndex": (0x48C5B8, 4),
                "DamageMode": (0x48C564, 4), "StrikeCount": (0x48C56C, 4), "TileClass": (0x48C58C, 4),
                "InputEnabled": (0x48C5CA, 2), "EventCursor": (0x48C5AC, 4),
                "EventStack": (0x48C74C, 512 * 6), "FlightCell": (0x48C580, 4),
                "FloorSpacing": (0x4B8674, 4), "MonsterText": (0x4B867C, 4), "MessageText": (0x4B8684, 4)}
FLIGHT_BOUNDARIES = {**BOUNDARIES, 0x4034FC: "@LStrArrayClr", 0x4291C8: "TCustomEdit.SetReadOnly", 0x42C150: "TImage.GetCanvas",
                     0x41C160: "TPicture.SetBitmap", 0x405B6C: "IntToStr", 0x4135D4: "TControl.SetText",
                     0x41353C: "TControl.SetEnabled", 0x416C60: "TWinControl.SetFocus",
                     0x42C454: "TTimer.SetEnabled"}


class FlightRunner(GraphicsRunner):
    def __init__(self, pe, original=False, map_path=None, assets=None,
                 extra_game=None, extra_storage=None, extra_boundaries=None):
        super().__init__(pe, original, map_path, assets, game={**FLIGHT_GAME, **(extra_game or {})},
                         storage={**FLIGHT_STATE, **(extra_storage or {})},
                         boundaries={**FLIGHT_BOUNDARIES, **(extra_boundaries or {})})
        self.string_globals.update(("FloorSpacing", "MonsterText", "MessageText"))
        self.items_vmt, self.items = 0x607000, 0x608000
        self.texts = {}
        button_vmt = class_vmt(pe, "TButton")
        slot = 0x80 if original else 0x78
        target = self.read32(button_vmt + slot)
        if self.boundaries.get(target) != "TWinControl.SetFocus":
            raise ValueError("Unexpected Button.SetFocus virtual target")
        if original and (self.read32(button_vmt + 0x78), self.read32(button_vmt + 0x7C)) != (0x415DA4, 0x415DBC):
            raise ValueError("Missing original IME virtual slots")
        self.button_vmt = button_vmt
        if original:
            # Normal post-finally epilogues omitted by Ghidra's exports.
            tails = {0x44B783: "5f5e5b595dc3", 0x44BC04: "5f5e5b8be55dc3", 0x44CCB8: "5f5e5b59595dc3"}
            for address, code in tails.items():
                raw = bytes.fromhex(code)
                if pe.get_data(address - pe.OPTIONAL_HEADER.ImageBase, len(raw)) != raw:
                    raise ValueError(f"Original Flight shared epilogue changed {address:#x}")
                self.allowed.update(range(address, address + len(raw)))
        self.strings = next(node["properties"]["Items.Strings"]["value"] for node in self.form["tree"]["children"]
                            if node["name"] == "ListBox2")

    def seed(self, *args, **kwargs):
        super().seed(*args, **kwargs)
        self.texts.clear()
        self.write32(self.items, self.items_vmt)
        self.write32(self.items_vmt + 0xC, 0x609000)
        self.write32(self.components["ListBox2"] + (0x100 if self.original else 0xFC), self.items)
        for name in ("Button8", "Button9", "Button10"):
            self.write32(self.components[name], self.button_vmt)
            self.u.mem_write(self.components[name] + 0x37, b"\0\1")
        self.write32(self.components["MouseControl1"] + 0x28, 1)
        self.write32(self.components["KeyboardControl1"] + 0x28, 0)
        self.u.mem_write(self.components["Timer4"] + 0x20, b"\0")
        original = pefile.PE(str(ROOT / "build/research/TSW.exe"))
        self.u.mem_write(self.storage["Monsters"], original.get_data(0x489910 - 0x400000, 528))
        self.u.mem_write(self.storage["Maps"], (ROOT / "data/original-map-bytes.bin").read_bytes())
        for offset, value in ((0, 1000), (4, 100), (8, 100), (12, 17), (16, 1), (20, 50), (24, 5), (28, 10), (352, 1), (360, 0)):
            self.write32(self.storage["Hero"] + offset, value)

    def step(self, u, at, size, data):
        if at == 0x609000:
            index = self.u.reg_read(UC_X86_REG_EDX)
            if not 0 <= index < len(self.strings):
                raise ValueError("Unreviewed original ListBox2 string index")
            self.put_string(self.u.reg_read(UC_X86_REG_ECX), self.strings[index].encode("cp1252"))
            self.ret()
            return
        super().step(u, at, size, data)

    def write(self, u, access, at, size, value, data):
        if at == self.self + (0x118 if self.original else 0x114) and size == 1:
            self.trace.append(["key_preview", value])
            return
        super().write(u, access, at, size, value, data)

    def observe(self, name):
        a, d, c = (self.u.reg_read(r) for r in (UC_X86_REG_EAX, UC_X86_REG_EDX, UC_X86_REG_ECX))
        if name == "TCustomEdit.SetReadOnly":
            self.trace.append(["read_only", self.object_name(a), d & 255])
        elif name == "TImage.GetCanvas":
            self.canvas_objects[a + 0x200] = dict(name=self.object_name(a), width=self.read32(a + 0x2C), height=self.read32(a + 0x30))
            self.ret(value=a + 0x200)
            return
        elif name == "TPicture.SetBitmap":
            self.trace.append(["picture_bitmap", self.object_name(a - 0x180), self.object_name(d)])
        elif name == "IntToStr":
            self.put_string(d, str(self.signed(a)).encode("ascii"))
        elif name == "TControl.SetText":
            text = self.string(d).decode("cp1252")
            self.texts[self.object_name(a)] = text
            self.trace.append(["text", self.object_name(a), text])
        elif name == "TControl.SetEnabled":
            self.trace.append(["property", self.object_name(a), "Enabled", d & 255])
            self.u.mem_write(a + 0x38, bytes([d & 255]))
        elif name == "TWinControl.SetFocus":
            self.trace.append(["focus_request", self.object_name(a)])
        elif name == "TTimer.SetEnabled":
            self.trace.append(["timer_enabled", self.object_name(a), d & 255])
            self.u.mem_write(a + 0x20, bytes([d & 255]))
        elif name == "TControl.SetVisible":
            self.u.mem_write(a + 0x37, bytes([d & 255]))
            super().observe(name)
            return
        else:
            super().observe(name)
            return
        self.ret()

    def state(self):
        result = super().state()
        result["buttons"] = {name: bytes(self.u.mem_read(self.components[name] + 0x37, 2)).hex()
                             for name in ("Button8", "Button9", "Button10")}
        result["timers"] = {name: bytes(self.u.mem_read(self.components[name] + 0x20, 1)).hex()
                            for name in ("Timer2", "Timer3", "Timer4")}
        result["texts"] = self.texts.copy()
        return result


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--check", action="store_true")
    args = parser.parse_args()
    if digest(ROOT / "build/research/TSW.exe") != ORIGINAL_HASH:
        raise ValueError("Original pin changed")
    build = json.loads((WORK / "build-report.json").read_text())
    for record in build["inputs"]:
        source = ROOT / record["source"]
        staged = WORK / source.relative_to(ROOT / "delphi")
        if digest(source) != record["source_sha256"] or digest(staged) != record["staged_sha256"]:
            raise ValueError("Stale Flight source: " + record["source"])
    for record in build["builds"].values():
        artifact = ROOT / record["artifact"]
        if digest(artifact) != record["artifact_sha256"] or digest(artifact.with_suffix(".map")) != record["map_sha256"]:
            raise ValueError("Stale Flight artifact")
    original = pefile.PE(str(ROOT / "build/research/TSW.exe"))
    old = FlightRunner(original, original=True)
    new = FlightRunner(pefile.PE(str(WORK / "game/Tower.exe")), map_path=WORK / "game/Tower.map")
    cases, sequences = [], []
    transcript = hashlib.sha256()
    def compare(method, inputs):
        expected, actual = old.run(method), new.run(method)
        a, b = old.state(), new.state()
        diff = first_difference(expected, actual)
        state_diff = [name for name in a if a[name] != b[name]]
        case = dict(method=method, inputs=inputs, passed=diff is None and not state_diff,
                    original_effects=len(expected), compiled_effects=len(actual),
                    first_difference=diff, state_differences=state_diff)
        cases.append(case)
        transcript.update(json.dumps([method, inputs, expected, actual, a, b], sort_keys=True).encode())
        if not case["passed"]:
            print(json.dumps(case, indent=2)); raise ValueError("Flight comparison failed")
        return expected

    print("Comparing full monster-display bodies", flush=True)
    for scale, cycle in itertools.product((0, 1), (0, 43)):
        for runner in (old, new):
            runner.seed(scale, cycle)
            runner.run("syokidata0")
        for row in (-17, -1, *range(33)):
            for runner in (old, new):
                runner.write32(runner.storage["MonsterIndex"], row)
            compare("monshyouji", dict(scale=scale, cycle=cycle, row=row))

    print("Comparing Flight sequences from their real opening gates", flush=True)
    ready = {}
    for scale in (0, 1):
        for runner in (old, new):
            runner.seed(scale)
            runner.run("syokidata0")
            ready[scale, runner.original] = dict(
                objects=bytes(runner.u.mem_read(0x600000, 0x200000)),
                globals={name: bytes(runner.u.mem_read(at, runner.spec[name][1])) for name, at in runner.storage.items()},
                models=copy.deepcopy((runner.bitmap_objects, runner.canvas_objects, runner.list_counts)),
                next_bitmap=runner.next_bitmap, next_string=runner.next_string)
    # Seed a starting game state once per sequence. Do not synthesize any state
    # between the opener, previews and confirmation.
    for scale, floor, highest, orb, neighbor_tile, path in itertools.product(
            (0, 1), (1, 2, 25, 29, 35, 43, 45, 49, 50), ("current", 50),
            (0, 1, 2), (6, 11, 12, 13), ("confirm", "up-down", "down-up")):
        highest = floor if highest == "current" else highest
        inputs = dict(scale=scale, floor=floor, highest=highest, orb=orb, adjacent=neighbor_tile, route=path)
        for runner in (old, new):
            prepared = ready[scale, runner.original]
            runner.u.mem_write(0x600000, prepared["objects"])
            for name, raw in prepared["globals"].items():
                runner.u.mem_write(runner.storage[name], raw)
            runner.bitmap_objects, runner.canvas_objects, runner.list_counts = copy.deepcopy(prepared["models"])
            runner.next_bitmap, runner.next_string = prepared["next_bitmap"], prepared["next_string"]
            runner.texts.clear()
            runner.trace.clear()
            for offset, value in ((16, floor), (20, highest), (24, 5), (28, 5), (76, orb), (352, 4)):
                runner.write32(runner.storage["Hero"] + offset, value)
            runner.u.mem_write(runner.storage["EventStack"], bytes([0xA5]) * (512 * 6))
            # One adjacent tile; the other three cannot override its message.
            for index in (49, 59, 61, 71):
                runner.u.mem_write(runner.storage["Maps"] + floor * 123 + index + 2, bytes([neighbor_tile if index == 49 else 6]))
        compare("img4work", inputs)
        opened = old.read32(old.storage["Hero"] + 48) == 1
        actions = []
        if opened:
            if path == "up-down":
                actions = ["Button8Click", "Button9Click"]
            elif path == "down-up":
                actions = ["Button9Click", "Button8Click"]
            for action in actions:
                compare(action, inputs)
            compare("Button10Click", inputs)
        final = old.storage["Hero"]
        sequences.append(dict(inputs=inputs, opened=opened, actions=actions + (["Button10Click"] if opened else []),
                              final_floor=old.read32(final + 16), final_x=old.read32(final + 24),
                              final_y=old.read32(final + 28), flight_landing_mode=old.read32(final + 632),
                              queued_cursor=old.read32(old.storage["EventCursor"]), passed=True))
        if len(sequences) % 250 == 0:
            print("Flight sequences checked", len(sequences), flush=True)
    report = dict(schema_version=1, original_sha256=ORIGINAL_HASH,
                  build_report_sha256=digest(WORK / "build-report.json"), comparisons=len(cases),
                  cases=cases, sequences=sequences, sequence_count=len(sequences),
                  opened_sequences=sum(s["opened"] for s in sequences),
                  fixture_transcript_sha256=transcript.hexdigest(), measured_flight_bodies_passed=True,
                  full_game_recovered=False, pixel_equivalence_established=False,
                  limits=["Original and newly compiled game callees execute. VCL controls, strings, bitmaps, image lists, timer setters and focus requests have explicit observer models.",
                          "Each sequence begins with the real Flight opener. Failed openers do not run previews or confirmation. Successful sequences preserve every measured state effect between real entries.",
                          "Starting graphics memory is restored from an initializer snapshot executed independently on each binary for each display size. No state is synthesized between Flight stages.",
                          "Effects include the 684-byte hero, all maps, monster table, rendering globals, texts, dialog button gates, requested timers and a seeded 512-command prefix.",
                          "BGM-enabled states and unrecovered soundcheck/soundplay are excluded. They are not treated as accepted differences or silent successes.",
                          "Queued animation commands are compared but not dispatched. Actual Windows focus delivery, input event reachability and timer callback ordering remain unverified."])
    target = ROOT / "build/delphi-game/reports/flight-comparison-report.json"
    content = json.dumps(report, indent=2) + "\n"
    if args.check:
        if target.read_text(encoding="utf-8") != content:
            raise ValueError("Stale Flight report")
    else:
        target.parent.mkdir(parents=True, exist_ok=True)
        target.write_text(content, encoding="utf-8")
    print("Flight/body comparisons", len(cases), "sequences", len(sequences), "opened", report["opened_sequences"], flush=True)


if __name__ == "__main__":
    main()
