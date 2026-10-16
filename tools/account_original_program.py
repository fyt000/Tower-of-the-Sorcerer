"""Account for the pinned whole image with explicit unresolved regions.

Uses a Ghidra snapshot, structural Delphi-2 metadata, and public IDR signatures.
No original game execution, binary patching, or licensed Delphi source is needed.
"""
from pathlib import Path
import argparse
import hashlib
import json
import re
import struct
from collections import Counter, defaultdict

import pefile
from capstone import Cs, CS_ARCH_X86, CS_MODE_32
from capstone.x86_const import X86_OP_IMM, X86_OP_MEM, X86_OP_REG, X86_REG_FS, X86_REG_ESP
from idr_knowledge_base import KnowledgeBase, find_matches, literal_runs

ROOT = Path(__file__).resolve().parents[1]
OUTPUT = ROOT / 'reference/original/whole-program'
HASH = '41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779'
HEX = lambda address: f'0x{address:08x}'


class Image:
    def __init__(self, path):
        self.raw = path.read_bytes()
        if hashlib.sha256(self.raw).hexdigest() != HASH:
            raise ValueError('Original executable hash mismatch')
        self.pe = pefile.PE(data=self.raw)
        self.base = self.pe.OPTIONAL_HEADER.ImageBase
        self.data = self.pe.get_memory_mapped_image()
        section = next(s for s in self.pe.sections if s.Name.startswith(b'CODE'))
        self.start = self.base + section.VirtualAddress
        self.end = self.start + section.Misc_VirtualSize
        self.code = self.data[self.start - self.base:self.end - self.base]

    def valid(self, address, size=1):
        return self.start <= address and address + size <= self.end

    def integer(self, address, fmt='<I'):
        if not self.valid(address, struct.calcsize(fmt)):
            raise ValueError(f'Address outside CODE: {HEX(address)}')
        return struct.unpack_from(fmt, self.data, address - self.base)[0]

    def short_string(self, address):
        if not self.valid(address):
            raise ValueError('Invalid short string address')
        size = self.integer(address, '<B')
        if not self.valid(address + 1, size):
            raise ValueError('Truncated short string')
        return self.data[address - self.base + 1:address - self.base + 1 + size].decode('ascii')


def class_metadata(image):
    classes, regions, issues = {}, [], []

    def region(start, end, kind, evidence):
        if image.valid(start, end - start):
            regions.append(dict(start=HEX(start), end_exclusive=HEX(end), kind=kind, evidence=evidence))

    # Delphi-2 layout is independently corroborated by TControl instance size
    # and relocation-masked system signatures. Do not guess another layout.
    marker = b'\x07\x08TControl'
    pos = image.data.find(marker)
    control_vmt = image.integer(image.base + pos + len(marker)) if pos >= 0 else 0
    if not control_vmt or image.integer(control_vmt - 0x18) != 0xa8:
        raise ValueError('Delphi-2 TControl layout fingerprint absent')

    def candidate(vmt):
        if not image.valid(vmt - 0x34, 0x34):
            return None
        name_pointer = image.integer(vmt - 0x1c)
        try:
            name = image.short_string(name_pointer)
        except (ValueError, UnicodeError):
            return None
        if not re.fullmatch(r'[A-Za-z_][A-Za-z_0-9]{1,80}', name):
            return None
        size, parent = image.integer(vmt - 0x18), image.integer(vmt - 0x14)
        if not 0 < size < 0x10000 or (parent and not image.valid(parent)):
            return None
        pointers = [image.integer(vmt + offset) for offset in [-0x30, -0x2c, -0x28, -0x24, -0x20]]
        if not all(pointer == 0 or image.valid(pointer) for pointer in pointers):
            return None
        if not parent and name != 'TObject':
            return None
        return dict(vmt=HEX(vmt), name=name, name_pointer=HEX(name_pointer), instance_size=size,
                    parent=HEX(parent) if parent else None,
                    initialization_table=HEX(pointers[0]) if pointers[0] else None,
                    type_info=HEX(pointers[1]) if pointers[1] else None,
                    field_table=HEX(pointers[2]) if pointers[2] else None,
                    published_table=HEX(pointers[3]) if pointers[3] else None,
                    dynamic_table=HEX(pointers[4]) if pointers[4] else None)

    # Every aligned class-name slot is considered; ancestry must close to TObject.
    candidates = {address: row for address in range(image.start + 0x34, image.end, 4)
                  if (row := candidate(address))}
    todo = dict(candidates)
    while todo:
        added = []
        for address, row in todo.items():
            if row['parent'] is None or int(row['parent'], 16) in classes:
                classes[address] = row
                added.append(address)
        if not added:
            break
        for address in added:
            del todo[address]
    for address, row in todo.items():
        issues.append(dict(kind='unclosed-class-ancestry', **row))

    for vmt, row in sorted(classes.items()):
        name = row['name']
        row['virtual_entries'], row['dynamic_entries'], row['published_entries'] = [], [], []
        row['fields'], row['properties'], row['managed_fields'] = [], [], []
        # Fixed negative lifecycle slots and contiguous positive VMT pointers.
        for offset in [-0x10, -0xc, -8, -4]:
            target = image.integer(vmt + offset)
            if image.valid(target):
                row['virtual_entries'].append(dict(offset=offset, address=HEX(target)))
        boundary = min([int(row[key], 16) for key in ['initialization_table', 'type_info', 'field_table',
                         'published_table', 'dynamic_table', 'name_pointer'] if row[key] and int(row[key], 16) >= vmt]
                       + [image.end])
        cursor = vmt
        while cursor + 4 <= boundary and cursor < vmt + 2048 and image.valid(image.integer(cursor)):
            row['virtual_entries'].append(dict(offset=cursor - vmt, address=HEX(image.integer(cursor))))
            cursor += 4
        region(vmt - 0x34, cursor, 'class-vmt', name)
        name_pointer = int(row['name_pointer'], 16)
        region(name_pointer, name_pointer + 1 + len(name), 'class-name', name)
        table = row['published_table']
        if table:
            start = cursor = int(table, 16)
            count = image.integer(cursor, '<H'); cursor += 2
            try:
                if count > 1000:
                    raise ValueError('Implausible published count')
                for _ in range(count):
                    length = image.integer(cursor, '<H')
                    target = image.integer(cursor + 2)
                    method = image.short_string(cursor + 6)
                    if length != 7 + len(method) or not image.valid(target):
                        raise ValueError('Invalid published entry')
                    row['published_entries'].append(dict(name=method, address=HEX(target), record=HEX(cursor)))
                    cursor += length
                region(start, cursor, 'published-method-table', name)
            except (ValueError, UnicodeError, struct.error) as error:
                issues.append(dict(kind='published-table-parse', owner=name, address=table, error=str(error)))
        table = row['dynamic_table']
        if table:
            start = int(table, 16); count = image.integer(start, '<H')
            if count > 1000 or not image.valid(start, 2 + 6 * count):
                issues.append(dict(kind='dynamic-table-parse', owner=name, address=table))
            else:
                for i in range(count):
                    target = image.integer(start + 2 + 2 * count + 4 * i)
                    identifier = image.integer(start + 2 + 2 * i, '<H')
                    if not image.valid(target):
                        issues.append(dict(kind='dynamic-target', owner=name, target=HEX(target)))
                    else:
                        row['dynamic_entries'].append(dict(identifier=identifier, address=HEX(target)))
                region(start, start + 2 + 6 * count, 'dynamic-method-table', name)
        table = row['field_table']
        if table:
            start = cursor = int(table, 16)
            try:
                count = image.integer(cursor, '<H')
                types = image.integer(cursor + 2)
                type_count = image.integer(types, '<H')
                if count > 1000 or type_count > 1000:
                    raise ValueError('Implausible field/type count')
                region(types, types + 2 + 4 * type_count, 'field-class-table', name)
                cursor += 6
                for _ in range(count):
                    offset = image.integer(cursor)
                    index = image.integer(cursor + 4, '<H')
                    field_name = image.short_string(cursor + 6)
                    if index >= type_count or offset + 4 > row['instance_size']:
                        raise ValueError('Invalid field type index/offset')
                    target_vmt = image.integer(types + 2 + 4 * index)
                    if target_vmt not in classes:
                        raise ValueError('Unknown published field class')
                    row['fields'].append(dict(name=field_name, offset=offset,
                        class_vmt=HEX(target_vmt), class_name=classes[target_vmt]['name']))
                    cursor += 7 + len(field_name)
                region(start, cursor, 'published-field-table', name)
            except (ValueError, UnicodeError, struct.error) as error:
                issues.append(dict(kind='field-table-parse', owner=name, address=table, error=str(error)))
        table = row['initialization_table']
        if table:
            start = int(table, 16)
            try:
                kind = image.integer(start, '<B')
                type_name = image.short_string(start + 1)
                cursor = start + 2 + len(type_name)
                data_size, count = image.integer(cursor), image.integer(cursor + 4)
                cursor += 8
                if kind != 14 or count > 1000:
                    raise ValueError('Unsupported managed-field record')
                for _ in range(count):
                    target = image.integer(cursor)
                    offset = image.integer(cursor + 4)
                    if not image.valid(target) or offset >= row['instance_size']:
                        raise ValueError('Invalid managed-field target/offset')
                    row['managed_fields'].append(dict(type_info=HEX(target), offset=offset))
                    cursor += 8
                row['managed_record_data_size'] = data_size
                region(start, cursor, 'managed-field-table', name)
            except (ValueError, UnicodeError, struct.error) as error:
                issues.append(dict(kind='managed-table-parse', owner=name, address=table, error=str(error)))
        table = row['type_info']
        if table:
            start = int(table, 16)
            try:
                if image.integer(start, '<B') != 7 or image.short_string(start + 1) != name:
                    raise ValueError('Class RTTI name/kind mismatch')
                cursor = start + 2 + len(name)
                if image.integer(cursor) != vmt:
                    raise ValueError('Class RTTI VMT mismatch')
                parent_type = image.integer(cursor + 4)
                inherited_count = image.integer(cursor + 8, '<H')
                unit = image.short_string(cursor + 10)
                cursor += 11 + len(unit)
                count = image.integer(cursor, '<H'); cursor += 2
                if count > inherited_count or count > 1000:
                    raise ValueError('Implausible class property count')
                row['unit_name'], row['parent_type_info'] = unit, HEX(parent_type) if parent_type else None
                for _ in range(count):
                    prop_name = image.short_string(cursor + 26)
                    prop = dict(name=prop_name, type_info=HEX(image.integer(cursor)),
                                record=HEX(cursor), accessors={})
                    for key, displacement in [('get', 4), ('set', 8), ('stored', 12)]:
                        value = image.integer(cursor + displacement)
                        accessor = dict(raw=HEX(value))
                        if image.valid(value):
                            accessor.update(kind='direct-method', address=HEX(value))
                        elif value >> 24 == 0xff:
                            accessor.update(kind='field', offset=value & 0xffffff)
                        elif value >> 24 == 0xfe:
                            offset = value & 0xffffff
                            if offset & 0x800000: offset -= 0x1000000
                            accessor.update(kind='virtual-slot', offset=offset)
                            if image.valid(vmt + offset, 4) and image.valid(image.integer(vmt + offset)):
                                accessor['address'] = HEX(image.integer(vmt + offset))
                        else:
                            accessor['kind'] = 'constant-or-unresolved'
                        prop['accessors'][key] = accessor
                    row['properties'].append(prop)
                    cursor += 27 + len(prop_name)
                region(start, cursor, 'class-rtti-and-properties', name)
            except (ValueError, UnicodeError, struct.error) as error:
                issues.append(dict(kind='class-rtti-parse', owner=name, address=table, error=str(error)))
    return list(classes.values()), regions, issues


def signatures(image, directory):
    result, scores = [], []
    for version in range(2, 8):
        kb = KnowledgeBase(directory / f'syskb{version}.bin')
        hits = []
        for proc in kb.procedures():
            fixed = sum(len(run) for _, run in literal_runs(proc['dump'], proc['mask']))
            if fixed < 32:
                continue
            positions = find_matches(image.code, proc, 32)
            if len(positions) == 1:
                hits.append(dict(name=proc['name'], address=HEX(image.start + positions[0]), fixed_bytes=fixed))
        scores.append(dict(version=version, unique_shape_matches=len(hits), matches=hits))
    kb = KnowledgeBase(directory / 'kb2.bin')
    for proc in kb.procedures():
        fixed = sum(len(run) for _, run in literal_runs(proc['dump'], proc['mask']))
        positions = find_matches(image.code, proc)
        if positions:
            result.append(dict(index=proc['index'], module=proc['module'], name=proc['name'],
                               size=len(proc['dump']), fixed_bytes=fixed, fixups=proc['fixups'],
                               addresses=[HEX(image.start + pos) for pos in positions],
                               evidence='relocation-masked byte shape; identity/effects require corroboration'))
    return result, scores


def referenced_types(image, classes, regions):
    """Only parse independently referenced Delphi-2 RTTI, never a byte sweep."""
    known_classes = {int(c['type_info'], 16) for c in classes if c['type_info']}
    todo = {int(p['type_info'], 16) for c in classes for p in c['properties']}
    todo.update(int(p['type_info'], 16) for c in classes for p in c['managed_fields'])
    result, issues, seen = [], [], set()
    while todo:
        address = todo.pop()
        if address in seen or address in known_classes: continue
        seen.add(address)
        try:
            kind = image.integer(address, '<B')
            name = image.short_string(address + 1)
            cursor = address + 2 + len(name)
            row = dict(address=HEX(address), kind=kind, name=name)
            if kind in [1, 2, 3]:
                ordinal = image.integer(cursor, '<B')
                minimum = image.integer(cursor + 1, '<i')
                maximum = image.integer(cursor + 5, '<i')
                cursor += 9
                row.update(ordinal_kind=ordinal, minimum=minimum, maximum=maximum)
                if kind == 3:
                    base = image.integer(cursor); cursor += 4
                    row['base_type'] = HEX(base)
                    if base == address:
                        if not 0 <= maximum - minimum <= 1000: raise ValueError('Implausible enum bounds')
                        values = []
                        for _ in range(maximum - minimum + 1):
                            value = image.short_string(cursor); values.append(value); cursor += 1 + len(value)
                        row['values'] = values
                    elif image.valid(base): todo.add(base)
                    else: raise ValueError('Invalid enum base')
            elif kind == 5:
                row['max_length'] = image.integer(cursor, '<B'); cursor += 1
            elif kind == 6:
                row['ordinal_kind'] = image.integer(cursor, '<B')
                base = image.integer(cursor + 1); cursor += 5
                row['base_type'] = HEX(base); todo.add(base)
            elif kind == 8:
                method, count = image.integer(cursor, '<B'), image.integer(cursor + 1, '<B'); cursor += 2
                if method > 7 or count > 50: raise ValueError('Implausible event signature')
                params = []
                for _ in range(count):
                    flags = image.integer(cursor, '<B'); cursor += 1
                    param_name = image.short_string(cursor); cursor += 1 + len(param_name)
                    type_name = image.short_string(cursor); cursor += 1 + len(type_name)
                    params.append(dict(flags=flags, name=param_name, type_name=type_name))
                row.update(method_kind=method, parameters=params)
                if method in [1, 5, 7]:
                    row['return_type'] = image.short_string(cursor); cursor += 1 + len(row['return_type'])
            elif kind not in [10, 11, 12]:
                raise ValueError('Unimplemented referenced RTTI kind')
            if not image.valid(address, cursor - address): raise ValueError('Truncated RTTI')
            regions.append(dict(start=HEX(address), end_exclusive=HEX(cursor), kind='referenced-type-rtti', evidence=name))
            result.append(row)
        except (ValueError, UnicodeError, struct.error) as error:
            issues.append(dict(kind='referenced-rtti-parse', address=HEX(address), error=str(error)))
    return sorted(result, key=lambda r: r['address']), issues


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--exe', type=Path, default=ROOT / 'build/research/TSW.exe')
    parser.add_argument('--snapshot', type=Path, default=OUTPUT / 'discovery-snapshot.json')
    parser.add_argument('--kb-dir', type=Path, default=ROOT / 'build/research/idr')
    parser.add_argument('--check', action='store_true')
    args = parser.parse_args()
    image = Image(args.exe)
    snapshot = json.loads(args.snapshot.read_text())
    if snapshot['original_sha256'] != HASH:
        raise ValueError('Snapshot image differs')
    classes, regions, issues = class_metadata(image)
    types, type_issues = referenced_types(image, classes, regions)
    issues.extend(type_issues)
    matches, versions = signatures(image, args.kb_dir)
    roots = defaultdict(list)
    for cls in classes:
        for kind in ['virtual', 'dynamic', 'published']:
            for method in cls[kind + '_entries']:
                roots[int(method['address'], 16)].append(f"{cls['name']}:{kind}:{method.get('name', method.get('offset', method.get('identifier')))}")
        for prop in cls['properties']:
            for key, accessor in prop['accessors'].items():
                if 'address' in accessor:
                    roots[int(accessor['address'], 16)].append(f"{cls['name']}:property:{prop['name']}:{key}")
    entry = image.base + image.pe.OPTIONAL_HEADER.AddressOfEntryPoint
    roots[entry].append('PE-entry')
    startup = []
    for instruction in Cs(CS_ARCH_X86, CS_MODE_32).disasm(image.data[entry - image.base:entry - image.base + 512], entry):
        if instruction.mnemonic == 'ret':
            break
        if instruction.mnemonic == 'call' and instruction.op_str.startswith('0x'):
            target = int(instruction.op_str, 16)
            roots[target].append('startup-direct-call')
            startup.append(dict(site=HEX(instruction.address), target=HEX(target)))
    for call in snapshot['direct_calls']:
        for target in call['targets']:
            if image.valid(int(target, 16)):
                roots[int(target, 16)].append('direct-call:' + call['site'])
    # A signature alone is not a seed. A decoded instruction independently
    # materializing that address plus a matching byte shape supports recovering
    # a callback candidate; neither fact proves its registration or invocation.
    signature_addresses = {int(address, 16) for match in matches for address in match['addresses']}
    seh_helpers = {int(address, 16): match['name'] for match in matches
                   if match['name'] in ['@HandleAnyException', '@HandleFinally'] for address in match['addresses']}
    exception_registrations = []
    seh_decoder = Cs(CS_ARCH_X86, CS_MODE_32); seh_decoder.detail = True
    materializations = {(r['site'], r['target']): dict(r) for r in snapshot['code_address_references']}
    # Independently inspect decoded operands too: -noanalysis recovery does not
    # necessarily install every Ghidra data-reference annotation.
    for a, b in snapshot['instruction_ranges']:
        start, end = int(a, 16), min(int(b, 16) + 1, image.end)
        for instruction in seh_decoder.disasm(image.code[start - image.start:end - image.start], start):
            if instruction.mnemonic.startswith('j') or instruction.mnemonic == 'call': continue
            for operand in instruction.operands:
                target = operand.imm if operand.type == X86_OP_IMM else operand.mem.disp if operand.type == X86_OP_MEM else 0
                if image.valid(target):
                    materializations.setdefault((HEX(instruction.address), HEX(target)), dict(
                        site=HEX(instruction.address), target=HEX(target), kind='decoded-operand-candidate'))
    materializations = sorted(materializations.values(), key=lambda r: (r['site'], r['target']))
    for ref in materializations:
        target = int(ref['target'], 16)
        if target in signature_addresses and not any(int(r['start'], 16) <= target < int(r['end_exclusive'], 16) for r in regions):
            roots[target].append('materialized-signature-candidate:' + ref['site'])
        site = int(ref['site'], 16)
        blob = image.code[site - image.start:site - image.start + 32]
        # Delphi-2 stack frame: PUSH handler; PUSH FS:[reg]; MOV FS:[reg],ESP.
        # These two positively matched helpers transfer to handler+5. The
        # implementations at 402fdf/402fe7 and 40315x corroborate that convention.
        registered = False
        if blob and blob[0] == 0x68:
            instructions = list(seh_decoder.disasm(blob, site))[:3]
            if len(instructions) == 3:
                _, push, move = instructions
                if (push.mnemonic == 'push' and move.mnemonic == 'mov' and len(move.operands) == 2
                        and push.operands[0].type == X86_OP_MEM and move.operands[0].type == X86_OP_MEM
                        and move.operands[1].type == X86_OP_REG and move.operands[1].reg == X86_REG_ESP):
                    p, m = push.operands[0].mem, move.operands[0].mem
                    registered = p.segment == m.segment == X86_REG_FS and (p.base, p.index, p.disp) == (m.base, m.index, m.disp)
        if registered:
            roots[target].append('installed-SEH-handler:' + ref['site'])
            registration = dict(site=ref['site'], handler=ref['target'])
            if image.integer(target, '<B') == 0xe9:
                helper = target + 5 + image.integer(target + 1, '<i')
                registration['runtime_target'] = HEX(helper)
                if helper in seh_helpers:
                    registration['helper_name'] = seh_helpers[helper]
                    registration['continuation'] = HEX(target + 5)
                    roots[target + 5].append('SEH-helper-continuation:' + ref['site'])
            exception_registrations.append(registration)
    output = OUTPUT; output.mkdir(parents=True, exist_ok=True)
    # Signature hits do not automatically become function seeds: many are labels,
    # short aliases or interiors. Only independent structural/call roots do.
    root_rows = [dict(address=HEX(address), evidence=sorted(set(evidence))) for address, evidence in sorted(roots.items())]
    report = dict(original_sha256=HASH, compiler_evidence=dict(family='Delphi-2-compatible Win32 layout',
                  control_instance_size=0xa8, control_size_offset=-0x18, version_signature_comparison=versions,
                  limits='Shared system signatures also match later versions; signature hit counts do not identify compiler version.'),
                  classes=classes, metadata_regions=regions, metadata_issues=issues,
                  referenced_types=types,
                  exception_registrations=exception_registrations,
                  materialized_code_candidates=materializations,
                  runtime_signature_matches=matches, startup_calls=startup, entry_roots=root_rows,
                  recognition_provenance=json.loads((args.kb_dir / 'download-manifest.json').read_text()),
                  knowledge_base_sha256=hashlib.sha256((args.kb_dir / 'kb2.bin').read_bytes()).hexdigest(),
                  snapshot_sha256=hashlib.sha256(args.snapshot.read_bytes()).hexdigest(),
                  limits='Structural roots and masked signatures only. Byte matches are not proof of identity, purity or callback behavior. Windows delivery, aliases, dynamic registration and unrecognized executable regions remain explicit boundaries.')
    outputs = {'structural-inventory.json': json.dumps(report, indent=2) + '\n',
               'roots.tsv': ''.join(f"{HEX(address)}\t{evidence[0]}\n" for address, evidence in sorted(roots.items())),
               'metadata.tsv': ''.join(f"{r['start']}\t{r['end_exclusive']}\t{r['kind']}:{r['evidence']}\n" for r in regions)}
    for name, content in outputs.items():
        if args.check:
            if (output / name).read_text() != content: raise ValueError('Structural inventory stale: ' + name)
        else:
            (output / name).write_text(content, encoding='utf-8')
    print(json.dumps(dict(classes=len(classes), metadata_issues=len(issues), signature_records_matched=len(matches),
                         root_addresses=len(roots), virtual_entries=sum(len(c['virtual_entries']) for c in classes),
                         dynamic_entries=sum(len(c['dynamic_entries']) for c in classes),
                         published_entries=sum(len(c['published_entries']) for c in classes),
                         properties=sum(len(c['properties']) for c in classes),
                         fields=sum(len(c['fields']) for c in classes)), indent=2), flush=True)


if __name__ == '__main__':
    main()
