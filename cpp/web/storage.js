// Loaded before main: restore the complete save directory before constructing the game session.
(function () {
    'use strict';
    var root = '/Savedat';
    var timer, dirty = false, syncing = false, available = false;
    var report = function (message, error) {
        Module['tswStorageMessage'] = message;
        if (typeof window !== 'undefined') {
            window.dispatchEvent(new CustomEvent('tsw-storage', { detail: { message: message, error: !!error } }));
        }
    };
    var inside = function (path) { return path === root || path.indexOf(root + '/') === 0; };
    var flush = function () {
        clearTimeout(timer);
        if (!available) {
            report('Browser storage unavailable. Export saves before leaving; reload to retry storage.', true);
            return;
        }
        if (syncing || !dirty) return;
        dirty = false;
        syncing = true;
        report('Saving to browser storage…');
        FS.syncfs(false, function (error) {
            syncing = false;
            if (error) {
                dirty = true;
                report('Browser storage failed. Export your saves; use Retry storage to try again.', true);
                console.error('Save storage:', error);
            } else if (dirty) {
                flush();
            } else {
                report('Saved in this browser');
            }
        });
    };
    var changed = function () {
        dirty = true;
        if (available) {
            report('Saving to browser storage…');
            clearTimeout(timer);
            timer = setTimeout(flush, 200);
        } else {
            report('Browser storage unavailable. Saves are temporary; export them before leaving.', true);
        }
    };
    Module['tswStorage'] = {
        flush: flush,
        files: function () {
            return FS.readdir(root).filter(function (name) {
                return FS.isFile(FS.stat(root + '/' + name).mode) && !/\.(tmp|pending)$/.test(name);
            }).sort();
        },
        read: function (name) {
            if (!name || name.indexOf('/') !== -1 || name.indexOf('\\') !== -1 || name === '.' || name === '..') {
                throw new Error('Invalid save filename');
            }
            return FS.readFile(root + '/' + name);
        }
    };
    Module['preRun'] = Module['preRun'] || [];
    Module['preRun'].push(function () {
        addRunDependency('tsw-restore-saves');
        report('Restoring browser saves…');
        try {
            FS.mkdirTree(root);
            FS.mount(IDBFS, {}, root);
            FS.syncfs(true, function (error) {
                if (error) {
                    // Do not write an empty directory over data that could not be restored.
                    report('Browser storage unavailable. Saves are temporary; export them before leaving.', true);
                    console.error('Save restore:', error);
                } else {
                    available = true;
                    report('Browser save storage ready');
                }
                // Track temporary saves too when persistence is unavailable, so they can be exported.
                // Native fstream writes go through FS.write; renames include backups and companions.
                ['write', 'rename', 'unlink', 'mkdir', 'rmdir'].forEach(function (name) {
                    var original = FS[name];
                    FS[name] = function () {
                        var path = name === 'write' ? FS.getPath(arguments[0].node) : arguments[0];
                        var destination = name === 'rename' ? arguments[1] : '';
                        var result = original.apply(FS, arguments);
                        if (inside(path) || inside(destination)) changed();
                        return result;
                    };
                });
                removeRunDependency('tsw-restore-saves');
            });
        } catch (error) {
            report('Browser storage unavailable. Saves are temporary; export them before leaving.', true);
            console.error('Save storage:', error);
            removeRunDependency('tsw-restore-saves');
        }
    });
    if (typeof window !== 'undefined') {
        window.addEventListener('pagehide', flush);
        document.addEventListener('visibilitychange', function () { if (document.hidden) flush(); });
        window.addEventListener('beforeunload', function (event) {
            if (dirty || syncing) {
                flush();
                event.preventDefault();
                event.returnValue = '';
            }
        });
    }
})();
