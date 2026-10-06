"""Compare the C++ command builders with the pinned original x86 executable.

Delphi/VCL rendering calls are skipped by the original probe and listed in the
report. The baseline itself is exercised through its compiled probe program.
"""
from pathlib import Path
import argparse, hashlib, json, random, struct, subprocess, sys

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0,str(ROOT/'tools'))
from original_event_probe import probe, pe, RAW

HASH = '41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779'
HERO = 0x4b8688
FIELDS = {'hp':0,'attack':4,'defense':8,'gold':12,'floor':16,'highest':20,'x':24,'y':28,
          'yellow':32,'red':36,'blue':40,'altar':44,'music':360,'facing':352,
          'cycle':636,'later':640,'sealed':624,'reward34':592,'reward35':596,'reward40':600,'reward41':616}
HANDLERS = {'guards':0x4664e4,'floor':0x46cb1c,'door':0x47beac}

def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--probe',type=Path,default=ROOT/'baseline/build-vs/Debug/tos_baseline_probe.exe')
    parser.add_argument('--report',type=Path,default=ROOT/'baseline/differential-report.json')
    args = parser.parse_args()
    if hashlib.sha256(pe.__data__).hexdigest() != HASH: raise RuntimeError('Original image hash mismatch')
    process = subprocess.Popen([str(args.probe)],stdin=subprocess.PIPE,stdout=subprocess.PIPE,text=True)
    skipped = set(); failures = []; passed = 0; scenarios = []
    generator = random.Random(0x12)
    for handler in HANDLERS:
        for floor in range(51):
            scenarios.append((f'{handler}/initial/{floor}',handler,floor,[],{},{}))
            if handler != 'door':
                scenarios.append((f'{handler}/roads/{floor}',handler,floor,[(floor,i%11,i//11,6) for i in range(121)],{},{}))
                for variant in range(3):
                    changes = [(floor,i%11,i//11, generator.choice([0,1,6,6,6,7,8,21,61,93])) for i in range(121)]
                    scenarios.append((f'{handler}/altered/{floor}/{variant}',handler,floor,changes,{'cycle':43 if variant else 0},{26:variant%2,36:variant%2,40:variant%2,41:variant%2}))
    # Read-dependent branches: clear all inspected cells, then restore each one.
    for floor in range(51):
        original = probe(HANDLERS['guards'],floor)
        reads = list({(f,x,y) for f,x,y,_ in original['reads'] if 0 <= x < 11 and 0 <= y < 11})
        cleared = [(f,x,y,6) for f,x,y in reads]
        scenarios.append((f'guards/clear-reads/{floor}','guards',floor,cleared,{},{}))
        for f,x,y in reads:
            changes = cleared+[(f,x,y,RAW[f*123+2+y*11+x])]
            scenarios.append((f'guards/restore/{floor}/{f}/{x}/{y}','guards',floor,changes,{},{}))
    for contact,hand in [(38,14),(14,38)]:
        changes = [(39,i%11,i//11,1) for i in [12,16,34,36,56,58,60]]+[(39,hand%11,hand//11,6)]
        scenarios.append((f'door/clock/{contact}','door',39,changes,{'contact':contact},{}))
    for dead in [False,True]:
        changes = [(49,x,y,6) for x,y in [(5,1),(5,3),(4,2),(6,2)]]
        if dead: changes.append((49,5,2,6))
        scenarios.append((f'guards/seal/{dead}','guards',49,changes,{},{}))
    for name,handler,floor,changes,values,flags in scenarios:
        floor_value = values.get('floor',floor)
        x,y = values.get('x',0),values.get('y',0)
        globals = [(HERO+FIELDS[k],v&0xffffffff) for k,v in values.items() if k in FIELDS]
        globals += [(HERO+320+4*k,v) for k,v in flags.items()]
        if 'contact' in values: globals.append((0x48c584,values['contact']))
        watched = [HERO+320+4*k for k in range(11,68)]+[HERO+v for k,v in FIELDS.items() if k.startswith('reward') or k == 'sealed']
        original = probe(HANDLERS[handler],floor_value,x,y,changes,globals=globals,include_presentation=True,
                         follow_calls=[0x4660d0,0x461a0c,0x461ef4],watch_globals=watched)
        skipped.update(original['calls'])
        lines = ['original',f'set floor {floor}',f'set contact {y*11+x}']
        lines += [f'tile {f} {y*11+x} {t}' for f,x,y,t in changes]
        lines += [f'set {k} {v}' for k,v in values.items()]
        lines += [f'flag {k} {v}' for k,v in flags.items()]
        lines += [f'call {handler}','snapshot']
        process.stdin.write('\n'.join(lines)+'\n'); process.stdin.flush()
        actual = json.loads(process.stdout.readline())
        differences = []
        if actual.get('queue') != original['queue']:
            left,right = actual.get('queue',[]),original['queue']
            index = next((i for i,(a,b) in enumerate(zip(left,right)) if a != b),min(len(left),len(right)))
            differences.append({'queue_index':index,'cpp':left[index:index+3],'original':right[index:index+3],'lengths':[len(left),len(right)]})
        expected = [list(RAW[f*123+2:(f+1)*123]) for f in range(51)]
        for f,x,y,t in changes+original['changed']:
            if 0 <= x < 11 and 0 <= y < 11: expected[f][y*11+x] = t
        if actual.get('maps') != expected:
            differences.append({'map_mismatch':[(f,i,actual['maps'][f][i],expected[f][i]) for f in range(51) for i in range(121) if actual['maps'][f][i] != expected[f][i]][:10]})
        for index in range(11,68):
            value = original['watched_globals'][hex(HERO+320+4*index)]
            if actual['flags'][index] != value: differences.append({'flag':index,'cpp':actual['flags'][index],'original':value})
        for i,key in enumerate(['reward34','reward35','reward40','reward41']):
            value = original['watched_globals'][hex(HERO+FIELDS[key])]
            if actual['reward_flags'][i] != value: differences.append({'field':key,'cpp':actual['reward_flags'][i],'original':value})
        if actual['cycle'][2] != original['watched_globals'][hex(HERO+FIELDS['sealed'])]: differences.append({'field':'sealed'})
        for index,row in original['monster_changes']:
            if actual['monsters'][index] != row: differences.append({'monster':index,'cpp':actual['monsters'][index],'original':row})
        if differences: failures.append({'scenario':name,'differences':differences})
        else: passed += 1
        if (passed+len(failures))%100 == 0: print(f'{passed} passed, {len(failures)} failed',flush=True)
    process.stdin.close(); process.wait()
    report = {'original_sha256':HASH,'probe':str(args.probe),'scenarios':len(scenarios),'passed':passed,'failures':failures,
              'skipped_original_calls':sorted(skipped),
              'limits':'Builder comparison only; rendering/Delphi helpers listed as skipped are not emulated. No complete natural playthrough is asserted.'}
    args.report.write_text(json.dumps(report,indent=2)+'\n',encoding='utf-8')
    print(f'{passed}/{len(scenarios)} matched; report: {args.report}',flush=True)
    if failures: print(json.dumps(failures[:4],indent=2)); return 1
    return 0

if __name__ == '__main__': sys.exit(main())
