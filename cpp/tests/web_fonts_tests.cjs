const assert = require('node:assert/strict');
const { test } = require('node:test');
const vm = require('node:vm');
const fs = require('node:fs');
const path = require('node:path');
const source = fs.readFileSync(path.join(__dirname, '../web/fonts.js'), 'utf8');
const settle = () => new Promise(resolve => setImmediate(resolve));

function fixture() {
    const files = new Map(), calls = [], events = [], timers = new Map();
    let serial = 0;
    const context = {
        Module: { tswFontFiles: { ja: 'fonts/ja-hash.otf', zh: 'fonts/zh-hash.otf' } },
        scriptDirectory: 'https://example.com/games/tower/', URL, AbortController,
        setTimeout(callback) { timers.set(++serial, callback); return serial; },
        clearTimeout(id) { timers.delete(id); },
        CustomEvent: class { constructor(name, options) { this.detail = options.detail; } },
        window: { dispatchEvent(event) { events.push(event.detail); } },
        FS: { mkdirTree() {}, writeFile(name, bytes) { files.set(name, bytes); } },
        fetch(url, options) {
            return new Promise((resolve, reject) => {
                const call = { url: String(url), resolve, reject };
                calls.push(call);
                options.signal.addEventListener('abort', () => reject(new Error('Timed out')));
            });
        }
    };
    vm.runInNewContext(source, context);
    return { fonts: context.Module.tswFonts, calls, files, events, timers,
        succeed(index, bytes = [79, 84, 84, 79, 0, 0, 0, 0, 0, 0, 0, 0]) {
            calls[index].resolve({ ok: true, arrayBuffer: async () => Uint8Array.from(bytes).buffer });
        } };
}

test('English startup never downloads CJK; requests are lazy, deduplicated, and shared by Chinese catalogs', async () => {
    const f = fixture();
    assert.equal(f.fonts.ensure('en'), 1);
    assert.equal(f.fonts.ensure('en-ja'), 1);
    assert.equal(f.calls.length, 0);
    assert.equal(f.fonts.ensure('ja'), 0);
    assert.equal(f.fonts.ensure('ja'), 0);
    assert.equal(f.calls.length, 1);
    assert.equal(f.calls[0].url, 'https://example.com/games/tower/fonts/ja-hash.otf');
    f.succeed(0); await settle();
    assert.equal(f.fonts.ensure('ja'), 1);
    assert.ok(f.files.has('/fonts/ja.otf'));
    assert.equal(f.fonts.ensure('zh-Hans-ja'), 0);
    assert.equal(f.fonts.ensure('zh-Hans-en'), 0);
    assert.equal(f.calls.length, 2);
    f.succeed(1); await settle();
    assert.equal(f.fonts.ensure('zh-Hans-en'), 1);
    assert.equal(f.fonts.ensure('zh-Hans-ja'), 1);
    assert.ok(f.files.has('/fonts/zh.otf'));
    assert.equal(f.fonts.ensure('ja'), 1);
    assert.equal(f.calls.length, 2);
    assert.equal(f.timers.size, 0);
});

test('HTTP failures and invalid font payloads stay recoverable and never create a broken font', async () => {
    const f = fixture();
    f.fonts.ensure('ja');
    f.calls[0].resolve({ ok: false, status: 404 }); await settle();
    assert.equal(f.fonts.ensure('ja'), -1);
    assert.equal(f.files.size, 0);
    assert.equal(f.calls.length, 1, 'Frames must not repeatedly retry a failed request');
    f.fonts.retry();
    assert.equal(f.fonts.ensure('ja'), 0);
    f.succeed(1, Array.from(Buffer.from('<html>missing</html>'))); await settle();
    assert.equal(f.fonts.ensure('ja'), -1);
    assert.equal(f.files.size, 0);
    f.fonts.retry(); f.succeed(2); await settle();
    assert.equal(f.fonts.ensure('ja'), 1);
    assert.equal(f.files.size, 1);
});

test('late completions cannot replace the notice for the current language', async () => {
    const f = fixture();
    f.fonts.ensure('ja');
    f.fonts.ensure('zh-Hans-en');
    const before = f.events.length;
    f.succeed(0); await settle();
    assert.equal(f.events.length, before);
    assert.equal(f.events.at(-1).family, 'zh');
    f.fonts.ensure('en');
    assert.equal(f.events.at(-1).state, 'ready');
    f.calls[1].reject(new Error('Offline')); await settle();
    assert.equal(f.events.at(-1).state, 'ready');
    assert.equal(f.fonts.ensure('zh-Hans-ja'), -1);
    assert.equal(f.events.at(-1).state, 'error');
});

test('a stalled request times out and can be retried', async () => {
    const f = fixture();
    f.fonts.ensure('ja');
    [...f.timers.values()][0](); await settle();
    assert.equal(f.fonts.ensure('ja'), -1);
    f.fonts.retry(); f.succeed(1); await settle();
    assert.equal(f.fonts.ensure('ja'), 1);
});
