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
            window.Module?.tswCanvasViewport &&
            Math.round(canvas.width * devicePixelRatio) === Module.canvas.width &&
            Math.round(canvas.height * devicePixelRatio) === Module.canvas.height;
    });
    const layout = await page.evaluate(() => {
        const bounds = id => {
            const box = document.getElementById(id).getBoundingClientRect();
            return { left: box.left, top: box.top, right: box.right, bottom: box.bottom,
                width: box.width, height: box.height };
        };
        return { width: innerWidth, height: innerHeight, scrollWidth: document.documentElement.scrollWidth,
            scrollHeight: document.documentElement.scrollHeight, canvas: bounds('canvas'),
            help: bounds('help-button'), fullscreen: bounds('fullscreen'), game: Module.tswCanvasViewport };
    });
    assert.ok(layout.scrollWidth <= layout.width && layout.scrollHeight <= layout.height,
        name + ': the player must fit the viewport without page scrolling');
    for (const id of ['canvas', 'help', 'fullscreen']) {
        const box = layout[id];
        assert.ok(box.left >= 0 && box.top >= 0 && box.right <= layout.width + 1 && box.bottom <= layout.height + 1,
            name + ': ' + id + ' must remain on screen');
    }
    assert.ok(Math.abs(layout.game.width / layout.game.height - 800 / 558) < .01,
        name + ': canvas scaling must preserve the game aspect ratio');
    const toolsAvailable = !await page.locator('#help-panel').evaluate(panel => panel.open);
    for (const id of ['help', 'fullscreen']) {
        const box = layout[id];
        assert.ok(box.width >= 44 && box.height >= 44,
            name + ': ' + id + ' must have a touch-sized target');
        assert.ok(box.right <= layout.canvas.left + layout.game.x ||
            box.bottom <= layout.canvas.top + layout.game.y,
            name + ': ' + id + ' must not cover the game');
        if (toolsAvailable) {
            assert.equal(await page.evaluate(({ x, y, id }) => document.elementFromPoint(x, y)?.closest('button')?.id === id,
                { x: box.left + box.width / 2, y: box.top + box.height / 2,
                    id: id === 'help' ? 'help-button' : id }), true,
                name + ': ' + id + ' must be reachable');
        }
    }
    assert.equal(await page.locator('#fullscreen').evaluate(button => getComputedStyle(button).backgroundColor),
        'rgba(0, 0, 0, 0)', name + ': fullscreen control must have a transparent background at rest');
    if (await page.evaluate(() => Module.tswTouchDevice) && layout.canvas.width > layout.canvas.height) {
        assert.ok(layout.game.x + layout.game.width <= layout.canvas.width - 176 + 1,
            name + ': the right-hand pad must leave the entire game and HUD visible');
    }
}

async function checkSmallText(page, name) {
    const screenshot = await page.screenshot();
    const pixels = await page.evaluate(async png => {
        const image = new Image();
        image.src = 'data:image/png;base64,' + png;
        await image.decode();
        const copy = document.createElement('canvas');
        copy.width = image.width; copy.height = image.height;
        const context = copy.getContext('2d');
        context.drawImage(image, 0, 0);
        const data = context.getImageData(0, 0, copy.width, copy.height).data;
        const bounds = Module.canvas.getBoundingClientRect(), game = Module.tswCanvasViewport;
        const sx = game.width * devicePixelRatio / 800, sy = game.height * devicePixelRatio / 558;
        // The small Game button has a one-logical-pixel outline on all four sides.
        const x = Math.round((bounds.x + game.x) * devicePixelRatio) + Math.round(6 * sx);
        const y = Math.round((bounds.y + game.y) * devicePixelRatio) + Math.round(3 * sy);
        const right = Math.round((bounds.x + game.x) * devicePixelRatio) + Math.round(64 * sx) - 1;
        const bottom = Math.round((bounds.y + game.y) * devicePixelRatio) + Math.round(25 * sy) - 1;
        const color = (x, y) => Array.from(data.slice(4 * (y * copy.width + x), 4 * (y * copy.width + x) + 3));
        const border = (x, y) => color(x, y).every((c, i) => Math.abs(c - [168, 145, 118][i]) <= 2);
        const sides = [[], [], [], []];
        for (let px = x; px <= right; ++px) {
            sides[0].push(border(px, y)); sides[1].push(border(px, bottom));
        }
        for (let py = y; py <= bottom; ++py) {
            sides[2].push(border(x, py)); sides[3].push(border(right, py));
        }
        let ink = 0;
        const shades = new Set();
        for (let py = y + 1; py < bottom; ++py) for (let px = x + 1; px < right; ++px) {
            const [r, g, b] = color(px, py);
            // At a 320px, 1x viewport, antialiased glyphs can cover less than one
            // full pixel per stroke. Require contrast, rather than opaque ink.
            if (r > 130 && g > 120 && b > 110) ++ink;
            if (r > 100 && g > 100 && b > 100) shades.add([r, g, b].join(','));
        }
        return { sides: sides.map(side => side.filter(Boolean).length / side.length), ink, shades: shades.size };
    }, screenshot.toString('base64'));
    assert.ok(pixels.sides.every(coverage => coverage >= .98), name + ': every box edge must stay visible: ' + JSON.stringify(pixels));
    assert.ok(pixels.ink >= 5 && pixels.shades >= 8,
        name + ': small English text must retain visible, antialiased glyphs: ' + JSON.stringify(pixels));
}

async function fullscreenSmoke(browser, url, output) {
    for (const [name, viewport, density, mobile] of [
        ['desktop-hidpi', { width: 1000, height: 800 }, 1.25, false],
        ['phone-small', { width: 320, height: 568 }, 1, true],
        ['phone-portrait', { width: 393, height: 851 }, 3, true],
        ['phone-landscape-compact', { width: 667, height: 375 }, 2, true],
        ['phone-landscape', { width: 915, height: 412 }, 2, true]
    ]) {
        const context = await browser.newContext({ viewport, deviceScaleFactor: density, isMobile: mobile, hasTouch: mobile });
        const page = await context.newPage();
        const errors = [];
        page.on('pageerror', error => errors.push(String(error)));
        // Emulation cannot rotate hardware; verify requests and cleanup independently
        // from viewport changes, and exercise both rejected and absent orientation APIs.
        await page.addInitScript(() => {
            window.orientationCalls = [];
            Object.defineProperty(screen.orientation, 'lock', { configurable: true, value: async mode => {
                orientationCalls.push([mode, document.fullscreenElement?.id]);
            } });
            Object.defineProperty(screen.orientation, 'unlock', { value: () => orientationCalls.push(['unlock']) });
        });
        try {
            await page.goto(url);
            await page.waitForFunction(() => document.getElementById('loading').hidden, null, { timeout: 60000 });
            await page.keyboard.press('Enter', { delay: 100 });
            await page.keyboard.press('q', { delay: 100 });
            await checkPlayerLayout(page, name);
            await checkSmallText(page, name);
            await page.locator('#fullscreen').click();
            await page.waitForFunction(() => document.fullscreenElement?.id === 'game' &&
                document.getElementById('fullscreen').getAttribute('aria-pressed') === 'true');
            assert.equal(await page.locator('#help-panel').isVisible(), false, 'Fullscreen needs no menu visit');
            assert.equal(await page.locator('#fullscreen').getAttribute('aria-label'), 'Exit full screen');
            assert.deepEqual(await page.evaluate(() => orientationCalls), mobile ? [['landscape', 'game']] : [],
                'Only touch devices should request landscape, after fullscreen entry');
            await page.mouse.move(viewport.width / 2, viewport.height / 2);
            await checkPlayerLayout(page, name + ' fullscreen');
            await checkSmallText(page, name + ' fullscreen');
            await page.screenshot({ path: path.join(output, name + '-fullscreen.png') });
            if (mobile) {
                const client = await context.newCDPSession(page);
                const box = await page.locator('#canvas').boundingBox();
                await client.send('Input.dispatchTouchEvent', { type: 'touchStart', touchPoints: [{
                    x: box.x + box.width - 144, y: box.y + box.height - 92, id: 1 }] });
                await page.waitForTimeout(60);
                await client.send('Input.dispatchTouchEvent', { type: 'touchEnd', touchPoints: [] });
                await page.waitForTimeout(180);
                await page.keyboard.press('q', { delay: 100 });
                assert.equal(await page.evaluate(() => {
                    const bytes = Module.tswStorage.read('quick.save');
                    return new DataView(bytes.buffer, bytes.byteOffset, bytes.byteLength).getInt32(6297, true);
                }), 4, 'Fullscreen must retain CSS-sized touch targets and correct input coordinates');
                if (name === 'phone-landscape') {
                    // Chromium disallows resizing a fullscreen native window. Device
                    // metrics emulate a phone rotating without resizing that window.
                    await client.send('Emulation.setDeviceMetricsOverride', { width: 393, height: 851,
                        deviceScaleFactor: density, mobile: true,
                        screenOrientation: { type: 'portraitPrimary', angle: 0 } });
                    await checkPlayerLayout(page, 'Fullscreen rotated to portrait');
                    await client.send('Emulation.setDeviceMetricsOverride', { ...viewport,
                        deviceScaleFactor: density, mobile: true,
                        screenOrientation: { type: 'landscapePrimary', angle: 90 } });
                    await checkPlayerLayout(page, 'Fullscreen rotated back');
                }
            }
            await page.locator('#help-button').click();
            const download = page.waitForEvent('download');
            await page.locator('#export').click();
            assert.ok((await download).suggestedFilename(), 'Export must be clickable in fullscreen');
            await page.locator('#close-help').click();
            await page.locator('#fullscreen').click();
            await page.waitForFunction(() => !document.fullscreenElement &&
                document.getElementById('fullscreen').getAttribute('aria-pressed') === 'false');
            assert.deepEqual(await page.evaluate(() => orientationCalls), mobile ? [['landscape', 'game'], ['unlock']] : []);
            assert.equal(await page.locator('#fullscreen').getAttribute('aria-label'), 'Enter full screen');
            await page.mouse.move(viewport.width / 2, viewport.height / 2);
            await checkPlayerLayout(page, name + ' restored');
            await checkSmallText(page, name + ' restored');
            if (mobile) {
                for (const unavailable of ['rejected', 'throws', 'missing']) {
                    await page.evaluate(mode => Object.defineProperty(screen.orientation, 'lock', { value:
                        mode === 'missing' ? undefined : mode === 'throws'
                            ? () => { throw new Error('Orientation lock unavailable'); }
                            : async () => { throw new Error('Orientation lock unavailable'); }
                    }), unavailable);
                    await page.locator('#fullscreen').click();
                    await page.waitForFunction(() => document.fullscreenElement?.id === 'game' &&
                        document.getElementById('fullscreen').getAttribute('aria-pressed') === 'true');
                    if (viewport.height > viewport.width) {
                        await page.waitForFunction(() => document.getElementById('status').textContent.includes('sideways'));
                        if (unavailable === 'rejected') {
                            const client = await context.newCDPSession(page);
                            await client.send('Emulation.setDeviceMetricsOverride', { width: viewport.height,
                                height: viewport.width, deviceScaleFactor: density, mobile: true,
                                screenOrientation: { type: 'landscapePrimary', angle: 90 } });
                            await page.waitForFunction(() => document.getElementById('status').textContent === '');
                            await client.send('Emulation.setDeviceMetricsOverride', { ...viewport,
                                deviceScaleFactor: density, mobile: true,
                                screenOrientation: { type: 'portraitPrimary', angle: 0 } });
                        }
                    } else {
                        assert.equal(await page.locator('#status').textContent(), '', 'Landscape needs no rotation hint');
                    }
                    await page.locator('#help-button').click();
                    // Browser-initiated exit must release a pending/rejected lock too.
                    await page.evaluate(() => document.exitFullscreen());
                    await page.waitForFunction(() => !document.fullscreenElement &&
                        document.getElementById('fullscreen').getAttribute('aria-pressed') === 'false');
                    await page.locator('#close-help').click();
                    assert.equal(await page.locator('#status').textContent(), '', 'Rotation hint clears on exit');
                }
                assert.deepEqual(await page.evaluate(() => orientationCalls.at(-1)), ['unlock']);
            } else {
                for (const failure of ['rejected', 'throws']) {
                    await page.evaluate(mode => {
                        const deny = options => {
                            window.fullscreenOptions = options;
                            throw new Error('Fullscreen denied');
                        };
                        document.getElementById('game').requestFullscreen = mode === 'throws' ? deny : async options => deny(options);
                    }, failure);
                    await page.locator('#fullscreen').click();
                    await page.waitForFunction(() => document.getElementById('status').textContent.includes('unavailable'));
                    assert.deepEqual(await page.evaluate(() => fullscreenOptions), { navigationUI: 'hide' });
                    assert.equal(await page.locator('#fullscreen').getAttribute('aria-pressed'), 'false');
                }
                await page.addInitScript(() => Object.defineProperty(document, 'fullscreenEnabled', { value: false }));
                await page.reload();
                await page.waitForFunction(() => document.getElementById('loading').hidden, null, { timeout: 60000 });
                assert.equal(await page.locator('#fullscreen').isVisible(), false, 'Unsupported fullscreen must hide the control');
                await page.locator('#help-button').click();
                assert.equal(await page.locator('#help-panel').isVisible(), true, 'Menu remains available without fullscreen');
            }
            assert.deepEqual(errors, []);
        } finally { await context.close(); }
    }
    console.log('PASS: unobstructed transparent fullscreen control, mobile landscape request/unlock/fallback, fullscreen menu and export, native resolution, small text and all four box edges at 1x/1.25x/2x/3x density');
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
        await page.keyboard.press('q', { delay: 100 });
        return page.evaluate(() => {
            const bytes = Module.tswStorage.read('quick.save');
            const view = new DataView(bytes.buffer, bytes.byteOffset, bytes.byteLength);
            return [view.getInt32(6297, true), view.getInt32(6301, true)];
        });
    }
    async function toggle() {
        await tap(100, 14); // Options
        await tap(400, 114); // Controls tab
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
            if (kind === 'controls') bytes.fill(6, 123 + 2 + 10 * 11, 123 + 2 + 11 * 11); // Clear corridor.
            else if (kind === 'shop') bytes[123 + 2 + 4 * 11 + 5] = 16; // Altar
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
        await page.keyboard.press('Shift+Q', { delay: 100 });
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
        await tap(37, 286); // The Orb of Wisdom directly opens a long conversation.
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
        for (const speed of [1, 3, 10]) {
            await tap(100, 14); // Options
            await tap(148, 114); // Game tab
            await tap(140 + (speed - 1) / 9 * 520, 300);
            await tap(636, 484); // Done
            await fixture('controls');
            assert.deepEqual(await position(), [5, 10]);
            await page.keyboard.press('ArrowLeft', { delay: 160 });
            assert.deepEqual(await position(), [4, 10], speed + 'x: a short arrow press takes exactly one step');
            await padStart('Left');
            await page.waitForTimeout(160);
            await end();
            assert.deepEqual(await position(), [3, 10], speed + 'x: a short pad press takes exactly one step');
            await page.keyboard.press('ArrowRight', { delay: 320 });
            assert.deepEqual(await position(), [5, 10], speed + 'x: a deliberate hold begins repeating after 250 ms');
            await page.keyboard.down('ArrowLeft');
            await page.waitForTimeout(60);
            await page.keyboard.press('i', { delay: 80 }); // Inventory blocks the direction already held.
            await page.waitForTimeout(300);
            await page.keyboard.press('Escape', { delay: 80 });
            await page.waitForTimeout(300);
            await page.keyboard.up('ArrowLeft');
            assert.deepEqual(await position(), [4, 10], speed + 'x: closing a menu cannot resume a held direction');
        }
        assert.deepEqual(errors, []);
        console.log('PASS: mobile movement, 1x/3x/10x keyboard and pad timing, held-key menu isolation, dialogue tap/drag/cancel, explicit shop choices, saved override and viewport fit');
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
        await click(400, 300); // Slider midpoint: 5.5x.
        assert.equal(await page.evaluate(() => JSON.parse(new TextDecoder().decode(
            Module.tswStorage.read('settings.json'))).animation_speed), 5.5);
        await click(266, 114);
        await page.screenshot({ path: path.join(output, 'settings-qol.png') });
        for (const [mode, value] of [['Description + confirm', 1], ['One-click', 2], ['Confirm', 0]]) {
            await click(568, 396);
            assert.equal(await page.evaluate(() => JSON.parse(new TextDecoder().decode(
                Module.tswStorage.read('settings.json'))).item_use_mode), value,
                'Item use must cycle to ' + mode);
        }
        await click(568, 396); // Persist Description + confirm through the reload below.
        await click(400, 114);
        await page.screenshot({ path: path.join(output, 'settings-controls.png') });
        await click(534, 114);
        await click(400, 216);
        assert.equal(await page.evaluate(() => JSON.parse(new TextDecoder().decode(
            Module.tswStorage.read('settings.json'))).recording), true, 'Recording belongs to Replay');
        await page.screenshot({ path: path.join(output, 'settings-replay.png') });
        await click(668, 114);
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
        assert.equal(await page.evaluate(() => JSON.parse(new TextDecoder().decode(
            Module.tswStorage.read('settings.json'))).item_use_mode), 1,
            'Item use mode must survive a browser reload');
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
    async function key(name) {
        await page.keyboard.press(name, { delay: 100 });
        // Shift+Q followed by Q reuses one physical key; let the game observe its release.
        await page.waitForTimeout(50);
    }
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
        await key('q');
        await page.waitForFunction(() => Module.FS.analyzePath('/Savedat/quick.save').exists);
        await page.waitForFunction(() => Module.FS.analyzePath('/Savedat/autosave.save').exists);
        await page.waitForFunction(() => document.getElementById('storage').textContent === 'Saved in this browser');
        const autosave = await page.evaluate(() => Array.from(Module.tswStorage.read('autosave.save')));
        assert.equal(autosave.length, 6957, 'Floor autosave must retain the original native format');
        await page.evaluate(() => {
            window.addEventListener('keydown', event => {
                if (event.ctrlKey && event.key.toLowerCase() === 'l')
                    window.browserShortcutPrevented = event.defaultPrevented;
            });
        });
        await key('Control+l');
        assert.equal(await page.evaluate(() => window.browserShortcutPrevented), false,
            'Ctrl+L must remain available to the browser');
        await page.locator('#canvas').focus();
        await key('ArrowLeft');
        await key('Shift+L');
        await key('q');
        const original = await page.evaluate(() => Array.from(Module.tswStorage.read('quick.save')));
        assert.equal(original.length, 6957, 'Original-format save must retain its exact byte size');
        assert.equal(new DataView(Uint8Array.from(original).buffer).getInt32(6297, true), 5,
            'Shift+L must restore the entry position after walking away');
        assert.deepEqual(await page.evaluate(() => Array.from(Module.tswStorage.read('autosave.save'))), autosave,
            'Walking, restoring and quick saving must leave the floor entry intact');
        const history = await page.evaluate(() => Array.from(Module.tswStorage.read('quick.save.achievements.json')));
        await page.screenshot({ path: path.join(output, 'game.png') });
        await page.reload();
        await ready();
        assert.deepEqual(await page.evaluate(() => Array.from(Module.tswStorage.read('autosave.save'))), autosave,
            'The latest floor-entry autosave must survive a browser reload');
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
        await page.locator('#fullscreen').click();
        await page.waitForFunction(() => document.fullscreenElement?.id === 'game');
        await page.mouse.move(500, 500);
        await checkPlayerLayout(page, 'Fullscreen');
        await page.locator('#help-button').click();
        assert.equal(await page.locator('#help-panel').isVisible(), true, 'Help must work inside fullscreen');
        await page.locator('#close-help').click();
        await page.locator('#fullscreen').click();
        await page.waitForFunction(() => !document.fullscreenElement);
        await page.mouse.move(500, 500);
        await checkPlayerLayout(page, 'Exited fullscreen');
        // Load through the actual game UI after hydration, then save again to exercise backups.
        await page.locator('#canvas').focus();
        await key('l');
        await key('Shift+Q');
        await key('q');
        await page.waitForFunction(() => Module.FS.analyzePath('/Savedat/quick.save.bak').exists);
        await page.waitForFunction(() => document.getElementById('storage').textContent === 'Saved in this browser');
        assert.deepEqual(await page.evaluate(() => Array.from(Module.tswStorage.read('quick.save.bak'))), original);
        await page.reload();
        await ready();
        assert.deepEqual(await page.evaluate(() => Array.from(Module.tswStorage.read('quick.save.bak'))), original);
        assert.deepEqual(errors, [], 'Game must not report uncaught browser errors');
        console.log('PASS: game startup, native save, IndexedDB reload, companion history, original-format export, load and backup');
        await mobileSmoke(browser, url, output);
        await fullscreenSmoke(browser, url, output);
        await languageSmoke(browser, url, output);
    } finally {
        console.log('Final page status:', await page.locator('body').innerText().catch(() => 'Page unavailable'));
        await page.screenshot({ path: path.join(output, 'latest.png') }).catch(() => {});
        await browser.close();
        if (server) await new Promise(resolve => server.close(resolve));
    }
}
main().catch(error => { console.error(error); process.exitCode = 1; });
