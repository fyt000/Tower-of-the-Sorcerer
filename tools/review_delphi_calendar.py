"""Trace and verify the original Japanese RTL weekday/era string resources.

The report distinguishes resource preservation from Japanese RTL behavior.
It authenticates the pinned original, the startup/load/parse instruction sites,
and the complete two payloads in the current linked game.
"""
import argparse
import hashlib
import json
import struct

import pefile

from recovery_evidence import ROOT, ORIGINAL_HASH, digest
from compare_delphi_binary import resource_payloads, string_table
from compare_delphi_routines import validate_current_build

REPORT = ROOT / "build/delphi-game/reports/calendar-review-report.json"
EXPECTED = ["日", "月", "火", "水", "木", "金", "土",
            "日曜日", "月曜日", "火曜日", "水曜日", "木曜日", "金曜日", "土曜日",
            "4", "M,明,明治,1868,1,1", "T,大,大正,1912,7,30",
            "S,昭,昭和,1926,12,25", "H,平,平成,1989,1,8"] + [""] * 13


def review(original, candidate):
    if hashlib.sha256(original.__data__).hexdigest() != ORIGINAL_HASH:
        raise ValueError("Original executable pin changed")
    left, right = resource_payloads(original), resource_payloads(candidate)
    tables, strings = [], {}
    for block, size in ((4073, 120), (4074, 128)):
        identity = (6, block, 0)
        raw = left[identity]
        if len(raw) != size or right.get(identity) != raw:
            raise ValueError(f"Japanese calendar resource missing or changed: {identity}")
        decoded = string_table(raw, block)
        strings.update(decoded)
        tables.append(dict(type=6, block=block, language=0, bytes=size,
                           sha256=hashlib.sha256(raw).hexdigest(), strings=decoded,
                           candidate_payload_exact=True))
    if list(strings.values()) != EXPECTED:
        raise ValueError("Unreviewed Japanese calendar contents")
    evidence = []

    def check(at, raw, meaning):
        if original.get_data(at - original.OPTIONAL_HEADER.ImageBase, len(raw)) != raw:
            raise ValueError(f"Calendar instruction evidence changed at {at:#x}")
        evidence.append(dict(address=hex(at), bytes=raw.hex(), meaning=meaning))

    for site, target, meaning in (
            (0x488D62, 0x408154, "Program startup calls SysUtils initialization"),
            (0x408177, 0x406FB4, "Initialize Japanese weekday arrays"),
            (0x40817C, 0x4070E4, "Initialize Japanese era records"),
            (0x406FF1, 0x405BF0, "Load short weekday string"),
            (0x407027, 0x405BF0, "Load long weekday string"),
            (0x40710E, 0x405BF0, "Load era count"),
            (0x407118, 0x405BD8, "Parse era count with StrToIntDef"),
            (0x407179, 0x405BF0, "Load the next era definition"),
            (0x407184, 0x407084, "Parse comma-delimited era fields"),
            (0x407258, 0x4067AC, "Encode the era start date"),
            (0x405C0D, 0x4050F4, "LoadStr calls the LoadStringA import thunk")):
        check(site, b"\xe8" + struct.pack("<i", target - site - 5), meaning)
    for site, raw, meaning in (
            (0x406FD6, "bb01000000", "Weekday loop starts at 1"),
            (0x406FDB, "be98a44800", "Short weekday array at 0x48a498"),
            (0x406FE0, "bfd0a44800", "Long weekday array at 0x48a4d0"),
            (0x406FEB, "8d837ffe0000", "Short weekday ID = 0xfe7f + index"),
            (0x407021, "8d8386fe0000", "Long weekday ID = 0xfe86 + index"),
            (0x407052, "83c71083c60883fb08", "Long/short strides 16/8; stop after 7 days"),
            (0x407109, "b88efe0000", "Era-count string ID 0xfe8e"),
            (0x40711D, "66a340a54800", "Era count stored as a Word at 0x48a540"),
            (0x40713F, "c1e0028d04c0", "Allocate count * 36 bytes of era records"),
            (0x40714A, "a344a54800", "Era-record pointer at 0x48a544"),
            (0x407173, "8d868efe0000", "Era definition ID = 0xfe8e + index"),
            (0x40725D, "dd5b1c", "Store encoded date at era-record offset 28"),
            (0x4050F4, "ff2528b44b00", "Indirect jump through LoadStringA IAT entry")):
        check(site, bytes.fromhex(raw), meaning)
    imports = {(dll.dll.lower(), entry.name): entry.address
               for dll in original.DIRECTORY_ENTRY_IMPORT for entry in dll.imports}
    if imports.get((b"user32.dll", b"LoadStringA")) != 0x4BB428:
        raise ValueError("LoadStringA import identity changed")
    return dict(schema_version=1, original_sha256=ORIGINAL_HASH, tables=tables,
                classification="Japanese RTL calendar initialization data", instruction_evidence=evidence,
                weekday_ids=[65152, 65165], era_count_id=65166, era_definition_ids=[65167, 65170],
                record_layout=dict(bytes=36, latin_abbreviation=0, japanese_abbreviation=5,
                                   full_name=10, encoded_start_date=28),
                japanese_runtime_behavior_restored=False,
                limits=["The two resources are preserved exactly; the English RTL does not contain the original Japanese weekday/era initializers.",
                        "These are runtime calendar strings, not game dialogue. This trace establishes startup consumers, not every indirect date-formatting use.",
                        "Historical era data ends at Heisei. No contemporary eras have been added to the recovered data."])


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--check", action="store_true")
    args = parser.parse_args()
    path = ROOT / "build/delphi-game/game/Tower.exe"
    report = review(pefile.PE(str(ROOT / "build/research/TSW.exe")), pefile.PE(str(path)))
    report.update(candidate_sha256=digest(path), auditor_sha256=digest(__file__),
                  build_report_sha256=validate_current_build(path, path.with_suffix(".map")))
    report["english_sysutils_source_sha256"] = digest(ROOT / "build/research/delphi2/base/source/RTL/SYS/SYSUTILS.PAS")
    content = json.dumps(report, indent=2, ensure_ascii=False) + "\n"
    if args.check:
        if REPORT.read_text(encoding="utf-8") != content:
            raise ValueError("Stale calendar review report")
    else:
        REPORT.parent.mkdir(parents=True, exist_ok=True)
        REPORT.write_text(content, encoding="utf-8")
    print("Japanese RTL calendar: 2 exact resource payloads, 19 nonempty strings, startup callers verified")


if __name__ == "__main__":
    main()
