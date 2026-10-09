"""Inventory recovered UI effects and unresolved calls; never infer purity.

This is review triage, not alias analysis or a complete Windows call graph.
Run after extract_original_ui.py and RecoverPresentation.java.
"""
from pathlib import Path
import argparse
import hashlib
import json
import re

ROOT = Path(__file__).resolve().parents[1]
PRESENTATION = ROOT / "reference/original/presentation"
WRITE = re.compile(r"(?:original_hero|original_maps|original_monsters|event_stack|event_cursor|dialogue_continue_stage).*?\s=(?!=)")


def inventory():
    manifest = json.loads((PRESENTATION / "ui-manifest.json").read_text())
    sources = {int(path.name[:8], 16): path for path in sorted((ROOT / "reference/original/decompiled").glob("*.c"))}
    recovered = {int(path.name[:8], 16): path for path in sorted((PRESENTATION / "decompiled").glob("*.c"))}
    sources.update(recovered)
    rows = {}
    for address, path in sorted(sources.items()):
        source = path.read_text(encoding="utf-8")
        asm_path = path.with_suffix(".asm")
        direct, indirect = [], []
        if asm_path.exists():
            for line in asm_path.read_text().splitlines():
                match = re.match(r"([0-9a-f]{8})\s+[0-9a-f]+\s+(CALL|JMP) (.*)", line)
                if not match:
                    continue
                site, kind, target = match.groups()
                if re.fullmatch("0x[0-9a-f]+", target):
                    if kind == "CALL" or (int(target, 16) in sources and int(target, 16) != address):
                        direct.append(dict(site="0x" + site, kind=kind.lower(), target=target))
                elif kind == "CALL":
                    indirect.append(dict(site="0x" + site, operand=target))
        else:
            # Old source-only entries cannot supply instruction call-site evidence.
            direct = [dict(site=None, kind="decompiler-reference", target="0x" + target)
                      for target in sorted(set(re.findall(r"(?:FUN_|func_0x)([0-9a-f]{8})\(", source)))]
        effects = [dict(line=i, text=line.strip()) for i, line in enumerate(source.splitlines(), 1) if WRITE.search(line)]
        rows[address] = dict(address=f"0x{address:08x}", source=str(path.relative_to(ROOT)),
                             source_sha256=hashlib.sha256(path.read_bytes()).hexdigest(),
                             assembly=str(asm_path.relative_to(ROOT)) if asm_path.exists() else None,
                             assembly_sha256=hashlib.sha256(asm_path.read_bytes()).hexdigest() if asm_path.exists() else None,
                             decompiled="FAILED:" not in source, named_protected_writes=effects,
                             direct_edges=direct, unresolved_indirect_calls=indirect,
                             review_status="triage-only; see REVIEW.md for branch and sequence review")
    for address, row in rows.items():
        reached, todo = set(), [address]
        while todo:
            target = todo.pop()
            if target in reached or target not in rows:
                continue
            reached.add(target)
            todo.extend(int(edge["target"], 16) for edge in rows[target]["direct_edges"])
        row["direct_reachable_protected_writers"] = [f"0x{target:08x}" for target in sorted(reached)
                                                    if rows[target]["named_protected_writes"]]
        row["unexported_direct_application_targets"] = sorted({edge["target"] for target in reached
            for edge in rows[target]["direct_edges"] if 0x434000 <= int(edge["target"], 16) < 0x489000 and int(edge["target"], 16) not in rows})
    events = []
    missing = []
    published = {int(method["address"], 16) for form in manifest["forms"] for method in form["methods"]}
    missing_published = [f"0x{address:08x}" for address in sorted(published)
                         if address not in recovered or not rows[address]["decompiled"]]
    failed_recovered = [f"0x{address:08x}" for address in sorted(recovered) if not rows[address]["decompiled"]]
    unexported_direct = sorted({int(edge["target"], 16) for row in rows.values()
                               for edge in row["direct_edges"] if int(edge["target"], 16) not in rows})
    for event in manifest["events"]:
        address = int(event["address"], 16)
        row = rows.get(address)
        if address not in recovered or not row or not row["decompiled"]:
            missing.append(event)
        events.append(dict(**event, source=row["source"] if row else None,
                           direct_reachable_protected_writers=row["direct_reachable_protected_writers"] if row else [],
                           unresolved_indirect_calls=len(row["unresolved_indirect_calls"]) if row else None))
    report = dict(original_sha256=manifest["original_sha256"], form_count=len(manifest["forms"]),
                  component_count=sum(f["components"] for f in manifest["forms"]),
                  event_bindings=len(events), published_methods=sum(len(f["methods"]) for f in manifest["forms"]),
                  recovered_entries=len(recovered), missing_event_exports=missing,
                  missing_published_exports=missing_published, failed_recovered_exports=failed_recovered,
                  direct_targets_without_exported_entry=[f"0x{address:08x}" for address in unexported_direct],
                  methods=list(rows.values()), events=events,
                  limits="Named assignments and recovered direct calls only. Aliases, virtual dispatch, Windows messages, dynamic event assignments, return values of skipped calls, and unexecuted branches remain outside this automatic inventory. No routine is classified as pure by absence of named writes.")
    return report


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--check", action="store_true")
    args = parser.parse_args()
    report = inventory()
    rendered = json.dumps(report, indent=2) + "\n"
    path = PRESENTATION / "effect-inventory.json"
    if args.check:
        if path.read_text() != rendered:
            raise RuntimeError("UI effect inventory is stale; regenerate and review changes")
    else:
        path.write_text(rendered, encoding="utf-8")
        lines = ["# Serialized UI event coverage", "", "Every binding below was recovered structurally from a Delphi form resource and resolved through its class method table. This is an entry-point inventory; review and sequence evidence are in [REVIEW.md](REVIEW.md).", "", "| Form / component | Event | Published method | Entry | Recovered source |", "|---|---|---|---|---|"]
        for event in report["events"]:
            path_label = Path(event["source"]).name if event["source"] else "MISSING"
            relative = "decompiled/" + path_label
            lines.append(f"| {event['form']} / {event['component']} | {event['event']} | {event['method']} | `{event['address']}` | [{path_label}]({relative}) |")
        (PRESENTATION / "EVENTS.md").write_text("\n".join(lines) + "\n", encoding="utf-8")
    print(json.dumps({key: report[key] for key in ("form_count", "component_count", "event_bindings", "published_methods", "recovered_entries", "missing_event_exports")}, indent=2))
    if report["missing_event_exports"] or report["missing_published_exports"] or report["failed_recovered_exports"]:
        raise RuntimeError("UI event, published method, or runtime recovery is incomplete")


if __name__ == "__main__":
    main()
