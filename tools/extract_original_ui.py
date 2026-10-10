"""Recover Delphi form events and published method tables from the pinned PE.

Reads resources structurally, rather than searching arbitrary bitmap bytes for
event names. Does not run or modify the installed game. Requires pefile.
"""
from pathlib import Path
import argparse
import hashlib
import json
import os
import struct

from recovery_evidence import ROOT, ORIGINAL_HASH as HASH


class FormReader:
    def __init__(self, data):
        if data[:4] != b"TPF0":
            raise ValueError("Not a binary Delphi form")
        self.data, self.pos = data, 4

    def take(self, count):
        start = self.pos
        self.pos += count
        if self.pos > len(self.data):
            raise ValueError("Truncated form")
        return self.data[start:self.pos]

    def number(self, fmt):
        return struct.unpack(fmt, self.take(struct.calcsize(fmt)))[0]

    def short(self):
        return self.take(self.number("<B")).decode("cp1252")

    def value(self):
        tag = self.number("<B")
        if tag in (0, 13):
            return None
        if tag == 1:
            result = []
            while self.data[self.pos] != 0:
                result.append(self.value())
            self.take(1)
            return result
        if tag in (2, 3, 4, 15, 16, 17, 19):
            return self.number({2: "<b", 3: "<h", 4: "<i", 15: "<f", 16: "<q", 17: "<d", 19: "<q"}[tag])
        if tag == 5:
            return {"extended_bytes": self.take(10).hex()}
        if tag in (6, 7):
            return self.short()
        if tag in (8, 9):
            return tag == 9
        if tag == 10:
            size = self.number("<I")
            data = self.take(size)
            return {"binary_bytes": size, "sha256": hashlib.sha256(data).hexdigest()}
        if tag == 11:
            values = []
            while self.data[self.pos] != 0:
                values.append(self.short())
            self.take(1)
            return values
        if tag in (12, 18, 20):
            size = self.number("<I")
            return self.take(size * (2 if tag == 18 else 1)).decode({12: "cp1252", 18: "utf-16le", 20: "utf-8"}[tag])
        if tag == 14:
            items = []
            while self.data[self.pos] != 0:
                if self.data[self.pos] in (2, 3, 4):
                    self.value()  # Optional collection item index.
                if self.number("<B") != 1:
                    raise ValueError("Expected collection item")
                items.append(self.properties())
            self.take(1)
            return items
        raise ValueError(f"Unknown value tag {tag} at {self.pos - 1:#x}")

    def properties(self):
        values = {}
        while self.data[self.pos] != 0:
            name, offset = self.short(), self.pos
            values[name] = {"value_offset": offset, "value": self.value()}
        self.take(1)
        return values

    def component(self):
        offset = self.pos
        if self.data[self.pos] & 0xF0 == 0xF0:
            flags = self.number("<B") & 0xF
            if flags & 2:
                self.value()  # Child position.
        cls, name = self.short(), self.short()
        result = dict(offset=offset, class_name=cls, name=name, properties=self.properties(), children=[])
        while self.data[self.pos] != 0:
            result["children"].append(self.component())
        self.take(1)
        return result


def methods(image, base, cls):
    marker = b"\x07" + bytes([len(cls)]) + cls.encode("ascii")
    start = image.find(marker)
    if start < 0:
        return dict(vmt=None, table=None, methods=[], recovery="No class type info in executable")
    if image.find(marker, start + 1) >= 0:
        raise ValueError(f"Missing/ambiguous class type info: {cls}")
    vmt = struct.unpack_from("<I", image, start + len(marker))[0]
    table = struct.unpack_from("<I", image, vmt - base - 36)[0]
    field_table = struct.unpack_from("<I", image, vmt - base - 40)[0]
    fields = []
    if field_table:
        cursor = field_table - base
        field_count, type_table = struct.unpack_from("<HI", image, cursor)
        cursor += 6
        for _ in range(field_count):
            offset, type_index, name_size = struct.unpack_from("<IHB", image, cursor)
            name = image[cursor + 7:cursor + 7 + name_size].decode("ascii")
            fields.append(dict(name=name, offset=f"0x{offset:x}", type_index=type_index,
                               record_address=f"0x{base + cursor:08x}"))
            cursor += 7 + name_size
    cursor = table - base
    count = struct.unpack_from("<H", image, cursor)[0]
    cursor += 2
    result = []
    for _ in range(count):
        size, address, name_size = struct.unpack_from("<HIB", image, cursor)
        if size != 7 + name_size or not 0x400000 <= address < 0x489000:
            raise ValueError(f"Invalid method record at {base + cursor:#x}")
        name = image[cursor + 7:cursor + size].decode("ascii")
        result.append(dict(name=name, address=f"0x{address:08x}", record_address=f"0x{base + cursor:08x}"))
        cursor += size
    return dict(vmt=f"0x{vmt:08x}", table=f"0x{table:08x}", methods=result,
                field_table=f"0x{field_table:08x}", fields=fields)


def walk(component):
    yield component
    for child in component["children"]:
        yield from walk(child)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--exe", type=Path, default=Path(os.environ.get("TOS_ORIGINAL_EXE", r"D:\Program Files (x86)\Tower of the Sorcerer\TSW.exe")))
    parser.add_argument("--output", type=Path, default=ROOT / "reference/original/presentation")
    args = parser.parse_args()
    import pefile

    raw = args.exe.read_bytes()
    if hashlib.sha256(raw).hexdigest() != HASH:
        raise ValueError("Executable hash differs; recovery requires review")
    pe = pefile.PE(data=raw)
    image, base = pe.get_memory_mapped_image(), pe.OPTIONAL_HEADER.ImageBase
    forms, events, exports = [], [], {}
    for kind in pe.DIRECTORY_ENTRY_RESOURCE.entries:
        if kind.id != 10:
            continue
        for resource in kind.directory.entries:
            data = resource.directory.entries[0].data.struct
            blob = pe.get_data(data.OffsetToData, data.Size)
            if not blob.startswith(b"TPF0"):
                continue
            reader = FormReader(blob)
            form = reader.component()
            if reader.pos != len(blob):
                raise ValueError("Trailing form data")
            table = methods(image, base, form["class_name"])
            lookup = {m["name"].lower(): m for m in table["methods"]}
            components = list(walk(form))
            for component in components:
                for prop, value in component["properties"].items():
                    if not prop.startswith("On"):
                        continue
                    method = lookup.get(str(value["value"]).lower())
                    if method is None:
                        raise ValueError(f"Unresolved event {component['name']}.{prop}: {value}")
                    events.append(dict(form=form["class_name"], component=component["name"],
                                       event=prop, method=method["name"], address=method["address"],
                                       resource_rva=f"0x{data.OffsetToData:08x}", value_offset=value["value_offset"]))
            for method in table["methods"]:
                exports.setdefault(method["address"], f"{form['class_name']}_{method['name']}")
            forms.append(dict(resource=str(resource.name), bytes=len(blob), components=len(components),
                              class_name=form["class_name"], **table, tree=form))
    args.output.mkdir(parents=True, exist_ok=True)
    manifest = dict(original_sha256=HASH, forms=forms, events=events,
                    limits="Published methods and serialized DFM events only. Dynamically assigned events, virtual dispatch, and unnamed helpers require call-site recovery.")
    (args.output / "ui-manifest.json").write_text(json.dumps(manifest, indent=2) + "\n", encoding="utf-8")
    corpus = ROOT / "reference/original/decompiled"
    missing = [address for address in exports if not list(corpus.glob(f"{int(address,16):08x}_*.c"))]
    (args.output / "published-methods.tsv").write_text("".join(f"{address}\t{name}\n" for address, name in sorted(exports.items())), encoding="utf-8")
    print(json.dumps(dict(forms=len(forms), components=sum(f["components"] for f in forms),
                          events=len(events), unique_methods=len(exports), missing_exports=len(missing), missing=missing), indent=2))


if __name__ == "__main__":
    main()
