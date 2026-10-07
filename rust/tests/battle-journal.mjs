import { chromium } from '@playwright/test';
import { readFileSync, mkdirSync } from 'node:fs';
import { resolve } from 'node:path';
import assert from 'node:assert/strict';

const root = resolve(import.meta.dirname, '..'), output = resolve(root, '../build/rust/test-results');
mkdirSync(output, { recursive: true });
const original = JSON.parse(readFileSync(resolve(root, '../data/campaign.json'), 'utf8'));
const tiles = Array(121).fill(6);
tiles[5 * 11 + 6] = 201;
const fixture = JSON.stringify({
  id: 'battle-journal-regression', title: 'Battle journal test', width: 11, height: 11,
  start: { floor: 1, x: 5, y: 5, hp: 1000, attack: 40, defense: 10, gold: 0, inventory: [] },
  rules: { empty_tile: 6, forecast_requires_item: 'hero_orb', presentation: { combat_strike_ms: 300 } },
  floors: [{ id: 1, title: 'Battle history room', tiles }],
  tiles: { 6: original.tiles['6'], 201: { name: 'History guard', kind: 'enemy', enemy: 'guard', sprite: 61 } },
  enemies: { guard: { name: 'History guard', hp: 100, attack: 30, defense: 5, gold: 27 } }, events: []
});
const browser = await chromium.launch({ headless: true,
  args: ['--use-angle=swiftshader-webgl', '--autoplay-policy=no-user-gesture-required'] });
const ui = page => page.evaluate(() => JSON.parse(window.tower.ui_json()));
const save = page => page.evaluate(() => JSON.parse(window.tower.save_json()));
const state = page => page.evaluate(() => JSON.parse(window.tower.state_json()));
const center = r => ({ x: r.x + r.w / 2, y: r.y + r.h / 2 });
const visible = (r, v) => r && r.x >= 0 && r.y >= 0 && r.x + r.w <= v.width + 1 && r.y + r.h <= v.height + 1;

async function idle(page) {
  await page.waitForFunction(() => { const s = JSON.parse(window.tower.ui_json());
    return !s.animation && !s.presentation_remaining && !s.path_remaining;
  }, undefined, { timeout: 10000 });
}
async function drag(cdp, from, to) {
  await cdp.send('Input.dispatchTouchEvent', { type: 'touchStart', touchPoints: [from] });
  for (let i = 1; i <= 12; i++) {
    await cdp.send('Input.dispatchTouchEvent', { type: 'touchMove', touchPoints: [{
      x: from.x + (to.x - from.x) * i / 12, y: from.y + (to.y - from.y) * i / 12
    }] });
    await new Promise(resolve => setTimeout(resolve, 25));
  }
  await cdp.send('Input.dispatchTouchEvent', { type: 'touchEnd', touchPoints: [] });
}
async function reveal(page, cdp, viewport, id) {
  for (let attempt = 0; attempt < 18; attempt++) {
    const bounds = (await ui(page)).bounds;
    const area = bounds.journal_history_viewport;
    const inHistory = id.startsWith('journal_battle_') || id.startsWith('journal_history_entry:');
    const clipped = inHistory && area && bounds[id] && (bounds[id].y < area.y || bounds[id].y + bounds[id].h > area.y + area.h);
    if (visible(bounds[id], viewport) && !clipped) return bounds[id];
    if (area) {
      const down = bounds[id] && bounds[id].y < area.y;
      if (cdp) await drag(cdp,
        { x: area.x + area.w / 2, y: down ? area.y + 20 : area.y + area.h - 20 },
        { x: area.x + area.w / 2, y: down ? area.y + area.h - 20 : area.y + 20 });
      else {
        const point = center(area); await page.mouse.move(point.x, point.y);
        await page.mouse.wheel(0, down ? -600 : 600);
      }
    } else if (cdp) {
      const down = bounds[id] && bounds[id].y < 0;
      await drag(cdp, { x: viewport.width - 30, y: down ? 160 : viewport.height - 60 },
        { x: viewport.width - 30, y: down ? viewport.height - 60 : 160 });
    } else {
      await page.mouse.move(viewport.width - 30, viewport.height - 60);
      await page.mouse.wheel(0, bounds[id]?.y < 0 ? -400 : 400);
    }
    await page.waitForTimeout(250);
  }
  assert.fail(`${id} is unreachable`);
}
async function activate(page, cdp, r) {
  const point = center(r);
  if (cdp) await page.touchscreen.tap(point.x, point.y);
  else await page.mouse.click(point.x, point.y);
  await page.waitForTimeout(300);
}
async function unchanged(page, saved, action, reason) {
  assert.deepEqual(await save(page), saved, `${reason}: save unchanged`);
  assert.deepEqual((await state(page)).last_action, action, `${reason}: no game action`);
}

try {
  for (const viewport of [{ width: 1440, height: 1000 }, { width: 390, height: 844 }, { width: 844, height: 390 }]) {
    if (process.env.TOS_BATTLE_JOURNAL_WIDTH && Number(process.env.TOS_BATTLE_JOURNAL_WIDTH) !== viewport.width) continue;
    for (const locale of ['en', 'zh-CN']) {
      const touch = viewport.width < 500 || viewport.height <= 500;
      const context = await browser.newContext({ viewport, hasTouch: touch });
      const page = await context.newPage(), errors = [];
      const cdp = touch ? await context.newCDPSession(page) : null;
      page.on('pageerror', error => errors.push(error.message));
      try {
        await page.goto(process.env.TOS_URL || 'http://127.0.0.1:8080');
        await page.waitForFunction(() => window.tower && JSON.parse(window.tower.ui_json()).sprites_loaded,
          undefined, { timeout: 45000 });
        await page.evaluate(({ fixture, locale }) => {
          window.tower.import_campaign(fixture); window.tower.set_language(locale);
          const saved = JSON.parse(window.tower.save_json());
          saved.log = Array.from({ length: 100 }, (_, i) => `Prior retained action ${i}`);
          saved.log_start = 400;
          saved.battle_log = [];
          window.tower.load_save(JSON.stringify(saved));
        }, { fixture, locale });
        await page.waitForTimeout(locale === 'zh-CN' ? 1600 : 400);
        await idle(page);
        await activate(page, cdp, await reveal(page, cdp, viewport, 'journal_header'));
        await page.waitForFunction(() => !!JSON.parse(window.tower.ui_json()).bounds.journal_history);
        await page.evaluate(() => window.tower.command_json(JSON.stringify({ type: 'move', direction: 'right' })));
        const activeSample = await (await page.waitForFunction(() => {
          const ui = JSON.parse(window.tower.ui_json());
          return ui.animation === 'battle' && ui.bounds.battle_overlay
            ? { ui, state: JSON.parse(window.tower.state_json()) } : false;
        })).jsonValue();
        const pending = activeSample.state.battle_log.at(-1);
        const activeBounds = activeSample.ui.bounds, overlay = activeBounds.battle_overlay, board = activeBounds.board;
        assert(overlay, 'Active combat appears on the floor');
        assert(overlay.x >= board.x && overlay.y >= board.y && overlay.x + overlay.w <= board.x + board.w
          && overlay.y + overlay.h <= board.y + board.h, 'The combat overlay is contained within the floor');
        assert.deepEqual([overlay.enemy_max_hp, overlay.attack, overlay.defense, overlay.gold], [100, 30, 5, null],
          'Before Hero Orb the overlay exposes actual raw stats and keeps reward hidden');
        assert.equal(activeBounds.inspection_battle, undefined, 'Combat does not replace the selected-tile inspector');
        assert(pending, 'A resolved battle is recorded even while its animation is playing');
        assert.equal(activeBounds[`journal_battle_toggle:${pending.log_id}`], undefined,
          'Future battle facts are not associated with old visible activity during presentation');
        await idle(page);
        assert.equal((await ui(page)).bounds.battle_overlay, undefined, 'The overlay ends with the fight');
        const completed = await state(page), battle = completed.battle_log.at(-1);
        assert(completed.log_start > 400, 'The oldest activity was trimmed with a stable offset');
        assert.equal(completed.log.length, 100);
        const index = battle.log_id - completed.log_start;
        assert(index >= 98 && index < 100, 'The resolved encounter is associated with a recent retained activity');
        assert.deepEqual(['enemy_hp', 'enemy_attack', 'enemy_defense', 'damage', 'reward', 'hero_after_hp']
          .map(key => battle[key]), [100, 30, 5, 40, 27, 960]);
        assert.deepEqual(['hp', 'attack', 'defense'].map(key => battle.hero_before[key]), [1000, 40, 10]);
        assert.equal(battle.outcome, 'defeated');
        assert.equal(completed.forecasts_unlocked, false, 'Past facts are available without Hero Orb');
        let bounds = (await ui(page)).bounds;
        assert(bounds[`journal_battle_toggle:${battle.log_id}`], 'The matching retained activity has an expansion control');
        assert.equal(bounds[`journal_battle_details:${battle.log_id}`], undefined, 'Details start collapsed');
        await activate(page, cdp, bounds.journal_history_close);
        const saved = await save(page), action = (await state(page)).last_action;
        await activate(page, cdp, await reveal(page, cdp, viewport, `journal_preview_entry:${index}`));
        await page.waitForFunction(id => !!JSON.parse(window.tower.ui_json()).bounds[`journal_battle_details:${id}`], battle.log_id);
        bounds = (await ui(page)).bounds;
        const details = bounds[`journal_battle_details:${battle.log_id}`];
        assert.deepEqual(['enemy_hp', 'enemy_attack', 'enemy_defense', 'damage', 'reward', 'hero_after_hp']
          .map(key => details[key]), [100, 30, 5, 40, 27, 960], 'Expanded UI shows historical facts from that entry');
        await unchanged(page, saved, action, 'Expanding a recent battle');
        await activate(page, cdp, await reveal(page, cdp, viewport, `journal_battle_toggle:${battle.log_id}`));
        await page.waitForTimeout(250);
        assert.equal((await ui(page)).bounds[`journal_battle_details:${battle.log_id}`], undefined);
        await unchanged(page, saved, action, 'Collapsing details');
        await activate(page, cdp, await reveal(page, cdp, viewport, `journal_battle_toggle:${battle.log_id}`));
        await page.waitForTimeout(250);
        await unchanged(page, saved, action, 'Reopening details');
        await page.mouse.move(5, 5); await page.waitForTimeout(200);
        await page.screenshot({ path: resolve(output, `battle-journal-${viewport.width}x${viewport.height}-${locale}.png`) });
        if (viewport.height <= 500) {
          let beforeOffset = (await ui(page)).bounds.journal_history_viewport.offset_y;
          for (let attempt = 0; attempt < 4; attempt++) {
            bounds = (await ui(page)).bounds;
            const area = bounds.journal_history_viewport, detail = bounds[`journal_battle_details:${battle.log_id}`];
            if (detail.y + detail.h <= area.y + area.h) break;
            await drag(cdp, { x: area.x + area.w / 2, y: area.y + area.h - 20 },
              { x: area.x + area.w / 2, y: area.y + 20 });
            await page.waitForTimeout(300);
          }
          bounds = (await ui(page)).bounds;
          assert(bounds.journal_history_viewport.offset_y > beforeOffset, 'Real touch scrolling reveals the lower battle facts');
          assert(bounds[`journal_battle_details:${battle.log_id}`].y + bounds[`journal_battle_details:${battle.log_id}`].h
            <= bounds.journal_history_viewport.y + bounds.journal_history_viewport.h, 'The HP transition and final strike counts are reachable');
          await unchanged(page, saved, action, 'Scrolling expanded battle details');
          await page.screenshot({ path: resolve(output, `battle-journal-bottom-${viewport.width}x${viewport.height}-${locale}.png`) });
        }

        await page.evaluate(source => window.tower.load_save(source), JSON.stringify(saved));
        await page.waitForTimeout(250);
        assert.deepEqual((await state(page)).battle_log, completed.battle_log, 'Battle history survives save/load');
        assert.equal((await state(page)).log_start, completed.log_start);
        const restoredAction = (await state(page)).last_action;
        await activate(page, cdp, await reveal(page, cdp, viewport, 'journal_header'));
        assert((await ui(page)).bounds[`journal_battle_toggle:${battle.log_id}`], 'Stable association survives save/load');
        await unchanged(page, saved, restoredAction, 'Reading restored battle history');
        if (viewport.height <= 500) {
          await page.evaluate(source => {
            const campaign = JSON.parse(source);
            campaign.rules.presentation.combat_strike_ms = 1000;
            window.tower.import_campaign(JSON.stringify(campaign));
          }, fixture);
          await page.waitForTimeout(250);
          await idle(page);
          await page.evaluate(() => window.tower.command_json(JSON.stringify({ type: 'move', direction: 'right' })));
          await page.waitForFunction(() => {
            const ui = JSON.parse(window.tower.ui_json());
            return ui.animation === 'battle' && ui.bounds.battle_overlay && !ui.bounds.journal_history;
          });
          await page.screenshot({ path: resolve(output, `battle-overlay-${viewport.width}x${viewport.height}-${locale}.png`) });
          await idle(page);
        }
        assert.deepEqual(errors, []);
        console.log(`PASS battle facts, stable retained log, save/load and read-only expansion: ${viewport.width}x${viewport.height} ${locale}`);
      } catch (error) {
        await page.screenshot({ path: resolve(output, `battle-journal-failure-${viewport.width}x${viewport.height}-${locale}.png`) });
        throw error;
      } finally {
        await context.close();
      }
    }
  }
} finally {
  await browser.close();
}
