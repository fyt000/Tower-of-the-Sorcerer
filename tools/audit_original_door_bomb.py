"""Probe keyed-door and Bomb branches in the installed TSW v1.2 x86.

Readable recovery is in delphi/src, with generated evidence under
build/research/decompilation. No C++ executable is built.
The original is read only. Only verified gameplay helpers are followed;
skipped UI/RTL calls remain in the evidence. Reports supply original-derived
oracles for regression checks, independent of the campaign translation.
"""
import hashlib
import json
import struct

from original_event_probe import RAW, ROOT, md, pe, probe
from unicorn.x86_const import UC_X86_REG_EBX, UC_X86_REG_ESI

EXE_HASH = '41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779'
CLOCK = [12, 14, 16, 34, 36, 38, 56, 58, 60]
IMAGE = pe.get_memory_mapped_image()


def initial_tiles(floor):
    return list(RAW[floor * 123 + 2:(floor + 1) * 123])


def changes(floor, tiles):
    return [(floor, i % 11, i // 11, tile) for i, tile in enumerate(tiles)]


def door_result(floor, target, keys, tiles, operation='door'):
    p = probe(0x444490 if operation == 'door' else 0x47beac, floor,
              changes=changes(floor, tiles), include_presentation=True,
              globals=[(0x48c584, target), *zip([0x4b86a8, 0x4b86ac, 0x4b86b0], keys)],
              follow_calls=[0x47beac, 0x4660d0], watch_globals=[0x48c584])
    assert p['direct_map_writes'] == []
    result = {'keys': p['stat_slots'][8:11], 'gold': p['stat_slots'][3],
              'bomb': 0, 'target': p['watched_globals']['0x48c584'], 'queue': p['queue']}
    return result, p['calls']


def bomb_result(x, y, tiles, cycle=0, lucky=0):
    p = probe(0x450f31, 1, x, y, changes=changes(1, tiles), end=0x45112c,
              globals=[(0x4b8694, 1000), (0x4b86e4, 1), (0x4b8904, cycle), (0x4b8704, lucky)],
              registers=[(UC_X86_REG_ESI, 0x200000), (UC_X86_REG_EBX, 0x48c5ac)],
              follow_calls=[0x451c20, 0x44bc34], include_presentation=True,
              watch_globals=[0x4b86e4, 0x48c584])
    assert p['direct_map_writes'] == []
    result = {'keys': p['stat_slots'][8:11], 'gold': p['stat_slots'][3],
              'bomb': p['watched_globals']['0x4b86e4'],
              'target': p['watched_globals']['0x48c584'], 'queue': p['queue']}
    return result, p['calls']


def main():
    assert hashlib.sha256(pe.__data__).hexdigest() == EXE_HASH, 'Review addresses for a different image'
    labels, skipped = [], set()

    def collect(label, scenario):
        result, calls = scenario
        labels.append(label)
        skipped.update(calls)
        return result

    classifier = []
    for tile in range(256):
        p = probe(0x451c20, 1, changes=[(1, 5, 4, tile)],
                  globals=[(0x48c55c, 49), (0x48c5b8, 999)], watch_globals=[0x48c58c, 0x48c5b8])
        result = {'kind': p['watched_globals']['0x48c58c'],
                  'monster_index': p['watched_globals']['0x48c5b8']}
        collect(f'classifier tile {tile}', (result, p['calls']))
        eligible = any(first <= tile <= last for first, last in [(61, 90), (93, 96), (133, 144), (147, 158)])
        kind = 2 if eligible else 1 if tile == 8 else 3 if tile == 13 else 0
        assert result['kind'] == kind
        index = (tile - 61) // 2 if tile < 97 else 20 + (tile - 133) // 2
        assert result['monster_index'] == (index if eligible else 999)
        classifier.append({'tile': tile, **result})

    # Enumerate all 256 open/closed patterns of the other eight clock cells
    # for each still-closed hand, including malformed partial puzzle states.
    patterns = 0
    for target in [14, 38]:
        others = [i for i in CLOCK if i != target]
        for mask in range(256):
            tiles = initial_tiles(39)
            for bit, index in enumerate(others):
                tiles[index] = 6 if mask & (1 << bit) else 1
            for yellow in [0, 1, 2]:
                result = collect(f'clock target {target} mask {mask} keys {yellow}',
                                 door_result(39, target, [yellow, 0, 0], tiles))
                other = 38 if target == 14 else 14
                reveals = tiles[other] == 6 and all(tiles[i] == 1 for i in CLOCK if i not in [14, 38])
                assert ([6, 36, 43] in result['queue']) == reveals
                assert result['keys'][0] == max(0, yellow - 1)
                patterns += 1

    # Small original-derived oracles for regression checks.
    clock_cases = []
    for target, other in [(14, 38), (38, 14)]:
        for yellow in [0, 1, 2]:
            for opened in [[], [other], [12, other], [12]]:
                for center in [1, 6, 43]:
                    tiles = initial_tiles(39)
                    for index in opened:
                        tiles[index] = 6
                    tiles[36] = center
                    result = collect(f'clock regression {target}/{yellow}/{opened}/{center}',
                                     door_result(39, target, [yellow, 0, 0], tiles))
                    clock_cases.append({'target': target, 'yellow_keys': yellow,
                                        'opened_indices': opened, 'center_tile': center,
                                        'yellow_keys_after': result['keys'][0],
                                        'reveals_staff': [6, 36, 43] in result['queue']})
    examples = []
    for target, other in [(14, 38), (38, 14)]:
        tiles = initial_tiles(39)
        tiles[other] = 6
        for yellow in [0, 1]:
            result = collect('39F key-saving example', door_result(39, target, [yellow, 0, 0], tiles))
            examples.append({'target': target, 'other_open_door': other,
                             'yellow_keys_before': yellow, **result})

    # All keyed-door branches plus off-floor and 43F doorcheck branches.
    door_branches = 0
    for floor in [1, 39, 43]:
        for target in [7, 14, 38, 60]:
            for tile, slot in [(1, 0), (2, 2), (3, 1)]:
                for keys_available in [0, 1, 2]:
                    tiles = initial_tiles(floor)
                    tiles[target] = tile
                    keys = [0, 0, 0]
                    keys[slot] = keys_available
                    collect(f'keyed door F{floor} target {target} color {tile} keys {keys_available}',
                            door_result(floor, target, keys, tiles))
                    door_branches += 1
    trap = []
    for guardian in [6, 93]:
        for yellow in [0, 1]:
            tiles = initial_tiles(43)
            tiles[8] = guardian
            result = collect('43F doorcheck', door_result(43, 7, [yellow, 0, 0], tiles))
            trap.append({'guardian_tile': guardian, 'yellow_keys_before': yellow, **result})
    # Preserve the literal numeric-sum predicate in the C++ reconstruction.
    # These balanced non-door values are synthetic, not a reachable route.
    tiles = initial_tiles(39)
    tiles[38], tiles[12], tiles[16] = 6, 0, 2
    collect('synthetic clock sum predicate', door_result(39, 14, [0, 0, 0], tiles))

    for tile in range(256):
        tiles = [6] * 121
        tiles[49] = tile       # north neighbor
        tiles[72] = 61         # diagonal control: never bombed
        result = collect(f'Bomb tile {tile}', bomb_result(5, 5, tiles))
        removed = [q[1] for q in result['queue'] if q[0] == 17]
        allowed = classifier[tile]['kind'] == 2
        assert removed == ([49] if allowed else [])
        reward = struct.unpack_from('<I', IMAGE, 0x48991c - 0x400000 + classifier[tile]['monster_index'] * 16)[0] if allowed else 0
        assert result['gold'] == 1000 + reward and result['bomb'] == 0
    edge_cases = []
    for y in range(11):
        for x in range(11):
            tiles = [61] * 121
            tiles[y * 11 + x] = 6
            result = collect(f'Bomb coordinate {x},{y}', bomb_result(x, y, tiles))
            removals = [q[1] for q in result['queue'] if q[0] == 17]
            expected = [ny * 11 + nx for nx, ny in [(x, y - 1), (x - 1, y), (x + 1, y), (x, y + 1)]
                        if 0 <= nx < 11 and 0 <= ny < 11]
            assert removals == expected and result['gold'] == 1000 + len(removals)
            edge_cases.append({'x': x, 'y': y, 'removed_indices': removals,
                               'gold_after': result['gold']})
    multi = []
    for cycle in [0, 43]:
        for lucky in [0, 1]:
            tiles = [6] * 121
            for index, tile in [(49, 95), (59, 145), (61, 91), (71, 133), (72, 61)]:
                tiles[index] = tile
            result = collect('Bomb mixed immune/susceptible reward flags',
                             bomb_result(5, 5, tiles, cycle, lucky))
            multi.append({'cycle_factor_minus_one': cycle, 'lucky_gold': lucky, **result})

    assert all(case['gold'] == multi[0]['gold'] and case['bomb'] == 0 for case in multi)
    assert [q[1] for q in multi[0]['queue'] if q[0] == 17] == [49, 71]

    # Assert integration with the authored campaign in addition to builders.
    campaign = json.loads((ROOT / 'data/campaign.json').read_text(encoding='utf-8'))
    for index in [14, 38]:
        event = next(e for e in campaign['events'] if e['id'] == f'floor_39_clock_door_{index}')
        assert event['trigger']['type'] == 'door_attempted'
    ranges = [[61, 90], [93, 96], [133, 144], [147, 158]]
    assert campaign['rules'].get('bomb_tile_ranges', ranges) == ranges
    armed = probe(0x444490, 43, changes=[(43, 7, 0, 7)], globals=[(0x48c584, 7)],
                  follow_calls=[0x46397c, 0x46cb1c, 0x4660d0], include_presentation=True)
    assert '0x46cb1c' in armed['followed_calls']

    ranges = [(0x4445d3, 0x4447c5), (0x47beac, 0x47c20b),
              (0x450f31, 0x45112c), (0x451c20, 0x451d3a)]
    report = {
        'executable_sha256': EXE_HASH,
        'reference_sources': ['build/research/decompilation/decompiled/0047beac_doorcheck.c',
                              'build/research/decompilation/decompiled/00450bc5_use_selected_item.c'],
        'executable_probe_scenarios': len(labels),
        'entry_paths': {
            'keyed_doors': {'dispatch': '0x444490', 'key_decision': '0x444601..0x44468B',
                            'doorcheck_call': '0x44468F', 'open_refusal_branch': '0x444694'},
            'bomb': {'item_dispatch_case': '0x450F31', 'classifier': '0x451C20',
                     'dissolve_builder': '0x44BC34', 'consumption': '0x451127',
                     'postcombat_queue': [11, 5, 0], 'postcombat_dispatch_call': '0x4533EB'},
        },
        'clock_pattern_scenarios': patterns, 'other_keyed_door_scenarios': door_branches,
        'floor_39_examples': examples, 'clock_runtime_cases': clock_cases,
        'floor_43_doorcheck_cases': trap,
        'floor_43_armed_road_entry': {'followed_calls': armed['followed_calls'],
                                     'skipped_calls': armed['calls'], 'queue_records': len(armed['queue'])},
        'tile_classifier': classifier, 'bomb_tile_scenarios': 256,
        'bomb_coordinate_cases': edge_cases, 'bomb_mixed_reward_cases': multi,
        'skipped_calls': sorted(skipped),
        'disassembly': {f'{start:#x}..{end:#x}':
                        [f'{i.address:#x}: {i.mnemonic} {i.op_str}' for i in
                         md.disasm(IMAGE[start - 0x400000:end - 0x400000], start)]
                        for start, end in ranges},
        'limits': [
            'Reference covers keyed doors/doorcheck and Bomb/classifier/dissolve records, not the complete game.',
            'Door/Bomb builders enqueue map changes; probes stop before the timer consumes them.',
            'UI controls, localized status-string construction and pixels are omitted; skipped calls are listed.',
            'Clock pattern sweep uses original door/road states; the numeric-sum counterexample is separately retained in the reference.',
            'These original-derived cases cover keyed doors, active items and event presentation; runtime regression checks are separate.',
            'A complete callback/branch inventory, fairy scoring, exact ending artwork and full natural tower routes remain future work.',
        ],
    }
    (ROOT / 'data/original-door-bomb-audit.json').write_text(
        json.dumps(report, ensure_ascii=False, indent=2) + '\n', encoding='utf-8', newline='\n')
    print(f'Verified {len(labels)} executable scenarios: {patterns} clock patterns, '
          f'{door_branches} other door branches, all 256 classifiers/Bomb inputs and 121 Bomb coordinates')


if __name__ == '__main__':
    main()
