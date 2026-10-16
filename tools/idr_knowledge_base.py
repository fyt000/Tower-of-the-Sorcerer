"""Read public IDR recognition records, retaining ambiguity and provenance.

Format checked against crypto2011/IDR KnowledgeBase.{h,cpp}, MIT licensed.
These are masked machine-code signatures, not licensed Delphi RTL source.
Relocation-mask byte FF means wildcard. A match is not a purity assessment.
"""
from pathlib import Path
import struct


class Reader:
    def __init__(self, data, pos=0):
        self.data, self.pos = data, pos

    def take(self, size):
        if size < 0 or self.pos < 0 or self.pos + size > len(self.data):
            raise ValueError("Truncated IDR record")
        result = self.data[self.pos:self.pos + size]
        self.pos += size
        return result

    def number(self, fmt):
        return struct.unpack(fmt, self.take(struct.calcsize(fmt)))[0]

    def string(self):
        size = self.number('<H')
        value = self.take(size).decode('cp1252')
        if self.take(1) != b'\0':
            raise ValueError('IDR string lacks terminator')
        return value


class KnowledgeBase:
    def __init__(self, path):
        self.path = Path(path)
        self.data = self.path.read_bytes()
        if not self.data.startswith(b'IDR Knowledge Base File\0'):
            raise ValueError('Unknown IDR KB signature')
        self.version = struct.unpack_from('<i', self.data, 25)[0]
        cursor = Reader(self.data, struct.unpack_from('<I', self.data, len(self.data) - 4)[0])
        self.sections = {}
        for name in ['modules', 'consts', 'types', 'vars', 'resstr', 'procs']:
            count, _ = struct.unpack('<II', cursor.take(8))
            if count > (len(self.data) - cursor.pos) // 16:
                raise ValueError('Invalid IDR section count')
            self.sections[name] = [struct.unpack('<IIii', cursor.take(16)) for _ in range(count)]
            for offset, size, _, _ in self.sections[name]:
                if offset + size > len(self.data):
                    raise ValueError('IDR record outside file')
        if cursor.pos != len(self.data) - 4:
            raise ValueError('Unexpected IDR section trailer')
        self.modules = {}
        for offset, size, _, _ in self.sections['modules']:
            reader = Reader(self.data[offset:offset + size])
            identifier = reader.number('<H')
            self.modules[identifier] = reader.string()

    def procedures(self):
        for index, (offset, size, _, _) in enumerate(self.sections['procs']):
            reader = Reader(self.data[offset:offset + size])
            module = reader.number('<H')
            name = reader.string()
            embedded, kind, method, call = struct.unpack('<4B', reader.take(4))
            vproc = reader.number('<i')
            result = reader.string()
            total = reader.number('<I')
            start = reader.pos
            length, fixup_count = struct.unpack('<II', reader.take(8))
            dump, mask = reader.take(length), reader.take(length)
            fixups = []
            for _ in range(fixup_count):
                fixups.append(dict(kind=chr(reader.number('<B')), offset=reader.number('<I'), name=reader.string()))
            if reader.pos > start + total or start + total > len(reader.data):
                raise ValueError('IDR dump exceeds record')
            yield dict(index=index, module=self.modules.get(module, str(module)), name=name,
                       dump_kind=chr(kind), method_kind=chr(method), call_kind=call,
                       result_type=result, embedded=embedded, vproc=vproc,
                       dump=dump, mask=mask, fixups=fixups)

    def types(self):
        for offset, size, _, _ in self.sections['types']:
            reader = Reader(self.data[offset:offset + size])
            declared_size = reader.number('<I')
            module = reader.number('<H')
            name = reader.string()
            kind = reader.number('<B')
            virtual_count = reader.number('<H')
            declaration = reader.string()
            yield dict(module=self.modules.get(module, str(module)), name=name, kind=kind,
                       virtual_count=virtual_count, declared_size=declared_size, declaration=declaration)


def literal_runs(dump, mask):
    if len(dump) != len(mask):
        raise ValueError('IDR mask length differs from dump')
    runs, start = [], None
    for offset in range(len(dump) + 1):
        literal = offset < len(dump) and mask[offset] != 0xff
        if literal and start is None:
            start = offset
        elif not literal and start is not None:
            runs.append((start, dump[start:offset]))
            start = None
    return runs


def find_matches(image, procedure, minimum_fixed=16):
    dump, mask = procedure['dump'], procedure['mask']
    if procedure['dump_kind'] != 'C' or not dump:
        return []
    runs = literal_runs(dump, mask)
    if sum(len(run) for _, run in runs) < minimum_fixed:
        return []
    anchor_offset, anchor = max(runs, key=lambda item: len(item[1]))
    if len(anchor) < 4:
        return []
    found, cursor = [], 0
    while True:
        match = image.find(anchor, cursor)
        if match < 0:
            break
        cursor = match + 1
        start = match - anchor_offset
        if start >= 0 and start + len(dump) <= len(image) and all(image[start + offset:start + offset + len(run)] == run for offset, run in runs):
            found.append(start)
    return found
