"""Extract MTW 1.6a text without executing it; input is the unpacked Mtw.exe.

The installer is LHA containing an InstallShield 3 archive. See
cpp/locales/README.md for the two extraction steps. Requires pefile.
"""
from pathlib import Path
import argparse
import hashlib
import json
import re
import struct
import sys
import zipfile

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))
from extract_original_ui import FormReader, walk

HASH = "9985d47483504489993c8db1fb7c088ccec69499843aafb5ae2a87423aa86cf9"
OPENING_HASH = "a7d7cbc408b1d8789d25f042fb1b4e39461adb32244c604400827a116e70aa45"
OPENING = "時は来たれり・・・\n我、全能の力を用いて、神剣を砕き、\n偉大なる知恵を手に入れん・・・"
ENDING = ("ながい戦いは終わりを告げ、虚栄の塔は崩れさる。\n\n神々は天へと帰り、\n"
          "戦士は大地へと戻った。\n\n現在は過去へと移り変わり、\n"
          "この旅も過去のものになろうとしている。\n\nあなたは、少しだけ振り返ると、\n"
          "新たな旅へ向けて足を踏み出すのであった。")


def help_text(raw):
    """Visible text in helpdeco RTF, decoding contiguous CP932 byte runs together.

    Rendering, pictures, hidden macros and hotspots are not part of this output.
    """
    token = re.compile(r"\\([a-zA-Z]+)(-?\d+)? ?|\\'([0-9a-fA-F]{2})|\\([^a-zA-Z])")
    ignored_groups = {"fonttbl", "colortbl", "stylesheet", "info", "field", "footnote", "pict", "object"}
    source = raw.decode('latin1')
    output, stack, pending = [], [], bytearray()
    ignored, pos = False, 0
    def flush():
        if pending:
            output.append(pending.decode('cp932'))
            pending.clear()
    while pos < len(source):
        c = source[pos]
        if c in '{}':
            flush()
            if c == '{':
                stack.append(ignored)
            else:
                ignored = stack.pop()
            pos += 1
        elif c == '\\':
            match = token.match(source, pos)
            if not match:
                raise ValueError(f'Invalid RTF token at {pos}')
            word, argument, hexadecimal, symbol = match.groups()
            pos = match.end()
            if hexadecimal:
                if not ignored:
                    pending.append(int(hexadecimal, 16))
                continue
            if symbol in ['\\', '{', '}']:
                if not ignored:
                    pending += symbol.encode('ascii')
                continue
            flush()
            if word in ignored_groups or symbol == '*':
                ignored = True
            elif word == 'v':
                ignored = argument != '0'
            elif not ignored:
                if word in ['par', 'line']:
                    output.append('\n')
                elif word == 'page':
                    output.append('\f')
                elif word == 'tab':
                    output.append('\t')
                elif symbol == '~':
                    output.append(' ')
        else:
            if not ignored and c not in '\r\n':
                pending.append(ord(c))
            pos += 1
    flush()
    if stack:
        raise ValueError('Unclosed RTF group')
    return ''.join(output)


class JapaneseFormReader(FormReader):
    def short(self):
        return self.take(self.number("<B")).decode("cp932")

    def value(self):
        if self.data[self.pos] == 12:
            self.take(1)
            return self.take(self.number("<I")).decode("cp932")
        return super().value()


def write(path, value):
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(json.dumps(value, ensure_ascii=False, indent=2) + "\n", encoding="utf-8")


def extract(exe, output, html5, help_rtf=None, opening_bmp=None):
    import pefile
    raw = exe.read_bytes()
    if hashlib.sha256(raw).hexdigest() != HASH:
        raise ValueError("Expected the Mtw.exe supplied by MTW16a.EXE")
    pe = pefile.PE(data=raw)
    dialogue, forms, ending = [], [], None
    for kind in pe.DIRECTORY_ENTRY_RESOURCE.entries:
        if kind.id != 10:
            continue
        for resource in kind.directory.entries:
            data = resource.directory.entries[0].data.struct
            blob = pe.get_data(data.OffsetToData, data.Size)
            if not blob.startswith(b"TPF0"):
                continue
            reader = JapaneseFormReader(blob)
            form = reader.component()
            if reader.pos != len(blob):
                raise ValueError("Trailing form data")
            for component in walk(form):
                for prop, record in component["properties"].items():
                    value = record["value"]
                    if component['name'] == 'Image21' and prop == 'Picture.Data':
                        at = record['value_offset']
                        size = struct.unpack_from('<I', blob, at + 1)[0]
                        picture = blob[at + 5:at + 5 + size]
                        start = picture.index(b'BM')
                        ending = dict(component='Image21', method='Manual transcription, visually checked',
                                      bitmap_sha256=hashlib.sha256(picture[start:]).hexdigest(), text=ENDING)
                    if prop not in ("Caption", "Hint", "Text", "Items.Strings", "Lines.Strings"):
                        continue
                    offset = pe.get_offset_from_rva(data.OffsetToData) + record["value_offset"]
                    forms.append(dict(form=str(resource.name), component=component["name"],
                                      property=prop, file_offset=hex(offset), value=value))
                    if prop == "Items.Strings" and isinstance(value, list) and len(value) == 268:
                        cursor = offset + 1
                        for i, text in enumerate(value):
                            tag = raw[cursor]
                            size = raw[cursor + 1] if tag == 6 else struct.unpack_from("<I", raw, cursor + 1)[0]
                            start = cursor + (2 if tag == 6 else 5)
                            dialogue.append(dict(id=i, text=text, file_offset=hex(cursor),
                                                 cp932_hex=raw[start:start + size].hex()))
                            cursor = start + size
    if len(dialogue) != 268:
        raise ValueError(f"Expected one complete dialogue table; got {len(dialogue)}")
    literals, cursor = [], 0
    # Delphi's static AnsiString layout is refcount=-1, byte length, payload, NUL.
    # Retain structurally valid Japanese candidates, without claiming code reachability.
    while True:
        at = raw.find(b'\xff\xff\xff\xff', cursor)
        if at < 0:
            break
        cursor = at + 4
        if at + 9 > len(raw):
            continue
        size = struct.unpack_from('<I', raw, at + 4)[0]
        if not (1 <= size <= 4096 and at + 8 + size < len(raw) and raw[at + 8 + size] == 0):
            continue
        payload = raw[at + 8:at + 8 + size]
        try:
            text = payload.decode('cp932')
        except UnicodeDecodeError:
            continue
        if (any('\u3040' <= c <= '\u30ff' or '\u4e00' <= c <= '\u9fff' for c in text)
                and all(c >= ' ' or c in '\r\n\t' for c in text)):
            literals.append(dict(file_offset=hex(at + 8), text=text, cp932_hex=payload.hex()))
    opening = None
    if opening_bmp:
        picture = opening_bmp.read_bytes()
        if hashlib.sha256(picture).hexdigest() != OPENING_HASH:
            raise ValueError("Expected the Group10/Open2.bmp supplied by MTW16a.EXE")
        opening = dict(file='Group10/Open2.bmp', method='Manual transcription, visually checked',
                       bitmap_sha256=OPENING_HASH, text=OPENING)
    write(output / "japanese-source.json", dict(edition="魔法の塔 for Windows Ver1.6a",
          authors="Oz & Kenichi", executable_sha256=HASH, encoding="cp932",
          dialogue=dialogue, forms=forms, runtime_literal_candidates=literals,
          opening_story=opening, ending_story=ending))
    docs = {p.name: p.read_bytes().decode("cp932") for p in exe.parent.iterdir()
            if p.suffix.lower() in (".txt", ".cnt")}
    write(output / "japanese-documents.json", docs)
    if help_rtf:
        text = help_text(help_rtf.read_bytes())
        topics = [p.strip() for p in text.split('\f') if p.strip()]
        write(output / 'japanese-help.json', dict(source='MTW.HLP, helpdeco /r export',
              help_sha256=hashlib.sha256((exe.parent / 'MTW.HLP').read_bytes()).hexdigest(),
              rtf_sha256=hashlib.sha256(help_rtf.read_bytes()).hexdigest(),
              encoding='cp932', limits='Visible prose only, without images, hotspots or hidden macros',
              exported_pages=len(text.split('\f')), topics=[dict(number=i+1, text=s) for i,s in enumerate(topics)]))
        print(f'Extracted {len(topics)} Japanese help topics')
    if html5:
        with zipfile.ZipFile(html5) as archive:
            terms = {}
            for category, path in [("items", "TSWH5/project/items.js"),
                                   ("monsters", "TSWH5/project/enemys.js")]:
                text = archive.read(path).decode("utf-8-sig")
                records = json.loads(text[text.index("{"):])
                terms[category] = {key: value["name"] for key, value in records.items()}
        write(output / "html5-terminology.json", dict(archive_sha256=hashlib.sha256(html5.read_bytes()).hexdigest(),
                                                     **terms))
    print(f"Extracted {len(dialogue)} dialogue entries, {len(forms)} form text properties and {len(docs)} documents")


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("exe", type=Path)
    parser.add_argument("--html5", type=Path)
    parser.add_argument("--help-rtf", type=Path, help='Optional MTW.HLP exported with helpdeco /r')
    parser.add_argument("--opening-bmp", type=Path, help='Optional extracted Group10/Open2.bmp for opening prose')
    parser.add_argument("--output", type=Path, default=ROOT / "cpp/locales/source")
    args = parser.parse_args()
    extract(args.exe, args.output, args.html5, args.help_rtf, args.opening_bmp)
