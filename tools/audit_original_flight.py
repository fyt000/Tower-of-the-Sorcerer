"""Read-only Flight control probes against the installed original executable.

This deliberately does not launch the game. It executes the installed x86
instructions in isolated memory, using the shared event probe's documented
call-skipping boundary. Run from any directory; evidence is written only to
this repository. TOS_ORIGINAL_EXE can override the installation path.
"""

import hashlib
import json
import os
import struct
from pathlib import Path

import unicorn
from unicorn.x86_const import UC_X86_REG_EAX, UC_X86_REG_EIP, UC_X86_REG_ESP

from original_event_probe import ROOT, md, pe, probe


EXE = Path(os.environ.get(
    "TOS_ORIGINAL_EXE", r"D:\Program Files (x86)\Tower of the Sorcerer\TSW.exe"
))


def control(name, address, floor, highest, direction=0, changes=()):
    result = probe(
        address, floor, 5, 5,
        globals=[(0x4B869C, highest), (0x4B8900, direction)],
        changes=changes,
    )
    return {
        "name": name,
        "entry": hex(address),
        "initial_selected_floor": floor,
        "highest_stair_floor": highest,
        "initial_last_direction": direction,
        "map_seed": list(changes),
        "result_selected_floor": result["stat_slots"][4],
        "result_position": result["stat_slots"][6:8],
        "map_writes": result["changed"],
        "skipped_calls": result["calls"],
    }


def disassembly(start, end):
    image = pe.get_memory_mapped_image()
    return [
        f"{instruction.address:08x} {instruction.mnemonic} {instruction.op_str}"
        for instruction in md.disasm(image[start - 0x400000:end - 0x400000], start)
    ]


def stairs(name, address, floor, highest, end, holy_sword_flag=0, changes=()):
    result = probe(
        address, floor, 5, 5, end=end,
        globals=[(0x4B869C, highest), (0x4B8714, holy_sword_flag)],
        changes=changes,
    )
    return {
        "name": name,
        "entry": hex(address),
        "end": hex(end),
        "resulting_floor": floor,
        "initial_highest_stair_floor": highest,
        "initial_holy_sword_collected_flag": holy_sword_flag,
        "map_seed": list(changes),
        "result_highest_stair_floor": result["stat_slots"][5],
        "map_writes": result["changed"],
        "skipped_calls": result["calls"],
    }


def holy_sword_state(name, entry, end, initial_flag, retain_items=0):
    """Execute direct pickup/reset writes, including the stat-base alias."""
    machine = unicorn.Uc(unicorn.UC_ARCH_X86, unicorn.UC_MODE_32)
    machine.mem_map(0, 0x300000)
    machine.mem_map(0x400000, 0x300000)
    machine.mem_write(0x400000, pe.get_memory_mapped_image())
    machine.reg_write(UC_X86_REG_EAX, 0x200000)
    machine.reg_write(UC_X86_REG_ESP, 0x6FF000)
    machine.mem_write(0x6FF000, struct.pack("<I", 0x6FFFF0))
    for address, value in [(0x4B8714, initial_flag),
                           (0x4B868C, 100), (0x4B86C4, 5),
                           (0x4B8904, 0), (0x4B8908, retain_items)]:
        machine.mem_write(address, struct.pack("<I", value))
    skipped = set()

    def hook(uc, address, size, _):
        if address in [end, 0x6FFFF0]:
            uc.emu_stop()
            return
        instruction = next(md.disasm(bytes(uc.mem_read(address, size)), address))
        if instruction.mnemonic == "call":
            skipped.add(instruction.op_str)
            uc.reg_write(UC_X86_REG_EIP, address + size)

    machine.hook_add(unicorn.UC_HOOK_CODE, hook)
    machine.emu_start(entry, 0x6FFFF0, count=200000)

    def read(address):
        return struct.unpack("<I", machine.mem_read(address, 4))[0]

    return {
        "name": name, "entry": hex(entry), "end": hex(end),
        "initial_holy_sword_collected_flag": initial_flag,
        "retain_items_flag": retain_items,
        "result_holy_sword_collected_flag": read(0x4B8714),
        "result_attack": read(0x4B868C),
        "result_displayed_sword_tier": read(0x4B86C4),
        "skipped_calls": sorted(skipped),
    }


def main():
    fairies = [(25, 5, 6, 23), (49, 5, 1, 23)]
    thief_done = [(35, 3, 8, 6), (2, 10, 10, 21)]
    cases = [
        control("upward_preview_34_to_35_completed_tunnel", 0x44ED94, 34, 40,
                changes=thief_done),
        control("upward_preview_34_to_35_incomplete_tunnel", 0x44ED94, 34, 40,
                changes=[(35, 3, 8, 8), (2, 10, 10, 21)]),
        control("downward_preview_36_to_35_has_no_completion_check", 0x44ED1C,
                36, 40, changes=thief_done),
        control("confirm_without_arrow_keeps_position_and_fairies", 0x44EAF4,
                24, 49, changes=fairies),
        control("confirm_selected_24_removes_both_existing_fairies", 0x44EAF4,
                24, 49, 2, fairies),
        control("confirm_selected_25_keeps_25_fairy_only", 0x44EAF4,
                25, 49, 1, fairies),
        control("confirm_selected_49_keeps_49_fairy_only", 0x44EAF4,
                49, 49, 1, fairies),
        control("confirm_below_29_when_highest_29_moves_thief", 0x44EAF4,
                28, 29, 2),
        control("confirm_29_when_highest_29_keeps_thief", 0x44EAF4,
                29, 29, 2),
        control("confirm_below_29_when_highest_30_keeps_thief", 0x44EAF4,
                28, 30, 2),
        control("up_preview_cannot_reach_35_when_highest_34", 0x44ED94,
                34, 34, changes=thief_done),
        control("up_preview_can_revisit_35_when_highest_35", 0x44ED94,
                34, 35, changes=thief_done),
    ]
    assert cases[0]["map_writes"] == [(2, 10, 10, 6)]
    assert cases[1]["map_writes"] == []
    assert cases[2]["map_writes"] == []
    assert cases[3]["map_writes"] == []
    assert cases[3]["result_position"] == [5, 5]
    assert cases[4]["map_writes"] == [(25, 5, 6, 6), (49, 5, 1, 6)]
    assert cases[5]["map_writes"] == [(49, 5, 1, 6)]
    assert cases[6]["map_writes"] == [(25, 5, 6, 6)]
    assert cases[7]["map_writes"] == [
        (29, 6, 1, 21), (29, 5, 2, 6), (29, 5, 3, 6)
    ]
    assert cases[8]["map_writes"] == []
    assert cases[9]["map_writes"] == []
    assert cases[10]["result_selected_floor"] == 34
    assert cases[10]["map_writes"] == []
    assert cases[11]["result_selected_floor"] == 35
    assert cases[11]["map_writes"] == [(2, 10, 10, 6)]
    stair_cases = [
        stairs("normal_downstairs_to_28_highest_29_moves_thief", 0x444FBC,
               28, 29, 0x444FE3),
        stairs("normal_downstairs_to_28_highest_30_keeps_thief", 0x444FBC,
               28, 30, 0x444FE3),
        stairs("normal_downstairs_to_27_highest_29_keeps_thief", 0x444FBC,
               27, 29, 0x444FE3),
        stairs("new_highest_35_holy_sword_flag_0_keeps_f2_thief", 0x444E0F,
               35, 34, 0x444E4C, 0, thief_done),
        stairs("new_highest_35_holy_sword_flag_1_keeps_f2_thief", 0x444E0F,
               35, 34, 0x444E4C, 1, thief_done),
        stairs("new_highest_35_synthetic_flag_35_clears_f2_thief", 0x444E0F,
               35, 34, 0x444E4C, 35, thief_done),
        stairs("normal_revisit_35_keeps_f2_thief", 0x444E0F,
               35, 35, 0x444E4C, 1, thief_done),
    ]
    assert stair_cases[0]["map_writes"] == [
        (29, 6, 1, 21), (29, 5, 2, 6), (29, 5, 3, 6)
    ]
    assert all(case["map_writes"] == [] for case in stair_cases[1:5])
    assert stair_cases[5]["map_writes"] == [(2, 10, 10, 6)]
    assert stair_cases[6]["map_writes"] == []
    assert all(case["result_highest_stair_floor"] == 35
               for case in stair_cases[3:])
    sword_cases = [
        holy_sword_state("pickup_sets_collected_flag_one", 0x445E91,
                         0x445EB4, 0),
        holy_sword_state("fresh_reset_clears_base_plus_8c", 0x455CBD,
                         0x455DEF, 1),
        holy_sword_state("retaining_items_reset_keeps_flag_one", 0x455CBD,
                         0x455DEF, 1, retain_items=1),
    ]
    assert sword_cases[0]["result_holy_sword_collected_flag"] == 1
    assert sword_cases[0]["result_attack"] == 150
    assert sword_cases[0]["result_displayed_sword_tier"] == 4
    assert sword_cases[1]["result_holy_sword_collected_flag"] == 0
    assert sword_cases[2]["result_holy_sword_collected_flag"] == 1
    evidence = {
        "original_exe_sha256": hashlib.sha256(EXE.read_bytes()).hexdigest(),
        "boundary": "Direct Flight-control instructions, isolated normal-stair guards and direct Sword pickup/reset writes; every helper call skipped and listed. Stair probes begin after the floor increment/decrement. No original game launch or installation write.",
        "probes": cases,
        "normal_stair_probes": stair_cases,
        "holy_sword_slot_probes": sword_cases,
        "disassembly": {
            "confirm_fairy_cleanup_and_landing": disassembly(0x44EB2B, 0x44EC25),
            "up_preview_tunnel_cleanup": disassembly(0x44EDD8, 0x44EDFE),
            "normal_downstairs_thief_relocation": disassembly(0x444FBC, 0x444FE3),
            "normal_ascent_holy_sword_flag_35_comparison": disassembly(0x444E0F, 0x444E4C),
            "holy_sword_pickup_flag": disassembly(0x445E91, 0x445EB4),
            "holy_sword_reset_via_stat_base_alias": disassembly(0x455D43, 0x455DEF),
            "flight_up_highest_stair_limit": disassembly(0x44ED94, 0x44EDCA),
            "stat_block_load_including_sword_flag": disassembly(0x47E85D, 0x47E873),
            "escape_only_item_picker": disassembly(0x461076, 0x4610A3),
        },
    }
    target = ROOT / "data" / "original-flight-evidence.json"
    target.write_text(json.dumps(evidence, indent=2) + "\n", encoding="utf-8")
    print(f"Passed {len(cases)} original Flight, {len(stair_cases)} stair and {len(sword_cases)} Sword-state probes; wrote {target}.")


if __name__ == "__main__":
    main()
