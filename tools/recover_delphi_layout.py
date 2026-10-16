"""Recover item and control hints from the reviewed syokidata0 export."""
from pathlib import Path
import re

ROOT = Path(__file__).resolve().parents[1]


def recover_hints(manifest):
    path = ROOT / "reference/original/whole-program/decompiled/00484f48.c"
    source = path.read_text()
    start = source.index('  FUN_0040352c((int *)(param_1[0x7c] + 0x54),')
    stop = source.index('  FUN_00419c7c(', start)
    form = next(f for f in manifest["forms"] if f["class_name"] == "TTSW10")
    fields = {int(f["offset"], 16) // 4: f["name"] for f in form["fields"]}
    result = ["{ Generated item and control hints. }"]
    hints = show_hints = 0
    for line in source[start:stop].splitlines():
        hint = re.fullmatch(r'  FUN_0040352c\(\(int \*\)\(param_1\[(0x[\da-f]+)\] \+ 0x54\),\(undefined4 \*\)(.*)\);', line)
        shown = re.fullmatch(r"  FUN_004136ac\(\(int \*\)param_1\[(0x[\da-f]+)\],'\\x01'\);", line)
        if hint:
            text = hint[2]
            if text == "&DAT_00488b9c":
                text = '"Gold"'  # Retained EXE bytes at $00488B9C, no inferred localization.
            if not re.fullmatch(r'"[ A-Za-z0-9.]+"', text):
                raise ValueError("Unreviewed hint literal: " + text)
            result.append("  " + fields[int(hint[1], 16)] + ".Hint := '" + text[1:-1] + "';")
            hints += 1
        elif shown:
            result.append("  " + fields[int(shown[1], 16)] + ".ShowHint := True;")
            show_hints += 1
        else:
            raise ValueError("Unreviewed hint statement: " + line)
    if hints != 46 or show_hints != 31:
        raise ValueError(f"Hint inventory changed: {hints}, {show_hints}")
    return "\n".join(result) + "\n"
