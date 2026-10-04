import { chromium } from '@playwright/test';
import { readFileSync, mkdirSync } from 'node:fs';
import { resolve } from 'node:path';
import assert from 'node:assert/strict';

const root = resolve(import.meta.dirname, '..');
const output = resolve(root, 'test-results');
mkdirSync(output, { recursive: true });
const original = JSON.parse(readFileSync(resolve(root, 'data/campaign.json'), 'utf8'));
const tiles = Array(121).fill(6);
tiles[5 * 11 + 6] = 61;
tiles[5 * 11 + 7] = 62;
const fixture = JSON.stringify({
  id: 'single-inspection-regression', title: 'Inspection test', width: 11, height: 11,
  start: { floor: 1, x: 5, y: 5, hp: 100, attack: 10, defense: 5, gold: 0, inventory: [] },
  rules: { empty_tile: 6, forecast_requires_item: 'hero_orb', presentation: { combat_strike_ms: 300 } },
  floors: [{ id: 1, title: 'Inspection room', tiles }],
  tiles: { 6: original.tiles['6'], 8: original.tiles['8'], 36: original.tiles['36'],
    61: { name: 'Guard', kind: 'enemy', enemy: 'guard', sprite: 61 },
    62: { name: 'Scout', kind: 'enemy', enemy: 'scout', sprite: 62 } },
  enemies: { guard: { name: 'Guard', hp: 1000, attack: 90, defense: 40, gold: 20 },
    scout: { name: 'Scout', hp: 150, attack: 30, defense: 5, gold: 42 } },
  events: []
});
const browser = await chromium.launch({ headless: true,
  args: ['--use-angle=swiftshader-webgl', '--autoplay-policy=no-user-gesture-required'] });
const state = page => page.evaluate(() => JSON.parse(window.tower.state_json()));
const ui = page => page.evaluate(() => JSON.parse(window.tower.ui_json()));
const save = page => page.evaluate(() => JSON.parse(window.tower.save_json()));

async function idle(page) {
  await page.waitForFunction(() => { const s = JSON.parse(window.tower.ui_json());
    return !s.animation && !s.presentation_remaining && !s.path_remaining;
  }, undefined, { timeout: 10000 });
}

function cell(bounds, x, y) {
  const board = bounds.board;
  return { x: board.x + (x + 0.5) * board.w / board.width,
    y: board.y + (y + 0.5) * board.h / board.height };
}

function visible(rect, viewport) {
  return rect && rect.x >= 0 && rect.y >= 0
    && rect.x + (rect.w ?? 0) <= viewport.width + 1
    && rect.y + (rect.h ?? 0) <= viewport.height + 1;
}

function exclusive(bounds, active = null) {
  for (const id of ['last_encounter', 'inspection_target', 'inspection_battle']) {
    assert.equal(Boolean(bounds[id]), id === active, `Only ${active} may be the active inspection: ${id}`);
  }
}

async function hover(page, x, y) {
  const point = cell((await ui(page)).bounds, x, y);
  await page.mouse.move(point.x, point.y);
  await page.waitForTimeout(250);
}

async function changeSave(page, change) {
  const saved = await save(page);
  change(saved);
  await page.evaluate(source => window.tower.load_save(source), JSON.stringify(saved));
  await page.waitForTimeout(250);
}

async function touchDrag(cdp, from, to) {
  await cdp.send('Input.dispatchTouchEvent', { type: 'touchStart', touchPoints: [from] });
  await new Promise(resolve => setTimeout(resolve, 70));
  for (let index = 1; index <= 12; index++) {
    await cdp.send('Input.dispatchTouchEvent', { type: 'touchMove', touchPoints: [{
      x: from.x + (to.x - from.x) * index / 12,
      y: from.y + (to.y - from.y) * index / 12
    }] });
    await new Promise(resolve => setTimeout(resolve, 25));
  }
  await cdp.send('Input.dispatchTouchEvent', { type: 'touchEnd', touchPoints: [] });
}

async function revealCell(page, cdp, viewport, x, y) {
  for (let attempt = 0; attempt < 10; attempt++) {
    const point = cell((await ui(page)).bounds, x, y);
    if (visible(point, viewport)) return point;
    const down = point.y < 0;
    await touchDrag(cdp,
      { x: viewport.width / 2, y: down ? 170 : viewport.height - 70 },
      { x: viewport.width / 2, y: down ? viewport.height - 70 : 170 });
    await page.waitForTimeout(250);
  }
  assert.fail(`Tile ${x},${y} remains unreachable in the scrollable mobile workspace`);
}

try {
  for (const viewport of [{ width: 1440, height: 1000 }, { width: 390, height: 844 },
    { width: 844, height: 390 }]) {
    if (process.env.TOS_INSPECTION_WIDTH && Number(process.env.TOS_INSPECTION_WIDTH) !== viewport.width) continue;
    for (const locale of ['en', 'zh-CN']) {
      const mobile = viewport.width < 500;
      const context = await browser.newContext({ viewport, hasTouch: mobile });
      const page = await context.newPage();
      const errors = [];
      page.on('pageerror', error => errors.push(error.message));
      try {
        await page.goto(process.env.TOS_URL || 'http://127.0.0.1:8080');
        await page.waitForFunction(() => window.tower && JSON.parse(window.tower.ui_json()).sprites_loaded,
          undefined, { timeout: 45000 });
        await page.evaluate(({ fixture, locale }) => {
          window.tower.import_campaign(fixture);
          window.tower.set_language(locale);
        }, { fixture, locale });
        await page.waitForTimeout(locale === 'zh-CN' ? 1600 : 500);
        await idle(page);
        if (viewport.height > 720) assert((await ui(page)).bounds.inspection_locked_hint,
          'The idle Hero requirement is explained before acquisition');

        if (!mobile) {
          const initial = await save(page);
          await hover(page, 6, 5);
          let bounds = (await ui(page)).bounds;
          exclusive(bounds, 'inspection_target');
          assert.equal(bounds.inspection_contact, undefined, 'An unseen enemy has no raw contact stats');
          assert.equal(bounds.inspection_forecast, undefined, 'Hero is required for an advance forecast');
          await page.mouse.move(5, 5);
          await page.waitForTimeout(200);
          exclusive((await ui(page)).bounds, 'inspection_target');
          assert.deepEqual(await save(page), initial, 'Hovering and reading do not dispatch game actions');

          await page.keyboard.press('ArrowRight');
          await page.waitForTimeout(200);
          await idle(page);
          bounds = (await ui(page)).bounds;
          exclusive(bounds);
          const contacted = await state(page);
          assert.deepEqual([contacted.last_encounter.hp, contacted.last_encounter.attack,
            contacted.last_encounter.defense], [1000, 90, 40]);
          assert.deepEqual([contacted.player.x, contacted.player.y, contacted.player.hp], [5, 5, 100]);

          await hover(page, 6, 5);
          bounds = (await ui(page)).bounds;
          exclusive(bounds, 'inspection_target');
          assert(bounds.inspection_contact, 'The selected actually contacted enemy shows raw HP/ATK/DEF');
          assert.equal(bounds.inspection_forecast, undefined, 'Actual contact does not unlock forecasts');
          await hover(page, 7, 5);
          bounds = (await ui(page)).bounds;
          exclusive(bounds, 'inspection_target');
          assert.equal(bounds.inspection_contact, undefined, 'Contact stats are not reused for another enemy');
          assert.equal(bounds.inspection_forecast, undefined);

          await page.mouse.move(5, 5);
          await changeSave(page, saved => {
            saved.player.inventory.push('hero_orb');
            saved.last_encounter = null;
          });
          assert.equal((await ui(page)).bounds.inspection_locked_hint, undefined,
            'The idle panel does not request an already-owned Hero Orb');
          await hover(page, 7, 5);
          bounds = (await ui(page)).bounds;
          exclusive(bounds, 'inspection_target');
          assert(bounds.inspection_forecast, 'Hero enables the selected enemy forecast');
          assert.equal(bounds.inspection_contact, undefined, 'Raw contact is not duplicated below a forecast');
          if (viewport.height <= 720) {
            const rows = ['hp', 'attack', 'defense', 'gold', 'damage'].map(key => bounds[`inspection_stat:${key}`]);
            assert(rows.every(row => row && row.h === 22), 'Landscape stats have readable icon-number rows');
            for (let index = 1; index < rows.length; index++) {
              assert(rows[index].y >= rows[index - 1].y + rows[index - 1].h,
                'Each landscape stat has its own vertical row');
            }
          }
          await page.mouse.move(5, 5);
          await page.waitForTimeout(250);
          assert((await ui(page)).bounds.inspection_forecast, 'Leaving the board keeps the inspected target readable');
          await page.screenshot({ path: resolve(output, `inspection-single-forecast-${locale}.png`) });

          await changeSave(page, saved => {
            saved.player.x = 7; saved.player.y = 6;
            saved.player.hp = 1000; saved.player.attack = 100; saved.player.defense = 50;
          });
          await page.keyboard.press('ArrowUp');
          await page.waitForFunction(() => JSON.parse(window.tower.ui_json()).animation === 'battle');
          bounds = (await ui(page)).bounds;
          exclusive(bounds);
          const overlay = bounds.battle_overlay, board = bounds.board;
          assert(overlay, 'Active combat has a separate faint overlay on the floor');
          assert(overlay.x >= board.x && overlay.y >= board.y && overlay.x + overlay.w <= board.x + board.w
            && overlay.y + overlay.h <= board.y + board.h, 'The combat overlay stays inside the board');
          assert.deepEqual([overlay.enemy_max_hp, overlay.attack, overlay.defense, overlay.gold], [150, 30, 5, 42]);
          await idle(page);
          bounds = (await ui(page)).bounds;
          exclusive(bounds);
          assert.equal(bounds.battle_overlay, undefined, 'The combat overlay disappears after the fight');
        } else {
          const cdp = await context.newCDPSession(page);
          let bounds = (await ui(page)).bounds;
          const target = await revealCell(page, cdp, viewport, 6, 5);
          assert(visible(target, viewport), 'The mobile target is on screen');
          await page.touchscreen.tap(target.x, target.y);
          await page.waitForTimeout(250);
          await idle(page);
          assert((await state(page)).last_encounter, 'A real touch tap still routes and contacts the enemy');
          exclusive((await ui(page)).bounds);
          const secondContact = await revealCell(page, cdp, viewport, 6, 5);
          await page.touchscreen.tap(secondContact.x, secondContact.y);
          await page.waitForTimeout(250);
          await idle(page);
          const contactSave = await save(page);
          for (let attempt = 0; attempt < 8; attempt++) {
            bounds = (await ui(page)).bounds;
            if (visible(bounds.inspection_target, viewport)) break;
            await touchDrag(cdp, { x: viewport.width / 2, y: viewport.height - 70 },
              { x: viewport.width / 2, y: 200 });
            await page.waitForTimeout(300);
          }
          bounds = (await ui(page)).bounds;
          exclusive(bounds, 'inspection_target');
          assert(bounds.inspection_contact, 'The selected contacted enemy shows its raw stats');
          assert(visible(bounds.inspection_target, viewport), 'Selected contact info is readable after mobile scrolling');
          assert.deepEqual(await save(page), contactSave, 'Scrolling the inspection dispatches no action');

          await changeSave(page, saved => saved.player.inventory.push('hero_orb'));
          for (let attempt = 0; attempt < 8; attempt++) {
            bounds = (await ui(page)).bounds;
            if (visible(cell(bounds, 4, 5), viewport)) break;
            await touchDrag(cdp, { x: viewport.width / 2, y: 200 },
              { x: viewport.width / 2, y: viewport.height - 70 });
            await page.waitForTimeout(300);
          }
          const road = cell((await ui(page)).bounds, 4, 5);
          assert(visible(road, viewport));
          await page.touchscreen.tap(road.x, road.y);
          await page.waitForTimeout(200);
          await idle(page);
          assert.deepEqual([(await state(page)).player.x, (await state(page)).player.y], [4, 5],
            'Real mobile tap keeps ordinary route movement');
          const afterTap = await save(page);
          bounds = (await ui(page)).bounds;
          exclusive(bounds, 'inspection_target');
          assert.deepEqual([bounds.inspection_target.tile_x, bounds.inspection_target.tile_y], [4, 5]);
          for (let attempt = 0; attempt < 8; attempt++) {
            bounds = (await ui(page)).bounds;
            if (visible(bounds.inspection_target, viewport)) break;
            await touchDrag(cdp, { x: viewport.width / 2, y: viewport.height - 70 },
              { x: viewport.width / 2, y: 200 });
            await page.waitForTimeout(300);
          }
          bounds = (await ui(page)).bounds;
          assert(visible(bounds.inspection_target, viewport), 'The tapped target remains readable after scrolling');
          assert.deepEqual([bounds.inspection_target.tile_x, bounds.inspection_target.tile_y], [4, 5],
            'Touch drag does not replace the selected tile with crossed board cells');
          exclusive(bounds, 'inspection_target');
          assert.deepEqual(await save(page), afterTap);
          await page.screenshot({ path: resolve(output, `inspection-mobile-selected-${locale}.png`) });
        }
        assert.deepEqual(errors, [], 'Browser raises no runtime errors');
        console.log(`PASS one inspection, actual-contact gate, Hero forecast and sticky target: ${viewport.width}x${viewport.height} ${locale}`);
      } catch (error) {
        await page.screenshot({ path: resolve(output, `inspection-failure-${viewport.width}x${viewport.height}-${locale}.png`) });
        throw error;
      } finally {
        await context.close();
      }
    }
  }
} finally {
  await browser.close();
}
