"""Audit special-road coverage and scene builders in the installed original.

Read-only x86 probes; no original Windows process or UI is launched. Run after
extract_original_events.py. Requires pefile, capstone and unicorn. The report
separates every initialized special-road trigger from hand-authored/helper
scene translations, and retains skipped calls as a boundary of the evidence.
"""
import hashlib
import json
import struct
import capstone
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
    # Enumerate incoming paths before checking map sites. A complete initial
    # tile-7 scan cannot discover handlers reached only by stairs or movement.
    expected_callers={
        0x46397c:[0x4447d5,0x444ea0,0x444ec4],
        0x46cb1c:[0x463bff,0x463c31,0x463c91,0x463e34,0x463e8b,0x463ebd,
                  0x463ec9,0x463efb,0x463f2d,0x463f84,0x463f90,0x463fc2,
                  0x463fcb,0x46401f],
        0x4664e4:[0x4533eb],
        0x44c5c4:[0x44c258,0x44c298,0x44c2d7,0x44c318],
        0x47beac:[0x44468f],
    }
    callers={target:[] for target in expected_callers}
    decoder=capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_32)
    decoder.skipdata=True
    code=next(s for s in pe.sections if s.Name.rstrip(b'\0')==b'CODE')
    for address,_,mnemonic,operand in decoder.disasm_lite(
            code.get_data(),pe.OPTIONAL_HEADER.ImageBase+code.VirtualAddress):
        if mnemonic=='call' and operand.startswith('0x') and int(operand,16) in callers:
            callers[int(operand,16)].append(address)
    assert callers==expected_callers, 'Review every new event-handler entry path'
    floors=[]
    for floor in range(51):
        sites=[]
        for index,tile in enumerate(RAW[floor*123+2:(floor+1)*123]):
            if tile!=7:continue
            x,y=index%11,index//11
            matches=[e['id'] for e in events if e['trigger']['type']=='step'
                     and e['trigger'].get('floor')==floor
                     and ((e['trigger'].get('x')==x and e['trigger'].get('y')==y)
                          or {'x':x,'y':y} in e['trigger'].get('positions',[]))]
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
    # Initial special-road coverage excludes callbacks reached through stairs
    # and ordinary movement. Probe the actual stair branch with its once flags.
    arrivals=[]
    for floor,flag,event_id in [(32,0x4b88f4,'floor_32_golden_knight_arrival'),
                                (42,0x4b8894,'floor_42_zeno_and_golden_knight_arrival')]:
        event=next(e for e in events if e['id']==event_id)
        assert event['trigger']=={'type':'stairs_up','floor':floor}
        cases=[]
        for already_seen in [0,1]:
            original=probe(0x444e8b,floor,5,9,end=0x444ed3,
                globals=[(0x6ffdfc,0x200000),(flag,already_seen)],
                registers=[(UC_X86_REG_EBP,0x6ffe00),(UC_X86_REG_EBX,0x48c5ac),(UC_X86_REG_ESI,0x48c74c)],
                follow_calls=[0x46397c,0x46cb1c],include_presentation=True,watch_globals=[flag])
            assert original['watched_globals'][hex(flag)]==1
            assert bool(original['queue']) == (not bool(already_seen))
            if not already_seen:
                assert original['followed_calls']==['0x46397c','0x46cb1c']
                if floor==32:
                    assert [11,10,104] in original['queue']
                    assert sum(q[0]==12 for q in original['queue'])==13
                else:
                    assert [q[1] for q in original['queue'] if q[0]==10]==[41,42,43,44]
            cases.append({'already_seen':bool(already_seen),
                'once_flag_after':original['watched_globals'][hex(flag)],**summary(original)})
        arrivals.append({'floor':floor,'builder':'0x444e8b..0x444ed3',
            'once_flag':hex(flag),'configured_event':event_id,'cases':cases})
    assert 133 not in RAW[32*123+2:33*123], 'The 32F Knight is created by the arrival event'
    knight_retreat=probe(0x4664e4,32,5,9,include_presentation=True,
        globals=[(0x4b8868,1)],changes=[(29,6,1,21)])
    assert sum(q[0]==12 for q in knight_retreat['queue'])==13
    assert [10,31,0] in knight_retreat['queue']
    assert [2,10,10,21] in [list(change) for change in knight_retreat['changed']]
    assert [29,6,1,6] in [list(change) for change in knight_retreat['changed']]
    knight_40=probe(0x46cb1c,40,5,6,include_presentation=True)
    last_battle=max(i for i,q in enumerate(knight_40['queue']) if q[:2]==[11,10])
    retreat_40=[q for q in knight_40['queue'][last_battle+1:] if q[0]==12]
    assert retreat_40==[[12,71,60],[12,60,49],[12,49,38],[12,38,27],[12,27,16]]
    guards_42=probe(0x461ef4,42,5,9,include_presentation=True,
        globals=[(0x48c558,71),(0x48c55c,93),(0x48c560,81),(0x48c564,83)])
    assert [(q[1],q[2]) for q in guards_42['queue'] if q[0]==9]==[
        (target,mask) for mask in [167,169,171,175,182] for target in [71,93,81,83]]
    execution_42=probe(0x46cb1c,42,5,9,include_presentation=True)
    execution_index=execution_42['queue'].index([9,82,183])
    assert execution_42['queue'][execution_index+1]==[0,133,184]
    execution_effect=next(e for e in events if e['id']=='floor_42_zeno_and_golden_knight_arrival')
    execution_effect=next(e for e in execution_effect['effects'] if e.get('frames')==[183])
    assert (execution_effect['underlying_tile'],execution_effect['color_tile'])==(133,184)
    portal=probe(0x46cb1c,24,5,0,include_presentation=True)
    portal_index=portal['queue'].index([9,49,166])
    assert portal['queue'][portal_index+1]==[0,21,91]
    portal_magic=next(e for e in events if e['id']=='time_gate_to_floor_50')
    portal_magic=next(e for e in portal_magic['effects'] if e.get('kind')=='magic')
    assert (portal_magic['underlying_tile'],portal_magic['color_tile'])==(21,91)
    movement_call_sites=[0x44c258,0x44c298,0x44c2d7,0x44c318]
    image=pe.get_memory_mapped_image()
    for site in movement_call_sites:
        assert image[site-0x400000]==0xe8
        assert site+5+struct.unpack_from('<i',image,site-0x400000+1)[0]==0x44c5c4
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
        'direct_handler_callers':{
            'mevent':{'helper':'0x46397c','call_sites':[hex(site) for site in callers[0x46397c]],
                'entry_paths':['special-road movement','32F upstairs arrival','42F upstairs arrival']},
            'ichicheck':{'helper':'0x46cb1c','call_sites':[hex(site) for site in callers[0x46cb1c]],
                'entry_paths':['mevent floor/position dispatch']},
            'moncheck':{'helper':'0x4664e4','call_sites':[hex(site) for site in callers[0x4664e4]],
                'entry_paths':['successful battle completion']},
            'mazyutu1':{'helper':'0x44c5c4','call_sites':[hex(site) for site in callers[0x44c5c4]],
                'entry_paths':['four ordinary movement neighbor checks']},
            'doorcheck':{'helper':'0x47beac','call_sites':[hex(site) for site in callers[0x47beac]],
                'entry_paths':['keyed-door attempts, including refusal without a key']},
        },
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
        'stair_arrival_scenes':arrivals,
        'floor_32_knight_retreat':{'builder':'0x46903b','successful_battle_predicate_slot':'0x4b8868',
            'tile_movements':13,'changed':[list(change) for change in knight_retreat['changed']],**summary(knight_retreat)},
        'floor_40_knight_retreat':{'builder':'0x473961','forced_battles':13,'retreat_movements':retreat_40},
        'floor_42_guard_materialization':{'builder':'0x461ef4','targets':[71,93,81,83],
            'mask_tiles':[167,169,171,175,182],**summary(guards_42)},
        'magic_operand_records':[
            {'floor':42,'target_index':82,'mask_tile':183,'underlying_tile':133,'color_tile':184},
            {'floor':50,'target_index':49,'mask_tiles':list(range(166,183)),
                'underlying_tile':21,'color_tile':91,'entry_floor':24},
        ],
        'movement_hazard_callback':{'helper':'0x44c5c4',
            'direct_call_sites':[hex(site) for site in movement_call_sites],
            'scope':'Ordinary movement neighbor checks; separate from special roads. Floor-47 retreat variants are checked by audit_original_mechanics.py.'},
        'first_cycle_ending':{'builder':'0x4463a1..0x448fbc',**summary(ending),
            'scene_stages':{stage:{'frames':len(values),'first':values[0],'last':values[-1]} for stage,values in ending_stages.items()},
            'sound_counts':dict(Counter(str(q[1]) for q in ending['queue'] if q[0]==1)),
            'remake':'Compact modern victory/credits timeline followed by the verified replay reset; exact original ending raster composition is not yet reproduced.'},
        'fidelity_boundaries':[
            'Coverage of all initialized tile-7 sites does not prove every possible later map state or NPC callback.',
            'The 32F and 42F stair callbacks and movement hazard helper are audited separately from the initial map scan.',
            'Floor-24 portal and floor-43 door trap are dynamically created or differently typed and have dedicated event scenarios.',
            'Capture and materialization helpers have been inspected separately; reported calls are otherwise skipped.',
            'Durations are configurable. Original Delphi timer tick scheduling and Windows timer granularity are not emulated.',
            'Fairy score/rank tables, exact ending raster artwork sequence and a natural complete first-cycle route remain unverified.'
        ]}
    (ROOT/'data/original-event-audit.json').write_text(json.dumps(report,ensure_ascii=False,indent=2)+'\n',encoding='utf-8',newline='\n')
    print(f"Reviewed 51 floors, {report['initialized_special_road_sites']} special-road sites and {len(events)} configured events")


if __name__=='__main__':main()
