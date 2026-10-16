"""Mutations protecting UI interactions and the unmasked resource audit."""
import struct
import unittest

import capstone
import pefile

from verify_delphi_ui import ROOT, WORK, UIRunner, HERO_OFFSETS
from verify_delphi_graphics import symbols, data_symbols, first_difference
from compare_delphi_binary import compare_resources, compare_sections
import delphi_routine_layout as layout


class UIIntegrityTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.original = pefile.PE(str(ROOT / "build/research/TSW.exe"))
        cls.path = WORK / "game/Tower.exe"
        cls.raw = cls.path.read_bytes()
        cls.pe = pefile.PE(data=cls.raw)
        cls.mapping = symbols(cls.pe, cls.path.with_suffix(".map"))
        cls.data = data_symbols(cls.pe, cls.path.with_suffix(".map"))
        cls.md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
        cls.md.detail = True

    def instructions(self, name):
        start = self.mapping[name]
        stop = next(a for a in sorted(set(self.mapping.values())) if a > start)
        layout.DONE_EXCEPT = self.mapping["@DoneExcept"]
        layout.DISPATCHERS |= {self.mapping[n] for n in ("@HandleAnyException", "@HandleFinally")}
        return [next(self.md.disasm(raw, at)) for at, raw in layout.trace_layout(self.pe, start, stop)["records"]]

    def mutate(self, address, raw):
        data = bytearray(self.raw)
        offset = self.pe.get_offset_from_rva(address - self.pe.OPTIONAL_HEADER.ImageBase)
        data[offset:offset + len(raw)] = raw
        return pefile.PE(data=bytes(data))

    def runners(self, pe, graphics=False):
        old = UIRunner(self.original, original=True)
        new = UIRunner(pe, map_path=self.path.with_suffix(".map"), include_prefixes=False)
        for runner in (old, new):
            runner.seed()
            if graphics:
                runner.run("syokidata0")
        return old, new

    def test_about_font_change_is_detected(self):
        ins = next(i for i in self.instructions("TAboutBox.formactivate") if i.mnemonic == "mov"
                   and i.op_str == "edx, 0xe")
        old, new = self.runners(self.mutate(ins.address + ins.imm_offset, struct.pack("<I", 15)))
        self.assertIsNotNone(first_difference(old.run("about_activate"), new.run("about_activate")))

    def test_blue_key_sprite_change_is_detected(self):
        ins = next(i for i in self.instructions("TTSW10.keydisplay") if i.mnemonic == "mov"
                   and i.operands[0].type == capstone.x86.X86_OP_MEM
                   and i.operands[0].mem.disp == self.data["DamageMode"]
                   and i.operands[1].type == capstone.x86.X86_OP_IMM and i.operands[1].imm == 1)
        old, new = self.runners(self.mutate(ins.address + ins.imm_offset, struct.pack("<I", 2)), True)
        for runner in (old, new):
            runner.write32(runner.storage["Hero"] + HERO_OFFSETS["blue_keys"], 1)
        self.assertIsNotNone(first_difference(old.run("keydisplay"), new.run("keydisplay")))

    def test_item_presence_gate_change_is_detected(self):
        instructions = self.instructions("TTSW10.itemdisp")
        index = next(i for i, ins in enumerate(instructions) if ins.mnemonic == "cmp"
                     and ins.operands[0].type == capstone.x86.X86_OP_MEM
                     and ins.operands[0].mem.disp == self.data["Hero"] + HERO_OFFSETS["hero_orb"]
                     and ins.operands[1].imm == 0)
        branch = instructions[index + 1]
        self.assertEqual(branch.bytes[0], 0x0F)
        self.assertEqual(branch.bytes[1], 0x84)
        old, new = self.runners(self.mutate(branch.address + 1, b"\x85"), True)
        for runner in (old, new):
            runner.write32(runner.storage["Hero"] + HERO_OFFSETS["hero_orb"], 2)
        self.assertIsNotNone(first_difference(old.run("itemdisp"), new.run("itemdisp")))

    def test_timer_two_tick_gate_change_is_detected(self):
        ins = next(i for i in self.instructions("TTSW10.Timer1Timer") if i.mnemonic == "cmp"
                   and i.operands[0].type == capstone.x86.X86_OP_MEM
                   and i.operands[0].mem.disp == self.data["Hero"] + HERO_OFFSETS["Word608"]
                   and i.operands[1].imm == 1)
        old, new = self.runners(self.mutate(ins.address + ins.imm_offset, b"\x02"), True)
        for runner in (old, new):
            for name, value in dict(floor=15, x=5, y=5, Word48=0, Word608=2, facing=1).items():
                runner.write32(runner.storage["Hero"] + HERO_OFFSETS[name], value)
            runner.u.mem_write(runner.storage["Maps"] + 15 * 123 + 62, b"\x06")
            runner.u.mem_write(runner.storage["AnimationFrame"], b"\x01")
        self.assertIsNotNone(first_difference(old.run("Timer1Timer"), new.run("Timer1Timer")))

    def test_unknown_game_callee_is_rejected(self):
        call = next(i for i in self.instructions("TTSW10.keydisplay") if i.mnemonic == "call"
                    and i.operands[0].imm == self.mapping["TCustomImageList.Draw"])
        changed = struct.pack("<i", self.mapping["TTSW10.optionl1"] - call.address - call.size)
        _, new = self.runners(self.mutate(call.address + call.imm_offset, changed), True)
        new.write32(new.storage["Hero"] + HERO_OFFSETS["red_keys"], 1)
        with self.assertRaisesRegex(ValueError, "Unmodeled graphics call"):
            new.run("keydisplay")

    def test_raw_audit_detects_one_form_payload_byte(self):
        resource = next(lang.data.struct for kind in self.pe.DIRECTORY_ENTRY_RESOURCE.entries if kind.id == 10
                        for name in kind.directory.entries if str(name.name) == "TABOUTBOX"
                        for lang in name.directory.entries)
        address = self.pe.OPTIONAL_HEADER.ImageBase + resource.OffsetToData + 20
        byte = self.pe.get_data(resource.OffsetToData + 20, 1)[0]
        mutated = self.mutate(address, bytes([byte ^ 1]))
        row = next(r for r in compare_resources(self.pe, mutated) if r["name"] == "TABOUTBOX")
        self.assertFalse(row["exact_bytes_equal"])
        self.assertEqual(row["different_at_same_offset"], 1)
        section = next(s for s in compare_sections(self.pe, mutated) if s["section"] == ".rsrc")
        self.assertEqual(section["different_at_same_offset"], 1)


if __name__ == "__main__":
    unittest.main(verbosity=2)
