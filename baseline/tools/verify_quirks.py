"""Check correction-log gameplay triggers against the unpatched original EXE.

The only normalized unsafe behavior is 49F's unwritten ghost command. Complete
playback and overflow-length combat are covered separately by core_tests.cpp.
"""
from pathlib import Path
import argparse
import hashlib
import json
import subprocess
import sys

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / 'tools'))
from original_event_probe import probe, pe, RAW
from differential import HASH, HERO, FIELDS
from verify_interactions import comparable

FOLLOW = [0x4660D0, 0x44C04C, 0x44C464, 0x44C5C4, 0x44C9F0,
          0x46397C, 0x46CB1C, 0x47BEAC, 0x461A0C, 0x465900,
          0x450064, 0x45031C, 0x450360, 0x450288, 0x4502D0, 0x4503A8,
          0x48028C, 0x4802FC, 0x480340]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--probe', type=Path,
                        default=ROOT / 'baseline/build-vs/Release/tos_baseline_probe.exe')
    args = parser.parse_args()
    if hashlib.sha256(pe.__data__).hexdigest() != HASH:
        raise RuntimeError('Original image hash mismatch')
    process = subprocess.Popen([str(args.probe)], stdin=subprocess.PIPE,
                               stdout=subprocess.PIPE, text=True)
    failures, skipped, groups, safety_exceptions = [], set(), {}, []

    def cpp(lines):
        process.stdin.write('\n'.join(lines) + '\n')
        process.stdin.flush()
        result = json.loads(process.stdout.readline())
        if isinstance(result, dict) and 'error' in result:
            raise RuntimeError(result)
        return result

    def compare(name, address, floor, x=5, y=5, target=None, changes=(),
                values=None, extra=(), commands=('call contact',), items=(),
                combat=False, ghost=False):
        target = y * 11 + x if target is None else target
        values = values or {}
        globals = [(HERO + FIELDS[k], v) for k, v in values.items()]
        globals += [(HERO + 68 + 4 * i, v) for i, v in items]
        globals += [(HERO + 352, 4), (0x48C584, target), (0x48C756, target)] + list(extra)
        watched = [HERO + 168 + 4 * i for i in range(12)]
        original = probe(address, floor, x, y, changes, globals=globals,
                         include_presentation=True, follow_calls=FOLLOW, watch_globals=watched)
        skipped.update(original['calls'])
        original_queue = original['queue']
        if ghost:
            if original_queue[0] != [7, 777, 0] or len(original_queue) != 129:
                raise RuntimeError('The original 49F ghost-command trigger did not reproduce')
            original_queue = original_queue[1:]
            safety_exceptions.append(dict(scenario=name, original_unwritten_command=[7, 777, 0],
                                          original_records=129, valid_records=128))
        lines = ['original', f'set floor {floor}', f'set x {x}', f'set y {y}',
                 'set facing 4', f'set contact {target}']
        lines += [f'tile {f} {ty * 11 + tx} {t}' for f, tx, ty, t in changes]
        lines += [f'set {k} {v}' for k, v in values.items()]
        lines += [f'item {i} {v}' for i, v in items]
        actual = cpp(lines + list(commands) + ['snapshot'])
        actual_queue = cpp(['trace 100000']) if combat else actual['queue']
        left = comparable(actual_queue) if combat else actual_queue
        right = comparable(original_queue) if combat else original_queue
        diff = []
        if left != right:
            index = next((i for i, pair in enumerate(zip(left, right)) if pair[0] != pair[1]),
                         min(len(left), len(right)))
            diff.append(dict(queue_index=index, cpp=left[index:index+3],
                             original=right[index:index+3], lengths=[len(left), len(right)]))
        for i in (*range(12), 14, 15, 16):
            if actual['hero'][i] != original['stat_slots'][i]:
                diff.append(dict(hero_slot=i, cpp=actual['hero'][i], original=original['stat_slots'][i]))
        expected = [list(RAW[f * 123 + 2:(f + 1) * 123]) for f in range(51)]
        for f, tx, ty, t in list(changes) + original['changed']:
            if 0 <= tx < 11 and 0 <= ty < 11:
                expected[f][ty * 11 + tx] = t
        if actual['maps'] != expected:
            diff.append(dict(map_mismatch=[(f, i, actual['maps'][f][i], expected[f][i])
                                          for f in range(51) for i in range(121)
                                          if actual['maps'][f][i] != expected[f][i]][:5]))
        for i in range(12):
            old = original['watched_globals'][hex(HERO + 168 + 4 * i)]
            if actual['merchant_used'][i] != old:
                diff.append(dict(merchant=i, cpp=actual['merchant_used'][i], original=old))
        if diff:
            failures.append(dict(scenario=name, differences=diff))
        group = name.split('/')[0]
        groups[group] = groups.get(group, 0) + 1
        return original, actual

    for y in (4, 6):
        old, new = compare(f'33F-trap/entry-{y}', 0x444490, 33, 9, y + 1, target=y * 11 + 9)
        if bool(old['queue']) != (y == 4):
            raise RuntimeError('Unexpected original 33F entry trigger')
    cleared = [(33, x, y, 6) for x, y in ((8, 4), (10, 4), (8, 6), (10, 6))]
    for gate in (6, 4):
        changes = cleared + [(33, 9, y, gate) for y in (3, 7)]
        old, new = compare(f'33F-trap/guards-cleared-gates-{gate}', 0x4664E4, 33,
                           changes=changes, commands=('call guards',))
        if bool(old['queue']) != (gate == 4):
            raise RuntimeError('Unexpected original 33F gate predicate')

    # Exercise row checks, failed vertical retreats, and horizontal row wrapping.
    for cycle in (0, 43):
        for x in (0, 1, 5, 9, 10):
            for y in (0, 1, 2, 5, 8, 9, 10):
                for dx, dy in ((0, -1), (-1, 0), (1, 0), (0, 1)):
                    mx, my = x + dx, y + dy
                    if not (0 <= mx < 11 and 0 <= my < 11):
                        continue
                    changes = [(47, i % 11, i // 11, 6) for i in range(121)]
                    changes.append((47, mx, my, 151))
                    compare(f'47F-retreat/{cycle}/{x}-{y}/{dx}-{dy}', 0x444490, 47, x, y,
                            changes=changes, values={'cycle': cycle})

    for cycle in (0, 43, 87):
        changes = [(45, 5, 4, 19)]
        captured = probe(0x449014, 45, 5, 5, changes,
                         globals=[(HERO + 12, 1000), (HERO + 636, cycle), (0x48C584, 49)],
                         watch_globals=[0x48C598, 0x48C594, 0x48C5CC])
        old, new = compare(f'45F-merchant/{cycle}', 0x44E1CC, 45, target=49, changes=changes,
                           values={'cycle': cycle, 'gold': 1000},
                           extra=[(int(a, 16), v) for a, v in captured['watched_globals'].items()],
                           commands=('call contact', 'choose 0'))
        if old['stat_slots'][0] != 2400 or old['stat_slots'][3] != 0:
            raise RuntimeError('Unexpected original 45F Merchant reward')

    old, new = compare('40F-prompt/boss-script', 0x46CB1C, 40, 5, 7,
                       commands=('call floor',))
    if [2, 4, 0] not in old['queue']:
        raise RuntimeError('Missing original 40F yellow-door prompt')
    compare('50F-thief/original-speech-id', 0x444490, 50, target=49, changes=[(50, 5, 4, 21)])
    for magician in (151, 153):
        changes = [(1, i % 11, i // 11, 6) for i in range(121)] + [(1, 5, 3, magician)]
        compare(f'backside-magic/message-{magician}', 0x444490, 1, target=49,
                changes=changes, values={'cycle': 43})

    for enemy_first in (False, True):
        compare(f'Lucky-Gold/enemy-first-{enemy_first}', 0x47F7D4 if enemy_first else 0x44A480,
                1, target=49, changes=[(1, 5, 4, 61)],
                values={'attack': 100, 'defense': 100}, items=[(14, 1)], combat=True,
                commands=(f'call battle {int(enemy_first)}',))

    compare('49F-safety/poisoned-stale-record', 0x462560, 49,
            changes=[(49, i % 11, i // 11, 6) for i in range(121)],
            extra=[(0x48C74C + 129 * 6, 7 | (777 << 16))],
            commands=('call summon',), ghost=True)
    process.stdin.close()
    process.wait()
    scenarios = sum(groups.values())
    report = dict(original_sha256=HASH, scenarios=scenarios, passed=scenarios-len(failures),
                  groups=groups, failures=failures, safety_exceptions=safety_exceptions,
                  skipped_original_calls=sorted(skipped),
                  limits='Isolated original builders/state writes. VCL text layout and audio are not '
                         'emulated. Zeno load behavior is covered by save-report.json; full trap '
                         'playback and overflow-length combat by core_tests.cpp. 49F compares only '
                         'the written commands, explicitly excluding the reproduced unsafe ghost.')
    (ROOT / 'baseline/quirk-report.json').write_text(json.dumps(report, indent=2) + '\n', encoding='utf-8')
    print(f'{report["passed"]}/{scenarios} correction-log scenarios passed')
    print(json.dumps(failures[:5], indent=2))
    return bool(failures)


if __name__ == '__main__':
    sys.exit(main())
