// Run against the built site. Requires Playwright on NODE_PATH; see docs/cross-platform.md.
const assert = require('node:assert/strict');
const fs = require('node:fs/promises');
const path = require('node:path');
const http = require('node:http');
const { chromium } = require('playwright');

async function checkPlayerLayout(page, name) {
    await page.waitForFunction(() => {
        const canvas = document.getElementById('canvas').getBoundingClientRect();
        const stage = document.getElementById('stage').getBoundingClientRect();
        return canvas.width > 0 && canvas.height > 0 &&
            Math.abs(canvas.width - stage.width) <= 1 && Math.abs(canvas.height - stage.height) <= 1 &&
            window.Module?.tswCanvasViewport && canvas.width === Module.canvas.width && canvas.height === Module.canvas.height;
    });
    const layout = await page.evaluate(() => {
        const bounds = id => {
            const box = document.getElementById(id).getBoundingClientRect();
            return { left: box.left, top: box.top, right: box.right, bottom: box.bottom,
                width: box.width, height: box.height };
        };
        return { width: innerWidth, height: innerHeight, scrollWidth: document.documentElement.scrollWidth,
            scrollHeight: document.documentElement.scrollHeight, canvas: bounds('canvas'),
            help: bounds('help-button'), game: Module.tswCanvasViewport };
    });
    assert.ok(layout.scrollWidth <= layout.width && layout.scrollHeight <= layout.height,
        name + ': the player must fit the viewport without page scrolling');
    for (const id of ['canvas', 'help']) {
        const box = layout[id];
        assert.ok(box.left >= 0 && box.top >= 0 && box.right <= layout.width + 1 && box.bottom <= layout.height + 1,
            name + ': ' + id + ' must remain on screen');
    }
    assert.ok(Math.abs(layout.game.width / layout.game.height - 800 / 558) < .01,
        name + ': canvas scaling must preserve the game aspect ratio');
    assert.ok(layout.help.width >= 44 && layout.help.height >= 44,
        name + ': player tools must have touch-sized targets');
    assert.ok(layout.help.right <= layout.canvas.left + layout.game.x ||
        layout.help.bottom <= layout.canvas.top + layout.game.y,
        name + ': player tools must not cover the game');
    if (await page.evaluate(() => Module.tswTouchDevice) && layout.canvas.width > layout.canvas.height) {
        assert.ok(layout.game.x + layout.game.width <= layout.canvas.width - 176 + 1,
            name + ': the right-hand pad must leave the entire game and HUD visible');
    }
}

async function mobileSmoke(browser, url, output) {
    const context = await browser.newContext({ viewport: { width: 915, height: 412 },
        isMobile: true, hasTouch: true, deviceScaleFactor: 2 });
    const page = await context.newPage();
    const client = await context.newCDPSession(page);
    const errors = [];
    page.on('pageerror', error => errors.push(String(error)));
    async function ready() {
        await page.waitForFunction(() => window.Module?.FS && document.getElementById('loading').hidden,
            null, { timeout: 60000 });
        assert.equal(await page.evaluate(() => Module.tswTouchDevice), true);
    }
    async function start(x, y) {
        const box = await page.locator('#canvas').boundingBox();
        const game = await page.evaluate(() => Module.tswCanvasViewport);
        await startScreen(box.x + game.x + x * game.width / 800, box.y + game.y + y * game.height / 558);
    }
    async function startScreen(x, y) {
        await client.send('Input.dispatchTouchEvent', { type: 'touchStart',
            touchPoints: [{ x, y, id: 1 }] });
    }
    async function end(type = 'touchEnd') {
        await client.send('Input.dispatchTouchEvent', { type, touchPoints: [] });
    }
    async function tap(x, y) { await start(x, y); await page.waitForTimeout(60); await end(); }
    async function padStart(direction) {
        const box = await page.locator('#canvas').boundingBox();
        const x = box.x + box.width - ({ Left: 144, Right: 40 }[direction] || 92);
        const y = box.y + box.height - ({ Up: 144, Down: 40 }[direction] || 92);
        await startScreen(x, y);
    }
    async function padTap(direction) { await padStart(direction); await page.waitForTimeout(60); await end(); }
    async function position() {
        await page.waitForTimeout(180);
        await page.keyboard.press('F5', { delay: 100 });
        return page.evaluate(() => {
            const bytes = Module.tswStorage.read('quick.save');
            const view = new DataView(bytes.buffer, bytes.byteOffset, bytes.byteLength);
            return [view.getInt32(6297, true), view.getInt32(6301, true)];
        });
    }
    async function toggle() {
        await tap(100, 14); // Options
        await tap(316, 114); // Controls tab
        await tap(400, 216); // Touch controls
        await tap(636, 484); // Done
    }
    async function fixture(kind) {
        await page.evaluate(kind => {
            // Original save record; keep valid checksums and restore through the real UI.
            const bytes = Module.tswStorage.read('quick.save').slice();
            const view = new DataView(bytes.buffer, bytes.byteOffset, bytes.byteLength);
            const hero = 6273;
            const set = (offset, value) => view.setInt32(hero + offset, value, true);
            set(0, 1000); set(8, 100); set(12, 100); set(16, 1);
            set(24, 5); set(28, kind === 'shop' ? 5 : 10);
            if (kind === 'shop') bytes[123 + 2 + 4 * 11 + 5] = 16; // Altar
            else {
                set(72, 1); // Orb of Wisdom
                for (const offset of [272, 276, 220, 224, 228, 236, 280, 288, 292, 296, 300, 244,
                    304, 308, 312, 248, 316, 252, 320, 324, 256, 328, 260, 332]) set(offset, 2);
            }
            let sum = 0, alternating = 0;
            for (let offset = 0; offset < 656; offset += 4) {
                const word = view.getUint32(hero + offset, true);
                sum = (sum + word) >>> 0;
                alternating = (alternating + (offset % 8 ? -word : word)) >>> 0;
            }
            set(656, sum); set(660, alternating);
            Module.FS.writeFile('/Savedat/quick.save', bytes);
        }, kind);
        await page.keyboard.press('F9', { delay: 100 });
        await page.waitForTimeout(200);
    }
    async function dialogueSnapshot(header = false) {
        const box = await page.locator('#canvas').boundingBox();
        const game = await page.evaluate(() => Module.tswCanvasViewport);
        return page.screenshot({ clip: { x: box.x + game.x + 212 * game.width / 800,
            y: box.y + game.y + (header ? 130 : 178) * game.height / 558,
            width: 376 * game.width / 800, height: (header ? 24 : 188) * game.height / 558 } });
    }
    try {
        await page.goto(url, { waitUntil: 'domcontentloaded' });
        await ready();
        await checkPlayerLayout(page, 'Mobile landscape');
        await tap(130, 70); // New game, using real touch input.
        assert.deepEqual(await position(), [5, 10]);
        await padTap('Left');
        assert.deepEqual(await position(), [4, 10], 'A pad tap must move exactly one tile');
        await padStart('Right'); // Held long enough to cross both free cells.
        await page.waitForTimeout(450);
        await end();
        assert.deepEqual(await position(), [6, 10], 'Holding an arrow must repeat');
        assert.deepEqual(await position(), [6, 10], 'Lifting the finger must stop movement');
        await padStart('Left');
        await page.waitForTimeout(60);
        await page.evaluate(() => window.dispatchEvent(new Event('blur')));
        await page.waitForTimeout(350);
        await end();
        assert.deepEqual(await position(), [5, 10], 'Page blur must cancel a held direction');
        await padStart('Left');
        await page.waitForTimeout(60);
        await end('touchCancel');
        assert.deepEqual(await position(), [4, 10], 'Touch cancellation must stop repeats');
        await page.screenshot({ path: path.join(output, 'mobile-controls.png') });
        await page.locator('#help-button').tap();
        assert.equal(await page.locator('#help-panel').isVisible(), true);
        await page.keyboard.press('ArrowRight', { delay: 350 });
        await page.screenshot({ path: path.join(output, 'mobile-help.png') });
        await page.locator('#save-file').selectOption('quick.save');
        const exportPromise = page.waitForEvent('download');
        await page.locator('#export').tap();
        assert.equal((await exportPromise).suggestedFilename(), 'quick.save', 'Mobile saves must be exportable');
        await checkPlayerLayout(page, 'Mobile with help scrolled to exports');
        const closeBox = await page.locator('#close-help').boundingBox();
        assert.ok(closeBox.y >= 0 && closeBox.y + closeBox.height <= 412,
            'Done must remain on screen when the help panel scrolls');
        await page.locator('#close-help').tap();
        await page.waitForFunction(() => document.activeElement.id === 'canvas');
        assert.deepEqual(await position(), [4, 10], 'Help-panel keys must not move the hero');
        await page.locator('#help-button').tap();
        await page.keyboard.press('Escape');
        assert.equal(await page.locator('#help-panel').isVisible(), false, 'Escape must dismiss help');
        await toggle();
        assert.equal(await page.evaluate(() => JSON.parse(new TextDecoder().decode(
            Module.tswStorage.read('settings.json'))).touch_controls), false);
        await page.waitForFunction(() => document.getElementById('storage').textContent === 'Saved in this browser');
        await page.reload();
        await ready();
        await tap(130, 70);
        await padTap('Left');
        assert.deepEqual(await position(), [5, 10], 'A saved override must disable the automatic mobile pad');
        await toggle();
        await padTap('Left');
        assert.deepEqual(await position(), [4, 10], 'The pad can be enabled again');
        await page.setViewportSize({ width: 393, height: 851 });
        await checkPlayerLayout(page, 'Mobile portrait');
        await padTap('Right');
        assert.deepEqual(await position(), [5, 10], 'Portrait resizing must preserve touch coordinates');
        await page.screenshot({ path: path.join(output, 'mobile-portrait.png') });
        for (const viewport of [{ width: 568, height: 320 }, { width: 667, height: 375 },
            { width: 844, height: 390 }, { width: 320, height: 568 }]) {
            await page.setViewportSize(viewport);
            await checkPlayerLayout(page, 'Mobile ' + viewport.width + 'x' + viewport.height);
        }
        await page.setViewportSize({ width: 915, height: 412 });
        await checkPlayerLayout(page, 'Mobile rotated back to landscape');
        await fixture('wisdom');
        await tap(37, 286); // Inspect the Orb of Wisdom in the unchanged inventory.
        await tap(300, 374); // Use it to open a genuinely long conversation.
        await page.waitForTimeout(180);
        const firstText = await dialogueSnapshot();
        const heading = await dialogueSnapshot(true);
        await start(300, 300);
        const box = await page.locator('#canvas').boundingBox();
        const game = await page.evaluate(() => Module.tswCanvasViewport);
        await client.send('Input.dispatchTouchEvent', { type: 'touchMove', touchPoints: [{
            x: box.x + game.x + 300 * game.width / 800,
            y: box.y + game.y + 190 * game.height / 558, id: 1 }] });
        await page.waitForTimeout(100);
        await end();
        await page.waitForTimeout(100);
        const scrolledText = await dialogueSnapshot();
        assert.notDeepEqual(scrolledText, firstText, 'Dragging must scroll long conversation text');
        assert.deepEqual(await dialogueSnapshot(true), heading, 'Dragging must keep the conversation open');
        await page.screenshot({ path: path.join(output, 'mobile-dialogue.png') });
        await start(300, 210);
        await page.waitForTimeout(60);
        await end('touchCancel');
        assert.deepEqual(await dialogueSnapshot(), scrolledText, 'A cancelled touch must not continue dialogue');
        await tap(300, 210);
        await page.waitForTimeout(100);
        assert.notDeepEqual(await dialogueSnapshot(), scrolledText, 'A conversation tap must continue on release');
        assert.notDeepEqual(await dialogueSnapshot(true), heading, 'A conversation tap must dismiss the completed passage');
        await fixture('shop');
        await padTap('Up');
        await page.waitForTimeout(250);
        const shop = await dialogueSnapshot();
        await tap(300, 210);
        await startScreen(box.x + box.width - 92, box.y + box.height - 92); // Former generic OK
        await page.waitForTimeout(60);
        await end();
        assert.deepEqual(await dialogueSnapshot(), shop, 'Shop prose and the former OK must leave the offer open');
        await tap(532, 433); // Explicit cancel
        await position();
        const gold = () => page.evaluate(() => {
            const bytes = Module.tswStorage.read('quick.save');
            return new DataView(bytes.buffer, bytes.byteOffset, bytes.byteLength).getInt32(6285, true);
        });
        assert.equal(await gold(), 100, 'Shop prose and the former OK cannot spend gold');
        await padTap('Up');
        await page.waitForTimeout(180);
        await page.screenshot({ path: path.join(output, 'mobile-shop.png') });
        await tap(260, 403); // Explicit purchase
        await page.waitForTimeout(180);
        await tap(532, 433); // Close a remaining offer, if any.
        await position();
        assert.ok(await gold() < 100, 'The explicit shop choice must still purchase');
        assert.deepEqual(errors, []);
        console.log('PASS: mobile movement, dialogue tap/drag/cancel, explicit shop choices, Menu isolation, saved override and viewport fit');
    } finally {
        await page.screenshot({ path: path.join(output, 'mobile-latest.png') }).catch(() => {});
        await context.close();
    }
}

async function languageSmoke(browser, url, output) {
    const context = await browser.newContext({ viewport: { width: 1000, height: 800 } });
    const page = await context.newPage();
    const requests = [], errors = [];
    let failChinese = true;
    page.on('pageerror', error => errors.push(String(error)));
    await page.route('**/fonts/*.otf', async route => {
        requests.push(route.request().url());
        await new Promise(resolve => setTimeout(resolve, 450));
        if (failChinese && /\/zh-/.test(route.request().url())) {
            failChinese = false;
            await route.abort();
        } else await route.continue();
    });
    async function ready() {
        await page.waitForFunction(() => window.Module?.FS && document.getElementById('loading').hidden);
        await page.locator('#canvas').focus();
    }
    async function click(x, y) {
        const box = await page.locator('#canvas').boundingBox();
        const view = await page.evaluate(() => Module.tswCanvasViewport);
        await page.mouse.click(box.x + view.x + x * view.width / 800, box.y + view.y + y * view.height / 558, { delay: 80 });
        await page.waitForTimeout(90);
    }
    async function fontReady(family) {
        await page.waitForFunction(family => Module.FS.analyzePath('/fonts/' + family + '.otf').exists, family);
        await page.waitForFunction(() => document.getElementById('font-notice').hidden);
        await page.waitForTimeout(120); // Let the renderer create its atlas from the downloaded bytes.
    }
    try {
        await page.goto(url);
        await ready();
        assert.equal(requests.length, 0, 'English startup must not request a full CJK font');
        assert.equal(await page.evaluate(() => Module.FS.analyzePath('/assets/fonts/labels.otf').exists), true);
        assert.equal(await page.evaluate(() => Module.FS.analyzePath('/assets/fonts/cjk.ttf').exists), false);
        await page.keyboard.press('Enter', { delay: 100 });
        await click(100, 14);
        await page.screenshot({ path: path.join(output, 'settings-game.png') });
        await click(316, 114);
        await page.screenshot({ path: path.join(output, 'settings-controls.png') });
        await click(484, 114);
        await click(400, 216);
        assert.equal(await page.evaluate(() => JSON.parse(new TextDecoder().decode(
            Module.tswStorage.read('settings.json'))).recording), true, 'Recording belongs to Replay');
        await page.screenshot({ path: path.join(output, 'settings-replay.png') });
        await click(652, 114);
        await page.screenshot({ path: path.join(output, 'settings-language.png') });
        assert.equal(requests.length, 0, 'Native language labels must render without a full font download');
        await click(400, 350); // Chinese from Japanese.
        await page.locator('#retry-font').waitFor({ state: 'visible' });
        await page.screenshot({ path: path.join(output, 'font-retry.png') });
        assert.match(await page.locator('#font-message').textContent(), /Using English/);
        await page.locator('#retry-font').click();
        await fontReady('zh');
        await page.screenshot({ path: path.join(output, 'settings-chinese.png') });
        await click(400, 406); // The other Chinese catalog shares the same font.
        assert.equal(requests.length, 2, 'Chinese catalogs must share one successful download');
        await click(400, 238); // Japanese.
        await page.locator('#font-notice').waitFor({ state: 'visible' });
        await fontReady('ja');
        await page.screenshot({ path: path.join(output, 'settings-japanese.png') });
        await click(400, 182); // English.
        await click(400, 238); // Cached Japanese.
        assert.equal(requests.length, 3, 'Returning to a downloaded language must reuse its font');
        await page.waitForFunction(() => document.getElementById('storage').textContent === 'Saved in this browser');
        await page.reload();
        await ready();
        await fontReady('ja');
        assert.equal(await page.evaluate(() => JSON.parse(new TextDecoder().decode(
            Module.tswStorage.read('settings.json'))).language), 'ja');
        await page.screenshot({ path: path.join(output, 'startup-japanese.png') });
        assert.deepEqual(errors, []);
        console.log('PASS: settings tabs, native language labels, lazy CJK download, failure/retry, font reuse and saved-language startup');
    } finally {
        await page.screenshot({ path: path.join(output, 'language-latest.png') }).catch(() => {});
        await context.close();
    }
}

async function main() {
    const site = process.argv[2] || 'build/cpp/web/site';
    let server;
    let url = site;
    if (!/^https?:\/\//.test(site)) {
        const root = path.resolve(site);
        server = http.createServer(async (request, response) => {
            try {
                const pathname = decodeURIComponent(new URL(request.url, 'http://localhost').pathname);
                const filename = path.resolve(root, '.' + (pathname === '/' ? '/index.html' : pathname));
                if (!filename.startsWith(root + path.sep)) throw new Error('Invalid path');
                const mime = { '.html': 'text/html', '.js': 'application/javascript', '.wasm': 'application/wasm' };
                const bytes = await fs.readFile(filename);
                response.writeHead(200, { 'Content-Type': mime[path.extname(filename)] || 'application/octet-stream', 'Cache-Control': 'no-store' });
                response.end(bytes);
            } catch {
                response.writeHead(404); response.end();
            }
        });
        await new Promise(resolve => server.listen(0, '127.0.0.1', resolve));
        url = 'http://127.0.0.1:' + server.address().port;
    }
    const output = path.resolve(process.argv[3] || 'build/browser-tests');
    await fs.mkdir(output, { recursive: true });
    const browser = await chromium.launch({ headless: true, args: ['--enable-unsafe-swiftshader'] }).catch(async error => {
        if (server) await new Promise(resolve => server.close(resolve));
        throw error;
    });
    const context = await browser.newContext({ viewport: { width: 1000, height: 1000 }, acceptDownloads: true });
    const page = await context.newPage();
    await page.route('**/index.data', async route => {
        await new Promise(resolve => setTimeout(resolve, 700));
        await route.continue();
    });
    const errors = [];
    page.on('pageerror', error => { errors.push(String(error)); console.error('Browser error:', error); });
    page.on('console', message => { if (message.type() === 'error') console.error(message.text()); });
    async function ready() {
        await page.waitForFunction(() => window.Module?.FS && !document.getElementById('retry').disabled, null, { timeout: 60000 });
        await page.locator('#canvas').focus();
    }
    async function key(name) { await page.keyboard.press(name, { delay: 100 }); }
    try {
        console.log('Opening', url);
        await page.goto(url, { waitUntil: 'domcontentloaded' });
        assert.equal(await page.title(), 'Tower of the Sorcerer');
        assert.equal(await page.locator('#loading').isVisible(), true, 'Loading overlay must cover the canvas');
        assert.equal(await page.locator('.spinner').isVisible(), true, 'Loading animation must be visible');
        await page.screenshot({ path: path.join(output, 'loading.png') });
        console.log('Game page loaded');
        await ready();
        await page.waitForFunction(() => document.getElementById('loading').hidden);
        await checkPlayerLayout(page, 'Desktop');
        assert.equal(await page.evaluate(() => Module.FS.analyzePath('/assets/music.sfo').exists), true);
        assert.equal(await page.evaluate(() => Module.tswTouchDevice), false, 'Desktop input must not auto-enable the pad');
        await page.screenshot({ path: path.join(output, 'startup.png') });
        await key('Enter');
        await key('F5');
        await page.waitForFunction(() => Module.FS.analyzePath('/Savedat/quick.save').exists);
        await page.waitForFunction(() => document.getElementById('storage').textContent === 'Saved in this browser');
        const original = await page.evaluate(() => Array.from(Module.tswStorage.read('quick.save')));
        assert.equal(original.length, 6957, 'Original-format save must retain its exact byte size');
        const history = await page.evaluate(() => Array.from(Module.tswStorage.read('quick.save.achievements.json')));
        await page.screenshot({ path: path.join(output, 'game.png') });
        await page.reload();
        await ready();
        assert.deepEqual(await page.evaluate(() => Array.from(Module.tswStorage.read('quick.save'))), original);
        assert.deepEqual(await page.evaluate(() => Array.from(Module.tswStorage.read('quick.save.achievements.json'))), history);
        await page.locator('#help-button').click();
        await page.locator('#save-file').selectOption('quick.save');
        const downloadPromise = page.waitForEvent('download');
        await page.locator('#export').click();
        const download = await downloadPromise;
        assert.equal(download.suggestedFilename(), 'quick.save');
        const destination = path.join(output, 'exported-quick.save');
        await download.saveAs(destination);
        assert.deepEqual(await fs.readFile(destination), Buffer.from(original));
        await page.locator('#close-help').click();
        // Storage trouble remains discoverable even while help is closed.
        await page.evaluate(() => window.dispatchEvent(new CustomEvent('tsw-storage', {
            detail: { message: 'Browser storage unavailable. Saves are temporary; export them before leaving.', error: true }
        })));
        assert.equal(await page.locator('#save-warning').isVisible(), true);
        await page.locator('#help-button').click();
        assert.equal(await page.locator('#retry').isVisible(), true);
        assert.match(await page.locator('#storage').textContent(), /temporary/);
        await page.locator('#close-help').click();
        await page.evaluate(() => window.dispatchEvent(new CustomEvent('tsw-storage', {
            detail: { message: Module.tswStorageMessage, error: false }
        })));
        assert.equal(await page.locator('#save-warning').isVisible(), false);
        await page.locator('#help-button').click();
        await page.locator('#fullscreen').click();
        await page.waitForFunction(() => document.fullscreenElement?.id === 'game');
        assert.equal(await page.locator('#help-panel').isVisible(), true, 'Menu stays accessible when entering fullscreen');
        await page.locator('#close-help').click();
        await checkPlayerLayout(page, 'Fullscreen');
        await page.locator('#help-button').click();
        assert.equal(await page.locator('#help-panel').isVisible(), true, 'Help must work inside fullscreen');
        await page.locator('#fullscreen').click();
        await page.waitForFunction(() => !document.fullscreenElement);
        await page.locator('#close-help').click();
        await checkPlayerLayout(page, 'Exited fullscreen');
        // Load through the actual game UI after hydration, then save again to exercise backups.
        await page.locator('#canvas').focus();
        await key('F7');
        await key('F9');
        await key('F5');
        await page.waitForFunction(() => Module.FS.analyzePath('/Savedat/quick.save.bak').exists);
        await page.waitForFunction(() => document.getElementById('storage').textContent === 'Saved in this browser');
        assert.deepEqual(await page.evaluate(() => Array.from(Module.tswStorage.read('quick.save.bak'))), original);
        await page.reload();
        await ready();
        assert.deepEqual(await page.evaluate(() => Array.from(Module.tswStorage.read('quick.save.bak'))), original);
        assert.deepEqual(errors, [], 'Game must not report uncaught browser errors');
        console.log('PASS: game startup, native save, IndexedDB reload, companion history, original-format export, load and backup');
        await mobileSmoke(browser, url, output);
        await languageSmoke(browser, url, output);
    } finally {
        console.log('Final page status:', await page.locator('body').innerText().catch(() => 'Page unavailable'));
        await page.screenshot({ path: path.join(output, 'latest.png') }).catch(() => {});
        await browser.close();
        if (server) await new Promise(resolve => server.close(resolve));
    }
}
main().catch(error => { console.error(error); process.exitCode = 1; });
