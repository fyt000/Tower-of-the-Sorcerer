"""Audit special-road coverage and scene builders in the installed original.

Read-only x86 probes; no original Windows process or UI is launched. Run after
extract_original_events.py. Requires pefile, capstone and unicorn. The report
separates every initialized special-road trigger from hand-authored/helper
scene translations, and retains skipped calls as a boundary of the evidence.
"""
import hashlib
import json
from collections import Counter
from original_event_probe import ROOT, RAW, pe, probe
from unicorn.x86_const import UC_X86_REG_EBP, UC_X86_REG_EBX, UC_X86_REG_ESI


def summary(result):
    return {
        'queue_records':len(result['queue']),
        'opcode_counts':{str(op):n for op,n in sorted(Counter(q[0] for q in result['queue']).items())},
        'called_helpers_not_executed':result['calls'],
    }


def main():
    events=json.loads((ROOT/'data/events.json').read_text(encoding='utf-8'))
    floors=[]
    for floor in range(51):
        sites=[]
        for index,tile in enumerate(RAW[floor*123+2:(floor+1)*123]):
            if tile!=7:continue
            x,y=index%11,index//11
            matches=[e['id'] for e in events if e['trigger']['type']=='step'
                     and e['trigger'].get('floor')==floor
                     and e['trigger'].get('x')==x and e['trigger'].get('y')==y]
            assert matches,(floor,x,y,'Unconfigured original special road')
            address=0x46397c if floor in [3,23] else 0x46cb1c
            original=probe(address,floor,x,y,include_presentation=True)
            sites.append({'x':x,'y':y,'builder':hex(address),
                          'configured_events':matches,**summary(original)})
        floors.append({'floor':floor,'special_road_sites':sites,
                       'configured_event_count':sum(e['trigger'].get('floor')==floor for e in events)})

    capture=probe(0x464048,3,4,8,include_presentation=True)
    materialization=probe(0x461a0c,3,4,8,include_presentation=True,globals=[(0x48c558,70)])
    skeleton=probe(0x46cb1c,10,5,4,include_presentation=True)
    vampire=probe(0x46cb1c,20,5,7,include_presentation=True)
    sorcerers=probe(0x462560,49,5,5,include_presentation=True)
    ending=probe(0x4463a1,50,5,4,end=0x448fbc,include_presentation=True,
        globals=[(0x6ffdfc,0x200000)],
        registers=[(UC_X86_REG_EBP,0x6ffe00),(UC_X86_REG_EBX,0x48c5ac),(UC_X86_REG_ESI,0x48c74c)])
    ending_stages={}
    for i,record in enumerate(ending['queue']):
        if record[:2]!=[11,12]:continue
        following=ending['queue'][i+1]
        assert following[0]==0
        ending_stages.setdefault(str(following[1]),[]).append(record[2])
    capture_parameters=[q[2] for q in capture['queue'] if q[:2]==[11,12]]
    assert capture_parameters[:16]==list(range(232,248))
    assert capture_parameters[17:-1]==list(range(100,406))
    assert [q[2] for q in materialization['queue'] if q[0]==9]==list(range(166,183))
    assert sum(q[0]==12 for q in skeleton['queue'])==43
    assert [q[2] for q in vampire['queue'] if q[:2]==[11,4]]==list(range(1,33))
    sorcerer_targets=[15,16,17,28,39,38,37,26]
    sorcerer_masks=[167,169,171,173,175,177,179,182]
    assert [(q[1],q[2]) for q in sorcerers['queue'] if q[0]==9]==[
        (target,mask) for mask in sorcerer_masks for target in sorcerer_targets]
    report={
        'source':'Installed English Tower of the Sorcerer Windows v1.2; isolated executable emulation',
        'executable_sha256':hashlib.sha256(pe.__data__).hexdigest(),
        'floors_reviewed':51,'configured_event_count':len(events),
        'initialized_special_road_sites':sum(len(f['special_road_sites']) for f in floors),
        'floors':floors,
        'capture_opening2':{'builder':'0x464048',**summary(capture),
            'title_dither_parameters':capture_parameters[:16],
            'text_scan_parameters':{'from':100,'through':405,'frames':306},
            'sound_counts':dict(Counter(str(q[1]) for q in capture['queue'] if q[0]==1))},
        'capture_materialization':{'builder':'0x461a0c','target_index':70,
            'color_tile':91,'mask_tiles':list(range(166,183)),**summary(materialization)},
        'skeleton_march':{'builder':'0x46cb1c','floor':10,'tile_movements':43,**summary(skeleton)},
        'vampire_transformation':{'builder':'0x46cb1c','floor':20,'original_frames':list(range(1,33)),**summary(vampire)},
        'decoy_sorcerer_materialization':{'builder':'0x462560','floor':49,
            'targets':sorcerer_targets,'color_tile':93,
            'mask_tiles':sorcerer_masks,**summary(sorcerers)},
        'first_cycle_ending':{'builder':'0x4463a1..0x448fbc',**summary(ending),
            'scene_stages':{stage:{'frames':len(values),'first':values[0],'last':values[-1]} for stage,values in ending_stages.items()},
            'sound_counts':dict(Counter(str(q[1]) for q in ending['queue'] if q[0]==1)),
            'remake':'Compact modern victory/credits timeline followed by the verified replay reset; exact original ending raster composition is not yet reproduced.'},
        'fidelity_boundaries':[
            'Coverage of all initialized tile-7 sites does not prove every possible later map state or NPC callback.',
            'Floor-24 portal and floor-43 door trap are dynamically created or differently typed and have dedicated event scenarios.',
            'Capture and materialization helpers have been inspected separately; reported calls are otherwise skipped.',
            'Durations are configurable. Original Delphi timer tick scheduling and Windows timer granularity are not emulated.',
            'Fairy score/rank tables, exact ending raster artwork sequence and a natural complete first-cycle route remain unverified.'
        ]}
    (ROOT/'data/original-event-audit.json').write_text(json.dumps(report,ensure_ascii=False,indent=2)+'\n',encoding='utf-8',newline='\n')
    print(f"Reviewed 51 floors, {report['initialized_special_road_sites']} special-road sites and {len(events)} configured events")


if __name__=='__main__':main()
