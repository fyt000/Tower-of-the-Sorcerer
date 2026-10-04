"""Read the installed manuals; never modify the installation or game data.

Supply a complete lookalike RTF exported by helpdeco (-r), or a helpdeco
executable. The RTF reader handles the text subset used by this English help
file; it deliberately omits images, hotspots, formatting and executable macros.
"""

import argparse
import hashlib
import json
import re
import subprocess
import tempfile
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
CONTROL = re.compile(r"\\([a-zA-Z]+)(-?\d+)? ?|\\'([0-9a-fA-F]{2})|\\([^a-zA-Z])")
DESTINATIONS = {
    "fonttbl", "colortbl", "stylesheet", "info", "field", "footnote",
    "pict", "object", "header", "footer",
}


def rtf_text(source: str) -> str:
    """Extract visible prose and page boundaries, with RTF group scoping."""
    stack = []
    ignored, uc, fallback = False, 1, 0
    output = []
    position = 0
    while position < len(source):
        char = source[position]
        if char == "{":
            stack.append((ignored, uc))
            position += 1
        elif char == "}":
            if not stack:
                raise ValueError("Unbalanced RTF closing brace")
            ignored, uc = stack.pop()
            position += 1
        elif char == "\\":
            token = CONTROL.match(source, position)
            if token is None:
                raise ValueError(f"Invalid RTF control at {position}")
            word, argument, hexadecimal, symbol = token.groups()
            position = token.end()
            if word in DESTINATIONS or symbol == "*":
                ignored = True
            elif word == "v":
                ignored = argument != "0"
            elif word == "uc":
                uc = int(argument or "1")
            elif not ignored:
                if word == "u":
                    output.append(chr(int(argument) % 65536))
                    fallback = uc
                elif word in {"par", "line"}:
                    output.append("\n")
                elif word == "page":
                    output.append("\f")
                elif word == "tab":
                    output.append("\t")
                elif hexadecimal or symbol in {"\\", "{", "}", "~"}:
                    if fallback:
                        fallback -= 1
                    else:
                        output.append(bytes.fromhex(hexadecimal).decode("cp1252")
                                      if hexadecimal else " " if symbol == "~" else symbol)
        else:
            if not ignored and char not in "\r\n":
                if fallback:
                    fallback -= 1
                else:
                    output.append(char)
            position += 1
    if stack:
        raise ValueError("Incomplete RTF: unclosed groups")
    return "".join(output)


def extract(source: Path, rtf: Path) -> dict:
    files = {}
    for name in ("TSW.txt", "Tsw.hlp", "Tsw.cnt"):
        raw = (source / name).read_bytes()
        files[name] = {"sha256": hashlib.sha256(raw).hexdigest(), "bytes": len(raw)}
    topics = []
    for page in rtf_text(rtf.read_text(encoding="cp1252")).split("\f"):
        lines = [line.strip() for line in page.splitlines()]
        text = "\n".join(lines).strip()
        if text:
            topics.append({"number": len(topics) + 1, "title": text.splitlines()[0], "text": text})
    if not topics or "Contacting The Authors" not in topics[-1]["text"]:
        raise ValueError("RTF does not contain the complete original help, including its last topic")
    return {
        "source_edition": "Tower of the Sorcerer for Windows 1.2, English installation",
        "attribution": "Original help and game by Oz & Kenichi; not covered by the remake's MIT license.",
        "files": files,
        "text_manual": (source / "TSW.txt").read_text(encoding="cp1252"),
        "contents": (source / "Tsw.cnt").read_text(encoding="cp1252"),
        "help_topics": topics,
    }


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--source", type=Path, default=Path(r"D:\Program Files (x86)\Tower of the Sorcerer"))
    options = parser.add_mutually_exclusive_group(required=True)
    options.add_argument("--hlp-rtf", type=Path, help="Complete helpdeco -r output")
    options.add_argument("--helpdeco", type=Path, help="Path to a working helpdeco executable")
    parser.add_argument("--output", type=Path, default=ROOT / "data/help/original.json")
    args = parser.parse_args()
    if args.hlp_rtf:
        result = extract(args.source, args.hlp_rtf)
    else:
        with tempfile.TemporaryDirectory(prefix="tos-help-") as temporary:
            subprocess.run([str(args.helpdeco.resolve()), str((args.source / "Tsw.hlp").resolve()),
                            "-r", "-y"], cwd=temporary, check=True, capture_output=True)
            result = extract(args.source, Path(temporary) / "Tsw.rtf")
    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_text(json.dumps(result, ensure_ascii=False, indent=2) + "\n", encoding="utf-8", newline="\n")
    print(f"Extracted {len(result['help_topics'])} help topics to {args.output}")


if __name__ == "__main__":
    main()
