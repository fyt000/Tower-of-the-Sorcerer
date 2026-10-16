"""Restricted translations of retained runtime UI setters and bounded prefixes.

Generated Pascal is independently compared with the executable. Register-clobber
annotations from the decompiler are the only discarded statements.
"""
from pathlib import Path
import re

ROOT = Path(__file__).resolve().parents[1]
PROPERTIES = {0x24: "Left", 0x28: "Top", 0x2C: "Width", 0x30: "Height"}


def recovered_ui(manifest):
    forms = {f["class_name"]: f for f in manifest["forms"]}
    fields = {name: {int(x["offset"], 16): x["name"] for x in f["fields"]}
              for name, f in forms.items() if f.get("fields")}

    def translate(source, cls):
        def expr(value):
            value = re.sub(r"\*\((?:int|undefined4) \*\)\(\*\(int \*\)\(param_1 \+ (0x[\da-f]+|\d+)\) \+ (0x24|0x28|0x2c|0x30)\)",
                           lambda m: fields[cls][int(m[1], 0)] + "." + PROPERTIES[int(m[2], 0)], value)
            value = re.sub(r"\*\(char \*\)\(\*\(int \*\)\(DAT_0048c510 \+ (0x[\da-f]+)\) \+ 0x28\)",
                           lambda m: "MainForm." + fields["TTSW10"][int(m[1], 0)] + ".Checked", value)
            value = re.sub(r"\*\(int \*\*?\)\(\*\(int \*\)\(param_1 \+ (0x[\da-f]+|\d+)\) \+ 0x44\)",
                           lambda m: fields[cls][int(m[1], 0)] + ".Font", value)
            value = re.sub(r"\*\(int \*\*?\)\(param_1 \+ (0x[\da-f]+|\d+)\)",
                           lambda m: fields[cls][int(m[1], 0)], value)
            value = value.replace("DAT_0048a760", "AboutBox")
            value = value.replace(" == ", " = ").replace(" && ", " and ")
            value = value.replace("'\\x01'", "True")
            value = re.sub(r"\(uint\)DAT_00489b9([cd])", lambda m: "GameOptions[" + str(int(m[1], 16) - 12) + "]", value)
            value = re.sub(r"DAT_00489b9([cdf])", lambda m: "GameOptions[" + str(int(m[1], 16) - 12) + "]", value)
            value = re.sub(r"'\\x0([123])'", r"\1", value)
            value = re.sub(r"0x([\da-f]+)", lambda m: "$" + m[1].upper(), value)
            value = re.sub(r"(GameOptions\[\d+\]) = True", r"\1 = 1", value)
            if "FUN_" in value or "*(" in value or "DAT_" in value or "param_" in value:
                raise ValueError("Unreviewed UI expression: " + value)
            return value

        result = []
        for statement in re.findall(r"[^;{}]+[;{}]|[{}]", source):
            s = " ".join(statement.split())
            if s == "}":
                result.append("end;")
            elif s == "else {":
                result[-1] = result[-1].removesuffix(";")
                result.extend(["else", "begin"])
            elif s.startswith("if (") or s.startswith("else if ("):
                prefix = ""
                if s.startswith("else"):
                    result[-1] = result[-1].removesuffix(";")
                    prefix, s = "else ", s[5:]
                result.extend([prefix + "if " + expr(s[4:-3]) + " then", "begin"])
            elif re.fullmatch(r"uVar[12] = extraout_(?:ECX|EDX)(?:_\d+)?;", s):
                continue
            elif s.startswith("iVar1 = FUN_00419e30("):
                result.append("FontSize := " + expr(s[len("iVar1 = FUN_00419e30("):-2]) + ".Size;")
            elif s.startswith("(**(code **)(**(int **)(param_1 + 0x1bc) + 0x80))()"):
                result.append("Button2.SetFocus;")
            else:
                m = re.fullmatch(r"FUN_([\da-f]{8})\((.*)\);", s)
                if not m:
                    raise ValueError("Unreviewed UI statement: " + s)
                at, args = m.groups()
                parts, depth, start = [], 0, 0
                for i, char in enumerate(args):
                    depth += (char == "(") - (char == ")")
                    if char == "," and depth == 0:
                        parts.append(args[start:i])
                        start = i + 1
                parts.append(args[start:])
                target, value, *clobbers = parts
                target = expr(target.strip())
                value = value.strip()
                prop = {"00413098": "Left", "004130b8": "Top", "004130d8": "Width", "004130f8": "Height",
                        "00419e4c": "Size", "004102f0": "Checked", "00413500": "Visible", "0042c454": "Enabled"}.get(at)
                if prop is None:
                    raise ValueError("Unreviewed UI setter: " + s)
                if prop in ("Visible", "Enabled", "Checked"):
                    if value not in ("0", "1", "'\\0'", "'\\x01'") and not re.fullmatch(
                            r"CONCAT31\(\(int3\)\(\(uint\)(?:uVar2|extraout_EDX(?:_\d+)?) >> 8\),1\)", value):
                        raise ValueError("Unreviewed UI boolean: " + value)
                    value = "False" if value in ("0", "'\\0'") else "True"
                    if prop == "Visible" and len(clobbers) != 1:
                        raise ValueError("Unreviewed visibility ABI")
                else:
                    value = expr(value).replace("iVar1", "FontSize")
                result.append(target + "." + prop + " := " + value + ";")
        return "\n".join("  " + line for line in result) + "\n"

    about = (ROOT / "reference/original/presentation/decompiled/0043416c_TAboutBox_formactivate.c").read_text()
    about = about[about.index("  FUN_004130d8("):about.index("  return;")]
    fonts = (ROOT / "reference/original/whole-program/decompiled/0047d4a4.c").read_text()
    fonts = fonts[fonts.index("  FUN_004102f0("):fonts.index("  FUN_0047f5a8(")]
    startup = (ROOT / "reference/original/whole-program/decompiled/00454de8.c").read_text()
    startup = startup[startup.index("  FUN_00413500("):startup.index("  if (original_hero.cycle_factor_minus_one")]
    if len(re.findall("FUN_00413500", startup)) != 73:
        raise ValueError("Startup hidden-control inventory changed")
    return {"AboutLayout.inc": translate(about, "TAboutBox"),
            "FontLayout.inc": translate(fonts, "TTSW10"),
            "StartupHidden.inc": translate(startup, "TTSW10")}
