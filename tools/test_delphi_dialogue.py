"""Mutations protecting recovered dialogue state, queue consumption and music paths."""
import struct
import unittest

import capstone
import pefile

from verify_delphi_dialogue import DialogueRunner, ROOT, WORK
from verify_delphi_graphics import symbols, data_symbols, first_difference
import delphi_routine_layout as layout


class DialogueIntegrityTests(unittest.TestCase):
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
        start = self.mapping["TTSW10." + name]
        stop = next(a for a in sorted(set(self.mapping.values())) if a > start)
        layout.DONE_EXCEPT = self.mapping["@DoneExcept"]
        layout.DISPATCHERS |= {self.mapping[n] for n in ("@HandleAnyException", "@HandleFinally")}
        return [next(self.md.disasm(raw, at)) for at, raw in layout.trace_layout(self.pe, start, stop)["records"]]

    def mutate(self, address, raw):
        data = bytearray(self.raw)
        offset = self.pe.get_offset_from_rva(address - self.pe.OPTIONAL_HEADER.ImageBase)
        data[offset:offset + len(raw)] = raw
        return pefile.PE(data=bytes(data))

    def runners(self, pe, **extras):
        old = DialogueRunner(self.original, original=True, **extras)
        new = DialogueRunner(pe, map_path=self.path.with_suffix(".map"), **extras)
        for runner in (old, new):
            runner.seed()
            runner.run("syokidata0")
        return old, new

    def test_merchant_clue_flag_cannot_be_replaced_with_trade_flag(self):
        ins = next(i for i in self.instructions("syounin") if i.mnemonic == "mov"
                   and i.operands[0].type == capstone.x86.X86_OP_MEM
                   and i.operands[0].mem.disp == self.data["MerchantClueWord"]
                   and i.operands[1].type == capstone.x86.X86_OP_IMM and i.operands[1].imm == 54)
        old, new = self.runners(self.mutate(ins.address + ins.imm_offset, struct.pack("<I", 42)))
        for runner in (old, new):
            for offset, value in ((16, 2), (168, 1), (216, 0)):
                runner.write32(runner.storage["Hero"] + offset, value)
        self.assertIsNotNone(first_difference(old.run("syounin"), new.run("syounin")))

    def test_dispatcher_pause_reset_is_observed(self):
        ins = next(i for i in self.instructions("stackwork") if i.mnemonic == "mov"
                   and i.operands[0].type == capstone.x86.X86_OP_MEM
                   and i.operands[0].mem.disp == self.data["EventPaused"])
        old, new = self.runners(self.mutate(ins.address + ins.disp_offset, struct.pack("<I", self.data["DialogueStage"])))
        for runner in (old, new):
            runner.write32(runner.storage["EventPaused"], 1)
            runner.write32(runner.storage["EventCursor"], 4)
            runner.run("stackwork")
        self.assertEqual(old.read32(old.storage["EventPaused"]), 0)
        self.assertEqual(new.read32(new.storage["EventPaused"]), 1)

    def test_queue_cursor_direction_change_is_detected(self):
        ins = [i for i in self.instructions("stackwork") if i.mnemonic == "dec"
               and i.operands[0].type == capstone.x86.X86_OP_MEM
               and i.operands[0].mem.disp == self.data["EventCursor"]][-1]
        self.assertEqual(bytes(ins.bytes[:2]), b"\xff\x0d")
        old, new = self.runners(self.mutate(ins.address + 1, b"\x05"))
        for runner in (old, new):
            runner.write32(runner.storage["EventCursor"], 4)
            runner.run("stackwork")
        self.assertEqual(old.read32(old.storage["EventCursor"]), 3)
        self.assertEqual(new.read32(new.storage["EventCursor"]), 5)

    def test_floor49_summon_does_not_execute_stale_slot_130(self):
        old, new = self.runners(self.pe, extra_game={"madoushi2": 0x462560},
                                extra_storage={"EventStack": (0x48C74C, 1200 * 6)})
        for runner in (old, new):
            runner.write32(runner.storage["Hero"] + 16, 49)
            runner.write32(runner.storage["EventCursor"], 2)
            base = runner.storage["EventStack"]
            runner.u.mem_write(base, bytes(1200 * 6))
            runner.u.mem_write(base + 2 * 6, struct.pack("<3H", 11, 3, 0))
            # A valid old command left beyond the active queue: change cell 60.
            runner.u.mem_write(base + 130 * 6, struct.pack("<3H", 17, 60, 1))
            runner.u.mem_write(runner.storage["Maps"] + 49 * 123 + 62, b"\x06")
            runner.run("stackwork")
        self.assertEqual(old.read32(old.storage["EventCursor"]), 130)
        self.assertEqual(new.read32(new.storage["EventCursor"]), 129)
        # All 128 deliberately written summon records still agree.
        self.assertEqual(bytes(old.u.mem_read(old.storage["EventStack"] + 12, 128 * 6)),
                         bytes(new.u.mem_read(new.storage["EventStack"] + 12, 128 * 6)))
        for runner in (old, new):
            runner.run("stackwork")
        self.assertEqual(bytes(old.u.mem_read(old.storage["Maps"] + 49 * 123 + 62, 1)), b"\x01")
        self.assertEqual(bytes(new.u.mem_read(new.storage["Maps"] + 49 * 123 + 62, 1)), b"\x06")

    def test_wrong_music_filename_is_detected(self):
        entry = self.mapping["TTSW10.soundplay"]
        start = self.pe.get_offset_from_rva(entry - self.pe.OPTIONAL_HEADER.ImageBase)
        stop = start + 1596
        index = self.raw.index(b"b_067xgw.mid", start, stop) + 4
        address = self.pe.get_rva_from_offset(index) + self.pe.OPTIONAL_HEADER.ImageBase
        old, new = self.runners(self.mutate(address, b"8"))
        for runner in (old, new):
            runner.write32(runner.storage["Hero"] + 360, 5)
        self.assertIsNotNone(first_difference(old.run("soundplay"), new.run("soundplay")))

    def test_old_man_gift_flag_prevents_duplicate_reward(self):
        from verify_delphi_contact import GAME
        ins = next(i for i in self.instructions("roujin") if i.mnemonic == "mov"
                   and i.operands[0].type == capstone.x86.X86_OP_MEM
                   and i.operands[0].mem.disp == self.data["Hero"] + 392
                   and i.operands[1].type == capstone.x86.X86_OP_IMM and i.operands[1].imm == 1)
        old, new = self.runners(self.mutate(ins.address + ins.imm_offset, bytes(ins.imm_size)), extra_game=GAME)
        for runner in (old, new):
            for offset, value in ((16, 2), (4, 100), (8, 100), (392, 0)):
                runner.write32(runner.storage["Hero"] + offset, value)
            runner.run("roujin")
            runner.run("roujin")
        self.assertEqual(old.read32(old.storage["Hero"] + 4), 103)
        self.assertEqual(new.read32(new.storage["Hero"] + 4), 106)

    def test_ending_commands_beyond_first_512_records_are_observed(self):
        from verify_delphi_contact import GAME, STATE
        ins = [i for i in self.instructions("handan") if i.mnemonic == "mov"
               and i.operands[0].type == capstone.x86.X86_OP_MEM and i.operands[0].size == 2
               and i.operands[0].mem.disp == 2
               and i.operands[1].type == capstone.x86.X86_OP_IMM and i.operands[1].imm == 14][-1]
        old, new = self.runners(self.mutate(ins.address + ins.imm_offset, struct.pack("<H", 15)),
                                extra_game=GAME, extra_storage=STATE)
        for runner in (old, new):
            for offset, value in ((16, 50), (636, 0), (360, 0)):
                runner.write32(runner.storage["Hero"] + offset, value)
            runner.write32(runner.storage["ContactIndex"], 49)
            runner.u.mem_write(runner.storage["Maps"] + 50 * 123 + 51, b"\x5b")
            runner.run("handan")
            self.assertGreater(runner.read32(runner.storage["EventCursor"]), 512)
        a, b = old.state()["EventStack"], new.state()["EventStack"]
        self.assertEqual(a[:512 * 12], b[:512 * 12])
        self.assertNotEqual(a, b)


if __name__ == "__main__":
    unittest.main(verbosity=2)
