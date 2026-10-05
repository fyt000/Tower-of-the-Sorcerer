import { chromium } from '@playwright/test';
import { readFileSync, mkdirSync } from 'node:fs';
import { resolve } from 'node:path';
import assert from 'node:assert/strict';

const root = resolve(import.meta.dirname, '..'), output = resolve(root, 'test-results');
mkdirSync(output, { recursive: true });
const original = JSON.parse(readFileSync(resolve(root, 'data/campaign.json'), 'utf8'));
const { magician_retreat: _retreat, ...roomRules } = original.rules;
const itemIds = Object.values(original.tiles).filter(tile => tile.kind === 'item').map(tile => tile.item);
assert.equal(itemIds.length, 15);
const specialTiles = Object.fromEntries(Object.entries(original.tiles).filter(([, tile]) =>
  ['item', 'equipment', 'floor', 'wall'].includes(tile.kind)));
function fixture(inventory, extras = {}, originalSlots = true) {
  return JSON.stringify({
    id: 'inventory-layout-regression', title: 'Inventory layout test', width: 11, height: 11,
    start: { floor: 1, x: 5, y: 5, hp: 100, attack: 10, defense: 5, gold: 0,
      inventory: ['sword_5', 'sacred_shield', ...inventory] },
    rules: { ...roomRules, stair_links: {}, floor_travel_callbacks: [],
      flying_original_selection: originalSlots },
    floors: [{ id: 1, title: 'Inventory room', tiles: Array(121).fill(6) }],
    tiles: { ...specialTiles, ...extras }, enemies: {}, events: []
  });
}
const browser = await chromium.launch({ headless: true,
  args: ['--use-angle=swiftshader-webgl', '--autoplay-policy=no-user-gesture-required'] });
const sizes = [{ width: 1440, height: 1000 }, { width: 1360, height: 920 }, { width: 390, height: 844 }];
const state = page => page.evaluate(() => JSON.parse(window.tower.state_json()));
const ui = page => page.evaluate(() => JSON.parse(window.tower.ui_json()));
const center = rect => ({ x: rect.x + rect.w / 2, y: rect.y + rect.h / 2 });
const coordinates = rect => [rect.x, rect.y, rect.w, rect.h];
function inViewport(rect, viewport) {
  return rect.x >= 0 && rect.y >= 0 && rect.x + rect.w <= viewport.width + 1
    && rect.y + rect.h <= viewport.height + 1;
}
function inGrid(rect, grid) {
  return rect.x >= grid.x - 1 && rect.y >= grid.y - 1 && rect.x + rect.w <= grid.x + grid.w + 1
    && rect.y + rect.h <= grid.y + grid.h + 1;
}
async function idle(page) {
  await page.waitForFunction(() => { const s = JSON.parse(window.tower.ui_json());
    return !s.animation && !s.presentation_remaining && !s.path_remaining; }, undefined, { timeout: 10000 });
}
async function importFixture(page, source) {
  await page.evaluate(source => window.tower.import_campaign(source), source);
  await page.waitForTimeout(250); await idle(page);
}
async function touchDrag(cdp, from, to) {
  await cdp.send('Input.dispatchTouchEvent', { type: 'touchStart', touchPoints: [from] });
  await new Promise(resolve => setTimeout(resolve, 70));
  for (let step = 1; step <= 12; step++) {
    await cdp.send('Input.dispatchTouchEvent', { type: 'touchMove', touchPoints: [{
      x: from.x + (to.x - from.x) * step / 12,
      y: from.y + (to.y - from.y) * step / 12 }] });
    await new Promise(resolve => setTimeout(resolve, 25));
  }
  await cdp.send('Input.dispatchTouchEvent', { type: 'touchEnd', touchPoints: [] });
}
async function open(viewport, locale) {
  const context = await browser.newContext({ viewport, hasTouch: viewport.width < 500 });
  const page = await context.newPage(), errors = [];
  page.on('pageerror', error => errors.push(error.message));
  await page.goto(process.env.TOS_URL || 'http://127.0.0.1:8080');
  await page.waitForFunction(() => window.tower && JSON.parse(window.tower.ui_json()).sprites_loaded,
    undefined, { timeout: 45000 });
  await page.evaluate(locale => window.tower.set_language(locale), locale);
  await page.waitForTimeout(locale === 'zh-CN' ? 1600 : 300);
  return { context, page, errors };
}

try {
  for (const viewport of sizes) {
    if (process.env.TOS_INVENTORY_WIDTH && Number(process.env.TOS_INVENTORY_WIDTH) !== viewport.width) continue;
    for (const locale of ['en', 'zh-CN']) {
      const { context, page, errors } = await open(viewport, locale);
      const mobile = viewport.width < 500;
      await importFixture(page, fixture([]));
      const empty = (await ui(page)).bounds, initial = await state(page);
      assert.equal(empty.inventory_grid.slots, 15, 'Original inventory reserves all 15 positions');
      assert.equal(empty.inventory_viewport, undefined, 'Inventory has no inner scroll area');
      assert.equal(Object.keys(empty).filter(id => id.startsWith('item:')).length, 0,
        'Unowned items expose no names, sprites, help or actions');
      for (let slot = 0; slot < 15; slot++) {
        const r = empty[`inventory_slot:${slot}`];
        assert.equal(r.occupied, false);
        assert.equal(r.w, r.h, 'Inventory positions stay square');
        if (mobile) assert.equal(r.w, 54, 'Portrait inventory retains its readable cell size');
        else assert(r.w >= 54, 'Desktop inventory fills its rail without shrinking the icons');
        assert(inGrid(r, empty.inventory_grid)); assert(inViewport(r, viewport));
      }
      if (!mobile) {
        const firstRow = Array.from({ length: 15 }, (_, slot) => empty[`inventory_slot:${slot}`])
          .filter(rect => rect.y === empty['inventory_slot:0'].y);
        assert([3, 5].includes(firstRow.length), 'Desktop inventory reserves complete rows for all 15 items');
        assert(Math.abs(firstRow[0].x - empty.inventory_grid.x) <= 1);
        assert(Math.abs(firstRow.at(-1).x + firstRow.at(-1).w
          - empty.inventory_grid.x - empty.inventory_grid.w) <= 1,
        'Desktop inventory uses the full available row width');
      }
      const blank = center(empty['inventory_slot:13']);
      if (mobile) await page.touchscreen.tap(blank.x, blank.y);
      else await page.mouse.click(blank.x, blank.y);
      await page.waitForTimeout(150);
      assert.deepEqual((await state(page)).player, initial.player, 'Empty slot is inert');
      assert.deepEqual((await state(page)).last_action, initial.last_action);
      if (viewport.width === 1440) await page.screenshot({ path: resolve(output, `inventory-layout-empty-${locale}.png`) });

      await importFixture(page, fixture([...itemIds].reverse()));
      let bounds = (await ui(page)).bounds;
      assert.deepEqual((await state(page)).inventory_items.map(item => item.id), [...itemIds].reverse());
      assert.equal(bounds.inventory_grid.slots, 15);
      for (const [slot, id] of itemIds.entries()) {
        const r = bounds[`item:${id}`];
        assert.equal(bounds[`inventory_slot:${slot}`].occupied, true);
        assert.deepEqual(coordinates(r), coordinates(empty[`inventory_slot:${slot}`]),
          'Canonical positions are independent of acquisition order');
        assert(inGrid(r, bounds.inventory_grid)); assert(inViewport(r, viewport), `${id} is fully visible`);
      }
      if (mobile) assert(bounds.inventory_grid.y + bounds.inventory_grid.h < bounds.board.y,
        'Mobile inventory is above the board');
      else {
        const lucky = center(bounds['item:lucky_gold']);
        await page.mouse.move(lucky.x, lucky.y); await page.waitForTimeout(900);
      }
      await page.screenshot({ path: resolve(output, `inventory-layout-full-${viewport.width}x${viewport.height}-${locale}.png`) });
      const active = center(bounds['item:super_mattock']);
      if (mobile) await page.touchscreen.tap(active.x, active.y);
      else await page.mouse.click(active.x, active.y);
      await page.waitForTimeout(150); await idle(page);
      const after = await state(page);
      assert(!after.player.inventory.includes('super_mattock'), 'Owned item remains usable');
      assert.deepEqual([after.player.x, after.player.y], [5, 5], 'Item use does not dispatch a board route');
      const consumed = (await ui(page)).bounds;
      assert.equal(consumed.inventory_grid.slots, 15); assert.equal(consumed['inventory_slot:13'].occupied, false);
      assert.equal(consumed['item:super_mattock'], undefined);
      for (let slot = 0; slot < 15; slot++) assert.deepEqual(coordinates(consumed[`inventory_slot:${slot}`]),
        coordinates(bounds[`inventory_slot:${slot}`]), 'Consumption does not move another item');

      if (mobile) {
        const cdp = await context.newCDPSession(page);
        const heading = { x: consumed.inventory_grid.x + consumed.inventory_grid.w / 2,
          y: consumed.inventory_grid.y - 38 };
        await touchDrag(cdp, heading, { x: heading.x, y: Math.max(20, heading.y - 300) });
        await page.waitForTimeout(500);
        bounds = (await ui(page)).bounds;
        assert(bounds.inventory_grid.y < consumed.inventory_grid.y - 50,
          'Touch dragging scrolls the whole workspace');
        assert.equal(bounds.inventory_grid.h, consumed.inventory_grid.h, 'Outer scrolling does not collapse inventory');
        assert.deepEqual((await state(page)).player, after.player, 'Touch scrolling does not move or use an item');
        assert.deepEqual((await state(page)).last_action, after.last_action, 'Touch scrolling does not dispatch a board action');
        await page.screenshot({ path: resolve(output, `inventory-layout-mobile-scrolled-${locale}.png`) });
        await page.evaluate(() => {
          const save = JSON.parse(window.tower.save_json());
          save.player.hp = 396000; save.player.attack = 4400; save.player.defense = 2200;
          window.tower.load_save(JSON.stringify(save));
        });
        await page.mouse.move(viewport.width / 2, viewport.height / 2);
        await page.mouse.wheel(0, -2000); await page.waitForTimeout(400);
        assert.equal((await state(page)).player.hp, 396000);
        await page.screenshot({ path: resolve(output, `inventory-layout-large-stats-${viewport.width}x${viewport.height}-${locale}.png`) });
      }
      assert.deepEqual(errors, []);
      console.log(`PASS stable 15 slots, full layout, help and item use: ${viewport.width}x${viewport.height} ${locale}`);
      await context.close();
    }
  }

  // A custom inventory can grow beyond the original capacity. Its card grows with
  // the grid, and scrolling belongs to the workspace rather than a clipped inner list.
  for (const viewport of [sizes[1], sizes[2]]) {
    if (process.env.TOS_INVENTORY_WIDTH && Number(process.env.TOS_INVENTORY_WIDTH) !== viewport.width) continue;
    const { context, page, errors } = await open(viewport, 'en');
    const extras = Object.fromEntries(Array.from({ length: 60 }, (_, index) => [200 + index,
      { name: `Custom item ${index + 1}`, kind: 'item', item: `custom_${index}`, sprite: original.tiles['50'].sprite }]));
    const ids = ['bomb', 'super_mattock', ...Array.from({ length: 60 }, (_, index) => `custom_${index}`)];
    await importFixture(page, fixture(ids, extras, false));
    const initial = await state(page), initialBounds = (await ui(page)).bounds;
    assert.equal(initialBounds.inventory_grid.slots, 62, 'Custom inventory uses only actual owned entries');
    assert(initialBounds.inventory_grid.h > 250, 'Custom items expand the full grid');
    for (const id of ids) assert(inGrid(initialBounds[`item:${id}`], initialBounds.inventory_grid),
      'Every custom entry belongs to the uncut grid');
    let bounds = initialBounds;
    assert(!inViewport(bounds['item:custom_59'], viewport), 'Large custom inventory requires workspace scrolling');
    for (let attempt = 0; attempt < 4 && !inViewport(bounds['item:custom_59'], viewport); attempt++) {
      const p = { x: bounds.inventory_grid.x + bounds.inventory_grid.w / 2,
        y: Math.max(30, Math.min(viewport.height - 80, bounds.inventory_grid.y + 60)) };
      await page.mouse.move(p.x, p.y); await page.mouse.wheel(0, 600); await page.waitForTimeout(400);
      bounds = (await ui(page)).bounds;
    }
    assert(inViewport(bounds['item:custom_59'], viewport), 'Workspace scrolling reaches the final custom item');
    assert(bounds.inventory_grid.y < initialBounds.inventory_grid.y, 'Wheel input scrolled the workspace');
    assert.equal(bounds.inventory_grid.h, initialBounds.inventory_grid.h, 'Scrolling keeps the full grid height');
    assert.equal(bounds.inventory_grid.y - initialBounds.inventory_grid.y,
      bounds.board.y - initialBounds.board.y, 'Inventory and board share the workspace scroll');
    assert.deepEqual((await state(page)).player, initial.player);
    assert.deepEqual((await state(page)).last_action, initial.last_action);
    await page.screenshot({ path: resolve(output, `inventory-layout-custom-${viewport.width}x${viewport.height}.png`) });
    assert.deepEqual(errors, []);
    console.log(`PASS 62 custom items expand the grid and remain reachable: ${viewport.width}x${viewport.height}`);
    await context.close();
  }
} finally {
  await browser.close();
}
