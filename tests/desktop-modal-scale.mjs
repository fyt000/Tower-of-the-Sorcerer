import { chromium } from '@playwright/test';
import { readFileSync, writeFileSync, mkdirSync } from 'node:fs';
import { resolve } from 'node:path';
import assert from 'node:assert/strict';

const root = resolve(import.meta.dirname, '..'), output = resolve(root, 'test-results');
mkdirSync(output, { recursive: true });
const original = JSON.parse(readFileSync(resolve(root, 'data/campaign.json'), 'utf8'));
const { magician_retreat: _retreat, ...roomRules } = original.rules;
const dialogue = JSON.parse(readFileSync(resolve(root, 'data/locales/en.json'), 'utf8')).dialogue;
const tiles = Array(121).fill(6);
tiles[5 * 11 + 6] = 201;
const fixture = JSON.stringify({
  id: 'desktop-modal-scale', title: 'Desktop modal scale', width: 11, height: 11,
  start: { floor: 1, x: 5, y: 5, hp: 100, attack: 10, defense: 5, gold: 0,
    inventory: ['wisdom_orb'] },
  rules: { ...roomRules, stair_links: {}, floor_travel_callbacks: [],
    presentation: { combat_strike_ms: 60 } },
  floors: [{ id: 1, title: 'Journal room', tiles }],
  tiles: { 6: original.tiles['6'], 8: original.tiles['8'], 37: original.tiles['37'],
    201: { name: 'History guard', kind: 'enemy', enemy: 'guard', sprite: 61 } },
  enemies: { guard: { name: 'History guard', hp: 10, attack: 8, defense: 5, gold: 2 } }, events: []
});
const clues = Array.from({ length: 24 }, (_, index) => ({
  cycle: 1, floor: 1, x: index % 11, y: Math.floor(index / 11),
  title: `Remembered clue ${index + 1}`, text: dialogue[String(62 + index)], dialogue_id: 62 + index
}));
const browser = await chromium.launch({ headless: true,
  args: ['--use-angle=swiftshader-webgl', '--autoplay-policy=no-user-gesture-required'] });
const ui = page => page.evaluate(() => JSON.parse(window.tower.ui_json()));
const state = page => page.evaluate(() => JSON.parse(window.tower.state_json()));
const save = page => page.evaluate(() => JSON.parse(window.tower.save_json()));
const center = r => ({ x: r.x + r.w / 2, y: r.y + r.h / 2 });
const inside = (r, v) => r && r.x >= -1 && r.y >= -1
  && r.x + r.w <= v.width + 1 && r.y + r.h <= v.height + 1;
const near = (a, b, label, tolerance = 2) => assert(Math.abs(a - b) <= tolerance,
  `${label}: ${a} versus ${b}`);

async function activate(page, rect) {
  const p = center(rect);
  await page.mouse.click(p.x, p.y);
  await page.waitForTimeout(250);
}
async function settle(page, modal, viewport, close) {
  let previous, count = 0;
  for (let i = 0; i < 15; i++) {
    const bounds = (await ui(page)).bounds, p = center(bounds[viewport]);
    await page.mouse.move(p.x + i % 2, p.y);
    await page.waitForTimeout(120);
    const updated = (await ui(page)).bounds;
    const current = JSON.stringify([updated[modal], updated[viewport], updated[close]]);
    count = current === previous ? count + 1 : 0;
    previous = current;
    if (count >= 3) return updated;
  }
  assert.fail(`Modal placement did not settle: ${previous}`);
}
async function unchanged(page, before, action, label) {
  assert.deepEqual(await save(page), before, `${label}: save unchanged`);
  assert.deepEqual((await state(page)).last_action, action, `${label}: no gameplay action`);
}

const report = [];
try {
  for (const viewport of [{ width: 1920, height: 1080 }, { width: 2560, height: 1440 }]) {
    for (const locale of ['en', 'zh-CN']) {
      const context = await browser.newContext({ viewport }), page = await context.newPage(), errors = [];
      page.on('pageerror', e => errors.push(e.message));
      try {
        await page.goto(process.env.TOS_URL || 'http://127.0.0.1:8080');
        await page.waitForFunction(() => window.tower && JSON.parse(window.tower.ui_json()).sprites_loaded,
          undefined, { timeout: 45000 });
        await page.evaluate(({ fixture, locale, clues }) => {
          window.tower.import_campaign(fixture);
          window.tower.set_language(locale);
          const saved = JSON.parse(window.tower.save_json());
          saved.log = Array.from({ length: 100 }, (_, i) => `History entry ${i}: explored a corridor and recorded the result of the attempt.`);
          saved.journal = clues;
          window.tower.load_save(JSON.stringify(saved));
        }, { fixture, locale, clues });
        await page.waitForTimeout(locale === 'zh-CN' ? 1600 : 400);
        await page.evaluate(() => window.tower.command_json(JSON.stringify({ type: 'move', direction: 'right' })));
        await page.waitForFunction(() => {
          const debug = JSON.parse(window.tower.ui_json());
          return !debug.animation && !debug.presentation_remaining && !debug.path_remaining;
        });
        let debug = await ui(page), scale = debug.ui_scale;
        assert(scale > 1 && scale <= 2, 'Larger desktop modal uses a proportional scale');
        const before = await save(page), action = (await state(page)).last_action;
        const battle = (await state(page)).battle_log.at(-1);
        assert(battle, 'Fixture creates a real completed battle to inspect at desktop scales');
        await activate(page, debug.bounds.journal_header);
        await page.waitForFunction(() => !!JSON.parse(window.tower.ui_json()).bounds.journal_history);
        let bounds = await settle(page, 'journal_history', 'journal_history_viewport', 'journal_history_close');
        for (const id of ['journal_history', 'journal_history_heading', 'journal_history_close']) {
          assert(inside(bounds[id], viewport), `${id} stays fully visible`);
        }
        near(bounds.journal_history.w, 660 * scale + 2, 'History width scales with text and padding', 3);
        near(bounds.journal_history_close.h, 34 * scale, 'History Close scales with typography', 0.2);
        assert(bounds.journal_history_heading.h >= 20 * scale, 'History heading scales with the desktop UI');
        await activate(page, bounds[`journal_battle_toggle:${battle.log_id}`]);
        bounds = await settle(page, 'journal_history', 'journal_history_viewport', 'journal_history_close');
        const details = bounds[`journal_battle_details:${battle.log_id}`];
        assert(inside(details, viewport), 'Expanded battle details remain visible at larger scales');
        assert(details.w <= bounds.journal_history_viewport.w, 'Expanded facts fit the journal content width');
        assert.deepEqual([details.enemy_hp, details.enemy_attack, details.enemy_defense, details.damage, details.reward],
          [10, 8, 5, 3, 2], 'Expanded scaled details preserve actual battle values');
        near(bounds[`journal_battle_toggle:${battle.log_id}`].h, 20 * scale,
          'Battle expansion control scales with its font', 0.2);
        const historyClose = structuredClone(bounds.journal_history_close);
        const historyHeading = structuredClone(bounds.journal_history_heading);
        let p = center(bounds.journal_history_viewport);
        await page.mouse.move(p.x, p.y);
        await page.mouse.wheel(0, 1200);
        await page.waitForTimeout(350);
        bounds = (await ui(page)).bounds;
        assert(bounds.journal_history_viewport.offset_y > 0, 'Large desktop history remains scrollable');
        assert.deepEqual(bounds.journal_history_close, historyClose, 'History Close remains fixed during scrolling');
        assert.deepEqual(bounds.journal_history_heading, historyHeading, 'History heading remains fixed during scrolling');
        await unchanged(page, before, action, 'Reading large desktop history');
        await page.screenshot({ path: resolve(output, `desktop-modal-history-${viewport.width}x${viewport.height}-${locale}.png`) });
        await activate(page, bounds.journal_history_close);

        bounds = (await ui(page)).bounds;
        await activate(page, bounds['item:wisdom_orb']);
        await page.waitForFunction(() => !!JSON.parse(window.tower.ui_json()).bounds.journal_dialog);
        bounds = await settle(page, 'journal_dialog', 'wisdom_journal_viewport', 'journal_close');
        assert(inside(bounds.journal_dialog, viewport), 'Scaled Wisdom modal fits');
        assert(inside(bounds.journal_close, viewport), 'Scaled Wisdom Close fits');
        near(bounds.journal_dialog.w, 628 * scale + 2, 'Wisdom width scales with text and padding', 3);
        near(bounds.journal_close.h, 34 * scale, 'Wisdom Close scales with typography', 0.2);
        const wisdomSave = await save(page), wisdomAction = (await state(page)).last_action;
        const wisdomClose = structuredClone(bounds.journal_close);
        p = center(bounds.wisdom_journal_viewport);
        await page.mouse.move(p.x, p.y);
        await page.mouse.wheel(0, 1200);
        await page.waitForTimeout(350);
        bounds = (await ui(page)).bounds;
        assert(bounds.wisdom_journal_viewport.offset_y > 0, 'Scaled Wisdom hints remain scrollable');
        assert.deepEqual(bounds.journal_close, wisdomClose, 'Wisdom Close remains fixed during scrolling');
        await unchanged(page, wisdomSave, wisdomAction, 'Reading large desktop Wisdom');
        await page.screenshot({ path: resolve(output, `desktop-modal-wisdom-${viewport.width}x${viewport.height}-${locale}.png`) });
        await activate(page, bounds.journal_close);
        await page.waitForFunction(() => !JSON.parse(window.tower.ui_json()).animation);

        debug = await ui(page);
        const settingsSave = await save(page), settingsAction = (await state(page)).last_action;
        await activate(page, debug.bounds.settings);
        await page.waitForFunction(() => !!JSON.parse(window.tower.ui_json()).bounds.new_game);
        await page.waitForTimeout(500);
        bounds = (await ui(page)).bounds;
        assert(inside(bounds.new_game, viewport), 'Scaled Settings content remains reachable');
        near(bounds.new_game.h, 34 * scale, 'Settings actions scale with typography', 0.2);
        await unchanged(page, settingsSave, settingsAction, 'Opening large desktop Settings');
        await page.mouse.move(4, 4);
        await page.screenshot({ path: resolve(output, `desktop-modal-settings-${viewport.width}x${viewport.height}-${locale}.png`) });
        await page.keyboard.press('Escape');
        await page.waitForFunction(() => !JSON.parse(window.tower.ui_json()).bounds.new_game);
        await unchanged(page, settingsSave, settingsAction, 'Closing large desktop Settings');
        assert.deepEqual(errors, [], 'No runtime errors');
        report.push({ viewport, locale, scale, history: { close: historyClose, heading: historyHeading }, wisdomClose });
        console.log(`PASS scaled journal, Wisdom, Settings and read-only scrolling: ${viewport.width}x${viewport.height} ${locale}, scale ${scale}`);
      } catch (error) {
        await page.screenshot({ path: resolve(output, `desktop-modal-failure-${viewport.width}x${viewport.height}-${locale}.png`) });
        throw error;
      } finally { await context.close(); }
    }
  }
  writeFileSync(resolve(output, 'desktop-modal-scale-report.json'), JSON.stringify(report, null, 2));
} finally { await browser.close(); }
