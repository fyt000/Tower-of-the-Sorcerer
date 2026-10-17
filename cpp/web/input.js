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
    function release(event) {
        if (event && event.pointerId !== undefined && event.pointerId !== pointer) return;
        pointer = null;
        Module['tswPointerDown'] = false;
    }
    canvas.addEventListener('pointerdown', function (event) {
        if (!event.isPrimary || pointer !== null) return;
        pointer = event.pointerId;
        Module['tswPointerDown'] = true;
        Module['tswPointerSerial']++;
        try { canvas.setPointerCapture(pointer); } catch (_) {}
    });
    window.addEventListener('pointerup', release);
    window.addEventListener('pointercancel', release);
    canvas.addEventListener('lostpointercapture', release);
    window.addEventListener('blur', function () { release(); });
    window.addEventListener('pagehide', function () { release(); });
    window.addEventListener('resize', function () { release(); });
    document.addEventListener('visibilitychange', function () { if (document.hidden) release(); });
})();
