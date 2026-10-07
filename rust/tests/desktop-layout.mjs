import { chromium } from '@playwright/test';
import { readFileSync, writeFileSync, mkdirSync } from 'node:fs';
import { resolve } from 'node:path';
import assert from 'node:assert/strict';

const root = resolve(import.meta.dirname, '..'), output = resolve(root, '../build/rust/test-results');
mkdirSync(output, { recursive: true });
const campaign = JSON.parse(readFileSync(resolve(root, '../data/campaign.json'), 'utf8'));
const itemIds = Object.values(campaign.tiles).filter(tile => tile.kind === 'item').map(tile => tile.item);
assert.equal(itemIds.length, 15);
const viewports = [{ width: 1360, height: 920 }, { width: 1440, height: 1000 },
  { width: 1920, height: 1080 }, { width: 2560, height: 1440 }];
const browser = await chromium.launch({ headless: true,
  args: ['--use-angle=swiftshader-webgl', '--autoplay-policy=no-user-gesture-required'] });
const report = [];
const ui = page => page.evaluate(() => JSON.parse(window.tower.ui_json()));
const state = page => page.evaluate(() => JSON.parse(window.tower.state_json()));
const save = page => page.evaluate(() => JSON.parse(window.tower.save_json()));
const center = rect => ({ x: rect.x + rect.w / 2, y: rect.y + rect.h / 2 });
const coordinates = rect => [rect.x, rect.y, rect.w, rect.h];
const bottom = rect => rect.y + rect.h;
const right = rect => rect.x + rect.w;
const inside = (rect, viewport) => rect && rect.x >= -1 && rect.y >= -1
  && right(rect) <= viewport.width + 1 && bottom(rect) <= viewport.height + 1;
const near = (actual, expected, label, tolerance = 2) =>
  assert(Math.abs(actual - expected) <= tolerance, `${label}: ${actual} versus ${expected}`);

async function idle(page) {
  await page.waitForFunction(() => {
    const value = JSON.parse(window.tower.ui_json());
    return !value.animation && !value.presentation_remaining && !value.path_remaining;
  }, undefined, { timeout: 15000 });
}

async function fixture(page, base, inventory, cycle) {
  const saved = structuredClone(base), multiplier = cycle === 1 ? 1 : 44;
  saved.cycle = cycle;
  Object.assign(saved.player, {
    floor: 4, x: 4, y: 6, hp: 9000 * multiplier,
    attack: 450 * multiplier, defense: 400 * multiplier, gold: 123,
    keys: { yellow: 3, blue: 1, red: 0 },
    inventory: ['sword_5', 'sacred_shield', ...inventory],
    weapon: 'sword_5', shield: 'sacred_shield',
    item_charges: inventory.includes('warp_staff') ? { warp_staff: 3 } : {},
  });
  saved.visited_floors = [1, 2, 3, 4];
  saved.highest_stair_floor = 4;
  saved.last_encounter = null;
  saved.log = ['Entered floor 4.', 'Opened the yellow door.', 'Defeated Green Slime: −24 HP, +1 gold.'];
  saved.log_start = 0;
  saved.battle_log = [];
  saved.journal = [];
  await page.evaluate(source => window.tower.load_save(source), JSON.stringify(saved));
  await page.waitForTimeout(300);
  await idle(page);
}

function checkScale(debug, viewport) {
  const scale = debug.ui_scale;
  assert(Number.isFinite(scale), 'The UI exposes its active typography scale');
  assert(scale >= 1 && scale <= 2, 'Desktop scaling remains within its readable bounds');
  if (viewport.width <= 1440) near(scale, 1, 'Standard desktop retains its baseline size', 0.001);
  else assert(scale > 1, 'Larger desktop views enlarge typography and controls');
  return scale;
}

function checkPanels(bounds, viewport, scale) {
  for (const id of ['left_sidebar', 'right_sidebar', 'floor_panel', 'inspection_panel',
    'tower_toolbar', 'board', 'inventory_grid', 'stats', 'keyring']) {
    assert(inside(bounds[id], viewport), `${id} is fully visible: ${JSON.stringify(bounds[id])}`);
  }
  const left = bounds.left_sidebar, rightPanel = bounds.right_sidebar, floor = bounds.floor_panel;
  assert(left.x <= 16 * scale, 'Desktop uses the left edge instead of a capped centered workspace');
  assert(right(rightPanel) >= viewport.width - 16 * scale,
    'Desktop uses the available right edge for its sidebar');
  for (const panel of [left, rightPanel]) {
    near(panel.y, floor.y, 'Sidebar and floor start together');
    near(bottom(panel), bottom(floor), 'Sidebar and floor use the same height');
  }
  assert(right(left) <= floor.x + 1 && bounds.right_sidebar.x >= right(floor) - 1,
    'Sidebars sit on their own sides of the complete floor');
  assert(bounds.board.cell >= 40, 'Desktop retains large, readable floor cells');
  assert(bounds.inspection_panel.x >= right(bounds.board) - 1,
    'The inspector occupies the right sidebar');
  assert(bottom(bounds.inspection_panel) <= bounds.tower_toolbar.y + 1,
    'The inspector leaves its own space above the toolbar');
  const toolbarInset = bottom(rightPanel) - bottom(bounds.tower_toolbar);
  assert(toolbarInset >= 0 && toolbarInset <= 24 * scale,
    'Toolbar is anchored near the sidebar bottom with panel padding');
  for (const key of ['hp', 'attack', 'defense', 'gold']) {
    const row = bounds[`stat:${key}`];
    assert(inside(row, viewport), `Hero ${key} remains fully visible`);
    near(row.h, 30 * scale, 'Stat row height follows the desktop typography scale', 0.1);
    near(row.w, left.w - 24 * scale - 2, 'Hero stats span the sidebar content width inside its border', 1);
  }
  for (const slot of ['weapon', 'shield']) {
    const row = bounds[`equipment:${slot}`];
    assert(inside(row, viewport), `Equipped ${slot} remains fully visible`);
    near(row.h, 38 * scale, 'Equipment row height follows the desktop typography scale', 0.1);
    near(row.w, rightPanel.w - 24 * scale - 2, 'Equipment spans the sidebar content width inside its border', 1);
  }
  const preview = Object.entries(bounds).filter(([id]) => id.startsWith('journal_preview_entry:'));
  assert.equal(preview.length, 2, 'The compact visible activity preview retains two entries');
  assert(inside(bounds.journal_preview, viewport));
  assert(bottom(bounds.journal_preview) <= bottom(left) && bounds.journal_preview.y > bottom(bounds.inventory_grid),
    'Recent activity remains accessible below the reserved inventory');
}

function checkToolbar(bounds, scale) {
  const groups = [['enemy_list_open', 'journal_header', 'save'], ['restore', 'settings', 'editor']];
  for (const group of groups) {
    const cells = group.map(id => bounds[id]);
    assert(cells.every(Boolean), 'All six controls retain their own visible targets');
    for (let index = 0; index < cells.length; index++) {
      near(cells[index].w, cells[0].w, 'Toolbar controls have equal widths', 0.1);
      near(cells[index].h, 34 * scale, 'Desktop toolbar height follows the typography scale', 0.1);
      near(cells[index].y, cells[0].y, 'Toolbar controls share their row', 0.1);
      if (index > 0) {
        assert(cells[index].x > right(cells[index - 1]), 'Toolbar targets are separated');
      }
    }
    near(cells[1].x - right(cells[0]), cells[2].x - right(cells[1]),
      'Toolbar gaps remain even across each row', 0.1);
    assert(cells[0].x - bounds.tower_toolbar.x <= 16 * scale,
      'Toolbar starts at its panel content edge');
    assert(right(bounds.tower_toolbar) - right(cells.at(-1)) <= 16 * scale,
      'Toolbar controls span the panel instead of clustering on the left');
  }
  groups[0].forEach((id, index) => near(bounds[id].x, bounds[groups[1][index]].x,
    'Toolbar columns align between rows', 0.1));
}

function checkInventory(bounds, viewport, owned, baseline) {
  assert.equal(bounds.inventory_grid.slots, 15);
  assert.equal(bounds.inventory_viewport, undefined, 'Reserved inventory has no clipped scrolling list');
  const slots = Array.from({ length: 15 }, (_, index) => bounds[`inventory_slot:${index}`]);
  const rows = [...new Set(slots.map(rect => rect.y))];
  assert([3, 5].includes(rows.length), 'Desktop inventory has three or five complete rows');
  const columns = 15 / rows.length;
  near(bounds.inventory_grid.w, bounds['stat:hp'].w,
    'Inventory fills the sidebar content width with only a rounding allowance', 2);
  for (const y of rows) {
    const row = slots.filter(rect => rect.y === y);
    assert.equal(row.length, columns, 'Empty inventory preserves every position in each complete row');
    near(row[0].x, bounds.inventory_grid.x, 'Inventory row begins at the content edge', 0.1);
    near(right(row.at(-1)), right(bounds.inventory_grid), 'Inventory row fills the available width', 1);
  }
  slots.forEach((rect, index) => {
    assert(inside(rect, viewport), `Reserved slot ${index} is fully visible`);
    assert.equal(rect.occupied, owned.includes(itemIds[index]));
    near(rect.w, rect.h, 'Inventory cells remain square', 0.1);
    assert(rect.w >= 54, 'Desktop inventory icons retain their readable size');
    near(rect.w, slots[0].w, 'Inventory cell sizing is uniform', 0.1);
    if (baseline) assert.deepEqual(coordinates(rect), coordinates(baseline[index]),
      'Inventory ownership changes preserve all canonical positions');
    const item = bounds[`item:${itemIds[index]}`];
    if (owned.includes(itemIds[index])) assert.deepEqual(coordinates(item), coordinates(rect));
    else assert.equal(item, undefined, 'Unowned slots reveal no item identity or actions');
  });
  return slots;
}

async function click(page, rect) {
  const point = center(rect);
  await page.mouse.click(point.x, point.y);
  await page.waitForTimeout(200);
}

async function settleModal(page, panel, ids) {
  let previous, stable = 0;
  for (let frame = 0; frame < 14; frame++) {
    const bounds = (await ui(page)).bounds;
    const point = center(bounds[panel]);
    await page.mouse.move(point.x + frame % 2, point.y);
    await page.waitForTimeout(120);
    const next = (await ui(page)).bounds;
    const current = JSON.stringify(ids.map(id => next[id]));
    stable = previous === current ? stable + 1 : 0;
    previous = current;
    if (stable >= 3) return next;
  }
  assert.fail(`${panel} geometry did not settle`);
}

async function unchanged(page, beforeSave, beforeAction, reason) {
  assert.deepEqual(await save(page), beforeSave, reason);
  assert.deepEqual((await state(page)).last_action, beforeAction, reason);
  assert.equal((await ui(page)).path_remaining, 0, 'Reading the UI starts no movement route');
}

try {
  for (const viewport of viewports) {
    if (process.env.TOS_DESKTOP_WIDTH && Number(process.env.TOS_DESKTOP_WIDTH) !== viewport.width) continue;
    for (const locale of ['en', 'zh-CN']) {
      for (const cycle of [1, 2]) {
        const context = await browser.newContext({ viewport });
        const page = await context.newPage(), errors = [];
        page.on('pageerror', error => errors.push(error.message));
        try {
          await page.goto(process.env.TOS_URL || 'http://127.0.0.1:8080');
          await page.waitForFunction(() => window.tower && JSON.parse(window.tower.ui_json()).sprites_loaded,
            undefined, { timeout: 45000 });
          await page.evaluate(({ source, locale }) => {
            window.tower.import_campaign(source);
            window.tower.set_language(locale);
          }, { source: JSON.stringify(campaign), locale });
          await page.waitForTimeout(locale === 'zh-CN' ? 1600 : 500);
          const base = await save(page);
          await fixture(page, base, [], cycle);
          let debug = await ui(page), bounds = debug.bounds;
          assert.equal(debug.landscape, false, 'Tall desktop views use the spacious desktop layout');
          assert.equal(debug.palette.reverse, cycle === 2);
          const scale = checkScale(debug, viewport);
          checkPanels(bounds, viewport, scale);
          checkToolbar(bounds, scale);
          const slots = checkInventory(bounds, viewport, []);
          const beforeEmpty = await save(page), beforeEmptyAction = (await state(page)).last_action;
          await click(page, bounds['inventory_slot:13']);
          await unchanged(page, beforeEmpty, beforeEmptyAction, 'Empty inventory positions remain inert');
          const emptyShot = `desktop-empty-${viewport.width}x${viewport.height}-${locale}-cycle${cycle}.png`;
          await page.screenshot({ path: resolve(output, emptyShot) });

          const partial = ['hero_orb', 'wisdom_orb', 'lucky_gold'];
          await fixture(page, base, partial, cycle);
          bounds = (await ui(page)).bounds;
          checkPanels(bounds, viewport, scale);
          checkInventory(bounds, viewport, partial, slots);

          await fixture(page, base, [...itemIds].reverse(), cycle);
          bounds = (await ui(page)).bounds;
          checkPanels(bounds, viewport, scale);
          checkToolbar(bounds, scale);
          checkInventory(bounds, viewport, itemIds, slots);
          const beforeRead = await save(page), beforeReadAction = (await state(page)).last_action;
          const toolbarBefore = structuredClone(bounds.tower_toolbar);
          await page.mouse.move(bounds.board.x + bounds.board.cell * 7.5,
            bounds.board.y + bounds.board.cell * 8.5);
          await page.waitForFunction(() => !!JSON.parse(window.tower.ui_json()).bounds.inspection_forecast);
          await page.waitForTimeout(200);
          bounds = (await ui(page)).bounds;
          checkPanels(bounds, viewport, scale);
          checkToolbar(bounds, scale);
          assert.deepEqual(bounds.tower_toolbar, toolbarBefore,
            'Inspecting an enemy leaves the bottom toolbar in place');
          assert(inside(bounds.inspection_forecast, viewport), 'Enemy forecast is visible in the desktop inspector');
          await unchanged(page, beforeRead, beforeReadAction, 'Inspecting an enemy does not change gameplay');
          const shot = `desktop-forecast-${viewport.width}x${viewport.height}-${locale}-cycle${cycle}.png`;
          await page.screenshot({ path: resolve(output, shot) });

          await click(page, bounds.journal_preview_open);
          await page.waitForFunction(() => !!JSON.parse(window.tower.ui_json()).bounds.journal_history);
          let modalBounds = await settleModal(page, 'journal_history_viewport',
            ['journal_history', 'journal_history_heading', 'journal_history_close']);
          assert(inside(modalBounds.journal_history, viewport));
          assert(inside(modalBounds.journal_history_close, viewport));
          await page.keyboard.press('ArrowLeft');
          await page.waitForTimeout(200);
          await unchanged(page, beforeRead, beforeReadAction, 'Reading activity blocks movement and leaves the save unchanged');
          await click(page, modalBounds.journal_history_close);
          await page.waitForFunction(() => !JSON.parse(window.tower.ui_json()).bounds.journal_history);

          bounds = (await ui(page)).bounds;
          await click(page, bounds.enemy_list_open);
          await page.waitForFunction(() => !!JSON.parse(window.tower.ui_json()).bounds.enemy_list_dialog);
          modalBounds = await settleModal(page, 'enemy_list_viewport',
            ['enemy_list_dialog', 'enemy_list_heading', 'enemy_list_close']);
          assert(inside(modalBounds.enemy_list_dialog, viewport));
          assert(inside(modalBounds.enemy_list_close, viewport));
          await unchanged(page, beforeRead, beforeReadAction, 'Opening the floor enemy list leaves gameplay unchanged');
          await click(page, modalBounds.enemy_list_close);
          await page.waitForFunction(() => !JSON.parse(window.tower.ui_json()).bounds.enemy_list_dialog);

          bounds = (await ui(page)).bounds;
          const lucky = center(bounds['item:lucky_gold']);
          await page.mouse.move(lucky.x, lucky.y);
          await page.waitForTimeout(900);
          await unchanged(page, beforeRead, beforeReadAction, 'Reading item help leaves gameplay unchanged');

          const destination = { x: bounds.board.x + bounds.board.cell * 5.5,
            y: bounds.board.y + bounds.board.cell * 6.5, w: 0, h: 0 };
          await click(page, destination);
          await idle(page);
          assert.deepEqual([(await state(page)).player.floor, (await state(page)).player.x,
            (await state(page)).player.y], [4, 5, 6], 'Desktop floor click routes to the selected adjacent cell');
          assert.deepEqual(errors, []);
          report.push({ viewport, locale, cycle, uiScale: scale, board: bounds.board, left: bounds.left_sidebar,
            right: bounds.right_sidebar, inventory: bounds.inventory_grid, toolbar: bounds.tower_toolbar,
            screenshot: shot, emptyScreenshot: emptyShot, errors });
          console.log(`PASS desktop adaptive typography (${scale.toFixed(3)}×), full-height panels, stable inventory and read actions: ${viewport.width}x${viewport.height} ${locale} cycle${cycle}`);
        } catch (error) {
          const debug = await ui(page);
          console.error(JSON.stringify({ uiScale: debug.ui_scale,
            left: debug.bounds.left_sidebar, inventory: debug.bounds.inventory_grid,
            slots: Array.from({ length: 15 }, (_, index) => debug.bounds[`inventory_slot:${index}`]) }));
          await page.screenshot({ path: resolve(output,
            `desktop-layout-failure-${viewport.width}x${viewport.height}-${locale}-cycle${cycle}.png`) });
          throw error;
        } finally {
          await context.close();
        }
      }
    }
  }
  if (!process.env.TOS_DESKTOP_WIDTH || Number(process.env.TOS_DESKTOP_WIDTH) === 1360) {
    const context = await browser.newContext({ viewport: viewports[0] });
    const page = await context.newPage(), errors = [];
    page.on('pageerror', error => errors.push(error.message));
    try {
      await page.goto(process.env.TOS_URL || 'http://127.0.0.1:8080');
      await page.waitForFunction(() => window.tower && JSON.parse(window.tower.ui_json()).sprites_loaded,
        undefined, { timeout: 45000 });
      await page.evaluate(source => {
        window.tower.import_campaign(source);
        window.tower.set_language('en');
      }, JSON.stringify(campaign));
      await page.waitForTimeout(500);
      await fixture(page, await save(page), itemIds, 1);
      const beforeResize = await save(page), beforeResizeAction = (await state(page)).last_action;
      const sequence = [viewports[0], viewports[2], viewports[3], viewports[0]], scales = [];
      let originalToolbar, originalSlots;
      for (const [index, viewport] of sequence.entries()) {
        await page.setViewportSize(viewport);
        await page.waitForTimeout(350);
        let debug = await ui(page), bounds = debug.bounds;
        assert.equal(debug.landscape, false, 'Desktop resizing preserves the desktop organization');
        const scale = checkScale(debug, viewport);
        scales.push(scale);
        checkPanels(bounds, viewport, scale);
        checkToolbar(bounds, scale);
        const slots = checkInventory(bounds, viewport, itemIds);
        if (index === 0) {
          originalToolbar = structuredClone(bounds.tower_toolbar);
          originalSlots = slots.map(coordinates);
        }
        if (index === sequence.length - 1) {
          near(bounds.tower_toolbar.x, originalToolbar.x, 'Toolbar returns to its original horizontal position', 0.1);
          near(bounds.tower_toolbar.y, originalToolbar.y, 'Toolbar returns to its original vertical position', 0.1);
          assert.deepEqual(slots.map(coordinates), originalSlots,
            'Returning to the original viewport restores all reserved inventory positions');
        }
        await page.mouse.move(bounds.board.x + bounds.board.cell * 7.5,
          bounds.board.y + bounds.board.cell * 8.5);
        await page.waitForFunction(() => !!JSON.parse(window.tower.ui_json()).bounds.inspection_forecast);
        await page.waitForTimeout(150);
        debug = await ui(page);
        checkPanels(debug.bounds, viewport, scale);
        checkToolbar(debug.bounds, scale);
        await unchanged(page, beforeResize, beforeResizeAction, 'Resizing and reading the inspector leave gameplay unchanged');
      }
      assert(scales[1] > scales[0] && scales[2] > scales[1],
        'Typography grows across larger desktop resolutions');
      near(scales[3], scales[0], 'Typography returns to baseline after shrinking the window', 0.001);
      assert.deepEqual(errors, []);
      report.push({ scenario: 'adaptive-desktop-resize', viewports: sequence, scales, errors });
      console.log(`PASS desktop resize restores scale and layout: ${scales.map(scale => scale.toFixed(3)).join(' → ')}`);
    } catch (error) {
      await page.screenshot({ path: resolve(output, 'desktop-layout-resize-failure.png') });
      throw error;
    } finally {
      await context.close();
    }
  }
  writeFileSync(resolve(output, 'desktop-layout-report.json'), JSON.stringify(report, null, 2));
} finally {
  await browser.close();
}
