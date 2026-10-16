"""Adversarial tests of strict routine correspondence and calendar preservation."""
import json
from pathlib import Path
import os
import re
import shutil
import struct
import subprocess
import unittest
from unittest.mock import patch

import pefile

from compare_delphi_routines import compare_span, report_for, ROOT, CORE_METHODS
from compare_delphi_builds import compare_images
from delphi_routine_layout import trace_layout
from review_delphi_calendar import review


class RoutineComparisonTests(unittest.TestCase):
    def compare(self, old, new, **kwargs):
        return compare_span(old, new, kwargs.pop("old_start", 0x1000),
                            kwargs.pop("new_start", 0x2000), kwargs.pop("old_relocs", set()),
                            kwargs.pop("new_relocs", set()), kwargs.pop("references", []),
                            kwargs.pop("records", []), **kwargs)

    def test_literal_complete_body(self):
        self.assertEqual(self.compare(b"\x31\xc0\xc3", b"\x31\xc0\xc3")["status"], "literal")

    def test_unknown_boundary_cannot_earn_equivalence(self):
        self.assertEqual(self.compare(b"\xc3", b"\xc3", boundary_reviewed=False)["status"], "boundary-unverified")

    def test_suffix_and_truncation_are_not_ignored(self):
        for old, new in [(b"\x31\xc0\xc3", b"\x31\xc0\xc3\x90"),
                         (b"\x31\xc0\xc3", b"\x31\xc0")]:
            self.assertEqual(self.compare(old, new)["status"], "different")

    def test_constants_registers_branches_and_instance_offsets_stay_literal(self):
        for old, new in [("b801000000c3", "b802000000c3"),
                         ("31c0c3", "31d2c3"), ("740231c0c3", "740131c0c3"),
                         ("8b80d0010000c3", "8b80cc010000c3")]:
            self.assertEqual(self.compare(bytes.fromhex(old), bytes.fromhex(new))["status"], "different")

    def test_only_same_identity_and_data_offset_relocate(self):
        old = b"\xa1" + struct.pack("<I", 0x5004) + b"\xc3"
        settings = dict(old_relocs={0x1001}, new_relocs={0x2001},
                        references=[(0x5000, 0x9000, 16, "Hero")])
        for value, expected in [(0x9004, "relocated"), (0x9008, "different"), (0xA004, "different")]:
            new = b"\xa1" + struct.pack("<I", value) + b"\xc3"
            self.assertEqual(self.compare(old, new, **settings)["status"], expected)
        changed_opcode = b"\xb8" + struct.pack("<I", 0x9004) + b"\xc3"
        self.assertEqual(self.compare(old, changed_opcode, **settings)["status"], "different")

    def test_relocation_marker_required_on_both_sides_even_if_raw_bytes_equal(self):
        raw = b"\xa1" + struct.pack("<I", 0x5000) + b"\xc3"
        for left, right in [({0x1001}, set()), (set(), {0x2001})]:
            self.assertEqual(self.compare(raw, raw, old_relocs=left, new_relocs=right)["status"], "different")

    def test_external_call_requires_corresponding_callee(self):
        old = b"\xe8" + struct.pack("<i", 0x3000 - 0x1005) + b"\xc3"
        for target, expected in [(0x4000, "literal"), (0x4001, "different"), (0x6000, "different")]:
            new = b"\xe8" + struct.pack("<i", target - 0x2005) + b"\xc3"
            self.assertEqual(self.compare(old, new, references=[(0x3000, 0x4000, 1, "callee")],
                                          records=[(0x1000, old[:5])])["status"], expected)

    def test_stale_assembly_cannot_supply_fake_transfer_sites(self):
        with self.assertRaisesRegex(ValueError, "Assembly evidence"):
            self.compare(bytes.fromhex("b801000000c3"), bytes.fromhex("b801000000c3"),
                         records=[(0x1000, bytes.fromhex("e801000000"))])

    def test_local_table_targets_require_same_routine_offset(self):
        old = struct.pack("<I", 0x1004) + b"\xc3"
        for value, expected in [(0x2004, "relocated"), (0x2003, "different")]:
            self.assertEqual(self.compare(old, struct.pack("<I", value) + b"\xc3",
                old_relocs={0x1000}, new_relocs={0x2000})["status"], expected)

    def test_linked_production_methods_and_explicit_remaining_differences(self):
        path = ROOT / "build/delphi-game/game/Tower.exe"
        report = report_for(path, path.with_suffix(".map"))
        rows = {row["method"]: row for row in report["routines"]}
        for method in CORE_METHODS.values():
            self.assertIn(rows["TTSW10." + method]["status"], ("literal", "relocated"))
        for method in ("ichicheck", "moncheck"):
            self.assertEqual(rows["TTSW10." + method]["status"], "different")
        # The remaining scene changes are explicit English VCL field operands.
        self.assertEqual(rows["TTSW10.moncheck"]["remaining_different_overlap_bytes"], 1)
        self.assertEqual(rows["TTSW10.ichicheck"]["remaining_different_overlap_bytes"], 21)
        self.assertTrue(report["current_build_validated"])
        self.assertEqual(report["published_methods"], 230)
        self.assertTrue(all(row["boundary_reviewed"] for row in rows.values()))
        self.assertEqual(report["counts"], {"relocated": 73, "different": 157})
        for method in (["TAboutBox.copyrightonclick", "TTSW10.kasanegaki", "TTSW10.toroad2", "TTSW10.savework",
                        "TTSW10.TSW10close", "TTSW10.soundcheck", "TTSW10.madoushi1"] +
                       [f"TTSW10.BitBtn{i}Click" for i in range(1, 5)] +
                       [f"TTSW10.Button{i}Click" for i in range(11, 35)]):
            self.assertEqual(rows[method]["status"], "relocated", method)
        # These restored bodies still fail strict equivalence: their remaining
        # instance-field operands differ by the English VCL's four bytes.
        for method, count in {"zenolivework": 4, "madoushilivework": 4, "yusyahyouji1": 8,
                              "yusyahyouji": 6, "mhyouji": 4, "yusyai1": 12, "yusyai2": 11,
                              "yusyai3": 10, "yusyai4": 12, "K5Click": 1}.items():
            row = rows["TTSW10." + method]
            self.assertEqual(row["status"], "different")
            self.assertEqual(row["original_bytes"], row["candidate_bytes"])
            self.assertEqual(row["unresolved_references"], [])
            self.assertEqual(row["remaining_different_overlap_bytes"], count)
            self.assertTrue(all(d["original"] - d["candidate"] == 4 for d in row["remaining_differences"]))
        door = rows["TTSW10.doorcheck"]
        self.assertEqual((door["original_bytes"], door["candidate_bytes"]), (863, 863))
        self.assertEqual(door["remaining_different_overlap_bytes"], 0)
        # Nested gift checks recover roujin's original allocation. Only the
        # Button1/RichEdit1 field displacements remain different in English VCL.
        old_man = rows["TTSW10.roujin"]
        self.assertEqual((old_man["original_bytes"], old_man["candidate_bytes"]), (1808, 1808))
        self.assertEqual(old_man["status"], "different")
        self.assertEqual(old_man["unresolved_references"], [])
        self.assertEqual(old_man["remaining_different_overlap_bytes"], 2)
        self.assertEqual(old_man["remaining_differences"], [
            dict(offset=16, original=0xD0, candidate=0xCC),
            dict(offset=35, original=0xCC, candidate=0xC8),
        ])
        restored = {"TTSW10.OptionSave1Click": 6, "TForm2.hyouji": 115,
                    "TForm2.optionload": 146, "TForm2.scoresave": 66,
                    "TForm2.loadwork": 2, "TForm2.Button1Click": 184,
                    "TForm4.Button3Click": 5}
        restored.update({f"TTSW10.Load{i}1Click": 14 for i in range(1, 9)})
        restored.update({f"TTSW10.Save{i}1Click": 10 for i in range(1, 9)})
        restored.update({f"TForm2.BitBtn{i}Click": 1 for i in range(1, 6)})
        restored.update({"TTSW10." + method: count for method, count in {
            "monswork": 6, "Button7Click": 5, "Button42Click": 5,
            "GameStart1Click": 1, "GameQuit1Click": 2, "Exit1Click": 2,
            "NormalOption1Click": 3, "HighScore1Click": 2, "K6Click": 8,
            "N640x4001Click": 5, "N800x5001Click": 5, "monshyouji": 48,
            "keydisplay": 7, "Timer1Timer": 2, "Button10Click": 5,
            "append": 26, "obudameiji": 6, "dameiji": 6, "timer3ontimer": 1,
            "syokidata0": 1137, "wavon1Click": 2, "mediaplayer5onnotify": 2,
            "itemlive": 48, "itemdisp": 110, "dooropen": 205, "openning9": 208,
            "optionl1": 70, "kaidanwork": 9, "openning31": 21, "mevent": 8, "touzoku": 4,
            "itemichiwork": 71, "timer4ontimer": 28,
            "Button35Click": 28, "monidouwork": 27, "monidou": 41,
            "banpaiawork": 94, "yusyaidou": 2, "idou": 11,
            "yousya": 100, "Button36Click": 64, "openning2": 5,
            "taisen": 48, "taisen2": 9, "timer2timer": 2,
            "syokidata2": 197, "loadwork": 7,
        }.items()})
        for method, count in restored.items():
            row = rows[method]
            self.assertEqual(row["status"], "different", method)
            self.assertEqual(row["original_bytes"], row["candidate_bytes"], method)
            self.assertEqual(row["unresolved_references"], [], method)
            self.assertEqual(row["remaining_different_overlap_bytes"], count, method)
        # The English SetFocus slot encodes three bytes shorter per call.
        # These remain strict failures, including shifted branches/literal pools.
        self.assertEqual(rows["TForm2.scoreload"]["candidate_bytes"], 7588)
        self.assertEqual(rows["TForm2.formactivate"]["candidate_bytes"], 8236)
        self.assertEqual(rows["TTSW10.formkeydown"]["candidate_bytes"], 1256)
        for method, size in {"img5work": 1264, "Button39Click": 660,
                             "Button40Click": 680, "Button41Click": 684, "img6work": 2604}.items():
            self.assertEqual(rows["TTSW10." + method]["status"], "different")
            self.assertEqual(rows["TTSW10." + method]["candidate_bytes"], size)
        self.assertEqual(rows["TTSW10.mazyutu1"]["status"], "relocated")
        self.assertEqual(rows["TTSW10.mazyutu1"]["candidate_bytes"], 1066)
        # Only the floor-49 stale event remains an intentional gameplay fix.
        self.assertEqual(rows["TTSW10.itemichiwork2"]["status"], "relocated")
        self.assertEqual(rows["TTSW10.itemichiwork2"]["candidate_bytes"], 66)
        for method, size in {"taisen": 4724, "taisen2": 2744, "timer2timer": 99,
                             "syokidata2": 3792, "loadwork": 776}.items():
            self.assertEqual(rows["TTSW10." + method]["candidate_bytes"], size)

    def test_comparison_uses_machine_code_without_whole_program_exports(self):
        original_open = Path.open

        def open_without_exports(path, *args, **kwargs):
            if path.is_relative_to(ROOT / "reference/original/whole-program"):
                raise AssertionError("Routine comparison must not depend on generated exports")
            return original_open(path, *args, **kwargs)

        binary = ROOT / "build/delphi-game/game/Tower.exe"
        with patch.object(Path, "open", open_without_exports):
            report = report_for(binary, binary.with_suffix(".map"))
        self.assertEqual(report["counts"], {"relocated": 73, "different": 157})
        self.assertTrue(report["current_build_validated"])

    def trace_original(self, start, limit, mutation=None):
        pe = pefile.PE(str(ROOT / "build/research/TSW.exe"))
        if mutation:
            at, raw = mutation
            data = bytearray(pe.__data__)
            offset = pe.get_offset_from_rva(at - pe.OPTIONAL_HEADER.ImageBase)
            data[offset:offset + len(raw)] = raw
            pe.close()
            pe = pefile.PE(data=bytes(data))
        try:
            return trace_layout(pe, start, limit)
        finally:
            pe.close()

    def test_decode_repairs_misaligned_about_export(self):
        records = dict(self.trace_original(0x434094, 0x4340B4)["records"])
        self.assertEqual(records[0x4340AC], bytes.fromhex("e84ff4fdff"))
        self.assertEqual(records[0x4340B2], b"\xc3")
        self.assertNotIn(0x4340B0, records)  # Ghidra incorrectly exported CALLF here.

    def test_exception_continuation_and_pool_cannot_be_truncated(self):
        layout = self.trace_original(0x46CB1C, 0x4770E0)
        self.assertEqual(layout["code_bytes"], 42422)
        self.assertEqual(layout["literal_pool_bytes"], 14)
        self.assertIn(0x4770CB, layout["exception_continuations"])
        for stop in (0x4770C4, 0x4770CB, 0x4770D2):
            with self.assertRaises(ValueError):
                self.trace_original(0x46CB1C, stop)

    def test_boundary_decoder_rejects_split_instructions_and_unexplained_padding(self):
        with self.assertRaises(ValueError):
            self.trace_original(0x434094, 0x4340B1)
        with self.assertRaisesRegex(ValueError, "Unexplained bytes after routine"):
            self.trace_original(0x47BEAC, 0x47C20C, (0x47C20B, b"\x00"))

    def test_switch_target_cannot_escape_reviewed_routine(self):
        with self.assertRaisesRegex(ValueError, "Switch target crosses boundary"):
            self.trace_original(0x44C9F0, 0x44CB34, (0x44CA22, struct.pack("<I", 0x500000)))

    def test_pool_header_is_validated_and_pool_bytes_are_compared(self):
        with self.assertRaisesRegex(ValueError, "Unexplained literal-pool byte"):
            self.trace_original(0x46CB1C, 0x4770E0, (0x4770D4, bytes(4)))
        self.assertEqual(self.compare(b"\xc3\0\0\0OK\0", b"\xc3\0\0\0NO\0")["status"], "different")

    def test_calendar_bytes_and_corruption(self):
        original = pefile.PE(str(ROOT / "build/research/TSW.exe"))
        path = ROOT / "build/delphi-game/game/Tower.exe"
        candidate = pefile.PE(str(path))
        self.assertEqual(len(review(original, candidate)["tables"]), 2)
        leaf = next(lang.data.struct for kind in candidate.DIRECTORY_ENTRY_RESOURCE.entries if kind.id == 6
                    for name in kind.directory.entries if name.id == 4074 for lang in name.directory.entries)
        data = bytearray(path.read_bytes())
        data[candidate.get_offset_from_rva(leaf.OffsetToData) + 2] ^= 1
        with self.assertRaisesRegex(ValueError, "calendar resource missing or changed"):
            review(original, pefile.PE(data=bytes(data)))

    def test_named_values_emit_identical_production_bytes_to_numeric_literals(self):
        # This is an isolated compiler experiment, not a production generator.
        source = ROOT / "build/delphi-game"
        dest = ROOT / "build/delphi-enum-equivalence"
        shutil.copytree(source / "src", dest / "src", dirs_exist_ok=True)
        shutil.copyfile(source / "Tower.dpr", dest / "Tower.dpr")
        shutil.copyfile(source / "GameResources.res", dest / "GameResources.res")
        text = (source / "src/GameState.pas").read_text(encoding="cp1252")
        declarations = re.sub(r"\{[^}]*\}", "", text)
        ordinals = {}
        for declaration in re.findall(r"\bT\w+ = \((.*?)\);", declarations, re.S):
            names = re.findall(r"\b[A-Za-z]\w*\b", declaration)
            ordinals.update(zip(names, range(len(names))))
        self.assertEqual(sum(name.startswith("ev") for name in ordinals), 23)
        self.assertEqual(ordinals["hfUp"], 4)
        self.assertEqual(ordinals["moveUp"], 1)
        self.assertEqual(ordinals["itemHeroOrb"], 1)
        self.assertEqual(ordinals["shopMerchant"], 0)
        values = {}
        constants = declarations.split("const", 1)[1].split("type", 1)[0]
        for name, expression in re.findall(r"\b(\w+) = ([^;]+);", constants):
            expression = expression.replace("SizeOf(Longint)", "4")
            values[name] = eval(expression, {"__builtins__": {}}, values)
        self.assertGreater(len(values), 200)
        identifiers = re.compile(r"\b(" + "|".join(values) + r")\b")
        for path in (dest / "src").rglob("*"):
            if path.suffix in (".pas", ".inc") and path.name != "GameState.pas":
                text = path.read_text(encoding="cp1252")
                text = re.sub(r"Ord\((\w+)\)",
                              lambda m: str(ordinals[m[1]]) if m[1] in ordinals else m[0], text)
                text = identifiers.sub(lambda m: str(values[m[1]]), text)
                path.write_text(text, encoding="cp1252")
        compiler = ROOT / "build/research/delphi2/base/bin/DCC32.EXE"
        lib = os.path.relpath(compiler.parent.parent / "lib", dest)
        result = subprocess.run([str(compiler), "-B", "-GD", "-U" + lib + ";src",
                                 "-Isrc;src\\generated", "-E.", "-N.", "Tower.dpr"],
                                cwd=dest, capture_output=True, timeout=30)
        self.assertEqual(result.returncode, 0, result.stdout.decode("cp1252"))
        comparison = compare_images((source / "game/Tower.exe").read_bytes(), (dest / "Tower.exe").read_bytes())
        self.assertTrue(comparison["passed"], comparison)


if __name__ == "__main__":
    unittest.main()
