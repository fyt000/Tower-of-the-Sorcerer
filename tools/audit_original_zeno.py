"""Verify the shared Zeno row across seal, portal, contact and event order.

Hash-pinned, read-only original executable. Each handler receives the previous
handler's stat/flag writes; drawing and combat are skipped and disclosed.
Readable game logic is in cpp/src/scenes.cpp and cpp/src/contact.cpp. These branch
observations provide evidence for item and floor-event regression checks.
"""
import hashlib
import json

from original_event_probe import ROOT, pe, md, probe

EXE_HASH = '41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779'
WATCH = [0x489a00, 0x489a04, 0x489a08, 0x4b88f8]


def handler(operation, cycle, stats, sealed, valid_pattern=True):
    values = [*zip(WATCH, [*stats, sealed]),
              (0x4b8904, 0 if cycle == 1 else 43), (0x4b8908, int(cycle >= 3))]
    if operation in ['seal', 'decoy_defeated']:
        cells = [(49, i % 11, i // 11, 6) for i in [16, 26, 28, 38]]
        cells += [(49, i % 11, i // 11, 93) for i in [15, 17, 37, 39]]
        cells += [(49, 5, 2, 6 if operation == 'decoy_defeated' else 91),
                  (49, 5, 6, 4), (49, 5, 5, 6)]
        if not valid_pattern:
            cells.append((49, 5, 1, 93))
        p = probe(0x4664e4, 49, changes=cells, globals=values, watch_globals=WATCH)
        if operation == 'decoy_defeated':
            assert all([6, i, 6] in p['queue'] for i in [15, 17, 37, 39])
            assert [10, 46, 0] not in p['queue'], 'Reward builder replaces the seal speech queue'
    elif operation == 'portal':
        p = probe(0x46cb1c, 24, 5, 0, globals=values, watch_globals=WATCH)
    else:
        p = probe(0x444490, 50, 5, 5, changes=[(50, 5, 4, 91)],
                  globals=[*values, (0x48c584, 49)], watch_globals=WATCH)
    observed = list(p['watched_globals'].values())
    return observed[:3], observed[3], p['calls']


def main():
    assert hashlib.sha256(pe.__data__).hexdigest() == EXE_HASH
    cases = []
    orders = [
        ['seal', 'portal', 'contact'],
        ['portal', 'seal', 'contact'],
        ['seal', 'portal', 'seal', 'contact'],
        ['seal', 'seal', 'contact'],
        ['contact', 'seal', 'contact'],
        ['seal', 'portal', 'decoy_defeated', 'contact'],
    ]
    for cycle in [1, 2, 3, 4]:
        for initial in [[8000, 5000, 1000], [1000, 625, 125], [12345, 5678, 999]]:
            for order in orders:
                stats, sealed, steps = initial[:], 0, []
                for operation in order:
                    before = stats[:]
                    before_sealed = sealed
                    expected = stats[:]
                    expected_sealed = sealed
                    if operation in ['seal', 'decoy_defeated'] and not sealed:
                        expected = [value // 10 for value in expected]
                        expected_sealed = 1
                    elif operation == 'portal':
                        if sealed:
                            expected = [value * 10 for value in expected]
                            expected_sealed = 0
                        if cycle == 2:
                            expected = [1000, 625, 125]
                    elif operation == 'contact' and cycle == 2:
                        expected = [1000, 625, 125]
                    stats, sealed, skipped = handler(operation, cycle, stats, sealed)
                    assert (stats, sealed) == (expected, expected_sealed), (cycle, order, operation, stats, sealed)
                    steps.append({'handler': operation, 'stats_before': before,
                                  'seal_before': before_sealed, 'stats_after': stats,
                                  'seal_after': sealed, 'skipped_calls': skipped})
                cases.append({'cycle': cycle, 'initial_stats': initial, 'order': order, 'steps': steps})
    stats, sealed, _ = handler('seal', 3, [8000, 5000, 1000], 0, valid_pattern=False)
    assert stats == [8000, 5000, 1000] and sealed == 0
    campaign = json.loads((ROOT / 'data/campaign.json').read_text(encoding='utf-8'))
    seal = next(e for e in campaign['events'] if e['id'] == 'floor_49_dice_seal')
    assert not seal['once']
    assert any(e['type'] == 'multiply_enemy' and e['numerator'] == 1 and e['denominator'] == 10 for e in seal['effects'])
    decoy = next(e for e in campaign['events'] if e['id'] == 'floor_49_decoy_zeno_defeated')
    assert decoy['trigger'] == {'type': 'post_combat', 'floor': 49}
    assert campaign['events'].index(seal) < campaign['events'].index(decoy)
    for event in campaign['events']:
        if event['id'].startswith('floor_50_backside_zeno_stats_'):
            assert {'type': 'cycle_at_most', 'amount': 2} in event['conditions']
    ranges = [(0x46b4db, 0x46b59c), (0x470506, 0x47057b), (0x4463a1, 0x4463de)]
    image = pe.get_memory_mapped_image()
    report = {
        'executable_sha256': EXE_HASH, 'shared_zeno_row': ['0x489A00', '0x489A04', '0x489A08'],
        'seal_flag': '0x4B88F8', 'scenarios': cases, 'invalid_pattern_unchanged': True,
        'decoy_death': {'seal_before_corner_removal': True,
                       'reward_builder_overwrites_seal_dialogue': True},
        'stat_write_sites': ['0x4463B3', '0x4463BD', '0x4463C7',
                            '0x455B58', '0x455B62', '0x455B6C', '0x455B85', '0x455B91', '0x455B9A',
                            '0x46B573', '0x46B585', '0x46B597',
                            '0x470520', '0x47052F', '0x47053E', '0x47055D', '0x470567', '0x470571'],
        'disassembly': {f'{start:#x}..{end:#x}':
                        [f'{i.address:#x}: {i.mnemonic} {i.op_str}' for i in
                         md.disasm(image[start - 0x400000:end - 0x400000], start)]
                        for start, end in ranges},
        'limits': ['Chains carry actual stat/flag writes between isolated handlers; they are not natural full-tower routes.',
                   'Drawing, normal combat arithmetic and queue playback are skipped in these probes.',
                   'Original save/load row reconstruction has separately documented cycle double-scaling; see docs/original-data.md.',
                   'C++ is reviewable source, with no standalone executable or alternate engine.'],
    }
    (ROOT / 'data/original-zeno-audit.json').write_text(
        json.dumps(report, ensure_ascii=False, indent=2) + '\n', encoding='utf-8', newline='\n')
    print(f'Verified {len(cases)} Zeno order scenarios and the invalid seal branch across four cycles')


if __name__ == '__main__':
    main()
