"""Compare original published routine spans with their actual linked Delphi methods.

Only authenticated corresponding addresses may change. Calls are never expanded,
registers/branches/constants/instance offsets stay literal, and unreviewed routine
boundaries cannot earn an equivalence verdict. This is not a whole-game proof.
"""
import argparse
import bisect
from collections import Counter
import hashlib
import json
from pathlib import Path
import re
import struct

import capstone
import pefile

from recovery_evidence import ROOT, ORIGINAL_HASH, digest
from verify_delphi2_reference import symbols, RUNTIME, class_vmt
from verify_delphi_graphics import data_symbols, GLOBALS, BOUNDARIES
from verify_delphi_game import STORAGE, CORE_METHODS, CORE_STORAGE_NAMES
from verify_delphi_flight import FLIGHT_BOUNDARIES, FLIGHT_STATE
from verify_delphi_startup import OBSERVERS, STATE as STARTUP_STATE
from verify_delphi_ui import UI_BOUNDARIES, UI_STATE
from delphi_routine_layout import trace_layout, NOP


# Reviewed extents are rechecked against decoded control flow and literal refs.
BOUNDARY_PATH = ROOT / "delphi/routine-boundaries.json"
BOUNDARY_REVIEW = json.loads(BOUNDARY_PATH.read_text())
REVIEWED = {int(row["entry"], 16): row for row in BOUNDARY_REVIEW["reviewed_routines"]}


def relocations(pe):
    return {pe.OPTIONAL_HEADER.ImageBase + item.rva
            for block in pe.DIRECTORY_ENTRY_BASERELOC for item in block.entries if item.type == 3}


def assembly_records(address):
    path = ROOT / f"reference/original/whole-program/decompiled/{address:08x}.asm"
    if digest(path) != REVIEWED[address]["assembly_sha256"]:
        raise ValueError(f"Reviewed assembly listing changed: {address:#x}")
    records = [(int(at, 16), bytes.fromhex(raw)) for at, raw in
            re.findall(r"^([0-9a-f]{8})  ([0-9a-f]+) ", path.read_text(), re.M)]
    return records


def memory_stream_vmt(pe):
    """TMemoryStream has a VMT name but no published-property RTTI record."""
    raw = pe.get_memory_mapped_image()
    base = pe.OPTIONAL_HEADER.ImageBase
    names = [m.start() for m in re.finditer(re.escape(b"\x0dTMemoryStream"), raw)]
    if len(names) != 1:
        raise ValueError("Ambiguous TMemoryStream VMT name")
    vmt = names[0] - 16
    if struct.unpack_from("<II", raw, vmt - 28) != (base + names[0], 20):
        raise ValueError("Unreviewed TMemoryStream class name/instance size")
    parent = struct.unpack_from("<I", raw, vmt - 20)[0] - base
    parent_name = struct.unpack_from("<I", raw, parent - 28)[0] - base
    if raw[parent_name:parent_name + 20] != b"\x13TCustomMemoryStream":
        raise ValueError("Unreviewed TMemoryStream parent")
    return base + vmt


def correspondence(original, candidate, mapping, data, methods):
    """Explicit source/layout identities, not inferred from coincident bytes."""
    references = []
    for name, old in methods:
        if name in mapping:
            references.append((old, mapping[name], 1, name))
    for name, old in RUNTIME.items():
        if name in mapping:
            references.append((old, mapping[name], 1, name))
    for old, name in {**BOUNDARIES, **FLIGHT_BOUNDARIES, **OBSERVERS, **UI_BOUNDARIES}.items():
        if name in mapping:
            references.append((old, mapping[name], 1, name))
    if "TControl.SetText" in mapping:
        references.append((0x4135D4, mapping["TControl.SetText"], 1, "TControl.SetText"))
    if "Rect" in mapping:
        references.append((0x40923C, mapping["Rect"], 1, "Rect"))
    if "TWinControl.GetHandle" in mapping:
        references.append((0x416CBC, mapping["TWinControl.GetHandle"], 1, "TWinControl.GetHandle"))
    for old, name in {0x4045A4: "@RewritFile", 0x404254: "@BlockWrite",
                      0x42CEC8: "MessageDlg", 0x42CF78: "ShowMessage",
                      0x42CF9C: "InputQuery", 0x406090: "CreateDir",
                      0x4135A4: "TControl.GetText", 0x43E08C: "TDriveComboBox.SetDrive",
                      0x431188: "TMediaPlayer.Close", 0x417DC4: "TCustomImageList.Clear",
                      0x41A784: "TCanvas.StretchDraw", 0x431C8C: "TMediaPlayer.SetDeviceType",
                      0x430F20: "TMediaPlayer.Open", 0x431C5C: "TMediaPlayer.SetNotify",
                      0x431250: "TMediaPlayer.Play",
                      0x4237DC: "TForm.ShowModal", 0x425018: "TApplication.Terminate",
                      0x42C464: "TTimer.SetInterval",
                      0x402C0C: "TObject.Create", 0x403570: "@LStrLAsg",
                      0x40B26C: "TMemoryStream.LoadFromFile",
                      0x40B19C: "TCustomMemoryStream.SaveToFile"}.items():
        if name in mapping:
            references.append((old, mapping[name], 1, name))
    # Authenticate the constructor's class operand by its named VMT on both sides.
    if class_vmt(original, "TBitmap") != 0x4193B4:
        raise ValueError("Original TBitmap VMT changed")
    references.append((0x4193B4, class_vmt(candidate, "TBitmap"), 1, "TBitmap.VMT"))
    if "TMemoryStream.LoadFromFile" in mapping:
        if memory_stream_vmt(original) != 0x408F68:
            raise ValueError("Original TMemoryStream VMT changed")
        references.append((0x408F68, memory_stream_vmt(candidate), 1, "TMemoryStream.VMT"))
    storage = {**GLOBALS, **FLIGHT_STATE, **STARTUP_STATE, **UI_STATE,
               "MainForm": (0x48C510, 4), "AboutBox": (0x48A760, 4),
               "DataHolderForm": (0x48C50C, 4), "Screen": (0x48A6FC, 4),
               "Application": (0x48A6F8, 4),
               "DamageText": (0x4B8678, 4), "RepeatEnabled": (0x48C5C6, 2),
               "RankingForm": (0x48A764, 4),
               "RankingCategory": (0x48A768, 4), "RankingPath": (0x48A76C, 4),
               "RankingFile": (0x48A770, 332), "RankingHero": (0x48A8BC, 684),
               "RankingMaps": (0x48AB68, 6273), "RankingRows": (0x48C3EC, 288),
               "RankingOptions": (0x4898E4, 10),
               # Button11Click stores the clue index; img8work stores the item
               # selection. Both operands are explicit in the original listings.
               "GameplayHintIndex": (0x48C5A0, 4), "GameplayItemChoice": (0x48C574, 4),
               # Altar handlers use the shared price, dialogue continuation and
               # dword pause flag. The orb row at $48C5B0 is separate.
               "GameplayShopCost": (0x48C594, 4), "DialogueStage": (0x48C5A4, 4),
               "DialogueSpeech": (0x48C5C8, 2),
               "ShopMode": (0x48C5CC, 2), "MerchantTradeWord": (0x48C598, 4),
               "MerchantClueWord": (0x48C59C, 4),
               "BattleHP": (0x48C5BC, 4),
               "PreviousCell": (0x48C588, 4),
               "EventPaused": (0x48C5C0, 4),
               # img6work/yousya share a one-based seven-byte portrait list.
               "OrbRow": (0x48C5B0, 4), "OrbEnemies": (0x489908, 7)}
    for name, old in STORAGE.items():
        actual = CORE_STORAGE_NAMES.get(name, name)
        length = dict(Hero=684, Map=6273, Monster=528, EventStack=180000).get(name, 4)
        storage[actual] = (old, length)
    for name, (old, length) in storage.items():
        if name in data:
            references.append((old, data[name], length, name))
    # mhyouji uses a one-based loop over RenderOrder[DrawIndex - 1]. The
    # indexed operand encodes the array base minus one on both compilers.
    if "RenderOrder" in data:
        references.append((0x489B1F, data["RenderOrder"] - 1, 1, "RenderOrder.index-bias-minus-one"))
    if "OrbEnemies" in data:
        references.append((0x489907, data["OrbEnemies"] - 1, 1, "OrbEnemies.index-bias-minus-one"))
    if "EventStack" in data:
        # stackwork coalesces paired wipe commands using the preceding opcode.
        references.append((0x48C746, data["EventStack"] - 6, 1, "EventStack.previous-opcode-index-bias"))
        # openning9 selects its mode from the preceding row's A field (+2).
        references.append((0x48C748, data["EventStack"] - 4, 1, "EventStack.previous-A-index-bias"))
        # dooropen reads EventStack[EventCursor - 1].B: 6-byte row, field +4.
        references.append((0x48C74A, data["EventStack"] - 2, 1, "EventStack.previous-B-index-bias"))
    def imports(pe):
        return {(dll.dll.lower(), item.name, item.ordinal): item.address
                for dll in pe.DIRECTORY_ENTRY_IMPORT for item in dll.imports}
    left, right = imports(original), imports(candidate)
    for identity in left.keys() & right.keys():
        references.append((left[identity], right[identity], 4, repr(identity)))
    # Import callers target six-byte JMP stubs. Authenticate each stub by its
    # relocated IAT operand and DLL/name identity, rather than masking calls.
    def import_stubs(pe, iat):
        by_address = {address: identity for identity, address in iat.items()}
        result = {}
        code = pe.sections[0]
        start = pe.OPTIONAL_HEADER.ImageBase + code.VirtualAddress
        for site in relocations(pe):
            if not start + 2 <= site <= start + code.Misc_VirtualSize - 4:
                continue
            raw = pe.get_data(site - 2 - pe.OPTIONAL_HEADER.ImageBase, 6)
            if raw[:2] == b"\xff\x25":
                identity = by_address.get(struct.unpack_from("<I", raw, 2)[0])
                if identity:
                    result.setdefault(identity, []).append(site - 2)
        return result
    old_stubs, new_stubs = import_stubs(original, left), import_stubs(candidate, right)
    for identity in old_stubs.keys() & new_stubs.keys():
        for old in old_stubs[identity]:
            for new in new_stubs[identity]:
                references.append((old, new, 1, "import-stub:" + repr(identity)))
    return references


def target_identity(old, new, references, old_start, new_start, length):
    if old_start <= old < old_start + length and new - new_start == old - old_start:
        return "routine+" + hex(old - old_start)
    for left, right, size, name in references:
        if left <= old < left + size and new - right == old - left:
            return name + "+" + hex(old - left)
    return None


def compare_span(old, new, old_start, new_start, old_relocs, new_relocs,
                 references, records, boundary_reviewed=True):
    """Never accept arbitrary address masking or an equal prefix of a routine."""
    original, candidate = bytearray(old), bytearray(new)
    substitutions, unresolved = [], []
    def substitute(offset, left, right, kind):
        identity = target_identity(left, right, references, old_start, new_start, len(old))
        if identity:
            original[offset:offset + 4] = candidate[offset:offset + 4] = bytes(4)
            substitutions.append(dict(offset=offset, kind=kind, identity=identity,
                                      original=hex(left), candidate=hex(right)))
        else:
            unresolved.append(dict(offset=offset, kind=kind, original=hex(left), candidate=hex(right)))
    # PE HIGHLOW relocation sites are authenticated independently on BOTH sides.
    old_sites = {at - old_start for at in old_relocs if old_start <= at < old_start + len(old)}
    new_sites = {at - new_start for at in new_relocs if new_start <= at < new_start + len(new)}
    for offset in sorted(old_sites ^ new_sites):
        unresolved.append(dict(offset=offset, kind="relocation-site-mismatch",
                               original=offset in old_sites, candidate=offset in new_sites))
    for at in sorted(old_relocs):
        offset = at - old_start
        if 0 <= offset <= min(len(old), len(new)) - 4:
            if new_start + offset not in new_relocs:
                continue
            left, right = struct.unpack_from("<I", old, offset)[0], struct.unpack_from("<I", new, offset)[0]
            substitute(offset, left, right, "PE-HIGHLOW")
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    md.detail = True
    for at, raw in records:
        offset = at - old_start
        if not 0 <= offset < min(len(old), len(new)):
            continue
        a = next(md.disasm(raw, at), None)
        if old[offset:offset + len(raw)] != raw:
            raise ValueError(f"Assembly evidence disagrees with original bytes at {at:#x}")
        b = next(md.disasm(new[offset:offset + 15], new_start + offset), None)
        if not a or not b or a.size != b.size or a.mnemonic != b.mnemonic:
            continue
        if not (a.mnemonic == "call" or a.mnemonic.startswith("j")):
            continue
        if (a.operands[0].type != capstone.x86.X86_OP_IMM
                or b.operands[0].type != capstone.x86.X86_OP_IMM or a.imm_size != 4
                or b.imm_size != 4 or a.imm_offset != b.imm_offset):
            continue
        left, right = a.operands[0].imm, b.operands[0].imm
        # Local relative branches must remain byte-for-byte identical.
        if not old_start <= left < old_start + len(old):
            substitute(offset + a.imm_offset, left, right, "external-relative-transfer")
    same = original == candidate
    differences = [i for i, (a, b) in enumerate(zip(original, candidate)) if a != b]
    literal = old == new
    status = ("literal" if literal else "relocated") if same and not unresolved else "different"
    if not boundary_reviewed:
        status = "boundary-unverified"
    return dict(status=status, original_bytes=len(old), candidate_bytes=len(new),
                literal_bytes_equal=literal, verified_relocated_bytes_equal=same and not unresolved,
                original_sha256=hashlib.sha256(old).hexdigest(), candidate_sha256=hashlib.sha256(new).hexdigest(),
                equal_at_routine_offset=sum(a == b for a, b in zip(old, new)),
                remaining_different_overlap_bytes=len(differences),
                remaining_differences=[dict(offset=i, original=old[i], candidate=new[i]) for i in differences[:64]],
                remaining_differences_truncated=len(differences) > 64,
                first_remaining_difference=(differences[0] if differences else
                    min(len(old), len(new)) if len(old) != len(new) else None),
                relocations=substitutions, unresolved_references=unresolved,
                boundary_reviewed=boundary_reviewed)


def validate_current_build(path, map_path):
    """Prevent a current-source claim against a stale executable or linker map."""
    work = ROOT / "build/delphi-game"
    build_path = work / "build-report.json"
    build = json.loads(build_path.read_text())
    for row in build["inputs"]:
        source = ROOT / row["source"]
        staged = work / source.relative_to(ROOT / "delphi")
        if digest(source) != row["source_sha256"] or digest(staged) != row["staged_sha256"]:
            raise ValueError("Stale build source: " + row["source"])
    if (digest(path) != build["builds"]["game"]["artifact_sha256"] or
            digest(map_path) != build["builds"]["game"]["map_sha256"]):
        raise ValueError("Stale build artifact/map")
    return digest(build_path)


def report_for(path, map_path):
    build_hash = (validate_current_build(path, map_path)
                  if path.resolve() == (ROOT / "build/delphi-game/game/Tower.exe").resolve() else None)
    original_path = ROOT / "build/research/TSW.exe"
    if digest(original_path) != ORIGINAL_HASH or BOUNDARY_REVIEW["original_sha256"] != ORIGINAL_HASH:
        raise ValueError("Original executable pin changed")
    original, candidate = pefile.PE(str(original_path)), pefile.PE(str(path))
    mapping, data = symbols(candidate, map_path), data_symbols(candidate, map_path)
    manifest_path = ROOT / "reference/original/presentation/ui-manifest.json"
    manifest = json.loads(manifest_path.read_text())
    methods = [(form["class_name"] + "." + method["name"], int(method["address"], 16))
               for form in manifest["forms"] for method in form["methods"]]
    if set(methods) != {(row["method"], at) for at, row in REVIEWED.items()}:
        raise ValueError("Published-method boundary coverage changed")
    evidence_dir = ROOT / "reference/original/whole-program"
    if (digest(evidence_dir / "metadata.tsv") != BOUNDARY_REVIEW["metadata_sha256"] or
            digest(evidence_dir / "analysis-snapshot.json") != BOUNDARY_REVIEW["function_inventory_sha256"]):
        raise ValueError("Original successor-boundary evidence changed")
    successors = {int(line.split()[0], 16) for line in (evidence_dir / "metadata.tsv").read_text().splitlines()}
    successors.update(int(row["entry"], 16) for row in json.loads(
        (evidence_dir / "analysis-snapshot.json").read_text())["functions"])
    references = correspondence(original, candidate, mapping, data, methods)
    old_relocs, new_relocs = relocations(original), relocations(candidate)
    addresses = sorted(set(mapping.values()))
    rows = []
    evidence = {}
    for name, start in methods:
        exported = dict(assembly_records(start))
        evidence[f"{start:08x}.asm"] = digest(ROOT / f"reference/original/whole-program/decompiled/{start:08x}.asm")
        boundary = REVIEWED[start]
        successor = int(boundary["successor"], 16)
        if successor not in successors:
            raise ValueError(f"Unverified successor boundary at {successor:#x}")
        layout = trace_layout(original, start, successor)
        records = layout.pop("records")
        code_length, pool_length = layout["code_bytes"], layout["literal_pool_bytes"]
        if (code_length, pool_length) != (boundary["code_bytes"], boundary["literal_pool_bytes"]):
            raise ValueError(f"Reviewed routine extent disagrees with control flow: {name}")
        length = code_length + pool_length
        target = mapping[name]
        end = addresses[bisect.bisect_right(addresses, target)]
        # A reviewed routine may have up to three alignment bytes after its end.
        # Only remove them when the next symbol is exactly the expected aligned end
        # and the bytes are the original compiler's known no-op encodings.
        padding = (-length) % 4
        pad = candidate.get_data(target - candidate.OPTIONAL_HEADER.ImageBase + length, padding)
        nop = NOP[padding]
        candidate_length = length if end - target == length + padding and pad == nop else end - target
        old = original.get_data(start - original.OPTIONAL_HEADER.ImageBase, length)
        new = candidate.get_data(target - candidate.OPTIONAL_HEADER.ImageBase, candidate_length)
        comparison = compare_span(old, new, start, target, old_relocs, new_relocs, references,
                                  records)
        decoded = dict(records)
        layout["instructions_missing_from_export"] = [hex(at) for at, raw in records if exported.get(at) != raw]
        layout["export_instructions_not_on_decoded_boundaries"] = [hex(at) for at in exported if at not in decoded]
        rows.append(dict(method=name, original_entry=hex(start), candidate_entry=hex(target),
                         original_code_bytes=code_length, original_literal_pool_bytes=pool_length,
                         original_layout=layout, **comparison))
    result = dict(schema_version=2, original_sha256=ORIGINAL_HASH, candidate_sha256=digest(path),
                candidate_map_sha256=digest(map_path), comparator_sha256=digest(Path(__file__)),
                layout_decoder_sha256=digest(ROOT / "tools/delphi_routine_layout.py"),
                manifest_sha256=digest(manifest_path), build_report_sha256=build_hash,
                boundary_review_sha256=digest(BOUNDARY_PATH),
                current_build_validated=build_hash is not None, assembly_sha256=evidence,
                full_assembly_sha256=digest(ROOT / "reference/original/whole-program/CODE.asm"),
                published_methods=len(rows),
                counts=dict(Counter(row["status"] for row in rows)), routines=rows,
                limits=["All published routine extents include decoded SEH continuations, switch data and referenced literal pools.",
                        "Candidate methods are the actual published implementations. Extracted helpers are never substituted or inlined by this comparator.",
                        "Only matching PE relocation sites or corresponding external transfers with authenticated target identities are normalized.",
                        "Instance offsets, constants, registers, local branches and unknown references are not normalized. English VCL ABI differences remain differences.",
                        "Matching callers do not prove matching callees or whole-game behavior. Defect fixes remain visible as differences."])
    original.close()
    candidate.close()
    return result


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--check", action="store_true")
    parser.add_argument("--details", action="store_true", help="Print every routine's result")
    parser.add_argument("--candidate", type=Path, default=ROOT / "build/delphi-game/game/Tower.exe")
    parser.add_argument("--output", type=Path, default=ROOT / "build/delphi-game/reports/routine-comparison-report.json")
    args = parser.parse_args()
    report = report_for(args.candidate, args.candidate.with_suffix(".map"))
    content = json.dumps(report, indent=2) + "\n"
    if args.check:
        if args.output.read_text() != content:
            raise ValueError("Stale routine comparison report")
    else:
        args.output.parent.mkdir(parents=True, exist_ok=True)
        args.output.write_text(content)
    print("Published routines", report["published_methods"], report["counts"])
    if args.details:
        for row in report["routines"]:
            print(row["method"], row["status"], row["original_bytes"], row["candidate_bytes"],
                  "remaining differences", row["remaining_different_overlap_bytes"])


if __name__ == "__main__":
    main()
