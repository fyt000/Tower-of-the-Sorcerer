"""Read-only item evidence from the installed English TSW v1.2 executable.

Only isolated memory is changed. UI/RTL calls are skipped and reported;
the probe establishes branch, flag, and enable-state behavior, not rendering.
Requires pefile, capstone, and unicorn, as used by original_event_probe.py.
"""
import hashlib
import json
import os
import pathlib
import struct

import capstone
import pefile
import unicorn
from unicorn.x86_const import UC_X86_REG_EAX, UC_X86_REG_EDX, UC_X86_REG_EIP, UC_X86_REG_ESP

ROOT = pathlib.Path(__file__).resolve().parents[1]
EXE = pathlib.Path(os.environ.get("TOS_ORIGINAL_EXE", r"D:\Program Files (x86)\Tower of the Sorcerer\TSW.exe"))
EXPECTED_SHA256 = "41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779"
IMAGE = pefile.PE(str(EXE)).get_memory_mapped_image()
MD = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
BASE = 0x4B8688
WISDOM = BASE + 0x48
# In button order, offsets of the 24 remembered old-man / merchant clues.
CLUE_OFFSETS = [0x110, 0x114, 0xDC, 0xE0, 0xE4, 0xEC, 0x118, 0x120,
                0x124, 0x128, 0x12C, 0xF4, 0x130, 0x134, 0x138, 0xF8,
                0x13C, 0xFC, 0x140, 0x144, 0x100, 0x148, 0x104, 0x14C]


def disassembly(address, size):
    return [f"0x{i.address:06x}: {i.mnemonic} {i.op_str}".rstrip()
            for i in MD.disasm(IMAGE[address - 0x400000:address - 0x400000 + size], address)]


def isolated(address, end, values, watch):
    u = unicorn.Uc(unicorn.UC_ARCH_X86, unicorn.UC_MODE_32)
    u.mem_map(0, 0x300000)
    u.mem_map(0x400000, 0x300000)
    u.mem_write(0x400000, IMAGE)
    u.reg_write(UC_X86_REG_EAX, 0x200000)
    u.reg_write(UC_X86_REG_ESP, 0x6FF000)
    u.mem_write(0x6FF000, struct.pack("<I", 0x6FFFF0))
    # Give each form field a distinct inert control so enable calls can be read.
    for offset in range(0, 0x500, 4):
        u.mem_write(0x200000 + offset, struct.pack("<I", 0x210000 + offset * 16))
    for location, value in values:
        u.mem_write(location, struct.pack("<I", value))
    calls = []
    enables = {}

    def hook(uc, pc, size, _):
        if pc in (end, 0x6FFFF0):
            uc.emu_stop()
            return
        instruction = next(MD.disasm(bytes(uc.mem_read(pc, size)), pc))
        if instruction.mnemonic == "call":
            calls.append(instruction.op_str)
            if instruction.op_str == "0x41353c":
                enables[hex(uc.reg_read(UC_X86_REG_EAX))] = bool(uc.reg_read(UC_X86_REG_EDX) & 0xFF)
            uc.reg_write(UC_X86_REG_EIP, pc + size)

    u.hook_add(unicorn.UC_HOOK_CODE, hook)
    u.emu_start(address, 0x6FFFF0, count=200000)
    return {"memory": {hex(a): struct.unpack("<I", u.mem_read(a, 4))[0] for a in watch},
            "enabled_clue_ordinals": [n for n in range(24)
                                      if enables.get(hex(0x210000 + (0x1F0 + n * 4) * 16))],
            "skipped_calls": sorted(set(calls))}


def main():
    digest = hashlib.sha256(EXE.read_bytes()).hexdigest()
    if digest != EXPECTED_SHA256:
        raise RuntimeError("Executable differs from the audited v1.2 image; review addresses first")
    old_slot, merchant_slot = BASE + 0x110, BASE + 0xDC
    hearing = {}
    for owned in (0, 1):
        hearing[f"old_man_orb_{owned}"] = isolated(
            0x449CAD, 0x449CDD, [(WISDOM, owned), (0x48C55C, 0x44)], [old_slot])
        hearing[f"merchant_orb_{owned}"] = isolated(
            0x449654, 0x449684, [(WISDOM, owned), (0x48C59C, 0x37)], [merchant_slot])
    availability = {}
    for owned in (0, 1):
        for state in (0, 1, 2):
            values = [(WISDOM, owned)] + [(BASE + offset, state) for offset in CLUE_OFFSETS]
            availability[f"orb_{owned}_clue_state_{state}"] = isolated(
                0x48198C, 0x481E7B, values, [WISDOM])
    reset = isolated(0x455CB8, 0x456140,
                     [(BASE + offset, 2) for offset in CLUE_OFFSETS] + [(0x4B8904, 43), (0x4B8908, 1)],
                     [BASE + offset for offset in CLUE_OFFSETS])
    evidence = {
        "source": "Installed English Tower of the Sorcerer v1.2 (read-only executable)",
        "sha256": digest,
        "limits": "Calls are skipped. Probes demonstrate direct flag/branch/UI enable behavior only; disassembly accompanies all claims.",
        "wisdom": {
            "item_slot": hex(WISDOM), "dialogue_ids_in_button_order": list(range(62, 86)),
            "clue_slots_in_button_order": [hex(BASE + offset) for offset in CLUE_OFFSETS],
            "first_hearing": hearing, "menu_availability": availability,
            "cycle_initializer": reset,
            "old_man_first_hearing": disassembly(0x449C8A, 0x53),
            "merchant_first_hearing": disassembly(0x44960B, 0x79),
            "pickup": disassembly(0x445A80, 0x19),
            "menu": disassembly(0x48198C, 0x4F2),
            "first_button": disassembly(0x44EE4C, 0x18),
            "replay_string_lookup": disassembly(0x44A1DA, 0x3F),
            "save_block_write": disassembly(0x47EBC3, 0x1B),
            "load_block_read": disassembly(0x47E858, 0x1B),
        },
        "active_item_routines": {
            "mattock": disassembly(0x450DA7, 0x18A),
            "bomb": disassembly(0x450F31, 0x207),
            "crystal": disassembly(0x4516AB, 0x23B),
            "crystal_tile_helper": disassembly(0x451D3C, 0xC0),
            "crystal_queue_execution": disassembly(0x4541A9, 0x20),
            "classifier": disassembly(0x451C20, 0x11C),
        },
    }
    assert hearing["old_man_orb_0"]["memory"][hex(old_slot)] == 1
    assert hearing["old_man_orb_1"]["memory"][hex(old_slot)] == 2
    assert hearing["merchant_orb_0"]["memory"][hex(merchant_slot)] == 1
    assert hearing["merchant_orb_1"]["memory"][hex(merchant_slot)] == 2
    assert availability["orb_1_clue_state_2"]["enabled_clue_ordinals"] == list(range(24))
    assert all(not result["enabled_clue_ordinals"] for key, result in availability.items()
               if key != "orb_1_clue_state_2")
    assert all(value == 0 for value in reset["memory"].values())
    (ROOT / "data/original-item-evidence.json").write_text(
        json.dumps(evidence, indent=2) + "\n", encoding="utf-8")
    print("Verified Wisdom first-hearing states, all 24 menu gates, and cycle reset; recorded item disassembly")


if __name__ == "__main__":
    main()
