"""Build/check an honest byte, function, root and callback accounting ledger.

This checks evidence completeness and freshness, not behavioral equivalence.
No Windows game execution, project mutation or compiler installation is needed.
"""
from pathlib import Path
import argparse
from collections import Counter, defaultdict
import hashlib
import json
import re
import struct
import sys
import bisect
from capstone import Cs, CS_ARCH_X86, CS_MODE_32, CS_OP_MEM, CS_OP_IMM

from account_original_program import Image, HASH, HEX, ROOT

OUTPUT = ROOT / 'reference/original/whole-program'
SOURCES = ['tools/account_original_program.py', 'tools/idr_knowledge_base.py',
           'tools/review_whole_program.py', 'tools/ghidra/RecoverWholeProgram.java',
           'tools/ghidra/InventoryWholeProgram.java', 'tools/fetch_idr_recognition.py',
           'cpp/tools/verify_original.py']


def sha(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()


def intervals(flags, category):
    start = 0
    while start < len(flags):
        stop = start + 1
        label = category(flags[start])
        while stop < len(flags) and category(flags[stop]) == label:
            stop += 1
        yield start, stop, label
        start = stop


def build(exe):
    image = Image(exe)
    structural = json.loads((OUTPUT / 'structural-inventory.json').read_text())
    snapshot = json.loads((OUTPUT / 'analysis-snapshot.json').read_text())
    manifest = json.loads((OUTPUT / 'decompiled/export-manifest.json').read_text())
    discovery = OUTPUT / 'discovery-snapshot.json'
    for report in [structural, snapshot, manifest]:
        if report['original_sha256'] != HASH:
            raise ValueError('Evidence uses a different original image')
    if structural['snapshot_sha256'] != sha(discovery):
        raise ValueError('Structural discovery snapshot is stale')
    if manifest['roots_sha256'] != sha(OUTPUT / 'roots.tsv') or manifest['metadata_sha256'] != sha(OUTPUT / 'metadata.tsv'):
        raise ValueError('Export roots/metadata are stale')
    if not manifest['root_closure_complete'] or structural['metadata_issues']:
        raise ValueError('Root discovery unfinished or structural metadata parsing failed')
    functions = {int(f['entry'], 16): f for f in snapshot['functions']}
    exports = {int(f['entry'], 16): f for f in manifest['exports']}
    if len(exports) != len(manifest['exports']) or exports.keys() != functions.keys():
        raise ValueError('Detected function/export entry mismatch')
    expected_files = {r[key] for r in manifest['exports'] for key in ['c', 'assembly']}
    actual_files = {p.name for p in (OUTPUT / 'decompiled').iterdir() if p.suffix in ['.c', '.asm']}
    if expected_files != actual_files:
        raise ValueError('Unlisted/missing C or assembly export files')
    flags, owned = bytearray(len(image.code)), bytearray(len(image.code))
    function_at_byte = [None] * len(image.code)
    for entry, function in functions.items():
        for a, b in function['body_ranges']:
            for i in range(max(int(a, 16), image.start) - image.start,
                           min(int(b, 16) + 1, image.end) - image.start):
                owned[i] = 1
                function_at_byte[i] = entry
    for key, bit in [('instruction_ranges', 1), ('defined_data_ranges', 2)]:
        for a, b in snapshot[key]:
            for i in range(max(int(a, 16), image.start) - image.start,
                           min(int(b, 16) + 1, image.end) - image.start):
                flags[i] |= bit
    for region in structural['metadata_regions']:
        for i in range(int(region['start'], 16) - image.start, int(region['end_exclusive'], 16) - image.start):
            flags[i] |= 4
    cs = Cs(CS_ARCH_X86, CS_MODE_32); cs.detail = True
    assembly_pattern = re.compile(r'^([0-9a-f]{8})\s+([0-9a-f]+)\s+', re.MULTILINE)
    complete_assembly = (OUTPUT / 'CODE.asm').read_text()
    instruction_addresses, complete_bytes = [], set()
    for match in assembly_pattern.finditer(complete_assembly):
        address, blob = int(match[1], 16), bytes.fromhex(match[2])
        if not image.valid(address, len(blob)) or image.code[address - image.start:address - image.start + len(blob)] != blob:
            raise ValueError('Complete CODE assembly differs from original')
        instruction_addresses.append(address)
        complete_bytes.update(range(address - image.start, address - image.start + len(blob)))
    if complete_bytes != {i for i, flag in enumerate(flags) if flag & 1}:
        raise ValueError('Complete CODE assembly misses/adds decoded instruction bytes')
    switches, switch_sites = [], {}
    for export in manifest['exports']:
        for switch in export.get('switch_tables', []):
            site = int(switch['site'], 16)
            cases = [int(a, 16) for a in switch['cases']]
            switch_sites[site] = cases
            instruction = next(cs.disasm(image.code[site - image.start:site - image.start + 15], site))
            row = dict(owner=export['entry'], **switch, table_validation='unresolved-layout', data_regions=[])
            if len(instruction.operands) == 1 and instruction.operands[0].type == CS_OP_MEM and instruction.operands[0].mem.scale == 4:
                table = instruction.operands[0].mem.disp
                index = bisect.bisect_left(instruction_addresses, site)
                previous = [next(cs.disasm(image.code[a - image.start:a - image.start + 15], a))
                            for a in instruction_addresses[max(0, index - 5):index]]
                default_guard = any(i.mnemonic == 'ja' and i.operands[0].type == CS_OP_IMM and i.operands[0].imm == cases[-1] for i in previous)
                remap = None
                if previous and previous[-1].mnemonic == 'mov':
                    candidates = [o.mem.disp for o in previous[-1].operands if o.type == CS_OP_MEM and o.size == 1 and image.valid(o.mem.disp)]
                    if candidates: remap = candidates[0]
                for count in [len(cases), len(cases) - 1] if default_guard else [len(cases)]:
                    if not count: continue
                    indexes = image.code[remap - image.start:remap - image.start + count] if remap is not None else list(range(count))
                    size = (max(indexes) + 1) * 4
                    if not image.valid(table, size): continue
                    actual = [image.integer(table + value * 4) for value in indexes]
                    if actual != cases[:count]: continue
                    row['table_validation'] = 'original-bytes-match-decompiler-cases'
                    row['data_regions'].append(dict(start=HEX(table), end_exclusive=HEX(table + size)))
                    if remap is not None:
                        row['data_regions'].append(dict(start=HEX(remap), end_exclusive=HEX(remap + count)))
                    for region in row['data_regions']:
                        for i in range(int(region['start'], 16) - image.start, int(region['end_exclusive'], 16) - image.start): flags[i] |= 8
                    break
            switches.append(row)
    def category(flag):
        if flag & 4: return 'metadata-instruction-conflict' if flag & 1 else 'validated-delphi-metadata'
        if flag & 8: return 'switch-data-instruction-conflict' if flag & 1 else 'validated-switch-data'
        if flag & 1: return 'decoded-instruction'
        if flag & 2: return 'defined-data-unreviewed'
        return 'unresolved'
    byte_rows, counts = [], Counter()
    for a, b, label in intervals(flags, category):
        row = dict(start=HEX(image.start + a), end_exclusive=HEX(image.start + b),
                   bytes=b - a, classification=label)
        if label in ['unresolved', 'metadata-instruction-conflict']:
            blob = image.code[a:b]
            row['sha256'] = hashlib.sha256(blob).hexdigest()
            row['sample_hex'] = blob[:32].hex()
            row['zero_bytes'] = blob.count(0)
        byte_rows.append(row); counts[label] += b - a
    if sum(counts.values()) != len(image.code):
        raise ValueError('CODE byte partition has a gap or overlap')
    def location(address):
        address = int(address, 16) if isinstance(address, str) else address
        if address in functions:
            return dict(status='exported-entry', entry=HEX(address))
        if image.valid(address):
            owner = function_at_byte[address - image.start]
            if owner is not None:
                return dict(status='interior-or-shared-entry', entry=HEX(owner))
            return dict(status=category(flags[address - image.start]))
        return dict(status='external-to-CODE')
    names = defaultdict(list)
    for match in structural['runtime_signature_matches']:
        for address in match['addresses']:
            names[int(address, 16)].append(dict(module=match['module'], name=match['name'],
                fixed_bytes=match['fixed_bytes'], shape_addresses=len(match['addresses']), size=match['size']))
    function_rows = []
    assembly_pattern = re.compile(r'^([0-9a-f]{8})\s+([0-9a-f]+)\s+', re.MULTILINE)
    evidence_files = {}
    exported_asm_bytes = set()
    for entry, function in sorted(functions.items()):
        export = exports[entry]
        for key in ['c', 'assembly']:
            path = OUTPUT / 'decompiled' / export[key]
            expected = export['c_sha256' if key == 'c' else 'assembly_sha256']
            if sha(path) != expected:
                raise ValueError(f'Export changed: {path.name}')
            evidence_files[str(path.relative_to(ROOT)).replace('\\', '/')] = expected
        c = (OUTPUT / 'decompiled' / export['c']).read_text()
        assembly = (OUTPUT / 'decompiled' / export['assembly']).read_text()
        decoded_bytes = 0
        decoded_count = 0
        for match in assembly_pattern.finditer(assembly):
            address = int(match[1], 16)
            blob = bytes.fromhex(match[2])
            if not image.valid(address, len(blob)) or image.code[address - image.start:address - image.start + len(blob)] != blob:
                raise ValueError(f'Assembly differs from pinned original at {HEX(address)}')
            if not any(int(a, 16) <= address and address + len(blob) - 1 <= int(b, 16) for a, b in function['body_ranges']):
                raise ValueError(f'Assembly outside function body at {HEX(address)}')
            exported_asm_bytes.update(range(address - image.start, address - image.start + len(blob)))
            decoded_bytes += len(blob); decoded_count += 1
        if decoded_bytes != export['instruction_bytes'] or decoded_count != export['instruction_count']:
            raise ValueError('Export instruction accounting differs')
        function_rows.append(dict(**function, export_status=export['status'],
            c='decompiled/' + export['c'], assembly='decompiled/' + export['assembly'],
            runtime_name_candidates=names[entry],
            decompiler_flow_conflicts=export.get('flow_conflicts', []),
            warnings=[line.strip() for line in c.splitlines() if 'WARNING:' in line]))
    direct = []
    for call in snapshot['direct_calls']:
        for target in call['targets']:
            direct.append(dict(site=call['site'], owner=call.get('owner'), target=target,
                instruction=call['instruction'],
                encoding_kind='call' if call['instruction'].startswith('CALL ') else 'tail-or-overridden-flow',
                **location(target)))
    roots = [dict(**root, location=location(root['address'])) for root in structural['entry_roots']]
    import_at = {item.address: dict(dll=module.dll.decode('ascii'), name=item.name.decode('ascii') if item.name else None, ordinal=item.ordinal)
                 for module in image.pe.DIRECTORY_ENTRY_IMPORT for item in module.imports}
    indirect = []
    for row in snapshot['indirect_transfers']:
        site = int(row['site'], 16)
        instruction = next(cs.disasm(image.code[site - image.start:site - image.start + 15], site))
        iat = next((o.mem.disp for o in instruction.operands if o.type == CS_OP_MEM and not o.mem.base and not o.mem.index and o.mem.disp in import_at), None)
        if iat is not None:
            indirect.append(dict(**row, resolution='named-Windows-import-boundary', imported=import_at[iat]))
        elif site in switch_sites:
            indirect.append(dict(**row, resolution='recovered-static-switch-candidates', cases=[HEX(a) for a in switch_sites[site]]))
        else:
            indirect.append(dict(**row, resolution='unresolved-target-or-runtime-delivery'))
    refs = [dict(**row, location=location(row['target']), runtime_name_candidates=names[int(row['target'], 16)])
            for row in structural['materialized_code_candidates']]
    # Raw code pointers are an additional candidate list, not function seeds.
    pointers = []
    for offset in range(0, len(image.code) - 3, 4):
        if flags[offset] & 1: continue
        target = struct.unpack_from('<I', image.code, offset)[0]
        if not image.valid(target): continue
        if target in functions or target in names:
            pointers.append(dict(site=HEX(image.start + offset), target=HEX(target),
                source_classification=category(flags[offset]), location=location(target),
                limits='Aligned pointer candidate; registration, use and reachability unproven.'))
    sections, file_intervals = [], []
    header_size = image.pe.OPTIONAL_HEADER.SizeOfHeaders
    file_intervals.append((0, header_size, 'PE-headers'))
    for section in image.pe.sections:
        name = section.Name.rstrip(b'\0').decode('ascii')
        start = image.base + section.VirtualAddress
        virtual, raw = section.Misc_VirtualSize, section.SizeOfRawData
        sections.append(dict(name=name, start=HEX(start), virtual_bytes=virtual, raw_bytes=raw,
            raw_offset=section.PointerToRawData, file_padding_bytes=max(0, raw - virtual),
            zero_fill_bytes=max(0, virtual - raw), executable=bool(section.Characteristics & 0x20000000),
            limits='CODE has per-byte ledger; other sections have PE structure inventory only. Writable memory can hold dynamically generated code.'))
        if raw: file_intervals.append((section.PointerToRawData, section.PointerToRawData + raw, name))
    cursor = 0; file_rows = []
    for a, b, label in sorted(file_intervals):
        if a < cursor or b > len(image.raw): raise ValueError('Overlapping/out-of-file PE section')
        if a > cursor: file_rows.append(dict(start=cursor, end_exclusive=a, classification='unassigned-file-gap-or-overlay'))
        file_rows.append(dict(start=a, end_exclusive=b, classification=label)); cursor = b
    if cursor < len(image.raw):
        file_rows.append(dict(start=cursor, end_exclusive=len(image.raw), classification='unassigned-file-gap-or-overlay'))
    imports = [dict(dll=module.dll.decode('ascii'), name=item.name.decode('ascii') if item.name else None,
                    ordinal=item.ordinal, iat=HEX(item.address))
               for module in image.pe.DIRECTORY_ENTRY_IMPORT for item in module.imports]
    resources = []
    def resource_walk(entries, ancestry):
        for item in entries:
            key = str(item.name) if item.name else item.id
            if hasattr(item, 'directory'): resource_walk(item.directory.entries, ancestry + [key])
            else:
                data = item.data.struct
                resources.append(dict(path=ancestry + [key], rva=HEX(data.OffsetToData), bytes=data.Size,
                    sha256=hashlib.sha256(image.pe.get_data(data.OffsetToData, data.Size)).hexdigest()))
    resource_walk(image.pe.DIRECTORY_ENTRY_RESOURCE.entries, [])
    old = json.loads((ROOT / 'reference/original/presentation/effect-inventory.json').read_text())
    old_targets = [dict(address=a, **location(a)) for a in old['direct_targets_without_exported_entry']]
    dependencies = [str(discovery.relative_to(ROOT)).replace('\\', '/'),
        'reference/original/whole-program/analysis-snapshot.json',
        'reference/original/whole-program/CODE.asm',
        'reference/original/whole-program/structural-inventory.json',
        'reference/original/whole-program/roots.tsv', 'reference/original/whole-program/metadata.tsv',
        'reference/original/whole-program/decompiled/export-manifest.json',
        'reference/original/presentation/effect-inventory.json'] + SOURCES
    report = dict(original_sha256=HASH, original_file_bytes=len(image.raw),
        evidence_sha256={path: sha(ROOT / path) for path in dependencies}, export_evidence_sha256=evidence_files,
        code_virtual_bytes=len(image.code), code_raw_padding_bytes=int(snapshot['code_end'], 16) + 1 - image.end,
        byte_counts=dict(counts), byte_regions=byte_rows, functions=function_rows,
        entry_roots=roots, direct_calls=direct, indirect_transfers=indirect,
        code_address_references=refs, aligned_code_pointer_candidates=pointers,
        switch_tables=switches, boundary_repairs=manifest['boundary_repairs'],
        sections=sections, file_regions=file_rows, imports=imports, resources=resources,
        tls_directory_present=hasattr(image.pe, 'DIRECTORY_ENTRY_TLS'),
        exported_pe_entries=[HEX(item.address + image.base) for item in getattr(getattr(image.pe, 'DIRECTORY_ENTRY_EXPORT', None), 'symbols', [])],
        data_directories=[dict(name=d.name, rva=HEX(d.VirtualAddress), bytes=d.Size) for d in image.pe.OPTIONAL_HEADER.DATA_DIRECTORY if d.Size],
        previous_unexported_targets=old_targets,
        summary=dict(detected_functions=len(functions), failed_decompilations=manifest['failed_decompilations'],
            functions_with_decompiler_warnings=sum(bool(f['warnings']) for f in function_rows),
            structural_roots=len(roots), root_locations=dict(Counter(r['location']['status'] for r in roots)),
            direct_call_sites=len(snapshot['direct_calls']), direct_target_locations=dict(Counter(r['status'] for r in direct)),
            direct_call_instruction_sites=sum(row['instruction'].startswith('CALL ') for row in snapshot['direct_calls']),
            registered_exception_sites=len(structural.get('exception_registrations', [])),
            indirect_transfer_sites=len(indirect), code_address_reference_sites=len(snapshot['code_address_references']),
            independent_code_operand_candidates=len(refs),
            indirect_resolutions=dict(Counter(r['resolution'] for r in indirect)),
            validated_switch_tables=sum(r['table_validation'] == 'original-bytes-match-decompiler-cases' for r in switches),
            switch_tables=len(switches),
            decompiler_flow_conflicts=sum(len(r.get('flow_conflicts', [])) for r in manifest['exports']),
            complete_assembly_instruction_bytes=len(complete_bytes),
            instruction_bytes_with_assembly_export=len(exported_asm_bytes),
            decoded_instruction_bytes_outside_functions=sum(bool(flag & 1) and not owned[i] for i, flag in enumerate(flags)),
            previous_target_locations=dict(Counter(r['status'] for r in old_targets))),
        limits='This partitions every virtual CODE byte and PE file byte, retaining unresolved bytes, decode/metadata conflicts, indirect transfers and pointer candidates. Detected-function decompilation is not exhaustive code discovery, runtime-source recovery, purity, translation, behavioral equivalence or Windows scheduling coverage.')
    return report


def render(report):
    summary = report['summary']
    text = '# Whole-program accounting index\n\n'
    text += f"Pinned original SHA-256: `{HASH}`.\n\n"
    text += (f"{summary['detected_functions']:,} detected functions have C-like and assembly exports; "
             f"{summary['failed_decompilations']} failed decompilations. "
             "Decompilation success does not mean the function was translated or behaviorally verified.\n\n")
    text += '| CODE byte classification | Virtual bytes |\n|---|---:|\n'
    for kind, count in report['byte_counts'].items(): text += f'| {kind} | {count:,} |\n'
    text += (f"\nThese add to {report['code_virtual_bytes']:,} virtual CODE bytes; "
             f"{report['code_raw_padding_bytes']} raw padding bytes are separate. "
             "Unresolved bytes and metadata/instruction conflicts remain open findings.\n\n"
             "See [REVIEW.md](REVIEW.md) for conclusions, [ledger.json](ledger.json) for the complete ledger, "
             "[structural-inventory.json](structural-inventory.json) for classes/properties/signatures, "
             "and [byte-ledger.tsv](byte-ledger.tsv) for the byte partition. "
             "The ledger also inventories every PE section/file byte, import and resource.\n\n"
             '| Entry | Ghidra name | Runtime name candidates | C-like | Assembly |\n|---|---|---|---|---|\n')
    for function in report['functions']:
        names = ', '.join(sorted(set(f"{r['module']}.{r['name']}" for r in function['runtime_name_candidates'])))
        text += f"| `{function['entry']}` | `{function['name']}` | {names} | [{function['export_status']}]({function['c']}) | [assembly]({function['assembly']}) |\n"
    byte_tsv = 'start\tend_exclusive\tbytes\tclassification\n' + ''.join(
        f"{r['start']}\t{r['end_exclusive']}\t{r['bytes']}\t{r['classification']}\n" for r in report['byte_regions'])
    return {'ledger.json': json.dumps(report, indent=2) + '\n', 'INDEX.md': text, 'byte-ledger.tsv': byte_tsv}


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--exe', type=Path, default=ROOT / 'build/research/TSW.exe')
    parser.add_argument('--check', action='store_true')
    args = parser.parse_args()
    report = build(args.exe)
    outputs = render(report)
    if args.check:
        stale = [name for name, content in outputs.items() if not (OUTPUT / name).exists() or (OUTPUT / name).read_text() != content]
        if stale: raise ValueError('Whole-program accounting stale: ' + ', '.join(stale))
    else:
        for name, content in outputs.items(): (OUTPUT / name).write_text(content, encoding='utf-8')
    print(json.dumps(dict(checked=args.check, **report['summary'], byte_counts=report['byte_counts']), indent=2))
    return 0


if __name__ == '__main__':
    sys.exit(main())
