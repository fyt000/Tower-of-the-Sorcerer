"""Read-only probes of the installed original Hero Orb's octopus list.

Executes the floor-list tile scanner and the row builder/arithmetic. Drawing,
Windows controls, strings and allocation are skipped and reported. Numeric
arguments passed to the original integer-to-string routine are recorded.
"""
import argparse
import hashlib
import json
import os
import pathlib
import struct

import capstone
import pefile
import unicorn
from extract_original import extract_dialogue
from unicorn.x86_const import (
    UC_X86_REG_EAX, UC_X86_REG_EBX, UC_X86_REG_EDX,
    UC_X86_REG_EIP, UC_X86_REG_ESP,
)

ROOT = pathlib.Path(__file__).resolve().parents[1]
EXE = pathlib.Path(os.environ.get(
    "TOS_ORIGINAL_EXE", r"D:\Program Files (x86)\Tower of the Sorcerer\TSW.exe"))
IMAGE = pefile.PE(str(EXE)).get_memory_mapped_image()
MD = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
END = 0x6FFFF0
MAP = 0x4B8934


def put(u, address, value):
    u.mem_write(address, struct.pack("<I", value))


def get(u, address):
    return struct.unpack("<I", u.mem_read(address, 4))[0]


def memory():
    u = unicorn.Uc(unicorn.UC_ARCH_X86, unicorn.UC_MODE_32)
    u.mem_map(0, 0x300000)
    u.mem_map(0x400000, 0x300000)
    u.mem_write(0x400000, IMAGE)
    u.reg_write(UC_X86_REG_EAX, 0x200000)
    u.reg_write(UC_X86_REG_EBX, 0x200000)
    u.reg_write(UC_X86_REG_ESP, 0x6FF000)
    put(u, 0x6FF000, END)
    put(u, 0x20044C, 0x201000)
    put(u, 0x201100, 0x202000)
    return u


def scan(tiles):
    u = memory()
    floor = 16
    put(u, 0x4B8698, floor)
    board = bytearray([6] * 121)
    for index, tile in enumerate(tiles):
        board[index] = tile
    u.mem_write(MAP + floor * 123 + 2, bytes(board))
    rows = []

    def hook(uc, address, size, _):
        if address == 0x481823:
            uc.emu_stop()
        elif address in (0x4817B9, 0x4817CC, 0x4817DF, 0x481814):
            index = get(uc, 0x48C570) - 1
            rows.append({"index": index, "tile": board[index],
                         "row": get(uc, 0x48C55C)})
            uc.reg_write(UC_X86_REG_EIP, address + size)

    u.hook_add(unicorn.UC_HOOK_CODE, hook)
    u.emu_start(0x481744, END, count=10000)
    return {"tiles": tiles, "row_builder_calls": rows,
            "skipped_calls": ["0x44f26c"] if rows else []}


def row(*, lucky, cycle_factor=0, attack=420, defense=100, raw_gold=100):
    u = memory()
    for address, value in ((0x48C55C, 18), (0x48C5B0, 1),
                           (0x4B868C, attack), (0x4B8690, defense),
                           (0x4B8904, cycle_factor), (0x4B8704, lucky),
                           (0x489910 + 18 * 16 + 12, raw_gold)):
        put(u, address, value)
    conversions, labels, followed, skipped, reward_reads = [], [], set(), set(), []

    def hook(uc, address, size, _):
        if address == END:
            uc.emu_stop()
            return
        ins = next(MD.disasm(bytes(uc.mem_read(address, size)), address))
        if ins.mnemonic != "call":
            return
        target = int(ins.op_str, 16) if ins.op_str.startswith("0x") else None
        if target in (0x44FF0C, 0x45031C):
            followed.add(hex(target))
            return
        if target == 0x405B6C:
            conversions.append(uc.reg_read(UC_X86_REG_EAX))
        if ins.op_str == "dword ptr [esi + 0xc]" or ins.op_str == "dword ptr [ebx + 0xc]":
            labels.append(uc.reg_read(UC_X86_REG_EDX))
        skipped.add(ins.op_str)
        # Skipped calls that consume explicit stack arguments.
        if target == 0x41DAD8:
            uc.reg_write(UC_X86_REG_ESP, uc.reg_read(UC_X86_REG_ESP) + 8)
        if target == 0x403710:
            uc.reg_write(UC_X86_REG_ESP, uc.reg_read(UC_X86_REG_ESP)
                         + 4 * uc.reg_read(UC_X86_REG_EDX))
        uc.reg_write(UC_X86_REG_EIP, address + size)

    def read(uc, access, address, size, value, _):
        gold_address = 0x489910 + 18 * 16 + 12
        if address <= gold_address < address + size:
            reward_reads.append(hex(address))

    u.hook_add(unicorn.UC_HOOK_CODE, hook)
    u.hook_add(unicorn.UC_HOOK_MEM_READ, read)
    u.emu_start(0x44F26C, END, count=100000)
    assert conversions[:3] == [1200 * (cycle_factor + 1),
                               180 * (cycle_factor + 1),
                               20 * (cycle_factor + 1)]
    assert len(conversions) == 4
    assert not reward_reads
    return {"lucky_gold": lucky, "cycle_factor": cycle_factor,
            "hero_attack": attack, "hero_defense": defense,
            "raw_gold": raw_gold, "numeric_strings": conversions,
            "string_resource_ids": labels,
            "hero_strikes": get(u, 0x48C56C),
            "damage": get(u, 0x48C568), "gold_table_reads": reward_reads,
            "followed_calls": sorted(followed), "skipped_calls": sorted(skipped)}


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--check", action="store_true")
    args = parser.parse_args()
    scans = [scan([tile]) for tile in range(97, 106)]
    scans += [scan(list(range(97, 106))), scan([104, 104])]
    assert [len(result["row_builder_calls"]) for result in scans[:9]] == [0] * 7 + [1, 0]
    assert scans[-2]["row_builder_calls"] == [{"index": 7, "tile": 104, "row": 18}]
    rows = [row(lucky=lucky, raw_gold=gold) for lucky in (0, 1) for gold in (100, 101)]
    assert all(result["numeric_strings"] == [1200, 180, 20, 160] for result in rows)
    rows += [row(lucky=0, cycle_factor=43, attack=18480, defense=4400)]
    assert rows[-1]["numeric_strings"] == [52800, 7920, 880, 7040]
    report = {"exe_sha256": hashlib.sha256(EXE.read_bytes()).hexdigest(),
              "scanner_range": "0x481744..0x481823",
              "row_builder": "0x44f26c", "damage_builder": "0x44ff0c",
              "limitations": "Only scanner/row builder/arithmetic executed; UI, strings, allocations and drawing skipped.",
              "string_resources": [entry for entry in extract_dialogue(EXE.read_bytes())
                                   if entry["id"] in (180, 184, 185, 214, 215, 216)],
              "scans": scans, "row_numeric_probes": rows}
    destination = ROOT / "data/original-octopus-forecast-evidence.json"
    output = json.dumps(report, indent=2) + "\n"
    if args.check:
        assert destination.read_text(encoding="utf-8") == output
    else:
        destination.write_text(output, encoding="utf-8")
    print(f"Verified {len(scans)} scanners and {len(rows)} numeric row probes: {destination}")


if __name__ == "__main__":
    main()
