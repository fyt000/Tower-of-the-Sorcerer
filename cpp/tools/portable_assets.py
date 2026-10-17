"""Stage the runtime assets shared by Android and WebAssembly (no research data or saves)."""
from __future__ import annotations

import argparse
import hashlib
import shutil
from pathlib import Path

SCENES = (
    "left", "leftr", "center", "right", "rightr", "title05", "title05r", "open0", "open1", "open2"
)
IMAGES = ["original-atlas.png", "original-background-atlas.png"]
IMAGES += [f"data3-{name}.png" for name in SCENES]
IMAGES += [f"data2-end{n:02}.png" for n in [*range(5, 21), 26]]
IMAGES += ["data-exe-ending-story.png", "data-exe-ending-card.png"]


def stage(source: Path, soundfont: Path, output: Path) -> None:
    source, output = source.resolve(), output.resolve()
    if source == output or source in output.parents or output in source.parents:
        raise ValueError("Source and output must be separate, non-nested directories")
    files = {name: source / name for name in IMAGES}
    for folder, extension in [("midi", ".mid"), ("wav", ".wav")]:
        entries = sorted((source / folder).glob(f"*{extension}"))
        if not entries:
            raise ValueError(f"Missing {folder} assets in {source}")
        files.update({f"{folder}/{p.name}": p for p in entries})
    # Optional freely redistributable fonts supplied by the builder, with their notices.
    files.update({p.relative_to(source).as_posix(): p for p in (source / "fonts").glob("*") if p.is_file()})
    if soundfont.suffix.lower() != ".sfo":
        raise ValueError(f"Expected an .sfo soundfont: {soundfont}")
    files["music.sfo"] = soundfont
    cpp = Path(__file__).resolve().parents[1]
    files.update({f"licenses/{p.name}": p for p in (cpp / "licenses").glob("*.txt")})
    files["licenses/GeneralUser-GS.txt"] = soundfont.parent / "LICENSE.txt"
    files["licenses/game-attribution.md"] = cpp.parent / "THIRD_PARTY.md"
    files["licenses/project.txt"] = cpp.parent / "LICENSE"
    missing = [str(p) for p in files.values() if not p.is_file()]
    if missing:
        raise ValueError("Missing runtime assets; run extract_original.py and extract_ui.py first:\n" + "\n".join(missing))
    digest = hashlib.sha256()
    output.mkdir(parents=True, exist_ok=True)
    for name, path in sorted(files.items()):
        data = path.read_bytes()
        digest.update(name.encode() + b"\0" + hashlib.sha256(data).digest())
        target = output / name
        target.parent.mkdir(parents=True, exist_ok=True)
        if not target.exists() or target.read_bytes() != data:
            shutil.copyfile(path, target)
    # Remove stale staged files, while keeping the output strictly within its resolved root.
    for path in output.rglob("*"):
        if path.is_file() and path.relative_to(output).as_posix() not in files and path.name != "asset-version.txt":
            path.unlink()
    version = output / "asset-version.txt"
    text = digest.hexdigest() + "\n"
    if not version.exists() or version.read_text() != text:
        version.write_text(text, encoding="utf-8", newline="\n")
    print(f"Staged {len(files)} runtime assets in {output}")


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--source", type=Path, required=True)
    parser.add_argument("--soundfont", type=Path, required=True)
    parser.add_argument("--output", type=Path, required=True)
    args = parser.parse_args()
    stage(args.source, args.soundfont, args.output)
