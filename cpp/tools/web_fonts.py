"""Build redistributable, catalog-sized Noto CJK fonts outside the startup .data package."""
from __future__ import annotations

import argparse
import hashlib
import json
from pathlib import Path
import urllib.request

try:
    import fontTools
    from fontTools import subset
    from fontTools.ttLib import TTFont
except ImportError:
    raise SystemExit("Web fonts need fontTools: python -m pip install -r cpp/tools/web-fonts-requirements.txt")

CPP = Path(__file__).resolve().parents[1]
REVISION = "f8d157532fbfaeda587e826d4cd5b21a49186f7c"
BASE = f"https://raw.githubusercontent.com/notofonts/noto-cjk/{REVISION}/Sans/"
SOURCES = {
    "jp.otf": ("OTF/Japanese/NotoSansCJKjp-Regular.otf",
               "68a3fc98800b2a27b371f2fb79991daf3633bd89309d4ffaa6946fd587f375b5"),
    "sc.otf": ("OTF/SimplifiedChinese/NotoSansCJKsc-Regular.otf",
               "2c76254f6fc379fddfce0a7e84fb5385bb135d3e399294f6eeb6680d0365b74b"),
    "LICENSE.txt": ("LICENSE", "6a73f9541c2de74158c0e7cf6b0a58ef774f5a780bf191f2d7ec9cc53efe2bf2"),
}


def write_changed(path: Path, data: bytes) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    if not path.is_file() or path.read_bytes() != data:
        path.write_bytes(data)


def source(cache: Path, name: str) -> Path:
    remote, expected = SOURCES[name]
    path = cache / name
    if not path.is_file() or hashlib.sha256(path.read_bytes()).hexdigest() != expected:
        with urllib.request.urlopen(BASE + remote, timeout=90) as response:
            data = response.read()
        if hashlib.sha256(data).hexdigest() != expected:
            raise ValueError(f"Noto CJK checksum mismatch: {name}")
        write_changed(path, data)
    return path


def strings(value):
    if isinstance(value, str):
        yield value
    elif isinstance(value, list):
        for entry in value:
            yield from strings(entry)
    elif isinstance(value, dict):
        for entry in value.values():
            yield from strings(entry)


def build(cache: Path, output: Path, preload: Path, manifest: Path) -> None:
    catalogs = [json.loads(p.read_text(encoding="utf-8")) for p in sorted((CPP / "locales").glob("*.json"))]
    labels = "".join(c["label"] for c in catalogs)
    # The renderer's atlas uses the union of catalog codepoints. Keep both regional
    # faces complete, including language names, symbols, and dynamic ASCII values.
    text = "".join(chr(cp) for cp in range(32, 127)) + labels
    for catalog in catalogs:
        text += "".join(strings({key: catalog[key] for key in
                                ("dialogue", "text", "status", "opening_story", "ending_story")}))
    characters = {ord(c) for c in text if ord(c) >= 32}
    paths = {name: source(cache, name) for name in SOURCES}
    fingerprint = hashlib.sha256(Path(__file__).read_bytes() + fontTools.__version__.encode() + text.encode()).hexdigest()
    stamp = manifest.with_suffix(".stamp")
    if (stamp.is_file() and stamp.read_text() == fingerprint and manifest.is_file()
            and (preload / "labels.otf").is_file()
            and len(list(output.glob("*.otf"))) == 2 and (output / "LICENSE.txt").is_file()):
        return

    def make(name: str, points: set[int], target: Path) -> bytes:
        font = TTFont(paths[name], recalcTimestamp=False)
        missing = points - font.getBestCmap().keys()
        if missing:
            raise ValueError(f"Noto {name} lacks catalog characters: {sorted(missing)}")
        options = subset.Options()
        options.hinting = False
        options.recalc_timestamp = False
        sub = subset.Subsetter(options=options)
        sub.populate(unicodes=sorted(points))
        sub.subset(font)
        font.save(target)
        font.close()
        return target.read_bytes()

    preload.mkdir(parents=True, exist_ok=True)
    output.mkdir(parents=True, exist_ok=True)
    make("jp.otf", set(range(32, 127)) | {ord(c) for c in labels}, preload / "labels.otf")
    files = {}
    for language, name in [("ja", "jp.otf"), ("zh", "sc.otf")]:
        temporary = output / f"{language}.tmp"
        data = make(name, characters, temporary)
        temporary.unlink()
        filename = f"{language}-{hashlib.sha256(data).hexdigest()[:16]}.otf"
        write_changed(output / filename, data)
        files[language] = "fonts/" + filename
        print(f"Web font {language}: {len(data):,} bytes, {len(characters)} codepoints")
    for path in output.glob("*.otf"):
        if "fonts/" + path.name not in files.values():
            path.unlink()
    write_changed(output / "LICENSE.txt", paths["LICENSE.txt"].read_bytes())
    write_changed(manifest, ("Module['tswFontFiles'] = " + json.dumps(files) + ";\n").encode())
    write_changed(stamp, fingerprint.encode())


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--cache", type=Path, required=True)
    parser.add_argument("--output", type=Path, required=True)
    parser.add_argument("--preload", type=Path, required=True)
    parser.add_argument("--manifest", type=Path, required=True)
    args = parser.parse_args()
    build(args.cache, args.output, args.preload, args.manifest)
