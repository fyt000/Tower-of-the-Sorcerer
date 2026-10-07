import { chromium } from '@playwright/test';
import { readFileSync, mkdirSync } from 'node:fs';
import { resolve } from 'node:path';
import assert from 'node:assert/strict';

const root = resolve(import.meta.dirname, '..');
const output = resolve(root, '../build/rust/test-results');
mkdirSync(output, { recursive: true });
const original = JSON.parse(readFileSync(resolve(root, '../data/campaign.json'), 'utf8'));
const tiles = Array(121).fill(6);
for (let y = 0; y < 4; y++) for (let x = 0; x < 11; x++) tiles[y * 11 + x] = 201;
tiles[0] = 209;
tiles[2 * 11 + 2] = 210;
tiles[5 * 11 + 6] = 202;
tiles[8 * 11 + 8] = 97;
tiles[8 * 11 + 9] = 104;
tiles[10 * 11 + 10] = 208;
const count = tiles.filter(id => [201, 202, 210, 97, 104].includes(id)).length;
const fixture = JSON.stringify({
  id: 'floor-enemy-list-regression', title: 'Enemy list test', width: 11, height: 11,
  start: { floor: 1, x: 5, y: 5, hp: 10000, attack: 420, defense: 100, gold: 0, inventory: [] },
  rules: { empty_tile: 6, forecast_requires_item: 'hero_orb', flying_original_selection: true },
  floors: [{ id: 1, title: 'Visible room', tiles },
    { id: 2, title: 'Unseen room', tiles: Array(121).fill(203) }],
  tiles: {
    6: original.tiles['6'],
    36: original.tiles['36'],
    39: original.tiles['39'],
    ...Object.fromEntries(original.tiles['104'].footprint.tiles.map(id => [id, original.tiles[id]])),
    201: { name: 'Visible guard', kind: 'enemy', enemy: 'guard', sprite: 61 },
    202: { name: 'Blocked guard', kind: 'enemy', enemy: 'blocked_guard', sprite: 62 },
    203: { name: 'Future secret monster', kind: 'enemy', enemy: 'future', sprite: 63 },
    208: { name: 'Ordinary speaker', kind: 'npc', sprite: 121 },
    209: { name: 'Hidden answer', kind: 'hidden_wall', sprite: 8,
      description: 'A secret answer must never appear in the enemy list.' },
    210: { name: 'Visible guard', kind: 'enemy', enemy: 'guard_variant', sprite: 61 }
  },
  enemies: {
    guard: { name: 'Visible guard', hp: 150, attack: 50, defense: 5, gold: 30 },
    guard_variant: { name: 'Visible guard', hp: 150, attack: 50, defense: 5, gold: 30 },
    blocked_guard: { name: 'Blocked guard', hp: 100000, attack: 900, defense: 900, gold: 90 },
    future: { name: 'Future secret monster', hp: 8888, attack: 8888, defense: 8888, gold: 8888 },
    giant_octopus: original.enemies.giant_octopus
  }, events: []
});
const browser = await chromium.launch({ headless: true,
  args: ['--use-angle=swiftshader-webgl', '--autoplay-policy=no-user-gesture-required'] });
const ui = page => page.evaluate(() => JSON.parse(window.tower.ui_json()));
const save = page => page.evaluate(() => JSON.parse(window.tower.save_json()));
const state = page => page.evaluate(() => JSON.parse(window.tower.state_json()));
const center = r => ({ x: r.x + r.w / 2, y: r.y + r.h / 2 });
const visible = (r, v) => r && r.x >= 0 && r.y >= 0 && r.x + r.w <= v.width + 1 && r.y + r.h <= v.height + 1;
const contains = (r, area) => r && r.y >= area.y - 1 && r.y + r.h <= area.y + area.h + 1;
const enemyRows = bounds => Object.entries(bounds).filter(([id]) => id.startsWith('enemy_list_entry:'));
const enemyRow = (bounds, predicate) => enemyRows(bounds).map(([, row]) => row).find(predicate);

function overflowFixture() {
  const campaign = JSON.parse(fixture);
  const guards = campaign.floors[0].tiles;
  let index = 0;
  for (let cell = 0; cell < guards.length; cell++) {
    if (![201, 210].includes(guards[cell])) continue;
    const variant = index++ % 24;
    const tile = 300 + variant;
    const key = `trial_${variant}`;
    guards[cell] = tile;
    campaign.tiles[tile] = { name: `Trial guard ${variant + 1}`, kind: 'enemy', enemy: key, sprite: 61 };
    campaign.enemies[key] = { name: `Trial guard ${variant + 1}`, hp: 150 + variant, attack: 50, defense: 5, gold: 30 };
  }
  campaign.start.inventory = ['hero_orb'];
  return JSON.stringify(campaign);
}

async function idle(page) {
  await page.waitForFunction(() => { const s = JSON.parse(window.tower.ui_json());
    return !s.animation && !s.presentation_remaining && !s.path_remaining;
  }, undefined, { timeout: 10000 });
}

async function touchDrag(cdp, from, to) {
  await cdp.send('Input.dispatchTouchEvent', { type: 'touchStart', touchPoints: [from] });
  await new Promise(resolve => setTimeout(resolve, 60));
  for (let step = 1; step <= 12; step++) {
    await cdp.send('Input.dispatchTouchEvent', { type: 'touchMove', touchPoints: [{
      x: from.x + (to.x - from.x) * step / 12, y: from.y + (to.y - from.y) * step / 12
    }] });
    await new Promise(resolve => setTimeout(resolve, 25));
  }
  await cdp.send('Input.dispatchTouchEvent', { type: 'touchEnd', touchPoints: [] });
}

async function reveal(page, cdp, viewport, id) {
  for (let attempt = 0; attempt < 16; attempt++) {
    const bounds = (await ui(page)).bounds;
    if (visible(bounds[id], viewport)) return bounds[id];
    if (cdp) await touchDrag(cdp, { x: viewport.width - 35, y: viewport.height - 60 },
      { x: viewport.width - 35, y: 110 });
    else {
      await page.mouse.move(viewport.width - 35, viewport.height - 60);
      await page.mouse.wheel(0, 300);
    }
    await page.waitForTimeout(250);
  }
  assert.fail(`${id} remains unreachable`);
}

async function activate(page, cdp, rect) {
  const point = center(rect);
  if (cdp) await page.touchscreen.tap(point.x, point.y);
  else await page.mouse.click(point.x, point.y);
  await page.waitForTimeout(250);
}

async function settle(page) {
  let previous, stable = 0;
  for (let frame = 0; frame < 14; frame++) {
    const bounds = (await ui(page)).bounds;
    const point = center(bounds.enemy_list_viewport);
    await page.mouse.move(point.x + frame % 2, point.y);
    await page.waitForTimeout(120);
    const next = (await ui(page)).bounds;
    const current = JSON.stringify([next.enemy_list_viewport, next.enemy_list_heading, next.enemy_list_close]);
    stable = previous === current ? stable + 1 : 0;
    previous = current;
    if (stable >= 3) return;
  }
  assert.fail('Enemy list modal geometry did not settle');
}

async function unchanged(page, saved, action, reason) {
  assert.deepEqual(await save(page), saved, `${reason}: save remains unchanged`);
  assert.deepEqual((await state(page)).last_action, action, `${reason}: no game action`);
}

async function captureOverview(page, path) {
  const bounds = (await ui(page)).bounds;
  await page.mouse.move(bounds.enemy_list_heading.x + 3, bounds.enemy_list_heading.y + 3);
  await page.waitForTimeout(250);
  await page.screenshot({ path });
}

try {
  for (const viewport of [{ width: 1440, height: 1000 }, { width: 1920, height: 1080 }, { width: 2560, height: 1440 }, { width: 390, height: 844 }, { width: 844, height: 390 }]) {
    if (process.env.TOS_ENEMY_LIST_WIDTH && Number(process.env.TOS_ENEMY_LIST_WIDTH) !== viewport.width) continue;
    for (const locale of ['en', 'zh-CN']) {
      const touch = viewport.width < 500 || viewport.height <= 500;
      const context = await browser.newContext({ viewport, hasTouch: touch });
      const page = await context.newPage();
      const cdp = touch ? await context.newCDPSession(page) : null;
      const errors = [];
      page.on('pageerror', error => errors.push(error.message));
      try {
        await page.goto(process.env.TOS_URL || 'http://127.0.0.1:8080');
        await page.waitForFunction(() => window.tower && JSON.parse(window.tower.ui_json()).sprites_loaded,
          undefined, { timeout: 45000 });
        await page.evaluate(({ fixture, locale }) => {
          window.tower.import_campaign(fixture); window.tower.set_language(locale);
        }, { fixture, locale });
        await page.waitForTimeout(locale === 'zh-CN' ? 1600 : 400);
        await idle(page);
        let bounds = (await ui(page)).bounds;
        assert.equal(bounds['item:hero_orb'], undefined, 'Unowned Hero Orb is not exposed in inventory');
        if (bounds.enemy_list_open) {
          assert.equal(bounds.enemy_list_open.enabled, false);
          const saved = await save(page), action = (await state(page)).last_action;
          if (visible(bounds.enemy_list_open, viewport)) await activate(page, cdp, bounds.enemy_list_open);
          assert.equal((await ui(page)).bounds.enemy_list_dialog, undefined, 'The button stays gated before acquisition');
          await unchanged(page, saved, action, 'Unowned button');
        }

        const acquired = await save(page);
        acquired.player.inventory.push('hero_orb');
        await page.evaluate(source => window.tower.load_save(source), JSON.stringify(acquired));
        await page.waitForTimeout(250);
        const saved = await save(page), action = (await state(page)).last_action;
        await activate(page, cdp, await reveal(page, cdp, viewport, 'item:hero_orb'));
        assert((await ui(page)).bounds.enemy_list_dialog, 'Clicking Hero Orb opens its floor list');
        await settle(page);
        bounds = (await ui(page)).bounds;
        assert(visible(bounds.enemy_list_heading, viewport));
        assert(visible(bounds.enemy_list_close, viewport));
        assert.equal(bounds.enemy_list_viewport.entries, 4, 'Equivalent encounters share a single profile');
        assert.equal(bounds.enemy_list_viewport.encounters, count, 'Grouped quantities retain every encounter');
        assert.equal(enemyRows(bounds).length, 4);
        assert.equal(enemyRows(bounds).reduce((sum, [, row]) => sum + row.count, 0), count);
        for (const [id, entry] of enemyRows(bounds)) {
          assert.notEqual(entry.name, 'Future secret monster', `${id} excludes unseen-floor enemies`);
          assert.notEqual(entry.name, 'Hidden answer', `${id} excludes hidden walls`);
          assert.notEqual(entry.name, 'Ordinary speaker', `${id} excludes NPCs`);
          assert(!JSON.stringify(entry).includes('secret answer'));
          assert.equal(entry.tile_x, undefined, 'Coordinates are absent from overview rows');
          assert.equal(entry.tile_y, undefined);
          assert.equal(id.split(':').length, 2, 'Profile IDs are independent of map positions');
          for (const metric of Object.values(entry.metrics)) {
            assert(metric.text_w <= metric.w + 0.1, 'Every full numeric value fits its column');
            assert(metric.font_size >= 17, 'Values keep a readable font size');
          }
        }
        const guard = enemyRow(bounds, row => row.name === 'Visible guard');
        assert.equal(guard.count, 43, 'Different tile IDs with identical visible facts deduplicate');
        assert.deepEqual(['hp', 'attack', 'defense', 'damage', 'gold'].map(key => guard[key]),
          [150, 50, 5, 0, 30], 'Floor list uses actual combat forecasts');
        const blocked = enemyRow(bounds, row => row.name === 'Blocked guard');
        assert.equal(blocked.damage, null);
        assert.equal(blocked.can_win, false);
        const part = enemyRow(bounds, row => row.hp === 1200 && row.gold === 50);
        const body = enemyRow(bounds, row => row.hp === 1200 && row.gold === 100);
        assert.deepEqual(['hp', 'attack', 'defense', 'damage', 'gold'].map(key => part[key]),
          [1200, 180, 20, 160, 50], 'Octopus part shows full damage and its reduced reward');
        assert(body, 'Octopus body retains a separate full-reward profile');
        assert.equal(bounds.enemy_list_viewport.table, viewport.width >= 620, 'Wide screens use one aligned table');
        if (bounds.enemy_list_viewport.table) {
          for (const field of ['hp', 'attack', 'defense', 'gold', 'damage']) {
            const right = guard.metrics[field].x + guard.metrics[field].w;
            for (const [, row] of enemyRows(bounds)) assert.equal(row.metrics[field].x + row.metrics[field].w, right,
              'Numeric columns align across all enemy profiles');
          }
        }
        if (viewport.width >= 1920) assert(guard.metrics.hp.font_size > 22, 'Desktop overview fonts grow with the workspace');
        await unchanged(page, saved, action, 'Opening and inspecting');
        const board = bounds.board;
        const underlying = { x: board.x + 5.5 * board.w / board.width,
          y: board.y + 6.5 * board.h / board.height };
        if (underlying.x >= 0 && underlying.x < viewport.width && underlying.y >= 0 && underlying.y < viewport.height) {
          if (cdp) await page.touchscreen.tap(underlying.x, underlying.y);
          else await page.mouse.click(underlying.x, underlying.y);
          await page.waitForTimeout(250);
          await unchanged(page, saved, action, 'A click or tap over the underlying board');
          if (!(await ui(page)).bounds.enemy_list_dialog) {
            await activate(page, cdp, await reveal(page, cdp, viewport, 'item:hero_orb'));
          }
          await settle(page);
          bounds = (await ui(page)).bounds;
        }
        await page.keyboard.press('ArrowDown');
        await page.keyboard.press('D');
        await page.keyboard.press('Space');
        await unchanged(page, saved, action, 'Keyboard while reading');

        bounds = (await ui(page)).bounds;
        await captureOverview(page, resolve(output, `enemy-list-${viewport.width}x${viewport.height}-${locale}.png`));
        await activate(page, cdp, bounds.enemy_list_close);
        assert.equal((await ui(page)).bounds.enemy_list_dialog, undefined);
        await unchanged(page, saved, action, 'Closing the list');

        bounds = (await ui(page)).bounds;
        if (bounds.enemy_list_open) {
          await activate(page, cdp, await reveal(page, cdp, viewport, 'enemy_list_open'));
          assert((await ui(page)).bounds.enemy_list_dialog, 'Toolbar opens the same list');
          await page.keyboard.press('Escape'); await page.waitForTimeout(200);
          assert.equal((await ui(page)).bounds.enemy_list_dialog, undefined, 'Escape closes the list');
          await unchanged(page, saved, action, 'Toolbar list');
        }

        const lucky = await save(page);
        lucky.enemy_overrides.guard_variant = {
          name: 'Visible guard', hp: 750, attack: 150, defense: 5, gold: 42, special: ''
        };
        lucky.player.inventory.push('lucky_gold');
        await page.evaluate(source => window.tower.load_save(source), JSON.stringify(lucky));
        await page.waitForTimeout(250);
        await activate(page, cdp, await reveal(page, cdp, viewport, 'item:hero_orb'));
        bounds = (await ui(page)).bounds;
        assert.equal(bounds.enemy_list_viewport.entries, 5, 'Runtime overrides split formerly identical profiles');
        assert.equal(enemyRow(bounds, row => row.name === 'Visible guard' && row.hp === 150).count, 42);
        assert.equal(enemyRow(bounds, row => row.name === 'Visible guard' && row.hp === 750).gold, 84,
          'Actual runtime stats and doubled rewards stay separate');
        assert(enemyRow(bounds, row => row.hp === 1200 && row.gold === 100));
        assert(enemyRow(bounds, row => row.hp === 1200 && row.gold === 200), 'Lucky Gold applies to each current reward');
        const noOrb = await save(page);
        noOrb.player.inventory = [];
        await page.evaluate(source => window.tower.load_save(source), JSON.stringify(noOrb));
        await page.waitForTimeout(250);
        assert.equal((await ui(page)).bounds.enemy_list_dialog, undefined, 'Save replacement closes the reader and rechecks ownership');

        const reverse = structuredClone(saved);
        reverse.cycle = 2;
        await page.evaluate(source => window.tower.load_save(source), JSON.stringify(reverse));
        await page.waitForTimeout(250);
        await activate(page, cdp, await reveal(page, cdp, viewport, 'item:hero_orb'));
        await settle(page);
        const reverseUi = await ui(page);
        assert(reverseUi.palette.reverse);
        assert(reverseUi.palette.accent[0] > reverseUi.palette.accent[2] * 1.5,
          'Reverse overview follows the warmer red theme');
        assert(visible(reverseUi.bounds.enemy_list_close, viewport));
        await captureOverview(page, resolve(output, `enemy-list-reverse-${viewport.width}x${viewport.height}-${locale}.png`));

        await page.evaluate(source => window.tower.import_campaign(source), overflowFixture());
        await page.waitForTimeout(250);
        await activate(page, cdp, await reveal(page, cdp, viewport, 'item:hero_orb'));
        await settle(page);
        bounds = (await ui(page)).bounds;
        const overflowSaved = await save(page), overflowAction = (await state(page)).last_action;
        const fixed = { heading: bounds.enemy_list_heading, close: bounds.enemy_list_close, columns: bounds.enemy_list_columns };
        const last = `enemy_list_entry:${bounds.enemy_list_viewport.entries - 1}`;
        for (let attempt = 0; attempt < 48; attempt++) {
          bounds = (await ui(page)).bounds;
          if (contains(bounds[last], bounds.enemy_list_viewport)) break;
          const area = bounds.enemy_list_viewport;
          if (cdp) await touchDrag(cdp,
            { x: area.x + area.w / 2, y: area.y + area.h - 20 },
            { x: area.x + area.w / 2, y: area.y + 20 });
          else {
            const point = center(area); await page.mouse.move(point.x, point.y); await page.mouse.wheel(0, 600);
          }
          await page.waitForTimeout(250);
        }
        bounds = (await ui(page)).bounds;
        assert(contains(bounds[last], bounds.enemy_list_viewport), 'Last distinct profile is reachable');
        assert(bounds.enemy_list_viewport.offset_y > 0, 'Many distinct profiles support real scrolling');
        assert.deepEqual(bounds.enemy_list_heading, fixed.heading, 'Heading stays fixed during real scrolling');
        assert.deepEqual(bounds.enemy_list_close, fixed.close, 'Close stays fixed during real scrolling');
        assert.deepEqual(bounds.enemy_list_columns, fixed.columns, 'Numeric column headings stay fixed');
        await unchanged(page, overflowSaved, overflowAction, 'Wheel or touch scrolling');
        await captureOverview(page, resolve(output, `enemy-list-scroll-${viewport.width}x${viewport.height}-${locale}.png`));
        assert.deepEqual(errors, []);
        console.log(`PASS Hero Orb grouped overview, aligned readable values, reward/runtime variants, safe scope and scrolling: ${viewport.width}x${viewport.height} ${locale}`);
      } catch (error) {
        await page.screenshot({ path: resolve(output, `enemy-list-failure-${viewport.width}x${viewport.height}-${locale}.png`) });
        throw error;
      } finally {
        await context.close();
      }
    }
  }
} finally {
  await browser.close();
}
