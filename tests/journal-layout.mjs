import { chromium } from '@playwright/test';
import { readFileSync, writeFileSync, mkdirSync } from 'node:fs';
import { resolve } from 'node:path';
import assert from 'node:assert/strict';

const root = resolve(import.meta.dirname, '..');
const output = resolve(root, 'test-results');
mkdirSync(output, { recursive: true });
const original = JSON.parse(readFileSync(resolve(root, 'data/campaign.json'), 'utf8'));
const dialogue = JSON.parse(readFileSync(resolve(root, 'data/locales/en.json'), 'utf8')).dialogue;
const fixture = JSON.stringify({
  id: 'journal-layout-regression', title: 'Journal layout test', width: 11, height: 11,
  start: { floor: 1, x: 5, y: 5, hp: 100, attack: 10, defense: 5, gold: 0,
    inventory: ['wisdom_orb'] },
  rules: { ...original.rules, stair_links: {}, floor_travel_callbacks: [] },
  floors: [{ id: 1, title: 'Journal room', tiles: Array(121).fill(6) }],
  tiles: { 6: original.tiles['6'], 8: original.tiles['8'], 37: original.tiles['37'] },
  enemies: {}, events: []
});
const log = Array.from({ length: 100 }, (_, index) =>
  `History entry ${String(index).padStart(3, '0')}: explored a corridor and recorded the result of the attempt.`);
const clues = Array.from({ length: 24 }, (_, index) => ({
  cycle: 1, floor: 1, x: index % 11, y: Math.floor(index / 11),
  title: `Remembered clue ${index + 1}`, text: dialogue[String(62 + index)], dialogue_id: 62 + index
}));
const browser = await chromium.launch({ headless: true,
  args: ['--use-angle=swiftshader-webgl', '--autoplay-policy=no-user-gesture-required'] });
const report = [];
const state = page => page.evaluate(() => JSON.parse(window.tower.state_json()));
const ui = page => page.evaluate(() => JSON.parse(window.tower.ui_json()));
const save = page => page.evaluate(() => JSON.parse(window.tower.save_json()));
const center = rect => ({ x: rect.x + rect.w / 2, y: rect.y + rect.h / 2 });

function inside(rect, viewport) {
  return rect && rect.x >= -1 && rect.y >= -1
    && rect.x + rect.w <= viewport.width + 1 && rect.y + rect.h <= viewport.height + 1;
}

function contained(rect, viewport) {
  return rect && rect.x >= viewport.x - 1 && rect.y >= viewport.y - 1
    && rect.x + rect.w <= viewport.x + viewport.w + 1
    && rect.y + rect.h <= viewport.y + viewport.h + 1;
}

async function ready(page) {
  await page.waitForFunction(() => window.tower && JSON.parse(window.tower.ui_json()).sprites_loaded,
    undefined, { timeout: 45000 });
}

async function idle(page) {
  await page.waitForFunction(() => { const s = JSON.parse(window.tower.ui_json());
    return !s.animation && !s.presentation_remaining && !s.path_remaining;
  }, undefined, { timeout: 10000 });
}

async function touchDrag(cdp, from, to) {
  await cdp.send('Input.dispatchTouchEvent', { type: 'touchStart', touchPoints: [from] });
  await new Promise(resolve => setTimeout(resolve, 70));
  for (let step = 1; step <= 12; step++) {
    await cdp.send('Input.dispatchTouchEvent', { type: 'touchMove', touchPoints: [{
      x: from.x + (to.x - from.x) * step / 12,
      y: from.y + (to.y - from.y) * step / 12
    }] });
    await new Promise(resolve => setTimeout(resolve, 25));
  }
  await cdp.send('Input.dispatchTouchEvent', { type: 'touchEnd', touchPoints: [] });
}

async function activate(page, cdp, rect) {
  const point = center(rect);
  if (cdp) {
    await page.touchscreen.tap(point.x, point.y);
  } else {
    await page.mouse.click(point.x, point.y);
  }
  await page.waitForTimeout(200);
}

async function unchanged(page, expectedSave, expectedAction, description) {
  assert.deepEqual(await save(page), expectedSave, `${description}: game save stays unchanged`);
  assert.deepEqual((await state(page)).last_action, expectedAction, `${description}: no game action is dispatched`);
}

async function settleModal(page, viewportKey, ids) {
  let previous;
  let stableFrames = 0;
  for (let frame = 0; frame < 12; frame++) {
    const area = (await ui(page)).bounds[viewportKey];
    const point = center(area);
    // Force actual egui frames: newly opened areas need to measure their width,
    // scroll bars and final centered placement before a fixed-position check.
    await page.mouse.move(point.x + frame % 2, point.y);
    await page.waitForTimeout(120);
    const bounds = (await ui(page)).bounds;
    const current = JSON.stringify([bounds[viewportKey], ...ids.map(id => bounds[id])]);
    stableFrames = current === previous ? stableFrames + 1 : 0;
    previous = current;
    if (stableFrames >= 3) return;
  }
  assert.fail(`Modal geometry did not settle: ${previous}`);
}

async function revealPanel(page, cdp, viewport) {
  const classic = viewport.width >= 1060 || (viewport.width >= 700 && viewport.height <= 720
    && viewport.width > viewport.height * 1.25);
  const historyId = classic ? 'journal_header' : 'journal_expand';
  const wisdomId = classic ? 'item:wisdom_orb' : 'journal_wisdom';
  for (let attempt = 0; attempt < 12; attempt++) {
    const bounds = (await ui(page)).bounds;
    if (inside(bounds[historyId], viewport) && inside(bounds[wisdomId], viewport)) return bounds;
    if (cdp) {
      const grid = bounds.inventory_grid;
      const heading = { x: grid.x + grid.w / 2, y: grid.y - 38, w: 1, h: 1 };
      const start = inside(heading, viewport) && heading.y > 150
        ? { x: heading.x, y: heading.y }
        : { x: viewport.width / 2, y: viewport.height - 80 };
      await touchDrag(cdp, start, { x: start.x, y: Math.max(20, start.y - 450) });
    } else {
      await page.mouse.move(viewport.width - 45, viewport.height - 80);
      await page.mouse.wheel(0, 450);
    }
    await page.waitForTimeout(300);
  }
  assert.fail(`Journal buttons remain unreachable: ${JSON.stringify((await ui(page)).bounds)}`);
}

try {
  for (const viewport of [{ width: 1440, height: 1000 }, { width: 1360, height: 920 },
    { width: 390, height: 844 }, { width: 844, height: 390 }]) {
    if (process.env.TOS_JOURNAL_WIDTH && Number(process.env.TOS_JOURNAL_WIDTH) !== viewport.width) continue;
    for (const locale of ['en', 'zh-CN']) {
      const mobile = viewport.width < 500;
      const classic = viewport.width >= 1060 || (viewport.width >= 700 && viewport.height <= 720
        && viewport.width > viewport.height * 1.25);
      const historyId = classic ? 'journal_header' : 'journal_expand';
      const wisdomId = classic ? 'item:wisdom_orb' : 'journal_wisdom';
      const context = await browser.newContext({ viewport, hasTouch: mobile });
      const page = await context.newPage();
      const cdp = mobile ? await context.newCDPSession(page) : null;
      const errors = [];
      page.on('pageerror', error => errors.push(error.message));
      try {
        await page.goto(process.env.TOS_URL || 'http://127.0.0.1:8080');
        await ready(page);
        await page.evaluate(({ fixture, locale, log, clues }) => {
          window.tower.import_campaign(fixture);
          window.tower.set_language(locale);
          const saved = JSON.parse(window.tower.save_json());
          saved.log = log;
          saved.journal = clues;
          window.tower.load_save(JSON.stringify(saved));
        }, { fixture, locale, log, clues });
        await page.waitForTimeout(locale === 'zh-CN' ? 1600 : 500);
        await idle(page);
        assert.equal((await state(page)).log.length, 100);
        assert.equal((await state(page)).journal.length, 24);
        const beforeSave = await save(page);
        const beforeAction = (await state(page)).last_action;
        let bounds = await revealPanel(page, cdp, viewport);
        await unchanged(page, beforeSave, beforeAction, 'Reaching the compact Journal');
        const preview = Object.entries(bounds).filter(([id]) => id.startsWith('journal_preview_entry:'));
        if (classic) {
          assert.equal(preview.length, 2, 'Classic layout keeps two visible recent activity rows');
          assert(inside(bounds.journal_preview, viewport), 'Compact activity preview is visible');
          assert(bounds.journal_preview.h <= 65, 'Classic preview remains compact');
          assert(bounds['journal_preview_entry:99'].y + bounds['journal_preview_entry:99'].h
            < bounds['journal_preview_entry:98'].y, 'Recent entries have separate backgrounds and gaps');
          assert.equal((await ui(page)).visual_log.at(-1), log.at(-1), 'Activity receives the newest retained action');
          await activate(page, cdp, bounds['journal_preview_entry:99']);
          await page.waitForFunction(() => !!JSON.parse(window.tower.ui_json()).bounds.journal_history);
          await settleModal(page, 'journal_history_viewport', ['journal_history', 'journal_history_close', 'journal_history_heading']);
          assert.equal((await ui(page)).bounds.journal_history_viewport.entries, 100,
            'Activity status opens the complete retained log');
          await unchanged(page, beforeSave, beforeAction, 'Opening history from recent activity');
          await activate(page, cdp, (await ui(page)).bounds.journal_history_close);
          await page.waitForFunction(() => !JSON.parse(window.tower.ui_json()).bounds.journal_history);
          bounds = (await ui(page)).bounds;
        } else {
          assert.equal(preview.length, 3, 'Portrait preview shows three distinct recent rows');
          for (let index = 99; index > 97; index--) {
            const newer = bounds[`journal_preview_entry:${index}`];
            const older = bounds[`journal_preview_entry:${index - 1}`];
            assert(newer.y + newer.h < older.y, 'Compact log entries have separate row backgrounds and gaps');
          }
        }
        assert.equal(bounds.journal_history, undefined, 'Full log stays closed until expanded');
        assert.equal(bounds.journal_dialog, undefined, 'Wisdom hints stay closed until the item is used');
        await page.screenshot({ path: resolve(output, `journal-compact-${viewport.width}x${viewport.height}-${locale}.png`) });

        await activate(page, cdp, bounds[historyId]);
        await page.waitForFunction(() => !!JSON.parse(window.tower.ui_json()).bounds.journal_history);
        await settleModal(page, 'journal_history_viewport',
          ['journal_history', 'journal_history_close', 'journal_history_heading']);
        bounds = (await ui(page)).bounds;
        const top = bounds.journal_history_viewport;
        const closeBefore = structuredClone(bounds.journal_history_close);
        const headingBefore = structuredClone(bounds.journal_history_heading);
        assert(inside(bounds.journal_history, viewport), `Full log modal fits: ${JSON.stringify(bounds.journal_history)}`);
        assert(inside(closeBefore, viewport), 'Close is visible at the top of the history');
        assert(inside(headingBefore, viewport), 'History heading is visible');
        assert.equal(top.entries, 100, 'The full history includes all retained actions');
        assert.equal(Object.keys(bounds).filter(id => id.startsWith('journal_history_entry:')).length, 100,
          'Every retained action has its own rendered history row');
        assert(top.content_h > top.h, 'The full 100-entry history requires scrolling');
        assert(contained(bounds['journal_history_entry:99'], top), 'Newest retained action is initially visible');
        assert(bounds['journal_history_entry:99'].y + bounds['journal_history_entry:99'].h
          < bounds['journal_history_entry:98'].y, 'Full log entries have separated rows');
        await unchanged(page, beforeSave, beforeAction, 'Opening log history');

        for (const key of ['ArrowRight', 'ArrowUp', 'd', 'w']) await page.keyboard.press(key);
        await page.waitForTimeout(200);
        await unchanged(page, beforeSave, beforeAction, 'Movement keys while history is open');
        // A desktop board cell behind the modal must never route the hero. On
        // mobile the stacked board is above the viewport once this card is reached.
        const board = bounds.board;
        const behind = { x: board.x + board.w * 6.5 / board.width,
          y: board.y + board.h * 5.5 / board.height, w: 1, h: 1 };
        if (inside(behind, viewport)) {
          await activate(page, cdp, behind);
          await idle(page);
          await unchanged(page, beforeSave, beforeAction, 'Board click behind log history');
          bounds = (await ui(page)).bounds;
          if (!bounds.journal_history) {
            await activate(page, cdp, bounds[historyId]);
            await page.waitForFunction(() => !!JSON.parse(window.tower.ui_json()).bounds.journal_history);
            await settleModal(page, 'journal_history_viewport', ['journal_history', 'journal_history_close', 'journal_history_heading']);
          }
        }

        for (let attempt = 0; attempt < 30; attempt++) {
          bounds = (await ui(page)).bounds;
          if (contained(bounds['journal_history_entry:0'], bounds.journal_history_viewport)) break;
          const area = bounds.journal_history_viewport;
          if (cdp) {
            await touchDrag(cdp, { x: area.x + area.w / 2, y: area.y + area.h - 15 },
              { x: area.x + area.w / 2, y: area.y + 15 });
          } else {
            const point = center(area);
            await page.mouse.move(point.x, point.y);
            await page.mouse.wheel(0, 900);
          }
          await page.waitForTimeout(300);
          assert(inside((await ui(page)).bounds.journal_history_close, viewport),
            'Close remains visible while history scrolls');
        }
        bounds = (await ui(page)).bounds;
        const bottom = bounds.journal_history_viewport;
        assert(bottom.offset_y > top.offset_y, 'History itself scrolls');
        assert(contained(bounds['journal_history_entry:0'], bottom),
          `Oldest retained action is reachable: ${JSON.stringify(bottom)}`);
        assert.deepEqual(bounds.journal_history_close, closeBefore, 'History scrolling does not move Close');
        assert.deepEqual(bounds.journal_history_heading, headingBefore, 'History scrolling does not move its heading');
        await unchanged(page, beforeSave, beforeAction, 'Scrolling the full history');
        await page.screenshot({ path: resolve(output, `journal-history-bottom-${viewport.width}x${viewport.height}-${locale}.png`) });
        await activate(page, cdp, bounds.journal_history_close);
        await page.waitForFunction(() => !JSON.parse(window.tower.ui_json()).bounds.journal_history);
        await unchanged(page, beforeSave, beforeAction, 'Closing log history');

        if (mobile) {
          // Open the same modal from the header with the underlying board still
          // visible, rather than claiming that an offscreen board was tested.
          for (let attempt = 0; attempt < 12; attempt++) {
            bounds = (await ui(page)).bounds;
            if (inside(bounds.journal_header, viewport)) break;
            await touchDrag(cdp, { x: viewport.width / 2, y: 220 },
              { x: viewport.width / 2, y: viewport.height - 80 });
            await page.waitForTimeout(300);
          }
          bounds = (await ui(page)).bounds;
          assert(inside(bounds.journal_header, viewport), 'Mobile header can be reached by touch scrolling');
          await unchanged(page, beforeSave, beforeAction, 'Returning to the mobile header');
          await activate(page, cdp, bounds.journal_header);
          await page.waitForFunction(() => !!JSON.parse(window.tower.ui_json()).bounds.journal_history);
          bounds = (await ui(page)).bounds;
          const mobileBoard = bounds.board;
          const target = { x: mobileBoard.x + mobileBoard.w * 6.5 / mobileBoard.width,
            y: mobileBoard.y + mobileBoard.h * 5.5 / mobileBoard.height, w: 1, h: 1 };
          assert(inside(target, viewport), 'A mobile board cell behind the modal is on screen');
          await activate(page, cdp, target);
          await idle(page);
          await unchanged(page, beforeSave, beforeAction, 'Touching the mobile board behind history');
          bounds = (await ui(page)).bounds;
          if (bounds.journal_history) {
            await activate(page, cdp, bounds.journal_history_close);
            await page.waitForFunction(() => !JSON.parse(window.tower.ui_json()).bounds.journal_history);
          }
        }

        bounds = await revealPanel(page, cdp, viewport);
        await activate(page, cdp, bounds[wisdomId]);
        await page.waitForFunction(() => JSON.parse(window.tower.ui_json()).animation === 'journal'
          && !!JSON.parse(window.tower.ui_json()).bounds.journal_dialog);
        await settleModal(page, 'wisdom_journal_viewport', ['journal_dialog', 'journal_close']);
        const reading = await state(page);
        assert.deepEqual(reading.last_action.presentation, [{ type: 'journal', entries: reading.journal }],
          'The Wisdom shortcut dispatches the real reusable item action');
        assert.equal(reading.journal.length, 24);
        assert(reading.player.inventory.includes('wisdom_orb'));
        bounds = (await ui(page)).bounds;
        assert(inside(bounds.journal_dialog, viewport), 'Wisdom modal fits the viewport');
        assert(inside(bounds.journal_close, viewport), 'Wisdom Close remains reachable');
        const wisdomClose = structuredClone(bounds.journal_close);
        const wisdomSave = await save(page);
        assert.equal(bounds.wisdom_journal_viewport.entries, 24, 'Wisdom renders all remembered hints');
        assert.equal(Object.keys(bounds).filter(id => id.startsWith('journal_clue:')).length, 24,
          'Every remembered hint has its own rendered text');
        await page.screenshot({ path: resolve(output, `journal-wisdom-${viewport.width}x${viewport.height}-${locale}.png`) });
        for (let attempt = 0; attempt < 20; attempt++) {
          bounds = (await ui(page)).bounds;
          if (contained(bounds['journal_clue:23'], bounds.wisdom_journal_viewport)) break;
          const area = bounds.wisdom_journal_viewport;
          if (cdp) {
            await touchDrag(cdp, { x: area.x + area.w / 2, y: area.y + area.h - 15 },
              { x: area.x + area.w / 2, y: area.y + 15 });
          } else {
            const point = center(area);
            await page.mouse.move(point.x, point.y);
            await page.mouse.wheel(0, 900);
          }
          await page.waitForTimeout(300);
        }
        bounds = (await ui(page)).bounds;
        assert(contained(bounds['journal_clue:23'], bounds.wisdom_journal_viewport),
          'The final remembered hint is reachable by scrolling');
        assert.deepEqual(bounds.journal_close, wisdomClose, 'Wisdom Close stays fixed while hints scroll');
        await unchanged(page, wisdomSave, reading.last_action, 'Scrolling remembered Wisdom hints');
        await page.screenshot({ path: resolve(output, `journal-wisdom-bottom-${viewport.width}x${viewport.height}-${locale}.png`) });
        await activate(page, cdp, bounds.journal_close);
        await idle(page);
        assert.deepEqual((await state(page)).journal, reading.journal, 'Reading does not change remembered hints');
        assert((await state(page)).player.inventory.includes('wisdom_orb'), 'Reading does not consume Wisdom');

        await page.evaluate(() => {
          const saved = JSON.parse(window.tower.save_json());
          saved.player.inventory = [];
          window.tower.load_save(JSON.stringify(saved));
        });
        await page.waitForTimeout(300);
        assert.equal((await ui(page)).bounds.journal_wisdom, undefined, 'Hints require owning the Wisdom item');
        assert.equal((await ui(page)).bounds['item:wisdom_orb'], undefined, 'Unowned Wisdom has no inventory action');
        assert.deepEqual((await state(page)).journal, [], 'Unowned hints are not exposed to the player');
        assert.deepEqual(errors, [], 'The browser has no runtime errors');
        report.push({ viewport, locale, entries: 100, clues: 24, top, bottom });
        console.log(`PASS ${classic ? 'classic activity/toolbar' : 'portrait Journal'}, full100-entry history, modal input blocking and Wisdom: ${viewport.width}x${viewport.height} ${locale}`);
      } catch (error) {
        await page.screenshot({ path: resolve(output, `journal-layout-failure-${viewport.width}x${viewport.height}-${locale}.png`) });
        throw error;
      } finally {
        await context.close();
      }
    }
  }
  writeFileSync(resolve(output, 'journal-layout-report.json'), JSON.stringify(report, null, 2));
} finally {
  await browser.close();
}
