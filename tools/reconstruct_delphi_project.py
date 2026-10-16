"""Generate DFM bindings, record fields, initialization, and control layouts."""
from pathlib import Path
import argparse
import hashlib
import json
import re

from format_delphi import format_source, formatter
from extract_original_ui import walk
from prepare_research import require_cache

ROOT = Path(__file__).resolve().parents[1]
OUT = ROOT / "delphi/src/generated"
INVENTORY = ROOT / "build/delphi-game/reports/method-inventory.json"
FIELD_NAMES = {20: "highest_floor", 164: "sacred_shield", 352: "facing",
               356: "effects_muted", 360: "music_track", 680: "save_version"}


def output_path(name):
    return INVENTORY if name == "method-inventory.json" else OUT / name


def sha(raw):
    return hashlib.sha256(raw).hexdigest()


def hero_fields():
    java = (ROOT / "tools/ghidra/ExportOriginal.java").read_text()
    section = java.split("Object[][] fields = {", 1)[1].split("};", 1)[0]
    return {**{int(offset, 16): name for offset, name in re.findall(r'\{(0x[\da-f]+),"(\w+)"\}', section)},
            **FIELD_NAMES}


def pas_name(name):
    match = re.fullmatch(r"_(\d+)_4_", name)
    if match:
        return hero_fields().get(int(match[1]), "Word" + match[1])
    return name


def expression(text):
    text = re.sub(r"original_hero\.(\w+)", lambda m: "Hero." + pas_name(m[1]), text)
    text = re.sub(r"original_maps\[(\d+)\]\[(\d+)\]", r"Maps[\1, \2]", text)
    text = re.sub(r"0x([\da-f]+)", lambda m: "$" + m[1].upper(), text)
    return text.replace(" == ", " = ")


def initialization():
    path = ROOT / "build/research/decompilation/whole-program/decompiled/00455cb8.c"
    source = path.read_text()
    source = source.split("void initialize_cycle(void)", 1)[1].strip()
    lines = source.splitlines()
    if lines[0] != "{" or lines[-1] != "}":
        raise ValueError("Unreviewed initialization structure")
    result = ["{ Original cycle reset, retained as individual stores for routine byte correspondence.",
              "  Fresh cycles reset combat stats; later cycles preserve selected progress.",
              "  Map columns 0/1 hold stair destinations; columns 2..122 are the 11x11 tiles. }"]
    conditions = assignments = 0
    for line in lines[1:-1]:
        stripped = line.strip()
        indent = line[:len(line) - len(line.lstrip())]
        if not stripped or stripped == "return;":
            continue
        if re.fullmatch(r"if \(original_hero\.(?:cycle_factor_minus_one|later_cycle) == 0\) \{", stripped):
            result.extend([indent + "if " + expression(stripped[4:-3]) + " then", indent + "begin"])
            conditions += 1
        elif stripped == "}":
            result.append(indent + "end;")
        elif re.fullmatch(r"(?:original_hero\.\w+|original_maps\[\d+\]\[\d+\]) = (?:0x[\da-f]+|\d+);", stripped):
            left, right = stripped.split(" = ")
            floor = re.fullmatch(r"original_maps\[(\d+)\]\[0\]", left)
            if floor:
                result.append(indent + "{ Floor " + floor[1] + ": reset stair destinations and every map cell. }")
            elif left == "original_hero._364_4_":
                result.append(indent + "{ Reset persisted story flags and event progress before restoring the maps. }")
            result.append(indent + expression(left) + " := " + expression(right))
            assignments += 1
        else:
            raise ValueError("Unsupported initialization statement: " + stripped)
    if conditions != 4 or assignments != 6439:
        raise ValueError(f"Initialization inventory changed: {conditions}, {assignments}")
    return "\n".join(result) + "\n", dict(original_entry="0x00455cb8", original_export_sha256=sha(path.read_bytes()),
                                         conditions=conditions, assignments=assignments)


def parameters(events):
    kinds = set(events)
    if not kinds:
        return ""
    if kinds <= {"OnActivate", "OnClick", "OnTimer", "OnChange", "OnNotify"}:
        return "(Sender: TObject)"
    if kinds == {"OnClose"}:
        return "(Sender: TObject; var Action: TCloseAction)"
    if kinds == {"OnKeyDown"}:
        return "(Sender: TObject; var Key: Word; Shift: TShiftState)"
    if kinds <= {"OnMouseDown", "OnMouseUp"}:
        return "(Sender: TObject; Button: TMouseButton; Shift: TShiftState; X, Y: Integer)"
    raise ValueError("Unreviewed event signatures: " + repr(kinds))


def forms(manifest, implemented):
    declaration, inventory = [], []
    for form in manifest["forms"]:
        cls = form["class_name"]
        components = {c["name"].lower(): c for c in walk(form["tree"])}
        declaration.extend([f"  {cls} = class(TForm)", "  published"])
        for field in form.get("fields", []):
            component = components[field["name"].lower()]
            declaration.append(f"    {field['name']}: {component['class_name']};")
        if not form.get("fields"):
            for component in list(walk(form["tree"]))[1:]:
                declaration.append(f"    {component['name']}: {component['class_name']};")
        for method in form["methods"]:
            events = [e for e in manifest["events"] if e["form"] == cls and e["method"].lower() == method["name"].lower()]
            param = parameters(e["event"] for e in events)
            if cls == "TForm2" and method["name"].lower() in ("hyouji", "scoreload"):
                param = "(Category: Byte)"
            if cls == "TTSW10" and method["name"].lower() == "itemichiwork":
                param = "(Direction: Longint)"
            declaration.append(f"    procedure {method['name']}{param};")
            key = cls + "." + method["name"]
            recovered = key.lower() in implemented
            if not recovered:
                raise ValueError("Missing published method body: " + key)
            inventory.append(dict(form=cls, method=method["name"], original_entry=method["address"],
                                  events=[e["event"] for e in events],
                                  status="implemented"))
        if cls == "TTSW10":
            declaration.extend(["  public", "    constructor Create(AOwner: TComponent); override;",
                                "    procedure PortableActivate(Sender: TObject);"])
        if cls == "TForm4":
            declaration.extend(["  public", "    procedure SelectPortableFolder(Sender: TObject);"])
        declaration.extend(["  end;", ""])
    return "\n".join(declaration) + "\n", inventory


def generated():
    manifest = json.loads((ROOT / "build/research/decompilation/presentation/ui-manifest.json").read_text())
    manual = "\n".join(path.read_text() for path in (ROOT / "delphi/src").glob("*")
                       if path.suffix in (".pas", ".inc"))
    implemented = {name.lower() for name in re.findall(r"^procedure (T\w+\.\w+)", manual, re.M)}
    declarations, inventory = forms(manifest, implemented)
    init, init_record = initialization()
    fields = hero_fields()
    record = ("{ WordN names retain byte offsets for fields whose meaning is unknown. }\n" +
              "\n".join("    " + fields.get(offset, "Word" + str(offset)) + ": Longint;"
                        for offset in range(0, 684, 4)) + "\n")
    report = dict(schema_version=1, original_sha256=manifest["original_sha256"],
                  accepted_difference="English Delphi 2 VCL lacks Japanese IME support. Original serialized resources remain intact.",
                  initialization=init_record, methods=inventory,
                  serialized_events=len(manifest["events"]), published_methods=len(inventory),
                  implemented_methods=len(inventory), missing_methods=0,
                  complete_published_coverage=True,
                  complete_game_recovered=False)
    smoke = []
    for form in manifest["forms"]:
        cls = form["class_name"]
        smoke.extend([f"  if Form.ClassName = '{cls}' then", "  begin"])
        for field in form.get("fields", []):
            smoke.append(f"    CheckField(Form, '{field['name']}', {int(field['offset'],16) - 4});")
        for method in form["methods"]:
            smoke.append(f"    CheckPublishedMethod(Form, '{method['name']}');")
        for event in manifest["events"]:
            if event["form"] == cls:
                smoke.append(f"    CheckBinding(Form, '{event['component']}', '{event['event']}', '{event['method']}');")
        smoke.extend(["  end;", ""])
    from recover_delphi_layout import recover_hints
    from recover_delphi_ui import recovered_ui
    result = {"HeroFields.inc": record, "InitializeCycle.inc": init,
            "GraphicsHints.inc": recover_hints(manifest),
            "FormDeclarations.inc": declarations,
            "FormChecks.inc": "\n".join(smoke) + "\n",
            "method-inventory.json": json.dumps(report, indent=2) + "\n", **recovered_ui(manifest)}
    executable = formatter()
    return {name: format_source(name, text, executable) if name.endswith(".inc") else text
            for name, text in result.items()}


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--check", action="store_true")
    args = parser.parse_args()
    try:
        require_cache(decompile=True)
    except ValueError as error:
        parser.exit(1, str(error) + "\n")
    OUT.mkdir(parents=True, exist_ok=True)
    for name, content in generated().items():
        path = output_path(name)
        if args.check:
            if path.read_text(encoding="utf-8") != content:
                raise ValueError("Stale reconstructed declaration: " + name)
        else:
            path.parent.mkdir(parents=True, exist_ok=True)
            path.write_text(content, encoding="utf-8", newline="\n")
    print("Delphi bindings, initialization, layouts, and method coverage verified")


if __name__ == "__main__":
    main()
