// Run against the built site. Requires Playwright on NODE_PATH; see docs/cross-platform.md.
const assert = require('node:assert/strict');
const fs = require('node:fs/promises');
const path = require('node:path');
const http = require('node:http');
const { chromium } = require('playwright');

async function mobileSmoke(browser, url, output) {
    const context = await browser.newContext({ viewport: { width: 915, height: 412 },
        isMobile: true, hasTouch: true, deviceScaleFactor: 2 });
    const page = await context.newPage();
    const client = await context.newCDPSession(page);
    const errors = [];
    page.on('pageerror', error => errors.push(String(error)));
    async function ready() {
        await page.waitForFunction(() => window.Module?.FS && !document.getElementById('retry').disabled,
            null, { timeout: 60000 });
        assert.equal(await page.evaluate(() => Module.tswTouchDevice), true);
    }
    async function start(x, y) {
        const box = await page.locator('#canvas').boundingBox();
        await client.send('Input.dispatchTouchEvent', { type: 'touchStart',
            touchPoints: [{ x: box.x + x * box.width / 800, y: box.y + y * box.height / 558, id: 1 }] });
    }
    async function end(type = 'touchEnd') {
        await client.send('Input.dispatchTouchEvent', { type, touchPoints: [] });
    }
    async function tap(x, y) { await start(x, y); await page.waitForTimeout(60); await end(); }
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
        await tap(611, 469); // Touch controls
        await tap(268, 502); // Done
    }
    try {
        await page.goto(url, { waitUntil: 'domcontentloaded' });
        await ready();
        await tap(130, 70); // New game, using real touch input.
        assert.deepEqual(await position(), [5, 10]);
        await tap(673, 447); // Left
        assert.deepEqual(await position(), [4, 10], 'A pad tap must move exactly one tile');
        await start(769, 447); // Right, held long enough to cross both free cells.
        await page.waitForTimeout(450);
        await end();
        assert.deepEqual(await position(), [6, 10], 'Holding an arrow must repeat');
        assert.deepEqual(await position(), [6, 10], 'Lifting the finger must stop movement');
        await start(673, 447);
        await page.waitForTimeout(60);
        await page.evaluate(() => window.dispatchEvent(new Event('blur')));
        await page.waitForTimeout(350);
        await end();
        assert.deepEqual(await position(), [5, 10], 'Page blur must cancel a held direction');
        await start(673, 447);
        await page.waitForTimeout(60);
        await end('touchCancel');
        assert.deepEqual(await position(), [4, 10], 'Touch cancellation must stop repeats');
        await page.screenshot({ path: path.join(output, 'mobile-controls.png') });
        await toggle();
        assert.equal(await page.evaluate(() => JSON.parse(new TextDecoder().decode(
            Module.tswStorage.read('settings.json'))).touch_controls), false);
        await page.waitForFunction(() => document.getElementById('storage').textContent === 'Saved in this browser');
        await page.reload();
        await ready();
        await tap(130, 70);
        await tap(673, 447);
        assert.deepEqual(await position(), [5, 10], 'A saved override must disable the automatic mobile pad');
        await toggle();
        await tap(673, 447);
        assert.deepEqual(await position(), [4, 10], 'The pad can be enabled again');
        await page.setViewportSize({ width: 393, height: 851 });
        await page.waitForTimeout(150);
        await tap(769, 447);
        assert.deepEqual(await position(), [5, 10], 'Portrait resizing must preserve touch coordinates');
        await page.screenshot({ path: path.join(output, 'mobile-portrait.png') });
        assert.deepEqual(errors, []);
        console.log('PASS: mobile detection, pad tap/hold/release, blur/cancel, saved override and portrait resize');
    } finally {
        await page.screenshot({ path: path.join(output, 'mobile-latest.png') }).catch(() => {});
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
        console.log('Game page loaded');
        await ready();
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
        await page.locator('#save-file').selectOption('quick.save');
        const downloadPromise = page.waitForEvent('download');
        await page.locator('#export').click();
        const download = await downloadPromise;
        assert.equal(download.suggestedFilename(), 'quick.save');
        const destination = path.join(output, 'exported-quick.save');
        await download.saveAs(destination);
        assert.deepEqual(await fs.readFile(destination), Buffer.from(original));
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
    } finally {
        console.log('Final page status:', await page.locator('body').innerText().catch(() => 'Page unavailable'));
        await page.screenshot({ path: path.join(output, 'latest.png') }).catch(() => {});
        await browser.close();
        if (server) await new Promise(resolve => server.close(resolve));
    }
}
main().catch(error => { console.error(error); process.exitCode = 1; });
