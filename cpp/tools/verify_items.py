"""Compare active item builders and Flight callbacks with the pinned x86 game.

Items execute the published confirmation callback (0x450BA0) from entry to
return, including its setup and exception epilogue. Reviewed gameplay helpers are followed;
skipped VCL and runtime calls are disclosed in the report.
"""
from pathlib import Path
import argparse
import hashlib
import json
import subprocess
import sys

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / 'tools'))
from original_event_probe import RAW, pe, probe
from differential import HASH
from verify_interactions import HERO, FIELDS
from comparison_boundary import check_skipped_calls

FOLLOW = [0x451C20, 0x451B98, 0x44BC34, 0x451D3C, 0x4660D0, 0x442F80, 0x443050, 0x47C8F8,
          0x442C38, 0x454C10]


def main():
    (ROOT / 'build/cpp/reports').mkdir(parents=True, exist_ok=True)
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--probe', type=Path, default=ROOT / 'build/cpp/vs/Release/tsw_probe.exe')
    args = parser.parse_args()
    if hashlib.sha256(pe.__data__).hexdigest() != HASH:
        raise RuntimeError('Original image hash mismatch')
    scenarios = []

    def add(name, item, floor=1, x=5, y=5, changes=(), values=None, cpp=(), extra=(), destination=None):
        scenarios.append((name, item, floor, x, y, list(changes), values or {}, list(cpp), list(extra), destination))

    # Every byte value, with a diagonal control that must remain untouched.
    for item in (5, 6, 11):
        for tile in range(256):
            changes = [(1, i % 11, i // 11, 6) for i in range(121)]
            changes += [(1, 5, 4, tile), (1, 6, 6, 8)]
            add(f'item/{item}/tile/{tile}', item, changes=changes)
        for y in range(11):
            for x in range(11):
                tile = 8 if item == 5 else 61 if item == 6 else 13
                changes = [(1, i % 11, i // 11, tile) for i in range(121)] + [(1, x, y, 6)]
                add(f'item/{item}/edge/{x}/{y}', item, x=x, y=y, changes=changes)
    for cycle in (0, 43):
        for attack, defense in ((10, 10), (157, 191), (0, 1)):
            add(f'elixir/{cycle}/{attack}/{defense}', 4, values={'attack': attack, 'defense': defense, 'cycle': cycle})
        for lucky in (0, 1):
            changes = [(1, i % 11, i // 11, 6) for i in range(121)]
            changes += [(1, 5, 4, 95), (1, 4, 5, 145), (1, 6, 5, 91), (1, 5, 6, 133)]
            add(f'bomb/mixed/{cycle}/{lucky}', 6, changes=changes, values={'cycle': cycle, 'gold': 1000},
                extra=[(HERO + 68 + 14 * 4, lucky)], cpp=[f'item 14 {lucky}'])
    for y in range(11):
        for x in range(11):
            for tile in (6, 8):
                target = 120 - y * 11 - x
                add(f'warp/{x}/{y}/{tile}', 7, x=x, y=y, changes=[(1, target % 11, target // 11, tile)])
    for floor in range(51):
        for item in (8, 9):
            target = floor + (1 if item == 8 else -1)
            for tile in (6, 8):
                changes = [(target, 5, 5, tile)] if 0 <= target <= 50 else []
                add(f'wing/{floor}/{item}/{tile}', item, floor=floor, changes=changes)
    for item, tile in ((12, 1), (13, 8)):
        for spacing in (1, 3, 17, 122):
            changes = [(1, i % 11, i // 11, tile if i % spacing == 0 else 6) for i in range(121)]
            add(f'whole-floor/{item}/{spacing}', item, changes=changes)
    for highest in (29, 50):
        for floor in range(1, highest + 1):
            if floor == 44:
                continue
            for direction in (0, 1, 2):
                for stair in (1, 2):
                    add(f'flight/{highest}/{floor}/{direction}/{stair}', 2, floor=floor,
                        values={'highest': highest, 'music': 5},
                        extra=[(HERO + 632, direction), (HERO + 664, stair)],
                        cpp=[f'set flight_direction {direction}', f'set highest_stair {stair}'], destination=floor)
    # Preview has the original upward-only 35F thief side effect. The modern
    # desktop keeps the selected floor in UI state instead of mutating hero.floor.
    for direction, address, source in ((1, 0x44ED94, 34), (2, 0x44ED1C, 36)):
        for thief in (21, 6):
            add(f'preview/{direction}/{thief}', -address, floor=source,
                changes=[(35, 3, 8, thief), (2, 10, 10, 6)], values={'highest': 50},
                cpp=[f'preview 35 {direction}'], destination=35)

    process = subprocess.Popen([str(args.probe)], stdin=subprocess.PIPE, stdout=subprocess.PIPE, text=True)
    skipped, failures, groups = set(), [], {}
    watched = [HERO + 68 + 4 * i for i in range(15)] + [HERO + o for o in (352, 360, 632, 664)]
    for name, item, floor, x, y, changes, values, cpp, extra, destination in scenarios:
        globals = [(HERO + 664, 2)] + [(HERO + FIELDS[k], v) for k, v in values.items()] + extra + [(HERO + 352, 4)]
        lines = ['original', f'set floor {floor}', f'set x {x}', f'set y {y}', 'set facing 4', 'set highest_stair 2']
        lines += [f'tile {f} {ty * 11 + tx} {t}' for f, tx, ty, t in changes]
        lines += [f'set {k} {v}' for k, v in values.items()] + cpp
        if item < 0:
            original = probe(-item, floor, x, y, changes, globals=globals,
                             include_presentation=True, follow_calls=FOLLOW, watch_globals=watched)
            group = 'flight-preview'
        elif item == 2:
            original = probe(0x44EAF4, floor, x, y, changes, globals=globals,
                             include_presentation=True, follow_calls=FOLLOW, watch_globals=watched)
            lines += ['item 2 1', f'flight_confirm {destination}']
            group = 'flight-confirm'
        else:
            globals += [(HERO + 68 + item * 4, 1), (0x48C574, item + 1)]
            original = probe(0x450BA0, floor, x, y, changes, globals=globals,
                             include_presentation=True, follow_calls=FOLLOW, watch_globals=watched)
            lines += [f'item {item} 1', f'use {item}']
            group = f'item-{item}'
        skipped.update(original['calls'])
        process.stdin.write('\n'.join(lines + ['snapshot']) + '\n')
        process.stdin.flush()
        actual = json.loads(process.stdout.readline())
        if 'error' in actual:
            raise RuntimeError((name, actual))
        diff = []
        if actual['queue'] != original['queue']:
            left, right = actual['queue'], original['queue']
            index = next((i for i, (a, b) in enumerate(zip(left, right)) if a != b), min(len(left), len(right)))
            diff.append(dict(queue_index=index, cpp=left[index:index + 3], original=right[index:index + 3], lengths=[len(left), len(right)]))
        for slot in (*range(12), 14, 15, 16):
            if item < 0 and slot == 4:
                continue  # Intentional GUI separation of preview floor and hero floor.
            if actual['hero'][slot] != original['stat_slots'][slot]:
                diff.append(dict(slot=slot, cpp=actual['hero'][slot], original=original['stat_slots'][slot]))
        for i, value in enumerate(actual['items']):
            if item == 2 and i == 2:
                continue  # Original confirm callback does not read possession.
            expected = original['watched_globals'][hex(HERO + 68 + 4 * i)]
            if value != expected:
                diff.append(dict(item=i, cpp=value, original=expected))
        for i, offset in enumerate((632, 664, 352)):
            expected = original['watched_globals'][hex(HERO + offset)]
            if actual['flight'][i] != expected:
                diff.append(dict(flight=i, cpp=actual['flight'][i], original=expected))
        expected = [list(RAW[f * 123 + 2:(f + 1) * 123]) for f in range(51)]
        for f, tx, ty, t in changes + original['changed']:
            if 0 <= tx < 11 and 0 <= ty < 11:
                expected[f][ty * 11 + tx] = t
        if actual['maps'] != expected:
            diff.append(dict(map_mismatch=[(f, i, actual['maps'][f][i], expected[f][i]) for f in range(51) for i in range(121) if actual['maps'][f][i] != expected[f][i]][:4]))
        if diff:
            failures.append(dict(scenario=name, differences=diff))
        groups[group] = groups.get(group, 0) + 1
    process.stdin.close()
    process.wait()
    boundary = check_skipped_calls(skipped)
    report = dict(original_sha256=HASH, scenarios=len(scenarios), passed=len(scenarios) - len(failures), groups=groups,
                  failures=failures, skipped_original_calls=sorted(skipped),
                  boundary_audit=boundary,
                  limits='Full published item-confirmation callback and isolated Flight callbacks; caller eligibility is not established here. Effectful map redraw is followed. Preview floor stays in modern UI state. Full Flight inputs are checked by verify_flight.py; rendering/device/string behavior is excluded.')
    output = ROOT / 'build/cpp/reports/item-report.json'
    output.write_text(json.dumps(report, indent=2) + '\n', encoding='utf-8')
    print(f'{report["passed"]}/{report["scenarios"]} matched; {output}')
    print(json.dumps(failures[:6], indent=2))
    return bool(failures or boundary['unreviewed_calls'] or boundary['effectful_skips'])


if __name__ == '__main__':
    sys.exit(main())
