"""Original-machine differential checks for NPCs, stairs, hazards and continuations."""
from pathlib import Path
import argparse, hashlib, json, subprocess, sys

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0,str(ROOT/'tools'))
from original_event_probe import probe, pe, RAW
from audit_original_items import CLUE_OFFSETS
from verify_interactions import HERO, FIELDS
from differential import HASH
from comparison_boundary import check_skipped_calls

def main():
    (ROOT / 'build/cpp/reports').mkdir(parents=True, exist_ok=True)
    p=argparse.ArgumentParser(description=__doc__)
    p.add_argument('--probe',type=Path,default=ROOT/'build/cpp/vs/Release/tsw_probe.exe')
    args=p.parse_args()
    if hashlib.sha256(pe.__data__).hexdigest() != HASH: raise RuntimeError('Original image hash mismatch')
    process=subprocess.Popen([str(args.probe)],stdin=subprocess.PIPE,stdout=subprocess.PIPE,text=True)
    scenarios=[];failures=[];skipped=set();groups={}
    def add(name,kind,floor,changes=(),values=None,extra=(),cpp=(),address=0x444490):
        scenarios.append((name,kind,floor,list(changes),values or {},list(extra),list(cpp),address))
    for f in (2,3,4,6,16,18,21,23,27,31,33,36,37,39,42,45,46,48):
        for orb in (0,1):
            for x in ((1,9) if f==16 else (5,)):
                add(f'oldman/{f}/{orb}/{x}','oldman',f,[(f,5,4,25)],{'x':x},[(HERO+72,orb)],[f'item 1 {orb}'])
    for f in (2,6,7,12,15,28,31,38,39,45,47):
        for x in ((1,9) if f==12 else (5,)):
            add(f'trade/{f}/{x}','trade',f,[(f,5,4,19)],{'x':x,'gold':10000,'yellow':1})
    for f in (1,10,11,20,21,31,41):
        for n in (0,3):
            for choice,address in enumerate((0x451E1C,0x4520B4,0x452360)):
                for cycle in (0,43):
                    cost=10*(n*n+n+2)
                    add(f'altar/{f}/{n}/{choice}/{cycle}','altar',f,[(f,5,4,16)],{'altar':n,'gold':100000,'cycle':cycle},[(0x48C594,cost)],['call contact',f'choose {choice}'],address)
    for stage in range(0,73):
        add(f'continue/{stage}','continue',2,extra=[(0x48C5A4,stage)],cpp=[f'continue {stage}'],address=0x44DA10)
    for f in range(1,50):
        for tile in (11,12):
            # Arrival into 32/42 invokes a separately verified floor script.
            add(f'stair/{f}/{tile}','stair',f,[(f,5,4,tile)],{'highest':f})
    for f in (1,47):
        for cycle in (0,43):
            for shield in (0,1):
                for t in (151,152,153,154,93):
                    changes=[(f,i%11,i//11,6) for i in range(121)]
                    changes += [(f,5,3,t),(f,4,4,t),(f,6,4,t),(f,5,5,t)]
                    add(f'hazard/{f}/{cycle}/{shield}/{t}','hazard',f,changes,{'hp':10000,'cycle':cycle},[(HERO+164,shield)],[f'equipment 9 {shield}'])
    # First-cycle contact builds the entire ending raster stack.
    add('ending/first-cycle','ending',50,[(50,5,4,91)])
    # Isolate the Fairy with default temporary ranking tables; user .dat files
    # and VCL strings are deliberately outside this oracle.
    for floor in (10,20,25,40,49):
        for cycle in (0,43):
            for music in (0,5):
                for hp,attack,defense in ((400,10,10),(1000,100,100),(10000,1000,800),(499,24,26)):
                    add(f'fairy/{floor}/{cycle}/{music}/{hp}','fairy',floor,[(floor,5,4,23)],
                        {'hp':hp,'attack':attack,'defense':defense,'cycle':cycle,'music':music},address=0x478F0C)
    follow=[0x4660D0,0x449708,0x449014,0x44C04C,0x44C464,0x44C5C4,0x44C9F0,
            0x47BEAC,0x442DC8,0x442F80,0x443050,0x46397C,0x46CB1C,0x461A0C,0x461EF4,0x464048,
            0x442C38,0x454C10,0x449E18]
    watched=[HERO+68+4*i for i in range(15)]+[HERO+128+4*i for i in range(10)]
    watched += [HERO+320+4*i for i in range(11,68)]+[HERO+o for o in CLUE_OFFSETS]+[HERO+168+4*i for i in range(12)]+[HERO+264,HERO+268,HERO+284,HERO+340,HERO+344,HERO+352,HERO+360,HERO+664]
    for name,kind,f,changes,values,extra,cpp,address in scenarios:
        x,y=values.get('x',5),values.get('y',5)
        globals=[(HERO+FIELDS[k],v) for k,v in values.items()]+extra+[(HERO+352,4),(HERO+664,2),(0x48C584,49)]
        original=probe(address,f,x,y,changes,globals=globals,include_presentation=True,follow_calls=follow,watch_globals=watched)
        skipped.update(original['calls'])
        lines=['original',f'set floor {f}',f'set x {x}',f'set y {y}','set facing 4','set contact 49','set highest_stair 2']
        lines += [f'tile {f} {y*11+x} {t}' for f,x,y,t in changes]+[f'set {k} {v}' for k,v in values.items()]
        lines += [c for c in cpp if not c.startswith('choose') and c!='call contact']
        lines += [] if kind=='continue' else ['call contact']
        lines += [c for c in cpp if c.startswith('choose')]
        lines += ['choose 0'] if kind=='trade' else []
        if kind=='trade':
            # The UI accept callback is independent: seed its captured offer inputs.
            # syounin writes these globals; reproduce its capture in a second probe.
            captured=probe(0x449014,f,x,y,changes,globals=globals,watch_globals=[0x48C598,0x48C594,0x48C5CC])
            original=probe(0x44E1CC,f,x,y,changes,globals=globals+[(int(a,16),v) for a,v in captured['watched_globals'].items()],include_presentation=True,watch_globals=watched)
            skipped.update(original['calls'])
        lines += ['snapshot'];process.stdin.write('\n'.join(lines)+'\n');process.stdin.flush()
        actual=json.loads(process.stdout.readline());diff=[]
        if 'error' in actual:raise RuntimeError((name,actual))
        if actual['queue']!=original['queue']:
            left,right=actual['queue'],original['queue'];index=next((i for i,(a,b) in enumerate(zip(left,right)) if a!=b),min(len(left),len(right)))
            diff.append(dict(index=index,cpp=left[index:index+3],original=right[index:index+3],lengths=[len(left),len(right)]))
        for i in (*range(12),14,15,16):
            if actual['hero'][i]!=original['stat_slots'][i]:diff.append(dict(slot=i,cpp=actual['hero'][i],original=original['stat_slots'][i]))
        for field,offsets in [('items',[68+4*i for i in range(15)]),('equipment',[128+4*i for i in range(10)]),('hints',CLUE_OFFSETS),('merchant_used',[168+4*i for i in range(12)]),('old_man_heard',[264,268,284])]:
            for i,o in enumerate(offsets):
                value=original['watched_globals'][hex(HERO+o)]
                if actual[field][i]!=value:diff.append(dict(field=field,index=i,cpp=actual[field][i],original=value))
        for i in range(11,68):
            value=original['watched_globals'][hex(HERO+320+4*i)]
            if actual['flags'][i]!=value:diff.append(dict(flag=i,cpp=actual['flags'][i],original=value))
        value=original['watched_globals'][hex(HERO+664)]
        if actual['flight'][1]!=value:diff.append(dict(highest_stair=actual['flight'][1],original=value))
        expected=[list(RAW[f*123+2:(f+1)*123]) for f in range(51)]
        for f,x,y,t in changes+original['changed']:
            if 0<=x<11 and 0<=y<11:expected[f][y*11+x]=t
        if actual['maps']!=expected:diff.append({'map_mismatch':[(f,i,actual['maps'][f][i],expected[f][i]) for f in range(51) for i in range(121) if actual['maps'][f][i]!=expected[f][i]][:4]})
        if kind=='fairy':
            for i,offset in enumerate((340,344)):
                value=original['watched_globals'][hex(HERO+offset)]
                if actual['fairy'][i]!=value:diff.append(dict(fairy=i,cpp=actual['fairy'][i],original=value))
            if not actual['fairy'][3]:diff.append(dict(checkpoint_requested=False))
            value=original['watched_globals'][hex(HERO+360)]
            if actual['music']!=value:diff.append(dict(music=actual['music'],original=value))
        if diff:failures.append(dict(scenario=name,differences=diff))
        groups[kind]=groups.get(kind,0)+1
    process.stdin.close();process.wait()
    boundary=check_skipped_calls(skipped)
    report=dict(original_sha256=hashlib.sha256(pe.__data__).hexdigest(),scenarios=len(scenarios),passed=len(scenarios)-len(failures),groups=groups,failures=failures,skipped_original_calls=sorted(skipped),boundary_audit=boundary,limits='Isolated builder/state comparisons. Effectful map redraw and dialogue display followed; excluded VCL/RTL calls explicitly audited. Fairy user ranking files and rendering are outside scope.')
    (ROOT/'build/cpp/reports/callback-report.json').write_text(json.dumps(report,indent=2)+'\n',encoding='utf-8')
    print(f'{report["passed"]}/{report["scenarios"]} matched')
    print(json.dumps(failures[:5],indent=2));return bool(failures or boundary['unreviewed_calls'] or boundary['effectful_skips'])

if __name__=='__main__':sys.exit(main())
