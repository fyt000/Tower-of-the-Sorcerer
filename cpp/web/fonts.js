// raylib needs font bytes in MEMFS; CSS font-face cannot supply the WebGL canvas.
(function () {
    'use strict';
    var states = {}, active = null;
    function family(id) { return id === 'ja' ? 'ja' : id.indexOf('zh-') === 0 ? 'zh' : null; }
    function report() {
        var entry = active && states[active];
        if (typeof window !== 'undefined') window.dispatchEvent(new CustomEvent('tsw-font', {
            detail: { family: active, state: entry ? entry.state : 'ready' }
        }));
    }
    function start(id) {
        var entry = states[id] = { state: 'loading' };
        var controller = new AbortController();
        var timeout = setTimeout(function () { controller.abort(); }, 30000);
        report();
        // Resolve relative to the game script, including when hosted under a subdirectory.
        var url = new URL(Module['tswFontFiles'][id], scriptDirectory);
        fetch(url, { signal: controller.signal }).then(function (response) {
            if (!response.ok) throw new Error('Font download: HTTP ' + response.status);
            return response.arrayBuffer();
        }).then(function (buffer) {
            var bytes = new Uint8Array(buffer);
            if (bytes.length < 12 || String.fromCharCode.apply(null, bytes.subarray(0, 4)) !== 'OTTO')
                throw new Error('Invalid OpenType font');
            FS.mkdirTree('/fonts');
            FS.writeFile('/fonts/' + id + '.otf', bytes);
            entry.state = 'ready';
        }).catch(function () {
            entry.state = 'error';
        }).finally(function () {
            clearTimeout(timeout);
            if (active === id) report();
        });
    }
    Module['tswFonts'] = {
        ensure: function (language) {
            var id = family(language);
            if (active !== id) { active = id; report(); }
            if (!id) return 1;
            if (!states[id]) start(id);
            return states[id].state === 'ready' ? 1 : states[id].state === 'error' ? -1 : 0;
        },
        retry: function () {
            if (active && states[active] && states[active].state === 'error') start(active);
        }
    };
})();
