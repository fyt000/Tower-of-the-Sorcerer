"""Cross-check tswKai source claims against read-only original game evidence.

Run after `gh repo clone Z-H-Sun/tswKai build/research/tswKai` and the
existing original extractors. Only isolated x86 helpers and local artwork are
read; neither game nor upstream binaries are launched or patched on disk.
Requires pefile, capstone, unicorn and Pillow, as the other extraction tools do.
"""
import codecs
import hashlib
import io
import json
import os
from pathlib import Path
import re
import subprocess
import zipfile

from PIL import Image, ImageChops
from original_event_probe import ROOT, RAW, pe, probe

EXE_HASH = '41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779'
UPSTREAM = ROOT / 'build/research/tswKai'
UPSTREAM_COMMIT = '08e5af7c8f3e4d1696ccd5725d745e87b989bff6'
WIKI_COMMIT = '9d5fd2f0b3589835a7c9e870bc232d80d0a8cf55'


def fnv(data):
    value = 0xcbf29ce484222325
    for byte in data:
        value = ((value ^ byte) * 0x100000001b3) & 0xffffffffffffffff
    return f'{value:016x}'


def signature(name, offset, length, source):
    pattern = rf'\[0x{offset:x},\s*{length},\s*"((?:\\.|[^"\\])*)"'
    match = re.search(pattern, source, flags=re.I)
    assert match, (name, 'Upstream original signature changed')
    expected = codecs.decode(match[1], 'unicode_escape').encode('latin1')
    assert len(expected) == length, name
    observed = pe.get_memory_mapped_image()[offset:offset + length]
    assert observed == expected, (name, 'Installed original differs from upstream original bytes')
    return {'issue': name, 'address': hex(0x400000 + offset),
            'upstream_original_bytes_match': True, 'original_hex': observed.hex()}


def retreat(x, y, delta, shield=1, floor=47):
    target = y * 11 + x + delta
    neighbor = y * 11 + x + delta // 2
    return probe(0x44c5c4, floor, x, y, include_presentation=True,
        changes=[(floor, neighbor % 11, neighbor // 11, 151),
                 (floor, target % 11, target // 11, 6)],
        globals=[(0x48c58c, 110), (0x48c568, delta & 0xffffffff),
                 (0x48c558, y * 11 + x), (0x4b872c, shield), (0x4b87e8, 3)])


def main():
    digest = hashlib.sha256(pe.__data__).hexdigest()
    assert digest == EXE_HASH, 'Review executable addresses before probing another version'
    commit = subprocess.check_output(['git', '-C', str(UPSTREAM), 'rev-parse', 'HEAD'], text=True).strip()
    assert commit == UPSTREAM_COMMIT, 'Review the upstream changes before updating the pinned comparison'
    wiki = ROOT / 'build/research/tswKai.wiki'
    if wiki.exists():
        assert subprocess.check_output(['git', '-C', str(wiki), 'rev-parse', 'HEAD'], text=True).strip() == WIKI_COMMIT
    source = (UPSTREAM / 'tswMod.rb').read_text(encoding='utf-8')
    signatures = [signature(name, offset, length, source) for name, offset, length in [
        ('49F phantom event increment', 0x637dd, 2),
        ('40F incorrect door prompt', 0x740be, 2),
        ('33F missing lower trigger setup', 0x54e0b, 34),
        ('33F two entrance trigger cleanup', 0x73723, 27),
        ('Lucky Gold first-strike reward display', 0x7ff54, 54),
    ]]
    image = pe.get_memory_mapped_image()
    assert image[0x55b78:0x55b7f] == bytes.fromhex('8b867c02000040')
    assert image[0x4e3d7:0x4e3e1] == bytes.fromhex('810588864b00d0070000')
    assert image[0x4c5fa:0x4c600] == bytes.fromhex('8b35a4864b00')

    # The queued half-HP opcode uses floor division on current HP. Stop before
    # any Delphi formatting/UI call. Therefore odd HP loses the larger half.
    half = []
    for hp in [1000, 1001, 1]:
        result = probe(0x4541ce, 49, globals=[(0x4b8688, hp)], end=0x4541df)
        assert result['stat_slots'][0] == hp // 2
        half.append({'before_hp': hp, 'after_hp': result['stat_slots'][0]})
    pincer = probe(0x44c464, 49, 5, 5, include_presentation=True,
        globals=[(0x48c558, 60), (0x4b87e8, 4)])
    assert [19, 0, 0] in pincer['queue']

    retreats = []
    for x, y, delta, expected in [(5, 0, 2, []), (9, 5, 2, [[12, 65, 66]]),
                                 (1, 5, -2, [[12, 55, 54]]), (5, 5, 2, [[12, 61, 62]])]:
        result = retreat(x, y, delta)
        moves = [q for q in result['queue'] if q[0] == 12]
        assert moves == expected
        retreats.append({'hero': [x, y], 'target_delta': delta, 'original_moves': moves})
    without_shield = retreat(5, 5, 2, shield=0)
    with_shield = retreat(5, 5, 2, shield=1)
    assert any(q[0] == 16 and 65336 in q[1:] for q in without_shield['queue'])  # signed -200
    assert not any(q[0] == 16 for q in with_shield['queue'])
    assert [12, 61, 62] in with_shield['queue']
    assert not any(q[0] == 12 for q in retreat(5, 5, 2, floor=46)['queue'])

    assert RAW[33 * 123 + 2 + 53] == 7 and RAW[33 * 123 + 2 + 75] == 6
    dead = [(33, x, y, 6) for x, y in [(8, 4), (10, 4), (8, 6), (10, 6)]]
    late_entry = probe(0x46cb1c, 33, 9, 4, changes=dead, include_presentation=True)
    gates = [q for q in late_entry['queue'] if q[0] == 13]
    assert [13, 42, 5] in gates and [13, 86, 5] in gates

    zeno = []
    for cycle, factor, later, stats in [(1, 0, 0, [8000, 5000, 1000, 500]),
                                       (2, 43, 0, [1000, 625, 125, 500]),
                                       (3, 43, 1, [8000, 5000, 1000, 500])]:
        result = probe(0x46cb1c, 24, 5, 0, include_presentation=True,
            changes=[(24, 5, 0, 7)],
            globals=[(0x4b8904, factor), (0x4b8908, later), (0x4b88f8, 1),
                     (0x489a00, 800), (0x489a04, 500), (0x489a08, 100)])
        assert [15, stats] in [list(row) for row in result['monster_changes']]
        moves = [q for q in result['queue'] if q[0] == 12]
        forced = [q for q in result['queue'] if q[:2] == [11, 10]]
        assert moves == ([[12, 49, 60], [12, 60, 71]] if cycle == 2 else [])
        assert forced == ([[11, 10, 71]] if cycle == 2 else [])
        zeno.append({'cycle': cycle, 'normalized_stats': stats, 'moves': moves, 'forced_battles': forced})

    thief = probe(0x465900, 50, 5, 5, changes=[(50, 5, 4, 21)], include_presentation=True)
    assert thief['queue'] == [[10, 264, 0], [0, 0, 0]]

    original_dir = Path(os.environ.get('TOS_ORIGINAL_EXE', r'D:\Program Files (x86)\Tower of the Sorcerer\TSW.exe')).parent
    original_masks = Image.open(original_dir / 'Data3/Chtableb.oz').convert('RGBA')
    with zipfile.ZipFile(UPSTREAM / 'tsw.patch.zip') as archive:
        patched_masks = Image.open(io.BytesIO(archive.read('Data3/Chtableb.oz'))).convert('RGBA')
    masks = []
    for tile in [151, 152]:
        x, y = (tile - 1) % 11 * 40, (tile - 1) // 11 * 40
        before = original_masks.crop((x, y, x + 40, y + 40))
        expected = patched_masks.crop((x, y, x + 40, y + 40))
        assert ImageChops.difference(ImageChops.offset(before, 1, 0), expected).getbbox() is None
        assert all(before.getpixel((dx, dy))[0] in [0, 255] for dy in range(40) for dx in range(40))
        masks.append({'tile': tile, 'original_rgba_fnv': fnv(before.tobytes()),
            'corrected_rgba_fnv': fnv(expected.tobytes()), 'correction': 'shift_right_1px',
            'original_black_rows': [f'{sum((1 << (39 - dx)) for dx in range(40) if before.getpixel((dx, dy))[0] == 0):010x}' for dy in range(40)]})

    events = json.loads((ROOT / 'data/events.json').read_text(encoding='utf-8'))
    campaign = json.loads((ROOT / 'data/campaign.json').read_text(encoding='utf-8'))
    assert campaign['events'] == events
    trap = next(e for e in events if e['id'] == 'floor_33_encounter_53')
    assert trap['trigger']['positions'] == [{'x': 9, 'y': 4}, {'x': 9, 'y': 6}]
    assert campaign['rules']['magician_retreat']['bounds'] == 'corrected'
    portal = next(e for e in events if e['id'] == 'time_gate_to_floor_50')
    assert any(e['type'] == 'battle_at' and e['y'] == 6 and e['first_strike'] for e in portal['effects'])
    speech = next(i for i in campaign['interactions'] if i['floor'] == 50 and i['x'] == 5 and i['y'] == 4)
    assert speech['text'] == "Ah!, we meet again! Thank goodness you're alive!"
    assert speech['dialogue_ids'] == [263] and speech['effects'] == []

    report = {'executable_sha256': digest, 'upstream_commit': commit, 'wiki_commit': WIKI_COMMIT,
        'matching_upstream_signatures': signatures, 'half_hp_handler': '0x4541ce..0x4541df',
        'half_hp_cases': half, 'pincer_opcode': [19, 0, 0], 'original_retreat_boundary_cases': retreats,
        'retreat_unprotected_queue': without_shield['queue'], 'retreat_protected_queue': with_shield['queue'],
        'original_floor_33': {'upper_entrance_tile': 7, 'lower_entrance_tile': 6, 'after_guard_deaths_gate_closures': gates},
        'floor_50_portal_variants': zeno, 'floor_50_thief_queue': thief['queue'], 'magician_masks': masks,
        'boundaries': ['Queue builders skip GUI/audio calls; no upstream executable or patch is launched.',
            'Half-HP calculation is executed directly; full walking and protection combinations are covered by native engine scenarios.',
            'Mask corrections are compared with pinned upstream artwork; remaining atlas differences are not silently imported.',
            'These controlled branches do not prove all reachable map states or a natural complete playthrough.']}
    (ROOT / 'data/original-mechanics-audit.json').write_text(json.dumps(report, ensure_ascii=False, indent=2) + '\n', encoding='utf-8', newline='\n')
    print('Verified 5 upstream bug signatures, odd/even pincer HP, 47F retreat/shield, 33F trap, 3 Zeno cycles and both Magician A masks')


if __name__ == '__main__':
    main()
