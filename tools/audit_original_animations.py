"""Reproduce animation and hidden-trigger checks without launching TSW.exe.

Only the isolated x86 queue helper doorstackin is followed. Delphi graphics,
audio and GUI calls are skipped and reported. Frame order, mode, tile writes
and trigger predicates are evidence; portable wall-clock durations are not.
"""
import hashlib
import json
import struct
from collections import Counter

import unicorn
from unicorn.x86_const import UC_X86_REG_ESP, UC_X86_REG_EAX, UC_X86_REG_EDX, UC_X86_REG_ECX, UC_X86_REG_EIP

from original_animation import TILE_TRANSITIONS
from original_event_probe import ROOT, RAW, pe, md, probe

EXPECTED_SHA256 = '41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779'


def ambient_offset(tile):
    u = unicorn.Uc(unicorn.UC_ARCH_X86, unicorn.UC_MODE_32)
    u.mem_map(0x400000, 0x300000)
    u.mem_write(0x400000, pe.get_memory_mapped_image())
    u.mem_write(0x48c5a8, struct.pack('<I', tile))
    u.reg_write(UC_X86_REG_ESP, 0x6ff000)
    u.mem_write(0x6ff000, struct.pack('<I', 0x6ffff0))
    u.emu_start(0x454c10, 0x6ffff0, count=1000)
    return struct.unpack('<I', u.mem_read(0x48c554, 4))[0]


def copy_rectangles(mode):
    """Record copy arguments; emulate only Delphi's four-coordinate Rect value.

    At a CALL instruction, EAX/EDX/ECX carry left/top/right and the two
    stack arguments carry the result pointer and bottom. No raster calls run.
    The controlled case uses a 40px square and frame 8 without large-mode
    adjustment, making vertical movement and lava direction distinguishable.
    """
    u = unicorn.Uc(unicorn.UC_ARCH_X86, unicorn.UC_MODE_32)
    u.mem_map(0, 0x300000)
    u.mem_map(0x400000, 0x300000)
    u.mem_write(0x400000, pe.get_memory_mapped_image())
    u.reg_write(UC_X86_REG_EAX, 0x200000)
    u.reg_write(UC_X86_REG_ESP, 0x6ff000)
    for address, value in [(0x200254, 0x201000), (0x20102c, 40), (0x201030, 40),
        (0x48c5ac, 1), (0x48c752, 60 * 65536 + 13), (0x48c756, mode),
        (0x48c750, 8), (0x4b8698, 1)]:
        u.mem_write(address, struct.pack('<I', value))
    copies = []

    def hook(uc, pc, size, _):
        if pc == 0x478f03:
            uc.emu_stop()
            return
        instruction = next(md.disasm(bytes(uc.mem_read(pc, size)), pc))
        if instruction.mnemonic != 'call':
            return
        esp = uc.reg_read(UC_X86_REG_ESP)
        if instruction.op_str == '0x40923c':
            destination, bottom = struct.unpack('<II', uc.mem_read(esp, 8))
            rect = [uc.reg_read(register) for register in
                    [UC_X86_REG_EAX, UC_X86_REG_EDX, UC_X86_REG_ECX]] + [bottom]
            uc.mem_write(destination, struct.pack('<4I', *rect))
            uc.reg_write(UC_X86_REG_ESP, esp + 8)
        elif instruction.op_str == '0x41a530':
            destination = uc.reg_read(UC_X86_REG_EDX)
            source = struct.unpack('<I', uc.mem_read(esp, 4))[0]
            copies.append({'source': list(struct.unpack('<4i', uc.mem_read(source, 16))),
                           'destination': list(struct.unpack('<4i', uc.mem_read(destination, 16)))})
            uc.reg_write(UC_X86_REG_ESP, esp + 4)
        elif instruction.op_str == '0x417e44':
            uc.reg_write(UC_X86_REG_ESP, esp + 8)
        uc.reg_write(UC_X86_REG_EIP, pc + size)

    u.hook_add(unicorn.UC_HOOK_CODE, hook)
    u.emu_start(0x4770e0, 0x478f03, count=5000)
    return copies


def main():
    digest = hashlib.sha256(pe.__data__).hexdigest()
    assert digest == EXPECTED_SHA256, 'Review addresses for this executable first'
    events = json.loads((ROOT / 'data/events.json').read_text(encoding='utf-8'))
    campaign = json.loads((ROOT / 'data/campaign.json').read_text(encoding='utf-8'))
    assert campaign['events'] == events, 'Regenerated events have not been integrated'

    altar = {str(tile): ambient_offset(tile) for tile in range(15, 19)}
    assert altar == {'15': 0, '16': 2, '17': 0, '18': 0}
    modes = []
    for mode, (style, result_tile) in TILE_TRANSITIONS.items():
        # Queue slot one: opcode 13, cell 60, mode. The preceding operand
        # carries frame 16. Stop before the GUI routine's stack cleanup.
        result = probe(0x4770e0, 1, changes=[(1, 5, 5, 99)], end=0x478f03,
            globals=[(0x48c5ac, 1), (0x48c752, 60 * 65536 + 13),
                     (0x48c756, mode), (0x48c750, 16)], include_presentation=True)
        assert [1, 5, 5, result_tile] in [list(v) for v in result['changed']], (mode, result)
        modes.append({'mode': mode, 'style': style, 'result_tile': result_tile,
                      'copy_rectangles_at_frame_8_with_40px_tile': copy_rectangles(mode),
                      'called_helpers_not_executed': result['calls']})

    expected = {7: [0, 16, 40, 40], 8: [0, 24, 40, 40], 9: [24, 0, 40, 40],
                10: [0, 0, 16, 40], 11: [0, 0, 40, 16], 12: [0, 24, 40, 40]}
    for mode, destination in expected.items():
        assert modes[mode - 1]['copy_rectangles_at_frame_8_with_40px_tile'][0]['destination'] == destination

    mattock = probe(0x451b98, 1, globals=[(0x48c55c, 60)], end=0x451c1c,
        include_presentation=True, follow_calls=[0x4660d0])
    frames = [q[2] for q in mattock['queue'] if q[0] == 0 and q[2] != 0]
    assert frames == list(range(1, 17))
    assert [q for q in mattock['queue'] if q[0] == 13] == [[13, 60, 7]] * 16
    bomb = probe(0x44bc34, 1, 5, 5, changes=[(1, 5, 5, 61)], include_presentation=True)
    assert [q[2] for q in bomb['queue'] if q[0] == 9] == [166, 170, 174, 178, 182]
    assert [q for q in bomb['queue'] if q[0] == 1] == [[1, 1, 0]] * 5
    magic = probe(0x44c464, 1, 5, 5, globals=[(0x48c558, 60), (0x4b87e8, 4)],
                  include_presentation=True)
    assert [9, 60, 216] in magic['queue'] and [0, 6, 215] in magic['queue']

    floors = []
    walls = []
    for floor in range(51):
        baseline = probe(0x4664e4, floor, include_presentation=True)
        guards = sorted(set((f, x, y) for f, x, y, tile in baseline['reads'] if 61 <= tile <= 158))
        cleared = probe(0x4664e4, floor, changes=[(f, x, y, 6) for f, x, y in guards],
                        include_presentation=True)
        queued_modes = sorted(set((q[1], q[2]) for q in cleared['queue'] if q[0] == 13))
        if guards:
            configured = [e for e in events if (e['trigger']['type'] == 'enemy_defeated'
                          or floor == 40 and e['trigger']['type'] == 'step')
                          and e['trigger'].get('floor') == floor]
            assert configured, ('Missing post-combat floor', floor)
            configured_targets = {(fx['y'] * 11 + fx['x'], fx.get('original_mode'))
                for e in configured for fx in e['effects']
                if fx['type'] == 'cinematic' and fx.get('kind') == 'tile_reveal'}
            # F49's two gate writes use the shared automatic gate transition.
            automatic_targets = {(fx['y'] * 11 + fx['x'], 4)
                for e in configured for fx in e['effects'] if fx['type'] == 'set_tile'
                and fx['tile'] == 6 and RAW[floor * 123 + 2 + fx['y'] * 11 + fx['x']] == 4}
            assert set(queued_modes) <= configured_targets | automatic_targets, (floor, queued_modes)
            floors.append({'floor': floor, 'guard_cells_read': [list(g) for g in guards],
                           'tile_modes': [list(q) for q in queued_modes],
                           'configured_events': [e['id'] for e in configured]})
        for index, tile in enumerate(RAW[floor * 123 + 2:(floor + 1) * 123]):
            if tile != 10:
                continue
            result = probe(0x444490, floor, index % 11, index // 11, end=0x448fbc,
                           include_presentation=True)
            matches = [e['id'] for e in events if e['trigger']['type'] == 'bump'
                and e['trigger'].get('floor') == floor and e['trigger'].get('x') == index % 11
                and e['trigger'].get('y') == index // 11]
            if result['queue'] or result['changed']:
                assert matches, ('Missing scripted wall', floor, index)
            walls.append({'floor': floor, 'cell': index, 'queue': result['queue'],
                          'configured_events': matches})

    hidden_reveals = []
    for floor, index, other, address, event_id, target in [
        (41, 20, 12, 0x444490, 'floor_41_reveal_hidden_magician', 151),
        (39, 14, 38, 0x47beac, 'floor_39_clock_door_14', 43),
        (39, 38, 14, 0x47beac, 'floor_39_clock_door_38', 43),
    ]:
        result = probe(address, floor, index % 11, index // 11,
            changes=[(floor, other % 11, other // 11, 6)],
            end=0x448fbc if address == 0x444490 else 0x6ffff0,
            include_presentation=True, globals=[(0x48c554, 1)])
        assert [1, 2, 0] in result['queue']
        event = next(e for e in events if e['id'] == event_id)
        assert any(fx['type'] == 'sound' and fx['cue'] == 'get' for fx in event['effects'])
        assert any(fx['type'] == 'set_tile' and fx['tile'] == target for fx in event['effects'])
        hidden_reveals.append({'event': event_id, 'builder': hex(address), 'queue': result['queue']})

    report = {'source': 'Read-only installed English TSW.exe v1.2', 'executable_sha256': digest,
        'ambient_builder': '0x454c10', 'altar_offsets': altar,
        'tile_renderer': '0x4770e0..0x478f03', 'tile_modes': modes,
        'frame_builder': '0x4660d0', 'mattock_queue': mattock['queue'],
        'followed_queue_helpers': mattock['followed_calls'],
        'bomb_builder': '0x44bc34', 'bomb_queue': bomb['queue'],
        'field_damage_builder': '0x44c464', 'field_damage_queue': magic['queue'],
        'floors_checked': 51, 'postcombat_guard_branches': floors, 'scripted_walls': walls,
        'conditional_hidden_reveals': hidden_reveals,
        'initialized_secret_wall_count': Counter(RAW[f * 123 + 2 + i] for f in range(51) for i in range(121))[9],
        'boundaries': [
            'The original leaves combat replacement images installed between strikes; the requested pulse intentionally clears each impact before the next strike.',
            'Queue helpers are followed only when explicitly whitelisted; Delphi rendering, audio and GUI calls remain skipped.',
            'Initialized-map checks plus existing staged boss/event probes do not enumerate every reachable campaign state.',
            'Original timer scheduling, fairy rank/score and the complete ending raster composition are not reproduced by this audit.']}
    (ROOT / 'data/original-animation-audit.json').write_text(
        json.dumps(report, ensure_ascii=False, indent=2) + '\n', encoding='utf-8', newline='\n')
    print(f'Checked 12 tile modes, altar eyes, 16 wall frames, Bomb/magic queues, 51 postcombat floors and {len(walls)} scripted-wall sites')


if __name__ == '__main__':
    main()
