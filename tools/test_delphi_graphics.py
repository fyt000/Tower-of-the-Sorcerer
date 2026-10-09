"""Deliberate graphics/Flight corruptions must fail the comparison boundary."""
import json
import struct
import unittest

import capstone
import pefile
from PIL import Image

from verify_delphi_graphics import (ROOT, WORK, symbols, GraphicsRunner, first_difference, pixel_check, class_vmt)
from verify_delphi_flight import FlightRunner


class GraphicsIntegrityTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.original = pefile.PE(str(ROOT / "build/research/TSW.exe"))
        cls.path = WORK / "game/Tower.exe"
        cls.data = cls.path.read_bytes()
        cls.candidate = pefile.PE(data=cls.data)
        cls.mapping = symbols(cls.candidate, cls.path.with_suffix(".map"))
        cls.md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
        cls.md.detail = True

    def mutate(self, address, raw):
        data = bytearray(self.data)
        offset = self.candidate.get_offset_from_rva(address - self.candidate.OPTIONAL_HEADER.ImageBase)
        data[offset:offset + len(raw)] = raw
        return pefile.PE(data=bytes(data))

    def instructions(self, name):
        start = self.mapping[name]
        stop = next(a for a in sorted(set(self.mapping.values())) if a > start)
        return list(self.md.disasm(self.candidate.get_data(start - self.candidate.OPTIONAL_HEADER.ImageBase, stop - start), start))

    def test_layout_scalar_mutation_is_detected(self):
        ins = next(i for i in self.instructions("TTSW10.syokidata0") if i.mnemonic == "mov"
                   and i.operands[0].type == capstone.x86.X86_OP_REG and i.reg_name(i.operands[0].reg) == "edx"
                   and i.operands[1].type == capstone.x86.X86_OP_IMM and i.operands[1].imm == 400)
        mutant = self.mutate(ins.address + ins.imm_offset, struct.pack("<I", 399))
        old = GraphicsRunner(self.original, original=True)
        new = GraphicsRunner(mutant, map_path=self.path.with_suffix(".map"))
        old.seed(); new.seed()
        self.assertIsNotNone(first_difference(old.run("syokidata0"), new.run("syokidata0")))

    def test_raster_operation_mutation_is_detected(self):
        ins = next(i for i in self.instructions("ComposeSprite") if i.mnemonic == "mov"
                   and i.operands[-1].type == capstone.x86.X86_OP_IMM and i.operands[-1].imm == 0x8800C6)
        mutant = self.mutate(ins.address + ins.imm_offset, struct.pack("<I", 0xCC0020))
        old = GraphicsRunner(self.original, original=True)
        new = GraphicsRunner(mutant, map_path=self.path.with_suffix(".map"))
        for runner in (old, new):
            runner.seed(); runner.run("syokidata0")
            runner.u.mem_write(runner.storage["Maps"], (ROOT / "data/original-map-bytes.bin").read_bytes())
            for offset, value in ((16, 1), (24, 5), (28, 5), (352, 1)):
                runner.write32(runner.storage["Hero"] + offset, value)
        self.assertIsNotNone(first_difference(old.run("yusyahyouji1"), new.run("yusyahyouji1")))

    def test_bitmap_virtual_target_swap_is_rejected(self):
        vmt = class_vmt(self.candidate, "TBitmap")
        mutant = self.mutate(vmt + 0x34, struct.pack("<I", self.mapping["TBitmap.SetWidth"]))
        with self.assertRaisesRegex(ValueError, "virtual target"):
            GraphicsRunner(mutant, map_path=self.path.with_suffix(".map"))

    def test_flight_orb_gate_mutation_is_detected_from_the_opener(self):
        ins = next(i for i in self.instructions("TTSW10.img4work") if i.mnemonic == "cmp"
                   and i.operands[0].type == capstone.x86.X86_OP_MEM and i.operands[0].mem.disp == 76
                   and i.operands[-1].type == capstone.x86.X86_OP_IMM and i.operands[-1].imm == 1)
        mutant = self.mutate(ins.address + ins.imm_offset, b"\0")
        old = FlightRunner(self.original, original=True)
        new = FlightRunner(mutant, map_path=self.path.with_suffix(".map"))
        for runner in (old, new):
            runner.seed(); runner.run("syokidata0")
            for offset, value in ((24, 5), (28, 5), (76, 0)):
                runner.write32(runner.storage["Hero"] + offset, value)
            for cell in (49, 59, 61, 71):
                runner.u.mem_write(runner.storage["Maps"] + 123 + cell + 2, bytes([11 if cell == 49 else 6]))
        self.assertIsNotNone(first_difference(old.run("img4work"), new.run("img4work")))
        self.assertEqual(old.read32(old.storage["Hero"] + 48), 0)
        self.assertEqual(new.read32(new.storage["Hero"] + 48), 1)

    def test_one_pixel_difference_is_detected(self):
        path = WORK / "graphics/scale0-cycle0/hero1a.bmp"
        expected = Image.open(path).convert("RGB")
        self.assertTrue(pixel_check(expected, path)["passed"])
        expected.putpixel((0, 0), tuple(v ^ 1 for v in expected.getpixel((0, 0))))
        result = pixel_check(expected, path)
        self.assertFalse(result["passed"])
        self.assertEqual(result["differing_pixels"], 1)

    def test_focus_virtual_target_swap_is_rejected(self):
        vmt = class_vmt(self.candidate, "TButton")
        mutant = self.mutate(vmt + 0x78, struct.pack("<I", self.mapping["TWinControl.CanFocus"]))
        with self.assertRaisesRegex(ValueError, "SetFocus virtual target"):
            FlightRunner(mutant, map_path=self.path.with_suffix(".map"))


if __name__ == "__main__":
    unittest.main(verbosity=2)
