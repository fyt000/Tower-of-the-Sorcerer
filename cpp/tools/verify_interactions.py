"""Compare contact writes and combat playback records with the original x86 image.

The combat comparison expands the C++ lazy strike generator through run_one().
It stops at the original post-combat callback; it does not emulate VCL drawing.
"""
from pathlib import Path
import argparse
import hashlib
import json
import struct
import subprocess
import sys

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / 'tools'))
from original_event_probe import probe, pe
from differential import HASH

HERO = 0x4B8688
FIELDS = dict(hp=0, attack=4, defense=8, gold=12, floor=16, highest=20,
              x=24, y=28, yellow=32, red=36, blue=40, altar=44, facing=352,
              cycle=636, later=640, music=360)
FOLLOW = [0x4660D0, 0x44C04C, 0x44C464, 0x44C5A4, 0x44C9F0,
          0x450064, 0x45031C, 0x450360, 0x450288, 0x4502D0, 0x4503A8,
          0x48028C, 0x4802FC, 0x480340, 0x47BEAC, 0x461A0C]

def comparable(queue):
    result = []
    for op, a, b in queue:
        # These b operands are not read by the Delphi interpreter. Some builders
        # leave them untouched, so the executable retains stale buffer contents.
        if op in (5, 7): b = 0
        result.append([op, a, b])
        if op == 3 or (op == 11 and a == 5): break
    return result

def main():
    (ROOT / 'build/cpp/reports').mkdir(parents=True, exist_ok=True)
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--probe', type=Path, default=ROOT/'build/cpp/vs/Release/tsw_probe.exe')
    args = parser.parse_args()
    if hashlib.sha256(pe.__data__).hexdigest() != HASH: raise RuntimeError('Original image hash mismatch')
    process = subprocess.Popen([str(args.probe)], stdin=subprocess.PIPE, stdout=subprocess.PIPE, text=True)
    failures, skipped, counts = [], set(), {}
    scenarios = []
    for f in (1, 12, 47):
        for cycle in (0, 43):
            for t in (1, 2, 3, 6, 9, *range(29, 36), *range(37, 61)):
                scenarios.append((f'contact/{f}/{cycle}/{t}', 'contact', f, t,
                                  dict(hp=100000, attack=100, defense=100, cycle=cycle, yellow=1, red=1, blue=1), []))
    rows = [struct.unpack_from('<4i', pe.get_memory_mapped_image(), 0x489910-0x400000+i*16) for i in range(33)]
    for enemy, (hp, attack, defense, gold) in enumerate(rows):
        t = 61+enemy*2 if enemy < 18 else 104 if enemy == 18 else 122 if enemy == 19 else 93+enemy*2
        for forced in (False, True):
            if forced and enemy in (18, 19): continue  # Forced builder does not classify large monsters.
            for cycle in (0, 43):
                scale = cycle+1
                for hits in (1, 3):
                    hero_attack = defense*scale+(hp*scale+hits-1)//hits
                    for health in (1, max(1, attack*scale), 10000000):
                        values = dict(hp=health, attack=hero_attack, defense=0, cycle=cycle)
                        scenarios.append((f'combat/{enemy}/{forced}/{cycle}/{hits}/{health}', 'forced' if forced else 'battle', 1, t, values, []))
    for enemy in (12, 13, 17, 19):
        for item in (3 if enemy != 19 else 10,):
            for health in (1, 10000000):
                hp, attack, defense, gold = rows[enemy]
                t = 61+enemy*2 if enemy < 18 else 122
                scenarios.append((f'bonus/{enemy}/{health}', 'battle', 1, t,
                                  dict(hp=health, attack=defense+50, defense=0), [(item, 1)]))
    for name, kind, floor, tile, values, items in scenarios:
        globals = [(HERO+FIELDS[k], v) for k, v in values.items()]
        globals += [(HERO+68+4*i, v) for i, v in items]
        globals += [(0x48C584,49), (0x48C756,49), (HERO+352,4)]
        changes = [(floor,i%11,i//11,6) for i in range(121)]+[(floor,5,4,tile)]
        address = 0x444490 if kind == 'contact' else 0x47F7D4 if kind == 'forced' else 0x44A480
        original = probe(address,floor,5,5,changes,globals=globals,include_presentation=True,follow_calls=FOLLOW)
        skipped.update(original['calls'])
        lines = ['original', f'set floor {floor}', 'set x 5', 'set y 5', 'set facing 4', 'set contact 49']
        lines += [f'tile {f} {y*11+x} {t}' for f,x,y,t in changes]
        lines += [f'set {k} {v}' for k,v in values.items()]+[f'item {i} {v}' for i,v in items]
        lines += [f'call battle {int(kind == "forced")}' if kind != 'contact' else 'call contact', 'snapshot']
        process.stdin.write('\n'.join(lines)+'\n'); process.stdin.flush()
        actual = json.loads(process.stdout.readline())
        if 'error' in actual: raise RuntimeError((name,actual))
        cpp_queue = actual['queue']
        if kind != 'contact':
            process.stdin.write('trace 100000\n'); process.stdin.flush()
            cpp_queue = json.loads(process.stdout.readline())
        diff = []
        left, right = comparable(cpp_queue), comparable(original['queue'])
        if left != right:
            index = next((i for i,(a,b) in enumerate(zip(left,right)) if a != b), min(len(left),len(right)))
            diff.append(dict(index=index,cpp=left[index:index+4],original=right[index:index+4],lengths=[len(left),len(right)]))
        for i in (*range(12), 14, 15, 16):
            if actual['hero'][i] != original['stat_slots'][i]:
                diff.append(dict(slot=i,cpp=actual['hero'][i],original=original['stat_slots'][i]))
        if diff: failures.append(dict(scenario=name,differences=diff))
        counts[kind] = counts.get(kind,0)+1
    process.stdin.close(); process.wait()
    report = dict(original_sha256=hashlib.sha256(pe.__data__).hexdigest(),scenarios=len(scenarios),
                  passed=len(scenarios)-len(failures),groups=counts,failures=failures,
                  skipped_original_calls=sorted(skipped),
                  limits='Contact direct hero writes and combat command playback only. Unread b operands of HeroStrike/Reward normalized. VCL calls skipped. No natural tower route asserted.')
    output = ROOT/'build/cpp/reports/interaction-report.json'
    output.write_text(json.dumps(report,indent=2)+'\n',encoding='utf-8')
    print(f'{report["passed"]}/{report["scenarios"]} matched; {output}')
    print(json.dumps(failures[:8],indent=2))
    return bool(failures)

if __name__ == '__main__': sys.exit(main())
