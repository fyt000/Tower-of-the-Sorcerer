"""Fetch the pinned public IDR recognition data, with size/hash verification.

This downloads signatures and IDR format/detector references, not Delphi source
or an IDE. Existing verified cache entries are reused. Requires existing 7-Zip
only when the Delphi-2 knowledge-base archive has not been extracted.
"""
from pathlib import Path
import argparse
import hashlib
import json
import shutil
import subprocess
import urllib.request

ROOT = Path(__file__).resolve().parents[1]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--output', type=Path, default=ROOT / 'build/research/idr')
    parser.add_argument('--check', action='store_true')
    args = parser.parse_args()
    inventory = json.loads((ROOT / 'tools/idr-inputs.json').read_text())
    provenance = inventory['recognition_provenance']
    args.output.mkdir(parents=True, exist_ok=True)
    for name, record in provenance['files'].items():
        path = args.output / name
        def valid():
            return path.exists() and path.stat().st_size == record['bytes'] and hashlib.sha256(path.read_bytes()).hexdigest() == record['sha256']
        if not valid() and not args.check:
            prefix = f"https://raw.githubusercontent.com/crypto2011/IDR/{provenance['commit']}/"
            if record['url'] != prefix + name or Path(name).name != name:
                raise ValueError('Unexpected recognition URL/path')
            with urllib.request.urlopen(record['url'], timeout=60) as response:
                blob = response.read()
            if len(blob) != record['bytes'] or hashlib.sha256(blob).hexdigest() != record['sha256']:
                raise ValueError(f'Download hash/size mismatch: {name}')
            path.write_bytes(blob)
        if not valid(): raise ValueError(f'Recognition cache hash/size mismatch: {name}')
    kb = args.output / 'kb2.bin'
    if not kb.exists() and not args.check:
        seven_zip = shutil.which('7z') or 'C:/Program Files/7-Zip/7z.exe'
        subprocess.run([seven_zip, 'e', str(args.output / 'kb2.7z'), 'kb2.bin',
                        '-o' + str(args.output.resolve()), '-y'], check=True)
    if not kb.exists() or hashlib.sha256(kb.read_bytes()).hexdigest() != inventory['knowledge_base_sha256']:
        raise ValueError('Extracted kb2.bin differs')
    (args.output / 'download-manifest.json').write_text(json.dumps(provenance, indent=2) + '\n', encoding='utf-8')
    print(f"Verified {len(provenance['files'])} pinned public IDR files and extracted Delphi-2 recognition KB")


if __name__ == '__main__':
    main()
