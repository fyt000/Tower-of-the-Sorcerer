"""Translate the reviewed control-layout prefix of original syokidata0.

This is a restricted grammar for one retained export, not a general C to
Pascal converter. Every nonlocal statement is either emitted or rejected.
Native/abstract comparisons are still required after translation.
"""
from pathlib import Path
import hashlib
import re

ROOT = Path(__file__).resolve().parents[1]
PROPERTIES = {0x24: "Left", 0x28: "Top", 0x2c: "Width", 0x30: "Height"}
SETTERS = {"00413098": "Left", "004130b8": "Top", "004130d8": "Width",
           "004130f8": "Height", "0042151c": "ClientHeight", "00410378": "Enabled"}


def recover_layout(manifest):
    path = ROOT / "reference/original/whole-program/decompiled/00484f48.c"
    source = path.read_text()
    start = source.index("  iVar1 = FUN_00423ba8();")
    stop = source.index("  FUN_00413500((int *)param_1[0x6e],0,uVar5);")
    source = source[start:stop]
    form = next(f for f in manifest["forms"] if f["class_name"] == "TTSW10")
    fields = {int(f["offset"], 16) // 4: f["name"] for f in form["fields"]}
    # Delphi's integer div 2 compiles to SAR plus negative/odd correction.
    # Consume the complete decompiler idiom, including its correction branch.
    halves = re.compile(r"(iVar[12]) = \(int\)(.*?) >> 1;\s*if \(\1 < 0\) \{\s*"
                        r"\1 = \1 \+ \(uint\)\(\((.*?) & 1\) != 0\);\s*\}", re.S)
    half_count = 0
    def half(match):
        nonlocal half_count
        if match[2].strip() != match[3].strip():
            raise ValueError("Unreviewed signed-half correction")
        half_count += 1
        return match[1] + " = (" + match[2] + ") / 2;"
    source = halves.sub(half, source)

    def expression(text):
        text = re.sub(r"\*\((?:int|uint|undefined4) \*\)\(param_1\[(0x[\da-f]+)\] \+ (0x[\da-f]+)\)",
                      lambda m: fields[int(m[1], 16)] + "." + PROPERTIES[int(m[2], 16)], text)
        text = re.sub(r"\(\(int \*\)param_1\[(0x[\da-f]+)\]\)\[0xb\]",
                      lambda m: fields[int(m[1], 16)] + ".Width", text)
        text = re.sub(r"\*\(int \*\)\(iVar1 \+ (0x[\da-f]+)\)",
                      lambda m: "TControl(Pointer(iVar1))." + PROPERTIES[int(m[1], 16)], text)
        text = re.sub(r"(?:\(int \*\))?param_1\[(0x[\da-f]+)\]",
                      lambda m: fields[int(m[1], 16)], text)
        text = text.replace("DAT_0048c510[0xb]", "Self.Width")
        text = text.replace("DAT_0048c510", "Self").replace("DAT_00489ba4", "OriginalOptions[8]")
        text = text.replace("DAT_0048c578", "UiSpan").replace("DAT_0048c57c", "UiStep")
        text = text.replace("(int)", "").replace("(uint)", "")
        text = text.replace("'\\0'", "0").replace("'\\x01'", "1")
        text = re.sub(r"0x([\da-f]+)", lambda m: "$" + m[1].upper(), text)
        text = text.replace("FUN_00423ba8()", "Screen.Width")
        text = text.replace("FUN_004131bc(param_1)", "Self.ClientHeight")
        text = text.replace("FUN_00413178(param_1)", "Self.ClientWidth")
        text = text.replace("FUN_004131bc(Self)", "Self.ClientHeight")
        text = text.replace(" == ", " = ").replace(" && ", " and ").replace(" / ", " div ")
        text = " ".join(text.split())
        # Reject residual C syntax and identifiers outside the reviewed family.
        tokens = re.findall(r"[A-Za-z_]\w*", re.sub(r"\$[\dA-F]+", "", text))
        allowed = set(fields.values()) | set(PROPERTIES.values()) | {
            "Self", "Screen", "ClientHeight", "ClientWidth", "Width", "OriginalOptions", "UiSpan", "UiStep",
            "iVar1", "iVar2", "uVar11", "div", "and", "TControl", "Pointer"}
        if (any(t not in allowed for t in tokens)
                or re.search(r"[\[\]]", text.replace("OriginalOptions[8]", ""))
                or "*(" in text
                or not re.fullmatch(r"[A-Za-z0-9_.$ \[\]+*()=<>-]+", text)):
            raise ValueError("Unreviewed layout expression: " + text)
        return text

    statements = re.findall(r"[^;{}]+[;{}]|[{}]", source)
    if "".join(statements).replace(" ", "").replace("\n", "") != source.replace(" ", "").replace("\n", ""):
        raise ValueError("Unparsed layout text")
    lines = ["{ Original $00484F48 control layout; restricted grammar, no machine code. }"]
    assignments = setters = 0
    for statement in statements:
        statement = " ".join(statement.split())
        statement = statement.replace(" ;", ";")
        if not statement:
            continue
        if statement == "}":
            lines.append("end;")
        elif statement == "else {":
            lines[-1] = lines[-1].removesuffix(";")
            lines.extend(["else", "begin"])
        elif statement.startswith("if (") or statement.startswith("else if ("):
            is_else = statement.startswith("else")
            if is_else:
                lines[-1] = lines[-1].removesuffix(";")
                statement = statement[5:]
            lines.extend([("else " if is_else else "") + "if " + expression(statement[4:-3]) + " then", "begin"])
        elif re.fullmatch(r"uVar[56] = extraout_ECX(?:_\d+)?;", statement):
            # Only unused decompiler representations of register clobbers.
            continue
        elif statement.startswith("FUN_0040352c((int *)&DAT_0048c5fc,"):
            match = re.fullmatch(r'FUN_0040352c\(\(int \*\)&DAT_0048c5fc,\(undefined4 \*\)"\\\\(data3?)"\);', statement)
            if not match:
                raise ValueError("Unreviewed graphics directory assignment")
            lines.append("DataDirectory := '\\" + match[1] + "';")
            assignments += 1
        elif statement.startswith("FUN_"):
            match = re.fullmatch(r"FUN_([\da-f]{8})\((.*?),(.*)\);", statement)
            if not match or match[1] not in SETTERS:
                raise ValueError("Unreviewed layout setter: " + statement)
            value = expression(match[3])
            if SETTERS[match[1]] == "Enabled":
                if value != "0":
                    raise ValueError("Unreviewed menu enable")
                value = "False"
            lines.append(expression(match[2]) + "." + SETTERS[match[1]] + " := " + value + ";")
            setters += 1
        else:
            match = re.fullmatch(r"(iVar[12]|uVar11|DAT_00489ba4|DAT_0048c578|DAT_0048c57c) = (.*);", statement)
            if not match:
                raise ValueError("Unreviewed layout statement: " + statement)
            value = expression(match[2])
            if value in fields.values():
                value = "Longint(" + value + ")"
            lines.append(expression(match[1]) + " := " + value + ";")
            assignments += 1
    if half_count != 27 or setters != 499:
        raise ValueError(f"Layout inventory changed: {half_count} halves, {setters} setters")
    return "\n".join("  " + line for line in lines) + "\n", dict(
        original_entry="0x00484f48", original_export_sha256=hashlib.sha256(path.read_bytes()).hexdigest(),
        prefix_only=True, signed_halves=half_count, control_setters=setters, assignments=assignments)


def recover_hints(manifest):
    path = ROOT / "reference/original/whole-program/decompiled/00484f48.c"
    source = path.read_text()
    start = source.index('  FUN_0040352c((int *)(param_1[0x7c] + 0x54),')
    stop = source.index('  FUN_00419c7c(', start)
    form = next(f for f in manifest["forms"] if f["class_name"] == "TTSW10")
    fields = {int(f["offset"], 16) // 4: f["name"] for f in form["fields"]}
    result = ["{ Original $00484F48 hint/ShowHint tail; every statement must match. }"]
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
