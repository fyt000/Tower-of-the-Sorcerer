"""Inventory Delphi exception continuations omitted by parent function exports.

This is a bounded static audit of published original game methods, not an
exhaustive exception/CFG or semantic recovery claim. Retain undecoded/indirect
exits and distinguish absence from the parent export from absence in all exports.
"""
import argparse
import json
import re

import capstone
import pefile

from verify_delphi2_reference import ROOT, ORIGINAL_HASH, digest

EXPORTS = ROOT / "reference/original/whole-program/decompiled"
OUT = ROOT / "reference/original/whole-program/exception-paths"
DISPATCHERS = {0x402F4C: "@HandleAnyException", 0x403140: "@HandleFinally"}


def exported_instructions(path):
    return {int(at, 16): bytes.fromhex(raw) for at, raw in
            re.findall(r"^([\da-f]{8})  ([\da-f]+) ", path.read_text(), re.M)}


def audit():
    original = ROOT / "build/research/TSW.exe"
    if digest(original) != ORIGINAL_HASH:
        raise ValueError("Original pin changed")
    pe = pefile.PE(str(original))
    base = pe.OPTIONAL_HEADER.ImageBase
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    md.detail = True
    manifest = json.loads((ROOT / "reference/original/presentation/ui-manifest.json").read_text())
    methods = [(form["class_name"] + "." + method["name"], int(method["address"], 16))
               for form in manifest["forms"] for method in form["methods"]]
    all_exports = set()
    export_owners = {}
    for path in sorted(EXPORTS.glob("*.asm")):
        addresses = exported_instructions(path)
        all_exports.update(addresses)
        for address in addresses:
            export_owners.setdefault(address, set()).add(path.stem)
    bodies = {}
    rows = []
    for name, entry in methods:
        parent = exported_instructions(EXPORTS / f"{entry:08x}.asm")
        insns = [next(md.disasm(raw, at)) for at, raw in parent.items()]
        for index, ins in enumerate(insns[:-2]):
            following = insns[index + 1:index + 3]
            if (ins.mnemonic != "push" or ins.operands[0].type != capstone.x86.X86_OP_IMM
                    or following[0].mnemonic != "push" or following[1].mnemonic != "mov"
                    or following[0].operands[0].type != capstone.x86.X86_OP_MEM
                    or following[0].operands[0].mem.segment != capstone.x86.X86_REG_FS
                    or following[1].operands[0].type != capstone.x86.X86_OP_MEM
                    or following[1].operands[0].mem.segment != capstone.x86.X86_REG_FS):
                continue
            handler = ins.operands[0].imm
            thunk = next(md.disasm(pe.get_data(handler - base, 5), handler))
            if thunk.mnemonic != "jmp" or thunk.operands[0].type != capstone.x86.X86_OP_IMM:
                rows.append(dict(method=name, original_entry=hex(entry), handler=hex(handler),
                                 kind="unrecognized-handler", reviewed=False))
                continue
            dispatcher = thunk.operands[0].imm
            pending = [handler + 5] if dispatcher in DISPATCHERS else []
            visited, exits = {}, []
            while pending:
                at = pending.pop()
                if at in visited:
                    continue
                if not 0x43416C <= at < 0x488B9C:
                    exits.append(dict(address=hex(at), reason="outside-retained-game-range")); continue
                if len(visited) >= 4096:
                    exits.append(dict(address=hex(at), reason="instruction-bound")); break
                decoded = list(md.disasm(pe.get_data(at - base, 15), at, count=1))
                if not decoded:
                    exits.append(dict(address=hex(at), reason="decode-failure")); continue
                item = decoded[0]
                visited[at] = item
                end = at + item.size
                if item.mnemonic.startswith("ret"):
                    continue
                if item.mnemonic == "call" and item.operands[0].type == capstone.x86.X86_OP_IMM and item.operands[0].imm == 0x403268:
                    exits.append(dict(address=hex(at), reason="@DoneExcept-runtime-transfer")); continue
                if item.mnemonic.startswith("j") or item.mnemonic.startswith("loop"):
                    if item.operands[0].type == capstone.x86.X86_OP_IMM:
                        pending.append(item.operands[0].imm)
                    else:
                        exits.append(dict(address=hex(at), reason="indirect-control-transfer"))
                    if item.mnemonic == "jmp":
                        continue
                pending.append(end)
            lines = [f"; Exception continuation for {name}; handler {handler:#010x}",
                     f"; Original SHA-256 {ORIGINAL_HASH}",
                     "; Bounded direct CFG; calls are retained, not inlined; unresolved exits are in inventory.json."]
            lines.extend(f"{at:08x}  {item.bytes.hex()}  {item.mnemonic.upper()} {item.op_str}"
                         for at, item in sorted(visited.items()))
            missing_parent = [at for at in visited if at not in parent]
            missing_all = [at for at in visited if at not in all_exports]
            record = dict(method=name, original_entry=hex(entry), handler=hex(handler),
                          dispatcher=hex(dispatcher), kind=DISPATCHERS.get(dispatcher, "unrecognized-dispatcher"),
                          instructions=len(visited), instruction_bytes=sum(item.size for item in visited.values()),
                          omitted_from_parent_export=len(missing_parent), omitted_from_all_exports=len(missing_all),
                          absent_addresses=[hex(at) for at in sorted(missing_all)], unresolved_exits=exits,
                          continuation_export_owners=sorted({owner for at in visited for owner in export_owners.get(at, ())
                                                              if owner != f"{entry:08x}"}),
                          assembly_file=f"{handler:08x}.asm", semantic_recovery_proven=False)
            rows.append(record)
            bodies[f"{handler:08x}.asm"] = "\n".join(lines) + "\n"
    report = dict(schema_version=1, original_sha256=ORIGINAL_HASH, published_methods=len(methods),
                  exception_frames=len(rows), frames_with_parent_omissions=sum(r.get("omitted_from_parent_export", 0) > 0 for r in rows),
                  frames_with_global_omissions=sum(r.get("omitted_from_all_exports", 0) > 0 for r in rows), frames=rows,
                  complete_exception_recovery=False,
                  limits=["Only retained published-method instructions that install a Delphi FS catch/finally frame are scanned. Omitted parent instructions can themselves hide further frames.",
                          "Continuation roots are recognized only for @HandleAnyException and @HandleFinally. Typed/unknown handlers are retained as unresolved.",
                          "Calls are recorded but not inlined; Windows dispatch and exception/unwind runtime are not executed by this audit.",
                          "This supplements the existing structural ledger; it does not relabel prior decompilation or establish semantic equivalence."])
    bodies["inventory.json"] = json.dumps(report, indent=2) + "\n"
    return bodies, report


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--check", action="store_true")
    args = parser.parse_args()
    bodies, report = audit()
    OUT.mkdir(parents=True, exist_ok=True)
    for name, content in bodies.items():
        path = OUT / name
        if args.check:
            if not path.exists() or path.read_text(encoding="utf-8") != content:
                raise ValueError("Stale exception continuation evidence: " + name)
        else:
            path.write_text(content, encoding="utf-8")
    print("Published-method exception frames", report["exception_frames"], "parent omissions",
          report["frames_with_parent_omissions"], "absent from all exports", report["frames_with_global_omissions"])


if __name__ == "__main__":
    main()
