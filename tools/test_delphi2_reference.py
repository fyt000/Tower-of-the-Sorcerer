"""Adversarial checks for compiler-assisted recovery comparison boundaries."""
import json
import struct
import unittest

import pefile

from verify_delphi2_reference import (
    ROOT, gameplay_comparison, instructions, normalized, symbols,
)
from verify_delphi2_ime import dispatcher_bytes, fixture


class DelphiReferenceTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.original = pefile.PE(str(ROOT / "build/research/TSW.exe"))
        cls.probe_path = ROOT / "build/research/delphi2/probe-base/RuntimeProbe.exe"
        cls.probe = pefile.PE(str(cls.probe_path))
        cls.symbols = symbols(cls.probe, cls.probe_path.with_suffix(".map"))

    def test_field_offset_changes_are_not_normalized(self):
        address = self.symbols["TWinControl.CanFocus"]
        data = bytearray(self.probe_path.read_bytes())
        offset = self.probe.get_offset_from_rva(address - self.probe.OPTIONAL_HEADER.ImageBase)
        # CMP [EAX + $38],0 checks Enabled. Change the actual object field.
        field = data.find(b"\x80\x78\x38\x00", offset, offset + 51)
        self.assertGreaterEqual(field, offset)
        data[field + 2] = 0x37
        mutant = pefile.PE(data=bytes(data))
        self.assertNotEqual(normalized(self.probe, instructions(self.probe, address, 51))[0],
                            normalized(mutant, instructions(mutant, address, 51))[0])

    def test_scalar_constants_are_not_normalized(self):
        address = self.symbols["TWinControl.CanFocus"]
        data = bytearray(self.probe_path.read_bytes())
        offset = self.probe.get_offset_from_rva(address - self.probe.OPTIONAL_HEADER.ImageBase)
        constant = data.find(b"\xB3\x01", offset, offset + 51)
        self.assertGreaterEqual(constant, offset)
        data[constant + 1] = 2
        mutant = pefile.PE(data=bytes(data))
        self.assertNotEqual(normalized(self.probe, instructions(self.probe, address, 51))[0],
                            normalized(mutant, instructions(mutant, address, 51))[0])

    def test_local_branch_changes_are_not_normalized(self):
        address = self.symbols["TWinControl.CanFocus"]
        data = bytearray(self.probe_path.read_bytes())
        offset = self.probe.get_offset_from_rva(address - self.probe.OPTIONAL_HEADER.ImageBase)
        branch = data.find(b"\x74\x1B", offset, offset + 51)
        self.assertGreaterEqual(branch, offset)
        data[branch + 1] -= 2
        mutant = pefile.PE(data=bytes(data))
        self.assertNotEqual(normalized(self.probe, instructions(self.probe, address, 51))[0],
                            normalized(mutant, instructions(mutant, address, 51))[0])

    def test_address_normalization_is_explicit(self):
        original = instructions(self.original, 0x416C2C, 51)
        compiled = instructions(self.probe, self.symbols["TWinControl.CanFocus"], 51)
        old, changes = normalized(self.original, original)
        new, other = normalized(self.probe, compiled)
        self.assertEqual(old, new)
        self.assertTrue(changes)
        self.assertTrue(other)
        self.assertEqual({c["reason"] for c in changes}, {"external-relative-transfer"})
        self.assertNotEqual(b"".join(i.bytes for i in original), b"".join(i.bytes for i in compiled))

    def test_gameplay_mutation_fails_bytes_and_effects(self):
        path = ROOT / "build/research/delphi2/recovery-probe/RecoveryProbe.dll"
        data = bytearray(path.read_bytes())
        candidate = pefile.PE(data=bytes(data))
        symbol = next(s for s in candidate.DIRECTORY_ENTRY_EXPORT.symbols if s.name == b"ClassifyNeighbor")
        offset = candidate.get_offset_from_rva(symbol.address)
        # Change the wall classification from 1 to 2, retaining valid code.
        expected = b"\xC7\x05" + struct.pack("<I", 0x48C58C) + struct.pack("<I", 1)
        site = data.find(expected, offset, offset + 282)
        self.assertGreaterEqual(site, offset)
        data[site + 6] = 2
        mutant = pefile.PE(data=bytes(data))
        result = gameplay_comparison(self.original, mutant)
        self.assertFalse(result["literal_byte_match"])
        self.assertFalse(result["passed"])
        self.assertTrue(result["mismatches"])

    def test_abi_mismatch_is_retained_as_unaccepted_baseline(self):
        report = json.loads((ROOT / "build/research/delphi2-reports/comparison-report.json").read_text())
        self.assertFalse(report["status"]["complete_runtime_baseline_accepted"])
        self.assertFalse(report["status"]["full_pascal_game_recovered"])
        for variant in report["variants"].values():
            button = next(r for r in variant["runtime_shapes"] if r["symbol"] == "TButton.CMDialogKey")
            self.assertFalse(button["normalized_shape_match"])
            self.assertEqual({r["class_name"] for r in variant["layouts"] if not r["matches_original"]},
                             {"TWinControl", "TForm", "TButton"})

    def test_ime_jump_target_is_not_discarded_as_a_relocation(self):
        data = bytearray((ROOT / "build/research/TSW.exe").read_bytes())
        offset = self.original.get_offset_from_rva(0x40EF36 - 0x400000)
        # Route imHira to the actual imSAlpha body, retaining valid local code.
        struct.pack_into("<I", data, offset, 0x40EF5C)
        mutant = pefile.PE(data=bytes(data))
        self.assertNotEqual(dispatcher_bytes(self.original, 0x40EE88)[0],
                            dispatcher_bytes(mutant, 0x40EE88)[0])
        inputs = dict(mode=4, library=True, context=True,
                      conversion=((0, 0), (0, 0)), api_result=1)
        self.assertNotEqual(fixture(self.original, 0x40EE88, inputs),
                            fixture(mutant, 0x40EE88, inputs))

    def test_ime_api_slot_identity_is_not_normalized(self):
        data = bytearray((ROOT / "build/research/TSW.exe").read_bytes())
        offset = self.original.get_offset_from_rva(0x40EE88 - 0x400000)
        call = data.find(b"\xFF\x15\x30\xA6\x48\x00", offset, offset + 253)
        self.assertGreaterEqual(call, offset)
        struct.pack_into("<I", data, call + 2, 0x48A63C)
        mutant = pefile.PE(data=bytes(data))
        self.assertNotEqual(dispatcher_bytes(self.original, 0x40EE88)[0],
                            dispatcher_bytes(mutant, 0x40EE88)[0])

    def test_ime_conversion_constant_mutation_changes_api_effect(self):
        data = bytearray((ROOT / "build/research/TSW.exe").read_bytes())
        offset = self.original.get_offset_from_rva(0x40EE88 - 0x400000)
        site = data.find(b"\x83\x0C\x24\x09", offset, offset + 253)
        self.assertGreaterEqual(site, offset)
        data[site + 3] = 8
        mutant = pefile.PE(data=bytes(data))
        inputs = dict(mode=4, library=True, context=True,
                      conversion=((0, 0), (0, 0)), api_result=1)
        self.assertNotEqual(fixture(self.original, 0x40EE88, inputs),
                            fixture(mutant, 0x40EE88, inputs))


if __name__ == "__main__":
    unittest.main(verbosity=2)
