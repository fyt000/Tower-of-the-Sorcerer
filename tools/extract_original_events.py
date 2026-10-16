"""Regenerate configurable campaign events from original v1.2 evidence.

Run after extract_original.py. Requires original_event_probe dependencies.
Events are authored translations of observed memory writes and queued
instructions; calls/graphics are not blindly interpreted as gameplay.
Campaign integration is deliberately a separate regeneration step.
"""
import json
from original_event_probe import probe as original_probe, RAW, ROOT
from original_animation import tile_transition

def probe(*args, **kwargs):
    # Presentation is part of the evidence, even though headless play applies
    # the resulting deterministic state changes without waiting in real time.
    follow_calls=[0x4660d0,*kwargs.pop('follow_calls',())]
    return original_probe(*args, include_presentation=True, follow_calls=follow_calls, **kwargs)

DIALOGUES={s['id']:s['text'] for s in json.loads((ROOT/'data/original-dialogue.json').read_text(encoding='utf-8'))}
TILES=list(RAW)
EVENTS=[]
SOUNDS={1:'open',2:'get',3:'taisen',4:'zeno',5:'music-start',6:'music-stop',
        7:'3f',8:'20f',9:'kai',10:'kai2'}

def tile_effect(f,index,tile):
    return {'type':'set_tile','floor':f,'x':index%11,'y':index//11,'tile':tile}
def tile_condition(f,index,tile):
    return {'type':'tile','floor':f,'x':index%11,'y':index//11,'tile':tile}

def overlay(f,index,frames,duration_ms=650,**extra):
    return {'type':'cinematic','kind':'magic','floor':f,'x':index%11,'y':index//11,
            'frames':frames,'duration_ms':duration_ms,**extra}

def summon(f,index,tile):
    return [tile_effect(f,index,tile),{'type':'sound','cue':'3f'},
            overlay(f,index,list(range(166,183)),color_tile=tile,underlying_tile=6)]

def convert(p,f,tiles=None):
    tiles=list(RAW if tiles is None else tiles)
    effects=[];unknown=[]
    transformation=any(q[0]==11 and q[1]==4 for q in p['queue'])
    deferred_changes=[]
    # A repeated write is still a gameplay operation even if it matches the
    # initial map. Branches requiring altered maps need separate probes below.
    for ff,x,y,t in p['direct_map_writes']:
        tiles[ff*123+2+y*11+x]=t
        (deferred_changes if transformation else effects).append(tile_effect(ff,y*11+x,t))
    queue=list(p['queue']); cursor=0
    while cursor<len(queue):
        opcode,a,b=queue[cursor];cursor+=1
        if opcode==0:
            if effects and effects[-1]['type']=='wait':effects[-1]['ms']+=25
            else:effects.append({'type':'wait','ms':25})
        elif opcode==1:
            effects.append({'type':'sound','cue':SOUNDS[a]})
        elif opcode in [2,8]:pass # Redraw/stats panel instructions, not game changes.
        elif opcode==9:
            # Temporary magic graphics are located on the queued tile, rather
            # than invariably on the hero. Retain the actual atlas sequence.
            frames=[b];waits=0
            operand=queue[cursor] if cursor<len(queue) and queue[cursor][0]==0 and queue[cursor][2] else None
            color_tile=operand[2] if operand else 91
            underlying_tile=operand[1] if operand else tiles[f*123+2+a]
            while cursor<len(queue):
                q=queue[cursor]
                if q[0]==0:
                    waits+=1;cursor+=1
                elif q[0]==9 and q[1]==a:
                    frames.append(q[2]);cursor+=1
                else:break
            effects.append(overlay(f,a,frames,max(60,waits*25),
                color_tile=color_tile,underlying_tile=underlying_tile))
        elif opcode==10:
            # roujin 0x44A255 decrements the queue ID before TStrings lookup.
            # Fairy records retain the score overlay rather than a string.
            if a not in [16,22,24,40,47]:
                text=DIALOGUES[a-1]
                if a in [5,17,55]:text+=' '+DIALOGUES[{5:57,17:58,55:59}[a]]
                effects.append({'type':'message','text':text,'dialogue_id':a-1,'original_queue_id':a})
            else:effects.append({'type':'cinematic','kind':'fairy','duration_ms':450})
        elif opcode in [6,13]:
            t=b
            if opcode==13:
                scene=tile_transition(f,a,tiles[f*123+2+a],b)
                # doorstackin expands one operation into sixteen frame/operand
                # pairs. The operand records are frame numbers, not waits.
                frames=[]
                while cursor<len(queue) and queue[cursor][0]==0 and 1<=queue[cursor][2]<=16:
                    frames.append(queue[cursor][2]);cursor+=1
                    if cursor<len(queue) and queue[cursor]==[13,a,b]:cursor+=1
                    else:break
                if frames:scene['original_frames']=frames
                effects.append(scene);t=scene['tile']
            tiles[f*123+2+a]=t;effects.append(tile_effect(f,a,t))
        elif opcode==12:
            t=tiles[f*123+2+a];tiles[f*123+2+a]=6;tiles[f*123+2+b]=t
            effects.append({'type':'move_tile','floor':f,'from_x':a%11,'from_y':a//11,
                            'x':b%11,'y':b//11,'tile':t,'duration_ms':130})
        elif opcode==17:
            tiles[f*123+2+a]=b;effects.append(tile_effect(f,a,b))
        elif opcode==11 and a==2:
            # This dispatch calls 461A0C after placing Zeno, not just set_tile.
            tiles[f*123+2+27]=91;effects.extend(summon(f,27,91))
        elif opcode==11 and a==3:
            for i in [15,16,17,26,28,37,38,39]:
                tiles[f*123+2+i]=93;effects.append(tile_effect(f,i,93))
            # 462560 sweeps all eight targets clockwise for each mask round.
            effects.append(overlay(f,27,[167,169,171,173,175,177,179,182],1200,
                color_tile=93,underlying_tile=6,
                targets=[{'x':i%11,'y':i//11} for i in [15,16,17,28,39,38,37,26]]))
        elif opcode==11 and a==4:
            frames=[b]
            while cursor<len(queue):
                q=queue[cursor]
                if q[0]==0:cursor+=1
                elif q[0]==11 and q[1]==4:frames.append(q[2]);cursor+=1
                else:break
            effects.append({'type':'cinematic','kind':'transformation','floor':f,
                'x':5,'y':5,'width':3,'height':3,'tile':95,
                'from_tiles':[RAW[f*123+2+y*11+x] for y in range(4,7) for x in range(4,7)],
                'original_frames':frames,'duration_ms':800})
            effects.extend(deferred_changes);deferred_changes=[]
        elif opcode==11 and a==10:
            effects.append({'type':'battle_at','floor':f,'x':b%11,'y':b//11,'first_strike':True})
            tiles[f*123+2+b]=6
        elif opcode==11 and a==11:
            arrival=RAW[b*123];effects.append({'type':'teleport','floor':b,'x':arrival%11,'y':arrival//11,
                'transition':'time_gate','duration_ms':90})
            f=b
        elif opcode==11 and a==6:effects.append({'type':'next_cycle'})
        elif opcode==11 and a in [1,7,8,9,12,13,14,15]:
            # 13/14/15 hide controls or save a raster background. They do not
            # imply victory or credits: 14 is also used in the capture scene.
            kinds={1:'capture',7:'fade_out',8:'fade_in',9:'redraw',
                   12:'fade',13:'redraw',14:'redraw',15:'redraw'}
            kind=kinds[a]
            # Collapse raster scan frames; keep the sequence and durations.
            if effects and effects[-1].get('kind')==kind:
                effects[-1]['duration_ms']=min(600,effects[-1]['duration_ms']+10)
            elif kind!='redraw':effects.append({'type':'cinematic','kind':kind,'duration_ms':150})
        else:unknown.append([opcode,a,b])
    effects.extend(deferred_changes)
    return effects,tiles,unknown

def add(id,trigger,effects,conditions=None,source=None,unknown=None):
    event={'id':id,'once':True,'trigger':trigger,'conditions':conditions or [],'effects':effects}
    if source:event['source']=source
    if unknown:event['untranslated_original_instructions']=unknown
    EVENTS.append(event)

def differences(a,b):
    return [(f,(i-2)%11,(i-2)//11,v) for off,(old,v) in enumerate(zip(a,b)) if old!=v for f,i in [divmod(off,123)]]

# Capture is a separate opening sequence. The summon occurs two tiles above
# the hero; opening2 then hides the hero, shows the title card, scans it away,
# and opening31 resets equipment/stats before the prison wake-up dialogue.
add('capture_on_floor_3',{'type':'step','floor':3,'x':4,'y':8},[
    tile_effect(3,92,6),{'type':'sound','cue':'3f'},
    overlay(3,70,list(range(166,183)),color_tile=91,underlying_tile=6),
    tile_effect(3,70,91),
    {'type':'message','text':DIALOGUES[9],'dialogue_id':9,'original_queue_id':10},
    {'type':'message','text':DIALOGUES[10],'dialogue_id':10,'original_queue_id':11},
    {'type':'sound','cue':'zeno'},
    tile_effect(3,70,6),
    {'type':'cinematic','kind':'fade_out','scene':'capture','duration_ms':350},
    {'type':'cinematic','kind':'title','scene':'capture','asset':'data3-title05',
        'target_asset':'data3-open1','frames':list(range(167,183)),
        'original_frames':list(range(232,248)),'duration_ms':1600,
        'sound_cue':'zeno','sound_offsets_ms':list(range(0,1600,100))},
    {'type':'cinematic','kind':'scan','scene':'capture','asset':'data3-open2',
        'background_asset':'data3-open1','original_frames':[100,405],
        'translation_key':'capture_incantation',
        'text':'Now is the time to act. Using omniscient power, I shall break the sacred sword and get great wisdom.',
        'duration_ms':1400},
    {'type':'cinematic','kind':'capture','duration_ms':400},
    *[{'type':'set_stat','stat':stat,'amount':amount,
       'conditions':[{'type':'cycle_at_most','amount':1}]}
      for stat,amount in [('hp',400),('attack',10),('defense',10)]],
    {'type':'remove_item','item':'sword_5'},{'type':'remove_item','item':'sacred_shield'},
    {'type':'clear_inventory','conditions':[{'type':'cycle_at_least','amount':2}]},
    {'type':'teleport','floor':2,'x':2,'y':7,'transition':'capture'},
    {'type':'set_highest_stair_floor','floor':2},
    {'type':'flag','flag':'captured'},
    *[{'type':'message','text':DIALOGUES[i],'dialogue_id':i} for i in [0,1,2,3]]],
    source='Original mevent 0x463A2C + magic 0x461A0C + opening2 0x464048 title/scan + opening31 0x4653B8; compact original stages with configurable durations')
p=probe(0x465900,2,2,7)
effects,stage,unknown=convert(p,2)
# The interaction already shows the first speech. Its Continue button then
# runs a separate queue, which moves the Thief to a second conversation site.
effects=[e for e in effects if e['type']!='message']
continuation=probe(0x44da10,2,globals=[(0x48c5a4,14)])
departure,_,more_unknown=convert(continuation,2,stage)
add('thief_opens_prison_tunnel',{'type':'interact','floor':2,'x':2,'y':6},effects+departure,
    source='Original touzoku 0x465900 wall opening + dialogue Continue stage 14 at 0x44DCAC; three departure moves to (0,7)',unknown=unknown+more_unknown)
continuation=probe(0x44da10,2,globals=[(0x48c5a4,15)])
stage=list(RAW);stage[2*123+2+77]=21
effects,_,unknown=convert(continuation,2,stage)
add('thief_leaves_prison',{'type':'interact','floor':2,'x':0,'y':7},effects,
    source='Original touzoku 0x465B2D dialogue 5 + dialogue Continue stage 15 at 0x44DDF4; two moves and removal',unknown=unknown)
continuation=probe(0x44da10,2,globals=[(0x48c5a4,16)])
effects,_,unknown=convert(continuation,2)
effects.append({'type':'flag','flag':'floor_35_thief_tunnel_started'})
add('thief_opens_floor_35_tunnel',{'type':'interact','floor':2,'x':10,'y':10},effects,
    source='Original dialogue Continue stage 16 at 0x44DF94: F35 tunnel and Thief placement; sets 0x4B8808',unknown=unknown)

for floor,index,tile in [(12,10,19),(16,120,25),(19,27,39)]:
    add(f'floor_{floor}_scripted_wall_reveal',
        {'type':'bump','floor':floor,'x':index%11,'y':index//11,'tile':10},
        [{'type':'sound','cue':'get'},tile_effect(floor,index,tile)],source='Original handan scripted-wall cases 0x4448CE..0x444BE0')

# The F15 thief opens the bypass of the octopus and leaves along the tunnel.
p=probe(0x465900,15,8,0)
effects,_,unknown=convert(p,15)
effects=[e for e in effects if e['type']!='message']  # Shown by the interaction.
add('thief_opens_floor_15_tunnel',{'type':'interact','floor':15,'x':8,'y':0},effects,
    source='Original touzoku floor-15 branch 0x465C23',unknown=unknown)

INITIAL_STAGES={}
for f in [10,15,20,25,30,33,38,40,48,49]:
    for i,t in enumerate(RAW[f*123+2:(f+1)*123]):
        if t!=7:continue
        p=probe(0x46cb1c,f,i%11,i//11)
        effects,stage,unknown=convert(p,f)
        if f==40:
            # Each of the twelve troops returns only if its cell is road.
            # The untouched-map probe never executes these restoration writes.
            troops=[j for j,t in enumerate(RAW[40*123+2:41*123])
                    if t in [135,137,139,141] and j//11<=3]
            assert len(troops)==12
            cleared=probe(0x46cb1c,f,i%11,i//11,
                          changes=[(f,j%11,j//11,6) for j in troops])
            assert cleared['queue']==p['queue']
            assert cleared['direct_map_writes']==[(f,j%11,j//11,RAW[f*123+2+j]) for j in troops]
            effects[:0]=[{**tile_effect(f,j,RAW[f*123+2+j]),
                          'conditions':[tile_condition(f,j,6)]} for j in troops]
        stage[f*123+2+i]=6;effects.insert(0,tile_effect(f,i,6))
        trigger={'type':'step','floor':f,'x':i%11,'y':i//11}
        source='Original ichicheck 0x46CB1C; ordered tile motion, sound and waits retained'
        if f==33 and i==53:
            # tswKai Rev8 fixes the lower entrance softlock. Keep one event ID
            # and once count for both entrances, and clear both trigger cells.
            trigger={'type':'step','floor':f,'positions':[{'x':9,'y':4},{'x':9,'y':6}]}
            guards=[(8,4),(10,4),(8,6),(10,6)]
            remain={'type':'any','conditions':[tile_condition(f,y*11+x,RAW[f*123+2+y*11+x]) for x,y in guards]}
            for effect in effects[1:]:effect['conditions']=[remain]
            effects.insert(1,tile_effect(f,75,6))
            source+='; tswKai Rev8: both entrances trigger once; already-cleared guard rooms stay open'
        add(f'floor_{f}_encounter_{i}',trigger,effects,source=source,unknown=unknown)
        INITIAL_STAGES[f]=stage

if __name__=='__main__':
    # These callbacks live in handan's *upstairs* branch, not in the initial
    # tile-7 map scan. 32F materializes its Knight only after stair arrival.
    # handan 0x444E8B/0x444EAF guards each scene with its own once flag.
    p=probe(0x46cb1c,32,5,9)
    effects,_,unknown=convert(p,32)
    effects.insert(0,{'type':'flag','flag':'floor_32_knight_challenged'})
    add('floor_32_golden_knight_arrival',{'type':'stairs_up','floor':32},effects,
        source='Original handan 0x444E8B..0x444EAF + mevent 0x463EC7 + ichicheck 0x472A2C: once-only stair arrival, 13 approach moves, speech and enemy-first battle',unknown=unknown)

    # Recover the previously unreachable post-combat branch by satisfying its
    # successful-battle predicate and seeding the relocated 29F Thief.
    p=probe(0x4664e4,32,5,9,globals=[(0x4b8868,1)],changes=[(29,6,1,21)])
    effects,_,unknown=convert(p,32)
    effects.insert(0,{'type':'flag','flag':'floor_32_knight_challenged','value':False})
    add('floor_32_golden_knight_retreat',
        {'type':'enemy_defeated','floor':32,'x':5,'y':9,'tile':133},effects,
        [{'type':'flag','flag':'floor_32_knight_challenged'}],
        source='Original moncheck 0x46903B: successful Knight battle, 13 retreat moves, return Thief from 29F to 2F',unknown=unknown)

    # 42F is another stair callback. Capture the two apparition helpers
    # separately: their Delphi drawing calls are skipped, while their queue
    # targets/masks remain independently verified by audit_original_events.py.
    guards=[71,93,81,83]
    apparition=summon(42,60,91)
    apparition.extend(tile_effect(42,i,93) for i in guards)
    guard_probe=probe(0x461ef4,42,5,9,globals=list(zip(
        [0x48c558,0x48c55c,0x48c560,0x48c564],guards)))
    masks=list(dict.fromkeys(q[2] for q in guard_probe['queue'] if q[0]==9))
    apparition.extend([{'type':'sound','cue':'3f'},overlay(42,82,masks,900,
        color_tile=93,underlying_tile=6,targets=[{'x':i%11,'y':i//11} for i in guards])])
    p=probe(0x46cb1c,42,5,9)
    stage=list(RAW)
    for i,t in [(60,91),*[(i,93) for i in guards]]:stage[42*123+2+i]=t
    effects,_,unknown=convert(p,42,stage)
    add('floor_42_zeno_and_golden_knight_arrival',{'type':'stairs_up','floor':42},apparition+effects,
        source='Original handan 0x444EAF..0x444ED3 + ichicheck 0x475FBA: once-only stair arrival, Zeno/four Sorcerers apparition, Knight execution, four speeches and departure',unknown=unknown)

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
                if e['type'] in ['wait','sound','cinematic']:continue
                key=json.dumps(e,sort_keys=True)
                previous=outcomes.get(key)
                if previous is None or len(dead)<len(previous[0]):outcomes[key]=(dead,e)
        grouped={}
        for dead,e in outcomes.values():grouped.setdefault(dead,[]).append(e)
        for n,(dead,writes) in enumerate(grouped.items()):
            # Recover the complete minimal branch again: selecting only its
            # final writes discarded gate movement, treasure cues and waits.
            p=probe(0x4664e4,f,changes=[(f,i%11,i//11,6) for i in dead])
            branch,_,unknown=convert(p,f)
            keys={json.dumps(e,sort_keys=True) for e in writes}
            targets={(e['floor'],e['x'],e['y']) for e in writes if e['type']=='set_tile'}
            effects=[e for e in branch if
                e['type'] in ['wait','sound'] or
                (e['type']=='cinematic' and (e.get('floor'),e.get('x'),e.get('y')) in targets) or
                json.dumps(e,sort_keys=True) in keys]
            conditions=[tile_condition(f,i,6) for i in dead]
            add(f'floor_{f}_guards_{n}',{'type':'enemy_defeated','floor':f},effects,conditions,
                source='Original moncheck 0x4664E4; minimal defeated-guard predicates and ordered presentation recovered by executable emulation',unknown=unknown)

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

    # doorcheck runs on both accepted and refused keyed-door attempts. The
    # other hand must already be road; the contacted door need not open.
    clock_remaining=[12,16,34,36,56,58,60]
    for index,other in [(14,38),(38,14)]:
        add(f'floor_39_clock_door_{index}',{'type':'door_attempted','floor':39,'x':index%11,'y':index//11,'tile':1},
            [{'type':'sound','cue':'get'},tile_effect(39,36,43)],
            [tile_condition(39,i,1) for i in clock_remaining]+[tile_condition(39,other,6)],
            source='Original handan 0x44468C calls doorcheck 0x47BEAC even without a key')

    add('floor_41_reveal_hidden_magician',{'type':'bump','floor':41,'x':9,'y':1,'tile':10},
        [{'type':'sound','cue':'get'},tile_effect(41,20,151)],[tile_condition(41,12,6)],source='Original handan secret-wall branch')
    p=probe(0x4664e4,41,changes=[(41,1,1,6),(41,9,1,6)])
    effects,_,unknown=convert(p,41)
    add('floor_41_two_magicians_defeated',{'type':'enemy_defeated','floor':41},effects,
        [tile_condition(41,12,6),tile_condition(41,20,6)],source='Original moncheck floor-41 branch')

    p=probe(0x46cb1c,43,7,0)
    effects,_,unknown=convert(p,43)
    add('floor_43_door_arms_trap',{'type':'door_attempted','floor':43,'x':7,'y':0,'tile':1},
        [tile_effect(43,7,7)],[tile_condition(43,7,1),tile_condition(43,8,93)],
        source='Original doorcheck 0x47C1C8: no-key attempt converts the closed door to special road')
    add('floor_43_magician_trap',{'type':'step','floor':43,'x':7,'y':0},effects,
        [tile_condition(43,8,93)],source='Original doorcheck + ichicheck floor-43 branch')

    add('floor_48_caster_defeated',{'type':'enemy_defeated','floor':48,'x':0,'y':0},
        [tile_effect(48,84,6)],[tile_condition(48,0,6),tile_condition(48,84,4)],
        source='Original moncheck floor-48 branch: tile[0] + tile[84] == 10')

    # The decoy Zeno seal is the five dots on a die: four corner sorcerers
    # remain and the four middle sorcerers are defeated. The EXE does not test
    # the center tile; it divides the current shared row once per seal flag.
    stage=list(INITIAL_STAGES[49])
    for i in [16,26,28,38]:stage[49*123+2+i]=6
    p=probe(0x4664e4,49,changes=differences(RAW,stage))
    effects,_,unknown=convert(p,49,stage)
    # The decoy-death builder overwrites the seal speech queue but leaves
    # these direct stat/flag writes intact. Suppress that speech on death.
    for effect in effects:
        effect['conditions']=[{'type':'any','conditions':[
            tile_condition(49,27,91),tile_condition(49,27,92)]}]
    effects.extend([
        {'type':'multiply_enemy','enemy':'zeno','numerator':1,'denominator':10,
         'conditions':[{'type':'flag','flag':'floor_49_zeno_sealed','value':False}]},
        {'type':'flag','flag':'floor_49_zeno_sealed'}])
    add('floor_49_dice_seal',{'type':'enemy_defeated','floor':49},effects,
        [tile_condition(49,i,6) for i in [16,26,28,38]]+[tile_condition(49,i,93) for i in [15,17,37,39]],
        source='Original moncheck 0x46B553..0x46B597: shared Zeno HP/ATK/DEF /= 10 when seal flag 0x4B88F8 is clear')
    EVENTS[-1]['once']=False
    stage[49*123+2+27]=6
    p=probe(0x4664e4,49,changes=differences(RAW,stage))
    effects,_,unknown=convert(p,49,stage)
    effects.append({'type':'flag','flag':'decoy_zeno_defeated'})
    # Run after the seal in the same floor-state stage. A per-victim callback
    # would clear the corners first and prevent the original post-gate reseal.
    add('floor_49_decoy_zeno_defeated',{'type':'post_combat','floor':49},effects,
        [tile_condition(49,27,6),tile_condition(49,71,4),tile_condition(49,60,6)],
        source='Original moncheck floor-49: seal arithmetic precedes decoy loot; reward builder overwrites seal dialogue')
    for n,(gate,guards) in enumerate([(71,[81,83]),(93,[103,105])]):
        add(f'floor_49_guard_gate_{n}',{'type':'enemy_defeated','floor':49},[tile_effect(49,gate,6)],
            [tile_condition(49,i,6) for i in guards],source='Original moncheck floor-49 guard predicates')

    # Floor 23 writes a wall behind the hero on its special road cells.
    for i,t in enumerate(RAW[23*123+2:24*123]):
        if t==7:add(f'floor_23_wall_{i}',{'type':'step','floor':23,'x':i%11,'y':i//11},[{'type':'sound','cue':'open'},tile_effect(23,i,8)],source='Original mevent 0x463C9B')

    # handan always places the F50 Thief and speaks queue IDs 25 then 26;
    # only the F24 portal writes depend on the F25 boss having disappeared.
    p=probe(0x444490,26,5,6,globals=[(0x48c584,60)],changes=[(25,5,5,6)])
    portal_effects,_,unknown=convert(p,26)
    portal_effects=[e for e in portal_effects if e.get('dialogue_id')!=24]  # Already shown by interaction.
    for effect in portal_effects:
        if effect['type']=='set_tile' and effect['floor']==24:
            effect['conditions']=[tile_condition(25,60,6)]
    add('princess_doll_unlocks_time_gate',{'type':'interact','floor':26,'x':5,'y':5},portal_effects,
        source='Original handan princess branch 0x445397: unconditional speeches/Thief at F50 (5,4); only F24 gate requires F25 boss cell road',unknown=unknown)
    EVENTS[-1]['once']=False
    p=probe(0x46cb1c,24,5,0)
    effects,_,unknown=convert(p,24)
    effects.insert(0,tile_effect(24,5,6))
    # The portal reverses a seal only when the shared seal flag is set.
    # Going to 50F first, then sealing on 49F, bypasses this restoration.
    effects[1:1]=[
        {'type':'multiply_enemy','enemy':'zeno','numerator':10,'denominator':1,
         'conditions':[{'type':'flag','flag':'floor_49_zeno_sealed'}]},
        {'type':'flag','flag':'floor_49_zeno_sealed','value':False},
        {'type':'set_enemy','enemy':'zeno','hp':1000,'attack':625,'defense':125,
         'conditions':[{'type':'cycle_at_least','amount':2},{'type':'cycle_at_most','amount':2}]}]
    second=probe(0x46cb1c,24,5,0,globals=[(0x4b8904,43),(0x4b8908,0)])
    second_effects,_,second_unknown=convert(second,24)
    first_effects,_,_=convert(p,24)
    # The extra retreat starts after the common narrative. A trailing wait
    # can merge into the next wait, so compare through the final speech.
    last_speech=max(i for i,e in enumerate(first_effects) if e['type']=='message')
    assert second_effects[:last_speech+1]==first_effects[:last_speech+1]
    effects.pop()  # Use the cycle-specific wait after the final speech below.
    for effect in first_effects[last_speech+1:]:
        effect['conditions']=[{'type':'any','conditions':[
            {'type':'cycle_at_most','amount':1},{'type':'cycle_at_least','amount':3}]}]
        effects.append(effect)
    for effect in second_effects[last_speech+1:]:
        effect['conditions']=[{'type':'cycle_at_least','amount':2},{'type':'cycle_at_most','amount':2}]
        effects.append(effect)
    add('time_gate_to_floor_50',{'type':'step','floor':24,'x':5,'y':0,'tile':7},effects,
        source='Original ichicheck 0x470506..0x470571: conditional seal reversal, then second-cycle fixed row and march/forced first-strike battle',unknown=unknown+second_unknown)
    for tile in [91,92]:
        add(f'floor_50_first_cycle_completion_{tile}',{'type':'bump','floor':50,'tile':tile},
            [{'type':'cinematic','kind':'victory','duration_ms':800},
             {'type':'sound','cue':'kai2'},
             {'type':'cinematic','kind':'credits','duration_ms':600},
             {'type':'next_cycle'}],[{'type':'cycle_at_most','amount':1}],
            source='Original handan 0x4463A1..0x446473; first cycle has no battle, ending then opcode11/sub6 replay reset')
        add(f'floor_50_backside_zeno_stats_{tile}',{'type':'bump','floor':50,'tile':tile},
            [{'type':'set_enemy','enemy':'zeno','hp':1000,'attack':625,'defense':125,'gold':500,
              'conditions':[{'type':'cycle_at_most','amount':2}]}],
            [{'type':'cycle_at_least','amount':2},{'type':'cycle_at_most','amount':2}],
            source='Original handan 0x4463AA..0x4463D1: only the second cycle overwrites the shared row; later cycles retain it')
        # Only the second-cycle branch resets the row after a refused attack.
        EVENTS[-1]['once']=False
    p=probe(0x4664e4,50,5,4,changes=[(50,5,4,6)],globals=[(0x4b8904,43)])
    effects,_,unknown=convert(p,50)
    add('floor_50_backside_completion',{'type':'enemy_defeated','floor':50},effects,
        [{'type':'cycle_at_least','amount':2},{'type':'no_enemies','floor':50}],
        source='Original moncheck floor50 0x46BFA8; both second-cycle ambush at (5,6) and later battle at (5,4) invoke ending and opcode11/sub6 replay reset',unknown=unknown)

    # moncheck observes floor state once after a battle or the entire Bomb
    # stack. Per-victim notifications remain available to authored campaigns.
    for event in EVENTS:
        trigger=event['trigger']
        if trigger['type']=='enemy_defeated' and not any(key in trigger for key in ['x','y','tile']):
            trigger['type']='post_combat'
        if event['id']=='floor_48_caster_defeated':
            event['trigger']={'type':'post_combat','floor':48}

    assert len({e['id'] for e in EVENTS}) == len(EVENTS), 'Duplicate event IDs'
    assert not any(e.get('untranslated_original_instructions') for e in EVENTS), 'Untranslated gameplay instruction'
    print('Recovered',len(EVENTS),'events')
    (ROOT/'data/events.json').write_text(json.dumps(EVENTS,ensure_ascii=False,indent=2)+'\n',encoding='utf-8',newline='\n')
