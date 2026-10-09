"""Startup corruptions must fail at the recovered handler/runtime boundary."""
import struct
import unittest

import capstone
import pefile

from verify_delphi_graphics import ROOT, WORK, symbols, class_vmt, first_difference
from verify_delphi_startup import StartupRunner


class StartupIntegrityTests(unittest.TestCase):
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

    def instructions(self):
        start = self.mapping["TTSW10.formactivate"]
        stop = next(a for a in sorted(set(self.mapping.values())) if a > start)
        return list(self.md.disasm(self.candidate.get_data(start - self.candidate.OPTIONAL_HEADER.ImageBase, stop - start), start))

    def test_fallback_name_reset_mutation_is_detected(self):
        old = StartupRunner(self.original, original=True)
        baseline = StartupRunner(self.candidate, map_path=self.path.with_suffix(".map"))
        address = baseline.storage["PlayerName"]
        ins = next(i for i in self.instructions() if i.mnemonic == "mov"
                   and i.operands[0].type == capstone.x86.X86_OP_MEM and i.operands[0].mem.disp == address
                   and i.operands[1].type == capstone.x86.X86_OP_IMM and i.operands[1].imm == 0)
        new = StartupRunner(self.mutate(ins.address + ins.imm_offset, b"\1"), map_path=self.path.with_suffix(".map"))
        for runner in (old, new):
            runner.seed_case([b"X:\\saves", b"X:\\original", b"Hero"], load_fault=True)
        self.assertIsNotNone(first_difference(old.run_prefix(), new.run_prefix()))
        self.assertNotEqual(old.state()["PlayerName"], new.state()["PlayerName"])

    def test_memo_get_virtual_target_swap_is_rejected(self):
        vmt = class_vmt(self.candidate, "TMemoStrings")
        mutant = self.mutate(vmt + 0x0C, struct.pack("<I", self.mapping["TStrings.Get"]))
        with self.assertRaisesRegex(ValueError, "Memo.Lines virtual target/body"):
            StartupRunner(mutant, map_path=self.path.with_suffix(".map"))

    def test_memo_get_external_callee_swap_is_rejected(self):
        vmt = class_vmt(self.candidate, "TMemoStrings")
        get = struct.unpack("<I", self.candidate.get_data(vmt + 0x0C - self.candidate.OPTIONAL_HEADER.ImageBase, 4))[0]
        ins = next(i for i in self.md.disasm(self.candidate.get_data(get - self.candidate.OPTIONAL_HEADER.ImageBase, 67), get)
                   if i.mnemonic == "call" and i.operands[0].imm == self.mapping["SendMessage"])
        mutant = self.mutate(ins.address + ins.imm_offset,
                             struct.pack("<i", self.mapping["SetWindowText"] - ins.address - ins.size))
        with self.assertRaisesRegex(ValueError, "Memo.Lines external callee"):
            StartupRunner(mutant, map_path=self.path.with_suffix(".map"))

    def test_catch_handler_swap_is_rejected(self):
        thunk = next(i for i in self.instructions() if i.mnemonic == "jmp"
                     and i.operands[0].type == capstone.x86.X86_OP_IMM and i.operands[0].imm == self.mapping["@HandleAnyException"])
        mutant = self.mutate(thunk.address + thunk.imm_offset,
                             struct.pack("<i", self.mapping["@HandleFinally"] - thunk.address - thunk.size))
        runner = StartupRunner(mutant, map_path=self.path.with_suffix(".map"))
        runner.seed_case([b"X:\\saves", b"X:\\original", b"Hero"], load_fault=True)
        with self.assertRaisesRegex(ValueError, "authenticated Delphi catch frame"):
            runner.run_prefix()


if __name__ == "__main__":
    unittest.main(verbosity=2)
