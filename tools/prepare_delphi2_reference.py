"""Extract the user's Delphi 2 research baseline without running its installer.

Requires an already unpacked media directory and a checkout of
https://github.com/lephilousophe/idecomp at the pinned revision below.
Borland compiler/library/source files stay in the ignored build directory.
Base units and the archive's separate Updates directory are never overlaid.
"""
from pathlib import Path, PureWindowsPath
import argparse
import hashlib
import importlib
import json
import subprocess
import sys
import stat

ROOT = Path(__file__).resolve().parents[1]
EXTRACTOR_COMMIT = "bd2b77624b96bb2a4f347518d087126759296a03"


def sha256(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--media", type=Path, required=True)
    parser.add_argument("--extractor", type=Path, required=True)
    parser.add_argument("--archive", type=Path)
    parser.add_argument("--output", type=Path, default=ROOT / "build/research/delphi2")
    args = parser.parse_args()
    revision = subprocess.check_output(
        ["git", "-C", str(args.extractor), "rev-parse", "HEAD"], text=True
    ).strip()
    if revision != EXTRACTOR_COMMIT:
        raise ValueError("Unreviewed InstallShield extractor revision")
    for name in ("idecomp.py", "pwexplode.py"):
        subprocess.run(["git", "-C", str(args.extractor), "diff", "--exit-code", "HEAD", "--", name], check=True)
    sys.path.insert(0, str(args.extractor.resolve()))
    extractor = importlib.import_module("idecomp")
    payload = args.media / "DATA.Z"
    archive = extractor.Archive(str(payload), encoding="cp1252")
    output = args.output.resolve()
    if not output.is_relative_to((ROOT / "build/research").resolve()):
        raise ValueError("Extraction must stay in the ignored research directory")
    records = []
    selected = []
    prefixes = {
        "DELPHI32/MINIMAL/BIN/": "base/bin/",
        "DELPHI32/MINIMAL/LIB/": "base/lib/",
        "DELPHI32/MINIMAL/SLIB/": "base/slib/",
        "DELPHI32/MINIMAL/DOC/": "base/doc/",
        "DELPHI32/OPTIONS/SOURCE/": "base/source/",
    }
    for entry in archive.files:
        name = entry.path.replace("\\", "/")
        windows_path = PureWindowsPath(name)
        if windows_path.is_absolute() or windows_path.drive or ".." in windows_path.parts:
            raise ValueError(f"Unsafe media path: {name}")
        record = dict(path=name, size=entry.original_size,
                      compressed_size=entry.compacted_size, offset=entry.data_offset,
                      date=entry.datetime.isoformat(), flags=entry.flags)
        if entry.data_offset < 255 or entry.data_offset + entry.compacted_size > payload.stat().st_size:
            raise ValueError(f"Payload range outside archive: {name}")
        for prefix, destination in prefixes.items():
            if name.upper().startswith(prefix):
                record["extracted_path"] = destination + name[len(prefix):]
                target = output / record["extracted_path"]
                if not target.resolve().is_relative_to(output):
                    raise ValueError("Destination escaped research directory")
                selected.append((entry, record, target))
                break
        records.append(record)
    # Validate every archive name before extracting any files.
    for index, (entry, record, target) in enumerate(selected):
        staging = output / "payload"
        staged = staging / entry.path
        if staged.exists():
            staged.chmod(staged.stat().st_mode | stat.S_IWRITE)
        # Re-extract rather than trusting a same-length cache as source proof.
        entry.extract(str(staging))
        if staged.stat().st_size != entry.original_size:
            raise ValueError(f"Wrong decompressed length: {entry.path}")
        target.parent.mkdir(parents=True, exist_ok=True)
        target.write_bytes(staged.read_bytes())
        record["sha256"] = sha256(target)
        if (index + 1) % 50 == 0:
            print(f"Extracted {index + 1}/{len(selected)} baseline files", flush=True)
    updates = []
    for path in sorted((args.media / "Updates").glob("*")):
        if not path.is_file():
            continue
        target = output / "updates" / path.name
        target.parent.mkdir(parents=True, exist_ok=True)
        target.write_bytes(path.read_bytes())
        updates.append(dict(path="updates/" + path.name, size=path.stat().st_size,
                            sha256=sha256(path)))
    manifest = dict(schema_version=1, media_path=str(args.media.resolve()),
                    payload_sha256=sha256(payload), payload_bytes=payload.stat().st_size,
                    extractor=dict(url="https://github.com/lephilousophe/idecomp",
                                   commit=revision,
                                   files={name: sha256(args.extractor / name)
                                          for name in ("idecomp.py", "pwexplode.py")}),
                    files=records, updates=updates,
                    extracted_count=len(selected), total_count=len(records),
                    updates_applied=False)
    if args.archive:
        manifest["archive"] = dict(path=str(args.archive.resolve()),
                                   bytes=args.archive.stat().st_size,
                                   sha256=sha256(args.archive))
    (output / "media-manifest.json").write_text(json.dumps(manifest, indent=2) + "\n", encoding="utf-8")
    print(f"Retained {len(records)} media records; extracted {len(selected)} files, {len(updates)} separate updates")


if __name__ == "__main__":
    main()
