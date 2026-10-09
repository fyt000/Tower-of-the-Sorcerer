"""Compare recovered UI bodies, bounded startup prefixes and native witnesses.

Every exercised game callee executes. An explicit stop at the first unrecovered
continuation is a prefix checkpoint, never a whole-method pass. Full client-area
captures are inspection artifacts, not a claim of original screenshot equality.
"""
from pathlib import Path
import argparse
import hashlib
import itertools
import json
import re
import struct

import capstone
import pefile
from unicorn.x86_const import (UC_X86_REG_EAX, UC_X86_REG_EDX, UC_X86_REG_ECX,
                               UC_X86_REG_ESP, UC_X86_REG_EIP, UC_X86_REG_EFLAGS)

from verify_delphi_flight import FlightRunner
from verify_delphi_graphics import (ROOT, WORK, ORIGINAL_HASH, digest, symbols, data_symbols,
                                   first_difference, walk, PixelOracle, pixel_check)
from reconstruct_delphi_project import hero_fields

_HERO_FIELDS = hero_fields()
HERO_OFFSETS = {_HERO_FIELDS.get(offset, "Word" + str(offset)): offset for offset in range(0, 684, 4)}

UI_GAME = dict(keydisplay=0x44BED8, itemdisp=0x44CCD8, Timer1Timer=0x443120,
               takowork1=0x4548A0, takowork2=0x454A58)
UI_STATE = dict(AnimationFrame=(0x48C5D2, 1), KeysPainted=(0x48C5C4, 2))
UI_BOUNDARIES = {0x419E4C: "TFont.SetSize", 0x419E30: "TFont.GetSize",
                 0x4102F0: "TMenuItem.SetChecked", 0x421A54: "TForm.GetCanvas"}
EXTRAS = {"about_activate": (0x43416C, "TAboutBox.formactivate"),
          "about_zeno_click": (0x434130, "TAboutBox.programicononclick"),
          "about_image1_click": (0x434094, "TAboutBox.image1onclick"),
          "about_image2_click": (0x4340B4, "TAboutBox.image2onclick"),
          "about_timer": (0x4340E0, "TAboutBox.Timer1Timer"),
          "holder_activate": (0x440A98, "TForm4.form4activate"),
          "font_prefix": (0x47D4A4, "ApplyOriginalFontPrefix"),
          "visual_prefix": (0x454DE8, "PrepareOriginalVisualPrefix")}
PREFIX_STOPS = {"font_prefix": 0x47F5A8, "visual_prefix": 0x431C8C}


class UIRunner(FlightRunner):
    def __init__(self, pe, original=False, map_path=None, assets=None, include_prefixes=True):
        super().__init__(pe, original, map_path, assets, extra_game=UI_GAME,
                         extra_storage=UI_STATE, extra_boundaries=UI_BOUNDARIES)
        self.font_sizes, self.control_properties, self.menu_checks = {}, {}, {}
        self.free_bitmap_slots, self.bitmap_serial = [], 0
        self.running, self.prefix_reached = None, False
        self.forms = {"TAboutBox": 0x650000, "TForm4": 0x660000}
        self.dialog_components = {}
        manifest = json.loads((ROOT / "reference/original/presentation/ui-manifest.json").read_text())
        self.dialogs = {f["class_name"]: f for f in manifest["forms"] if f["class_name"] in self.forms}
        published = {f["class_name"] + "." + m["name"]: int(m["address"], 16)
                     for f in manifest["forms"] for m in f["methods"]}
        for at, symbol in EXTRAS.values():
            if symbol in published and published[symbol] != at:
                raise ValueError("UI fixture entry disagrees with original method table: " + symbol)
        for cls, form in self.dialogs.items():
            root = self.forms[cls]
            self.names[root] = cls
            components = {f["name"]: root + 0x2000 + i * 0x400 for i, f in enumerate(form["fields"])}
            self.dialog_components[cls] = components
            self.names.update({at: cls + "." + name for name, at in components.items()})
        if original:
            self.dialog_globals = {"TAboutBox": 0x48A760, "TForm4": 0x48C50C}
            for name, (at, _) in EXTRAS.items():
                self.entries[name] = at
                path = ROOT / f"reference/original/whole-program/decompiled/{at:08x}.asm"
                if not path.exists():
                    path = ROOT / f"reference/original/presentation/decompiled/{at:08x}_{EXTRAS[name][1].replace('.', '_')}.asm"
                self.allowed.update(int(x, 16) for x in re.findall(r"^([\da-f]{8})  ", path.read_text(), re.M))
            # Both retained image1onclick exports lose the final setter/return;
            # the whole-program export even decodes bytes at $4340B0 as CALLF.
            # Authenticate this short complete body from the pinned executable.
            body = bytes.fromhex("538bd833d28b83d0010000e85cf4fdffb2018b83b8010000e84ff4fdff5bc3")
            if pe.get_data(0x434094 - pe.OPTIONAL_HEADER.ImageBase, len(body)) != body:
                raise ValueError("Original image1onclick completion changed")
            md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
            self.allowed.update(i.address for i in md.disasm(body, 0x434094))
            self.boundaries.update({at: "PREFIX:" + name for name, at in PREFIX_STOPS.items()})
        else:
            mapping, data = symbols(pe, map_path), data_symbols(pe, map_path)
            self.dialog_globals = {"TAboutBox": data["AboutBox"], "TForm4": data["DataHolderForm"]}
            addresses = sorted(set(mapping.values()))
            for name, (_, symbol) in EXTRAS.items():
                if not include_prefixes and name in PREFIX_STOPS:
                    continue
                at = mapping[symbol]
                self.entries[name] = at
                self.allowed.update(range(at, next(a for a in addresses if a > at)))
        self.entry_names = {v: k for k, v in self.entries.items()}
        self.base_names = self.names.copy()

    def seed(self, *args, **kwargs):
        self.names = self.base_names.copy()
        super().seed(*args, **kwargs)
        self.font_sizes.clear()
        self.free_bitmap_slots.clear()
        self.bitmap_serial = 0
        self.control_properties.clear()
        self.menu_checks.clear()
        for cls, form in self.dialogs.items():
            root, components = self.forms[cls], self.dialog_components[cls]
            self.u.mem_write(root, bytes(0x500))
            self.write32(self.dialog_globals[cls], root)
            for node in walk(form["tree"]):
                if node["name"] not in components:
                    continue
                pointer = components[node["name"]]
                self.u.mem_write(pointer, bytes(0x400))
                for prop, offset in (("Left", 0x24), ("Top", 0x28), ("Width", 0x2C), ("Height", 0x30)):
                    self.write32(pointer + offset, node["properties"].get(prop, {}).get("value", 0))
                if node["class_name"] == "TButton":
                    self.write32(pointer, self.button_vmt)
            for field in form["fields"]:
                self.write32(root + int(field["offset"], 16) - (0 if self.original else 4), components[field["name"]])
        for pointer, name in list(self.names.items()):
            if pointer in self.forms.values() or pointer == self.self:
                continue
            font = pointer + 0x300
            self.names[font] = name + ".Font"
            self.write32(pointer + 0x44, font)
            self.font_sizes[font] = 10

    def write(self, u, access, at, size, value, data):
        for root in self.forms.values():
            if at == root + (0x1A4 if self.original else 0x1A0):
                self.trace.append(["modal_result", self.object_name(root), value])
                return
        super().write(u, access, at, size, value, data)

    def new_bitmap(self):
        if self.free_bitmap_slots:
            pointer = self.free_bitmap_slots.pop()
        else:
            pointer, self.next_bitmap = self.next_bitmap, self.next_bitmap + 0x400
        self.write32(pointer, self.bitmap_vmt)
        self.bitmap_objects[pointer] = dict(name="bitmap" + str(self.bitmap_serial), width=0, height=0)
        self.bitmap_serial += 1
        self.canvas_objects[pointer + 0x200] = self.bitmap_objects[pointer]
        self.write32(pointer + 0x220, 0xCC0020)
        self.trace.append(["bitmap_create", self.bitmap_objects[pointer]["name"]])
        return pointer

    def step(self, u, at, size, data):
        if self.original and self.running in PREFIX_STOPS and at == PREFIX_STOPS[self.running]:
            self.prefix_reached = True
            u.emu_stop()
            return
        super().step(u, at, size, data)

    def observe(self, name):
        a, d = self.u.reg_read(UC_X86_REG_EAX), self.u.reg_read(UC_X86_REG_EDX)
        if name == "TObject.Free":
            self.trace.append(["bitmap_free", self.object_name(a)])
            self.bitmap_objects.pop(a)
            self.canvas_objects.pop(a + 0x200)
            self.free_bitmap_slots.append(a)
        elif name == "TFont.SetSize":
            self.font_sizes[a] = self.signed(d)
            self.trace.append(["font_size", self.object_name(a), self.signed(d)])
        elif name == "TFont.GetSize":
            self.trace.append(["font_get_size", self.object_name(a)])
            self.ret(value=self.font_sizes[a])
            return
        elif name == "TMenuItem.SetChecked":
            self.menu_checks[self.object_name(a)] = d & 255
            self.trace.append(["menu_checked", self.object_name(a), d & 255])
            self.u.mem_write(a + 0x28, bytes([d & 255]))
        elif name == "TForm.GetCanvas":
            pointer = a + 0x800
            self.names[pointer] = "window_canvas"
            self.canvas_objects[pointer] = dict(name="window_canvas", width=self.read32(a + 0x2C), height=self.read32(a + 0x30))
            self.ret(value=pointer)
            return
        elif name in ("TControl.SetVisible", "TControl.SetShowHint", "TControl.SetEnabled"):
            self.control_properties.setdefault(self.object_name(a), {})[name.split("Set")[1]] = d & 255
            super().observe(name)
            return
        elif name == "TTimer.SetEnabled":
            self.control_properties.setdefault(self.object_name(a), {})["Enabled"] = d & 255
            super().observe(name)
            return
        else:
            super().observe(name)
            return
        self.ret()

    def run(self, name):
        previous, self.running, self.prefix_reached = self.self, name, False
        if name.startswith("about_"):
            self.self = self.forms["TAboutBox"]
        elif name.startswith("holder_"):
            self.self = self.forms["TForm4"]
        try:
            if not self.original or name not in PREFIX_STOPS:
                return super().run(name)
            start, stack, stop = len(self.trace), 0x3FE000, 0x3FF000
            self.u.mem_write(0x3FD000, bytes(0x2000))
            self.write32(stack, stop)
            for reg, value in ((UC_X86_REG_ESP, stack), (UC_X86_REG_EAX, self.self),
                               (UC_X86_REG_EDX, 0), (UC_X86_REG_ECX, 0), (UC_X86_REG_EFLAGS, 2)):
                self.u.reg_write(reg, value)
            self.u.emu_start(self.entries[name], stop, count=500000)
            if not self.prefix_reached:
                raise ValueError("Original UI prefix did not reach its declared checkpoint")
            # The installed finally frame is live at this checkpoint. No claim
            # about its continuation/cleanup is made; reset only the test frame.
            self.write32(0, 0)
            return self.trace[start:]
        finally:
            self.self = previous

    def state(self):
        result = super().state()
        result["font_sizes"] = {self.object_name(a): size for a, size in self.font_sizes.items()}
        result["menu_checks"] = self.menu_checks.copy()
        result["control_properties"] = self.control_properties.copy()
        result["dialog_bounds"] = {self.object_name(p): [self.signed(self.read32(p + o)) for o in (0x24, 0x28, 0x2C, 0x30)]
                                   for cls in self.forms for p in [self.forms[cls], *self.dialog_components[cls].values()]}
        return result


def verify_build():
    if digest(ROOT / "build/research/TSW.exe") != ORIGINAL_HASH:
        raise ValueError("Original executable changed")
    build = json.loads((WORK / "build-report.json").read_text())
    for row in build["inputs"]:
        source = ROOT / row["source"]
        staged = WORK / source.relative_to(ROOT / "delphi")
        if digest(source) != row["source_sha256"] or digest(staged) != row["staged_sha256"]:
            raise ValueError("Stale UI source: " + row["source"])
    for row in build["builds"].values():
        path = ROOT / row["artifact"]
        if digest(path) != row["artifact_sha256"] or digest(path.with_suffix(".map")) != row["map_sha256"]:
            raise ValueError("Stale UI executable: " + str(path))
    for row in build["graphics_assets"]:
        if digest(Path(row["path"])) != row["sha256"]:
            raise ValueError("Stale UI asset: " + row["path"])
    return build


class UIPixelOracle(PixelOracle):
    def replay(self, trace):
        for event in trace:
            super().replay([event])
            if event[0] == "load" and event[1] in self.frames:
                # TImage.GetCanvas reads the picture loaded into that control.
                # The graphics-only oracle previously needed these as frames.
                name = event[1]
                self.bitmaps[name] = self.frames[name].copy()
                self.sizes[name] = list(self.bitmaps[name].size)
                self.modes[name] = 0xCC0020


def native_property_checks(trace, rows, stage):
    controls = {r["control"]: r for r in rows if r.get("stage") == stage and "control" in r}
    menus = {r["menu"]: r for r in rows if r.get("stage") == stage and "menu" in r}
    form = next(r for r in rows if r.get("stage") == stage and "control" not in r and "menu" not in r)
    expected = {}
    for event in trace:
        if event[0] == "property":
            _, name, prop, value = event
            expected[name, prop] = value
        elif event[0] == "font_size":
            expected[event[1].removesuffix(".Font"), "font_size"] = event[2]
        elif event[0] == "font_color":
            expected[event[1], "font_color"] = event[2] - 0x100000000 if event[2] >= 0x80000000 else event[2]
        elif event[0] == "menu_checked":
            expected[event[1], "Checked"] = event[2]
        elif event[0] == "hint":
            expected[event[1], "Hint"] = event[2]
        elif event[0] == "text":
            # These fixtures set single-line ASCII TMemo.Text values. Native
            # Text is read verbatim; physical line wrapping is not masked.
            if "\r" in event[2] or "\n" in event[2]:
                raise ValueError("Unreviewed native UI text fixture")
            expected[event[1], "memo_text"] = event[2]
    checks = []
    for (name, prop), value in expected.items():
        name = name.split(".")[-1]
        if name in ("form", "TAboutBox", "TForm4"):
            if prop == "ClientHeight":
                actual = form["client"][1]
            elif prop in ("Width", "Height"):
                actual = form["outer"][0 if prop == "Width" else 1]
            elif prop in ("Left", "Top"):
                actual = form["position"][0 if prop == "Left" else 1]
            else:
                raise ValueError("Unreviewed native form property: " + prop)
        elif name in menus:
            actual = menus[name][prop.lower()]
        else:
            row = controls[name]
            if prop in ("Left", "Top", "Width", "Height"):
                actual = row["bounds"][("Left", "Top", "Width", "Height").index(prop)]
            elif prop.startswith("font_"):
                actual = row["font"][prop.removeprefix("font_")]
            else:
                actual = row[{"ShowHint": "show_hint"}.get(prop, prop.lower())]
        checks.append(dict(stage=stage, object=name, property=prop, expected=value, actual=actual,
                           passed=value == actual))
    if not checks:
        raise ValueError("Native UI property witness is empty: " + stage)
    return checks


def compare_native_ui(original, build):
    record = build["builds"]["ui"]
    output = ROOT / record["output"]
    log = output / "native.log"
    if record["native_exit"] or digest(log) != record["native_log_sha256"]:
        raise ValueError("Native UI execution/log changed")
    if log.read_bytes().decode("cp1252") != record["native_output"]:
        raise ValueError("Native UI output differs from log")
    for name, sha in record["bitmaps"].items():
        if digest(output / name) != sha:
            raise ValueError("Native UI bitmap changed: " + name)
    rows = [json.loads(s) for s in record["native_output"].splitlines() if s.startswith("{")]
    if not rows[-1].get("ui_smoke_passed"):
        raise ValueError("Incomplete native UI smoke")
    assets = Path(r"D:\Program Files (x86)\Tower of the Sorcerer")
    runner = UIRunner(original, original=True, assets=assets)
    checks, pixels = [], []
    for scale in (0, 1):
        seed = next(r for r in rows if r.get("stage") == f"main-seed{scale}" and "control" not in r and "menu" not in r)
        controls = {r["control"]: r["bounds"] for r in rows if r.get("stage") == f"main-seed{scale}" and "control" in r}
        runner.seed(scale, screen_width=seed["screen_width"], form_seed=seed["outer"] + seed["client"], controls=controls)
        oracle = UIPixelOracle(assets)
        trace = runner.run("syokidata0") + runner.run("font_prefix") + runner.run("visual_prefix")
        oracle.replay(trace)
        checks.extend(native_property_checks(trace, rows, f"main-title{scale}"))
        frame = runner.object_name(runner.read32(runner.storage["FrameBitmap"]))
        pixels.append(pixel_check(oracle.bitmaps[frame], output / f"title-frame{scale}.bmp"))
        for name, value in dict(sword=2, shield=3, hero_orb=1, wisdom_orb=1, flight_orb=1,
                                red_keys=2, blue_keys=3, yellow_keys=10).items():
            runner.write32(runner.storage["Hero"] + HERO_OFFSETS[name], value)
        item_trace = runner.run("itemdisp")
        oracle.replay(item_trace)
        checks.extend(native_property_checks(item_trace, rows, f"main-gameplay{scale}"))
        for control, name in (("Image19", "sword"), ("Image20", "shield"), ("Image6", "hero-orb")):
            pixels.append(pixel_check(oracle.bitmaps[control], output / f"{name}{scale}.bmp"))
        key_trace = runner.run("keydisplay")
        oracle.replay(key_trace)
        checks.extend(native_property_checks(key_trace, rows, f"main-gameplay{scale}"))
        pixels.append(pixel_check(oracle.bitmaps["Image32"], output / f"key-display{scale}.bmp"))
    for cls, method, stage in (("TAboutBox", "about_activate", "about"), ("TForm4", "holder_activate", "holder")):
        for size in range(3):
            runner.seed()
            runner.u.mem_write(runner.components["Small1"] + 0x28, bytes([size == 1]))
            runner.u.mem_write(runner.components["tiny1"] + 0x28, bytes([size == 2]))
            for row in rows:
                if row.get("stage") == f"{stage}-seed{size}" and "control" in row:
                    pointer = runner.dialog_components[cls][row["control"]]
                    for offset, value in zip((0x24, 0x28, 0x2C, 0x30), row["bounds"]):
                        runner.write32(pointer + offset, value)
            checks.extend(native_property_checks(runner.run(method), rows, f"{stage}{size}"))
    # The copied original icon payloads are verified in both linked UI targets.
    from compare_delphi_binary import resource_payloads
    icons = []
    original_resources = resource_payloads(original)
    for variant in ("ui", "native"):
        linked = resource_payloads(pefile.PE(str(ROOT / build["builds"][variant]["artifact"])))
        for identity, raw in original_resources.items():
            if identity[0] in (3, 14):
                icons.append(dict(variant=variant, type=identity[0], name=identity[1], language=identity[2],
                                  bytes=len(raw), sha256=hashlib.sha256(raw).hexdigest(),
                                  passed=linked.get(identity) == raw))
    # The instruction observer models setter requests, not the native combo
    # box's font-driven height adjustment. Keep these two visible mismatches
    # unresolved; they are not passes or authorized IME differences.
    unresolved = [c for c in checks if not c["passed"] and c["stage"] in ("holder0", "holder2")
                  and c["object"] == "DriveComboBox1" and c["property"] == "Height"
                  and c["expected"] == 20 and c["actual"] == {"holder0": 24, "holder2": 19}[c["stage"]]]
    for check in unresolved:
        check["reason"] = "Original requests Height=20, then changes Font.Size. The native combo box realizes a different height; original native control geometry has not been measured."
    supported = [c for c in checks if c not in unresolved]
    passed = all(c["passed"] for c in supported + pixels + icons)
    report = dict(property_checks=checks, bitmap_checks=pixels, icon_checks=icons,
                  supported_witness_checks_passed=passed,
                  all_requested_properties_realized_verbatim=all(c["passed"] for c in checks),
                  unresolved_native_control_realizations=unresolved,
                  pixels_compared=sum(c.get("pixels", 0) for c in pixels),
                  full_window_captures=[r for r in rows if "capture" in r],
                  skipped_captures=[r for r in rows if "capture_skipped" in r],
                  title_asset_sha256={name: digest(assets / "Data" / name) for name in ("title05.bmp", "title05R.bmp")},
                  focus_assertions=3, original_window_pixels_verified=False)
    if not passed:
        print(json.dumps([c for c in supported + pixels + icons if not c["passed"]][:8], indent=2))
        raise ValueError("Native UI witness mismatch")
    print("Native UI checked properties", len(supported), "isolated pixels", report["pixels_compared"],
          "passed; unresolved native geometry", len(unresolved), flush=True)
    return report


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--check", action="store_true")
    args = parser.parse_args()
    build = verify_build()
    original = pefile.PE(str(ROOT / "build/research/TSW.exe"))
    old = UIRunner(original, original=True)
    new = UIRunner(pefile.PE(str(WORK / "ui/UISmoke.exe")), map_path=WORK / "ui/UISmoke.map")
    production = UIRunner(pefile.PE(str(WORK / "native/Tower.exe")), map_path=WORK / "native/Tower.map", include_prefixes=False)
    candidates = {"ui": new, "native": production}
    runners, cases, transcript = (old, *candidates.values()), [], hashlib.sha256()

    def compare(name, inputs):
        expected = old.run(name)
        left = old.state()
        for variant, candidate in candidates.items():
            if name not in candidate.entries:
                if name not in PREFIX_STOPS or variant != "native":
                    raise ValueError("Missing production UI entry: " + name)
                continue
            actual, right = candidate.run(name), candidate.state()
            difference = first_difference(expected, actual)
            state_diff = [key for key in left if left[key] != right[key]]
            record = dict(method=name, variant=variant, inputs=inputs, prefix_only=name in PREFIX_STOPS,
                          passed=difference is None and not state_diff, effects=len(expected),
                          first_difference=difference, state_differences=state_diff)
            cases.append(record)
            transcript.update(json.dumps([name, variant, inputs, expected, actual, left, right], sort_keys=True).encode())
            if not record["passed"]:
                print(json.dumps(record, indent=2))
                raise ValueError("UI comparison mismatch")

    for small, tiny in itertools.product((0, 1), repeat=2):
        for runner in runners:
            runner.seed()
            runner.u.mem_write(runner.components["Small1"] + 0x28, bytes([small]))
            runner.u.mem_write(runner.components["tiny1"] + 0x28, bytes([tiny]))
        compare("about_activate", dict(small=small, tiny=tiny))
        compare("holder_activate", dict(small=small, tiny=tiny))
        for stage, method in enumerate(("about_timer", "about_timer", "about_zeno_click",
                                       "about_timer", "about_image1_click", "about_timer", "about_image2_click")):
            compare(method, dict(small=small, tiny=tiny, stage=stage))
    print("Dialog activation comparisons passed", flush=True)
    for small, large, speed in itertools.product((8, 9, 10, 12, 11), (10, 11, 12, 14, 13), (0, 1, 2, 3, 4)):
        for runner in runners:
            runner.seed()
            runner.u.mem_write(runner.storage["OriginalOptions"], bytes([small, large, 0, speed, 0, 1, 0, 0, 0, 0]))
        compare("font_prefix", dict(small=small, large=large, speed=speed))
    print("Font/menu prefixes passed", flush=True)
    for scale, cycle in itertools.product((0, 1), (0, 43)):
        for runner in runners:
            runner.seed(scale, cycle)
            runner.run("syokidata0")
        compare("visual_prefix", dict(scale=scale, cycle=cycle))
    print("Startup visual prefixes passed", flush=True)
    for scale in (0, 1):
        for runner in runners:
            runner.seed(scale)
            runner.run("syokidata0")
        for keys in itertools.product((0, 1, 7, 24, 25, -1), repeat=3):
            for runner in runners:
                for offset, value in zip((32, 36, 40), keys):
                    runner.write32(runner.storage["Hero"] + offset, value)
            compare("keydisplay", dict(scale=scale, keys=keys))
        for sword, shield, items in itertools.product(range(7), range(7), (0, 1, 2, -1)):
            for runner in runners:
                for offset, value in ((HERO_OFFSETS["sword"], sword), (HERO_OFFSETS["shield"], shield)):
                    runner.write32(runner.storage["Hero"] + offset, value)
                runner.u.mem_write(runner.storage["Hero"] + HERO_OFFSETS["hero_orb"], struct.pack("<15i", *([items] * 15)))
            compare("itemdisp", dict(scale=scale, sword=sword, shield=shield, items=items))
        # Uniform item fixtures cannot detect a read from the wrong item slot.
        for owned, value in itertools.product(range(15), (1, 2, -1)):
            items = [0] * 15
            items[owned] = value
            for runner in runners:
                runner.u.mem_write(runner.storage["Hero"] + HERO_OFFSETS["hero_orb"], struct.pack("<15i", *items))
            compare("itemdisp", dict(scale=scale, owned=owned, value=value))
        # Carried-state sequences catch frame toggles and the exact two-tick
        # special-tile counter gates. No reseeding between ticks.
        for floor, frame, frozen, count, tile, facing in itertools.product(
                (1, 15, 35), (0, 1, 2), (0, 1), (-1, 0, 1, 2), (5, 6), (0, 1, 2, 3, 4, 5)):
            for runner in runners:
                cell = {1: 116, 15: 60, 35: 71}[floor]
                for offset, value in ((16, floor), (24, cell % 11), (28, cell // 11), (48, frozen),
                                      (352, facing), (608, count), (612, count)):
                    runner.write32(runner.storage["Hero"] + offset, value)
                runner.u.mem_write(runner.storage["Maps"] + floor * 123 + cell + 2, bytes([tile]))
                runner.u.mem_write(runner.storage["AnimationFrame"], bytes([frame]))
                runner.u.mem_write(runner.storage["KeysPainted"], bytes(2))
                # A stale direction is intentional for out-of-range facing.
                runner.write32(runner.storage["ScratchIndex"], 254)
            for tick in range(3):
                compare("Timer1Timer", dict(scale=scale, floor=floor, frame=frame, frozen=frozen,
                                            count=count, tile=tile, facing=facing, tick=tick))
    print("UI body and carried-timer comparisons", len(cases), "passed", flush=True)
    native = compare_native_ui(original, build)
    report = dict(schema_version=1, original_sha256=ORIGINAL_HASH,
                  verifier_sha256=digest(Path(__file__)),
                  build_report_sha256=digest(WORK / "build-report.json"), comparisons=len(cases),
                  fixture_transcript_sha256=transcript.hexdigest(), cases=cases,
                  native_ui=native,
                  recovered_ui_comparisons_passed=True, full_game_recovered=False,
                  pixel_equivalence_established=False,
                  limits=["VCL setters, strings, focus requests, image lists and canvas calls are explicit observer boundaries; every exercised game callee executes.",
                          "About and data-holder activation bodies are complete. The font and startup-visual helpers are bounded prefixes, stopping before timer configuration and media setup respectively.",
                          "Native isolated bitmap checks use independent original-operation replay. Property/font/menu witnesses check original setter requests; font glyphs, theme rendering and full-window pixels remain unproven.",
                          "Native full-client captures are reconstruction inspection artifacts; no original running-window screenshot oracle is claimed."])
    target = ROOT / "delphi/ui-comparison-report.json"
    content = json.dumps(report, indent=2) + "\n"
    if args.check:
        if target.read_text() != content:
            raise ValueError("Stale UI comparison report")
    else:
        target.write_text(content)


if __name__ == "__main__":
    main()
