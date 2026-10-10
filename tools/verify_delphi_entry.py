"""Compare both program-entry paths with explicit Windows/VCL observers.

Runs the retained entry and compiled Tower entry in Unicorn, never as Windows
processes. Unit initialization and framework calls are observed, not executed.
The normal path uses no command-line arguments; portable setup is out of scope.
"""
from pathlib import Path
import argparse
import json
import struct

import capstone
import unicorn
from unicorn.x86_const import UC_X86_REG_EAX, UC_X86_REG_EDX, UC_X86_REG_ESP, UC_X86_REG_EIP
import pefile

from recovery_evidence import ROOT, ORIGINAL_HASH, digest
from verify_delphi2_reference import emulator, symbols, class_vmt

WARNING = "Sorry, cannot execute plural 'Tower of the Sorcerer'."
UNIT_INITIALIZERS = {
    "@InitExe", "System", "SysUtils", "Classes", "Printers", "Menus",
    "Controls", "Forms", "Dialogs", "Buttons",
}
ORIGINAL_INITIALIZERS = {
    0x403420, 0x404A10, 0x408154, 0x40EBD0, 0x40ED0C, 0x40F140,
    0x411098, 0x41898C, 0x4258A0, 0x42D338, 0x433E20,
}


class EntryTrace:
    def __init__(self, pe, mapping=None):
        self.pe = pe
        self.u = emulator(pe)
        self.entry = pe.OPTIONAL_HEADER.ImageBase + pe.OPTIONAL_HEADER.AddressOfEntryPoint
        self.trace = []
        self.finished = False
        md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
        md.detail = True
        if mapping is None:
            self.boundaries = {
                0x404F4C: "find", 0x42CF78: "warning", 0x4051AC: "foreground",
                0x424F08: "initialize", 0x424C34: "title",
                0x424F18: "form", 0x424FA8: "run", 0x40441C: "exit",
                **dict.fromkeys(ORIGINAL_INITIALIZERS, "unit"),
            }
            self.forms = {0x440F60: "TTSW10", 0x433E70: "TAboutBox",
                          0x43463C: "TForm2", 0x4400A4: "TForm4"}
            stop = 0x488E21
        else:
            names = {
                "FindWindow": "find", "ShowMessage": "warning",
                "SetForegroundWindow": "foreground", "TApplication.Initialize": "initialize",
                "TApplication.SetTitle": "title", "TApplication.CreateForm": "form",
                "TApplication.Run": "run", "@Halt0": "exit",
                "@LStrClr": "string-clear", "ParamCount": "arguments",
                "LoadGameContent": "content",
                **dict.fromkeys(UNIT_INITIALIZERS, "unit"),
            }
            self.boundaries = {mapping[name]: kind for name, kind in names.items()}
            self.forms = {class_vmt(pe, name): name for name in
                          ("TTSW10", "TAboutBox", "TForm2", "TForm4")}
            stop = pe.OPTIONAL_HEADER.ImageBase + pe.sections[0].VirtualAddress + pe.sections[0].Misc_VirtualSize
        self.allowed = {i.address for i in md.disasm(pe.get_data(
            self.entry - pe.OPTIONAL_HEADER.ImageBase, stop - self.entry), self.entry)}
        if mapping is not None:
            start = mapping["ActivateExistingGame"]
            end = min(address for address in mapping.values() if address > start)
            self.allowed.update(i.address for i in md.disasm(
                pe.get_data(start - pe.OPTIONAL_HEADER.ImageBase, end - start), start))
        self.u.hook_add(unicorn.UC_HOOK_CODE, self.observe)

    def string(self, address):
        if address == 0:
            return None
        value = bytearray()
        while len(value) < 1024:
            char = self.u.mem_read(address + len(value), 1)[0]
            if char == 0:
                return value.decode("cp1252")
            value.append(char)
        raise ValueError("Unterminated entry string")

    def argument(self, index):
        stack = self.u.reg_read(UC_X86_REG_ESP)
        return struct.unpack("<I", self.u.mem_read(stack + 4 * index, 4))[0]

    def return_from_call(self, cleanup=0, value=0):
        destination = self.argument(0)
        self.u.reg_write(UC_X86_REG_ESP, self.u.reg_read(UC_X86_REG_ESP) + 4 + cleanup)
        self.u.reg_write(UC_X86_REG_EAX, value)
        self.u.reg_write(UC_X86_REG_EIP, destination)

    def observe(self, u, address, size, data):
        kind = self.boundaries.get(address)
        if kind is None:
            if address not in self.allowed:
                raise ValueError(f"Unobserved entry callee/instruction: {address:#x}")
            return
        cleanup, result = 0, 0
        if kind == "find":
            self.trace.append(["find", self.string(self.argument(1)), self.string(self.argument(2))])
            cleanup, result = 8, self.existing
        elif kind == "warning":
            self.trace.append(["warning", self.string(u.reg_read(UC_X86_REG_EAX))])
        elif kind == "foreground":
            self.trace.append(["foreground", self.argument(1)])
            cleanup, result = 4, self.foreground_result
        elif kind == "title":
            self.trace.append(["title", self.string(u.reg_read(UC_X86_REG_EDX))])
        elif kind == "form":
            self.trace.append(["form", self.forms[u.reg_read(UC_X86_REG_EDX)]])
        elif kind in ("initialize", "run", "exit"):
            self.trace.append([kind])
        elif kind in ("unit", "string-clear", "arguments", "content"):
            pass
        else:
            raise ValueError("Unknown entry observer: " + kind)
        if kind == "exit":
            self.finished = True
            u.emu_stop()
        else:
            self.return_from_call(cleanup, result)

    def run(self, existing, foreground_result=1):
        self.existing = existing
        self.foreground_result = foreground_result
        self.u.reg_write(UC_X86_REG_ESP, 0x3FF000)
        self.u.emu_start(self.entry, 0, count=10000)
        if not self.finished:
            raise ValueError("Entry did not reach normal process exit")
        return self.trace


def compare_entry(game, map_path):
    original_path = ROOT / "build/research/TSW.exe"
    if digest(original_path) != ORIGINAL_HASH:
        raise ValueError("Reference executable pin changed")
    old_pe, new_pe = pefile.PE(str(original_path)), pefile.PE(str(game))
    mapping = symbols(new_pe, map_path)
    cases = []
    for existing, focus in ((0, 1), (0x701234, 1), (0x702345, 0)):
        old = EntryTrace(old_pe).run(existing, focus)
        new = EntryTrace(new_pe, mapping).run(existing, focus)
        expected = [["find", "TTSW10", None]]
        if existing:
            expected += [["warning", WARNING], ["foreground", existing], ["exit"]]
        else:
            expected += [["initialize"], ["title", "Tower of the Sorcerer Ver1.2"]]
            expected += [["form", name] for name in ("TTSW10", "TAboutBox", "TForm2", "TForm4")]
            expected += [["run"], ["exit"]]
        if old != expected or new != old:
            raise ValueError(f"Program entry mismatch: expected {expected}, reference {old}, compiled {new}")
        cases.append(dict(existing_window=existing, foreground_result=focus, trace=new))
    return dict(reference_sha256=ORIGINAL_HASH, game_sha256=digest(game), cases=cases,
                scope="Program entry decisions; Windows/VCL calls observed; unit initialization skipped",
                reference_executable_launched=False, passed=True)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--game", type=Path, default=ROOT / "build/delphi-game/game/Tower.exe")
    args = parser.parse_args()
    report = compare_entry(args.game, args.game.with_suffix(".map"))
    output = ROOT / "build/delphi-game/reports/entry-comparison.json"
    output.parent.mkdir(parents=True, exist_ok=True)
    output.write_text(json.dumps(report, indent=2) + "\n", encoding="utf-8")
    print(f"Program entry: {len(report['cases'])} reference/compiled traces agree")


if __name__ == "__main__":
    main()
