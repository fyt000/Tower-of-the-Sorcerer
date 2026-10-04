import { chromium } from '@playwright/test';
import { readFileSync, writeFileSync, mkdirSync } from 'node:fs';
import { resolve } from 'node:path';
import assert from 'node:assert/strict';

const root = resolve(import.meta.dirname, '..');
const output = resolve(root, 'test-results');
mkdirSync(output, { recursive: true });
const original = JSON.parse(readFileSync(resolve(root, 'data/campaign.json'), 'utf8'));
const itemIds = Object.values(original.tiles).filter(tile => tile.kind === 'item').map(tile => tile.item);
assert.equal(itemIds.length, 15);
const viewports = [
  { width: 844, height: 390 },
  { width: 932, height: 430 },
  { width: 1024, height: 600 },
  { width: 390, height: 844 },
];
const browser = await chromium.launch({ headless: true,
  args: ['--use-angle=swiftshader-webgl', '--autoplay-policy=no-user-gesture-required'] });
const report = [];
const state = page => page.evaluate(() => JSON.parse(window.tower.state_json()));
const ui = page => page.evaluate(() => JSON.parse(window.tower.ui_json()));
const save = page => page.evaluate(() => JSON.parse(window.tower.save_json()));
const center = rect => ({ x: rect.x + rect.w / 2, y: rect.y + rect.h / 2 });
const inside = (rect, viewport) => rect && rect.x >= -1 && rect.y >= -1
  && rect.x + rect.w <= viewport.width + 1 && rect.y + rect.h <= viewport.height + 1;
const location = s => [s.player.floor, s.player.x, s.player.y];
const toolbarIds = ['restore', 'save', 'editor', 'settings', 'journal_header', 'enemy_list_open'];

async function idle(page) {
  await page.waitForFunction(() => {
    const s = JSON.parse(window.tower.ui_json());
    return !s.animation && !s.presentation_remaining && !s.path_remaining;
  }, undefined, { timeout: 15000 });
}

async function fixture(page, cycle, locale) {
  await page.evaluate(({ source, itemIds, cycle, locale }) => {
    window.tower.import_campaign(source);
    window.tower.set_language(locale);
    const saved = JSON.parse(window.tower.save_json());
    const multiplier = cycle === 1 ? 1 : 44;
    saved.cycle = cycle;
    Object.assign(saved.player, {
      floor: 4, x: 4, y: 6, hp: 9000 * multiplier,
      attack: 450 * multiplier, defense: 400 * multiplier, gold: 123,
      keys: { yellow: 3, blue: 1, red: 0 },
      inventory: ['sword_5', 'sacred_shield', ...itemIds],
      weapon: 'sword_5', shield: 'sacred_shield', item_charges: { warp_staff: 3 },
    });
    saved.last_encounter = {
      cycle, floor: 4, x: 0, y: 6, tile: 63, enemy_name: 'Green Slime',
      hp: 35 * multiplier, attack: 18 * multiplier, defense: multiplier,
    };
    saved.visited_floors = [1, 2, 3, 4];
    saved.highest_stair_floor = 4;
    saved.log = ['Entered floor 4.', 'Opened the yellow door.', 'Defeated Green Slime: −24 HP, +1 gold.'];
    saved.journal = [];
    window.tower.load_save(JSON.stringify(saved));
  }, { source: JSON.stringify(original), itemIds, cycle, locale });
  await page.waitForTimeout(locale === 'zh-CN' ? 1600 : 500);
  await idle(page);
}

async function activate(page, rect, touch) {
  const point = center(rect);
  if (touch) await page.touchscreen.tap(point.x, point.y);
  else await page.mouse.click(point.x, point.y);
  await page.waitForTimeout(200);
}

async function touchDrag(cdp, from, to) {
  await cdp.send('Input.dispatchTouchEvent', { type: 'touchStart', touchPoints: [from] });
  await new Promise(resolve => setTimeout(resolve, 60));
  for (let step = 1; step <= 12; step++) {
    await cdp.send('Input.dispatchTouchEvent', { type: 'touchMove', touchPoints: [{
      x: from.x + (to.x - from.x) * step / 12,
      y: from.y + (to.y - from.y) * step / 12,
    }] });
    await new Promise(resolve => setTimeout(resolve, 25));
  }
  await cdp.send('Input.dispatchTouchEvent', { type: 'touchEnd', touchPoints: [] });
}

async function revealBoard(page, context, viewport, touch) {
  const beforeSave = await save(page), beforeAction = (await state(page)).last_action;
  const cdp = touch ? await context.newCDPSession(page) : null;
  for (let attempt = 0; attempt < 6; attempt++) {
    const bounds = (await ui(page)).bounds;
    if (inside(bounds.board, viewport)) {
      assert.deepEqual(await save(page), beforeSave, 'Reaching the portrait board leaves the game unchanged');
      assert.deepEqual((await state(page)).last_action, beforeAction);
      return bounds;
    }
    if (cdp) {
      const from = { x: Math.max(12, bounds.board.x - 5), y: viewport.height - 70 };
      await touchDrag(cdp, from, { x: from.x, y: Math.max(80, from.y - 230) });
    } else {
      await page.mouse.move(Math.max(12, bounds.board.x - 5), viewport.height - 70);
      await page.mouse.wheel(0, 180);
    }
    await page.waitForTimeout(400);
  }
  assert.fail(`Portrait board remains unreachable: ${JSON.stringify((await ui(page)).bounds.board)}`);
}

function checkInspection(bounds, selected) {
  assert.equal(bounds.inspection_battle, undefined, 'Battle progress belongs to the board and log');
  assert.equal(bounds.last_encounter, undefined, 'Closed encounters do not become a second inspection view');
  if (selected !== undefined) assert.equal(!!bounds.inspection_target, selected,
    selected ? 'Inspection renders the chosen tile' : 'Idle inspection does not invent a selected tile');
  assert(!(bounds.inspection_forecast && bounds.inspection_contact), 'Only one selected-tile stat view is active');
  if (!bounds.inspection_target) {
    assert.equal(bounds.inspection_forecast, undefined, 'Idle inspector has no forecast');
    assert.equal(bounds.inspection_contact, undefined, 'Idle inspector has no separate encounter stats');
  }
}

function checkToolbar(bounds, viewport) {
  assert(inside(bounds.tower_toolbar, viewport),
    `The complete toolbar card, including padding and frame, fits the viewport: ${JSON.stringify(bounds.tower_toolbar)}`);
  for (const id of toolbarIds) {
    assert(inside(bounds[id], viewport), `${id} is reachable in the right-side toolbar`);
    assert(bounds[id].x >= bounds.board.x + bounds.board.w - 1, `${id} lives in the side toolbar`);
  }
}

function rgb(value) {
  assert(Array.isArray(value) && value.length >= 3,
    `Theme debug colors are RGB arrays: ${JSON.stringify(value)}`);
  return value.slice(0, 3);
}

try {
  for (const viewport of viewports) {
    if (process.env.TOS_LANDSCAPE_WIDTH && Number(process.env.TOS_LANDSCAPE_WIDTH) !== viewport.width) continue;
    for (const locale of ['en', 'zh-CN']) {
      for (const cycle of [1, 2]) {
        const touch = viewport.width < 1000;
        const context = await browser.newContext({ viewport, hasTouch: touch });
        const page = await context.newPage();
        const errors = [];
        page.on('pageerror', error => errors.push(error.message));
        try {
          await page.goto(process.env.TOS_URL || 'http://127.0.0.1:8080');
          await page.waitForFunction(() => window.tower && JSON.parse(window.tower.ui_json()).sprites_loaded,
            undefined, { timeout: 45000 });
          await fixture(page, cycle, locale);
          let snapshot = await state(page);
          let debug = await ui(page);
          let bounds = debug.bounds;
          const landscape = viewport.width > viewport.height;
          assert.equal(debug.landscape, landscape, 'Landscape mode follows the short wide viewport');
          assert.equal(debug.palette.reverse, cycle === 2, 'Palette follows the presented cycle');
          const [r, , b] = rgb(debug.palette.bg);
          if (cycle === 1) assert(b > r, 'Normal tower masonry uses the original blue/lavender colors');
          else assert(r > b, 'Reverse tower masonry changes to red/crimson');
          const [ar, , ab] = rgb(debug.palette.accent);
          if (cycle === 1) assert(ab > ar, 'Normal tower accents are blue/lavender');
          else assert(ar > ab, 'Reverse tower accents are red');
          const [sr, , sb] = rgb(debug.palette.surface);
          if (cycle === 1) assert(sb > sr, 'Modern normal panels are blue/purple');
          else assert(sr > sb, 'Modern reverse panels are burgundy');
          rgb(debug.palette.metal);
          assert.equal(snapshot.cycle, cycle);
          assert.equal(bounds.inventory_grid.slots, 15);
          assert.equal(bounds.inventory_viewport, undefined, 'Original inventory has no inner scrolling');
          for (const [index, id] of itemIds.entries()) {
            const rect = bounds[`item:${id}`];
            assert(inside(rect, viewport), `${id} is fully displayed: ${JSON.stringify(rect)}`);
            assert.equal(rect.w, landscape ? 40 : 54);
            assert.equal(rect.h, landscape ? 40 : 54);
            assert.equal(bounds[`inventory_slot:${index}`].occupied, true);
          }
          for (const slot of ['weapon', 'shield']) {
            assert(inside(bounds[`equipment:${slot}`], viewport), `Current ${slot} is accessible`);
            assert.equal(snapshot.player[slot], slot === 'weapon' ? 'sword_5' : 'sacred_shield');
          }
          assert(bounds.board.cell >= 20, 'Height fitting preserves legible cells');
          for (const id of ['stats', 'keyring']) assert(inside(bounds[id], viewport), `${id} is accessible`);
          if (landscape) {
            assert(inside(bounds.board, viewport), `Complete 11x11 floor fits the landscape viewport: ${JSON.stringify(bounds.board)}`);
            assert(bounds.board.h >= viewport.height * 0.90,
              `Floor uses nearly all landscape height: ${JSON.stringify(bounds.board)}`);
            for (const id of ['stats', 'inventory_grid']) {
              assert(bounds[id].x + bounds[id].w <= bounds.board.x + 1, `${id} occupies the left side`);
            }
            for (const id of ['equipment:weapon', 'equipment:shield', 'keyring']) {
              assert(bounds[id].x >= bounds.board.x + bounds.board.w - 1, `${id} occupies the right side`);
              assert(inside(bounds[id], viewport), `${id} is fully visible beside the floor`);
            }
            if (!inside(bounds.tower_toolbar, viewport)) await page.screenshot({ path: resolve(output,
              `landscape-toolbar-failure-${viewport.width}x${viewport.height}-${locale}-cycle${cycle}.png`) });
            checkToolbar(bounds, viewport);
            const rows = Object.entries(bounds).filter(([id]) => id.startsWith('journal_preview_entry:'));
            assert.equal(rows.length, 2, 'Two recent action rows stay visible beside the floor');
            for (const [id, row] of rows) {
              assert(inside(row, viewport), `${id} is fully readable in the left panel`);
              assert(row.x + row.w <= bounds.board.x + 1, 'Recent actions stay to the left of the floor');
            }
            const [newer, older] = rows.map(([, row]) => row).sort((a, b) => a.y - b.y);
            assert(newer.y + newer.h < older.y, 'Recent entries have visually separate rows');
            assert(inside(bounds.journal_preview_open, viewport), 'The recent log can expand from the left panel');
          } else {
            assert.equal(bounds.board.x + bounds.board.w <= viewport.width + 1, true,
              'Portrait board keeps the full usable width');
          }
          checkInspection(bounds, false);
          await page.mouse.move(2, 2);
          await page.waitForTimeout(200);
          const screenshot = `landscape-theme-${viewport.width}x${viewport.height}-${locale}-cycle${cycle}.png`;
          await page.screenshot({ path: resolve(output, screenshot) });

          if (landscape) {
            const beforeHistory = await save(page), historyAction = (await state(page)).last_action;
            await activate(page, bounds.journal_preview_open, touch);
            await page.waitForFunction(() => !!JSON.parse(window.tower.ui_json()).bounds.journal_history);
            const historyBounds = (await ui(page)).bounds;
            assert(inside(historyBounds.journal_history, viewport), 'Expanded recent log fits the phone landscape viewport');
            assert(inside(historyBounds.journal_history_close, viewport), 'Log Close stays reachable');
            await page.keyboard.press('ArrowLeft');
            await page.waitForTimeout(150);
            assert.deepEqual(await save(page), beforeHistory, 'Reading the log blocks game movement without changing the save');
            assert.deepEqual((await state(page)).last_action, historyAction);
            await page.screenshot({ path: resolve(output,
              `landscape-log-${viewport.width}x${viewport.height}-${locale}-cycle${cycle}.png`) });
            await activate(page, (await ui(page)).bounds.journal_history_close, touch);
            await page.waitForFunction(() => !JSON.parse(window.tower.ui_json()).bounds.journal_history);
          }

          // Forecast rows occupy more space than the idle hint. They
          // must never push Save, settings, or the other controls off the phone.
          if (landscape) {
            const beforeForecast = await save(page), forecastAction = (await state(page)).last_action;
            const toolbarBeforeForecast = structuredClone(bounds.tower_toolbar);
            const board = bounds.board;
            await page.mouse.move(board.x + board.cell * 7.5, board.y + board.cell * 8.5);
            await page.waitForFunction(() => !!JSON.parse(window.tower.ui_json()).bounds.inspection_forecast,
              undefined, { timeout: 5000 });
            await page.waitForTimeout(200);
            const forecastBounds = (await ui(page)).bounds;
            checkInspection(forecastBounds, true);
            if (!inside(forecastBounds.tower_toolbar, viewport)) await page.screenshot({ path: resolve(output,
              `landscape-toolbar-failure-forecast-${viewport.width}x${viewport.height}-${locale}-cycle${cycle}.png`) });
            checkToolbar(forecastBounds, viewport);
            assert.deepEqual(forecastBounds.tower_toolbar, toolbarBeforeForecast,
              'Switching from idle inspection to a Hero forecast keeps the toolbar in place');
            assert(inside(forecastBounds.inspection_forecast, viewport), 'Forecast details remain visible beside the floor');
            assert(inside(forecastBounds.board, viewport), 'Forecast does not displace the complete floor');
            assert.deepEqual(await save(page), beforeForecast, 'Hovering a forecast leaves the game unchanged');
            assert.deepEqual((await state(page)).last_action, forecastAction);
            assert.equal((await ui(page)).path_remaining, 0, 'Inspection hover does not start a route');
            await page.screenshot({ path: resolve(output,
              `landscape-forecast-${viewport.width}x${viewport.height}-${locale}-cycle${cycle}.png`) });
          }

          // Passive help does not dispatch a route or use an item.
          const beforeHover = await save(page), actionBeforeHover = snapshot.last_action;
          const lucky = center(bounds['item:lucky_gold']);
          await page.mouse.move(lucky.x, lucky.y);
          await page.waitForTimeout(900);
          assert.deepEqual(await save(page), beforeHover, 'Reading owned-item help leaves the game unchanged');
          assert.deepEqual((await state(page)).last_action, actionBeforeHover);
          await page.screenshot({ path: resolve(output,
            `landscape-help-${viewport.width}x${viewport.height}-${locale}-cycle${cycle}.png`) });

          // Item activation uses the same visible hit target for mouse and touch.
          await activate(page, bounds['item:wisdom_orb'], touch);
          await page.waitForFunction(() => !!JSON.parse(window.tower.ui_json()).bounds.journal_dialog,
            undefined, { timeout: 10000 });
          debug = await ui(page);
          assert(inside(debug.bounds.journal_dialog, viewport), 'Wisdom popup fits the viewport');
          assert(inside(debug.bounds.journal_close, viewport), 'Popup Close stays reachable');
          const modalLocation = location(await state(page));
          for (const key of ['ArrowLeft', 'ArrowRight', 'a', 'd']) await page.keyboard.press(key);
          await page.waitForTimeout(200);
          assert.deepEqual(location(await state(page)), modalLocation, 'Popup keys do not move the hero');
          await activate(page, (await ui(page)).bounds.journal_close, touch);
          await page.waitForFunction(() => !JSON.parse(window.tower.ui_json()).bounds.journal_dialog);
          await idle(page);
          assert.deepEqual(location(await state(page)), [4, 4, 6], 'Item popup never starts a floor route');

          // A usable inventory cell can dispatch only its item action.
          bounds = (await ui(page)).bounds;
          await activate(page, bounds['item:super_mattock'], touch);
          await idle(page);
          snapshot = await state(page);
          assert(!snapshot.player.inventory.includes('super_mattock'), 'Visible consumable can be activated');
          assert.deepEqual(location(snapshot), [4, 4, 6], 'Using a visible item does not move the hero');
          assert.equal((await ui(page)).path_remaining, 0, 'Inventory input does not start a board path');

          // Restore the standard floor after the destructive test, then verify
          // the board coordinates still route correctly at the height-fitted scale.
          await fixture(page, cycle, locale);
          bounds = landscape ? (await ui(page)).bounds : await revealBoard(page, context, viewport, touch);
          if (!landscape) await page.screenshot({ path: resolve(output,
            `landscape-portrait-board-${locale}-cycle${cycle}.png`) });
          const board = bounds.board;
          const target = { x: board.x + board.cell * 5.5, y: board.y + board.cell * 6.5, w: 0, h: 0 };
          await activate(page, target, touch);
          await idle(page);
          assert.deepEqual(location(await state(page)), [4, 5, 6], 'Scaled board click moves to exactly the selected free cell');
          await page.keyboard.press('ArrowLeft');
          await page.waitForFunction(() => {
            const s = JSON.parse(window.tower.state_json());
            return s.player.floor === 4 && s.player.x === 4 && s.player.y === 6;
          }, undefined, { timeout: 5000 });
          await idle(page);
          assert.deepEqual(location(await state(page)), [4, 4, 6], 'Keyboard movement remains available after pointer routing');
          assert.deepEqual((await state(page)).player.keys, { yellow: 3, blue: 1, red: 0 },
            'Pointer and keyboard input do not spend a key');
          checkInspection((await ui(page)).bounds);
          assert.deepEqual(errors, []);
          report.push({ viewport, locale, cycle, landscape, board: bounds.board,
            inventory: bounds.inventory_grid, palette: debug.palette, screenshot, errors });
          console.log(`PASS complete inventory, height fitting, ${touch ? 'touch' : 'mouse'} actions and theme: ${viewport.width}x${viewport.height} ${locale} cycle${cycle}`);
        } finally {
          await context.close();
        }
      }
    }
  }
  writeFileSync(resolve(output, 'landscape-theme-report.json'), JSON.stringify(report, null, 2));
} finally {
  await browser.close();
}
