"""Read-only executable evidence for original Giant Octopus encounters.

This runs the actual dispatcher, battle queue builder, and arithmetic helpers
in isolated Unicorn memory. Windows drawing/strings are not executed. The
movement helper executes its coordinate-update fragment; visual movement and
unrelated field-hazard callbacks are bypassed and explicitly reported.
"""
import argparse
import hashlib
import json
import pathlib
import struct

import capstone
import pefile
import unicorn
from unicorn.x86_const import (
    UC_X86_REG_EAX, UC_X86_REG_EBX, UC_X86_REG_ECX,
    UC_X86_REG_EDX, UC_X86_REG_EIP, UC_X86_REG_ESP,
)

from recovery_evidence import original_exe

ROOT = pathlib.Path(__file__).resolve().parents[1]
EXE = original_exe()
PE = pefile.PE(str(EXE))
IMAGE = PE.get_memory_mapped_image()
MD = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
MAP = 0x4B8934
QUEUE = 0x48C74C
CURSOR = 0x48C5AC
END = 0x6FFFF0
FOLLOW = {0x44A480, 0x44C04C, 0x450064, 0x450288, 0x4502D0,
          0x45031C, 0x450360, 0x4503A8}


def memory():
    u = unicorn.Uc(unicorn.UC_ARCH_X86, unicorn.UC_MODE_32)
    u.mem_map(0, 0x300000)
    u.mem_map(0x400000, 0x300000)
    u.mem_write(0x400000, IMAGE)
    u.reg_write(UC_X86_REG_EAX, 0x200000)
    u.reg_write(UC_X86_REG_ESP, 0x6FF000)
    u.mem_write(0x6FF000, struct.pack("<I", END))
    return u


def put(u, address, value):
    u.mem_write(address, struct.pack("<I", value))


def get(u, address):
    return struct.unpack("<I", u.mem_read(address, 4))[0]


def run_encounter(tile, *, lucky=0, cycle_factor=0, attack=420,
                  defense=100, hp=10000, removed=(), raw_gold=100):
    u = memory()
    floor = 16
    index = tile - 97
    x, y = 4 + index % 3, 4 + index // 3
    encounter = y * 11 + x
    board = bytearray([6] * 121)
    for i in range(9):
        board[(4 + i // 3) * 11 + 4 + i % 3] = 97 + i
    for old in removed:
        i = old - 97
        board[(4 + i // 3) * 11 + 4 + i % 3] = 6
    u.mem_write(MAP + floor * 123 + 2, bytes(board))
    for address, value in [
        (0x200254, 0x201000), (0x20102C, 40), (0x201030, 40),
        (0x4B8688, hp), (0x4B868C, attack), (0x4B8690, defense),
        (0x4B8698, floor), (0x4B86A0, x), (0x4B86A4, y + 1),
        (0x48C584, encounter), (0x4B87E8, 4), (0x4B8704, lucky),
        (0x4B8904, cycle_factor), (CURSOR, 0),
        (0x489910 + 18 * 16 + 12, raw_gold),
    ]:
        put(u, address, value)
    skipped = set()
    followed = set()
    redirects = set()
    state = {}

    def hook(uc, address, size, _):
        if address in {0x44B6AA, 0x4547E8, END}:
            uc.emu_stop()
            return
        # Execute the original idou x/y writes without Win32 walking/drawing.
        redirects_by_address = {0x44C052: 0x44C18A, 0x44C1AF: 0x44C45C,
                                0x4501DE: 0x450252, 0x44AACB: 0x44AB6E}
        if address in redirects_by_address:
            target = redirects_by_address[address]
            redirects.add(f"{address:#x}->{target:#x}")
            uc.reg_write(UC_X86_REG_EIP, target)
            return
        if address == 0x44AA49:
            state.update(monster_row=get(uc, 0x48C5B8),
                         monster_hp=get(uc, 0x48C5BC),
                         hero_strikes=get(uc, 0x48C56C),
                         expected_damage=get(uc, 0x48C568))
        ins = next(MD.disasm(bytes(uc.mem_read(address, size)), address))
        if ins.mnemonic != "call":
            return
        direct = int(ins.op_str, 16) if ins.op_str.startswith("0x") else None
        if direct in FOLLOW:
            followed.add(f"{direct:#x}")
            return
        skipped.add(ins.op_str)
        # Delphi's string concatenation consumes EDX stack arguments.
        if direct == 0x403710:
            uc.reg_write(UC_X86_REG_ESP,
                         uc.reg_read(UC_X86_REG_ESP) + 4 * uc.reg_read(UC_X86_REG_EDX))
        uc.reg_write(UC_X86_REG_EIP, address + size)

    u.hook_add(unicorn.UC_HOOK_CODE, hook)
    u.emu_start(0x444490, END, count=1000000)
    records = [list(struct.unpack("<HHH", u.mem_read(QUEUE + i * 6, 6)))
               for i in range(get(u, CURSOR), 0, -1)]
    rewards = [q[1] for q in records if q[0] == 7]
    clears = [[q[1] % 11, q[1] // 11] for q in records if q[0] == 17 and q[2] == 6]
    count = get(u, CURSOR)
    assert count < 10000
    handlers = {4: 0x452C2A, 5: 0x452B2A, 7: 0x452DEB, 17: 0x4541A9}
    # Run the actual HP, gold and map-write opcode bodies, in queue order.
    for slot, record in zip(range(count, 0, -1), records):
        if record[0] not in handlers:
            continue
        put(u, CURSOR, slot)
        u.reg_write(UC_X86_REG_EBX, 0x200000)
        u.reg_write(UC_X86_REG_ECX, slot * 3)
        u.emu_start(handlers[record[0]], END, count=100000)
    final_board = bytes(u.mem_read(MAP + floor * 123 + 2, 121))
    return {"tile": tile, "lucky_gold": lucky, "cycle_factor_minus_one": cycle_factor,
            "input_monster_gold": raw_gold,
            "input_hero": {"hp": hp, "attack": attack, "defense": defense},
            "prior_removed_tiles": list(removed), "encounter": [x, y], **state,
            "raw_reward_records": rewards,
            "reward_after_opcode7_lucky_multiplier": [r * (lucky + 1) for r in rewards],
            "clear_cells": clears, "queue_records": len(records),
            "applied_hero_hp": get(u, 0x4B8688),
            "applied_hero_gold": get(u, 0x4B8694),
            "applied_tile_changes": [[i % 11, i // 11, new]
                                     for i, (old, new) in enumerate(zip(board, final_board))
                                     if old != new],
            "hero_strike_records": sum(q[0] == 5 for q in records),
            "enemy_strike_records": sum(q[0] == 4 for q in records),
            "whole_creature_animation_records": [q for q in records if q[0] == 14],
            "final_hero_position": [get(u, 0x4B86A0), get(u, 0x4B86A4)],
            "followed_calls": sorted(followed), "skipped_calls": sorted(skipped),
            "bypassed_ui_paths": sorted(redirects)}


def dispatcher_and_mapping(tile):
    """Probe alternate atlas IDs only to the stat-row mapping boundary."""
    u = memory()
    put(u, 0x4B8698, 1)
    put(u, 0x48C584, 60)
    put(u, 0x48C554, 0)
    u.mem_write(MAP + 123 + 2 + 60, bytes([tile]))
    result = {}

    def hook(uc, address, size, _):
        if address == 0x44A54A:
            result["sprite_marker"] = get(uc, 0x48C554)
            uc.emu_stop()
            return
        if address == END:
            uc.emu_stop()
            return
        ins = next(MD.disasm(bytes(uc.mem_read(address, size)), address))
        if ins.mnemonic == "call":
            direct = int(ins.op_str, 16) if ins.op_str.startswith("0x") else None
            if direct == 0x44A480:
                result["dispatches_to_battle"] = True
            else:
                uc.reg_write(UC_X86_REG_EIP, address + size)

    u.hook_add(unicorn.UC_HOOK_CODE, hook)
    u.emu_start(0x444490, END, count=100000)
    marker = result.get("sprite_marker")
    return {"tile": tile, **result,
            "monster_row": marker - 198 if marker is not None else None}


def evidence():
    ordinary = [run_encounter(tile, lucky=lucky)
                for lucky in [0, 1] for tile in range(97, 106)]
    for r in ordinary:
        assert r["monster_row"] == 18
        assert r["monster_hp"] == 1200
        assert r["hero_strikes"] == 3
        assert r["expected_damage"] == 160
        assert r["hero_strike_records"] == 3
        assert r["enemy_strike_records"] == 2
        assert r["raw_reward_records"] == [100 if r["tile"] == 104 else 50]
        assert len(r["clear_cells"]) == (9 if r["tile"] == 104 else 1)
        assert r["applied_hero_hp"] == 9840
        assert r["applied_hero_gold"] == (100 if r["tile"] == 104 else 50) * (r["lucky_gold"] + 1)
        assert len(r["applied_tile_changes"]) == (9 if r["tile"] == 104 else 1)
    backside = [run_encounter(tile, lucky=lucky, cycle_factor=43,
                             attack=18480, defense=4400, hp=440000)
                for lucky in [0, 1] for tile in [103, 104, 105]]
    for r in backside:
        assert r["monster_hp"] == 52800 and r["hero_strikes"] == 3
        assert r["expected_damage"] == 7040
        assert r["raw_reward_records"] == [100 if r["tile"] == 104 else 50]
    repeat = [run_encounter(104, removed=[103]), run_encounter(105, removed=[103])]
    for r in repeat:
        assert r["monster_hp"] == 1200 and r["expected_damage"] == 160
    impossible = run_encounter(103, attack=20)
    fatal = run_encounter(103, hp=160)
    assert not impossible["raw_reward_records"] and not impossible["clear_cells"]
    assert not fatal["raw_reward_records"] and not fatal["clear_cells"]
    odd = [run_encounter(tile, lucky=lucky, raw_gold=101)
           for lucky in [0, 1] for tile in [103, 104, 105]]
    for r in odd:
        assert r["applied_hero_gold"] == (101 if r["tile"] == 104 else 50) * (r["lucky_gold"] + 1)
    return {
        "source": str(EXE), "sha256": hashlib.sha256(EXE.read_bytes()).hexdigest(),
        "method": "Actual handan/taisen and recursive arithmetic helpers in isolated memory; GUI and string routines bypassed. Queue effects independently decoded, not a live Windows run.",
        "octopus_monster_row": list(struct.unpack("<4I", IMAGE[0x89910 + 18 * 16:0x89910 + 19 * 16])),
        "ordinary_encounters": ordinary, "backside_encounters": backside,
        "after_limb_removed_encounters": repeat,
        "edited_odd_reward_encounters": odd,
        "impossible_encounter": impossible, "fatal_encounter": fatal,
        "atlas_id_dispatch_and_mapping": [dispatcher_and_mapping(tile) for tile in range(97, 115)],
        "verified_addresses": {
            "dispatcher": "0x4445ad..0x4445b3 -> 0x448fa0 -> 0x44a480",
            "octopus_row_selection": "0x44a506 writes 0xd8, subtract0xc6 -> row18",
            "enemy_hp_cycle_scaling": "0x44a5a6..0x44a5be",
            "battle_forecast": "0x450064 and recursive0x45031c",
            "limb_reward_halving": "0x44ab6e..0x44aea2, eight cells except104",
            "main_body_footprint_clear": "0x44aeea..0x44b0e1, tile104 only",
            "lucky_gold_queue_handler": "0x452deb..0x452e04",
            "whole_creature_visual_clear": "opcode14 calls takowork1/2 at0x4548a0/0x454a58",
            "map_tile_write_queue_handler": "opcode17 at0x4541a9..0x4541c5",
        },
    }


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("--check", action="store_true")
    args = parser.parse_args()
    report = evidence()
    destination = ROOT / "data/original-octopus-evidence.json"
    text = json.dumps(report, indent=2) + "\n"
    if args.check:
        assert json.loads(destination.read_text(encoding="utf-8")) == report
        print("Original octopus evidence matches installed executable.")
    else:
        destination.write_text(text, encoding="utf-8")
        print(f"Wrote {destination}")
