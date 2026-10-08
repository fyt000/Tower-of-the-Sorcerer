# Game architecture

The repository separates a faithful C++ baseline from the existing Rust rewrite.
They share original content and research evidence, but do not share gameplay
implementations or save formats. The C++ baseline is the reference for checking
future changes; its command recordings can support later Rust comparison and TUI work.

## C++ core

`tsw_core` owns hero state, 51 floors, 33 shared monster rows, inventory,
dialogue continuations and pending original commands. It has no graphics, audio
or Windows dependency. Maps, monster constants and dialogue are compiled into
`src/original_constants.hpp` from the supported executable.

A player action follows this path:

```text
Desktop input → Game::move / use / choose
              → contact, item, NPC or floor branches
              → immediate state writes + original command records
              → Game::run_one()
              → state, presentation state and sound cues
```

The command record is three 16-bit words: opcode and two operands. `push()`
appends a record; `commands.back()` executes first, matching the Delphi stack.
Callbacks remain named enum values dispatched through an explicit switch.
They can insert further commands, preserving the original continuation order.
`run_one()` executes one record per call without recursively invoking a timer.

Combat emits one strike at a time with bounded queue memory while retaining
ordinary/forced attack order, fatal truncation, rewards and post-combat checks.
The original shared monster rows remain shared: Zeno's gate/seal arithmetic
changes that row rather than creating independent enemy instances.

| Core file | Responsibility |
|---|---|
| `include/tsw/game.hpp` | Named state, tile/item/command IDs and core API |
| `src/game.cpp` | Initialization, movement, command interpreter and cycles |
| `src/contact.cpp` | Tile contact, doors, stairs, hazards and floor music |
| `src/combat.cpp` | Forecasts, strike generation and victory records |
| `src/items.cpp`, `src/npcs.cpp` | Item loops, Flight, shops and dialogue continuations |
| `src/floor_checks.cpp`, `src/scenes.cpp` | Explicit floor predicates, scripts and cutscenes |
| `src/original_save.cpp`, `src/save.cpp`, `src/save_slots.cpp` | Original save records, raw Fairy checkpoints and eight independent slots |

Original tile IDs, flag aliases, numeric puzzle sums and script coordinates are
retained where changing them would obscure source comparison. Named enums and
constants describe their meaning; concise comments identify source addresses
and ordering constraints. RAII, fixed arrays and checked arithmetic replace
unsafe memory access while the branch structure remains recognizable.

## Desktop and media

`desktop.cpp` polls keyboard input and runs the native window loop.
`DesktopSession` applies UI actions, advances commands on a scaled clock and
writes completed Fairy checkpoints. `presentation.cpp` owns raylib textures, the 11×11 board and
original 800×500 content proportions, panel artwork and scene compositor.
Walking input and animation use the same selected clock. Dialogue, items,
shops, enemy forecasts and saves use overlays.

The startup menu uses the original opening/title images. Settings are small C++
aggregates serialized automatically by Glaze to `Savedat/settings.json`. They
select recording, mute and separate gameplay/replay speeds. Home and modal menus
pause gameplay; returning home retains a live game or replay for Continue.

`ReplayPlayer` owns the input list and consumed position. Animated playback leaves
commands queued for `DesktopSession` to execute with the selected clock and existing
renderer. The session delays automatic speech/ending acknowledgments and preserves
recorded shop decisions. Pause freezes commands, sprites and audio. Previous/restart
rebuild a prefix with real actions in a temporary `Game`; there is no snapshot cache
or common state schema. Takeover retains the current queue and optionally hands the
consumed prefix to the recorder. Save/reload inputs and automatic Fairy boundaries
run through the original serializer in memory while watching.

`assets.cpp` reads either the original `Data3/Data2/Midi/Wav` layout or the
older extracted PNG layout. `.oz` sprite sheets are decoded as BMPs using
`stb_image`; raylib uploads the resulting images and applies the original masks.
The replacement embeds the two original form pictures and GeneralUser GS bank
as PE resources. `embedded_media.cpp` reads them through standard file I/O,
without direct Windows API calls. Assets are read during loading, not per frame.

`audio_mixer.cpp` loads the original MIDI messages and decodes WAV effects before
`audio.cpp` starts a miniaudio device. Its direct callback owns the TinySoundFont synth,
MIDI cursor and all effect voices. The game thread publishes a packed
track/play/mute/suspend/restart request through a lock-free atomic and writes effects to
a fixed queue. The callback reads the request once per block; it takes no mutex,
performs no I/O, and allocates or frees no memory. Raylib's audio mixer is bypassed.

TSF's ordinary reset frees its channel array. The implementation instead uses its
quick note release and restores initialized channel defaults in the same storage.
All 256 synth voices, 16 MIDI channels and 16 voices per WAV are allocated before
playback. Song changes, looping, pause/resume and muting have separate meanings;
muting keeps the cursors advancing. The mixer has no verification counters or
diagnostic snapshots. Catch2 tests render its output directly without opening a
device. MSVC Debug tests install a CRT heap hook around prepared rendering; the
hook and its counters exist only in `tests/audio_tests.cpp`. The native device
case checks initialization, control changes and shutdown.

Replay suspension silences a block before consuming cues or advancing music and
effect cursors. It uses one bit in the existing atomic request and the same
preallocated playback storage, keeping the callback free of locking and allocation.

`presentation.cpp` measures the GLFW window and framebuffer separately each frame
and sets a logical projection over the full physical viewport. The same centered,
aspect-preserving rectangle maps mouse input back onto the canvas. Tests compare
actual framebuffer pixels after resizing, maximizing and restoring, including
native DPI changes. The canvas render target matches its displayed physical pixel
size, while layout and gameplay stay in 800×558 logical coordinates. Installed
Segoe UI fonts are rasterized at each requested size for the current scale. The
font bytes are read once; each logical size retains one atlas that is replaced
when its required pixel size changes. Text positions and clipping align to physical
pixels, and glyph coverage supplies antialiasing without bilinear atlas filtering.
Raylib's bundled font remains the fallback when Segoe UI is unavailable.

Saves contain the original floor records and 171-word hero record. Monster rows
are reconstructed from constants and seal/cycle flags as in `0x454DE8`; Zeno
remains one shared mutable row. Unmapped original words survive import and
rewriting. Pending commands and presentation snapshots are omitted. Loading
parses into a temporary `Game`, validates it, then replaces the live state.
Fairy checkpoints use the original raw `save0.dat` record layout, preserving
existing checksum words rather than refreshing them. Their explicit restore path
checks gameplay fields and bounds; manual slots also verify the original checksums.
The Fairy checkpoint is written after her dialogue and animation finish. [Original data](original-data.md)
records the byte layout and load-time scaling quirk.

Manual slots read and write `Savedat/save1.dat` through `save8.dat` beside the
executable. The same path is used regardless of which executable created a save.
`--save-dir` selects a different directory explicitly; slot lookup stays within it.

## Existing Rust implementation

`tos-core` is a deterministic engine with configurable campaign rules, scripts,
commands and observations. `tos-ui` provides the shared egui desktop/browser UI
and campaign editor. CLI, headless and MCP adapters call that engine; Node scripts
build and launch its clients. This architecture is retained. The C++ baseline
uses explicit original branches instead of importing Rust event definitions.

## Verification

`tsw_tests` runs named Catch2 core cases through the `Game` API, including complete command
playback, save I/O and deliberately constructed edge states. CTest discovers
each case so it can be run independently. The Python comparison tools execute
original x86 handlers and the separate `tsw_probe` research adapter.
The adapter accepts state setup and handler commands, then prints state and
command snapshots for comparison. It shares the same compiled core as the game.

The original-machine tests inject matching hero, map and inventory states into
an emulated copy of the original EXE. They bypass VCL/device calls and report
what was skipped. These controlled cases expose branches without requiring a
full tower playthrough; altered-map cases also exercise unusual bounds and
numeric predicates. Desktop smoke fixtures check the modern window, input,
scene timing and saves. The [replay recorder and CLI](replay-verification.md)
use `tsw_replay` at the application boundary for player inputs, exact Flight
selection and opt-in save companions. `tsw_cli` drains automatic commands without
graphics or audio. Explicit assertions belong to Catch2 and an external test
script; neither engine needs a common state schema for later Rust comparisons.
The research probe's raw state edits and
internal handler calls remain research controls.

`tsw_audio_tests` drives the production mixer for offline functional and Debug
heap checks. `tsw_verify` owns all injected desktop fixtures, renderer/window
checks, asset comparisons and report generation. Both are optional test targets;
the game executable has no verification entry points. Desktop scenarios call the
same `DesktopSession` used by the window loop rather than duplicating its actions
or scheduler. Presentation tests check frames and scenes; asset tests compare
original decoded pixels and audio bytes with the extracted versions. [Fidelity notes](../cpp/FIDELITY.md) state what this evidence proves
and what remains unverified.
