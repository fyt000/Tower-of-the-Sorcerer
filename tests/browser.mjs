import { chromium } from '@playwright/test';
import { readFileSync, writeFileSync, mkdirSync } from 'node:fs';
import { resolve } from 'node:path';
import { execFileSync } from 'node:child_process';
import assert from 'node:assert/strict';

const root=resolve(import.meta.dirname,'..'), output=resolve(root,'test-results');
mkdirSync(output,{recursive:true});
const original=readFileSync(resolve(root,'data/campaign.json'),'utf8');
const previousOriginal=execFileSync('git',['show','840a7a5:data/campaign.json'],{cwd:root,encoding:'utf8',maxBuffer:4*1024*1024});
const browser=await chromium.launch({headless:true,args:['--use-angle=swiftshader-webgl','--autoplay-policy=no-user-gesture-required']});
const context=await browser.newContext({viewport:{width:1440,height:1000},acceptDownloads:true});
const page=await context.newPage(), errors=[], report=[];
page.on('pageerror',error=>errors.push(error.message));
const state=()=>page.evaluate(()=>JSON.parse(window.tower.state_json()));
const ui=()=>page.evaluate(()=>JSON.parse(window.tower.ui_json()));
async function test(name,run){await run();report.push(name);console.log(`PASS ${name}`);}
async function ready(){await page.waitForFunction(()=>window.tower && JSON.parse(window.tower.ui_json()).sprites_loaded,undefined,{timeout:45000});}
async function idle(){await page.waitForFunction(()=>{const s=JSON.parse(window.tower.ui_json());return !s.animation&&!s.presentation_remaining&&!s.path_remaining;},undefined,{timeout:30000});}
async function button(id,editor=false){
  await page.waitForFunction(({id,editor})=>{const u=JSON.parse(window.tower.ui_json());return !!(editor?u.editor.bounds:u.bounds)[id];},{id,editor},{timeout:10000});
  const u=await ui(),r=(editor?u.editor.bounds:u.bounds)[id];
  const beforePresentation=JSON.stringify([u.animation,u.animations_seen,u.visual_log,u.visual_floor]);
  await page.mouse.click(r.cx??r.x+(r.width??r.w)/2,r.cy??r.y+(r.height??r.h)/2);
  if(id==='dialogue_continue') await page.waitForFunction(before=>{
    const current=JSON.parse(window.tower.ui_json());
    return JSON.stringify([current.animation,current.animations_seen,current.visual_log,current.visual_floor])!==before;
  },beforePresentation,{timeout:5000});
  await page.waitForTimeout(150);
}
async function cell(x,y,editor=false){const u=await ui(),r=editor?u.editor.bounds.board:u.bounds.board;
  const w=editor?u.editor.width:r.width,h=editor?u.editor.height:r.height;
  await page.mouse.click(r.x+(x+.5)*(r.w??r.width)/w,r.y+(y+.5)*(r.h??r.height)/h);
  await page.waitForTimeout(150);
}
async function hoverCell(x,y){const r=(await ui()).bounds.board;
  await page.mouse.move(r.x+(x+.5)*r.w/r.width,r.y+(y+.5)*r.h/r.height);
  await page.waitForTimeout(200);
}
async function command(action){return page.evaluate(action=>JSON.parse(window.tower.command_json(JSON.stringify(action))),action);}
async function load(change){const save=JSON.parse(await page.evaluate(()=>window.tower.save_json()));change(save);await page.evaluate(source=>window.tower.load_save(source),JSON.stringify(save));await page.waitForTimeout(100);}
async function importCampaign(source){await page.evaluate(source=>window.tower.import_campaign(source),source);await idle();await page.waitForTimeout(100);}
async function skip(){if((await ui()).animation||(await ui()).presentation_remaining)await button('skip');await idle();}
async function sceneUntil(type){await page.waitForFunction(type=>JSON.parse(window.tower.ui_json()).animation===type,type,{timeout:20000});}
async function cinematicUntil(kind){await page.waitForFunction(kind=>{const u=JSON.parse(window.tower.ui_json());return u.animation==='cinematic'&&u.animation_details.at(-1)?.kind===kind;},kind,{timeout:20000});}
async function heroIdle(){await page.waitForFunction(()=>JSON.parse(window.tower.ui_json()).hero_pose==='idle',undefined,{timeout:5000});}
async function dialogueInsideBoard(){
  // egui reuses the conversation area across speakers. Its initial rectangle
  // can be the previous conversation's size before the next frame lays it out.
  await page.waitForFunction(()=>{
    const bounds=JSON.parse(window.tower.ui_json()).bounds,b=bounds.board,d=bounds.dialogue;
    if(!b||!d)return false;
    const actions=Object.entries(bounds).filter(([id])=>id.startsWith('choice:')||id==='dialogue_continue');
    return d.x>=b.x-1&&d.y>=b.y-1&&d.x+d.w<=b.x+b.w+1&&d.y+d.h<=b.y+b.h+1
      &&actions.every(([,r])=>r.y>=d.y&&r.y+r.h<=d.y+d.h);
  },undefined,{timeout:5000});
  const bounds=(await ui()).bounds,{board:b,dialogue:d}=bounds;
  assert(d.x>=b.x-1&&d.y>=b.y-1&&d.x+d.w<=b.x+b.w+1&&d.y+d.h<=b.y+b.h+1,`Dialogue must remain inside the board: ${JSON.stringify({board:b,dialogue:d})}`);
  for(const [id,r] of Object.entries(bounds).filter(([id])=>id.startsWith('choice:')||id==='dialogue_continue')) {
    assert(r.y>=d.y&&r.y+r.h<=d.y+d.h,`Dialogue action ${id} must remain visible inside its panel`);
  }
}

const corridor=JSON.stringify({id:'browser-regression',title:'Browser test',width:5,height:3,
  start:{floor:1,x:0,y:1,hp:100,attack:10,defense:5,gold:0,keys:{yellow:0,blue:0,red:0},inventory:[]},
  rules:{empty_tile:6,forecast_requires_item:'hero_orb'},
  floors:[{id:1,title:'Corridor',tiles:[8,8,8,8,8,6,6,61,6,29,8,8,8,8,8]}],
  tiles:{6:{name:'Road',kind:'floor',sprite:6},8:{name:'Wall',kind:'wall',sprite:8},61:{name:'Slime',kind:'enemy',enemy:'slime',sprite:61},29:{name:'Yellow key',kind:'key',key:'yellow',amount:1,sprite:29}},
  enemies:{slime:{name:'Slime',hp:20,attack:8,defense:1,gold:2}},events:[]});

const originalData=JSON.parse(original);
const originalDialogue=JSON.parse(readFileSync(resolve(root,'data/locales/en.json'),'utf8')).dialogue;
const wisdomFixture=JSON.stringify({id:'wisdom-browser-regression',title:'Wisdom journal test',width:5,height:3,
  start:{floor:1,x:0,y:1,hp:100,attack:10,defense:5,gold:0,inventory:[]},
  rules:{empty_tile:6,forecast_requires_item:'hero_orb',save_requires_hero_orb:true},
  floors:[{id:1,title:'Journal room',tiles:[100,8,8,101,8,6,36,37,6,43,8,8,8,8,8]}],
  tiles:{6:originalData.tiles['6'],8:originalData.tiles['8'],36:originalData.tiles['36'],
    37:originalData.tiles['37'],43:originalData.tiles['43'],
    100:{...originalData.tiles['25'],text:originalDialogue['62']},
    101:{...originalData.tiles['25'],text:originalDialogue['78']}},
  enemies:{},events:[]});

const equipmentContactFixture=JSON.stringify({id:'equipment-contact-browser',title:'Equipment and encounter test',width:5,height:3,
  start:{floor:1,x:0,y:1,hp:100,attack:10,defense:5,gold:0,inventory:['sword_5','sacred_shield']},
  rules:{empty_tile:6,forecast_requires_item:'hero_orb'},
  floors:[{id:1,tiles:[8,8,8,8,8,6,51,56,61,6,6,6,6,6,6]}],
  tiles:{6:originalData.tiles['6'],8:originalData.tiles['8'],51:originalData.tiles['51'],
    55:originalData.tiles['55'],56:originalData.tiles['56'],60:originalData.tiles['60'],
    61:{name:'Guard',kind:'enemy',enemy:'guard',sprite:61}},
  enemies:{guard:{name:'Guard',hp:1200,attack:180,defense:30,gold:100}},events:[]});

try {
  await page.goto(process.env.TOS_URL||'http://127.0.0.1:8080');await ready();await page.waitForTimeout(500);
  await test('Rust WebGL board and readable desktop layout',async()=>{
    const s=await state(),u=await ui();assert.equal(s.floors.length,51);assert.equal(s.width,11);
    const b=u.bounds.board;assert(b.x>=0&&b.x+b.w<=1440&&b.y+b.h<=1000,JSON.stringify(b));
    assert.equal(u.sprites_loaded,true);await page.screenshot({path:resolve(output,'desktop.png')});
    await page.setViewportSize({width:1360,height:920});await page.waitForTimeout(150);
    const compact=(await ui()).bounds;
    assert(compact.board.y+compact.board.h<920);
    assert.equal(compact.right,undefined,'Direction controls are replaced by board pathing and keyboard movement');
    await page.screenshot({path:resolve(output,'compact-desktop.png')});
    await page.setViewportSize({width:1440,height:1000});await page.waitForTimeout(150);
  });
  await test('Known original first-version save migrates and remains backed up',async()=>{
    const legacy=JSON.parse(await page.evaluate(()=>window.tower.save_json()));
    legacy.campaign_fingerprint='56277325ec91e254';delete legacy.cycle;
    legacy.player.hp=888;legacy.steps=9;
    // Inject after the old page's lifecycle autosave, before the new Rust app starts.
    await page.addInitScript(value=>{
      if(!sessionStorage.getItem('migration-fixture')){
        localStorage.setItem('tos-rust:save:v1',JSON.stringify(value));
        sessionStorage.setItem('migration-fixture','installed');
      }
    },legacy);
    await page.reload();await ready();assert.equal((await state()).player.hp,888);assert.equal((await state()).steps,9);
    assert(await page.evaluate(()=>localStorage.getItem('tos-rust:save:recovery')));
    await importCampaign(original);
  });
  await test('Cached previous campaign, autosave and checkpoint migrate without resetting backside progress',async()=>{
    const legacy=JSON.parse(await page.evaluate(()=>window.tower.save_json()));
    legacy.campaign_fingerprint='800993184d7842ca';legacy.cycle=2;legacy.player.hp=777;legacy.player.gold=41;legacy.steps=17;
    const checkpoint=structuredClone(legacy);checkpoint.player.hp=666;checkpoint.steps=16;
    await page.addInitScript(({campaign,save,checkpoint})=>{
      if(!sessionStorage.getItem('cached-campaign-migration-fixture')){
        localStorage.setItem('tos-rust:campaign:v1',campaign);
        localStorage.setItem('tos-rust:save:v1',JSON.stringify(save));
        localStorage.setItem('tos-rust:checkpoint:v1',JSON.stringify({campaign,save:checkpoint}));
        sessionStorage.setItem('cached-campaign-migration-fixture','installed');
      }
    },{campaign:previousOriginal,save:legacy,checkpoint});
    await page.reload();await ready();const migrated=await state();
    assert.deepEqual([migrated.cycle,migrated.player.hp,migrated.player.gold,migrated.steps],[2,777,41,17]);
    assert.equal(await page.evaluate(()=>localStorage.getItem('tos-rust:campaign:recovery')),previousOriginal);
    assert.equal(JSON.parse(await page.evaluate(()=>localStorage.getItem('tos-rust:save:recovery'))).campaign_fingerprint,'800993184d7842ca');
    await button('restore');await idle();assert.deepEqual([(await state()).cycle,(await state()).player.hp,(await state()).steps],[2,666,16]);
    await importCampaign(original);
  });
  await test('Rejected cached campaign is preserved and its validation error is visible',async()=>{
    const rejected='{"id":"broken-cached-campaign"}';
    await page.addInitScript(source=>{
      if(!sessionStorage.getItem('invalid-campaign-recovery-fixture')) {
        localStorage.setItem('tos-rust:campaign:v1',source);
        localStorage.removeItem('tos-rust:save:v1');
        sessionStorage.setItem('invalid-campaign-recovery-fixture','installed');
      }
    },rejected);
    await page.reload();await ready();
    assert.equal(await page.evaluate(()=>localStorage.getItem('tos-rust:campaign:recovery')),rejected);
    assert.equal(JSON.parse(await page.evaluate(()=>localStorage.getItem('tos-rust:campaign:v1'))).id,JSON.parse(original).id);
    const notice=(await ui()).notice;
    assert.match(notice,/Campaign could not be loaded:.*missing field/);
    assert.match(notice,/rejected campaign is preserved/);
    assert.match(notice,/Loaded the bundled campaign/);
    assert.equal((await state()).floors.length,51);
  });
  await test('Actual mouse click follows road and collects the selected key',async()=>{
    await cell(4,9);assert.equal((await ui()).bounds.skip,undefined,'Ordinary travel must not show a skip-scene control');
    await idle();await heroIdle();const s=await state();assert.deepEqual([s.player.x,s.player.y,s.player.keys.yellow],[4,9,1]);
  });
  await test('Original WAV effects and configured MIDI music play through WebAudio',async()=>{
    await page.waitForFunction(()=>{const a=JSON.parse(window.tower.ui_json()).audio;return a.unlocked&&a.effects_played>0&&a.music;},undefined,{timeout:20000});
    assert.equal((await ui()).audio.error,null);assert.match((await ui()).audio.music,/b_067xgw/);
  });
  await test('Independent browser checkpoint survives further autosaves',async()=>{
    await load(s=>{if(!s.player.inventory.includes('hero_orb'))s.player.inventory.push('hero_orb');});
    await button('save');const saved=(await state()).player;await page.keyboard.press('ArrowRight');await page.waitForTimeout(150);await idle();assert.notDeepEqual((await state()).player,saved);
    await button('restore');await idle();assert.deepEqual((await state()).player,saved);
  });
  await test('Browser autosave resumes after reload',async()=>{
    const saved=(await state()).player;await page.reload();await ready();assert.deepEqual((await state()).player,saved);
  });
  await test('Actual Hero and Wisdom item collection gates save and Journal, with reusable translated item-click recall',async()=>{
    await page.evaluate(()=>window.tower.set_language('en'));await importCampaign(wisdomFixture);
    const locked=await ui();assert(locked.bounds.journal_preview_open,'Recent activity remains visible before the Wisdom Orb');
    assert(locked.bounds.journal_header,'The complete activity log is available independently of Wisdom');
    assert.equal(locked.bounds['item:wisdom_orb'],undefined,'Hints are unavailable without the owned Wisdom Orb');
    assert.equal(locked.bounds.save.enabled,false,'Manual save is disabled without the Hero Orb');
    const checkpointBefore=await page.evaluate(()=>localStorage.getItem('tos-rust:checkpoint:v1'));
    await button('save');assert.equal(await page.evaluate(()=>localStorage.getItem('tos-rust:checkpoint:v1')),checkpointBefore,'A disabled save click cannot replace the checkpoint');
    await cell(0,0);await page.waitForFunction(()=>JSON.parse(window.tower.state_json()).pending_interaction);
    await button('choice:leave');await idle();assert.deepEqual((await state()).journal,[]);

    await cell(1,1);await idle();assert((await state()).player.inventory.includes('hero_orb'));
    assert.equal((await ui()).bounds.save.enabled,true,'Collecting Hero enables the actual save control');
    await button('save');const savedCheckpoint=JSON.parse(await page.evaluate(()=>localStorage.getItem('tos-rust:checkpoint:v1')));
    assert.equal(savedCheckpoint.save.campaign_id,'wisdom-browser-regression');
    assert.deepEqual([savedCheckpoint.save.player.x,savedCheckpoint.save.player.y],[1,1]);

    await cell(2,1);await idle();assert.equal((await state()).journal_unlocked,true);
    assert((await ui()).bounds['item:wisdom_orb'],'Collecting Wisdom makes its hint reader available through the actual item');
    assert.deepEqual((await state()).journal,[],'Acquisition does not backfill the already heard clue');
    await cell(0,0);await page.waitForFunction(()=>JSON.parse(window.tower.state_json()).pending_interaction);
    await button('choice:leave');await idle();assert.deepEqual((await state()).journal,[],'Rereading a pre-orb clue still cannot backfill it');
    await cell(3,0);await page.waitForFunction(()=>JSON.parse(window.tower.state_json()).pending_interaction);
    await button('choice:leave');await idle();
    const entries=(await state()).journal;assert.equal(entries.length,1);assert.equal(entries[0].text,originalDialogue['78']);
    assert(!JSON.stringify(entries).includes(originalDialogue['62']),'The earlier clue remains excluded');
    await cell(4,1);await idle();assert.equal((await state()).inventory_items.find(item=>item.id==='warp_staff').charges,3);

    for(const locale of ['en','zh-CN']) {
      await page.evaluate(locale=>window.tower.set_language(locale),locale);await page.waitForTimeout(locale==='zh-CN'?1200:150);
      const staff=(await ui()).bounds['item:warp_staff'];
      await page.mouse.move(staff.x+staff.w/2,staff.y+staff.h/2);await page.waitForTimeout(800);
      await page.screenshot({path:resolve(output,`wisdom-item-help-${locale}.png`)});
      await button('item:wisdom_orb');await sceneUntil('journal');
      await page.waitForFunction(()=>!!JSON.parse(window.tower.ui_json()).bounds.journal_dialog);
      const modal=(await ui()).bounds.journal_dialog,close=(await ui()).bounds.journal_close;
      assert(modal.x>=0&&modal.y>=0&&modal.x+modal.w<=1440&&modal.y+modal.h<=1000,JSON.stringify(modal));
      assert(close.y>=modal.y&&close.y+close.h<=modal.y+modal.h,'Journal Close remains inside the visible modal');
      assert.deepEqual((await state()).last_action.presentation,[{type:'journal',entries}]);
      await page.waitForTimeout(250);assert.equal((await ui()).animation,'journal','Journal remains open until player dismissal');
      await page.screenshot({path:resolve(output,`wisdom-journal-${locale}.png`)});
      await button('journal_close');await idle();assert((await state()).player.inventory.includes('wisdom_orb'),'Reading the Journal does not consume Wisdom');
      assert.equal((await ui()).bounds.journal_dialog,undefined);assert.deepEqual((await state()).journal,entries);
    }
    await page.evaluate(()=>window.tower.set_language('en'));await importCampaign(original);
  });
  await test('Dedicated equipment slots and raw contact stats remain visible before Hero and after reload',async()=>{
    await importCampaign(equipmentContactFixture);
    assert.equal((await state()).equipment.weapon.id,'sword_5');
    assert.equal((await state()).equipment.shield.id,'sacred_shield');
    assert((await ui()).bounds['equipment:weapon']);assert((await ui()).bounds['equipment:shield']);
    assert.equal((await ui()).bounds.last_encounter,undefined);
    const unseen=await page.evaluate(()=>JSON.parse(window.tower.inspect_json(3,1)));
    assert.equal(unseen.enemy,null);assert.equal(unseen.encountered_enemy,null);
    await cell(1,1);await idle();await cell(2,1);await idle();
    const equipped=await state();assert.equal(equipped.equipment.weapon.id,'sword_1');
    assert.equal(equipped.equipment.shield.id,'shield_1');assert.equal(equipped.abilities.field_magic_protection,true);
    assert.deepEqual(equipped.inventory_items,[],'Equipment has its own slots');
    assert.deepEqual([equipped.player.attack,equipped.player.defense],[20,15]);
    await page.mouse.move(5,5); // Actual contact replaces the older tile selection when the pointer is off the board.
    await page.keyboard.press('ArrowRight');await page.waitForTimeout(150);await idle();
    const contact=(await state()).last_encounter;
    assert.deepEqual([contact.hp,contact.attack,contact.defense],[1200,180,30]);
    assert.equal((await state()).last_action.ok,false);assert.deepEqual((await state()).enemies,[]);
    await hoverCell(3,1);assert((await ui()).bounds.inspection_contact);
    for(const locale of ['en','zh-CN']) {
      await page.evaluate(locale=>window.tower.set_language(locale),locale);await page.waitForTimeout(locale==='zh-CN'?1200:150);
      const bounds=(await ui()).bounds;
      for(const id of ['equipment:weapon','equipment:shield','inspection_contact']) {
        const r=bounds[id];assert(r.x>=0&&r.y>=0&&r.x+r.w<=1441&&r.y+r.h<=1001,`${id}: ${JSON.stringify(r)}`);
      }
      await page.screenshot({path:resolve(output,`equipment-encounter-${locale}.png`)});
    }
    await page.reload();await ready();assert.deepEqual((await state()).last_encounter,contact);
    assert.equal((await state()).equipment.shield.id,'shield_1');
    await hoverCell(3,1);assert((await ui()).bounds.inspection_contact);
    await load(save=>{save.cycle=2;save.last_encounter=null;});
    await page.keyboard.press('ArrowRight');await page.waitForTimeout(150);await idle();
    assert.deepEqual([(await state()).last_encounter.hp,(await state()).last_encounter.attack,
      (await state()).last_encounter.defense],[52800,7920,1320]);
    await page.screenshot({path:resolve(output,'equipment-encounter-backside-zh-CN.png')});
    await page.evaluate(()=>window.tower.set_language('en'));
  });
  await test('Mouse route cannot cross an intermediate enemy',async()=>{
    await importCampaign(corridor);await cell(4,1);await idle();const s=await state();assert.equal(s.player.x,1);assert.equal(s.player.hp,100);assert.equal(s.tiles[7],61);
  });
  await test('Enemy hover/inspection numerical details stay gated',async()=>{
    const locked=await page.evaluate(()=>JSON.parse(window.tower.inspect_json(2,1)));assert.equal(locked.details_locked,true);assert.equal(locked.enemy,null);assert.deepEqual((await state()).enemies,[]);
  });
  await test('Keyboard travel remains responsive and blocked movement preserves position and facing',async()=>{
    await page.keyboard.press('ArrowLeft');await page.waitForTimeout(35);await page.keyboard.press('ArrowRight');assert.equal((await ui()).bounds.skip,undefined);
    await idle();await heroIdle();assert.deepEqual([(await state()).player.x,(await state()).player.y],[1,1]);
    await page.keyboard.press('ArrowUp');await page.waitForFunction(()=>JSON.parse(window.tower.ui_json()).facing==='up');await idle();await heroIdle();const blocked=await state();
    assert.deepEqual([blocked.player.x,blocked.player.y],[1,1]);assert.equal((await ui()).facing,'up');assert.equal((await ui()).hero_pose,'idle');
  });
  await test('Real enemy click animates every strike, its sound and progressive damage',async()=>{
    await page.waitForFunction(()=>{const a=JSON.parse(window.tower.ui_json()).audio;return a.unlocked&&a.enabled;});
    const effectsBefore=(await ui()).audio.effects_played;
    await cell(2,1);await sceneUntil('battle');
    const battle=(await state()).last_action.presentation.find(e=>e.type==='battle');assert.equal(battle.hero_strikes,3);assert.equal(battle.enemy_strikes,2);
    await page.waitForFunction(()=>{const b=JSON.parse(window.tower.ui_json()).battle;return b?.completed===1&&!b.hero_turn;});
    assert.deepEqual([(await ui()).battle.hero_hp,(await ui()).battle.enemy_hp],[100,11]);
    await page.waitForFunction(()=>{const b=JSON.parse(window.tower.ui_json()).battle;return b?.completed===2&&b.hero_turn;});
    assert.deepEqual([(await ui()).battle.hero_hp,(await ui()).battle.enemy_hp],[97,11]);
    await page.screenshot({path:resolve(output,'battle.png')});
    await idle();assert.equal((await state()).player.hp,94);assert.equal((await state()).player.gold,2);assert.equal((await state()).player.x,2);
    assert.equal((await ui()).audio.effects_played-effectsBefore,5,'Three hero strikes and two enemy strikes each play the original attack sound');
  });
  await test('Malformed JSON commands preserve an active battle, save, facing and sound state',async()=>{
    await importCampaign(corridor);
    await command({type:'move',direction:'right'});await idle();
    await command({type:'move',direction:'right'});await sceneUntil('battle');
    // Keep the comparison in one synchronous browser task. No animation frame
    // can advance naturally between these before/after snapshots.
    const result=await page.evaluate(()=>{
      const beforeUi=JSON.parse(window.tower.ui_json());
      const beforeSave=window.tower.save_json();
      const beforeState=window.tower.state_json();
      const rejected=[];
      for(const source of [
        'not json',
        '{"type":"move","direction":"diagonal"}',
        '{"type":"move","direction":"up","unexpected":true}',
        '{"type":"choose"}',
        '{"type":"new_game","unexpected":true}'
      ]) {
        try { window.tower.command_json(source);rejected.push(null); }
        catch(error) { rejected.push(String(error)); }
      }
      return {beforeUi,afterUi:JSON.parse(window.tower.ui_json()),beforeSave,afterSave:window.tower.save_json(),beforeState,afterState:window.tower.state_json(),rejected};
    });
    assert.equal(result.beforeUi.animation,'battle','The rejected input must arrive during an actual active animation');
    assert(result.rejected.every(error=>error?.includes('Invalid command')),JSON.stringify(result.rejected));
    assert.equal(result.afterSave,result.beforeSave,'Rejected commands must not mutate persistent game state');
    assert.equal(result.afterState,result.beforeState,'Rejected commands must not change last_action or the snapshot');
    for(const field of ['animation','presentation_remaining','path_remaining','facing','hero_pose','battle']) {
      assert.deepEqual(result.afterUi[field],result.beforeUi[field],`Rejected commands must preserve ${field}`);
    }
    assert.deepEqual(result.afterUi.audio,result.beforeUi.audio,'Rejected commands must not unlock or play audio');
    await idle();
  });
  await test('Invalid campaign/save import preserves the live session',async()=>{
    const before=(await state()).player;
    assert(await page.evaluate(()=>{try{window.tower.import_campaign('{"id":"broken"}');return false;}catch{return true;}}));
    assert(await page.evaluate(()=>{try{window.tower.load_save('broken');return false;}catch{return true;}}));assert.deepEqual((await state()).player,before);
  });
  await test('Actual old-man conversation rewards the Hero Orb and unlocks forecasts',async()=>{
    await importCampaign(original);await load(s=>{s.player.floor=3;s.player.x=9;s.player.y=3;});
    await page.keyboard.press('ArrowRight');await page.waitForFunction(()=>JSON.parse(window.tower.state_json()).pending_interaction);
    await dialogueInsideBoard();
    await button('choice:accept');await idle();assert((await state()).player.inventory.includes('hero_orb'));assert.equal((await state()).forecasts_unlocked,true);
    await button('choice:leave');await idle();
  });
  await test('English/Chinese switch persists and renders translated dialogue',async()=>{
    await page.evaluate(()=>window.tower.set_language('zh-CN'));await page.waitForTimeout(250);
    await page.keyboard.press('ArrowRight');await page.waitForTimeout(350);await page.screenshot({path:resolve(output,'chinese-dialogue.png')});
    assert.equal((await ui()).locale,'zh-CN');await command({type:'cancel'});await idle();await page.reload();await ready();assert.equal((await ui()).locale,'zh-CN');
  });
  await test('Floor-3 capture retains ordered magic, sound, conversations and teleport',async()=>{
    await page.evaluate(()=>window.tower.set_language('en'));await importCampaign(original);await load(s=>{s.player.floor=3;s.player.x=4;s.player.y=9;});
    await command({type:'move',direction:'up'});const s=await state();assert.deepEqual([s.floor,s.player.hp,s.player.attack,s.player.defense],[2,400,10,10]);
    assert(s.last_action.presentation.some(e=>e.type==='cinematic'&&e.kind==='magic'));
    assert.deepEqual(s.last_action.presentation.filter(e=>e.type==='cinematic').map(e=>e.kind),['magic','fade_out','title','scan','capture']);
    await cinematicUntil('magic');await page.waitForTimeout(150);await page.screenshot({path:resolve(output,'capture-magic.png')});
    await sceneUntil('dialogue');await page.waitForTimeout(700);const early=await ui();assert.equal(early.visual_floor,3);assert.equal(early.visual_player.hp,1000);assert(early.visual_player.inventory.includes('sword_5'));assert(!early.visual_log.some(t=>t.includes('escape tunnel')));
    await dialogueInsideBoard();
    await page.screenshot({path:resolve(output,'capture-dialogue.png')});await button('dialogue_continue');
    await sceneUntil('dialogue');await button('dialogue_continue');
    await cinematicUntil('title');assert.equal((await ui()).animation_details.at(-1).asset,'data3-title05');assert.equal((await ui()).visual_floor,3);await page.screenshot({path:resolve(output,'capture-title.png')});
    await cinematicUntil('scan');assert.equal((await ui()).animation_details.at(-1).asset,'data3-open2');assert.equal((await ui()).visual_floor,3);await page.waitForTimeout(1000);await page.screenshot({path:resolve(output,'capture-scan.png')});
    await sceneUntil('floor');
    await sceneUntil('dialogue');assert.equal((await ui()).visual_floor,2);assert.equal((await ui()).visual_player.hp,400);assert(!(await ui()).visual_player.inventory.includes('sword_5'));
    for(let n=0;n<3;n++){await button('dialogue_continue');await sceneUntil('dialogue');}
    await page.waitForTimeout(700);await page.screenshot({path:resolve(output,'capture-prison.png')});await button('dialogue_continue');await idle();
  });
  await test('Floor-10 skeleton trap plays its recovered guard movements',async()=>{
    await importCampaign(original);await load(s=>{s.player.floor=10;s.player.x=5;s.player.y=5;});await command({type:'move',direction:'up'});
    assert.equal((await state()).last_action.presentation.filter(e=>e.type==='move_tile').length,43);
    await sceneUntil('dialogue');await button('dialogue_continue');await sceneUntil('move_tile');await page.screenshot({path:resolve(output,'skeleton-trap.png')});await skip();
  });
  await test('Stairs in both directions use the original spiral wipe and sound',async()=>{
    await importCampaign(original);await load(s=>{s.player.x=1;s.player.y=0;});await command({type:'move',direction:'left'});
    await sceneUntil('floor');assert.equal((await state()).floor,2);
    const up=(await state()).last_action.presentation.find(e=>e.type==='floor');assert.deepEqual([up.direction,up.style,up.sound],['up','original_spiral','kai']);
    assert.equal((await ui()).animation_details.at(-1).style,'original_spiral');await page.screenshot({path:resolve(output,'stairs-up.png')});await idle();
    await command({type:'move',direction:'up'});await sceneUntil('floor');assert.equal((await state()).floor,1);
    const down=(await state()).last_action.presentation.find(e=>e.type==='floor');assert.deepEqual([down.direction,down.style,down.sound],['down','original_spiral','kai']);
    assert.equal((await ui()).animation_details.at(-1).style,'original_spiral');await page.screenshot({path:resolve(output,'stairs-down.png')});await idle();
  });
  await test('Floor-20 Vampire transformation preserves its original raster sequence',async()=>{
    await importCampaign(original);await load(s=>{s.player.floor=20;s.player.x=5;s.player.y=8;});await command({type:'move',direction:'up'});
    const transformation=(await state()).last_action.presentation.find(e=>e.type==='cinematic'&&e.kind==='transformation');
    assert.equal(transformation.tile,95);assert.equal(transformation.original_frames.length,32);
    await cinematicUntil('transformation');assert.equal((await ui()).visual_floor,20);await page.waitForTimeout(200);await page.screenshot({path:resolve(output,'vampire-transformation.png')});
    await sceneUntil('dialogue');await dialogueInsideBoard();await skip();
  });
  await test('Floor-49 Zeno and eight guards appear through their original magic masks',async()=>{
    await importCampaign(original);await load(s=>{s.player.floor=49;s.player.x=5;s.player.y=6;});await command({type:'move',direction:'up'});
    const magic=(await state()).last_action.presentation.filter(e=>e.type==='cinematic'&&e.kind==='magic');
    assert.equal(magic.length,2);assert.equal(magic[0].frames[0],166);assert.equal(magic[1].targets.length,8);
    await cinematicUntil('magic');assert.equal((await ui()).visual_floor,49);await page.waitForTimeout(150);await page.screenshot({path:resolve(output,'zeno-magic.png')});
    await sceneUntil('dialogue');await dialogueInsideBoard();await button('dialogue_continue');await cinematicUntil('magic');await page.waitForTimeout(300);await page.screenshot({path:resolve(output,'zeno-guard-magic.png')});await skip();
  });
  await test('First completion enters the backside tower and persists its cycle',async()=>{
    await importCampaign(original);await load(s=>{s.player.floor=50;s.player.x=5;s.player.y=5;s.floors['50'][49]=91;s.player.gold=123;});
    await command({type:'move',direction:'up'});assert.equal((await state()).cycle,2);assert.equal((await state()).backside_multiplier,44);assert.equal((await state()).player.gold,0);await skip();
    await page.reload();await ready();assert.equal((await state()).cycle,2);
  });
  await test('Visual floor painting, undo and validation work through the real editor',async()=>{
    await importCampaign(original);await button('editor');await page.waitForFunction(()=>JSON.parse(window.tower.ui_json()).editor_open);
    const layout=await ui();assert(layout.bounds.back_to_game.y+layout.bounds.back_to_game.h<=1000);assert(layout.editor.bounds.search.x>=layout.editor.bounds.board.x+layout.editor.bounds.board.width);
    await cell(0,0,true);await page.waitForFunction(()=>JSON.parse(window.tower.ui_json()).editor.dirty);
    await button('undo',true);assert.equal((await ui()).editor.dirty,false);
    await cell(0,0,true);await button('validate',true);assert.equal((await ui()).editor.valid,true);
    await page.screenshot({path:resolve(output,'editor-floors.png')});
  });
  await test('Visual enemy editing exports validated JSON and the draft can be played',async()=>{
    await button('tab.Enemies',true);const selected=(await ui()).editor.selected_enemy;const r=(await ui()).editor.bounds['enemy.hp'];
    await page.mouse.dblclick(r.cx,r.cy);await page.waitForTimeout(150);await page.keyboard.press('Control+a');await page.keyboard.type('137',{delay:40});await page.waitForTimeout(150);await page.keyboard.press('Enter');await page.waitForTimeout(150);
    await button('validate',true);assert.equal((await ui()).editor.valid,true);await page.screenshot({path:resolve(output,'editor-enemies.png')});
    const downloadPromise=page.waitForEvent('download');await button('export',true);const download=await downloadPromise;const exported=JSON.parse(readFileSync(await download.path(),'utf8'));
    assert.equal(exported.floors[0].tiles[0],6);assert.equal(exported.enemies[selected].hp,137);
    await button('play',true);await page.waitForFunction(()=>!JSON.parse(window.tower.ui_json()).editor_open);assert.equal((await state()).player.floor,1);
  });
  await test('Responsive Chinese mobile canvas and touch controls remain usable',async()=>{
    await importCampaign(original);await page.evaluate(()=>window.tower.set_language('zh-CN'));await page.setViewportSize({width:390,height:844});await page.waitForTimeout(400);
    const b=(await ui()).bounds.board;assert(b.x>=0&&b.x+b.w<=390,JSON.stringify(b));await page.waitForTimeout(6200);await page.screenshot({path:resolve(output,'mobile.png')});
    // Inventory now stays above the board on narrow screens. Reveal the board
    // through the workspace scroll before clicking a tile in its lower rows.
    await page.mouse.move(b.x+b.w/2,Math.min(760,b.y+20));
    await page.mouse.wheel(0,Math.max(0,b.y+b.h+24-844));await page.waitForTimeout(400);
    const visibleBoard=(await ui()).bounds.board;
    assert(visibleBoard.y>=0&&visibleBoard.y+visibleBoard.h<=844,JSON.stringify(visibleBoard));
    await cell(4,9);await idle();await heroIdle();assert.deepEqual([(await state()).player.x,(await state()).player.y,(await state()).player.keys.yellow],[4,9,1]);
  });
  await test('Chinese mobile conversations stay inside the game board',async()=>{
    await load(s=>{s.player.floor=3;s.player.x=9;s.player.y=3;});await cell(10,3);
    await page.waitForFunction(()=>JSON.parse(window.tower.state_json()).pending_interaction);await page.waitForTimeout(650);await dialogueInsideBoard();
    await page.screenshot({path:resolve(output,'mobile-dialogue.png')});await command({type:'cancel'});await idle();
  });
  assert.deepEqual(errors,[],'Browser should not raise JavaScript/Rust runtime errors');
  writeFileSync(resolve(output,'browser-report.json'),JSON.stringify({checks:report,errors},null,2));
  console.log(`Browser integration passed: ${report.length} checks using real Rust WebAssembly and actual pointer/keyboard input.`);
} catch(error) {
  await page.screenshot({path:resolve(output,'browser-failure.png')});
  writeFileSync(resolve(output,'browser-report.json'),JSON.stringify({checks:report,errors,failure:String(error)},null,2));throw error;
} finally {await browser.close();}
