"""Ensure the cleanup comparator rejects drift outside resource timestamps."""
import unittest
from pathlib import Path
import tempfile
from unittest.mock import patch

import pefile

from compare_delphi_builds import WORK, compare_images, resource_timestamps, sha, validate_build_inputs


class DelphiBuildComparisonTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.raw = (WORK / "game/Tower.exe").read_bytes()
        cls.pe = pefile.PE(data=cls.raw)

    @classmethod
    def tearDownClass(cls):
        cls.pe.close()

    def mutated(self, offset):
        raw = bytearray(self.raw)
        raw[offset] ^= 1
        return bytes(raw)

    def test_exact_build_passes(self):
        result = compare_images(self.raw, self.raw)
        self.assertTrue(result["passed"])
        self.assertTrue(result["exact_bytes_equal"])

    def test_all_resource_directory_timestamps_may_change(self):
        raw = bytearray(self.raw)
        offsets = resource_timestamps(self.raw).values()
        self.assertGreater(len(offsets), 1)
        for offset in offsets:
            for i in range(4):
                raw[offset + i] ^= 0xFF
        result = compare_images(self.raw, bytes(raw))
        self.assertTrue(result["passed"])
        self.assertEqual(result["differing_timestamp_bytes"], len(offsets) * 4)

    def test_instruction_mutation_fails_even_with_timestamp_changes(self):
        raw = bytearray(self.raw)
        raw[self.pe.sections[0].PointerToRawData + 16] ^= 1
        for offset in resource_timestamps(self.raw).values():
            raw[offset] ^= 1
        result = compare_images(self.raw, bytes(raw))
        self.assertFalse(result["passed"])
        self.assertEqual(result["unexpected_differing_bytes"], 1)

    def test_initialized_data_mutation_fails(self):
        section = next(s for s in self.pe.sections if s.Name.rstrip(b"\0") == b"DATA")
        self.assertFalse(compare_images(self.raw, self.mutated(section.PointerToRawData))["passed"])

    def test_bss_size_change_fails(self):
        section = next(s for s in self.pe.sections if s.Name.rstrip(b"\0") == b"BSS")
        offset = section.get_field_absolute_offset("Misc_VirtualSize")
        self.assertFalse(compare_images(self.raw, self.mutated(offset))["passed"])

    def test_pe_linker_timestamp_is_not_exempt(self):
        offset = self.pe.FILE_HEADER.get_field_absolute_offset("TimeDateStamp")
        self.assertFalse(compare_images(self.raw, self.mutated(offset))["passed"])

    def test_resource_header_version_is_not_exempt(self):
        offset = self.pe.DIRECTORY_ENTRY_RESOURCE.struct.get_field_absolute_offset("MajorVersion")
        self.assertFalse(compare_images(self.raw, self.mutated(offset))["passed"])

    def test_resource_payload_mutation_fails(self):
        directory = self.pe.DIRECTORY_ENTRY_RESOURCE
        while hasattr(directory.entries[0], "directory"):
            directory = directory.entries[0].directory
        offset = self.pe.get_offset_from_rva(directory.entries[0].data.struct.OffsetToData)
        self.assertFalse(compare_images(self.raw, self.mutated(offset))["passed"])

    def test_resource_identity_change_fails(self):
        entry = self.pe.DIRECTORY_ENTRY_RESOURCE.entries[0]
        offset = entry.struct.get_field_absolute_offset("Name")
        result = compare_images(self.raw, self.mutated(offset))
        self.assertFalse(result["passed"])
        self.assertFalse(result["resource_directory_layout_equal"])

    def test_image_layout_change_fails(self):
        offset = self.pe.OPTIONAL_HEADER.get_field_absolute_offset("SizeOfImage")
        self.assertFalse(compare_images(self.raw, self.mutated(offset))["passed"])

    def test_adding_or_removing_bytes_fails(self):
        for raw in (self.raw + b"\0", self.raw[:-1]):
            with self.subTest(length=len(raw)):
                self.assertFalse(compare_images(self.raw, raw)["passed"])


class BuildInputTests(unittest.TestCase):
    def test_original_and_crlf_staged_source_are_checked_independently(self):
        for changed in (None, "source", "staged"):
            with self.subTest(changed=changed), tempfile.TemporaryDirectory() as temporary:
                root = Path(temporary)
                work = root / "build"
                source = root / "delphi/src/GameState.pas"
                staged = work / "src/GameState.pas"
                source.parent.mkdir(parents=True)
                staged.parent.mkdir(parents=True)
                source.write_bytes(b"unit GameState;\n")
                staged.write_bytes(b"unit GameState;\r\n")
                report = dict(inputs=[dict(source="delphi/src/GameState.pas",
                                          source_sha256=sha(source.read_bytes()),
                                          staged_sha256=sha(staged.read_bytes()))])
                if changed:
                    target = source if changed == "source" else staged
                    target.write_bytes(target.read_bytes() + b"{ stale }\n")
                with patch("compare_delphi_builds.ROOT", root):
                    if changed:
                        with self.assertRaisesRegex(ValueError, "changed since build"):
                            validate_build_inputs(report, work)
                    else:
                        validate_build_inputs(report, work)


if __name__ == "__main__":
    unittest.main(verbosity=2)
