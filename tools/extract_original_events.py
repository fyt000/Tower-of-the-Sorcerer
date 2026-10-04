"""Regenerate configurable campaign events from original v1.2 evidence.

Run after extract_original.py. Requires original_event_probe dependencies.
Events are authored translations of observed memory writes and queued
instructions; calls/graphics are not blindly interpreted as gameplay.
Campaign integration is deliberately a separate regeneration step.
"""
import json,pathlib
from original_event_probe import probe, RAW, ROOT

DIALOGUES={s['id']:s['text'] for s in json.loads((ROOT/'data/original-dialogue.json').read_text(encoding='utf-8'))}
TILES=list(RAW)
EVENTS=[]

def tile_effect(f,index,tile):
    return {'type':'set_tile','floor':f,'x':index%11,'y':index//11,'tile':tile}
def tile_condition(f,index,tile):
    return {'type':'tile','floor':f,'x':index%11,'y':index//11,'tile':tile}
def convert(p,f,tiles=None):
    tiles=list(RAW if tiles is None else tiles)
    effects=[];unknown=[]
    for ff,x,y,t in p['changed']:
        tiles[ff*123+2+y*11+x]=t;effects.append(tile_effect(ff,y*11+x,t))
    for opcode,a,b in p['queue']:
        if opcode==10:
            # roujin 0x44A255 decrements the queue ID before TStrings lookup.
            # Fairy records retain the score overlay rather than a string.
            if a not in [16,22,24,40,47]:
                text=DIALOGUES[a-1]
                if a in [5,17,55]:text+=' '+DIALOGUES[{5:57,17:58,55:59}[a]]
                effects.append({'type':'message','text':text,'dialogue_id':a-1,'original_queue_id':a})
        elif opcode in [6,13]:
            t=b if opcode==6 else (4 if b==5 else 8 if b==8 else 6)
            tiles[f*123+2+a]=t;effects.append(tile_effect(f,a,t))
        elif opcode==12:
            t=tiles[f*123+2+a];tiles[f*123+2+a]=6;tiles[f*123+2+b]=t
            effects.extend([tile_effect(f,a,6),tile_effect(f,b,t)])
        elif opcode==17:
            tiles[f*123+2+a]=b;effects.append(tile_effect(f,a,b))
        elif opcode==11 and a==2:
            tiles[f*123+2+27]=91;effects.append(tile_effect(f,27,91))
        elif opcode==11 and a==3:
            for i in [15,16,17,26,28,37,38,39]:
                tiles[f*123+2+i]=93;effects.append(tile_effect(f,i,93))
        elif opcode==11 and a==10:
            effects.append({'type':'battle_at','floor':f,'x':b%11,'y':b//11,'first_strike':True})
            tiles[f*123+2+b]=6
        elif opcode==11 and a==11:
            arrival=RAW[b*123];effects.append({'type':'teleport','floor':b,'x':arrival%11,'y':arrival//11})
            f=b
        elif opcode==11 and a in [4,8,9,12,13,14]:pass # Graphics and title/caption effects.
        else:unknown.append([opcode,a,b])
    return effects,tiles,unknown

def add(id,trigger,effects,conditions=None,source=None,unknown=None):
    event={'id':id,'once':True,'trigger':trigger,'conditions':conditions or [],'effects':effects}
    if source:event['source']=source
    if unknown:event['untranslated_original_instructions']=unknown
    EVENTS.append(event)

def differences(a,b):
    return [(f,(i-2)%11,(i-2)//11,v) for off,(old,v) in enumerate(zip(a,b)) if old!=v for f,i in [divmod(off,123)]]

# Verified capture and prison escape from opening31 and touzoku.
add('capture_on_floor_3',{'type':'step','floor':3,'x':4,'y':8},[
    tile_effect(3,92,6),{'type':'message','text':DIALOGUES[9],'dialogue_id':9},
    {'type':'message','text':DIALOGUES[10],'dialogue_id':10},
    {'type':'set_stat','stat':'hp','amount':400},{'type':'set_stat','stat':'attack','amount':10},
    {'type':'set_stat','stat':'defense','amount':10},
    {'type':'remove_item','item':'sword_5'},{'type':'remove_item','item':'sacred_shield'},
    {'type':'teleport','floor':2,'x':2,'y':7},
    {'type':'flag','flag':'captured'},{'type':'message','text':DIALOGUES[3],'dialogue_id':3}],
    source='Original mevent 0x463A2C + opening31 0x4655E0')
add('thief_opens_prison_tunnel',{'type':'interact','floor':2,'x':2,'y':6},[
    tile_effect(2,67,6),tile_effect(2,68,6),{'type':'message','text':DIALOGUES[4]+' '+DIALOGUES[57],'dialogue_id':4}],
    source='Original touzoku 0x465900: door record (13,67,7)')

for floor,index,tile in [(12,10,19),(16,120,25),(19,27,39)]:
    add(f'floor_{floor}_scripted_wall_reveal',
        {'type':'bump','floor':floor,'x':index%11,'y':index//11,'tile':10},
        [tile_effect(floor,index,tile)],source='Original handan scripted-wall cases 0x4448CE..0x444BE0')

# The F15 thief opens the bypass of the octopus and leaves along the tunnel.
p=probe(0x465900,15,8,0)
effects,_,unknown=convert(p,15)
add('thief_opens_floor_15_tunnel',{'type':'interact','floor':15,'x':8,'y':0},effects,
    source='Original touzoku floor-15 branch 0x465C23',unknown=unknown)

INITIAL_STAGES={}
for f in [10,15,20,25,30,33,38,40,48,49]:
    for i,t in enumerate(RAW[f*123+2:(f+1)*123]):
        if t!=7:continue
        p=probe(0x46cb1c,f,i%11,i//11)
        effects,stage,unknown=convert(p,f)
        stage[f*123+2+i]=6;effects.insert(0,tile_effect(f,i,6))
        add(f'floor_{f}_encounter_{i}',{'type':'step','floor':f,'x':i%11,'y':i//11},effects,
            source='Original ichicheck 0x46CB1C; animation collapsed to ordered state transitions',unknown=unknown)
        INITIAL_STAGES[f]=stage

if __name__=='__main__':
    # Recover independent gate / treasure predicates by testing all combinations
    # of the cells read by the original post-combat handler. Keep minimal sets of
    # defeated guards; this avoids requiring unrelated enemies to be killed.
    for f in [2,8,11,14,17,32,34,35,38,44,45]:
        base=probe(0x4664e4,f)
        guards=[y*11+x for ff,x,y,t in base['reads'] if ff==f and 61<=t<=158]
        outcomes={}
        for mask in range(1,1<<len(guards)):
            dead=tuple(guards[i] for i in range(len(guards)) if mask&(1<<i))
            p=probe(0x4664e4,f,changes=[(f,i%11,i//11,6) for i in dead])
            effects,_,unknown=convert(p,f)
            for e in effects:
                key=json.dumps(e,sort_keys=True)
                previous=outcomes.get(key)
                if previous is None or len(dead)<len(previous[0]):outcomes[key]=(dead,e)
        grouped={}
        for dead,e in outcomes.values():grouped.setdefault(dead,[]).append(e)
        for n,(dead,effects) in enumerate(grouped.items()):
            conditions=[tile_condition(f,i,6) for i in dead]
            add(f'floor_{f}_guards_{n}',{'type':'enemy_defeated','floor':f},effects,conditions,
                source='Original moncheck 0x4664E4; minimal defeated-guard predicates recovered by executable emulation')

    # Floor ten has two distinct post-combat stages: guards, then the boss.
    stage=INITIAL_STAGES[10]
    initial=probe(0x4664e4,10,changes=differences(RAW,stage))
    guard_indices=[y*11+x for ff,x,y,t in initial['reads'] if ff==10 and 61<=t<=158 and y*11+x!=5]
    defeated=list(stage)
    for i in guard_indices:defeated[10*123+2+i]=6
    p=probe(0x4664e4,10,changes=differences(RAW,defeated))
    effects,ready,unknown=convert(p,10,defeated)
    add('floor_10_guards_defeated',{'type':'enemy_defeated','floor':10},effects,
        [tile_condition(10,i,6) for i in guard_indices]+[tile_condition(10,27,4)],
        source='Original moncheck floor-10 first stage',unknown=unknown)
    ready[10*123+2+5]=6
    p=probe(0x4664e4,10,changes=differences(RAW,ready))
    effects,_,unknown=convert(p,10,ready)
    add('floor_10_skeleton_boss_defeated',{'type':'enemy_defeated','floor':10,'x':5,'y':0},effects,
        [tile_condition(10,27,6),tile_condition(10,71,4)],source='Original moncheck floor-10 final stage',unknown=unknown)

    for f in [15,20,25,30]:
        stage=INITIAL_STAGES[f];dead=list(stage)
        enemies=[i for i,t in enumerate(stage[f*123+2:(f+1)*123]) if 61<=t<=158]
        for i in enemies:dead[f*123+2+i]=6
        p=probe(0x4664e4,f,changes=differences(RAW,dead))
        effects,_,unknown=convert(p,f,dead)
        # Only the cells actually read by this handler constrain progression.
        conditions=[tile_condition(ff,y*11+x,t) for ff,x,y,t in p['reads']]
        add(f'floor_{f}_boss_defeated',{'type':'enemy_defeated','floor':f},effects,conditions,
            source='Original moncheck 0x4664E4',unknown=unknown)

    # The Golden Knight calls moncheck after fleeing; its loot is created as
    # part of the step event so no later battle is needed to trigger it.
    stage=INITIAL_STAGES[40];p=probe(0x4664e4,40,changes=differences(RAW,stage))
    effects,_,unknown=convert(p,40,stage)
    for e in EVENTS:
        if e['id']=='floor_40_encounter_71':
            e['effects'].extend(effects);e.pop('untranslated_original_instructions',None)

    # The second floor-33 trap only seals a corridor. Its first trap has four
    # guards and two gates; these predicates are separate from other monsters.
    p=probe(0x4664e4,33,changes=[(33,9,3,4),(33,9,7,4)]+[(33,x,y,6) for x,y in [(8,4),(10,4),(8,6),(10,6)]])
    effects,_,unknown=convert(p,33)
    add('floor_33_four_guards_defeated',{'type':'enemy_defeated','floor':33},effects,
        [tile_condition(33,y*11+x,6) for x,y in [(8,4),(10,4),(8,6),(10,6)]]+[tile_condition(33,42,4)],
        source='Original moncheck floor-33 trap')

    # Floor 39 clock puzzle: precisely two yellow doors open, seven untouched.
    clock_remaining=[12,16,34,36,56,58,60]
    for index,other in [(14,38),(38,14)]:
        add(f'floor_39_clock_door_{index}',{'type':'step','floor':39,'x':index%11,'y':index//11,'tile':1},
            [tile_effect(39,36,43)],
            [tile_condition(39,i,1) for i in clock_remaining]+[tile_condition(39,other,6)],
            source='Original doorcheck 0x47BEAC')

    add('floor_41_reveal_hidden_magician',{'type':'bump','floor':41,'x':9,'y':1,'tile':10},
        [tile_effect(41,20,151)],[tile_condition(41,12,6)],source='Original handan secret-wall branch')
    p=probe(0x4664e4,41,changes=[(41,1,1,6),(41,9,1,6)])
    effects,_,unknown=convert(p,41)
    add('floor_41_two_magicians_defeated',{'type':'enemy_defeated','floor':41},effects,
        [tile_condition(41,12,6),tile_condition(41,20,6)],source='Original moncheck floor-41 branch')

    p=probe(0x46cb1c,43,7,0)
    effects,_,unknown=convert(p,43)
    add('floor_43_magician_trap',{'type':'step','floor':43,'x':7,'y':0,'tile':1},effects,
        [tile_condition(43,8,93)],source='Original doorcheck + ichicheck floor-43 branch')

    add('floor_48_caster_defeated',{'type':'enemy_defeated','floor':48,'x':0,'y':0},
        [tile_effect(48,84,6)],[tile_condition(48,0,6),tile_condition(48,84,4)],
        source='Original moncheck floor-48 branch: tile[0] + tile[84] == 10')

    # The decoy Zeno seal is the five dots on a die: four corner sorcerers
    # remain, the four middle sorcerers are defeated, and Zeno is in the center.
    stage=list(INITIAL_STAGES[49])
    for i in [16,26,28,38]:stage[49*123+2+i]=6
    p=probe(0x4664e4,49,changes=differences(RAW,stage))
    effects,_,unknown=convert(p,49,stage)
    effects.append({'type':'set_enemy','enemy':'zeno','hp':800,'attack':500,'defense':100,'gold':500})
    add('floor_49_dice_seal',{'type':'enemy_defeated','floor':49},effects,
        [tile_condition(49,i,6) for i in [16,26,28,38]]+[tile_condition(49,i,93) for i in [15,17,37,39]]+[tile_condition(49,27,91)],
        source='Original moncheck floor-49 branch; directly observed table mutation 8000/5000/1000 -> 800/500/100')
    stage[49*123+2+27]=6
    p=probe(0x4664e4,49,changes=differences(RAW,stage))
    effects,_,unknown=convert(p,49,stage)
    effects.append({'type':'flag','flag':'decoy_zeno_defeated'})
    add('floor_49_decoy_zeno_defeated',{'type':'enemy_defeated','floor':49,'x':5,'y':2},effects,
        [tile_condition(49,71,4)],source='Original moncheck floor-49 Zeno victory branch')
    for n,(gate,guards) in enumerate([(71,[81,83]),(93,[103,105])]):
        add(f'floor_49_guard_gate_{n}',{'type':'enemy_defeated','floor':49},[tile_effect(49,gate,6)],
            [tile_condition(49,i,6) for i in guards],source='Original moncheck floor-49 guard predicates')

    # Floor 23 writes a wall behind the hero on its special road cells.
    for i,t in enumerate(RAW[23*123+2:24*123]):
        if t==7:add(f'floor_23_wall_{i}',{'type':'step','floor':23,'x':i%11,'y':i//11},[tile_effect(23,i,8)],source='Original mevent 0x463C9B')

    portal_effects=[{'type':'message','text':DIALOGUES[25],'dialogue_id':25},
        {'type':'message','text':DIALOGUES[24],'dialogue_id':24}]
    portal_effects.extend(tile_effect(24,i,t) for i,t in [(4,8),(6,8),(16,6),(27,6),(38,6),(5,7)])
    portal_effects.append(tile_effect(50,92,21))
    add('princess_doll_unlocks_time_gate',{'type':'interact','floor':26,'x':5,'y':5},portal_effects,
        [tile_condition(25,60,6)],source='Original handan princess branch 0x445397')
    p=probe(0x46cb1c,24,5,0)
    effects,_,unknown=convert(p,24)
    effects.insert(0,tile_effect(24,5,6))
    add('time_gate_to_floor_50',{'type':'step','floor':24,'x':5,'y':0,'tile':7},effects,
        source='Original ichicheck floor-24 time gate; narrative scene before final Zeno interaction',unknown=unknown)
    for tile in [91,92]:
        add(f'floor_50_first_cycle_completion_{tile}',{'type':'bump','floor':50,'tile':tile},
            [{'type':'win'}],
            source='Original handan 0x4463A1..0x446473; first cycle has no battle, queues ending animation and opcode11/sub6 replay reset; remake records completion')

    assert len({e['id'] for e in EVENTS}) == len(EVENTS), 'Duplicate event IDs'
    assert not any(e.get('untranslated_original_instructions') for e in EVENTS), 'Untranslated gameplay instruction'
    print('Recovered',len(EVENTS),'events')
    (ROOT/'data/events.json').write_text(json.dumps(EVENTS,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
