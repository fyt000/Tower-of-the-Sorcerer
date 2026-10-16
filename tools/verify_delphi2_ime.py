"""Verify independently reconstructed IMECtrl helpers and public declarations.

Only the compiler runs natively. The DLL is executed in Unicorn with explicitly
modeled Windows IME APIs; traces include order, arguments, returns and outputs.
The full dispatcher span includes its embedded five-entry jump table.
"""
from pathlib import Path
import argparse
import html
import itertools
import json
import re
import struct
import subprocess
import zipfile

import pefile
import unicorn
from unicorn.x86_const import UC_X86_REG_EAX, UC_X86_REG_ESP

from build_delphi2_reference import stage
from delphi2_toolchain import describe, validate_media
from verify_delphi2_reference import ROOT, ORIGINAL_HASH, digest, emulator, execute

DIFF_ZIP_HASH = "9d998eaa662e6f22b28f12eeb73934d5e42279a77243cf0856b3f6ab9c0ae968"
API = {
    "WINNLSEnableIME": (0x48A628, 2),
    "ImmGetContext": (0x48A630, 1),
    "ImmGetConversionStatus": (0x48A634, 3),
    "ImmReleaseContext": (0x48A638, 2),
    "ImmSetOpenStatus": (0x48A63C, 2),
    "ImmSetConversionStatus": (0x48A640, 3),
}


def build_probe(toolchain, work):
    compiler = toolchain / "base/bin/DCC32.EXE"
    record = dict(compiler=describe(compiler), media_manifest=describe(toolchain / "media-manifest.json"))
    work.mkdir(exist_ok=True)
    record["inputs"] = [stage(ROOT / name, work / Path(name).name) for name in
                        ("tools/delphi2/probes/ImeRecoveryProbe.dpr", "tools/delphi2/recovered/RecoveredIme.pas")]
    command = [str(compiler), "-B", "-U..\\base\\lib", "-GD", "ImeRecoveryProbe.dpr"]
    result = subprocess.run(command, cwd=work, capture_output=True, timeout=30)
    (work / "compile.log").write_bytes(result.stdout + result.stderr)
    record.update(compile_exit=result.returncode, arguments=command[1:], compile_log=describe(work / "compile.log"))
    if result.returncode:
        raise ValueError("IME recovery compilation failed; retained compile.log")
    record["artifacts"] = [describe(work / n) for n in ("ImeRecoveryProbe.dll", "ImeRecoveryProbe.map")]
    (work / "build-report.json").write_text(json.dumps(record, indent=2) + "\n", encoding="utf-8")
    return record


def validate_build(work, build):
    for record in [build["compiler"], build["media_manifest"], build["compile_log"], *build["artifacts"]]:
        if digest(Path(record["path"])) != record["sha256"]:
            raise ValueError("IME build input/artifact changed")
    for source in build["inputs"]:
        if digest(ROOT / source["source"]) != source["source_sha256"] or digest(work / Path(source["source"]).name) != source["staged_sha256"]:
            raise ValueError("IME Pascal source changed")


def dispatcher_bytes(pe, address):
    raw = bytearray(pe.get_data(address - pe.OPTIONAL_HEADER.ImageBase, 253))
    # Require the exact indexed indirect branch and its expected table location.
    if raw[167:170] != b"\xFF\x24\x85" or struct.unpack_from("<I", raw, 170)[0] != address + 174:
        raise ValueError("Dispatcher jump table structure changed")
    relocations = [dict(offset=170, original_value=address + 174, relative_value=174)]
    struct.pack_into("<I", raw, 170, 174)
    for offset in range(174, 194, 4):
        target = struct.unpack_from("<I", raw, offset)[0]
        if not address + 194 <= target < address + 253:
            raise ValueError("Jump table target outside its local branch bodies")
        relocations.append(dict(offset=offset, original_value=target, relative_value=target - address))
        struct.pack_into("<I", raw, offset, target - address)
    return bytes(raw), relocations


def fixture(pe, address, inputs, helper=False):
    machine = emulator(pe)
    trace = []
    read_count = [0]
    machine.mem_write(0x3FD000, bytes(0x2000))
    machine.mem_write(0x48A624, struct.pack("<I", int(inputs.get("library", True))))
    def observer(u, at, size, _):
        if at not in observers:
            return
        name, argc = observers[at]
        stack = u.reg_read(UC_X86_REG_ESP)
        args = list(struct.unpack("<" + "I" * argc, u.mem_read(stack + 4, argc * 4)))
        event = dict(api=name, arguments=args)
        result = inputs.get("api_result", 1)
        if name == "ImmGetContext":
            result = 0x77 if inputs["context"] else 0
        elif name == "ImmGetConversionStatus":
            conversion, sentence = inputs["conversion"][min(read_count[0], 1)]
            read_count[0] += 1
            u.mem_write(args[1], struct.pack("<I", conversion))
            u.mem_write(args[2], struct.pack("<I", sentence))
            # Stack locations differ by entry address; compare logical API
            # output arguments rather than private scratch pointer values.
            event["arguments"] = [args[0], "conversion-output", "sentence-output"]
            event["outputs"] = dict(conversion=conversion, sentence=sentence)
        if name in ("WINNLSEnableIME", "ImmSetOpenStatus"):
            event["arguments"][1] &= 0xFF
        event["return"] = result
        trace.append(event)
        u.reg_write(UC_X86_REG_EAX, result & 0xFFFFFFFF)
    observers = {}
    for index, (name, (slot, argc)) in enumerate(API.items()):
        at = 0x3FC000 + index * 0x10
        observers[at] = (name, argc)
        machine.mem_write(at, b"\xC2" + struct.pack("<H", argc * 4))
        assigned = not (helper and name == "WINNLSEnableIME" and not inputs["assigned"])
        machine.mem_write(slot, struct.pack("<I", at if assigned else 0))
    def writer(u, access, at, size, value, _):
        if not 0x3FD000 <= at < 0x3FF000 or at + size > 0x3FF000:
            raise ValueError(f"Unexpected non-stack IME write: {at:#x}")
    machine.hook_add(unicorn.UC_HOOK_CODE, observer)
    machine.hook_add(unicorn.UC_HOOK_MEM_WRITE, writer)
    execute(machine, address, eax=0x2345, edx=inputs["enable"] if helper else inputs["mode"])
    result = dict(api_trace=trace)
    if helper:
        result["result"] = machine.reg_read(UC_X86_REG_EAX)
    return result


def public_declarations(inventory):
    root = ROOT / "build/research/ime-web"
    if digest(root / "diff.zip") != DIFF_ZIP_HASH:
        raise ValueError("Unreviewed public declaration archive")
    with zipfile.ZipFile(root / "diff.zip") as archive:
        if archive.read("Diff.chm") != (root / "Diff.chm").read_bytes():
            raise ValueError("CHM differs from downloaded archive")
    def enum(version):
        path = root / f"docs/Diff/{version}/VCL/Controls.html"
        text = path.read_text(encoding="utf-8")
        section = text.split('name="TImeMode"', 1)[1].split("</ul>", 1)[0]
        return re.findall(r"<li>\s*(\w+):", section)
    doc_enum = enum(2)
    original_enum = next(t["values"] for t in inventory["referenced_types"] if t["name"] == "TImeMode")
    wincontrol = (root / "docs/Diff/2/VCL/Controls.TWinControl.html").read_text(encoding="utf-8")
    plain = re.sub(r"\s+", " ", html.unescape(re.sub("<[^>]+>", " ", wincontrol)))
    report = dict(author_page="https://ht-deko.com/tech053.html#DIFFCHM",
        download_url="https://ht-deko.com/Delphi/archives/diff.zip", archive=describe(root / "diff.zip"),
        chm=describe(root / "Diff.chm"), declaration_only=True, implementation_bodies_present=False,
        extracted_pages=[describe(p) for p in sorted((root / "docs").rglob("*.html"))],
        delphi2_enum=doc_enum, original_enum=original_enum, enum_order_matches_original=doc_enum == original_enum,
        delphi3_enum=enum(3), documented_backing_field="FImeFlag",
        documented_virtual_methods=[name for name in ("SetImeMode", "ResetImeMode") if f"procedure {name} ; virtual;" in plain],
        documented_helper_unit="IMECtrl", helpers=["SetImeStatus", "WINNLSEnableIME"])
    if not report["enum_order_matches_original"] or len(report["documented_virtual_methods"]) != 2 or "read FImeFlag write FImeFlag" not in plain:
        raise ValueError("Public declaration corroboration failed")
    return report


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--check", action="store_true")
    args = parser.parse_args()
    toolchain = ROOT / "build/research/delphi2"
    validate_media(toolchain)
    work = toolchain / "ime-recovery-probe"
    build = json.loads((work / "build-report.json").read_text()) if args.check else build_probe(toolchain, work)
    validate_build(work, build)
    original_path = ROOT / "build/research/TSW.exe"
    if digest(original_path) != ORIGINAL_HASH:
        raise ValueError("Original differs from pin")
    original = pefile.PE(str(original_path))
    candidate = pefile.PE(str(work / "ImeRecoveryProbe.dll"))
    entries = {s.name.decode("ascii"): candidate.OPTIONAL_HEADER.ImageBase + s.address for s in candidate.DIRECTORY_ENTRY_EXPORT.symbols}
    inventory = json.loads((ROOT / "build/research/decompilation/whole-program/structural-inventory.json").read_text())
    old, old_reloc = dispatcher_bytes(original, 0x40EE88)
    new, new_reloc = dispatcher_bytes(candidate, entries["RecoveredSetImeStatus"])
    old_helper = original.get_data(0x40EE6C - original.OPTIONAL_HEADER.ImageBase, 27)
    new_helper = candidate.get_data(entries["RecoveredEnableIme"] - candidate.OPTIONAL_HEADER.ImageBase, 27)
    report = dict(schema_version=1, original_sha256=ORIGINAL_HASH, build_report=describe(work / "build-report.json"),
        source=build["inputs"], public_reference=public_declarations(inventory),
        byte_comparisons=dict(enable_helper=dict(bytes=27, literal_byte_match=old_helper == new_helper),
            dispatcher=dict(bytes_including_jump_table=253, instruction_bytes=233, embedded_table_bytes=20,
                normalized_byte_match=old == new, original_relocations=old_reloc, compiled_relocations=new_reloc,
                scope="Only six local jump-table addresses become relative offsets. All other bytes, API-pointer slots, conditions and constants remain literal.")),
        mode_fixtures=[], enable_fixtures=[])
    conversion = [((0, 0), (0, 0)), ((0xFFFFFFFF, 0x234), (0x12345678, 0x456)), ((0xABCD0004, 0x77), (0x9876000B, 0x99))]
    for mode, library, context, values, api_result in itertools.product(list(range(9)) + [9, 255], (False, True), (False, True), conversion, (0, 1)):
        inputs = dict(mode=mode, library=library, context=context, conversion=values, api_result=api_result)
        a = fixture(original, 0x40EE88, inputs)
        b = fixture(candidate, entries["RecoveredSetImeStatus"], inputs)
        report["mode_fixtures"].append(dict(inputs=inputs, original=a, compiled=b, passed=a == b))
    for assigned, enable, api_result in itertools.product((False, True), (False, True), (0, 1, 7)):
        inputs = dict(assigned=assigned, enable=enable, api_result=api_result)
        a = fixture(original, 0x40EE6C, inputs, helper=True)
        b = fixture(candidate, entries["RecoveredEnableIme"], inputs, helper=True)
        report["enable_fixtures"].append(dict(inputs=inputs, original=a, compiled=b, passed=a == b))
    report["status"] = dict(byte_correspondence_passed=old == new and old_helper == new_helper,
        modeled_api_traces_passed=all(c["passed"] for c in report["mode_fixtures"] + report["enable_fixtures"]),
        rebuilt_ime_vcl_validated=False, native_ime_behavior_validated=False,
        exact_original_library_release_identified=False, full_pascal_game_recovered=False)
    report["limits"] = ["Public CHM contains signatures/declarations, not a source unit or DCU.",
        "Reconstructed helpers use original absolute globals exclusively for emulator use.",
        "Windows APIs are observer models; selected API failures return false with supplied output values.",
        "Missing individual function pointers with a loaded library and actual OS notifications/focus are not exercised.",
        "Only the two standalone helpers are reconstructed; VCL class bodies, loader and virtual dispatch still need integration."]
    target = ROOT / "build/research/delphi2-reports/ime-review.json"
    text = json.dumps(report, indent=2) + "\n"
    if args.check:
        if target.read_text(encoding="utf-8") != text:
            raise ValueError("Stale IME report")
    else:
        target.parent.mkdir(parents=True, exist_ok=True)
        target.write_text(text, encoding="utf-8")
    print("Enable helper:", old_helper == new_helper, "27 literal bytes")
    print("Dispatcher:", old == new, "253 bytes with six explicit local address relocations")
    print("API traces:", len(report["mode_fixtures"]) + len(report["enable_fixtures"]), "passed", report["status"]["modeled_api_traces_passed"])
    if not report["status"]["byte_correspondence_passed"] or not report["status"]["modeled_api_traces_passed"]:
        raise SystemExit("IME comparison failed")


if __name__ == "__main__":
    main()
