import { chromium } from '@playwright/test';
import { readFileSync, writeFileSync, mkdirSync } from 'node:fs';
import { resolve } from 'node:path';
import assert from 'node:assert/strict';

const root=resolve(import.meta.dirname,'..'), output=resolve(root,'test-results');
mkdirSync(output,{recursive:true});
const original=readFileSync(resolve(root,'data/campaign.json'),'utf8');
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
  await page.mouse.click(r.cx??r.x+(r.width??r.w)/2,r.cy??r.y+(r.height??r.h)/2);
  await page.waitForTimeout(150);
}
async function cell(x,y,editor=false){const u=await ui(),r=editor?u.editor.bounds.board:u.bounds.board;
  const w=editor?u.editor.width:r.width,h=editor?u.editor.height:r.height;
  await page.mouse.click(r.x+(x+.5)*(r.w??r.width)/w,r.y+(y+.5)*(r.h??r.height)/h);
  await page.waitForTimeout(150);
}
async function command(action){return page.evaluate(action=>JSON.parse(window.tower.command_json(JSON.stringify(action))),action);}
async function load(change){const save=JSON.parse(await page.evaluate(()=>window.tower.save_json()));change(save);await page.evaluate(source=>window.tower.load_save(source),JSON.stringify(save));await page.waitForTimeout(100);}
async function importCampaign(source){await page.evaluate(source=>window.tower.import_campaign(source),source);await idle();await page.waitForTimeout(100);}
async function skip(){if((await ui()).animation||(await ui()).presentation_remaining)await button('skip');await idle();}
async function sceneUntil(type){await page.waitForFunction(type=>JSON.parse(window.tower.ui_json()).animation===type,type,{timeout:20000});}

const corridor=JSON.stringify({id:'browser-regression',title:'Browser test',width:5,height:3,
  start:{floor:1,x:0,y:1,hp:100,attack:10,defense:5,gold:0,keys:{yellow:0,blue:0,red:0},inventory:[]},
  rules:{empty_tile:6,forecast_requires_item:'hero_orb'},
  floors:[{id:1,title:'Corridor',tiles:[8,8,8,8,8,6,6,61,6,29,8,8,8,8,8]}],
  tiles:{6:{name:'Road',kind:'floor',sprite:6},8:{name:'Wall',kind:'wall',sprite:8},61:{name:'Slime',kind:'enemy',enemy:'slime',sprite:61},29:{name:'Yellow key',kind:'key',key:'yellow',amount:1,sprite:29}},
  enemies:{slime:{name:'Slime',hp:20,attack:8,defense:1,gold:2}},events:[]});

try {
  await page.goto(process.env.TOS_URL||'http://127.0.0.1:8080');await ready();await page.waitForTimeout(500);
  await test('Rust WebGL board and readable desktop layout',async()=>{
    const s=await state(),u=await ui();assert.equal(s.floors.length,51);assert.equal(s.width,11);
    const b=u.bounds.board;assert(b.x>=0&&b.x+b.w<=1440&&b.y+b.h<=1000,JSON.stringify(b));
    assert.equal(u.sprites_loaded,true);await page.screenshot({path:resolve(output,'desktop.png')});
    await page.setViewportSize({width:1360,height:920});await page.waitForTimeout(150);
    const compact=(await ui()).bounds;
    assert(compact.board.y+compact.board.h<920);
    assert(compact.right.y+compact.right.h<=892,'Movement controls must fit the default native-sized viewport');
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
  await test('Actual mouse click follows road and collects the selected key',async()=>{
    await cell(4,9);await idle();const s=await state();assert.deepEqual([s.player.x,s.player.y,s.player.keys.yellow],[4,9,1]);
  });
  await test('Original WAV effects and configured MIDI music play through WebAudio',async()=>{
    await page.waitForFunction(()=>{const a=JSON.parse(window.tower.ui_json()).audio;return a.unlocked&&a.effects_played>0&&a.music;},undefined,{timeout:20000});
    assert.equal((await ui()).audio.error,null);assert.match((await ui()).audio.music,/b_067xgw/);
  });
  await test('Independent browser checkpoint survives further autosaves',async()=>{
    await button('save');const saved=(await state()).player;await page.keyboard.press('ArrowRight');await page.waitForTimeout(150);await idle();assert.notDeepEqual((await state()).player,saved);
    await button('restore');await idle();assert.deepEqual((await state()).player,saved);
  });
  await test('Browser autosave resumes after reload',async()=>{
    const saved=(await state()).player;await page.reload();await ready();assert.deepEqual((await state()).player,saved);
  });
  await test('Mouse route cannot cross an intermediate enemy',async()=>{
    await importCampaign(corridor);await cell(4,1);await idle();const s=await state();assert.equal(s.player.x,1);assert.equal(s.player.hp,100);assert.equal(s.tiles[7],61);
  });
  await test('Enemy hover/inspection numerical details stay gated',async()=>{
    const locked=await page.evaluate(()=>JSON.parse(window.tower.inspect_json(2,1)));assert.equal(locked.details_locked,true);assert.equal(locked.enemy,null);assert.deepEqual((await state()).enemies,[]);
  });
  await test('Real enemy click animates alternating combat and commits exact damage',async()=>{
    await cell(2,1);await sceneUntil('battle');await page.screenshot({path:resolve(output,'battle.png')});
    const battle=(await state()).last_action.presentation.find(e=>e.type==='battle');assert.equal(battle.hero_strikes,3);assert.equal(battle.enemy_strikes,2);
    await idle();assert.equal((await state()).player.hp,94);assert.equal((await state()).player.gold,2);assert.equal((await state()).player.x,2);
  });
  await test('Invalid campaign/save import preserves the live session',async()=>{
    const before=(await state()).player;
    assert(await page.evaluate(()=>{try{window.tower.import_campaign('{"id":"broken"}');return false;}catch{return true;}}));
    assert(await page.evaluate(()=>{try{window.tower.load_save('broken');return false;}catch{return true;}}));assert.deepEqual((await state()).player,before);
  });
  await test('Actual old-man conversation rewards the Hero Orb and unlocks forecasts',async()=>{
    await importCampaign(original);await load(s=>{s.player.floor=3;s.player.x=9;s.player.y=3;});
    await page.keyboard.press('ArrowRight');await page.waitForFunction(()=>JSON.parse(window.tower.state_json()).pending_interaction);
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
    await sceneUntil('cinematic');await page.waitForTimeout(150);await page.screenshot({path:resolve(output,'capture-magic.png')});
    await sceneUntil('dialogue');await page.waitForTimeout(700);const early=await ui();assert.equal(early.visual_floor,3);assert.equal(early.visual_player.hp,1000);assert(early.visual_player.inventory.includes('sword_5'));assert(!early.visual_log.some(t=>t.includes('escape tunnel')));
    await page.screenshot({path:resolve(output,'capture-dialogue.png')});await button('dialogue_continue');
    await sceneUntil('dialogue');await button('dialogue_continue');await sceneUntil('cinematic');await sceneUntil('floor');
    await sceneUntil('dialogue');assert.equal((await ui()).visual_floor,2);assert.equal((await ui()).visual_player.hp,400);assert(!(await ui()).visual_player.inventory.includes('sword_5'));
    for(let n=0;n<3;n++){await button('dialogue_continue');await sceneUntil('dialogue');}
    await page.waitForTimeout(700);await page.screenshot({path:resolve(output,'capture-prison.png')});await button('dialogue_continue');await idle();
  });
  await test('Floor-10 skeleton trap plays its recovered guard movements',async()=>{
    await importCampaign(original);await load(s=>{s.player.floor=10;s.player.x=5;s.player.y=5;});await command({type:'move',direction:'up'});
    assert.equal((await state()).last_action.presentation.filter(e=>e.type==='move_tile').length,43);
    await sceneUntil('dialogue');await button('dialogue_continue');await sceneUntil('move_tile');await page.screenshot({path:resolve(output,'skeleton-trap.png')});await skip();
  });
  await test('Stair transitions animate before the landing state becomes visible',async()=>{
    await importCampaign(original);await load(s=>{s.player.x=1;s.player.y=0;});await command({type:'move',direction:'left'});
    await sceneUntil('floor');assert.equal((await state()).floor,2);await idle();
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
    await button('up');await idle();assert.equal((await state()).player.y,9);
  });
  assert.deepEqual(errors,[],'Browser should not raise JavaScript/Rust runtime errors');
  writeFileSync(resolve(output,'browser-report.json'),JSON.stringify({checks:report,errors},null,2));
  console.log(`Browser integration passed: ${report.length} checks using real Rust WebAssembly and actual pointer/keyboard input.`);
} catch(error) {
  await page.screenshot({path:resolve(output,'browser-failure.png')});
  writeFileSync(resolve(output,'browser-report.json'),JSON.stringify({checks:report,errors,failure:String(error)},null,2));throw error;
} finally {await browser.close();}
