"""Compare recovered Delphi game code and retained original resources.

Both original-address and production-storage compilations execute in Unicorn.
All calls inside tested core routines execute; no gameplay call is stubbed.
IME acceptance is narrow, checked independently of gameplay comparisons.
"""
import argparse
import hashlib
import itertools
import json
import random
import struct

import pefile
import unicorn
from unicorn.x86_const import UC_X86_REG_EAX, UC_X86_REG_ESP, UC_X86_REG_EIP, UC_X86_REG_EFLAGS
from unicorn.x86_const import UC_X86_REG_EDX

from verify_delphi2_reference import (ROOT, ORIGINAL_HASH, digest, emulator, execute,
                                     symbols, instructions, normalized, framework_cases, RUNTIME)
from build_delphi_game import WORK

ENTRIES = dict(InitializeCycle=0x455CB8, ClassifyNeighbor=0x451C20, ClassifyInteraction=0x44C9F0,
               FaceUpLanding=0x442F80, FaceDownLanding=0x443050, CountHeroStrikes=0x45031C,
               CountDoubleHeroStrikes=0x450360, CountEnemyStrikes=0x4503A8,
               EnemyFirstDamage=0x450288, SelectGraphicFrame=0x454C10,
               DoubleEnemyFirstDamage=0x4502D0, CountBattleHeroStrikes=0x4802FC,
               CountBattleEnemyStrikes=0x480340, BattleDamage=0x48028C,
               DoorAnimation=0x4660D0, MattockWall=0x451B98, CrystalLava=0x451D3C,
               CheckSpecialDoors=0x47BEAC)
STORAGE = dict(Hero=0x4B8688, Map=0x4B8934, Monster=0x489910, Scratch=0x48C558,
               Neighbor=0x48C55C, TileClass=0x48C58C, MonsterIndex=0x48C5B8,
               RemainingHP=0x48C5B4, Strike=0x48C56C, Damage=0x48C568,
               Graphic=0x48C5A8, Door=0x48C554, EventCursor=0x48C5AC,
               EventStack=0x48C74C, Contact=0x48C584, DamageMode=0x48C564)
# Exercise and guard the first 512 records; native storage has a provisional
# 30,000-record provision whose original declaration is not authenticated.
SIZES = {name: dict(Hero=684, Map=6273, Monster=528, EventStack=512 * 6).get(name, 4) for name in STORAGE}


def exports(pe):
    return {s.name.decode(): pe.OPTIONAL_HEADER.ImageBase + s.address for s in pe.DIRECTORY_ENTRY_EXPORT.symbols}


def locations(pe, entry):
    machine = emulator(pe)
    result = {}
    for name in STORAGE:
        execute(machine, entry[name + "Storage"])
        result[name] = machine.reg_read(UC_X86_REG_EAX)
    spans = [(a, a + SIZES[name]) for name, a in result.items()]
    for i, (start, stop) in enumerate(spans):
        if any(start < b and a < stop for a, b in spans[:i]):
            raise ValueError("Compiled core storage unexpectedly overlaps")
    return result


class Runner:
    def __init__(self, pe, entries, storage):
        self.machine = emulator(pe)
        self.entries, self.storage = entries, storage
        self.calls, self.writes = [], []
        self.effects = []
        self.allowed = [(at, at + SIZES[n]) for n, at in storage.items()]
        self.names = {v: k for k, v in entries.items() if k in ENTRIES}
        self.machine.hook_add(unicorn.UC_HOOK_MEM_WRITE, self.write)
        self.machine.hook_add(unicorn.UC_HOOK_CODE, self.step)

    def write(self, u, access, at, size, value, _):
        if 0x3FD000 <= at and at + size <= 0x3FF000:
            return
        for name, address in self.storage.items():
            if address <= at and at + size <= address + SIZES[name]:
                event = [name, at - address, size, value & ((1 << (size * 8)) - 1)]
                self.writes.append(event)
                self.effects.append(["write", *event])
                return
        raise ValueError(f"Unexpected CPU write outside reconstructed state: {at:#x}")

    def step(self, u, at, size, _):
        if at in self.names:
            self.calls.append(self.names[at])
            self.effects.append(["enter", self.names[at]])

    def run(self, name, state):
        self.calls.clear()
        self.writes.clear()
        self.effects.clear()
        for field, raw in state.items():
            self.machine.mem_write(self.storage[field], bytes(raw))
        stop, stack = 0x3FF000, 0x3FE000
        self.machine.mem_write(0x3FD000, bytes(0x2000))
        self.machine.mem_write(stack, struct.pack("<I", stop))
        self.machine.reg_write(UC_X86_REG_ESP, stack)
        self.machine.reg_write(UC_X86_REG_EFLAGS, 2)
        self.machine.reg_write(UC_X86_REG_EAX, 0)
        self.machine.emu_start(self.entries[name], stop, count=200000)
        if self.machine.reg_read(UC_X86_REG_EIP) != stop or self.machine.reg_read(UC_X86_REG_ESP) != stack + 4:
            raise ValueError("Core routine failed to return within the instruction budget")
        result = {field: bytes(self.machine.mem_read(at, SIZES[field])) for field, at in self.storage.items()}
        return result, list(self.calls), list(self.writes), list(self.effects)


def baseline(original, seed=1):
    rng = random.Random(seed)
    state = {k: bytes(SIZES[k]) for k in STORAGE}
    state["Hero"] = bytearray(rng.randbytes(684))
    state["Map"] = bytearray((ROOT / "data/original-map-bytes.bin").read_bytes())
    state["Monster"] = original.get_data(0x489910 - original.OPTIONAL_HEADER.ImageBase, 528)
    for offset, value in [(0, 1000), (4, 100), (8, 100), (16, 1), (20, 1), (24, 5), (28, 5), (636, 0)]:
        struct.pack_into("<I", state["Hero"], offset, value)
    return state


def sethero(state, offset, value):
    struct.pack_into("<I", state["Hero"], offset, value & 0xFFFFFFFF)


def setscalar(state, field, value):
    state[field] = struct.pack("<I", value & 0xFFFFFFFF)


def cases(original):
    for cycle, later, seed in itertools.product((0, 43), (0, 1), (0, 7, 49)):
        state = baseline(original, seed)
        sethero(state, 636, cycle)
        sethero(state, 640, later)
        yield "InitializeCycle", dict(cycle=cycle, later=later, seed=seed), state
    for tile, floor, index, prior in itertools.product(range(256), (0, 1, 50), (0, 60, 120), (-1, 7)):
        state = baseline(original)
        sethero(state, 16, floor)
        state["Map"][floor * 123 + index + 2] = tile
        setscalar(state, "Neighbor", index)
        setscalar(state, "MonsterIndex", prior)
        yield "ClassifyNeighbor", dict(tile=tile, floor=floor, index=index, prior_monster=prior), state
    for tile, floor, highest, prior in itertools.product(range(256), (1, 50), (1, 50), (-7, 19)):
        state = baseline(original)
        sethero(state, 16, floor)
        sethero(state, 20, highest)
        sethero(state, 664, 77)
        state["Map"][floor * 123 + 62] = tile
        setscalar(state, "Neighbor", 60)
        setscalar(state, "TileClass", prior)
        yield "ClassifyInteraction", dict(tile=tile, floor=floor, highest=highest, prior_message=prior), state
    positions = [(0, 0), (0, 10), (10, 0), (10, 10), (5, 0), (0, 5), (10, 5), (5, 10), (5, 5)]
    for name, tile in (("FaceUpLanding", 12), ("FaceDownLanding", 11)):
        for mask, (x, y), floor in itertools.product(range(16), positions, (1, 50)):
            state = baseline(original)
            sethero(state, 16, floor)
            sethero(state, 24, x)
            sethero(state, 28, y)
            sethero(state, 352, 91)
            for i, index in enumerate((y * 11 + x - 11, y * 11 + x - 1, y * 11 + x + 1, y * 11 + x + 11)):
                if 0 <= index < 121:
                    state["Map"][floor * 123 + 2 + index] = tile if mask & (1 << i) else 6
            yield name, dict(mask=mask, x=x, y=y, floor=floor), state
    for row, cycle, hit, hp in itertools.product(range(33), (0, 43), (1, 7, 177), (-1, 0, 1, 17, 55)):
        state = baseline(original)
        monster = struct.unpack_from("<4i", state["Monster"], row * 16)
        sethero(state, 636, cycle)
        setscalar(state, "MonsterIndex", row)
        setscalar(state, "RemainingHP", hp)
        setscalar(state, "Strike", 4)
        sethero(state, 4, monster[2] * (cycle + 1) + hit)
        yield "CountHeroStrikes", dict(row=row, cycle=cycle, hit=hit, hp=hp), state
        yield "CountBattleHeroStrikes", dict(row=row, cycle=cycle, hit=hit, hp=hp), state
        # This retains positive double-attack penetration and bounded recursion.
        yield "CountDoubleHeroStrikes", dict(row=row, cycle=cycle, hit=hit, hp=hp), state
        if monster[1] * (cycle + 1) >= hit:
            sethero(state, 8, monster[1] * (cycle + 1) - hit)
            yield "CountEnemyStrikes", dict(row=row, cycle=cycle, hit=hit, hp=hp), state
            yield "CountBattleEnemyStrikes", dict(row=row, cycle=cycle, hit=hit, hp=hp), state
            sethero(state, 0, max(1, hp))
            yield "EnemyFirstDamage", dict(row=row, cycle=cycle, hit=hit, hp=max(1, hp)), state
            yield "DoubleEnemyFirstDamage", dict(row=row, cycle=cycle, hit=hit, hp=max(1, hp)), state
    for tile, flag in itertools.product(range(256), (0, 1, 7)):
        state = baseline(original)
        sethero(state, 464, flag)
        setscalar(state, "Graphic", tile)
        yield "SelectGraphicFrame", dict(tile=tile, time_gate_flag=flag), state
    for row, cycle, defense_delta in itertools.product(range(33), (0, 43), (-7, 0, 7)):
        state = baseline(original)
        monster = struct.unpack_from("<4i", state["Monster"], row * 16)
        sethero(state, 636, cycle)
        sethero(state, 4, monster[2] * (cycle + 1) + max(1, monster[0] * (cycle + 1) // 17))
        sethero(state, 8, monster[1] * (cycle + 1) + defense_delta)
        setscalar(state, "MonsterIndex", row)
        yield "BattleDamage", dict(row=row, cycle=cycle, defense_delta=defense_delta), state
    for name in ("DoorAnimation", "MattockWall", "CrystalLava"):
        for cursor, a, b in itertools.product((0, 7, 400), (0, 60, 120, 0xFFFF), (0, 7, 200, 0xFFFF)):
            state = baseline(original)
            state["EventStack"] = bytearray(random.Random(19).randbytes(SIZES["EventStack"]))
            struct.pack_into("<HHH", state["EventStack"], cursor * 6, 13, a, b)
            setscalar(state, "EventCursor", cursor)
            setscalar(state, "Neighbor", a)
            setscalar(state, "DamageMode", b)
            yield name, dict(cursor=cursor, a=a, b=b), state
    for floor, contact, total, special, cursor in itertools.product((38, 39, 43, 44), (7, 14, 38), (7, 8), (6, 8), (0, 7)):
        state = baseline(original)
        sethero(state, 16, floor)
        setscalar(state, "Contact", contact)
        setscalar(state, "EventCursor", cursor)
        for index in (14, 18, 36, 38, 58, 60, 62):
            state["Map"][39 * 123 + index] = 1
        state["Map"][39 * 123 + 14] += total - 7
        state["Map"][39 * 123 + 16] = special
        state["Map"][39 * 123 + 40] = special
        state["Map"][43 * 123 + 10] = 93 if special == 6 else 94
        yield "CheckSpecialDoors", dict(floor=floor, contact=contact, total=total, special=special, cursor=cursor), state


def accepted_button_comparison(original, candidate, mapping, policy):
    a = instructions(original, 0x42A480, 100)
    b = instructions(candidate, mapping["TButton.CMDialogKey"], 100)
    expected = policy["accepted_differences"][0]["button_dialog_key_operands"]
    changed = []
    normalized_a, _ = normalized(original, a)
    normalized_b, _ = normalized(candidate, b)
    for rule in expected:
        i = next(i for i, ins in enumerate(a) if ins.address - a[0].address == rule["instruction_offset"])
        left, right = a[i], b[i]
        if left.mnemonic != "cmp" or right.mnemonic != "cmp":
            raise ValueError("Accepted IME layout operand is no longer a comparison")
        if left.operands[0].mem.disp != rule["original_displacement"] or right.operands[0].mem.disp != rule["english_displacement"]:
            raise ValueError("Unapproved field displacement change")
        if right.address - b[0].address != rule["instruction_offset"] or left.disp_size != 4 or right.disp_size != 4:
            raise ValueError("Accepted operand location changed")
        patched = bytearray.fromhex(normalized_b[i])
        struct.pack_into("<I", patched, right.disp_offset, rule["original_displacement"])
        normalized_b[i] = patched.hex()
        changed.append(rule)
    # Do not let external-transfer address normalization conceal a changed callee.
    called = {0x41FF20: "KeyDataToShiftState", 0x416C2C: "TWinControl.CanFocus",
              0x402CDC: "@CallDynaInst", 0x4162D4: "TWinControl.CMDialogKey"}
    for left, right in zip(a, b):
        if left.mnemonic == "call":
            name = called[left.operands[0].imm]
            if right.mnemonic != "call" or right.operands[0].imm != mapping[name]:
                raise ValueError("Button framework callee identity changed")
    if normalized_a != normalized_b:
        raise ValueError("Additional button changes beyond the two accepted IME field displacements")
    return dict(passed=True, original_entry="0x0042a480", symbol="TButton.CMDialogKey",
                accepted_operands=changed, external_callee_identities_checked=list(called.values()),
                scope="Two named TButton field operands only; branch bytes and scalar constants retained.")


def compare_native_gates(original, output):
    """Full original gate bodies vs native, streamed-form property outcomes.

    Original setters have explicit observer models. Candidate setters execute
    through the actual English VCL/Windows in FormSmoke. No other call target
    is accepted or skipped in these original routine bodies.
    """
    manifest = json.loads((ROOT / "reference/original/presentation/ui-manifest.json").read_text())
    form = next(f for f in manifest["forms"] if f["class_name"] == "TTSW10")
    fields = {f["name"]: int(f["offset"], 16) for f in form["fields"]}
    machine = emulator(original)
    root = 0x180000
    controls = {name: 0x200000 + i * 0x200 for i, name in enumerate(fields)}
    controls_by_pointer = {p: n for n, p in controls.items()}
    modeled = []
    setters = {0x41353C: ("Enabled", 0x38), 0x413500: ("Visible", 0x37),
               0x410378: ("MenuEnabled", 0x29)}
    def step(u, at, size, _):
        if at in setters:
            pointer = u.reg_read(UC_X86_REG_EAX)
            if pointer not in controls_by_pointer:
                raise ValueError("Original gate setter targets an unknown component")
            value = u.reg_read(UC_X86_REG_EDX) & 0xFF
            if value not in (0, 1):
                raise ValueError("Invalid original property setter Boolean")
            name, offset = setters[at]
            modeled.append([controls_by_pointer[pointer], name, value])
            u.mem_write(pointer + offset, bytes([value]))
            stack = u.reg_read(UC_X86_REG_ESP)
            target = struct.unpack("<I", u.mem_read(stack, 4))[0]
            u.reg_write(UC_X86_REG_ESP, stack + 4)
            u.reg_write(UC_X86_REG_EIP, target)
        elif bytes(u.mem_read(at, 1)) == b"\xE8":
            target = at + 5 + struct.unpack("<i", u.mem_read(at + 1, 4))[0]
            if target not in setters:
                raise ValueError(f"Unmodeled call in original modal gate: {target:#x}")
    machine.hook_add(unicorn.UC_HOOK_CODE, step)
    names = ["BitBtn1", "BitBtn2", "BitBtn3", "BitBtn4", "Image4", "Image5", "Image6", "Image7",
             "Image8", "Image9", "Image10", "Image11", "Image12", "Image13", "Image14", "Image15",
             "Image16", "Image17", "Image18"]
    menus = ["HighScore1", "GameLoad1", "GameSave1", "Option1"]
    def snapshot():
        return "".join(str(machine.mem_read(controls[n] + offset, 1)[0])
                       for n in names for offset in (0x38, 0x37)) + \
               "".join(str(machine.mem_read(controls[n] + 0x29, 1)[0]) for n in menus) + \
               str(machine.mem_read(root + 0x118, 1)[0]) + \
               str(int(struct.unpack("<H", machine.mem_read(0x48C5CA, 2))[0] != 0))
    rows = [json.loads(s) for s in output.splitlines() if s.strip().startswith("{")]
    observed = [r for r in rows if "gate_case" in r]
    if len(observed) != 384 or len({tuple(r["gate_case"]) for r in observed}) != 384:
        raise ValueError("Incomplete native modal-gate fixture set")
    checks = []
    for native in observed:
        orb, mouse, keyboard, ending, mask = native["gate_case"]
        if not (orb in range(3) and mouse in range(2) and keyboard in range(2) and ending in range(2) and mask in range(16)):
            raise ValueError("Unreviewed native gate scenario")
        machine.mem_write(root, bytes(0x500))
        machine.mem_write(0x48C510, struct.pack("<I", root))
        machine.mem_write(0x4B8688, bytes(684))
        for name, offset in fields.items():
            machine.mem_write(root + offset, struct.pack("<I", controls[name]))
            machine.mem_write(controls[name], bytes(0x200))
            machine.mem_write(controls[name] + 0x37, b"\x01\x01")
            machine.mem_write(controls[name] + 0x29, b"\x01")
        for name, value, offset in (("MouseControl1", mouse, 0x28), ("KeyboardControl1", keyboard, 0x28), ("Timer4", ending, 0x20)):
            machine.mem_write(controls[name] + offset, bytes([value]))
        inventory = native["inventory"]
        seed = native["seed"]
        if len(inventory) != 15 or inventory[0] != orb or any(v not in (0, 1, 2, 3, 6) for v in inventory):
            raise ValueError("Unreviewed native inventory values")
        if len(seed) != 44 or set(seed) - {"0", "1"}:
            raise ValueError("Unreviewed native control seed")
        for i, value in enumerate(inventory):
            machine.mem_write(0x4B8688 + 68 + i * 4, struct.pack("<I", value))
        for i, name in enumerate(names):
            machine.mem_write(controls[name] + 0x38, bytes([int(seed[i * 2])]))
            machine.mem_write(controls[name] + 0x37, bytes([int(seed[i * 2 + 1])]))
        for i, name in enumerate(menus):
            machine.mem_write(controls[name] + 0x29, bytes([int(seed[38 + i])]))
        machine.mem_write(root + 0x118, bytes([int(seed[42])]))
        machine.mem_write(0x48C5CA, struct.pack("<H", int(seed[43])))
        modeled.clear()
        execute(machine, 0x450758, eax=root)
        disabled = snapshot()
        execute(machine, 0x450880, eax=root)
        restored = snapshot()
        checks.append(dict(inputs=native["gate_case"], inventory=inventory, seed=seed,
                           original_disabled=disabled, native_disabled=native["disabled"],
                           original_restored=restored, native_restored=native["restored"],
                           original_modeled_setters=list(modeled),
                           passed=disabled == native["disabled"] and restored == native["restored"]))
    return dict(cases=checks, comparisons=len(checks), passed=all(c["passed"] for c in checks),
                controls_in_bit_order=names, menus_in_bit_order=menus,
                final_bits=["KeyPreview", "InputEnabled"],
                boundary="Only original Enabled/Visible/MenuEnabled setters are modeled. Candidate executes native VCL setters. Notifications/focus/timer delivery are not measured.")


def verify_form_resources(candidate, records):
    verified = []
    for record in records:
        found = [language.data.struct for kind in candidate.DIRECTORY_ENTRY_RESOURCE.entries if kind.id == 10
                 for name in kind.directory.entries if str(name.name) == record["name"]
                 for language in name.directory.entries if language.id == record["language"]]
        if len(found) != 1:
            raise ValueError("Missing/ambiguous original form resource")
        raw = candidate.get_data(found[0].OffsetToData, found[0].Size)
        if hashlib.sha256(raw).hexdigest() != record["sha256"]:
            raise ValueError("Original form resource changed")
        verified.append({**record, "byte_identical": True})
    return verified


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--check", action="store_true")
    args = parser.parse_args()
    original_path = ROOT / "build/research/TSW.exe"
    if digest(original_path) != ORIGINAL_HASH:
        raise ValueError("Original executable differs from pin")
    original = pefile.PE(str(original_path))
    build = json.loads((WORK / "build-report.json").read_text())
    # Validate staged source and compiled binaries before accepting observations.
    for record in build["inputs"]:
        source = ROOT / record["source"]
        staged = WORK / source.relative_to(ROOT / "delphi")
        if digest(source) != record["source_sha256"] or digest(staged) != record["staged_sha256"]:
            raise ValueError("Build source changed: " + record["source"])
    for record in build["builds"].values():
        artifact = ROOT / record["artifact"]
        if digest(artifact) != record["artifact_sha256"] or digest(artifact.with_suffix(".map")) != record["map_sha256"]:
            raise ValueError("Compiled artifact changed")
    policy_path = ROOT / "delphi/comparison-policy.json"
    policy = json.loads(policy_path.read_text())
    main_pe = pefile.PE(str(WORK / "game/Tower.exe"))
    main_symbols = symbols(main_pe, WORK / "game/Tower.map")
    runtime = accepted_button_comparison(original, main_pe, main_symbols, policy)
    original_framework = framework_cases(original, {**RUNTIME, "TButton.Click": 0x42A370})
    compiled_framework = framework_cases(main_pe, main_symbols)
    if original_framework != compiled_framework or not all(c["passed"] for c in original_framework):
        raise ValueError("Linked framework fixture mismatch")
    native_output = build["builds"]["smoke"].get("native_output")
    if not native_output or build["builds"]["smoke"].get("native_exit") != 0:
        raise ValueError("Run build_delphi_game.py --smoke before comparing native forms")
    native_log = WORK / "smoke/native.log"
    if digest(native_log) != build["builds"]["smoke"]["native_log_sha256"] or native_log.read_bytes().decode("cp1252") != native_output:
        raise ValueError("Native observations differ from the retained execution log")
    native_rows = [json.loads(s) for s in native_output.splitlines() if s.strip().startswith("{")]
    summaries = [r for r in native_rows if "serialized_bindings_verified" in r]
    if len(summaries) != 1 or any(summaries[0].get(k) != v for k, v in
                               dict(serialized_bindings_verified=130, published_fields_verified=279,
                                    published_methods_verified=230, modal_gate_cases=384, passed=True).items()):
        raise ValueError("Incomplete native form/binding validation")
    gates = compare_native_gates(original, native_output)
    records = verify_form_resources(main_pe, build["original_form_resources"])
    content_records = verify_form_resources(main_pe, build["original_content_resources"])
    runners = {"original": Runner(original, ENTRIES, STORAGE)}
    byte_matches = {}
    for name in ("emulator", "core-probe"):
        candidate = pefile.PE(str(ROOT / build["builds"][name]["artifact"]))
        entry = exports(candidate)
        storage = locations(candidate, entry)
        if name == "emulator" and storage != STORAGE:
            raise ValueError("Original-address probe layout changed")
        runners[name] = Runner(candidate, {k: entry[k] for k in ENTRIES}, storage)
        byte_matches[name] = candidate.get_data(entry["ClassifyNeighbor"] - candidate.OPTIONAL_HEADER.ImageBase, 282) == original.get_data(0x451C20 - original.OPTIONAL_HEADER.ImageBase, 282)
    counts = {k: 0 for k in ENTRIES}
    disagreements = []
    trace_differences = {k: 0 for k in ENTRIES}
    evidence = hashlib.sha256()
    for name, inputs, state in cases(original):
        old, old_calls, old_writes, old_effects = runners["original"].run(name, state)
        for variant in ("emulator", "core-probe"):
            new, new_calls, new_writes, new_effects = runners[variant].run(name, state)
            same = old == new and old_effects == new_effects
            if not same:
                disagreements.append(dict(method=name, inputs=inputs, variant=variant,
                    state_differences=[k for k in old if old[k] != new[k]],
                    original_calls=old_calls, candidate_calls=new_calls,
                    ordered_writes_match=old_writes == new_writes,
                    interleaved_effects_match=old_effects == new_effects))
            if old_writes != new_writes:
                trace_differences[name] += 1
            evidence.update(json.dumps([name, inputs, variant, same], sort_keys=True).encode())
            evidence.update(b"".join(old[k] for k in sorted(old)))
            evidence.update(b"".join(new[k] for k in sorted(new)))
            evidence.update(json.dumps([old_effects, new_effects]).encode())
        counts[name] += 1
        if counts[name] == 1:
            print("Comparing", name, flush=True)
    inventory = json.loads((ROOT / "build/delphi-game/reports/method-inventory.json").read_text())
    report = dict(schema_version=1, original_sha256=ORIGINAL_HASH, policy_sha256=digest(policy_path),
                  build_report_sha256=digest(WORK / "build-report.json"), resources=records,
                  content_resources=content_records,
                  accepted_ime_button_comparison=runtime, fixtures_per_variant=counts,
                  linked_framework_fixture_comparisons=dict(comparisons=len(original_framework),
                      passed=True, original=original_framework, compiled=compiled_framework,
                      boundary="Synthetic object/message trees; only Windows GetKeyState and observer event are modeled. No framework call is skipped."),
                  compared_variants=["original-addresses", "production-storage"],
                  comparisons=sum(counts.values()) * 2, state_and_core_call_effects_passed=not disagreements,
                  ordered_interleaved_state_effects_passed=not disagreements,
                  disagreements=disagreements[:100], disagreement_count=len(disagreements),
                  ordered_cpu_write_trace_differences=trace_differences,
                  fixture_transcript_sha256=evidence.hexdigest(), classify_neighbor_literal_bytes_match=byte_matches,
                  native_smoke=[r for r in native_rows if "gate_case" not in r],
                  native_modal_gate_comparisons=gates,
                  published_methods=len(inventory["methods"]),
                  explicit_unrecovered_methods=sum(m["status"].startswith("unrecovered") for m in inventory["methods"]),
                  full_game_recovered=False, pixel_equivalence_established=False,
                  queue_records_compared=512,
                  limits=["Fixtures establish final recovered-state bytes, a 512-record event prefix and transitive core entry sequences, not whole-game input reachability.",
                          "Only ClassifyNeighbor has literal byte correspondence. All measured state-write addresses, sizes, values and their ordering must agree; instruction correspondence for other routines remains unestablished.",
                          "Strike fixtures use positive penetration and bounded recursion; nonterminating original inputs are outside this measured domain.",
                          "Original Delphi resources are exact; native form streaming is validated on this host without activating the game.",
                          "IME is an authorized exception; other library and unrecovered gameplay differences are not accepted."])
    target = ROOT / "build/delphi-game/reports/comparison-report.json"
    content = json.dumps(report, indent=2) + "\n"
    if args.check:
        if target.read_text(encoding="utf-8") != content:
            raise ValueError("Stale Delphi game comparison report")
    else:
        target.parent.mkdir(parents=True, exist_ok=True)
        target.write_text(content, encoding="utf-8")
    print("Core comparisons", report["comparisons"], "disagreements", len(disagreements), flush=True)
    print("Native modal gates", gates["comparisons"], "passed", gates["passed"], flush=True)
    if disagreements:
        print(json.dumps(disagreements[:5], indent=2))
        raise SystemExit("Delphi core comparisons failed")
    if not gates["passed"]:
        print(json.dumps([c for c in gates["cases"] if not c["passed"]][:3], indent=2))
        raise SystemExit("Native modal-gate comparisons failed")


if __name__ == "__main__":
    main()
