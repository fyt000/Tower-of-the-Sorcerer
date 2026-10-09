"""Adversarial checks of recognition and accounting guards, not game fidelity."""
from contextlib import contextmanager
from pathlib import Path
import json
import unittest

from account_original_program import Image, ROOT
from idr_knowledge_base import KnowledgeBase, find_matches
from review_whole_program import OUTPUT, build, render


@contextmanager
def changed(path, content):
    original = path.read_bytes()
    try:
        path.write_bytes(content)
        yield
    finally:
        path.write_bytes(original)


class AccountingGuards(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.exe = ROOT / 'build/research/TSW.exe'
        cls.image = Image(cls.exe)
        cls.procs = list(KnowledgeBase(ROOT / 'build/research/idr/kb2.bin').procedures())

    def test_fixed_byte_mutation_is_rejected_and_wildcard_retains_match(self):
        procedure = next(p for p in self.procs if p['module'] == 'ExtCtrls' and p['name'] == 'TTimer.WndProc')
        offset = 0x42c390 - self.image.start
        sample = bytearray(self.image.code[offset:offset + len(procedure['dump'])])
        self.assertEqual(find_matches(sample, procedure), [0])
        fixed = next(i for i, m in enumerate(procedure['mask']) if m != 0xff)
        wildcard = next(i for i, m in enumerate(procedure['mask']) if m == 0xff)
        sample[fixed] ^= 1
        self.assertEqual(find_matches(sample, procedure), [])
        sample[fixed] ^= 1
        sample[wildcard] ^= 1
        self.assertEqual(find_matches(sample, procedure), [0])

    def test_identical_callback_shapes_stay_ambiguous(self):
        procedure = next(p for p in self.procs if p['module'] == 'ExtCtrls' and p['name'] == 'TTimer.Timer')
        self.assertEqual([self.image.start + a for a in find_matches(self.image.code, procedure)], [0x41aaa8, 0x42c48c])

    def test_export_drift_is_rejected(self):
        path = OUTPUT / 'decompiled/0042c48c.asm'
        with changed(path, path.read_bytes() + b'; unexpected change\n'):
            with self.assertRaisesRegex(ValueError, 'Export changed'):
                build(self.exe)

    def test_missing_decoded_byte_partition_is_rejected(self):
        path = OUTPUT / 'analysis-snapshot.json'
        snapshot = json.loads(path.read_bytes())
        snapshot['instruction_ranges'] = snapshot['instruction_ranges'][1:]
        with changed(path, json.dumps(snapshot).encode()):
            with self.assertRaisesRegex(ValueError, 'Complete CODE assembly misses/adds'):
                build(self.exe)

    def test_truncated_function_body_is_rejected(self):
        path = OUTPUT / 'analysis-snapshot.json'
        snapshot = json.loads(path.read_bytes())
        function = next(f for f in snapshot['functions'] if f['entry'] == '0x00450ba0')
        function['body_ranges'] = [['0x00450ba0', '0x00450ba0']]
        with changed(path, json.dumps(snapshot).encode()):
            with self.assertRaisesRegex(ValueError, 'Assembly outside function body'):
                build(self.exe)

    def test_generated_ledger_is_current(self):
        report = build(self.exe)
        for name, expected in render(report).items():
            self.assertEqual((OUTPUT / name).read_text(), expected, name)


if __name__ == '__main__':
    unittest.main(verbosity=2)
