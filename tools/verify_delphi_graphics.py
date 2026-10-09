"""Original/native-compiled graphics comparison with explicit VCL observers.

Game drawing and initialization bodies execute without gameplay replacements.
The observer boundary covers strings, controls, bitmaps and image lists. A
separate real-VCL hidden process and independent pixel oracle test that boundary.
This is not a full Windows presentation or startup equivalence claim.
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
import unicorn
from unicorn.x86_const import (UC_X86_REG_EAX, UC_X86_REG_EDX, UC_X86_REG_ECX,
                               UC_X86_REG_ESP, UC_X86_REG_EIP, UC_X86_REG_EFLAGS)
from PIL import Image, ImageChops

from verify_delphi2_reference import ROOT, ORIGINAL_HASH, digest, emulator, symbols, class_vmt
from build_delphi_game import WORK

GAME = dict(syokidata0=0x484F48, mhyouji=0x442C38, yusyahyouji1=0x4433A4,
            yusyahyouji=0x443648, kasanegaki=0x44439C, imagework=0x454C10)
GLOBALS = dict(Hero=(0x4B8688, 684), Maps=(0x4B8934, 6273), RenderOrder=(0x489B20, 121),
               GameOptions=(0x489B9C, 10), UiSpan=(0x48C578, 4), UiStep=(0x48C57C, 4),
               DrawX=(0x48C54C, 4), DrawY=(0x48C550, 4), DrawIndex=(0x48C570, 4),
               NeighborY=(0x48C560, 4), NeighborIndex=(0x48C55C, 4), ScratchIndex=(0x48C558, 4),
               GraphicTile=(0x48C5A8, 4), DoorOpened=(0x48C554, 4),
               DrawFlag1=(0x48C5CE, 2), DrawFlag2=(0x48C5D0, 2),
               SourceRect=(0x48C52C, 16), TargetRect=(0x48C53C, 16),
               MapBitmap1=(0x48C514, 4), MapBitmap2=(0x48C518, 4),
               WorkBitmap1=(0x48C51C, 4), WorkBitmap2=(0x48C520, 4),
               WorkBitmap3=(0x48C524, 4), FrameBitmap=(0x48C528, 4), DataDirectory=(0x48C5FC, 4))
BOUNDARIES = {
    0x423BA8: "TScreen.GetWidth", 0x410378: "TMenuItem.SetEnabled",
    0x413098: "TControl.SetLeft", 0x4130B8: "TControl.SetTop",
    0x4130D8: "TControl.SetWidth", 0x4130F8: "TControl.SetHeight",
    0x42151C: "TForm.SetClientHeight", 0x4131BC: "TControl.GetClientHeight",
    0x413178: "TControl.GetClientWidth", 0x413500: "TControl.SetVisible",
    0x4136AC: "TControl.SetShowHint", 0x419C7C: "TFont.SetColor",
    0x40352C: "@LStrAsg", 0x403658: "@LStrCat", 0x40369C: "@LStrCat3",
    0x4034DC: "@LStrClr", 0x4036FC: "@LStrCatN",
    0x402C34: "TObject.Free", 0x41D718: "TBitmap.Create", 0x41DAD8: "TBitmap.GetCanvas",
    0x41E1BC: "TBitmap.SetHeight", 0x41E21C: "TBitmap.SetWidth",
    0x41DB3C: "TBitmap.GetHeight", 0x41DB94: "TBitmap.GetWidth",
    0x41C1E8: "TPicture.LoadFromFile", 0x41BFBC: "TGraphic.LoadFromFile",
    0x4178F4: "TCustomImageList.SetWidth", 0x41793C: "TCustomImageList.SetHeight",
    0x417B00: "TCustomImageList.Add", 0x417E44: "TCustomImageList.Draw",
    0x41A530: "TCanvas.CopyRect", 0x41A5B8: "TCanvas.Draw",
}


def data_symbols(pe, path):
    span = max(s.VirtualAddress + s.Misc_VirtualSize for s in pe.sections if s.Name.rstrip(b"\0") in (b"DATA", b"BSS")) - pe.sections[1].VirtualAddress
    return {name: pe.OPTIONAL_HEADER.ImageBase + pe.sections[1].VirtualAddress + int(offset, 16)
            for offset, name in re.findall(r"^ 0002:([\dA-F]+)\s+(\S+)\s*$", path.read_text(encoding="cp1252"), re.M)
            if int(offset, 16) < span}


def walk(tree):
    yield tree
    for child in tree["children"]:
        yield from walk(child)


class GraphicsRunner:
    def __init__(self, pe, original=False, map_path=None, assets=None,
                 game=None, storage=None, boundaries=None, helpers=()):
        self.pe, self.original = pe, original
        self.game = game or GAME
        self.spec = storage or GLOBALS
        self.boundary_spec = boundaries or BOUNDARIES
        self.string_globals = {"DataDirectory"}
        self.u = emulator(pe)
        self.u.mem_map(0x600000, 0x200000)
        self.self = 0x600000
        self.bitmap_vmt, self.lines_vmt = 0x601000, 0x602000
        self.lines, self.font = 0x603000, 0x604000
        self.assets = assets or Path(r"D:\Program Files (x86)\Tower of the Sorcerer")
        manifest = json.loads((ROOT / "reference/original/presentation/ui-manifest.json").read_text())
        self.form = next(f for f in manifest["forms"] if f["class_name"] == "TTSW10")
        self.components = {f["name"]: 0x610000 + i * 0x400 for i, f in enumerate(self.form["fields"])}
        self.names = {v: k for k, v in self.components.items()} | {self.self: "form"}
        if original:
            self.entries = self.game.copy()
            self.storage = {k: a for k, (a, _) in self.spec.items()}
            self.boundaries = self.boundary_spec.copy()
            self.screen, self.main = 0x48A6FC, 0x48C510
            self.rect = 0x40923C
            self.allowed = set()
            for address in list(self.game.values()) + [self.rect]:
                path = ROOT / f"reference/original/whole-program/decompiled/{address:08x}.asm"
                self.allowed.update(int(at, 16) for at in re.findall(r"^([\da-f]{8})  ", path.read_text(), re.M))
            # Ghidra's syokidata0 export omits its normal post-finally epilogue.
            if pe.get_data(0x488849 - pe.OPTIONAL_HEADER.ImageBase, 7) != bytes.fromhex("5f5e5b8be55dc3"):
                raise ValueError("Original shared startup epilogue changed")
            self.allowed.update((0x488849, 0x48884A, 0x48884B, 0x48884C, 0x48884E, 0x48884F))
        else:
            mapping = symbols(pe, map_path)
            data = data_symbols(pe, map_path)
            self.entries = {name: mapping["TTSW10." + name] for name in self.game}
            self.storage = {name: data[name] for name in self.spec}
            self.boundaries = {mapping[name]: name for name in set(self.boundary_spec.values()) if name in mapping}
            self.screen, self.main, self.rect = data["Screen"], data.get("MainForm"), mapping["Rect"]
            self.allowed = set()
            addresses = sorted(set(mapping.values()))
            for address in list(self.entries.values()) + [mapping["ComposeSprite"], mapping["SelectGraphicFrame"], self.rect] + [mapping[name] for name in helpers]:
                stop = next(a for a in addresses if a > address)
                self.allowed.update(range(address, stop))
            # Delphi 2 emits CatN for long concatenations; explicitly modeled below.
            for name in ("@LStrCatN", "@LStrArrayClr"):
                if name in mapping:
                    self.boundaries[mapping[name]] = name
        self.entry_names = {v: k for k, v in self.entries.items()}
        bitmap_vmt = class_vmt(pe, "TBitmap")
        for offset, name in ((0x1C, "TBitmap.GetHeight"), (0x20, "TBitmap.GetWidth"),
                             (0x28, "TBitmap.SetHeight"), (0x2C, "TBitmap.SetWidth"), (0x34, "TGraphic.LoadFromFile")):
            expected = next(a for a, n in self.boundaries.items() if n == name)
            actual = struct.unpack("<I", pe.get_data(bitmap_vmt + offset - pe.OPTIONAL_HEADER.ImageBase, 4))[0]
            if actual != expected:
                raise ValueError("Unreviewed bitmap virtual target " + name)
        self.trace, self.bitmap_objects, self.canvas_objects, self.list_counts = [], {}, {}, {}
        self.next_bitmap, self.next_string = 0x700000, 0x780000
        self.screen_width = 1920
        self.border = (0, 0)
        self.u.hook_add(unicorn.UC_HOOK_CODE, self.step)
        self.u.hook_add(unicorn.UC_HOOK_MEM_WRITE, self.write)
        self.md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
        self.md.detail = True
        self.disassembly = {}

    def read32(self, at):
        return struct.unpack("<I", self.u.mem_read(at, 4))[0]

    def write32(self, at, value):
        self.u.mem_write(at, struct.pack("<I", value & 0xFFFFFFFF))

    def signed(self, value):
        return value - 0x100000000 if value >= 0x80000000 else value

    def string(self, at):
        return bytes(self.u.mem_read(at, self.read32(at - 4))) if at else b""

    def put_string(self, destination, raw):
        pointer = self.next_string + 8
        self.next_string += (len(raw) + 12 + 15) & ~15
        if self.next_string >= 0x800000:
            raise ValueError("Graphics string observer capacity")
        self.u.mem_write(pointer - 8, struct.pack("<ii", -1, len(raw)) + raw + b"\0")
        self.write32(destination, pointer)
        if destination in [self.storage[name] for name in self.string_globals]:
            name = next(name for name in self.string_globals if destination == self.storage[name])
            self.trace.append(["string", name, raw.decode("cp1252")])
        elif destination - 0x54 in self.names:
            self.trace.append(["hint", self.names[destination - 0x54], raw.decode("cp1252")])

    def ret(self, cleanup=0, value=None):
        stack = self.u.reg_read(UC_X86_REG_ESP)
        target = self.read32(stack)
        self.u.reg_write(UC_X86_REG_ESP, stack + 4 + cleanup)
        self.u.reg_write(UC_X86_REG_EIP, target)
        if value is not None:
            self.u.reg_write(UC_X86_REG_EAX, value & 0xFFFFFFFF)

    def new_bitmap(self):
        pointer = self.next_bitmap
        self.next_bitmap += 0x400
        self.write32(pointer, self.bitmap_vmt)
        self.bitmap_objects[pointer] = dict(name="bitmap" + str(len(self.bitmap_objects)), width=0, height=0)
        self.canvas_objects[pointer + 0x200] = self.bitmap_objects[pointer]
        self.write32(pointer + 0x220, 0xCC0020)
        self.trace.append(["bitmap_create", self.bitmap_objects[pointer]["name"]])
        return pointer

    def object_name(self, pointer):
        if pointer in self.names:
            return self.names[pointer]
        if pointer in self.bitmap_objects:
            return self.bitmap_objects[pointer]["name"]
        if pointer in self.canvas_objects:
            return self.canvas_objects[pointer]["name"]
        raise ValueError(f"Unknown graphics observer object {pointer:#x}")

    def write(self, u, access, at, size, value, _):
        if 0x3FD000 <= at and at + size <= 0x3FF000 or at == 0 and size == 4:
            return
        for name, address in self.storage.items():
            length = self.spec[name][1]
            if address <= at and at + size <= address + length:
                if name in self.string_globals or name == "RenderOrder":
                    raise ValueError("Unexpected direct string/constant-table write")
                self.trace.append(["write", name, at - address, size, value & ((1 << (size * 8)) - 1)])
                return
        if at - 0x20 in self.canvas_objects and size == 4:
            self.trace.append(["copy_mode", self.object_name(at - 0x20), value])
            return
        raise ValueError(f"Unexpected graphics CPU write {at:#x}/{size}")

    def step(self, u, at, size, _):
        if at in self.entry_names:
            self.trace.append(["enter", self.entry_names[at]])
        if at in self.boundaries:
            self.observe(self.boundaries[at])
            return
        if at == 0x605000:
            # Real game calls TStrings.Get virtually. The observer supplies the
            # asset root at exactly original Memo12.Lines[1].
            if self.u.reg_read(UC_X86_REG_EDX) != 1:
                raise ValueError("Unreviewed startup Memo12 index")
            self.put_string(self.u.reg_read(UC_X86_REG_ECX), b"X:\\original")
            self.ret()
            return
        if at not in self.allowed:
            raise ValueError(f"Unmodeled graphics/runtime entry {at:#x}")
        ins = self.disassembly.get(at)
        if ins is None:
            ins = next(self.md.disasm(bytes(u.mem_read(at, size)), at))
            self.disassembly[at] = ins
        # Reject unexpected indirect/direct calls even when their targets happen
        # to lie in a neighboring allowed span.
        if ins.mnemonic == "call" and ins.operands[0].type == capstone.x86.X86_OP_IMM:
            target = ins.operands[0].imm
            if target not in self.allowed and target not in self.boundaries:
                raise ValueError(f"Unmodeled graphics call {at:#x} -> {target:#x}")

    def observe(self, name):
        a, d, c, sp = (self.u.reg_read(r) for r in (UC_X86_REG_EAX, UC_X86_REG_EDX, UC_X86_REG_ECX, UC_X86_REG_ESP))
        if name.startswith("@LStr"):
            if name == "@LStrAsg":
                self.put_string(a, self.string(d))
            elif name == "@LStrCat":
                self.put_string(a, self.string(self.read32(a)) + self.string(d))
            elif name == "@LStrCat3":
                self.put_string(a, self.string(d) + self.string(c))
            elif name == "@LStrCatN":
                self.put_string(a, b"".join(self.string(self.read32(sp + 4 + i * 4)) for i in reversed(range(d))))
                self.ret(d * 4)
                return
            elif name == "@LStrClr":
                self.write32(a, 0)
            elif name == "@LStrArrayClr":
                if not (0x3FD000 <= a and a + d * 4 <= 0x3FF000):
                    raise ValueError("String-array cleanup outside local stack")
                for i in range(d):
                    self.write32(a + i * 4, 0)
            else:
                raise ValueError("Unsupported string observer " + name)
        elif name == "TScreen.GetWidth":
            self.ret(value=self.screen_width)
            return
        elif name in ("TControl.GetClientWidth", "TControl.GetClientHeight"):
            i = 0 if name.endswith("Width") else 1
            self.ret(value=self.read32(a + (0x2C if i == 0 else 0x30)) - self.border[i])
            return
        elif name == "TForm.SetClientHeight":
            self.trace.append(["property", "form", "ClientHeight", self.signed(d)])
            self.write32(a + 0x30, d + self.border[1])
        elif name in ("TMenuItem.SetEnabled", "TControl.SetShowHint", "TControl.SetVisible"):
            self.trace.append(["property", self.object_name(a), name.split("Set")[1], d & 255])
        elif name.startswith("TControl.Set"):
            prop = name.split("Set")[1]
            self.trace.append(["property", self.object_name(a), prop, self.signed(d)])
            offset = {"Left": 0x24, "Top": 0x28, "Width": 0x2C, "Height": 0x30}[prop]
            self.write32(a + offset, d)
        elif name == "TFont.SetColor":
            self.trace.append(["font_color", "Memo11", d])
        elif name == "TBitmap.Create":
            self.ret(value=self.new_bitmap())
            return
        elif name == "TObject.Free":
            self.trace.append(["bitmap_free", self.object_name(a)])
        elif name == "TBitmap.GetCanvas":
            self.ret(value=a + 0x200)
            return
        elif name.startswith("TBitmap.Get"):
            self.ret(value=self.bitmap_objects[a][name.split("Get")[1].lower()])
            return
        elif name.startswith("TBitmap.Set"):
            prop = name.split("Set")[1].lower()
            self.bitmap_objects[a][prop] = self.signed(d)
            self.trace.append(["bitmap_size", self.object_name(a), prop, self.signed(d)])
        elif name in ("TPicture.LoadFromFile", "TGraphic.LoadFromFile"):
            path = self.string(d).decode("cp1252")
            if not path.startswith("X:\\original\\"):
                raise ValueError("Unreviewed asset lookup " + path)
            relative = path[len("X:\\original\\"):].lower()
            actual = self.assets.joinpath(*relative.split("\\"))
            with Image.open(actual) as image:
                width, height = image.size
            if name == "TPicture.LoadFromFile":
                owner = self.object_name(a - 0x180)
            else:
                owner = self.object_name(a)
                self.bitmap_objects[a].update(width=width, height=height)
            self.trace.append(["load", owner, relative, width, height])
        elif name.startswith("TCustomImageList.Set"):
            prop = name.split("Set")[1]
            self.trace.append(["list_size", self.object_name(a), prop, self.signed(d)])
        elif name == "TCustomImageList.Add":
            self.trace.append(["list_add", self.object_name(a), self.object_name(d), c])
            count = self.list_counts.get(a, 0)
            self.list_counts[a] = count + 1
            self.ret(value=count)
            return
        elif name == "TCustomImageList.Draw":
            self.trace.append(["list_draw", self.object_name(a), self.object_name(d), self.signed(c),
                               self.signed(self.read32(sp + 4)), self.signed(self.read32(sp + 8))])
            self.ret(8)
            return
        elif name == "TCanvas.CopyRect":
            dest = list(struct.unpack("<4i", self.u.mem_read(d, 16)))
            source = list(struct.unpack("<4i", self.u.mem_read(self.read32(sp + 4), 16)))
            self.trace.append(["copy_rect", self.object_name(a), dest, self.object_name(c), source])
            self.ret(4)
            return
        elif name == "TCanvas.Draw":
            self.trace.append(["draw", self.object_name(a), self.signed(d), self.signed(c), self.object_name(self.read32(sp + 4))])
            self.ret(4)
            return
        else:
            raise ValueError("Unknown graphics observer " + name)
        self.ret()

    def seed(self, scale=0, cycle=0, screen_width=1920, form_seed=(640, 426, 640, 426), controls=None):
        self.trace.clear()
        self.bitmap_objects.clear()
        self.canvas_objects.clear()
        self.list_counts.clear()
        self.next_bitmap, self.next_string = 0x700000, 0x780000
        self.screen_width = screen_width
        self.border = (form_seed[0] - form_seed[2], form_seed[1] - form_seed[3])
        for name, address in self.storage.items():
            self.u.mem_write(address, bytes(self.spec[name][1]))
        self.u.mem_write(self.storage["GameOptions"], bytes([10, 12, 0, 1, 0, 1, 0, 0, scale, 0]))
        self.u.mem_write(self.storage["RenderOrder"], self.pe.get_data(0x489B20 - self.pe.OPTIONAL_HEADER.ImageBase, 121) if self.original
                         else pefile.PE(str(ROOT / "build/research/TSW.exe")).get_data(0x489B20 - 0x400000, 121))
        self.write32(self.storage["Hero"] + 636, cycle)
        self.u.mem_write(self.self, bytes(0x500))
        if self.main is not None:
            self.write32(self.main, self.self)
        self.write32(self.screen, 0x606000)
        self.write32(self.lines, self.lines_vmt)
        self.write32(self.lines_vmt + 0x0C, 0x605000)
        # Same VMT slot layout for the English/Japanese bitmap classes.
        for offset, name in ((0x1C, "TBitmap.GetHeight"), (0x20, "TBitmap.GetWidth"),
                             (0x28, "TBitmap.SetHeight"), (0x2C, "TBitmap.SetWidth"), (0x34, "TGraphic.LoadFromFile")):
            self.write32(self.bitmap_vmt + offset, next(a for a, n in self.boundaries.items() if n == name))
        for node in walk(self.form["tree"]):
            if node["name"] not in self.components:
                continue
            at = self.components[node["name"]]
            self.u.mem_write(at, bytes(0x400))
            for prop, offset in (("Left", 0x24), ("Top", 0x28), ("Width", 0x2C), ("Height", 0x30)):
                self.write32(at + offset, node["properties"].get(prop, {}).get("value", 0))
            self.write32(at + 0xAC, at + 0x180)  # TImage.Picture
            self.write32(at + 0x44, self.font)
        for field in self.form["fields"]:
            self.write32(self.self + int(field["offset"], 16) - (0 if self.original else 4), self.components[field["name"]])
        if controls:
            for name, bounds in controls.items():
                for offset, value in zip((0x24, 0x28, 0x2C, 0x30), bounds):
                    self.write32(self.components[name] + offset, value)
        self.write32(self.components["Memo12"] + (0x118 if self.original else 0x114), self.lines)
        for offset, value in ((0x2C, form_seed[0]), (0x30, form_seed[1])):
            self.write32(self.self + offset, value)

    def run(self, name):
        start = len(self.trace)
        stack, stop = 0x3FE000, 0x3FF000
        self.u.mem_write(0x3FD000, bytes(0x2000))
        self.write32(stack, stop)
        self.u.reg_write(UC_X86_REG_ESP, stack)
        self.u.reg_write(UC_X86_REG_EAX, self.self)
        self.u.reg_write(UC_X86_REG_EDX, 0)
        self.u.reg_write(UC_X86_REG_ECX, 0)
        self.u.reg_write(UC_X86_REG_EFLAGS, 2)
        self.u.emu_start(self.entries[name], stop, count=500000)
        if self.u.reg_read(UC_X86_REG_EIP) != stop or self.u.reg_read(UC_X86_REG_ESP) != stack + 4:
            raise ValueError("Graphics routine did not return normally")
        if self.read32(0) != 0:
            raise ValueError("Graphics exception frame was not restored")
        return self.trace[start:]

    def state(self):
        result = {name: bytes(self.u.mem_read(address, self.spec[name][1])).hex()
                  for name, address in self.storage.items() if name not in self.string_globals}
        for name in self.string_globals:
            result[name] = self.string(self.read32(self.storage[name])).hex()
        return result


def first_difference(left, right):
    return next((dict(index=i, original=a, candidate=b) for i, (a, b) in
                 enumerate(itertools.zip_longest(left, right)) if a != b), None)


class PixelOracle:
    """Replay observed original drawing requests on RGB arrays, without Delphi.

    Fixtures use valid original sprite indices and unscaled, fully covered
    destinations. Image-list unused tail cells and uninitialized bitmap pixels
    are excluded from pixel claims.
    """
    def __init__(self, assets):
        self.assets = assets
        self.bitmaps, self.sizes, self.modes, self.lists, self.frames = {}, {}, {}, {}, {}

    def blit(self, destination, source, x, y, mode=0xCC0020):
        import numpy as np
        box = (x, y, x + source.width, y + source.height)
        if mode == 0xCC0020:
            result = source
        else:
            a = np.asarray(self.bitmaps[destination].crop(box), dtype=np.uint8)
            b = np.asarray(source, dtype=np.uint8)
            if mode == 0xEE0086:
                out = a | b
            elif mode == 0x330008:
                out = ~b
            elif mode == 0x8800C6:
                out = a & b
            else:
                raise ValueError(f"Unreviewed original raster operation {mode:#x}")
            result = Image.fromarray(out)
        self.bitmaps[destination].paste(result, (x, y))

    def replay(self, trace):
        for event in trace:
            kind = event[0]
            if kind == "bitmap_create":
                self.bitmaps[event[1]] = Image.new("RGB", (0, 0))
                self.sizes[event[1]] = [0, 0]
                self.modes[event[1]] = 0xCC0020
            elif kind == "bitmap_size":
                name, prop, value = event[1:]
                size = self.sizes[name]
                size[0 if prop == "width" else 1] = value
                image = Image.new("RGB", tuple(size), "white")
                image.paste(self.bitmaps[name], (0, 0))
                self.bitmaps[name] = image
            elif kind == "load":
                owner, relative = event[1:3]
                with Image.open(self.assets.joinpath(*relative.split("\\"))) as loaded:
                    image = loaded.convert("RGB")
                if owner.startswith("bitmap"):
                    self.bitmaps[owner] = image
                    self.sizes[owner] = list(image.size)
                else:
                    self.frames[owner] = image
            elif kind == "copy_mode":
                self.modes[event[1]] = event[2]
            elif kind == "copy_rect":
                name, box, source, source_box = event[1:]
                cropped = self.bitmaps[source].crop(tuple(source_box))
                if cropped.size != (box[2] - box[0], box[3] - box[1]):
                    raise ValueError("Pixel fixture unexpectedly requires rescaling")
                self.blit(name, cropped, box[0], box[1], self.modes[name])
            elif kind == "list_add":
                name, bitmap, mask = event[1:]
                if mask != 0:
                    raise ValueError("Pixel fixture unexpectedly has an image-list mask")
                self.lists.setdefault(name, []).append(self.bitmaps[bitmap].copy())
            elif kind == "list_draw":
                name, bitmap, x, index, y = event[1:]
                if not 0 <= index < len(self.lists[name]):
                    raise ValueError("Pixel fixture has an out-of-range sprite")
                self.blit(bitmap, self.lists[name][index], x, y)
            elif kind == "draw":
                bitmap, x, y, source = event[1:]
                if bitmap not in self.bitmaps:
                    if bitmap != "Image31" or (x, y) != (0, 0):
                        raise ValueError("Unreviewed control canvas in pixel fixture")
                    self.bitmaps[bitmap] = Image.new("RGB", self.bitmaps[source].size)
                    self.modes[bitmap] = 0xCC0020
                self.blit(bitmap, self.bitmaps[source], x, y, self.modes[bitmap])
            elif kind == "picture_bitmap":
                self.bitmaps[event[1]] = self.bitmaps[event[2]].copy()
                self.frames[event[1]] = self.bitmaps[event[1]]


def pixel_check(expected, path, region=None):
    with Image.open(path) as loaded:
        actual = loaded.convert("RGB")
    if expected.size != actual.size:
        return dict(file=path.name, passed=False, expected_size=expected.size, actual_size=actual.size)
    if region:
        expected, actual = expected.crop(region), actual.crop(region)
    difference = ImageChops.difference(expected, actual)
    return dict(file=path.name, region=region, pixels=expected.width * expected.height,
                expected_rgb_sha256=hashlib.sha256(expected.tobytes()).hexdigest(),
                actual_rgb_sha256=hashlib.sha256(actual.tobytes()).hexdigest(),
                differing_pixels=sum(any(p) for p in difference.get_flattened_data()),
                passed=difference.getbbox() is None)


def compare_native_pixels(original, build, assets):
    from verify_delphi_flight import FlightRunner
    reports = []
    for case in build["builds"]["graphics"].get("native_cases", []):
        output = ROOT / case["output"]
        if case["native_exit"] != 0 or digest(output / "native.log") != case["native_log_sha256"]:
            raise ValueError("Invalid retained native graphics log")
        if (output / "native.log").read_bytes().decode("cp1252") != case["native_output"]:
            raise ValueError("Native graphics output differs from its log")
        for name, sha256 in case["bitmaps"].items():
            if digest(output / name) != sha256:
                raise ValueError("Native graphics bitmap changed: " + name)
        rows = [json.loads(line) for line in case["native_output"].splitlines() if line.startswith("{")]
        seed = next(r for r in rows if "seed_form" in r)
        summary = next(r for r in rows if "graphics_startup" in r)
        if summary["counts"] != [218, 159, 4] or not rows[-1].get("graphics_smoke_passed") or not any(r.get("referenced_vcl_fields_verified") for r in rows):
            raise ValueError("Incomplete native graphics smoke")
        runner = FlightRunner(original, original=True, assets=assets)
        control_seeds = {r["control_seed"]: r["bounds"] for r in rows if "control_seed" in r}
        if len(control_seeds) != len([r for r in rows if "control" in r]) or not control_seeds:
            raise ValueError("Native control seeds incomplete")
        runner.seed(case["scale"], case["cycle"], seed["screen_width"], seed["seed_form"], control_seeds)
        oracle = PixelOracle(assets)
        oracle.replay(runner.run("syokidata0"))
        bounds_checks = []
        for row in rows:
            if "control" in row:
                pointer = runner.components[row["control"]]
                expected = [runner.signed(runner.read32(pointer + offset)) for offset in (0x24, 0x28, 0x2C, 0x30)]
                bounds_checks.append(dict(control=row["control"], expected=expected, actual=row["bounds"],
                                          passed=expected == row["bounds"]))
        checks = []
        # All populated atlas cells; deliberately exclude the original unused
        # two/six-cell tails, which are not initialized by this routine.
        for name, count, filename in (("ImageList1", 218, "atlas1.bmp"), ("ImageList3", 159, "atlas3.bmp")):
            sprites = oracle.lists[name]
            tw, th = sprites[0].size
            with Image.open(output / filename) as loaded:
                actual = loaded.convert("RGB")
            for i in range(count):
                image = actual.crop(((i % 11) * tw, (i // 11) * th, (i % 11 + 1) * tw, (i // 11 + 1) * th))
                expected = sprites[i]
                checks.append(dict(file=filename, sprite=i, pixels=tw * th,
                                   passed=image.tobytes() == expected.tobytes()))
        keys = Image.new("RGB", (summary["tile_width"], summary["tile_height"]))
        for i, sprite in enumerate(oracle.lists["ImageList2"]):
            keys.paste(sprite, ((i % 2) * sprite.width, (i // 2) * sprite.height))
        checks.append(pixel_check(keys, output / "keys.bmp"))
        for name, filename in (("Image1", "center.bmp"), ("Image2", "left.bmp"), ("Image3", "right.bmp")):
            checks.append(pixel_check(oracle.frames[name], output / filename))
        runner.u.mem_write(runner.storage["Maps"], (ROOT / "data/original-map-bytes.bin").read_bytes())
        runner.write32(runner.storage["Hero"] + 636, 0)
        for floor in (1, 49):
            runner.write32(runner.storage["Hero"] + 16, floor)
            oracle.replay(runner.run("mhyouji"))
            for key, suffix in (("MapBitmap1", "a"), ("MapBitmap2", "b")):
                checks.append(pixel_check(oracle.bitmaps[runner.object_name(runner.read32(runner.storage[key]))],
                                          output / f"floor{floor}{suffix}.bmp"))
        runner.write32(runner.storage["Hero"] + 16, 1)
        runner.write32(runner.storage["Hero"] + 24, 6)
        runner.write32(runner.storage["Hero"] + 28, 10)
        for facing in range(1, 5):
            runner.write32(runner.storage["Hero"] + 352, facing)
            oracle.replay(runner.run("mhyouji"))
            oracle.replay(runner.run("yusyahyouji1"))
            for key, suffix in (("MapBitmap1", "a"), ("MapBitmap2", "b")):
                checks.append(pixel_check(oracle.bitmaps[runner.object_name(runner.read32(runner.storage[key]))],
                                          output / f"hero{facing}{suffix}.bmp"))
        runner.write32(runner.storage["Hero"] + 636, case["cycle"])
        monsters = [r for r in rows if "monster" in r]
        if [r["monster"] for r in monsters] != list(range(-1, 33)):
            raise ValueError("Incomplete native monster display cases")
        for native in monsters:
            row = native["monster"]
            runner.write32(runner.storage["MonsterIndex"], row)
            trace = runner.run("monshyouji")
            oracle.replay(trace)
            checks.append(pixel_check(oracle.bitmaps["Image31"], output / f"monster{row}.bmp"))
            wanted = [runner.texts[name] for name in ("Memo8", "Memo5", "Memo6", "Memo7")]
            checks.append(dict(file=f"monster{row}.labels", pixels=0, expected=wanted, actual=native["labels"],
                               passed=wanted == native["labels"] and native["visible"] == (row >= 0)))
        reports.append(dict(scale=case["scale"], cycle=case["cycle"], checks=checks, control_bounds=bounds_checks,
                            passed=all(c["passed"] for c in checks + bounds_checks)))
    if len(reports) != 4:
        raise ValueError("Four native graphics configurations required")
    return reports


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--assets", type=Path, default=Path(r"D:\Program Files (x86)\Tower of the Sorcerer"))
    parser.add_argument("--check", action="store_true")
    args = parser.parse_args()
    original_path = ROOT / "build/research/TSW.exe"
    if digest(original_path) != ORIGINAL_HASH:
        raise ValueError("Original executable pin changed")
    original = pefile.PE(str(original_path))
    path = WORK / "game/Tower.exe"
    build = json.loads((WORK / "build-report.json").read_text())
    for record in build["inputs"]:
        source = ROOT / record["source"]
        staged = WORK / source.relative_to(ROOT / "delphi")
        if digest(source) != record["source_sha256"] or digest(staged) != record["staged_sha256"]:
            raise ValueError("Stale native graphics source: " + record["source"])
    for record in build["builds"].values():
        artifact = ROOT / record["artifact"]
        if digest(artifact) != record["artifact_sha256"] or digest(artifact.with_suffix(".map")) != record["map_sha256"]:
            raise ValueError("Native graphics artifact changed")
    for record in build["graphics_assets"]:
        if digest(Path(record["path"])) != record["sha256"]:
            raise ValueError("Native graphics input asset changed")
    old = GraphicsRunner(original, original=True, assets=args.assets)
    runners = {name: GraphicsRunner(pefile.PE(str(ROOT / build["builds"][name]["artifact"])),
                        map_path=(ROOT / build["builds"][name]["artifact"]).with_suffix(".map"), assets=args.assets)
               for name in ("game", "graphics")}
    cases = []
    transcript = hashlib.sha256()
    def compare(method, inputs):
        expected = old.run(method)
        old_state = old.state()
        for variant, runner in runners.items():
            actual = runner.run(method)
            new_state = runner.state()
            difference = first_difference(expected, actual)
            state_differences = [name for name in old_state if old_state[name] != new_state[name]]
            cases.append(dict(method=method, inputs=inputs, variant=variant, passed=difference is None and not state_differences,
                              original_effects=len(expected), candidate_effects=len(actual),
                              first_difference=difference, state_differences=state_differences))
            transcript.update(json.dumps([method, inputs, variant, expected, actual, old_state, new_state], sort_keys=True).encode())
            if not cases[-1]["passed"]:
                print(json.dumps(cases[-1], indent=2))
                raise ValueError("Compiled graphics mismatch")
    for scale, cycle, width in itertools.product((0, 1), (0, 43), (639, 640, 641, 799, 800, 801, 1920)):
        old.seed(scale, cycle, width)
        for runner in runners.values():
            runner.seed(scale, cycle, width)
        compare("syokidata0", dict(scale=scale, cycle=cycle, screen_width=width))
    print("Graphics startup comparisons passed", flush=True)
    for scale in (0, 1):
        for runner in [old, *runners.values()]:
            runner.seed(scale)
            runner.run("syokidata0")
            runner.u.mem_write(runner.storage["Maps"], (ROOT / "data/original-map-bytes.bin").read_bytes())
        for floor, gate in itertools.product(range(51), (0, 1)):
            for runner in [old, *runners.values()]:
                runner.write32(runner.storage["Hero"] + 16, floor)
                runner.write32(runner.storage["Hero"] + 464, gate)
                runner.write32(runner.storage["Hero"] + 664, 77)
            compare("mhyouji", dict(scale=scale, floor=floor, time_gate=gate))
        # Every byte tile value, including out-of-range image-list indices.
        for tile in range(256):
            for runner in [old, *runners.values()]:
                runner.write32(runner.storage["Hero"] + 16, 1)
                runner.u.mem_write(runner.storage["Maps"] + 123 + 62, bytes([tile]))
            compare("mhyouji", dict(scale=scale, floor=1, injected_tile=tile))
        for runner in [old, *runners.values()]:
            runner.u.mem_write(runner.storage["Maps"], (ROOT / "data/original-map-bytes.bin").read_bytes())
        for floor, facing, position in itertools.product((1, 25, 49), range(6), ((0, 0), (10, 0), (0, 10), (10, 10), (5, 5))):
            for runner in [old, *runners.values()]:
                for offset, value in ((16, floor), (24, position[0]), (28, position[1]), (352, facing)):
                    runner.write32(runner.storage["Hero"] + offset, value)
            compare("yusyahyouji1", dict(scale=scale, floor=floor, facing=facing, x=position[0], y=position[1]))
    print("Graphics state/drawing comparisons", len(cases), "passed", flush=True)
    native_pixels = compare_native_pixels(original, build, args.assets)
    passed = all(r["passed"] for r in native_pixels)
    report = dict(schema_version=1, original_sha256=ORIGINAL_HASH,
                  build_report_sha256=digest(WORK / "build-report.json"),
                  comparisons=len(cases), cases=cases, fixture_transcript_sha256=transcript.hexdigest(),
                  native_configurations=native_pixels, native_pixels_compared=sum(c["pixels"] for r in native_pixels for c in r["checks"]),
                  measured_graphics_passed=passed, full_game_recovered=False, pixel_equivalence_established=False,
                  limits=["All six recovered graphics game bodies execute. Controls, strings, bitmap and image-list operations use explicit observer models during instruction comparisons.",
                          "Actual original/native bitmap VMT targets are authenticated. Every other runtime entry is rejected; no game callback is skipped.",
                          "The original normal startup post-finally epilogue is byte-authenticated because its Ghidra export omitted it.",
                          "Native hidden Delphi/Windows execution covers two display sizes and two cycle frame sets. Pixel results compare against an independent replay of original drawing requests.",
                          "Pixels cover populated atlas cells, frame bitmaps, floors 1 and 49 in both animation frames and all four hero facings. Unwritten atlas tails and uninitialized pixels are excluded.",
                          "Native control bounds use recorded initial streamed-control bounds; differences produced by unrelated component constructors are not classified by these game-body tests.",
                          "Main formactivate and other startup, input, story, timer and I/O paths remain unrecovered; these measurements do not establish full-window pixels or complete-game equivalence."])
    target = ROOT / "build/delphi-game/reports/graphics-comparison-report.json"
    content = json.dumps(report, indent=2) + "\n"
    if args.check:
        if target.read_text(encoding="utf-8") != content:
            raise ValueError("Stale graphics comparison report")
    else:
        target.parent.mkdir(parents=True, exist_ok=True)
        target.write_text(content, encoding="utf-8")
    print("Native graphics pixels", report["native_pixels_compared"], "passed", passed, flush=True)
    if not passed:
        print(json.dumps([c for r in native_pixels for c in r["checks"] + r["control_bounds"] if not c["passed"]][:5], indent=2))
        raise SystemExit("Native pixel/bounds mismatch")


if __name__ == "__main__":
    main()
