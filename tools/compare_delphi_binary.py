"""Unmasked raw PE-section and resource-payload accounting.

This is a byte comparison, not a semantic equivalence verdict. Sections are
paired by name and bytes by section-relative offset, without relocation,
instruction, UI, padding, timestamp or IME normalization. Resource leaves are
also paired by their exact type/name/language identity so directory placement
does not hide whether the original content survived linking.
"""
from pathlib import Path
import argparse
import hashlib
import json
import struct

import pefile

from verify_delphi2_reference import ROOT, ORIGINAL_HASH, digest
from build_delphi_game import WORK


def byte_difference(original, candidate):
    overlap = min(len(original), len(candidate))
    differing = [i for i in range(overlap) if original[i] != candidate[i]]
    first = differing[0] if differing else (overlap if len(original) != len(candidate) else None)
    return dict(original_bytes=len(original), candidate_bytes=len(candidate),
                overlapping_bytes=overlap, equal_at_same_offset=overlap - len(differing),
                different_at_same_offset=len(differing),
                original_only_tail=len(original) - overlap, candidate_only_tail=len(candidate) - overlap,
                first_difference_offset=first, exact_bytes_equal=original == candidate,
                original_sha256=hashlib.sha256(original).hexdigest(),
                candidate_sha256=hashlib.sha256(candidate).hexdigest())


def resource_payloads(pe):
    records = {}
    for kind in pe.DIRECTORY_ENTRY_RESOURCE.entries:
        for name in kind.directory.entries:
            for language in name.directory.entries:
                identity = (kind.id if kind.name is None else str(kind.name),
                            name.id if name.name is None else str(name.name), language.id)
                data = language.data.struct
                records[identity] = pe.get_data(data.OffsetToData, data.Size)
    return records


def string_table(blob, block):
    """Decode all 16 UTF-16 entries, retaining their original numeric IDs."""
    result, offset = {}, 0
    for slot in range(16):
        length = struct.unpack_from("<H", blob, offset)[0]
        offset += 2
        end = offset + length * 2
        if end > len(blob):
            raise ValueError("Truncated string-table resource")
        result[(block - 1) * 16 + slot] = blob[offset:end].decode("utf-16le")
        offset = end
    if offset != len(blob):
        raise ValueError("Unreviewed string-table trailing bytes")
    return result


def compare_sections(original, candidate):
    left = {s.Name.rstrip(b"\0").decode("ascii"): s for s in original.sections}
    right = {s.Name.rstrip(b"\0").decode("ascii"): s for s in candidate.sections}
    records = []
    for name in dict.fromkeys([*left, *right]):
        old, new = left.get(name), right.get(name)
        record = dict(section=name, original_present=old is not None, candidate_present=new is not None)
        if old is not None and new is not None:
            record.update(byte_difference(old.get_data(), new.get_data()))
            record.update(original_rva=old.VirtualAddress, candidate_rva=new.VirtualAddress,
                          original_virtual_bytes=old.Misc_VirtualSize, candidate_virtual_bytes=new.Misc_VirtualSize,
                          virtual_sizes_equal=old.Misc_VirtualSize == new.Misc_VirtualSize,
                          original_characteristics=old.Characteristics, candidate_characteristics=new.Characteristics,
                          characteristics_equal=old.Characteristics == new.Characteristics,
                          contains_file_bytes=bool(old.SizeOfRawData or new.SizeOfRawData))
        records.append(record)
    return records


def section_deltas(original, candidate):
    left = {s.Name.rstrip(b"\0").decode("ascii"): s.get_data() for s in original.sections}
    right = {s.Name.rstrip(b"\0").decode("ascii"): s.get_data() for s in candidate.sections}
    records = []
    for name in dict.fromkeys([*left, *right]):
        old, new = left.get(name, b""), right.get(name, b"")
        reconstructed = bytearray(old[:len(new)])
        reconstructed.extend(bytes(max(0, len(new) - len(reconstructed))))
        for offset in range(0, max(len(old), len(new)), 16):
            before, after = old[offset:offset + 16], new[offset:offset + 16]
            if before != after:
                records.append(dict(section=name, offset=offset, original_hex=before.hex(), candidate_hex=after.hex()))
                if after:
                    reconstructed[offset:offset + len(after)] = after
        if bytes(reconstructed) != new:
            raise ValueError("Raw delta does not reconstruct section: " + name)
    return records


def compare_resources(original, candidate):
    left, right = resource_payloads(original), resource_payloads(candidate)
    records = []
    for identity in sorted(left.keys() | right.keys(), key=lambda x: json.dumps(x)):
        old, new = left.get(identity), right.get(identity)
        record = dict(type=identity[0], name=identity[1], language=identity[2],
                      original_present=old is not None, candidate_present=new is not None,
                      original_form=old is not None and identity[0] == 10 and old.startswith(b"TPF0"),
                      original_icon=old is not None and identity[0] in (3, 14))
        if old is not None and new is not None:
            record.update(byte_difference(old, new))
        else:
            record.update(original_bytes=len(old) if old is not None else None,
                          candidate_bytes=len(new) if new is not None else None,
                          original_sha256=hashlib.sha256(old).hexdigest() if old is not None else None,
                          candidate_sha256=hashlib.sha256(new).hexdigest() if new is not None else None,
                          exact_bytes_equal=False)
        if identity[0] == 6 and not record["exact_bytes_equal"]:
            old_strings = string_table(old, identity[1]) if old is not None else {}
            new_strings = string_table(new, identity[1]) if new is not None else {}
            record["string_differences"] = [dict(id=i, original=old_strings.get(i), candidate=new_strings.get(i))
                for i in sorted(old_strings.keys() | new_strings.keys()) if old_strings.get(i) != new_strings.get(i)]
        records.append(record)
    return records


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--check", action="store_true")
    args = parser.parse_args()
    old_path, new_path = ROOT / "build/research/TSW.exe", WORK / "native/Tower.exe"
    if digest(old_path) != ORIGINAL_HASH:
        raise ValueError("Original executable pin changed")
    build = json.loads((WORK / "build-report.json").read_text())
    for row in build["inputs"]:
        if digest(ROOT / row["source"]) != row["source_sha256"]:
            raise ValueError("Rebuild changed Delphi source: " + row["source"])
    if digest(new_path) != build["builds"]["native"]["artifact_sha256"]:
        raise ValueError("Compiled executable differs from build report")
    old, new = pefile.PE(str(old_path)), pefile.PE(str(new_path))
    sections, resources = compare_sections(old, new), compare_resources(old, new)
    deltas = section_deltas(old, new)
    delta_text = "".join(json.dumps(row, separators=(",", ":")) + "\n" for row in deltas)
    delta_path = WORK / "binary-diff/raw-sections.diff.jsonl"
    if args.check:
        if delta_path.read_text() != delta_text:
            raise ValueError("Stale raw section delta artifact")
    else:
        delta_path.parent.mkdir(exist_ok=True)
        delta_path.write_text(delta_text)
    probe_path = WORK / "emulator/CoreRecoveryProbe.dll"
    if digest(probe_path) != build["builds"]["emulator"]["artifact_sha256"]:
        raise ValueError("Original-address core probe changed")
    probe = pefile.PE(str(probe_path))
    classify = probe.OPTIONAL_HEADER.ImageBase + next(s.address for s in probe.DIRECTORY_ENTRY_EXPORT.symbols
                                                    if s.name == b"ClassifyNeighbor")
    content = []
    linked_resources = resource_payloads(new)
    for name, address, length in (("ORIGINAL_MONSTERS", 0x489910, 528), ("ORIGINAL_RENDER_ORDER", 0x489B20, 121)):
        content.append(dict(name=name, original_address=address, candidate_location="RCDATA:" + name,
                            **byte_difference(old.get_data(address - old.OPTIONAL_HEADER.ImageBase, length),
                                              linked_resources[10, name, 0])))
    report = dict(schema_version=1, original_sha256=ORIGINAL_HASH, candidate_sha256=digest(new_path),
                  comparator_sha256=digest(Path(__file__)),
                  build_report_sha256=digest(WORK / "build-report.json"),
                  file_bytes=byte_difference(old_path.read_bytes(), new_path.read_bytes()),
                  headers=byte_difference(old_path.read_bytes()[:old.OPTIONAL_HEADER.SizeOfHeaders],
                                          new_path.read_bytes()[:new.OPTIONAL_HEADER.SizeOfHeaders]),
                  image_base=[old.OPTIONAL_HEADER.ImageBase, new.OPTIONAL_HEADER.ImageBase],
                  entry_point_rva=[old.OPTIONAL_HEADER.AddressOfEntryPoint, new.OPTIONAL_HEADER.AddressOfEntryPoint],
                  linker_timestamp=[old.FILE_HEADER.TimeDateStamp, new.FILE_HEADER.TimeDateStamp],
                  section_comparisons=sections, resource_payload_comparisons=resources,
                  raw_section_deltas=dict(path=str(delta_path.relative_to(ROOT)).replace("\\", "/"),
                                          sha256=digest(delta_path), changed_16_byte_rows=len(deltas),
                                          every_candidate_section_reconstructed=True),
                  relocated_game_content=content,
                  literal_core_code_witness=dict(method="ClassifyNeighbor", original_address=0x451C20,
                      candidate_address=classify, candidate_artifact=str(probe_path.relative_to(ROOT)).replace("\\", "/"),
                      **byte_difference(old.get_data(0x451C20 - old.OPTIONAL_HEADER.ImageBase, 282),
                                        probe.get_data(classify - probe.OPTIONAL_HEADER.ImageBase, 282))),
                  exact_shared_resource_payloads=sum(r["exact_bytes_equal"] for r in resources),
                  original_resources_missing=sum(r["original_present"] and not r["candidate_present"] for r in resources),
                  original_resources_changed=sum(r["original_present"] and r["candidate_present"] and not r["exact_bytes_equal"] for r in resources),
                  candidate_resources_added=sum(not r["original_present"] and r["candidate_present"] for r in resources),
                  string_slots_differing=sum(len(r.get("string_differences", [])) for r in resources),
                  nonempty_string_entries_differing=sum(bool(s["original"] or s["candidate"])
                      for r in resources for s in r.get("string_differences", [])),
                  whole_binary_identical=old_path.read_bytes() == new_path.read_bytes(),
                  semantic_equivalence_established=False, full_game_recovered=False,
                  limits=["No bytes are masked, including accepted IME operands and all UI code/resources.",
                          "Section-relative offsets are compared literally; shifted code/data and absolute/relative addresses can cause differences even when behavior agrees.",
                          "Zero raw bytes in BSS/TLS do not prove equal storage layout; virtual sizes are reported separately.",
                          "Resource payload equality is checked by exact type/name/language, independently of resource directory/RVA placement.",
                          "Raw differences are not classified as behavioral failures or accepted differences by this report. Unimplemented methods and runtime/UI dependencies remain outside whole-program equivalence."])
    content = json.dumps(report, indent=2) + "\n"
    target = ROOT / "delphi/binary-comparison-report.json"
    if args.check:
        if target.read_text() != content:
            raise ValueError("Stale binary comparison report")
    else:
        target.write_text(content)
    for record in sections:
        print(record["section"], "raw equal", record.get("exact_bytes_equal"),
              "sizes", record.get("original_bytes"), record.get("candidate_bytes"))
    print("Resources: identical", report["exact_shared_resource_payloads"], "changed", report["original_resources_changed"],
          "missing", report["original_resources_missing"], "added", report["candidate_resources_added"])


if __name__ == "__main__":
    main()
