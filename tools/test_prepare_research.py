"""Check clean-checkout preparation and preservation of editable local data."""
import json
from pathlib import Path
import tempfile
import unittest
from unittest.mock import patch

import prepare_research as prep


class ResearchPreparationTests(unittest.TestCase):
    def test_missing_cache_explains_both_preparation_modes(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            with self.assertRaisesRegex(ValueError, "prepare_research.py --source"):
                prep.require_cache(root=root)
            with self.assertRaisesRegex(ValueError, "--decompile --ghidra"):
                prep.require_cache(root=root, decompile=True)
            self.assertEqual(list(root.iterdir()), [])

    def test_new_campaign_is_assembled_after_event_recovery(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            source = root / "installation"
            source.mkdir()
            (source / "TSW.exe").write_bytes(b"test original")
            with patch.object(prep, "ROOT", root), patch.object(prep, "digest", return_value=prep.ORIGINAL_HASH), \
                    patch.object(prep, "python") as run:
                prep.prepare_data(source)
                calls = [call.args for call in run.call_args_list]
                events = calls.index(("tools/extract_original_events.py",))
                campaign = next(i for i, call in enumerate(calls) if "--regenerate-campaign" in call)
                self.assertGreater(campaign, events)
                self.assertEqual((root / "build/research/TSW.exe").read_bytes(), b"test original")
                (root / "data").mkdir()
                campaign_file = root / "data/campaign.json"
                campaign_file.write_text('{"custom": true}')
                run.reset_mock()
                prep.prepare_data(source)
                self.assertFalse(any("--regenerate-campaign" in call.args for call in run.call_args_list))
                self.assertEqual(json.loads(campaign_file.read_text()), {"custom": True})

    def test_wrong_original_is_rejected_before_writing(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            (root / "TSW.exe").write_bytes(b"wrong executable")
            with patch.object(prep, "ROOT", root), patch.object(prep, "python") as run:
                with self.assertRaisesRegex(ValueError, "supported English"):
                    prep.prepare_data(root)
                run.assert_not_called()
                self.assertFalse((root / "build").exists())


if __name__ == "__main__":
    unittest.main()
