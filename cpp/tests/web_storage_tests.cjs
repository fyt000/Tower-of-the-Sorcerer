const assert = require('node:assert/strict');
const { test } = require('node:test');
const vm = require('node:vm');
const fs = require('node:fs');
const path = require('node:path');
const source = fs.readFileSync(path.join(__dirname, '../web/storage.js'), 'utf8');

function fixture() {
    const files = new Map();
    const calls = [];
    const dependencies = new Set();
    const events = [];
    const context = {
        Module: {}, IDBFS: {}, console: { error() {} },
        setTimeout() { return 1; }, clearTimeout() {},
        addRunDependency(name) { dependencies.add(name); },
        removeRunDependency(name) { dependencies.delete(name); },
        CustomEvent: class { constructor(name, options) { this.type = name; this.detail = options.detail; } },
        window: { addEventListener() {}, dispatchEvent(event) { events.push(event.detail); } },
        document: { addEventListener() {} },
        FS: {
            mkdirTree() {}, mount() {},
            syncfs(populate, callback) { calls.push({ populate, callback }); },
            getPath(node) { return node.path; },
            write(stream, bytes) { files.set(stream.node.path, bytes); return bytes.length; },
            rename(from, to) { files.set(to, files.get(from)); files.delete(from); },
            unlink(name) { files.delete(name); }, mkdir() {}, rmdir() {},
            readdir() { return ['.', '..', ...[...files.keys()].filter(p => p.startsWith('/Savedat/')).map(p => p.slice(9))]; },
            stat(name) { return { mode: files.has(name) ? 1 : 0 }; },
            isFile(mode) { return mode === 1; },
            readFile(name) { if (!files.has(name)) throw new Error('Missing file'); return files.get(name); }
        }
    };
    vm.runInNewContext(source, context);
    context.Module.preRun[0]();
    return {
        ...context, files, calls, dependencies, events,
        storage: context.Module.tswStorage,
        restore(error) { calls.shift().callback(error); },
        write(name, bytes = [1, 2, 3]) { context.FS.write({ node: { path: name } }, Uint8Array.from(bytes)); }
    };
}

test('main waits for IndexedDB restoration before any save can replace existing data', () => {
    const f = fixture();
    assert.equal(f.dependencies.size, 1);
    assert.equal(f.calls[0].populate, true);
    f.storage.flush();
    assert.equal(f.calls.length, 1);
    f.files.set('/Savedat/save1.dat', Uint8Array.from([42]));
    f.restore();
    assert.equal(f.dependencies.size, 0);
    assert.deepEqual([...f.storage.read('save1.dat')], [42]);
});

test('native writes and atomic renames persist saves and companions; asset reads do not', () => {
    const f = fixture(); f.restore();
    f.write('/assets/test'); f.storage.flush();
    assert.equal(f.calls.length, 0);
    f.write('/Savedat/save1.dat.tmp');
    f.FS.rename('/Savedat/save1.dat.tmp', '/Savedat/save1.dat');
    f.write('/Savedat/save1.dat.achievements.json');
    f.storage.flush();
    assert.equal(f.calls.length, 1);
    assert.equal(f.calls[0].populate, false);
    f.calls.shift().callback();
    assert.equal(f.events.at(-1).message, 'Saved in this browser');
    assert.deepEqual(Array.from(f.storage.files()), ['save1.dat', 'save1.dat.achievements.json']);
});

test('a write during synchronization queues another sync without overlapping operations', () => {
    const f = fixture(); f.restore();
    f.write('/Savedat/quick.save'); f.storage.flush();
    f.write('/Savedat/settings.json'); f.storage.flush();
    assert.equal(f.calls.length, 1);
    f.calls.shift().callback();
    assert.equal(f.calls.length, 1);
    f.calls.shift().callback();
    assert.equal(f.events.at(-1).message, 'Saved in this browser');
});

test('quota errors retain dirty data and exports, and explicit retry can persist it', () => {
    const f = fixture(); f.restore();
    f.write('/Savedat/save8.dat', [7, 8, 9]); f.storage.flush();
    f.calls.shift().callback(new Error('Quota exceeded'));
    assert.equal(f.events.at(-1).error, true);
    assert.deepEqual([...f.storage.read('save8.dat')], [7, 8, 9]);
    f.storage.flush();
    assert.equal(f.calls.length, 1);
    f.calls.shift().callback();
    assert.equal(f.events.at(-1).error, false);
});

test('a failed restore permits temporary exports and never overwrites the inaccessible database', () => {
    const f = fixture(); f.restore(new Error('IndexedDB denied'));
    assert.equal(f.dependencies.size, 0);
    f.write('/Savedat/quick.save', [5]); f.storage.flush();
    assert.equal(f.calls.length, 0);
    assert.equal(f.events.at(-1).error, true);
    assert.deepEqual(Array.from(f.storage.files()), ['quick.save']);
    assert.deepEqual([...f.storage.read('quick.save')], [5]);
});

test('exports preserve bytes, reject traversal and omit unfinished transaction files', () => {
    const f = fixture(); f.restore();
    f.write('/Savedat/quick.save', [0, 128, 255]);
    f.write('/Savedat/quick.save.tmp');
    f.write('/Savedat/quick.save.pending');
    assert.deepEqual([...f.storage.read('quick.save')], [0, 128, 255]);
    assert.deepEqual(Array.from(f.storage.files()), ['quick.save']);
    for (const name of ['../assets/music.sfo', 'folder/file', 'folder\\file', '.', '..', ''])
        assert.throws(() => f.storage.read(name), /Invalid save filename/);
});
