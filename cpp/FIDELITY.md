# Fidelity scope

The C++ baseline aims to preserve the supported English **Tower of the Sorcerer
1.2** core decisions, state writes and command order. Its source comes from the
original Delphi executable, reviewed Ghidra output and assembly, independently
of the Rust campaign. [Source recovery](../docs/reverse-engineering.md) identifies
the executable hash and workflow; [architecture](../docs/architecture.md) explains
the translation; [retained rules](../docs/mechanics.md) identifies important branches.

## Current evidence

The [whole-program accounting](../reference/original/whole-program/REVIEW.md)
now retains 3,298 machine-entry C/assembly pairs and inventories every CODE and
PE file byte. All 102 direct targets missing from the earlier presentation
corpus have exports. It identifies Delphi-2 runtime shapes, callback
trampolines, incomplete listing bodies and exception continuations. Remaining
gaps include 14,369 unresolved CODE bytes, 101 metadata/instruction conflict
bytes, 397 warned exports and unresolved framework delivery. This adds source
evidence and freshness guards, not additional behavioral agreement cases.
`verify_original.py` requires a current ledger and records its hash.

| Original-machine comparison | Passing cases or stages |
|---|---:|
| Floor/guard/door builders and altered-state predicates | 731 |
| Contact and ordinary/forced combat | 992 |
| NPCs, continuations, stairs, hazards, capture/ending and Fairy scoring | 426 |
| Items, cardinal bounds, wings and Flight | 2,067 |
| Save bytes, checksums, raw Fairy records and Zeno load reconstruction | 148 |
| Correction-log triggers, border retreats and explicit 49F safety exception | 246 |
| Flight entry matrices and complete input sequences | 1,670 |
| Original Hero Orb displayed arithmetic | 528 |
| Total cases/stages | 6,808 |

These execute isolated original x86 handlers and compare their output with the
compiled C++ probe. Flight comparisons carry original memory between callbacks;
the other counts mainly describe isolated cases. Active item confirmation now
executes from the published callback entry through return. Original-only UI
gate/timer/prompt assertions are separate from these agreement counts.
Reports list skipped calls.
The [9 October Flight audit](../docs/fidelity-audit-2026-10-09.md) documents an
entry check and effectful redraw that the old 4,610 comparisons missed. Pass
counts establish agreement only within each report's stated boundary.
Unread stale `b` operands in
HeroStrike/Reward are normalized; other compared operands and orders are retained.

The Catch2 core, replay and MCP cases execute complete command stacks, bounded long fights,
fatal cancellation, dialogue aliases, Fairy restores, all eight save slots,
replacement backups, shared original slot paths, cycle carry/reset rules and
the 50F gate/seal/wing branches. They reproduce the 33F lower-entry softlock
through walking and combat, check gold completion text and safe 47F boundaries,
and finish the original 4,500-round Archsorcerer
and 7,920-round backside Gateman fights with every strike and bounded memory.
The core, renderer, asset loading, complete MIDI synthesis and audio-device
checks have passed MSVC AddressSanitizer Release runs.

The **131 presentation checks** cover original standing/walking poses, all twelve
door/wall/lava modes, both stair phases, all 32 Vampire frames, capture and ending
playback, red panels, Zeno variants and overlays. They run with both original
and extracted media. The **71 asset checks** establish pixel equality for all
31 loaded images, unchanged bytes for 17 MIDI tracks and eight WAV effects,
WAV decoding, embedded media and selection/error handling. Catch2 audio cases
check that the bank supplies every MIDI program used by the 35,343 parsed messages,
render all 17 complete tracks across varied callback sizes, and verify finite,
nonzero output on playback and looping. Offline PCM checks cover the original
startup lead-in, pause/resume, mute, same-track restart and sixteen overlapping
voices per WAV. Queue cases exercise capacity, rollover and concurrent bursts.
MSVC Debug tests use the CRT heap hook to require zero allocation, reallocation
or free operations during complete prepared tracks, loops, switches and effect
bursts. This instrumentation is confined to the test executable. The native-device
case checks WASAPI initialization, cached track control and joined shutdown;
it does not establish audible equivalence or uninterrupted playback on every device.

Window checks verify six resize/maximize/restore layouts, including native canvas
dimensions, physical framebuffer pixels and pointer mapping. Enlarged glyphs must
contain detail within their former logical pixels, proving the text is rasterized
at the display resolution rather than enlarging a fixed low-resolution canvas.

Desktop smoke checks cover command pause/resume, numbered saves, Fairy
checkpoints and the ending at the installed high-DPI setting. The replacement
is also tested as `TSW.exe` beside only copied original media folders, without
an external soundfont, extracted PNGs or original EXE.

Save checks execute the original writer's wrapping checksum loops, its loader's
acceptance path, the raw Fairy write/read instructions, load refresh, effectful
map redraw and Zeno reconstruction. They cover writer-exact bytes before and
after refresh, edits, opaque-word retention, frontside/backside seal states,
all directions, raw Fairy snapshots, corrupt/truncated records and bounds checks.
File I/O and VCL UI calls are mocked. Fixtures come from the original writer;
the installed `Savedat/` folder had no historical player files to test.

## Correction-log policy

The [tswKai correction log](https://github.com/Z-H-Sun/tswKai/wiki/1.1-%E2%80%90-Run-TSW-Game#corrections-log)
and [patch descriptions](https://github.com/Z-H-Sun/tswKai/wiki/1.2.1-%E2%80%90-Patch-Config#features)
identify triggers to investigate. The pinned unpatched EXE remains the oracle.
Gameplay quirks stay in the baseline; memory corruption and audio scheduling
faults do not. `tools/verify_quirks.py` records the additional machine comparisons.

| Case | Baseline behavior |
|---|---|
| 33F trap | Only the upper cell triggers it. Clearing the guards first from below, then touching that cell, still seals the exits. |
| 47F Magician A | The hero-row guard and horizontal wrapping within the flat floor array remain. Index 121 is rejected: it aliases the next floor's stair landing byte in the original packed maps. |
| Backside 45F Merchant | Pays the original unscaled 2,000 HP for 1,000 gold. |
| Sealed Zeno after load | Retains the shared-row reconstruction and extra backside scaling documented above. |
| Lucky Gold and enemy-first combat | Actual income doubles, as in the original. The modern completion text includes the credited amount; Delphi's wrong enemy-first display of the undoubled amount is a presentation difference. |
| 40F boss prompt | The original yellow-door message command remains. |
| 50F Thief / backside magic text | Original speech/message IDs remain. VCL text positioning is outside the modern overlay's fidelity scope. |
| Magician A mask | The original bitmap pixels remain unchanged; no one-pixel asset correction is applied. |
| 49F summon ghost | Eight guards × eight animation stages × two records gives 128 written commands. The stray cursor increment at `0x4637DD` exposes an unwritten 129th record; the report reproduces that stale command and explicitly excludes it. |
| Combat buffer overflow | Every round executes incrementally; no legacy fixed event buffer is used. |
| Closely spaced effects / BGM stalls | Preloaded WAV voices overlap. Parsed MIDI tracks are cached; the direct device callback takes no lock and allocates or frees no memory. |

Prologue options, translations, shortcuts, fonts, window placement, loading during
events and sound preferences belong to the modern UI/settings scope. The runtime
mute option persists across loads, independently of saved gameplay music state.
No optional gameplay fixes from tswKai are enabled by this audit.

## Deliberate differences and remaining work

The [presentation/input review](../reference/original/presentation/REVIEW.md)
recovers all 130 serialized UI event bindings and 230 published methods, with
240 C-like/assembly pairs including runtime boundaries. The old corpus lacked
100 of those published entries. Entry recovery is separate from branch, alias,
and Windows event-delivery coverage.

The default Hero Orb display uses its separate original arithmetic, which omits
Cross and Dragon Slayer bonuses; actual combat forecasts retain them. The only
optional QOL setting, **Hero Orb actual damage**, defaults off and switches the
Orb display to the combat forecast when enabled. It is a desktop preference,
separate from native game saves and replay inputs, with an enabled-QOL hover
explanation. There
are 528 original numeric row comparisons, plus separately labeled item
open/cancel, idle-timer, and death-prompt checks. Native file actions respect
item/Orb modal controls across desktop dispatch, shortcuts, and Flight
replay/MCP paths. Imported idle redraw words 608/612 are retained, without
advancing the legacy wall clock; exact save bytes after arbitrary original
idle timing are outside the verified scope.

- Command execution is iterative and combat memory is bounded; legacy recursive
  timers and fixed stack buffers are replaced while command order is preserved.
- raylib provides rendering and input; miniaudio provides the audio device. Original board proportions, assets,
  masks and scene stages remain; GUI overlays, fonts, settings and timing are modern.
- MIDI uses TinySoundFont/GeneralUser GS, so instrument timbre differs from a
  Windows MIDI device. Uninterrupted audio on every device is not established.
- Saves use the original 6,957-byte records and shared-Zeno load reconstruction,
  including legacy backside scaling. Fairy snapshots retain the original raw
  `Savedat/save0.dat` record layout without recalculating slot checksums. Bounds
  validation, backups and independent manual/quick/Fairy files are modern.
  Manual slots use the original `Savedat/save1.dat` through `save8.dat` paths;
  there is no alternate-directory or old-filename lookup. Original settings
  and custom rankings are not imported. Original checksums
  do not protect map bytes or the final hero words; no extension is added.
- Tests establish agreement for sampled states and isolated handlers. They do not
  prove every possible branch, pixel-exact Delphi compositing, exact legacy timer
  durations or a full natural tower playthrough.

Machine-readable original comparisons are generated in `build/cpp/reports/`.
`tools/verify_original.py` runs all retained suites and rejects unknown or
effectful skipped callees through `comparison_boundary.py`. Packaging requires
the resulting probe/report hashes. The scan catches direct named writes;
aliased and transitive effects still require review.
Renderer, asset and window reports live in their configured build tree under
`build/cpp/`. Packages carry copies of this evidence; generated reports are not
tracked as source files.
