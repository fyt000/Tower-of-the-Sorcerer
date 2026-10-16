"""Deliberate binary mutations must break the program-entry comparison."""
import unittest

import capstone
import pefile

from recovery_evidence import ROOT
from verify_delphi2_reference import symbols
from verify_delphi_entry import EntryTrace, compare_entry

GAME = ROOT / "build/delphi-game/game/Tower.exe"


class EntryIntegrity(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.pe = pefile.PE(str(GAME))
        cls.mapping = symbols(cls.pe, GAME.with_suffix(".map"))
        cls.expected = compare_entry(GAME, GAME.with_suffix(".map"))["cases"][1]["trace"]

    def runner(self):
        return EntryTrace(self.pe, self.mapping)

    def replace_literal(self, runner, before, after):
        image = self.pe.get_memory_mapped_image()
        offset = image.find(before + b"\0")
        self.assertGreaterEqual(offset, 0)
        self.assertEqual(len(before), len(after))
        runner.u.mem_write(self.pe.OPTIONAL_HEADER.ImageBase + offset, after)

    def remove_call(self, runner, caller, callee, cleanup=0):
        start = caller
        md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
        md.detail = True
        for instruction in md.disasm(self.pe.get_data(start - self.pe.OPTIONAL_HEADER.ImageBase, 1024), start):
            if instruction.mnemonic == "call" and instruction.operands[0].imm == callee:
                self.assertEqual(instruction.size, 5)
                if cleanup:
                    # Retain stdcall argument cleanup while removing the API effect.
                    runner.u.mem_write(instruction.address, bytes((0x83, 0xC4, cleanup, 0x66, 0x90)))
                    runner.allowed.add(instruction.address + 3)
                else:
                    # A five-byte jump to the next instruction preserves boundaries.
                    runner.u.mem_write(instruction.address, b"\xe9\0\0\0\0")
                return
        self.fail("Mutation call target not found")

    def test_wrong_window_class(self):
        runner = self.runner()
        self.replace_literal(runner, b"TTSW10", b"WRONG!")
        self.assertNotEqual(self.expected, runner.run(0x701234))

    def test_wrong_warning(self):
        runner = self.runner()
        self.replace_literal(runner, b"Sorry, cannot execute plural 'Tower of the Sorcerer'.",
                             b"Wrong, cannot execute plural 'Tower of the Sorcerer'.")
        self.assertNotEqual(self.expected, runner.run(0x701234))

    def test_missing_foreground_request(self):
        runner = self.runner()
        self.remove_call(runner, self.mapping["ActivateExistingGame"], self.mapping["SetForegroundWindow"], cleanup=4)
        self.assertNotEqual(self.expected, runner.run(0x701234))

    def test_missing_entry_guard(self):
        runner = self.runner()
        self.remove_call(runner, runner.entry, self.mapping["ActivateExistingGame"])
        self.assertNotEqual(self.expected, runner.run(0x701234))


if __name__ == "__main__":
    unittest.main()
