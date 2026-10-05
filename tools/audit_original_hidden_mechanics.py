"""Verify original Windows hidden mechanics and every Thief speech branch.

Moegirl supplies questions, not expected behavior. The installed, hash-pinned
TSW 1.2 executable supplies the answers. UI calls remain skipped; Continue is
probed as a separate entry point. Run after extract_original_events.py.
"""
import hashlib
import json

from original_event_probe import ROOT, RAW, pe, probe

EXE_HASH = '41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779'
ARTICLE = 'https://zh.moegirl.org.cn/%E9%AD%94%E5%A1%94'
FLAGS = [0x4b8808, 0x4b8860, 0x4b8870]


def event(campaign, identifier):
    return next(e for e in campaign['events'] if e['id'] == identifier)


def interaction(campaign, floor, x, y):
    return next(i for i in campaign['interactions']
                if (i['floor'], i['x'], i['y']) == (floor, x, y))


def speech(floor, x, y, expected, globals=()):
    result = probe(0x465900, floor, x, y, globals=globals, include_presentation=True)
    ids = [q[1] - 1 for q in result['queue'] if q[0] == 10]
    assert ids == [expected], (floor, x, y, ids)
    return {'hero': [floor, x, y], 'dialogue_ids': ids,
            'direct_map_writes': result['direct_map_writes'],
            'queue': result['queue'], 'skipped_calls': result['calls']}


def continuation(stage, floor):
    result = probe(0x44da10, floor, globals=[(0x48c5a4, stage)],
                   include_presentation=True, watch_globals=FLAGS)
    return {'stage': stage, 'direct_map_writes': result['direct_map_writes'],
            'queue': result['queue'], 'flags': result['watched_globals'],
            'skipped_calls': result['calls']}


def main():
    digest = hashlib.sha256(pe.__data__).hexdigest()
    assert digest == EXE_HASH, 'Review addresses before probing another executable'
    campaign = json.loads((ROOT / 'data/campaign.json').read_text(encoding='utf-8'))
    assert campaign['events'] == json.loads((ROOT / 'data/events.json').read_text(encoding='utf-8'))
    assert campaign['interactions'] == json.loads((ROOT / 'data/interactions.json').read_text(encoding='utf-8'))
    dialogues = {d['id']: d['text'] for d in json.loads(
        (ROOT / 'data/original-dialogue.json').read_text(encoding='utf-8'))}

    speeches = {
        'prison': speech(2, 2, 7, 3),
        'prison_departure': speech(2, 0, 6, 4),
        'dragon_tunnel_request': speech(2, 9, 10, 5),
        'dragon_tunnel_request_repeat': speech(2, 9, 10, 6, [(0x4b8808, 1)]),
        'octopus_bypass': speech(15, 9, 0, 17),
        '29f_unfinished': speech(29, 5, 2, 26),
        '29f_finished': speech(29, 5, 1, 27),
        '29f_finished_repeat': speech(29, 5, 1, 28, [(0x4b8860, 1)]),
        '35f_finished': speech(35, 5, 9, 31),
        '35f_finished_repeat': speech(35, 5, 9, 32, [(0x4b8870, 1)]),
        '50f': speech(50, 5, 5, 263),
    }
    continues = {str(stage): continuation(stage, floor) for stage, floor in
                 [(14, 2), (15, 2), (16, 2), (17, 2), (37, 29), (38, 29), (42, 35), (43, 35)]}
    # Inventory every dialogue Continue stage, then probe meaningful branches
    # in their actual floors above. This sweep uses default flags; it does not
    # prove that every possible reachable-state branch has been exercised.
    heard_flags = list(range(0x4b87f4, 0x4b8904, 4))
    scan = []
    for stage in range(10, 279):
        result = probe(0x44da10, 2, globals=[(0x48c5a4, stage)], watch_globals=heard_flags)
        flags = {address: value for address, value in result['watched_globals'].items() if value}
        if flags or result['direct_map_writes'] or result['queue']:
            scan.append({'stage': stage, 'direct_map_writes': result['direct_map_writes'],
                         'queue': result['queue'], 'heard_flags': flags,
                         'skipped_calls': result['calls']})
    assert [entry['stage'] for entry in scan if entry['direct_map_writes'] or entry['queue']] == [14, 15, 16]
    assert [entry['stage'] for entry in scan if entry['heard_flags']] == list(range(11, 68))
    assert [q for q in continues['14']['queue'] if q[0] == 12] == [
        [12, 68, 67], [12, 67, 66], [12, 66, 77]]
    assert [q for q in continues['15']['queue'] if q[0] == 12] == [[12, 77, 88], [12, 88, 99]]
    assert continues['16']['direct_map_writes'] == [(35, 3, 8, 6), (35, 4, 9, 21)]
    assert continues['16']['flags']['0x4b8808'] == 1
    assert continues['38']['flags']['0x4b8860'] == 1
    assert continues['42']['flags']['0x4b8870'] == 1
    assert speeches['35f_finished']['direct_map_writes'] == [(2, 10, 10, 6)]
    for floor, x, y, first, repeat in [(2, 10, 10, 5, 6), (29, 6, 1, 27, 28), (35, 4, 9, 31, 32)]:
        npc = interaction(campaign, floor, x, y)
        assert npc['text'] == dialogues[first]
        assert npc['after_text']['text'] == dialogues[repeat]
    for floor, x, y, first in [(2, 2, 6, 3), (15, 8, 0, 17), (29, 5, 3, 26), (50, 5, 4, 263)]:
        assert interaction(campaign, floor, x, y)['text'] == dialogues[first]
    assert interaction(campaign, 2, 0, 7)['text'] == dialogues[4] + ' ' + dialogues[57]
    assert not any('Talk to the thief' in i['text'] for i in campaign['interactions'])
    tunnel = event(campaign, 'thief_opens_floor_35_tunnel')
    assert [(e['floor'], e['x'], e['y'], e['tile']) for e in tunnel['effects']
            if e['type'] == 'set_tile'] == continues['16']['direct_map_writes']

    # F40 restores each precleared troop independently, but leaves an occupied
    # cell alone. Probing only the untouched initializer misses this branch.
    troop_cells = [i for i, t in enumerate(RAW[40 * 123 + 2:41 * 123])
                   if t in [135, 137, 139, 141] and i // 11 <= 3]
    assert len(troop_cells) == 12  # The Knight is not recreated by these writes.
    ambush = []
    for precleared in [False, True]:
        changes = [(40, i % 11, i // 11, 6) for i in troop_cells] if precleared else []
        result = probe(0x46cb1c, 40, 5, 6, changes=changes, include_presentation=True)
        writes = result['direct_map_writes']
        expected = [(40, i % 11, i // 11, RAW[40 * 123 + 2 + i]) for i in troop_cells]
        assert writes == (expected if precleared else [])
        assert len([q for q in result['queue'] if q[:2] == [11, 10]]) == 13
        ambush.append({'precleared': precleared, 'direct_map_writes': writes,
                       'changed': result['changed'], 'forced_battles': 13})
    staged = event(campaign, 'floor_40_encounter_71')
    configured = {(e['floor'], e['x'], e['y'], e['tile']) for e in staged['effects']
                  if e['type'] == 'set_tile'}
    assert set(ambush[1]['direct_map_writes']) <= configured
    for floor, x, y, tile in ambush[1]['direct_map_writes']:
        restored = next(e for e in staged['effects'] if e['type'] == 'set_tile'
                        and (e['floor'], e['x'], e['y'], e['tile']) == (floor, x, y, tile))
        assert restored['conditions'] == [{'type': 'tile', 'floor': floor, 'x': x, 'y': y, 'tile': 6}]
    thief_cleanup = probe(0x46cb1c, 42, 5, 9, changes=[(35, 4, 9, 21)])
    assert (35, 4, 9, 6) in thief_cleanup['direct_map_writes']
    assert {'type': 'set_tile', 'floor': 35, 'x': 4, 'y': 9, 'tile': 6} in event(
        campaign, 'floor_42_zeno_and_golden_knight_arrival')['effects']

    closure = probe(0x46cb1c, 15, 5, 7, include_presentation=True)
    assert [13, 93, 5] in closure['queue']  # Gate closes behind the hero.
    dragon_cells = [RAW[35 * 123 + 2 + y * 11 + x] for y in range(4, 7) for x in range(4, 7)]
    assert dragon_cells == list(range(115, 124))
    assert all(campaign['tiles'][str(t)]['kind'] == 'wall' for t in dragon_cells if t != 122)
    assert 47 not in RAW[35 * 123 + 2:36 * 123], 'Crystal is spawned after victory'
    passages = [(i % 11, i // 11) for i, t in enumerate(RAW[36 * 123 + 2:37 * 123]) if t == 9]
    assert len(passages) == 20 and campaign['tiles']['9']['kind'] == 'hidden_wall'
    red_keys = [e for e in event(campaign, 'floor_25_boss_defeated')['effects']
                if e['type'] == 'set_tile' and e['tile'] == 30]
    assert len(red_keys) == 5
    assert campaign['tiles']['3']['key'] == 'red'
    assert sum(t == 3 for t in RAW[26 * 123 + 2:27 * 123]) == 4
    princess = []
    for boss_dead in [False, True]:
        result = probe(0x444490, 26, 5, 6, include_presentation=True,
                       changes=[(25, 5, 5, 6)] if boss_dead else [], globals=[(0x48c584, 60)])
        ids = [q[1] - 1 for q in result['queue'] if q[0] == 10]
        assert ids == [24, 25]
        assert (50, 5, 4, 21) in result['direct_map_writes']
        assert any(f == 24 for f, _, _, _ in result['direct_map_writes']) == boss_dead
        princess.append({'boss_dead': boss_dead, 'dialogue_ids': ids,
                         'direct_map_writes': result['direct_map_writes']})
    assert interaction(campaign, 26, 5, 5)['text'] == dialogues[24]
    assert not any(i['floor'] == 50 and (i['x'], i['y']) == (4, 8) for i in campaign['interactions'])
    caster = probe(0x46cb1c, 48, 0, 0, include_presentation=True)
    assert [6, 0, 93] in caster['queue']
    gate = probe(0x4664e4, 48, changes=[(48, 0, 0, 6)], include_presentation=True)
    assert [13, 84, 4] in gate['queue']  # Gate-opening blend mode 4.

    # The article's no-boss-immunity claim is too broad for this Windows image.
    bomb = []
    for tile, susceptible in [(61, True), (91, False), (92, False), (93, True), (95, True),
                              (97, False), (115, False), (122, False), (133, True),
                              (145, False), (146, False), (159, False)]:
        result = probe(0x451c20, 50, changes=[(50, 5, 4, tile)],
                       globals=[(0x48c55c, 49)], watch_globals=[0x48c58c])
        allowed = result['watched_globals']['0x48c58c'] == 2
        assert allowed == susceptible
        bomb.append({'tile': tile, 'susceptible': allowed})

    # Follow arithmetic but skip drawing/strings. A lethal later-cycle normal
    # Zeno battle queues death, not the post-victory moncheck callback.
    battles = []
    for hp in [1000, 500000]:
        result = probe(0x444490, 50, 5, 5, changes=[(50, 5, 4, 91)],
            globals=[(0x48c584, 49), (0x4b8904, 43), (0x4b8688, hp),
                     (0x4b868c, 10000), (0x4b8690, 5000)],
            follow_calls=[0x44a480, 0x450064, 0x450288, 0x4502d0,
                          0x45031c, 0x450360, 0x4503a8], include_presentation=True)
        death = [q for q in result['queue'] if q[0] == 3]
        postcombat = [q for q in result['queue'] if q[:2] == [11, 5]]
        assert bool(death) == (hp == 1000)
        assert bool(postcombat) == (hp == 500000)
        battles.append({'hero_hp': hp, 'hero_attack': 10000, 'hero_defense': 5000,
                        'death_records': death, 'postcombat_records': postcombat,
                        'skipped_calls': result['calls'], 'followed_calls': result['followed_calls']})
    first = probe(0x444490, 50, 5, 5, changes=[(50, 5, 4, 91)], globals=[(0x48c584, 49)])
    assert [11, 6, 0] in first['queue'] and '0x44a480' not in first['calls']
    reset = []
    for later in [0, 1]:
        result = probe(0x455cb8, 50, globals=[(0x4b8904, 43), (0x4b8908, later),
                       (0x4b86cc, 1), (0x4b86d0, 1), (0x4b86d4, 1), (0x4b8694, 789)])
        assert result['stat_slots'][17:20] == ([0, 0, 0] if later == 0 else [1, 1, 1])
        assert result['stat_slots'][3] == (0 if later == 0 else 789)
        reset.append({'later_flag': later, 'orbs_after': result['stat_slots'][17:20],
                      'gold_after': result['stat_slots'][3]})

    report = {'executable_sha256': digest, 'article': ARTICLE,
        'article_revision_seen': '2026-09-11 01:32', 'speech_handler': '0x465900',
        'dialogue_continue_handler': '0x44da10', 'thief_speeches': speeches,
        'thief_continuations': continues,
        'dialogue_continue_default_state_scan': {'inclusive_stage_range': [10, 278], 'active_stages': scan},
        'floor_40_actor_restoration': ambush,
        'floor_42_thief_cleanup': thief_cleanup['direct_map_writes'],
        'octopus_retreat_gate': [13, 93, 5], 'dragon_body': dragon_cells,
        'floor_36_hidden_wall_cells': passages, 'floor_25_red_key_count': len(red_keys),
        'floor_26_red_door_count': 4, 'princess_prerequisite': princess,
        'floor_48_caster_queue': caster['queue'], 'floor_48_gate_queue': gate['queue'],
        'bomb_classifier': bomb, 'later_zeno_battles': battles,
        'first_cycle_ending_has_no_battle': True, 'cycle_reset': reset,
        'limits': ['GUI and audio calls remain skipped, with ABI stack cleanup preserved.',
                  'Direct writes include unchanged values; queue interpretation is separately tested in Rust.',
                  'This is branch evidence for the listed scenarios, not full reachable-state coverage.',
                  'Normal lethal later-cycle combat is checked here; the separate scripted enemy-first builder is outside this probe.']}
    (ROOT / 'data/original-hidden-mechanics-audit.json').write_text(
        json.dumps(report, ensure_ascii=False, indent=2) + '\n', encoding='utf-8', newline='\n')
    print('Verified 11 Thief speech branches, 8 Continue stages, F40 respawn, hidden passages/gates, princess prerequisites, bomb immunity and ending/reset claims')


if __name__ == '__main__':
    main()
