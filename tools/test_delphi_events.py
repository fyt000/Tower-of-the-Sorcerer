"""Compare native Delphi scene queues with the pinned original machine code.

The native side runs real hidden VCL controls. The original side runs the
recovered entry in Unicorn, follows queue builders and door expansion, and
skips VCL/audio calls. The report explicitly retains those skipped calls.
This is queue/state evidence, not a pixel equality or full campaign claim.
"""
from pathlib import Path
import json
import hashlib
import os
import struct
import subprocess

import build_delphi_game
from build_delphi2_reference import stage
from original_event_probe import probe, RAW, pe
from unicorn.x86_const import UC_X86_REG_EBP, UC_X86_REG_EBX, UC_X86_REG_ESI

ROOT = Path(__file__).resolve().parents[1]
WORK = ROOT / 'build/delphi-native-events'


def native(case, raw):
    input_path = WORK / 'input.bin'
    output_path = WORK / 'output.bin'
    input_path.write_bytes(raw)
    result = subprocess.run([str(WORK / 'EventQueueSmoke.exe'), str(case['builder']),
                             str(input_path), str(output_path), '40'], cwd=WORK,
                            capture_output=True, timeout=20,
                            creationflags=subprocess.CREATE_NO_WINDOW)
    if result.returncode:
        raise RuntimeError(result.stdout.decode('cp1252') + result.stderr.decode('cp1252'))
    out = output_path.read_bytes()
    count, = struct.unpack_from('<I', out)
    queue = [list(struct.unpack_from('<HHH', out, 4 + index * 6)) for index in range(count)]
    position = 4 + count * 6
    return queue, out[position:position + 684], out[position + 684:position + 684 + 6273], out[-528:]


def main():
    WORK.mkdir(parents=True, exist_ok=True)
    for source in (ROOT / 'delphi/src').rglob('*'):
        if source.suffix.lower() not in ('.pas', '.inc'):
            continue
        target = WORK / 'src' / source.relative_to(ROOT / 'delphi/src')
        target.parent.mkdir(parents=True, exist_ok=True)
        stage(source, target)
    (WORK / 'tests').mkdir(exist_ok=True)
    stage(ROOT / 'delphi/tests/EventQueueSmoke.dpr', WORK / 'tests/EventQueueSmoke.dpr')
    # Resource generation writes only inside this fixture's private directory.
    build_delphi_game.WORK = WORK
    build_delphi_game.resources(pe)
    toolchain = ROOT / 'build/research/delphi2/base'
    lib = os.path.relpath(toolchain / 'lib', WORK)
    result = subprocess.run([str(toolchain / 'bin/DCC32.EXE'), '-B', '-U' + lib + ';src',
                             '-Isrc;src\\generated', '-E.', '-N.', 'tests\\EventQueueSmoke.dpr'],
                            cwd=WORK, capture_output=True, timeout=30)
    (WORK / 'compile.log').write_bytes(result.stdout + result.stderr)
    if result.returncode:
        print((result.stdout + result.stderr).decode('cp1252'))
        raise SystemExit(result.returncode)
    cases = []
    # These are actual direct arrival builders. Position-dependent 33F branches
    # and first/repeated 10F branches receive distinct fixtures below.
    for floor in (10, 15, 20, 24, 25, 30, 32, 33, 38, 40, 42, 43, 48, 49):
        cases.append(dict(name=f'arrival-{floor}', builder=1, address=0x46cb1c,
                          floor=floor, x=5, y=5))
    cases += [dict(name='arrival-33-wall', builder=1, address=0x46cb1c, floor=33, x=8, y=9),
              dict(name='arrival-10-repeat', builder=1, address=0x46cb1c, floor=10, x=5, y=5,
                   words={424: 1}),
              dict(name='zeno', builder=3, address=0x461a0c, floor=3, x=5, y=5,
                   indices=(70, 0, 0, 0)),
              dict(name='four-guards', builder=4, address=0x461ef4, floor=42, x=5, y=9,
                   indices=(71, 93, 81, 83)),
              dict(name='eight-guards', builder=5, address=0x462560, floor=49, x=5, y=5),
              dict(name='capture', builder=6, address=0x464048, floor=3, x=4, y=8),
              dict(name='ending', builder=7, address=0x4463a1, floor=50, x=5, y=4,
                   end=0x448fbc)]
    for floor in (2, 8, 10, 11, 14, 15, 17, 20, 25, 30, 32, 33, 34, 35, 38, 40, 41, 45, 48, 49, 50):
        cases.append(dict(name=f'guards-{floor}', builder=2, address=0x4664e4,
                          floor=floor, x=5, y=5))
    cases += [dict(name='guard-reward-2', builder=2, address=0x4664e4, floor=2, x=5, y=5,
                   changes=[(2, 5, 1, 6), (2, 7, 1, 6)]),
              dict(name='zeno-seal', builder=2, address=0x4664e4, floor=49, x=5, y=5,
                   changes=[(49, x, y, 6) for x, y in ((5, 1), (4, 2), (6, 2), (5, 3))]),
              dict(name='backside-ending', builder=2, address=0x4664e4, floor=50, x=5, y=5,
                   words={636: 43})]
    events = json.loads((ROOT / 'data/events.json').read_text())
    for event in events:
        if event['trigger']['type'] != 'post_combat':
            continue
        floor = event['trigger']['floor']
        changes = [(row['floor'], row['x'], row['y'], row['tile'])
                   for row in event['conditions'] if row['type'] == 'tile']
        words = {360: 5}  # Include the original music stop/start branches.
        if any(row['type'] == 'cycle_at_least' for row in event['conditions']):
            words[636] = 43
        cases.append(dict(name=event['id'], builder=2, address=0x4664e4,
                          floor=floor, x=5, y=5, changes=changes, words=words))
    cases += [dict(name='arrival-24-backside', builder=1, address=0x46cb1c,
                   floor=24, x=5, y=5, words={636: 43, 360: 17}),
              dict(name='arrival-24-sealed', builder=1, address=0x46cb1c,
                   floor=24, x=5, y=5, words={624: 1, 360: 17}),
              dict(name='arrival-20-music', builder=1, address=0x46cb1c,
                   floor=20, x=5, y=5, words={360: 16})]
    report = []
    failures = []
    monster_bytes = pe.get_data(0x489910 - pe.OPTIONAL_HEADER.ImageBase, 528)
    for case in cases:
        hero = bytearray(684)
        for offset, value in {0: 400, 4: 10, 8: 10, 16: case['floor'], 24: case['x'],
                              28: case['y'], 352: 4, **case.get('words', {})}.items():
            struct.pack_into('<i', hero, offset, value)
        maps = bytearray(RAW)
        for floor, x, y, tile in case.get('changes', []):
            maps[floor * 123 + 2 + y * 11 + x] = tile
        indices = case.get('indices', (0, 0, 0, 0))
        raw = hero + maps + monster_bytes + struct.pack('<4i', *indices)
        actual, native_hero, native_maps, native_monsters = native(case, raw)
        globals_ = [(0x48c558, indices[0]), (0x48c55c, indices[1]),
                    (0x48c560, indices[2]), (0x48c564, indices[3])]
        registers = []
        if case['builder'] == 7:
            globals_ += [(0x6ffdfc, 0x200000)]
            registers = [(UC_X86_REG_EBP, 0x6ffe00), (UC_X86_REG_EBX, 0x48c5ac),
                         (UC_X86_REG_ESI, 0x48c74c)]
        original = probe(case['address'], case['floor'], case['x'], case['y'],
                         state={0x4b8688: bytes(hero), 0x4b8934: bytes(maps),
                                0x489910: monster_bytes}, globals=globals_, registers=registers,
                         end=case.get('end', 0x6ffff0), include_presentation=True,
                         follow_calls=[0x4660d0, 0x461a0c, 0x461ef4], return_state=True)
        expected = original['queue']
        raw_queue_equal = actual == expected
        # The 49F summon has a documented stray INC exposing an unwritten
        # record at 0x4637DD. Native deliberately omits that stale command.
        omitted_stale_record = False
        if case['builder'] == 5 and len(expected) == len(actual) + 1 and expected[0] == [0, 0, 0]:
            expected = expected[1:]
            omitted_stale_record = True
        same_queue = actual == expected
        same_map = native_maps == original['state'][0x4b8934]
        same_monsters = native_monsters == original['state'][0x489910]
        # Original presentation hooks write unrelated transient hero flags;
        # compare persisted story flags and statistics independently.
        hero_slots = list(range(0, 48, 4)) + list(range(364, 644, 4))
        hero_diffs = [offset for offset in hero_slots if
                      native_hero[offset:offset + 4] != original['state'][0x4b8688][offset:offset + 4]]
        okay = same_queue and same_map and same_monsters and not hero_diffs
        row = dict(fixture=case['name'], passed=okay, queue_records=len(actual),
                   raw_queue_equal=raw_queue_equal, scoped_queue_equal=same_queue,
                   maps_equal=same_map, monsters_equal=same_monsters,
                   story_hero_differences=hero_diffs, original_skipped_calls=original['calls'])
        if omitted_stale_record:
            row['original_stale_record_omitted'] = dict(address='0x004637DD', record=[0, 0, 0])
        if not same_queue:
            row['first_queue_difference'] = next(((i, x, y) for i, (x, y) in
                                                  enumerate(zip(actual, expected)) if x != y),
                                                 (min(len(actual), len(expected)), 'length', len(expected)))
            row['actual_queue'] = actual
            row['expected_queue'] = expected
        report.append(row)
        if not okay:
            failures.append(case['name'])
        print(case['name'], 'PASS' if okay else 'FAIL', len(actual))
    output = dict(schema_version=1,
                  original_sha256=hashlib.sha256(pe.__data__).hexdigest(),
                  fixture_count=len(report), passing=sum(row['passed'] for row in report),
                  raw_matching_queues=sum(row['raw_queue_equal'] for row in report),
                  compared_queue_records=sum(row['queue_records'] for row in report),
                  native_compiler_sha256=hashlib.sha256((toolchain / 'bin/DCC32.EXE').read_bytes()).hexdigest(),
                  native_executable_sha256=hashlib.sha256((WORK / 'EventQueueSmoke.exe').read_bytes()).hexdigest(),
                  source_sha256={str(path.relative_to(ROOT)).replace('\\', '/'):
                                 hashlib.sha256(path.read_bytes()).hexdigest()
                                 for path in [ROOT / 'delphi/src/EventMethods.inc',
                                              ROOT / 'delphi/src/EventScenes.inc',
                                              ROOT / 'delphi/tests/EventQueueSmoke.dpr']},
                  scope='Native hidden VCL queue builders versus original x86 emulation; VCL and audio original callees skipped.',
                  limits=['Does not establish pixel identity, manual UI usability, or a complete campaign playthrough.',
                          'Only compared the stated fixture inputs; original stale 49F summon record explicitly omitted.'],
                  fixtures=report, failures=failures)
    encoded = json.dumps(output, indent=2) + '\n'
    (WORK / 'report.json').write_text(encoded)
    target = ROOT / 'build/delphi-game/reports/event-comparison-report.json'
    target.parent.mkdir(parents=True, exist_ok=True)
    target.write_text(encoded)
    if failures:
        raise SystemExit('Scene comparison failed: ' + ', '.join(failures))


if __name__ == '__main__':
    main()
