# Game architecture

The repository separates a faithful C++ baseline from the existing Rust rewrite.
They share original content and research evidence, but do not share gameplay
implementations or save formats. The C++ baseline is the reference for checking
future changes; replay, TUI and other experiments can be developed separately.

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
| `src/original_save.cpp`, `src/save.cpp`, `src/save_slots.cpp` | Original save records, earlier C++ imports and eight independent slots |

Original tile IDs, flag aliases, numeric puzzle sums and script coordinates are
retained where changing them would obscure source comparison. Named enums and
constants describe their meaning; concise comments identify source addresses
and ordering constraints. RAII, fixed arrays and checked arithmetic replace
unsafe memory access while the branch structure remains recognizable.

## Desktop and media

`desktop.cpp` translates keyboard/mouse actions and advances commands on a
scaled clock. `presentation.cpp` owns raylib textures, the 11×11 board and
original 800×500 content proportions, panel artwork and scene compositor.
Walking input and animation use the same selected clock. Dialogue, items,
shops, enemy forecasts and saves use overlays.

`assets.cpp` reads either the original `Data3/Data2/Midi/Wav` layout or the
older extracted PNG layout. `.oz` sprite sheets are decoded as BMPs using
`stb_image`; raylib uploads the resulting images and applies the original masks.
The replacement embeds the two original form pictures and GeneralUser GS bank
as PE resources. `embedded_media.cpp` reads them through standard file I/O,
without direct Windows API calls. Assets are read during loading, not per frame.

`audio.cpp` loads the original MIDI messages and decodes WAV effects before
starting a miniaudio device. Its direct callback owns the TinySoundFont synth,
MIDI cursor and all effect voices. The game thread publishes a packed
track/play/mute/restart request through a lock-free atomic and writes effects to
a fixed queue. The callback reads the request once per block; it takes no mutex,
performs no I/O, and allocates or frees no memory. Raylib's audio mixer is bypassed.

TSF's ordinary reset frees its channel array. The implementation instead uses its
quick note release and restores initialized channel defaults in the same storage.
All 256 synth voices, 16 MIDI channels and 16 voices per WAV are allocated before
playback. Song changes, looping, pause/resume and muting have separate meanings;
muting keeps the cursors advancing. Allocation hooks verify complete tracks and
looping; device checks cover startup and restart behavior.

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

Catch2 runs named core cases through the `Game` API, including complete command
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
scene timing and saves. A future gameplay CLI can call the same `Game` API;
the research probe's raw state edits and internal handler calls remain research
controls, and a public CLI design is still open.

Presentation tests check frames and scenes; asset tests compare original decoded
pixels and audio bytes with the extracted
versions. [Fidelity notes](../cpp/FIDELITY.md) state what this evidence proves
and what remains unverified.
