// Share the native touch overlay. Detect the primary input, rather than guessing from user agents.
(function () {
    'use strict';
    var coarse = window.matchMedia('(pointer: coarse)');
    function detect() {
        Module['tswTouchDevice'] = coarse.matches;
        document.documentElement.classList.toggle('touch-device', coarse.matches);
    }
    detect();
    if (coarse.addEventListener) coarse.addEventListener('change', detect);
    else coarse.addListener(detect);

    var canvas = Module['canvas'], pointer = null;
    Module['tswPointerDown'] = false;
    Module['tswPointerSerial'] = 0;
    Module['tswPointerCancelled'] = false;
    function release(event, cancelled) {
        if (pointer === null) return;
        if (event && event.pointerId !== undefined && event.pointerId !== pointer) return;
        pointer = null;
        Module['tswPointerDown'] = false;
        Module['tswPointerCancelled'] = !!cancelled;
    }
    canvas.addEventListener('pointerdown', function (event) {
        if (!event.isPrimary || pointer !== null) return;
        pointer = event.pointerId;
        Module['tswPointerDown'] = true;
        Module['tswPointerCancelled'] = false;
        Module['tswPointerSerial']++;
        try { canvas.setPointerCapture(pointer); } catch (_) {}
    });
    window.addEventListener('pointerup', function (event) { release(event, false); });
    window.addEventListener('pointercancel', function (event) { release(event, true); });
    canvas.addEventListener('lostpointercapture', function (event) { release(event, true); });
    window.addEventListener('blur', function () { release(null, true); });
    window.addEventListener('pagehide', function () { release(null, true); });
    window.addEventListener('resize', function () { release(null, true); });
    document.addEventListener('visibilitychange', function () { if (document.hidden) release(null, true); });
})();
