# Fidelity scope

The C++ baseline aims to preserve the supported English **Tower of the Sorcerer
1.2** core decisions, state writes and command order. Its source comes from the
original Delphi executable, reviewed Ghidra output and assembly, independently
of the Rust campaign. [Source recovery](../docs/reverse-engineering.md) identifies
the executable hash and workflow; [architecture](../docs/architecture.md) explains
the translation; [retained rules](../docs/mechanics.md) identifies important branches.

## Current evidence

| Original-machine comparison | Passing scenarios |
|---|---:|
| Floor/guard/door builders and altered-state predicates | 731 |
| Contact and ordinary/forced combat | 992 |
| NPCs, continuations, stairs, hazards, capture/ending and Fairy scoring | 426 |
| Items, cardinal bounds, wings and Flight | 2,067 |
| Save bytes, checksums, import/rewrite and Zeno load reconstruction | 145 |
| Correction-log triggers, border retreats and explicit 49F safety exception | 246 |
| Total | 4,607 |

These execute isolated original x86 handlers and compare their output with the
compiled C++ probe. Reports list skipped calls. Unread stale `b` operands in
HeroStrike/Reward are normalized; other compared operands and orders are retained.

The **107 core checks** execute complete command stacks, bounded long fights,
fatal cancellation, dialogue aliases, Fairy restores, all eight save slots,
replacement backups, shared original slot paths, cycle carry/reset rules and
the 50F gate/seal/wing branches. They reproduce the 33F lower-entry softlock
through walking and combat, and finish the original 4,500-round Archsorcerer
and 7,920-round backside Gateman fights with every strike and bounded memory.
The core, renderer, asset loading, complete MIDI synthesis and audio-device
checks have passed MSVC AddressSanitizer Release runs.

The **131 presentation checks** cover original standing/walking poses, all twelve
door/wall/lava modes, both stair phases, all 32 Vampire frames, capture and ending
playback, red panels, Zeno variants and overlays. They run with both original
and extracted media. The **71 asset checks** establish pixel equality for all
31 loaded images, unchanged bytes for 17 MIDI tracks and eight WAV effects,
WAV decoding, embedded media and selection/error handling. Audio checks render
all 17 complete MIDI tracks, dispatch all 35,343 parsed messages across varied
callback block sizes, verify looping and produce finite, nonzero stereo synthesis.
A WASAPI device check exercises overlapping effects, bounded bursts, the sample
clock and all cached track selections; it does not establish audible equivalence
or uninterrupted playback on every device.

Desktop smoke checks cover command pause/resume, numbered saves, Fairy
checkpoints and the ending at the installed high-DPI setting. The replacement
is also tested as `TSW.exe` beside only copied original media folders, without
an external soundfont, extracted PNGs or original EXE.

Save checks execute the original writer's wrapping checksum loops, its loader's
acceptance path and the Zeno reconstruction instructions. They cover byte-exact
import/rewrite, edits, opaque-word retention, frontside/backside seal states,
all directions, earlier C++ import, corrupt/truncated records and bounds checks.
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
| 47F Magician A | The hero-row guard and horizontal wrapping within the flat floor array remain. Out-of-floor memory access is rejected. |
| Backside 45F Merchant | Pays the original unscaled 2,000 HP for 1,000 gold. |
| Sealed Zeno after load | Retains the shared-row reconstruction and extra backside scaling documented above. |
| Lucky Gold and enemy-first combat | Actual income doubles. The modern completion text omits the amount, so Delphi's wrong displayed amount is not reproduced. |
| 40F boss prompt | The original yellow-door message command remains. |
| 50F Thief / backside magic text | Original speech/message IDs remain. VCL text positioning is outside the modern overlay's fidelity scope. |
| Magician A mask | The original bitmap pixels remain unchanged; no one-pixel asset correction is applied. |
| 49F summon ghost | Exactly 128 written commands execute. The stray cursor increment at `0x4637DD` is omitted; the report explicitly reproduces and excludes the unsafe 129th record. |
| Combat buffer overflow | Every round executes incrementally; no legacy fixed event buffer is used. |
| Closely spaced effects / BGM stalls | Preloaded WAV voice aliases overlap. Parsed MIDI tracks are cached; selection performs no disk reads, parsing or message freeing under the callback lock. |

Prologue options, translations, shortcuts, fonts, window placement, loading during
events and sound preferences belong to the modern UI/settings scope. The runtime
mute option persists across loads, independently of saved gameplay music state.
No optional gameplay fixes from tswKai are enabled by this audit.

## Deliberate differences and remaining work

- Command execution is iterative and combat memory is bounded; legacy recursive
  timers and fixed stack buffers are replaced while command order is preserved.
- raylib provides rendering, input and audio. Original board proportions, assets,
  masks and scene stages remain; GUI overlays, fonts, settings and timing are modern.
- MIDI uses TinySoundFont/GeneralUser GS, so instrument timbre differs from a
  Windows MIDI device. Uninterrupted audio on every device is not established.
- Saves use the original 6,957-byte records and shared-Zeno load reconstruction,
  including legacy backside scaling. Earlier C++ `TOSB` v1 files import. Bounds
  validation, backups and independent manual/quick/Fairy files are modern.
  Manual slots use the original `Savedat/save1.dat` through `save8.dat` paths;
  there is no alternate-directory or old-filename lookup. Original settings
  and custom rankings are not imported. Original checksums
  do not protect map bytes or the final hero words; no extension is added.
- Tests establish agreement for sampled states and isolated handlers. They do not
  prove every possible branch, pixel-exact Delphi compositing, exact legacy timer
  durations or a full natural tower playthrough.

Machine-readable reports remain in `baseline/*-report.json`, with renderer and
asset reports generated in the build tree. Packages carry copies of this evidence.
