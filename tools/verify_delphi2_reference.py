"""Compare locally compiled Delphi-2 probes with the pinned original executable.

Library comparisons normalize only image address operands and external relative
control-transfer operands. Instance offsets, scalar constants and local branches
remain literal. Such shape agreement is supporting evidence, not a purity or
whole-library equivalence claim. Gameplay reconstruction requires literal bytes
and compares complete memory-write effects with no skipped calls.
"""
from pathlib import Path
import argparse
import hashlib
import json
import re
import struct

import capstone
import pefile
import unicorn
from unicorn.x86_const import (
    UC_X86_REG_EAX, UC_X86_REG_EDX, UC_X86_REG_ECX, UC_X86_REG_ESP,
    UC_X86_REG_EIP, UC_X86_REG_EFLAGS,
)

from recovery_evidence import ROOT, ORIGINAL_HASH, digest

RUNTIME = {
    "TControl.Click": 0x413EAC,
    "TWinControl.CanFocus": 0x416C2C,
    "TButton.CMDialogKey": 0x42A480,
    "TTimer.Timer": 0x42C48C,
    "TTimer.WndProc": 0x42C390,
    "MakeObjectInstance": 0x41FD4C,
    "@InitExe": 0x403420,
    "@HandleAnyException": 0x402F4C,
    "@HandleFinally": 0x403140,
}


def symbols(pe, path):
    result = {}
    text = path.read_text(encoding="cp1252")
    for segment, offset, name in re.findall(r"^ (\d{4}):([\dA-F]+)\s+(\S+)\s*$", text, re.M):
        if int(segment) != 1:
            continue
        address = pe.OPTIONAL_HEADER.ImageBase + pe.sections[0].VirtualAddress + int(offset, 16)
        if name in result and result[name] != address and name in RUNTIME:
            raise ValueError("Ambiguous map symbol")
        result[name] = address
    return result


def instructions(pe, address, size):
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    md.detail = True
    data = pe.get_data(address - pe.OPTIONAL_HEADER.ImageBase, size)
    result = list(md.disasm(data, address))
    if sum(i.size for i in result) != size:
        raise ValueError("Incomplete instruction decoding")
    return result


def normalized(pe, insns):
    start, stop = insns[0].address, insns[-1].address + insns[-1].size
    base, end = pe.OPTIONAL_HEADER.ImageBase, pe.OPTIONAL_HEADER.ImageBase + pe.OPTIONAL_HEADER.SizeOfImage
    result, substitutions = [], []
    for instruction in insns:
        raw = bytearray(instruction.bytes)
        for operand in instruction.operands:
            offset, size, reason = None, 0, None
            if operand.type == capstone.x86.X86_OP_MEM and base <= operand.mem.disp < end:
                offset, size, reason = instruction.disp_offset, instruction.disp_size, "image-memory-address"
            elif operand.type == capstone.x86.X86_OP_IMM:
                transfer = instruction.mnemonic == "call" or instruction.mnemonic.startswith("j")
                if transfer and not start <= operand.imm < stop:
                    offset, size, reason = instruction.imm_offset, instruction.imm_size, "external-relative-transfer"
                elif not transfer and base <= operand.imm < end:
                    offset, size, reason = instruction.imm_offset, instruction.imm_size, "image-pointer-immediate"
            if reason:
                if size != 4:
                    raise ValueError("Unexpected address-operand width")
                raw[offset:offset + size] = bytes(size)
                substitutions.append(dict(instruction_offset=instruction.address - start,
                                          operand_offset=offset, bytes=size, reason=reason))
        result.append(raw.hex())
    return result, substitutions


def original_span(address):
    path = ROOT / f"reference/original/whole-program/decompiled/{address:08x}.asm"
    records = [(int(a, 16), bytes.fromhex(raw)) for a, raw in
               re.findall(r"^([0-9a-f]{8})  ([0-9a-f]+) ", path.read_text(), re.M)]
    # Handler/continuation ownership is separate in Ghidra; some runtime bytes
    # are still absent from its complete listing. These full routine spans are
    # corroborated by the matching IDR records and compiled source-library
    # baseline; they are retained here without relabeling the earlier ledger.
    if address in (0x42C390, 0x402F4C):
        return {0x42C390: 113, 0x402F4C: 195}[address]
    cursor = address
    for at, raw in records:
        if at != cursor:
            raise ValueError("Focused comparison requires a contiguous assembly body")
        cursor += len(raw)
    return cursor - address


def class_vmt(pe, name):
    image = pe.get_memory_mapped_image()
    marker = b"\x07" + bytes([len(name)]) + name.encode("ascii")
    offsets = [m.start() for m in re.finditer(re.escape(marker), image)]
    if len(offsets) != 1:
        raise ValueError(f"Ambiguous class RTTI: {name}")
    return struct.unpack_from("<I", image, offsets[0] + len(marker))[0]


def emulator(pe):
    u = unicorn.Uc(unicorn.UC_ARCH_X86, unicorn.UC_MODE_32)
    u.mem_map(0, 0x10000)  # Synthetic FS:[0] exception-frame head.
    u.mem_map(0x100000, 0x300000)
    u.mem_map(0x400000, 0x200000)
    u.mem_write(pe.OPTIONAL_HEADER.ImageBase, pe.get_memory_mapped_image())
    return u


def execute(u, address, eax=0, edx=0):
    stop, stack = 0x3FF000, 0x3FE000
    u.reg_write(UC_X86_REG_ESP, stack)
    u.mem_write(stack, struct.pack("<I", stop))
    u.reg_write(UC_X86_REG_EAX, eax)
    u.reg_write(UC_X86_REG_EDX, edx)
    u.reg_write(UC_X86_REG_ECX, 0)
    u.reg_write(UC_X86_REG_EFLAGS, 2)
    u.emu_start(address, stop, count=10000)
    if u.reg_read(UC_X86_REG_EIP) != stop or u.reg_read(UC_X86_REG_ESP) != stack + 4:
        raise ValueError("Routine failed to return normally within instruction budget")


def framework_cases(pe, entries):
    """Follow actual VCL methods/dynamic dispatch; model only Windows GetKeyState.

    Synthetic object trees have real class VMTs and version-specific field
    offsets. Callback bodies are explicit observers. No library call is skipped.
    These are object/message fixtures, not a whole-game or Windows-input test.
    """
    u = emulator(pe)
    vmts = {name: class_vmt(pe, name) for name in ("TForm", "TButton", "TPanel", "TTimer")}
    form_size = struct.unpack("<I", u.mem_read(vmts["TForm"] - 24, 4))[0]
    delta = form_size - 428
    if delta not in (0, 4):
        raise ValueError("Unreviewed VCL object layout")
    button, panel, form, message, callback, count = 0x200000, 0x201000, 0x202000, 0x203000, 0x3FD000, 0x204000
    # INC [count]; RET -- observer event, not a replacement framework method.
    u.mem_write(callback, b"\xFF\x05" + struct.pack("<I", count) + b"\xC3")
    external = 0x3FC000
    # EAX=0 (no physical Shift/Ctrl pressed); Windows stdcall RET 4.
    u.mem_write(external, b"\x31\xC0\xC2\x04\x00")
    import_found = False
    for dll in pe.DIRECTORY_ENTRY_IMPORT:
        for item in dll.imports:
            if item.name == b"GetKeyState":
                u.mem_write(item.address, struct.pack("<I", external))
                import_found = True
    if not import_found:
        raise ValueError("Missing Windows key-state boundary")
    def write32(address, value):
        u.mem_write(address, struct.pack("<I", value))
    def read32(address):
        return struct.unpack("<I", u.mem_read(address, 4))[0]
    scenarios = [
        ("Escape.enabled", {}, 1),
        ("Escape.button-disabled", {"button_enabled": False}, 0),
        ("Escape.parent-disabled", {"panel_enabled": False}, 0),
        ("Escape.parent-hidden", {"panel_visible": False}, 0),
        ("Escape.button-hidden", {"button_visible": False}, 0),
        ("Escape.alt", {"key_data": 0x20000000}, 0),
        ("Escape.no-parent-form", {"no_form": True}, 0),
        ("Enter.default-active", {"key": 13}, 1),
        ("Enter.inactive", {"key": 13, "active": False}, 0),
        ("Escape.not-cancel", {"cancel": False}, 0),
        ("Click.direct-disabled", {"direct": True, "button_enabled": False}, 1),
    ]
    records = []
    for name, inputs, expected in scenarios:
        for address, cls in ((button, "TButton"), (panel, "TPanel"), (form, "TForm")):
            u.mem_write(address, bytes(0x500))
            write32(address, vmts[cls])
        write32(button + 0x20, panel)
        write32(panel + 0x20, 0 if inputs.get("no_form") else form)
        u.mem_write(button + 0x37, bytes([inputs.get("button_visible", True), inputs.get("button_enabled", True)]))
        u.mem_write(panel + 0x37, bytes([inputs.get("panel_visible", True), inputs.get("panel_enabled", True)]))
        u.mem_write(button + 0x101 + delta, bytes([inputs.get("cancel", True), inputs.get("active", True)]))
        write32(button + 0x98, callback)
        write32(button + 0x9C, button)
        write32(button + 0x104 + delta, 7)
        write32(count, 0)
        u.mem_write(message, struct.pack("<IIII", 0xB005, inputs.get("key", 27), inputs.get("key_data", 0), 0))
        execute(u, entries["TButton.Click"] if inputs.get("direct") else entries["TButton.CMDialogKey"], button, message)
        actual = dict(callbacks=read32(count), message_result=read32(message + 12),
                      modal_result=read32(form + 0x128 + delta))
        wanted = dict(callbacks=expected, message_result=0 if inputs.get("direct") else expected,
                      modal_result=7 if expected else 0)
        records.append(dict(name=name, inputs=inputs, expected=wanted, actual=actual, passed=actual == wanted))
    timer = 0x205000
    for name, handler, expected in (("Timer.delivered-while-disabled", True, 1), ("Timer.no-handler", False, 0)):
        u.mem_write(timer, bytes(0x34))
        write32(timer, vmts["TTimer"])
        if handler:
            write32(timer + 0x2C, callback)
            write32(timer + 0x30, timer)
        write32(count, 0)
        write32(0, 0x1234)
        u.mem_write(message, struct.pack("<IIII", 0x113, 1, 0, 0))
        execute(u, entries["TTimer.WndProc"], timer, message)
        actual = dict(callbacks=read32(count), exception_frame_restored=read32(0) == 0x1234)
        wanted = dict(callbacks=expected, exception_frame_restored=True)
        records.append(dict(name=name, inputs=dict(enabled=False, handler_assigned=handler),
                            expected=wanted, actual=actual, passed=actual == wanted))
    return records


def gameplay_comparison(original, candidate):
    symbol = next(s for s in candidate.DIRECTORY_ENTRY_EXPORT.symbols if s.name == b"ClassifyNeighbor")
    address = candidate.OPTIONAL_HEADER.ImageBase + symbol.address
    size = original_span(0x451C20)
    old = original.get_data(0x451C20 - original.OPTIONAL_HEADER.ImageBase, size)
    new = candidate.get_data(symbol.address, size)
    record = dict(original_address="0x00451c20", compiled_address=f"0x{address:08x}",
                  bytes=size, literal_byte_match=old == new,
                  original_bytes_sha256=hashlib.sha256(old).hexdigest(),
                  compiled_bytes_sha256=hashlib.sha256(new).hexdigest(), cases=0,
                  mismatches=[], floors=[0, 1, 50], indices=[0, 10, 110, 120],
                  previous_monster_values=[-123, 0, 32])
    machines = [emulator(original), emulator(candidate)]
    effects = [[], []]
    def writer(machine, access, at, length, value, output):
        if at in (0x48C58C, 0x48C5B8):
            output.append(dict(address=f"0x{at:08x}", bytes=length, value=value & ((1 << (length * 8)) - 1)))
        elif not 0x3FD000 <= at < 0x3FF000:
            raise ValueError(f"Unexpected classifier write at {at:#x}")
    for machine, output in zip(machines, effects):
        machine.hook_add(unicorn.UC_HOOK_MEM_WRITE, writer, output)
    for floor in record["floors"]:
        for index in record["indices"]:
            for previous in record["previous_monster_values"]:
                for tile in range(256):
                    results = []
                    for machine, entry, output in zip(machines, (0x451C20, address), effects):
                        output.clear()
                        for at, value in ((0x4B8698, floor), (0x48C55C, index), (0x48C58C, -1), (0x48C5B8, previous)):
                            machine.mem_write(at, struct.pack("<i", value))
                        machine.mem_write(0x4B8934 + floor * 123 + index + 2, bytes([tile]))
                        execute(machine, entry)
                        results.append(dict(tile_class=struct.unpack("<i", machine.mem_read(0x48C58C, 4))[0],
                                            monster_index=struct.unpack("<i", machine.mem_read(0x48C5B8, 4))[0],
                                            writes=list(output)))
                    record["cases"] += 1
                    if results[0] != results[1]:
                        record["mismatches"].append(dict(floor=floor, index=index, previous=previous,
                                                       tile=tile, original=results[0], compiled=results[1]))
    record["passed"] = record["literal_byte_match"] and not record["mismatches"]
    return record


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--toolchain", type=Path, default=ROOT / "build/research/delphi2")
    parser.add_argument("--original", type=Path, default=ROOT / "build/research/TSW.exe")
    parser.add_argument("--output", type=Path, default=ROOT / "reference/delphi2/comparison-report.json")
    parser.add_argument("--check", action="store_true", help="Compare regenerated report and runtime spans without overwriting")
    args = parser.parse_args()
    if digest(args.original) != ORIGINAL_HASH:
        raise ValueError("Original EXE differs from pin")
    toolchain = args.toolchain.resolve()
    build = json.loads((toolchain / "build-report.json").read_text())
    if digest(toolchain / "media-manifest.json") != build["media_manifest_sha256"]:
        raise ValueError("Toolchain manifest changed since compilation")
    if digest(toolchain / "base/bin/DCC32.EXE") != build["compiler_sha256"]:
        raise ValueError("Compiler changed since compilation")
    for name, record in [*build["variants"].items(), ("recovery", build["recovery"])]:
        directory = toolchain / ("recovery-probe" if name == "recovery" else "probe-" + name)
        for source in record["inputs"]:
            if digest(ROOT / source["source"]) != source["source_sha256"]:
                raise ValueError("Tracked Pascal source changed since compilation")
            if digest(directory / Path(source["source"]).name) != source["staged_sha256"]:
                raise ValueError("Staged Pascal source changed since compilation")
    original = pefile.PE(str(args.original))
    inventory = json.loads((ROOT / "reference/original/whole-program/structural-inventory.json").read_text())
    sizes = {c["name"]: c["instance_size"] for c in inventory["classes"]}
    report = dict(schema_version=1, original_sha256=ORIGINAL_HASH,
                  archive_sha256=json.loads((toolchain / "media-manifest.json").read_text())["archive"]["sha256"],
                  compiler_sha256=build["compiler_sha256"],
                  variants={}, original_framework_cases=framework_cases(original, {**RUNTIME, "TButton.Click": 0x42A370}))
    media = json.loads((toolchain / "media-manifest.json").read_text())
    report["toolchain_provenance"] = dict(payload_sha256=media["payload_sha256"],
                                         extractor=media["extractor"],
                                         total_media_files=media["total_count"], extracted_files=media["extracted_count"],
                                         updates=media["updates"],
                                         build_report_sha256=digest(toolchain / "build-report.json"))
    keys = {"DCC32.EXE", "SYSTEM.DCU", "CONTROLS.DCU", "FORMS.DCU", "STDCTRLS.DCU", "EXTCTRLS.DCU",
            "SYSTEM.PAS", "CONTROLS.PAS", "FORMS.PAS", "STDCTRLS.PAS", "EXTCTRLS.PAS"}
    report["toolchain_provenance"]["key_files"] = [r for r in media["files"] if Path(r["path"]).name.upper() in keys]
    complete_code = (ROOT / "reference/original/whole-program/CODE.asm").read_text()
    listed = {int(address, 16) for address in re.findall(r"^([0-9a-f]{8})  [0-9a-f]+ ", complete_code, re.M)}
    report["focused_original_runtime_spans"] = []
    for name, address in RUNTIME.items():
        length = original_span(address)
        insns = instructions(original, address, length)
        unlisted = [dict(address=f"0x{i.address:08x}", bytes=i.bytes.hex(), instruction=f"{i.mnemonic} {i.op_str}".rstrip())
                    for i in insns if i.address not in listed]
        report["focused_original_runtime_spans"].append(dict(symbol=name, address=f"0x{address:08x}", bytes=length,
                                                             unlisted_instructions=unlisted,
                                                             unlisted_instruction_bytes=sum(len(bytes.fromhex(i["bytes"])) for i in unlisted)))
        assembly = f"; {name}; compiler-assisted focused span, not a new Ghidra ownership claim\n; Original SHA-256 {ORIGINAL_HASH}\n"
        assembly += "\n".join(f"{i.address:08x}  {i.bytes.hex()}  {i.mnemonic.upper()} {i.op_str}".rstrip() for i in insns) + "\n"
        target = args.output.parent / f"runtime-spans/{address:08x}.asm"
        if args.check:
            if target.read_text(encoding="utf-8") != assembly:
                raise ValueError(f"Stale runtime span: {target}")
        else:
            target.parent.mkdir(parents=True, exist_ok=True)
            target.write_text(assembly, encoding="utf-8")
    for name, built in build["variants"].items():
        record = dict(compile=built["compile"], updates=built["updates"])
        report["variants"][name] = record
        if built["compile"]["exit_code"]:
            continue
        work = toolchain / ("probe-" + name)
        for file in ("RuntimeProbe.exe", "RuntimeProbe.map"):
            if digest(work / file) != built[file]["sha256"]:
                raise ValueError("Compiled artifact changed")
        pe = pefile.PE(str(work / "RuntimeProbe.exe"))
        entries = symbols(pe, work / "RuntimeProbe.map")
        record["exe_sha256"] = digest(work / "RuntimeProbe.exe")
        record["code_sha256"] = hashlib.sha256(pe.sections[0].get_data()).hexdigest()
        record["runtime_shapes"] = []
        for symbol, address in RUNTIME.items():
            length = original_span(address)
            a = instructions(original, address, length)
            b = instructions(pe, entries[symbol], length)
            old, ma = normalized(original, a)
            new, mb = normalized(pe, b)
            item = dict(symbol=symbol, original_address=f"0x{address:08x}",
                        compiled_address=f"0x{entries[symbol]:08x}", bytes=length,
                        normalized_shape_match=old == new,
                        original_masked_operands=ma, compiled_masked_operands=mb)
            if old != new:
                first = next((i for i, pair in enumerate(zip(old, new)) if pair[0] != pair[1]), min(len(old), len(new)))
                item["first_difference"] = dict(instruction=first,
                                                original=str(a[first]) if first < len(a) else None,
                                                compiled=str(b[first]) if first < len(b) else None)
            record["runtime_shapes"].append(item)
        record["compiled_framework_cases"] = framework_cases(pe, entries)
        if "native" in built:
            record["native"] = built["native"]
            record["layouts"] = [dict(class_name=o["name"].split(".")[0],
                                      original=sizes[o["name"].split(".")[0]], compiled=o["value"],
                                      matches_original=sizes[o["name"].split(".")[0]] == o["value"])
                                  for o in built["native"]["observations"] if "passed" not in o]
    path = toolchain / "recovery-probe/RecoveryProbe.dll"
    if digest(path) != build["recovery"]["RecoveryProbe.dll"]["sha256"]:
        raise ValueError("Recovery DLL changed")
    report["reconstruction"] = gameplay_comparison(original, pefile.PE(str(path)))
    report["reconstruction"]["source"] = build["recovery"]["inputs"]
    report["limits"] = [
        "Only one gameplay routine reconstructed, not a full Pascal game project or author's source text.",
        "Runtime address-normalized shapes do not establish effect equivalence; ABI mismatches remain failures.",
        "Framework emulation follows VCL code but models Windows GetKeyState and uses synthetic objects/events.",
        "Native framework tests exercise this archive's VCL on this Windows host, not the original game executable.",
        "No campaign, complete Windows-input/timer schedule, file-failure matrix or full-game behavioral proof.",
    ]
    cases = report["original_framework_cases"] + [case for record in report["variants"].values()
                                                 for case in record.get("compiled_framework_cases", [])]
    native_checks = [o for record in report["variants"].values() for o in record.get("native", {}).get("observations", []) if "passed" in o]
    native_runs_succeeded = len(report["variants"]) == 4 and all(
        record.get("native", {}).get("exit_code") == 0 and record["compile"]["exit_code"] == 0
        for record in report["variants"].values())
    report["status"] = dict(gameplay_reconstruction_passed=report["reconstruction"]["passed"],
                            framework_fixtures_passed=all(c["passed"] for c in cases),
                            native_framework_checks_passed=native_runs_succeeded and bool(native_checks) and all(c["passed"] for c in native_checks),
                            complete_runtime_baseline_accepted=False,
                            full_pascal_game_recovered=False)
    text = json.dumps(report, indent=2) + "\n"
    if args.check:
        if args.output.read_text(encoding="utf-8") != text:
            raise ValueError("Stale Delphi comparison report")
    else:
        args.output.parent.mkdir(parents=True, exist_ok=True)
        args.output.write_text(text, encoding="utf-8")
    print("Reconstruction:", report["reconstruction"]["bytes"], "literal bytes;",
          report["reconstruction"]["cases"], "effect comparisons; passed", report["reconstruction"]["passed"])
    print("Original framework cases:", len(report["original_framework_cases"]), "passed",
          sum(c["passed"] for c in report["original_framework_cases"]))
    for name, record in report["variants"].items():
        print(name, "runtime shapes", sum(c["normalized_shape_match"] for c in record.get("runtime_shapes", [])),
              "/", len(record.get("runtime_shapes", [])), "layout mismatches",
              [c["class_name"] for c in record.get("layouts", []) if not c["matches_original"]])
    if not report["status"]["gameplay_reconstruction_passed"] or not report["status"]["framework_fixtures_passed"] or not report["status"]["native_framework_checks_passed"]:
        raise SystemExit("Comparison failed; inspect retained report")


if __name__ == "__main__":
    main()
