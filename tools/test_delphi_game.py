"""Mutation tests for the new Delphi project's comparison and IME exception."""
import json
import struct
import unittest

import capstone
import pefile

from verify_delphi2_reference import ROOT, symbols
from verify_delphi_game import (WORK, ENTRIES, STORAGE, Runner, exports, locations,
                               baseline, setscalar, accepted_button_comparison,
                               compare_native_gates, verify_form_resources)
from reconstruct_delphi_project import generated


class DelphiGameTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.original = pefile.PE(str(ROOT / "build/research/TSW.exe"))
        cls.path = WORK / "game/Tower.exe"
        cls.candidate = pefile.PE(str(cls.path))
        cls.mapping = symbols(cls.candidate, cls.path.with_suffix(".map"))
        cls.policy = json.loads((ROOT / "delphi/comparison-policy.json").read_text())
        cls.build = json.loads((WORK / "build-report.json").read_text())
        cls.core_path = WORK / "core-probe/CoreProbe.dll"
        cls.core = pefile.PE(str(cls.core_path))
        cls.entries = exports(cls.core)
        cls.storage = locations(cls.core, cls.entries)

    def mutate_native(self, offset, raw):
        data = bytearray(self.path.read_bytes())
        data[offset:offset + len(raw)] = raw
        return pefile.PE(data=bytes(data))

    def test_only_documented_ime_operands_are_accepted(self):
        self.assertTrue(accepted_button_comparison(self.original, self.candidate, self.mapping, self.policy)["passed"])

    def test_another_field_offset_is_rejected(self):
        address = self.mapping["TButton.CMDialogKey"]
        offset = self.candidate.get_offset_from_rva(address - self.candidate.OPTIONAL_HEADER.ImageBase)
        mutant = self.mutate_native(offset + 15, struct.pack("<I", 0x103))
        with self.assertRaisesRegex(ValueError, "Unapproved field displacement"):
            accepted_button_comparison(self.original, mutant, self.mapping, self.policy)

    def test_scalar_key_mutation_is_rejected(self):
        address = self.mapping["TButton.CMDialogKey"]
        offset = self.candidate.get_offset_from_rva(address - self.candidate.OPTIONAL_HEADER.ImageBase)
        self.assertEqual(self.path.read_bytes()[offset + 10], 13)
        mutant = self.mutate_native(offset + 10, b"\x0C")
        with self.assertRaisesRegex(ValueError, "Additional button changes"):
            accepted_button_comparison(self.original, mutant, self.mapping, self.policy)

    def test_external_callee_swap_is_rejected(self):
        start = self.mapping["TButton.CMDialogKey"]
        md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
        md.detail = True
        call = next(i for i in md.disasm(self.candidate.get_data(start - self.candidate.OPTIONAL_HEADER.ImageBase, 100), start)
                    if i.mnemonic == "call" and i.operands[0].imm == self.mapping["TWinControl.CanFocus"])
        offset = self.candidate.get_offset_from_rva(call.address - self.candidate.OPTIONAL_HEADER.ImageBase)
        mutant = self.mutate_native(offset + 1, struct.pack("<i", self.mapping["KeyDataToShiftState"] - call.address - 5))
        with self.assertRaisesRegex(ValueError, "callee identity"):
            accepted_button_comparison(self.original, mutant, self.mapping, self.policy)

    def test_original_resource_mutation_is_rejected(self):
        record = self.build["original_form_resources"][0]
        res = next(language.data.struct for kind in self.candidate.DIRECTORY_ENTRY_RESOURCE.entries if kind.id == 10
                   for name in kind.directory.entries if str(name.name) == record["name"]
                   for language in name.directory.entries if language.id == record["language"])
        offset = self.candidate.get_offset_from_rva(res.OffsetToData) + 20
        mutant = self.mutate_native(offset, bytes([self.path.read_bytes()[offset] ^ 1]))
        with self.assertRaisesRegex(ValueError, "resource changed"):
            verify_form_resources(mutant, self.build["original_form_resources"])

    def test_queue_opcode_mutation_changes_compared_state(self):
        start = self.entries["DoorAnimation"]
        md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
        md.detail = True
        instruction = next(i for i in md.disasm(self.core.get_data(start - self.core.OPTIONAL_HEADER.ImageBase, 400), start)
                           if i.mnemonic == "mov" and i.operands[-1].type == capstone.x86.X86_OP_IMM
                           and i.operands[-1].imm == 13)
        data = bytearray(self.core_path.read_bytes())
        offset = self.core.get_offset_from_rva(instruction.address - self.core.OPTIONAL_HEADER.ImageBase)
        data[offset + instruction.imm_offset] = 12
        mutant = pefile.PE(data=bytes(data))
        state = baseline(self.original)
        state["EventStack"] = bytearray(state["EventStack"])
        struct.pack_into("<HHH", state["EventStack"], 7 * 6, 13, 60, 7)
        setscalar(state, "EventCursor", 7)
        original = Runner(self.original, ENTRIES, STORAGE).run("DoorAnimation", state)[0]
        candidate = Runner(mutant, {k: self.entries[k] for k in ENTRIES}, self.storage).run("DoorAnimation", state)[0]
        self.assertNotEqual(original["EventStack"], candidate["EventStack"])

    def test_native_gate_outcome_mutation_is_detected(self):
        rows = [json.loads(s) for s in self.build["builds"]["smoke"]["native_output"].splitlines() if s.strip().startswith("{")]
        row = next(r for r in rows if "gate_case" in r)
        # The 41st bit is GameSave1.Enabled after the modal-disable routine.
        self.assertEqual(row["disabled"][40], "0")
        row["disabled"] = row["disabled"][:40] + "1" + row["disabled"][41:]
        result = compare_native_gates(self.original, "\n".join(json.dumps(r) for r in rows))
        self.assertFalse(result["passed"])

    def test_all_methods_have_bodies_without_claiming_full_equivalence(self):
        files = generated()
        inventory = json.loads(files["method-inventory.json"])
        missing = [m for m in inventory["methods"] if m["status"].startswith("unrecovered")]
        self.assertNotIn("MissingMethods.inc", files)
        self.assertEqual(len(missing), 0)
        self.assertEqual(inventory["implemented_methods"], 230)
        self.assertTrue(inventory["complete_published_coverage"])
        self.assertFalse(inventory["complete_game_recovered"])
        report = json.loads((ROOT / "build/delphi-game/reports/comparison-report.json").read_text())
        self.assertFalse(report["full_game_recovered"])
        self.assertFalse(report["pixel_equivalence_established"])


if __name__ == "__main__":
    unittest.main(verbosity=2)
