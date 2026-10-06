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
| Total | 4,361 |

These execute isolated original x86 handlers and compare their output with the
compiled C++ probe. Reports list skipped calls. Unread stale `b` operands in
HeroStrike/Reward are normalized; other compared operands and orders are retained.

The **88 core checks** execute complete command stacks, bounded long fights,
fatal cancellation, dialogue aliases, Fairy restores, all eight save slots,
replacement backups, shared original slot paths, cycle carry/reset rules and
the 50F gate/seal/wing branches.
The core has also passed an MSVC AddressSanitizer Release run.

The **131 presentation checks** cover original standing/walking poses, all twelve
door/wall/lava modes, both stair phases, all 32 Vampire frames, capture and ending
playback, red panels, Zeno variants and overlays. They run with both original
and extracted media. The **71 asset checks** establish pixel equality for all
31 loaded images, unchanged bytes for 17 MIDI tracks and eight WAV effects,
WAV decoding, embedded media and selection/error handling. All 17 tracks also
produce finite, nonzero stereo synthesis through the selected bank.

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
