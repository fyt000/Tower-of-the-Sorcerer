// Exercise the actual shared WebGL renderer, including pixel changes between
// phases. Scenario saves are isolated in this browser's temporary context.
import { chromium } from '@playwright/test';
import { readFileSync, writeFileSync, mkdirSync } from 'node:fs';
import { execFileSync } from 'node:child_process';
import { resolve } from 'node:path';
import assert from 'node:assert/strict';

const root = resolve(import.meta.dirname, '..');
const output = resolve(root, 'test-results', 'animations');
mkdirSync(output, { recursive: true });
const original = JSON.parse(readFileSync(resolve(root, 'data/campaign.json'), 'utf8'));
const browser = await chromium.launch({ headless: true, args: ['--use-angle=swiftshader-webgl', '--autoplay-policy=no-user-gesture-required'] });
const page = await browser.newPage({ viewport: { width: 1360, height: 1000 } });
const errors = [], tests = [], pictures = {};
page.on('pageerror', error => errors.push(error.message));
const ui = () => page.evaluate(() => JSON.parse(window.tower.ui_json()));
const state = () => page.evaluate(() => JSON.parse(window.tower.state_json()));
const command = action => page.evaluate(action => JSON.parse(window.tower.command_json(JSON.stringify(action))), action);
async function waitFor(predicate, argument) {
  await page.waitForFunction(predicate, argument, { timeout: 20000, polling: 'raf' });
}
async function idle() {
  await waitFor(() => { const u = JSON.parse(window.tower.ui_json()); return !u.animation && !u.presentation_remaining; });
}
function room() {
  const campaign = structuredClone(original);
  campaign.id = 'animation-rendering';
  campaign.width = campaign.height = 5;
  campaign.start = { floor: 1, x: 2, y: 2, hp: 10000, attack: 10, defense: 5, inventory: [], keys: { yellow: 1, blue: 1, red: 1 } };
  campaign.rules = { empty_tile: 6, wall_break_tile_ranges: [[8, 8]], presentation: { tile_transition_ms: 1200, ambient_frame_ms: 1000, combat_strike_ms: 1200 } };
  campaign.floors = [{ id: 1, tiles: Array(25).fill(6) }];
  campaign.events = [];
  campaign.interactions = [];
  campaign.enemies.green_slime = { name: 'Slime', hp: 20, attack: 8, defense: 1, gold: 2 };
  return campaign;
}
async function load(campaign) {
  await page.evaluate(source => window.tower.import_campaign(source), JSON.stringify(campaign));
  await idle();
  await page.mouse.move(0, 0);
  await page.waitForTimeout(80);
}
async function editSave(edit) {
  const saved = JSON.parse(await page.evaluate(() => window.tower.save_json()));
  edit(saved);
  await page.evaluate(saved => window.tower.load_save(JSON.stringify(saved)), saved);
  await idle();
}
async function animationSpeed(speed) {
  await page.evaluate(speed => {
    const key = 'tos-rust:prefs:v2';
    const prefs = JSON.parse(localStorage.getItem(key) || '{}');
    prefs.speed = speed;
    localStorage.setItem(key, JSON.stringify(prefs));
  }, speed);
  await page.reload();
  await waitFor(() => window.tower && JSON.parse(window.tower.ui_json()).sprites_loaded);
}
async function speech(id) {
  await waitFor(id => {
    const u = JSON.parse(window.tower.ui_json());
    return u.animation === 'dialogue' && u.animation_effect.dialogue_id === id && u.bounds.dialogue_continue;
  }, id);
}
async function continueSpeech() {
  const before = (await ui()).animation_effect.dialogue_id;
  // Enter follows the real conversation control without racing a modal's
  // first layout frame when successive speeches have different heights.
  await page.locator('canvas').focus();
  await page.keyboard.press('Enter');
  await waitFor(before => {
    const u = JSON.parse(window.tower.ui_json());
    return u.animation !== 'dialogue' || u.animation_effect.dialogue_id !== before;
  }, before);
}
async function phase(style, minimum = 0.35) {
  await waitFor(({ style, minimum }) => {
    const u = JSON.parse(window.tower.ui_json());
    return u.animation_effect?.style === style && u.animation_progress >= minimum && u.animation_progress < minimum + 0.25;
  }, { style, minimum });
}
async function capture(name, cell) {
  const before = await ui();
  const path = resolve(output, `${name}.png`);
  await page.screenshot({ path });
  pictures[name] = { path, board: before.bounds.board, cell, battle: before.battle, progress: before.animation_progress };
}
async function test(name, run) {
  await run();
  tests.push(name);
  console.log(`PASS ${name}`);
}

try {
  await page.goto(process.env.TOS_URL || 'http://127.0.0.1:8080');
  await waitFor(() => window.tower && JSON.parse(window.tower.ui_json()).sprites_loaded);
  await test('Previously published campaign and save migrate together', async () => {
    for (const [commit, fingerprint] of [['bbc5dd7', 'ad358ec82db8b9ef'], ['4c0ae3f', 'abd9d284f2e9b303'], ['2e0f15e', '689db6b6a00a3400'], ['2767a0c', '3a59316f31dbcd22']]) {
      const oldCampaign = execFileSync('git', ['show', `${commit}:data/campaign.json`], { cwd: root, encoding: 'utf8', maxBuffer: 4 * 1024 * 1024 });
      // Real previously shipped campaigns must upgrade with their progress.
      const saved = JSON.parse(await page.evaluate(() => window.tower.save_json()));
      saved.campaign_fingerprint = fingerprint;
      saved.cycle = 2; saved.steps = 432; saved.player.hp = 8123;
      saved.flags = ['captured']; saved.event_counts = { capture_on_floor_3: 1 };
      saved.visited_floors = [1, 32, 42]; saved.highest_stair_floor = 42;
      await page.evaluate(({ campaign, saved }) => {
        localStorage.setItem('tos-rust:campaign:v1', campaign);
        localStorage.setItem('tos-rust:save:v1', JSON.stringify(saved));
      }, { campaign: oldCampaign, saved });
      await page.reload();
      await waitFor(() => window.tower && JSON.parse(window.tower.ui_json()).sprites_loaded);
      const current = await state();
      assert.deepEqual([current.cycle, current.steps, current.player.hp], [2, 432, 8123]);
      const migrated = JSON.parse(await page.evaluate(() => window.tower.save_json()));
      assert.deepEqual(migrated.event_counts, { capture_on_floor_3: 1,
        floor_32_golden_knight_arrival: 1, floor_32_golden_knight_retreat: 1,
        floor_42_zeno_and_golden_knight_arrival: 1 });
      assert.deepEqual(migrated.flags, ['captured']);
      assert(await page.evaluate(() => localStorage.getItem('tos-rust:save:recovery')));
    }
  });
  await test('Altar eye pixels blink while its body stays still', async () => {
    const campaign = room(); campaign.floors[0].tiles[0] = 16; campaign.floors[0].tiles[5] = 15;
    await load(campaign);
    await waitFor(() => JSON.parse(window.tower.ui_json()).ambient_frame === 0);
    await capture('altar-open', [0, 0]);
    await waitFor(() => JSON.parse(window.tower.ui_json()).ambient_frame === 1);
    await capture('altar-closed', [0, 0]);
  });
  await test('Every colored door slides open before travel and stays open', async () => {
    for (const tile of [1, 2, 3]) {
      const campaign = room(); campaign.floors[0].tiles[13] = tile;
      await load(campaign); await capture(`door-${tile}-closed`, [3, 2]);
      const soundBefore = (await ui()).audio.effects_played;
      await command({ type: 'move', direction: 'right' });
      assert.equal((await state()).tiles[13], 6);
      await phase('door_open');
      const middle = await ui(); assert.equal(middle.visual_player.x, 2); assert.equal(middle.visual_tiles[13], tile);
      await capture(`door-${tile}-middle`, [3, 2]);
      await waitFor(() => JSON.parse(window.tower.ui_json()).animation === 'tile');
      assert.equal((await ui()).visual_tiles[13], 6, 'Opening must not flash the closed door again');
      await idle(); assert.equal((await state()).player.x, 3);
      assert.equal((await ui()).audio.effects_played - soundBefore, 1);
    }
  });
  await test('Pickaxe walls collapse vertically and Bomb enemies dissolve', async () => {
    for (const item of ['mattock', 'super_mattock', 'bomb']) {
      const campaign = room(); campaign.start.inventory = [item]; campaign.floors[0].tiles[11] = item === 'bomb' ? 61 : 8;
      await load(campaign); await capture(`${item}-before`, [1, 2]);
      await command({ type: 'use_item', item });
      await phase(item === 'bomb' ? 'dissolve' : 'wall_collapse');
      await capture(`${item}-middle`, [1, 2]);
      await waitFor(() => JSON.parse(window.tower.ui_json()).animation === 'tile');
      assert.equal((await ui()).visual_tiles[11], 6);
      await idle(); await capture(`${item}-after`, [1, 2]);
      assert.equal((await state()).tiles[11], 6);
    }
  });
  await test('Sealed gate closes with four quadrants and opens with the same geometry', async () => {
    const campaign = room();
    campaign.events = [{ id: 'close', trigger: { type: 'step', floor: 1, x: 3, y: 2 }, effects: [{ type: 'set_tile', floor: 1, x: 0, y: 0, tile: 4 }] },
      { id: 'open', trigger: { type: 'step', floor: 1, x: 4, y: 2 }, effects: [
        { type: 'cinematic', kind: 'tile_reveal', style: 'gate_open', floor: 1, x: 0, y: 0, from_tile: 6, tile: 6, duration_ms: 1200 },
        { type: 'set_tile', floor: 1, x: 0, y: 0, tile: 6 }] }];
    await load(campaign); await capture('gate-road', [0, 0]);
    await command({ type: 'move', direction: 'right' }); await phase('gate_close'); await capture('gate-closing', [0, 0]); await idle(); await capture('gate-closed', [0, 0]);
    await command({ type: 'move', direction: 'right' }); await phase('gate_open'); await capture('gate-opening', [0, 0]); await idle();
    assert.equal((await state()).tiles[0], 6);
  });
  await test('Retreating magician moves once, including when Sacred Shield suppresses its hit', async () => {
    for (const protectedByShield of [false, true]) {
      const campaign = room(); campaign.start.y = 3;
      campaign.start.inventory = protectedByShield ? ['sacred_shield'] : [];
      campaign.floors[0].tiles[13] = 151;
      campaign.rules.magician_retreat = { floor: 1, special: 'magician_a', bounds: 'corrected' };
      await load(campaign); await command({ type: 'move', direction: 'up' });
      await waitFor(() => JSON.parse(window.tower.ui_json()).animation === 'move_tile');
      const moving = (await ui()).animation_effect;
      assert.deepEqual([moving.from_x, moving.x, moving.tile], [3, 4, 151]);
      await idle(); const finished = await state();
      assert.deepEqual([finished.tiles[13], finished.tiles[14], finished.player.hp], [6, 151, protectedByShield ? 10000 : 9800]);
      assert.equal((await ui()).visual_tiles[14], 151);
    }
  });
  await test('32F Knight approaches, battles, retreats and stays gone after another climb', async () => {
    await load(original);
    await editSave(saved => {
      Object.assign(saved.player, { floor: 31, x: 4, y: 10, hp: 5000, attack: 70, defense: 100, gold: 7 });
      saved.floors['29'][17] = 21;
    });
    await command({ type: 'move', direction: 'right' });
    await waitFor(() => {
      const u = JSON.parse(window.tower.ui_json());
      return u.animation === 'move_tile' && u.animation_effect.from_y === 0 && u.visual_floor === 32;
    });
    await capture('32f-knight-approach', [7, 0]);
    await speech(29);
    assert.equal((await ui()).visual_player.hp, 5000);
    await continueSpeech();
    await speech(30);
    assert.deepEqual([(await ui()).visual_player.hp, (await ui()).visual_player.gold], [4700, 107]);
    await continueSpeech();
    await waitFor(() => {
      const u = JSON.parse(window.tower.ui_json());
      return u.animation === 'move_tile' && u.animation_effect.from_y === 9 && u.animation_effect.y === 8;
    });
    await capture('32f-knight-retreat', [5, 8]);
    await idle();
    const done = await state();
    assert.deepEqual([done.floor, done.player.x, done.player.y, done.tiles[9], done.tiles[104]], [32, 5, 9, 6, 6]);
    assert.equal((await ui()).visual_tiles[9], 6);
    await editSave(saved => Object.assign(saved.player, { floor: 31, x: 4, y: 10 }));
    await command({ type: 'move', direction: 'right' });
    await idle();
    assert.deepEqual([(await state()).player.hp, (await state()).player.gold], [4700, 107]);
    assert(!(await state()).last_action.presentation.some(e => ['battle', 'move_tile', 'dialogue'].includes(e.type)));
  });
  await test('42F Zeno and guards materialize, Knight is executed, and every actor disappears', async () => {
    // Use the normal Slow preference so a screenshot finishes inside the
    // original 125ms impact. The campaign's recovered durations stay intact.
    await animationSpeed(0.5);
    await load(original);
    await editSave(saved => Object.assign(saved.player, { floor: 41, x: 4, y: 10 }));
    const before = await state();
    await command({ type: 'move', direction: 'right' });
    await waitFor(() => {
      const u = JSON.parse(window.tower.ui_json());
      return u.animation_effect?.kind === 'magic' && u.animation_effect.targets?.length === 4;
    });
    await capture('42f-guard-materialization', [5, 6]);
    await speech(40);
    const staged = await ui();
    assert.equal(staged.visual_tiles[60], 91);
    assert.equal(staged.visual_tiles[82], 133);
    for (const target of [71, 93, 81, 83]) assert.equal(staged.visual_tiles[target], 93);
    await capture('42f-knight-and-zeno', [5, 7]);
    await continueSpeech(); await speech(41); await continueSpeech(); await speech(42); await continueSpeech();
    await waitFor(() => {
      const u = JSON.parse(window.tower.ui_json());
      return u.animation_effect?.kind === 'magic' && u.animation_effect.color_tile === 184;
    });
    assert.equal((await ui()).visual_tiles[82], 133);
    await capture('42f-knight-execution', [5, 7]);
    await speech(43); await continueSpeech(); await idle();
    const done = await state(), rendered = await ui();
    assert.deepEqual([done.player.hp, done.player.gold], [before.player.hp, before.player.gold]);
    for (const target of [60, 71, 93, 81, 83, 82]) {
      assert.equal(done.tiles[target], 6);
      assert.equal(rendered.visual_tiles[target], 6);
    }
    await capture('42f-after-execution', [5, 7]);
    assert(!done.last_action.presentation.some(e => e.type === 'battle'));
    await animationSpeed(1);
  });
  await test('Every hero and enemy strike has clean, impact and clean phases', async () => {
    const campaign = room(); campaign.floors[0].tiles[13] = 61;
    campaign.rules.presentation.ambient_frame_ms = 150;
    await load(campaign);
    const effectsBefore = (await ui()).audio.effects_played;
    await command({ type: 'move', direction: 'right' });
    for (let strike = 0; strike < 5; strike++) {
      for (const [label, low, high, impact] of [['before', 0.08, 0.26, false], ['impact', 0.40, 0.60, true], ['after', 0.74, 0.93, false]]) {
        await waitFor(({ strike, low, high }) => { const b = JSON.parse(window.tower.ui_json()).battle; return b?.strike === strike && b.phase >= low && b.phase < high; }, { strike, low, high });
        assert.equal((await ui()).battle.impact_visible, impact);
        await capture(`strike-${strike}-${label}`, [3, 2]);
      }
    }
    await idle(); const s = await state(); assert.equal(s.player.hp, 9994); assert.equal(s.player.gold, 2);
    assert.equal((await ui()).audio.effects_played - effectsBefore, 5);
  });
  await test('Magic-field damage uses the entered square and clears its hit pose', async () => {
    const campaign = room(); campaign.floors[0].tiles[8] = 151;
    await load(campaign); await command({ type: 'move', direction: 'right' });
    await waitFor(() => { const u = JSON.parse(window.tower.ui_json()); return u.animation === 'damage' && u.battle?.impact_visible; });
    assert.equal((await ui()).visual_player.x, 3);
    await capture('field-impact', [3, 2]); await idle();
    assert.equal((await state()).player.hp, 9800);
    assert.equal((await ui()).battle, null);
  });
  assert.deepEqual(errors, []);
  const report = resolve(output, 'report.json');
  writeFileSync(report, JSON.stringify({ tests, pictures, errors }, null, 2));
  const pixels = execFileSync('python', ['-c', `
import json,sys
from PIL import Image,ImageChops,ImageStat
r=json.load(open(sys.argv[1],encoding='utf-8'));p=r['pictures']
def crop(name,cell=None):
 s=p[name];b=s['board'];x,y=cell or s['cell'];c=b['cell'];left=round(b['x']+x*c);top=round(b['y']+y*c)
 return Image.open(s['path']).convert('RGB').crop((left,top,left+c,top+c))
def diff(a,b):return sum(ImageStat.Stat(ImageChops.difference(a,b)).mean)/3
eye=diff(crop('altar-open'),crop('altar-closed'));body=diff(crop('altar-open',[0,1]),crop('altar-closed',[0,1]))
assert eye>1,(eye,body)
assert body==0,(eye,body)
for tile in (1,2,3):assert diff(crop(f'door-{tile}-closed'),crop(f'door-{tile}-middle'))>10
for item in ('mattock','super_mattock','bomb'):
 assert diff(crop(f'{item}-before'),crop(f'{item}-middle'))>5,item
 assert diff(crop(f'{item}-middle'),crop(f'{item}-after'))>5,item
def center(image):
 w,h=image.size
 return image.crop((round(w*.4),round(h*.4),round(w*.6),round(h*.6)))
road=crop('gate-road')
for name in ('gate-closing','gate-opening'):
 assert diff(crop(name),road)>5,name
 assert diff(center(crop(name)),center(road))==0,name
for i in range(5):
 before,hit,after=(crop(f'strike-{i}-{phase}') for phase in ('before','impact','after'))
 clean=diff(before,after);impact=diff(hit,after)
 assert impact>15,(i,clean,impact)
 assert clean<impact*0.4,(i,clean,impact)
assert diff(crop('42f-knight-execution'),crop('42f-after-execution'))>5
print('PASS rendered pixels: blinking eyes/still body, sliding doors, four gate quadrants, falling walls, Bomb dissolve, all five impact pulses, Knight execution/cleanup')
` , report], { encoding: 'utf8' });
  console.log(pixels.trim());
} finally {
  await browser.close();
}
