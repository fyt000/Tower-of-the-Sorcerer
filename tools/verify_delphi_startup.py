"""Compare activation's installation/settings prefix, including its lost handler.

Stop at syokidata0 without replacing it or any downstream game callee. The
Windows/file/VCL boundaries are explicit observers. Faults transfer through the
installed Delphi catch frame; this is not native SEH/runtime verification.
"""
import argparse
import hashlib
import itertools
import json
import struct

import capstone
import pefile
from unicorn.x86_const import (UC_X86_REG_EAX, UC_X86_REG_EDX, UC_X86_REG_ECX,
                               UC_X86_REG_EBP, UC_X86_REG_ESP, UC_X86_REG_EIP,
                               UC_X86_REG_EFLAGS)

from verify_delphi_graphics import (ROOT, WORK, ORIGINAL_HASH, digest, symbols,
                                   class_vmt, GraphicsRunner, GLOBALS, BOUNDARIES,
                                   first_difference)
from verify_delphi2_reference import normalized

GAME = dict(formactivate=0x44280C, syokidata0=0x484F48)
STATE = {**GLOBALS, "IOPath": (0x48C5D4, 4), "WindowsDirectory": (0x48C5D8, 4),
         "SaveDirectory": (0x48C5DC, 4), "AssetDirectory": (0x48C5E0, 4),
         "PlayerName": (0x48C5EF, 11), "SettingsFile": (0x48C600, 332)}
OBSERVERS = {**BOUNDARIES, 0x406068: "GetCurrentDir", 0x4060AC: "StrLen",
             0x403924: "@LStrSetLength", 0x403814: "@LStrToPChar",
             0x403988: "@LStrToString", 0x402918: "@PStrNCpy",
             0x4035FC: "@LStrFromString", 0x4135D4: "TControl.SetText",
             0x404BAC: "GetWindowsDirectory", 0x40414D: "@Assign",
             0x40458D: "@ResetFile", 0x4041F0: "@BlockRead",
             0x4042B8: "@Close", 0x402710: "@_IOTest", 0x403268: "@DoneExcept"}
OBSERVERS.update({0x416CBC: "TWinControl.GetHandle", 0x405184: "SendMessage",
                  0x4051FC: "SetWindowText", 0x4035BC: "@LStrFromLenStr"})
VIRTUALS = {0x0C: "memo_get", 0x2C: "memo_add", 0x38: "memo_clear",
            0x50: "memo_load", 0x5C: "memo_save"}


class StartupRunner(GraphicsRunner):
    def __init__(self, pe, original=False, map_path=None):
        super().__init__(pe, original, map_path, game=GAME, storage=STATE, boundaries=OBSERVERS)
        self.string_globals.update(("IOPath", "WindowsDirectory", "SaveDirectory", "AssetDirectory"))
        # Read the complete body directly. Ghidra's original function export
        # stops before the handler, normal continuation and final epilogue.
        if original:
            start, stop = 0x44280C, 0x442BB6
            self.handle_exception = 0x402F4C
        else:
            mapping = symbols(pe, map_path)
            start = mapping["TTSW10.formactivate"]
            stop = next(a for a in sorted(set(mapping.values())) if a > start)
            self.handle_exception = mapping["@HandleAnyException"]
        body = pe.get_data(start - pe.OPTIONAL_HEADER.ImageBase, stop - start)
        self.allowed.update(i.address for i in self.md.disasm(body, start))
        self.body_evidence = dict(start=hex(start), bytes=len(body), sha256=hashlib.sha256(body).hexdigest())
        vmt = class_vmt(pe, "TMemoStrings")
        self.memo_targets = {slot: struct.unpack("<I", pe.get_data(vmt + slot - pe.OPTIONAL_HEADER.ImageBase, 4))[0]
                             for slot in VIRTUALS}
        self.boundaries.update({self.memo_targets[s]: name for s, name in VIRTUALS.items() if s not in (0x0C, 0x38)})
        # Execute the real getter and clear wrappers. Authenticate entire bodies
        # and every external callee, including private methods without symbols.
        baseline = pe if original else pefile.PE(str(ROOT / "build/research/TSW.exe"))
        self.memo_body_evidence = []
        for label, orig_at, at, size, callees in (
            ("TMemoStrings.Get", 0x428CE8, self.memo_targets[0x0C], 67,
             ("TWinControl.GetHandle", "SendMessage", "@LStrFromLenStr")),
            ("TMemoStrings.Clear", 0x428F3C, self.memo_targets[0x38], 9, ("TCustomEdit.Clear",)),
            ("TCustomEdit.Clear", 0x428850, 0x428850 if original else mapping["TCustomEdit.Clear"], 23,
             ("TWinControl.GetHandle", "SetWindowText"))):
            old = list(self.md.disasm(baseline.get_data(orig_at - baseline.OPTIONAL_HEADER.ImageBase, size), orig_at))
            actual = list(self.md.disasm(pe.get_data(at - pe.OPTIONAL_HEADER.ImageBase, size), at))
            try:
                shape_agrees = sum(i.size for i in actual) == size and normalized(baseline, old)[0] == normalized(pe, actual)[0]
            except ValueError:
                shape_agrees = False
            if not shape_agrees:
                raise ValueError("Unexpected Memo.Lines virtual target/body " + label)
            targets = [i.operands[0].imm for i in actual if i.mnemonic == "call"]
            identities = {**OBSERVERS, 0x428850: "TCustomEdit.Clear"} if original else {address: name for name, address in mapping.items()}
            expected = [identities.get(target, "unrecognized-callee") for target in targets]
            if expected != list(callees):
                raise ValueError("Unexpected Memo.Lines external callee " + label)
            self.allowed.update(i.address for i in actual)
            self.memo_body_evidence.append(dict(method=label, bytes=size, external_callees=expected))
        if not original:
            for slot, name in ((0x2C, "TStrings.Add"), (0x50, "TStrings.LoadFromFile"), (0x5C, "TStrings.SaveToFile")):
                if self.memo_targets[slot] != mapping[name]:
                    raise ValueError("Unexpected Memo.Lines virtual target " + name)

    def seed_case(self, lines, load_fault=False, bitmap_fault=False, save_fault=False, options=bytes(range(10)),
                  option_fault=None):
        super().seed()
        self.ini_lines = list(lines)
        self.current_dir = b"X:\\original"
        self.windows_dir = b"X:\\windows"
        self.load_fault, self.bitmap_fault, self.save_fault = load_fault, bitmap_fault, save_fault
        self.option_fault, self.option_bytes = option_fault, options
        self.memo = []
        self.saved = None
        self.io_error = 0
        self.terminal = None
        self.file_name = None
        self.file_open = False
        self.caption = None
        self.u.mem_write(self.storage["PlayerName"], b"\xA5" * 11)
        for slot, address in self.memo_targets.items():
            self.write32(self.lines_vmt + slot, address)
        self.write32(self.lines + 8, self.components["Memo12"])

    def write(self, u, access, at, size, value, data):
        # The real memo getter uses a 4 KiB local buffer in addition to the
        # activation frame. No object/game writes are exempted by this range.
        if 0x3FB000 <= at and at + size <= 0x3FF000:
            return
        super().write(u, access, at, size, value, data)

    def fault(self, cause):
        frame = self.read32(0)
        handler = self.read32(frame + 4)
        ins = next(self.md.disasm(bytes(self.u.mem_read(handler, 5)), handler))
        if ins.mnemonic != "jmp" or ins.operands[0].type != capstone.x86.X86_OP_IMM or ins.operands[0].imm != self.handle_exception:
            raise ValueError("Fault is not inside the authenticated Delphi catch frame")
        self.trace.append(["installation_exception", cause])
        self.write32(0, self.read32(frame))
        self.u.reg_write(UC_X86_REG_EBP, self.read32(frame + 8))
        self.u.reg_write(UC_X86_REG_ESP, frame + 12)
        self.u.reg_write(UC_X86_REG_EIP, handler + 5)

    def stop(self, terminal):
        self.terminal = terminal
        self.trace.append(["boundary_stop", terminal])
        self.u.emu_stop()

    def step(self, u, at, size, data):
        if at == self.entries["syokidata0"]:
            self.stop("syokidata0")
            return
        super().step(u, at, size, data)

    def observe(self, name):
        a, d, c, sp = (self.u.reg_read(r) for r in (UC_X86_REG_EAX, UC_X86_REG_EDX, UC_X86_REG_ECX, UC_X86_REG_ESP))
        if name == "GetCurrentDir":
            self.put_string(a, self.current_dir)
        elif name == "GetWindowsDirectory":
            capacity, pointer = self.read32(sp + 8), self.read32(sp + 4)
            if capacity != 255:
                raise ValueError("Windows-directory capacity changed")
            self.u.mem_write(pointer, self.windows_dir + b"\0")
            self.trace.append(["windows_directory", capacity, self.windows_dir.decode()])
            self.ret(8, len(self.windows_dir)); return
        elif name == "@LStrSetLength":
            raw = self.string(self.read32(a))
            self.put_string(a, raw[:d] + bytes(max(0, d - len(raw))))
        elif name == "@LStrToPChar":
            if not a:
                raise ValueError("Unexpected nil directory buffer")
            self.ret(value=a); return
        elif name == "StrLen":
            raw = bytes(self.u.mem_read(a, 255))
            self.ret(value=raw.index(0)); return
        elif name == "@LStrToString":
            raw = self.string(d)[:c]
            self.u.mem_write(a, bytes([len(raw)]) + raw)
        elif name == "@PStrNCpy":
            length = min(bytes(self.u.mem_read(d, 1))[0], c & 255)
            raw = bytes(self.u.mem_read(d + 1, length))
            self.u.mem_write(a, bytes([length]) + raw)
            if a != self.storage["PlayerName"]:
                raise ValueError("Unexpected short-name destination")
            self.trace.append(["player_name", raw.decode("cp1252")])
        elif name == "@LStrFromString":
            self.put_string(a, bytes(self.u.mem_read(d + 1, bytes(self.u.mem_read(d, 1))[0])))
        elif name == "@LStrFromLenStr":
            self.put_string(a, bytes(self.u.mem_read(d, c)))
        elif name == "TWinControl.GetHandle":
            if a != self.components["Memo12"]:
                raise ValueError("Unexpected memo handle request")
            self.ret(value=a); return
        elif name == "SendMessage":
            handle, message, index, pointer = (self.read32(sp + n) for n in (4, 8, 12, 16))
            if handle != self.components["Memo12"] or message != 0xC4:
                raise ValueError("Unexpected memo Windows message")
            capacity = struct.unpack("<H", self.u.mem_read(pointer, 2))[0]
            if capacity != 4096:
                raise ValueError("Memo getter buffer capacity changed")
            raw = self.memo[index] if index < len(self.memo) else b""
            self.u.mem_write(pointer, raw[:capacity])
            self.trace.append(["memo_get", index, raw[:capacity].decode("cp1252")])
            self.ret(16, min(len(raw), capacity)); return
        elif name == "SetWindowText":
            if self.read32(sp + 4) != self.components["Memo12"] or bytes(self.u.mem_read(self.read32(sp + 8), 1)) != b"\0":
                raise ValueError("Unexpected memo clear request")
            self.memo.clear(); self.trace.append(["memo_clear"])
            self.ret(8, 1); return
        elif name == "TControl.SetText":
            self.caption = self.string(d).decode("cp1252")
            self.trace.append(["text", self.object_name(a), self.caption])
        elif name.startswith("memo_"):
            if a != self.lines:
                raise ValueError("Unexpected startup memo owner")
            if name == "memo_load":
                self.trace.append(["memo_load", self.string(d).decode("cp1252")])
                if self.load_fault:
                    self.fault("ini-load"); return
                self.memo[:] = self.ini_lines
            elif name == "memo_add":
                raw = self.string(d)
                self.memo.append(raw); self.trace.append(["memo_add", raw.decode("cp1252")])
                self.ret(value=len(self.memo) - 1); return
            elif name == "memo_save":
                self.trace.append(["memo_save", self.string(d).decode("cp1252"), [s.decode("cp1252") for s in self.memo]])
                if self.save_fault:
                    self.stop("unhandled-ini-save-error"); return
                self.saved = list(self.memo)
        elif name == "TPicture.LoadFromFile":
            self.trace.append(["initial_bitmap_load", self.string(d).decode("cp1252")])
            if self.bitmap_fault:
                self.fault("initial-bitmap-load"); return
        elif name in ("@Assign", "@ResetFile", "@BlockRead", "@Close"):
            if a != self.storage["SettingsFile"]:
                raise ValueError("Settings file storage changed")
            if name == "@Assign":
                self.file_name = self.string(d).decode("cp1252")
                self.trace.append(["file_assign", self.file_name])
            elif name == "@ResetFile":
                self.trace.append(["file_reset", self.file_name, d])
                self.file_open = self.option_fault != "open"
                self.io_error = 2 if not self.file_open else 0
            elif name == "@BlockRead":
                if d != self.storage["GameOptions"] or c != 10 or self.read32(sp + 4) != 0:
                    raise ValueError("Option record read changed")
                raw = self.option_bytes[:c]
                self.u.mem_write(d, raw)
                self.io_error = 100 if len(raw) < c else 0
                self.trace.append(["file_read", c, raw.hex(), self.io_error])
                self.ret(4, len(raw)); return
            else:
                self.trace.append(["file_close", self.file_name])
                self.file_open = False
                self.io_error = 6 if self.option_fault == "close" else 0
        elif name == "@_IOTest":
            self.trace.append(["io_test", self.io_error])
            if self.io_error:
                self.stop("unhandled-option-io-error:" + str(self.io_error)); return
        elif name == "@DoneExcept":
            pass
        else:
            super().observe(name); return
        self.ret()

    def run_prefix(self):
        stack = 0x3FE000
        self.u.mem_write(0x3FB000, bytes(0x4000))
        self.write32(0, 0)
        self.write32(stack, 0x3FF000)
        self.u.reg_write(UC_X86_REG_ESP, stack)
        self.u.reg_write(UC_X86_REG_EAX, self.self)
        self.u.reg_write(UC_X86_REG_EDX, self.self)
        self.u.reg_write(UC_X86_REG_ECX, 0)
        self.u.reg_write(UC_X86_REG_EFLAGS, 2)
        self.u.emu_start(self.entries["formactivate"], 0x3FF000, count=100000)
        if self.terminal is None:
            raise ValueError("Startup prefix did not reach a declared boundary")
        return self.trace.copy()

    def state(self):
        result = super().state()
        # Runtime file records contain OS handles/private pointers and are
        # observed as named operations; do not claim raw file-record equality.
        del result["SettingsFile"]
        result.update(memo=[s.hex() for s in self.memo], saved=None if self.saved is None else [s.hex() for s in self.saved],
                      file_name=self.file_name, file_open=self.file_open, terminal=self.terminal, caption=self.caption)
        return result


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--check", action="store_true")
    args = parser.parse_args()
    if digest(ROOT / "build/research/TSW.exe") != ORIGINAL_HASH:
        raise ValueError("Original pin changed")
    build = json.loads((WORK / "build-report.json").read_text())
    for record in build["inputs"]:
        source = ROOT / record["source"]
        staged = WORK / source.relative_to(ROOT / "delphi")
        if digest(source) != record["source_sha256"] or digest(staged) != record["staged_sha256"]:
            raise ValueError("Stale startup source: " + record["source"])
    artifact = WORK / "game/Tower.exe"
    record = build["builds"]["game"]
    if digest(artifact) != record["artifact_sha256"] or digest(artifact.with_suffix(".map")) != record["map_sha256"]:
        raise ValueError("Stale startup artifact")
    native = build["builds"]["startup-io"]
    native_log = WORK / "startup-io/native.log"
    if native.get("native_exit") != 0 or digest(native_log) != native["native_log_sha256"]:
        raise ValueError("Native startup I/O boundary evidence missing or stale")
    witness_exe = ROOT / native["artifact"]
    if (digest(witness_exe) != native["artifact_sha256"]
            or digest(witness_exe.with_suffix(".map")) != native["map_sha256"]
            or native_log.read_bytes().decode("cp1252") != native["native_output"]):
        raise ValueError("Native startup witness artifact/log changed")
    for name, sha in native["fixtures"].items():
        if digest(WORK / "startup-io/fixtures" / name) != sha:
            raise ValueError("Native startup fixture changed: " + name)
    native_cases = [json.loads(line) for line in native["native_output"].splitlines() if line.strip()]
    if not native_cases[-1].get("startup_io_boundary_passed"):
        raise ValueError("Native startup I/O boundary did not finish")
    line_lengths = {case["memo_name_bytes"]: case["physical_line_lengths"] for case in native_cases[:-1]}
    old = StartupRunner(pefile.PE(str(ROOT / "build/research/TSW.exe")), original=True)
    new = StartupRunner(pefile.PE(str(artifact)), map_path=artifact.with_suffix(".map"))
    cases = []
    transcript = hashlib.sha256()
    names = (b"", b"Hero", b"1234567890", b"12345678901", b"A" * 255, b"A" * 256, b"A" * 300)
    for name, path, options in itertools.product(names, ("load", "missing-ini", "missing-bitmap"),
                                               ("valid", "missing-options", "short-options", "close-error", "save-error")):
        inputs = dict(name_bytes=len(name), name_sha256=hashlib.sha256(name).hexdigest(), installation=path, options=options)
        lengths = line_lengths[len(name)]
        if lengths[:2] != [8, 9] or sum(lengths[2:]) != len(name):
            raise ValueError("Native physical memo-line witness changed")
        # Use the admitted Windows boundary values, obtained independently of
        # the recovered game procedure. The real old/new getters consume them.
        physical_lines = [b"X:\\saves", b"X:\\assets"]
        physical_lines.extend(name[sum(lengths[2:i + 2]):sum(lengths[2:i + 3])] for i in range(len(lengths) - 2))
        for runner in (old, new):
            runner.seed_case(physical_lines, load_fault=path == "missing-ini",
                             bitmap_fault=path == "missing-bitmap", save_fault=options == "save-error",
                             options=b"\x80\x00\xFF\x03\x01\x00\x01\x01\x00\x7F" if options != "short-options" else b"\x80\x00\xFF",
                             option_fault={"missing-options": "open", "close-error": "close"}.get(options))
        expected, actual = old.run_prefix(), new.run_prefix()
        a, b = old.state(), new.state()
        diff = first_difference(expected, actual)
        state_diff = [key for key in a if a[key] != b[key]]
        case = dict(inputs=inputs, passed=diff is None and not state_diff, terminal=old.terminal,
                    original_effects=len(expected), compiled_effects=len(actual), first_difference=diff, state_differences=state_diff)
        cases.append(case)
        transcript.update(json.dumps([inputs, expected, actual, a, b], sort_keys=True).encode())
        if not case["passed"]:
            print(json.dumps(case, indent=2))
            if state_diff:
                print({key: (a[key], b[key]) for key in state_diff})
            raise ValueError("Startup prefix comparison failed")
    report = dict(schema_version=1, original_sha256=ORIGINAL_HASH, build_report_sha256=digest(WORK / "build-report.json"),
                  comparisons=len(cases), cases=cases, original_activation_body=old.body_evidence,
                  compiled_activation_body=new.body_evidence, fixture_transcript_sha256=transcript.hexdigest(),
                  executed_memo_framework_bodies=new.memo_body_evidence, native_io_boundary_cases=native_cases,
                  startup_prefix_passed=True, full_activation_compared=False, full_game_recovered=False,
                  pixel_equivalence_established=False,
                  limits=["Execution stops at the entry to syokidata0; no downstream game callback is skipped or declared recovered by these fixtures.",
                          "Windows-directory, current-directory, VCL memo/bitmap I/O, string helpers and Pascal file runtime use explicit observers. Real old/new memo getters and clear wrappers execute; Windows messages and handle creation remain boundaries.",
                          "Fault injection transfers through the installed @HandleAnyException frame into its real original/compiled handler. OS exception dispatch, RtlUnwind, cleanup and native failure timing are not certified.",
                          "Uncaught INI-save and option-I/O failures stop at named boundaries; their exception unwinding is not compared.",
                          "Physical memo lines, including native wrapping of 255/256/300-byte ASCII names, come from the independent hidden native boundary harness. The original Windows process is not run; arbitrary fonts/DPI/DBCS/long-line behavior remains outside this scope.",
                          "Raw runtime file records are excluded because handles/private pointers are modeled. Requests, requested byte counts, option bytes, paths, names and ordered game writes are compared."])
    target = ROOT / "build/delphi-game/reports/startup-comparison-report.json"
    content = json.dumps(report, indent=2) + "\n"
    if args.check:
        if target.read_text(encoding="utf-8") != content:
            raise ValueError("Stale startup comparison report")
    else:
        target.parent.mkdir(parents=True, exist_ok=True)
        target.write_text(content, encoding="utf-8")
    print("Startup installation/settings prefix comparisons", len(cases), "passed")


if __name__ == "__main__":
    main()
