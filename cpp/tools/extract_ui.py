"""Recover ending pictures and save-slot menu evidence from the original Delphi form."""
from pathlib import Path
import argparse
import hashlib
import io
import json
import os
import struct

import pefile
from PIL import Image

ROOT = Path(__file__).resolve().parents[2]
ORIGINAL_HASH = '41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779'
RESOURCE_NAME = 'TTSW10'
# Reviewed Picture.Data BMP starts for Image21 and Image33 in this hash-pinned form.
PICTURES = {'ending-story': ('Image21', 3098), 'ending-card': ('Image33', 260264)}


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--exe', type=Path, default=Path(os.environ.get(
        'TOS_ORIGINAL_EXE', r'D:\Program Files (x86)\Tower of the Sorcerer\TSW.exe')))
    parser.add_argument('--output', type=Path, default=ROOT / 'build/assets')
    parser.add_argument('--binary-output', type=Path, help='Write original BMP resources for embedding, without PNG conversion')
    args = parser.parse_args()
    raw = args.exe.read_bytes()
    if hashlib.sha256(raw).hexdigest() != ORIGINAL_HASH:
        raise RuntimeError('Original executable hash differs; form offsets need review')
    pe = pefile.PE(data=raw)
    form = None
    for kind in pe.DIRECTORY_ENTRY_RESOURCE.entries:
        if kind.id != 10:  # RT_RCDATA: Delphi binary form.
            continue
        for resource in kind.directory.entries:
            if str(resource.name) == RESOURCE_NAME:
                data = resource.directory.entries[0].data.struct
                form = pe.get_data(data.OffsetToData, data.Size)
    if form is None or not form.startswith(b'TPF0'):
        raise RuntimeError('Original Delphi main form was not found')
    if args.binary_output:
        args.binary_output.mkdir(parents=True, exist_ok=True)
        for name, (component, offset) in PICTURES.items():
            if form[offset:offset + 2] != b'BM' or component.encode() not in form[offset - 120:offset]:
                raise RuntimeError(f'Unexpected picture header for {component}')
            length = struct.unpack_from('<I', form, offset + 2)[0]
            bitmap = form[offset:offset + length]
            if len(bitmap) != length or struct.unpack_from('<ii', bitmap, 18) != (640, 400):
                raise RuntimeError(f'Unexpected embedded picture size for {component}')
            (args.binary_output / f'{name}.bmp').write_bytes(bitmap)
        print('Prepared the two original ending BMP resources for the replacement executable')
        return
    slots = []
    for number in range(1, 9):
        entry = dict(number=number, caption=f'Data &{number}')
        for kind, first in [('save', 561430), ('load', 560829)]:
            component = f'{kind.title()}{number}1'
            offset = first + (number - 1) * 68
            expected = component.encode() + b'\x07Caption\x06\x07' + entry['caption'].encode()
            if form[offset:offset + len(expected)] != expected:
                raise RuntimeError(f'Unexpected original save menu item: {component}')
            entry[kind] = dict(component=component, resource=RESOURCE_NAME, offset=offset)
        slots.append(entry)
    args.output.mkdir(parents=True, exist_ok=True)
    recovered = []
    for name, (component, offset) in PICTURES.items():
        if form[offset:offset + 2] != b'BM' or component.encode() not in form[offset - 120:offset]:
            raise RuntimeError(f'Unexpected picture header for {component}')
        length = struct.unpack_from('<I', form, offset + 2)[0]
        bitmap = form[offset:offset + length]
        with Image.open(io.BytesIO(bitmap)) as image:
            if image.size != (640, 400):
                raise RuntimeError(f'Unexpected ending picture size: {image.size}')
            target = args.output / f'data-exe-{name}.png'
            image.convert('RGB').save(target, optimize=True)
        recovered.append(dict(component=component, resource=RESOURCE_NAME, offset=offset,
                              bitmap_bytes=length, bitmap_sha256=hashlib.sha256(bitmap).hexdigest(),
                              output=target.name, size=[640, 400]))
        print(f'Recovered {component}: {target}')
    (ROOT / 'reference/original/ui-extraction-manifest.json').write_text(
        json.dumps(dict(original_sha256=ORIGINAL_HASH, pictures=recovered, manual_save_slots=slots),
                   indent=2) + '\n', encoding='utf-8')
    print(f'Verified {len(slots)} paired manual Save/Load slots in {RESOURCE_NAME}')


if __name__ == '__main__':
    main()
