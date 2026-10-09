"""Recover only the original ranking form's control-layout prefix as Pascal."""
from pathlib import Path
import json
import re
import argparse

from format_delphi import format_source

ROOT = Path(__file__).resolve().parents[1]
PROPERTIES = {0x24: "Left", 0x28: "Top", 0x2C: "Width", 0x30: "Height"}
SETTERS = {"00413098": "Left", "004130b8": "Top", "004130d8": "Width", "004130f8": "Height"}


def recover():
    manifest = json.loads((ROOT / "reference/original/presentation/ui-manifest.json").read_text())
    form = next(f for f in manifest["forms"] if f["class_name"] == "TForm2")
    fields = {int(f["offset"], 16): f["name"] for f in form["fields"]}
    source = (ROOT / "reference/original/presentation/decompiled/00434bc4_TForm2_formactivate.c").read_text()
    start = source.index("  FUN_004130d8(DAT_0048a764,")
    end = min(source.index("  FUN_00413500(", start), source.index("  FUN_004135d4(", start))
    source = source[start:end]
    source = re.sub(r"(iVar[13]) = \(int\)uVar2 >> 1;\s*if \(\1 < 0\) \{\s*"
                    r"\1 = \1 \+ \(uint\)\(\(uVar2 & 1\) != 0\);\s*\}",
                    r"\1 = uVar2 / 2;", source)
    source = re.sub(r"iVar1 = DAT_0048a764\[0xb\] >> 1;\s*if \(iVar1 < 0\) \{\s*"
                    r"iVar1 = iVar1 \+ \(uint\)\(\(DAT_0048a764\[0xb\] & 1U\) != 0\);\s*\}",
                    "iVar1 = Self.Width / 2;", source)

    def expression(value):
        value = re.sub(r"\*\((?:int|uint|undefined4) \*\)\(\*\(int \*\)\(param_1 \+ (0x[\da-f]+|\d+)\) \+ (0x[\da-f]+)\)",
                       lambda m: fields[int(m[1], 0)] + "." + PROPERTIES[int(m[2], 0)], value)
        value = re.sub(r"\(\*\(int \*\*\)\(param_1 \+ (0x[\da-f]+|\d+)\)\)\[0xb\]",
                       lambda m: fields[int(m[1], 0)] + ".Width", value)
        value = re.sub(r"\*\(int \*\*\)\(param_1 \+ (0x[\da-f]+|\d+)\)",
                       lambda m: fields[int(m[1], 0)], value)
        value = value.replace("DAT_0048a764", "Self").replace("FUN_00413178(Self)", "ClientWidth")
        value = value.replace("(int)", "").replace("(uint)", "")
        value = re.sub(r"0x([\da-f]+)", lambda m: "$" + m[1].upper(), value)
        value = " ".join(value.split()).replace(" / ", " div ")
        tokens = re.findall(r"[A-Za-z_]\w*", re.sub(r"\$[\dA-F]+", "", value))
        allowed = set(fields.values()) | set(PROPERTIES.values()) | {"Self", "ClientWidth", "iVar1", "iVar3", "uVar2", "div"}
        if any(t not in allowed for t in tokens) or not re.fullmatch(r"[A-Za-z0-9_.$ +*()/-]+", value):
            raise ValueError("Unreviewed ranking layout expression: " + value)
        return value

    statements = [" ".join(s.split()) for s in source.split(";") if s.strip()]
    result = ["{ Generated ranking column bounds. }"]
    for statement in statements:
        if statement == "_DAT_0048a768 = 0":
            continue
        setter = re.fullmatch(r"FUN_([\da-f]{8})\((.*?),(.*)\)", statement)
        if setter and setter[1] in SETTERS:
            result.append(expression(setter[2]) + "." + SETTERS[setter[1]] + " := " + expression(setter[3]) + ";")
        else:
            assignment = re.fullmatch(r"(iVar1|iVar3|uVar2) = (.*)", statement)
            if not assignment:
                raise ValueError("Unreviewed ranking layout statement: " + statement)
            result.append(assignment[1] + " := " + expression(assignment[2]) + ";")
    return "\n".join("  " + line for line in result) + "\n"


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--check", action="store_true")
    args = parser.parse_args()
    text = format_source("RankingLayout.inc", recover())
    target = ROOT / "delphi/src/generated/RankingLayout.inc"
    if args.check:
        if target.read_text(encoding="utf-8") != text:
            raise ValueError("Stale ranking layout")
    else:
        target.write_text(text, encoding="utf-8", newline="\n")
    print("Ranking layout verified")
