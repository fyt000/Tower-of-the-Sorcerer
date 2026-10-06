# Game architecture

The repository separates a faithful C++ baseline from the existing Rust rewrite.
They share original content and research evidence, but do not share gameplay
implementations or save formats. The C++ baseline is the reference for checking
future changes; replay, TUI and other experiments can be developed separately.

## C++ core

`baseline_core` owns hero state, 51 floors, 33 shared monster rows, inventory,
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
| `include/baseline/game.hpp` | Named state, tile/item/command IDs and core API |
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

`audio.cpp` parses and caches the MIDI tracks at startup, then synthesizes them
through TinySoundFont. Track selection performs no file I/O or parsing. The
callback uses preallocated synth voices and sample progress, independent of
command speed. Original WAV effects are decoded once; a bounded pool of raylib
aliases shares their samples and lets repeated effects overlap. Fonts use
installed Segoe UI when available and raylib's fallback
otherwise; system fonts are not distributed.

Saves contain the original floor records and 171-word hero record. Monster rows
are reconstructed from constants and seal/cycle flags as in `0x454DE8`; Zeno
remains one shared mutable row. Unmapped original words survive import and
rewriting. Pending commands and presentation snapshots are omitted. Loading
parses into a temporary `Game`, validates it, then replaces the live state.
Earlier C++ saves have a compatibility reader. The Fairy checkpoint is written
after her dialogue and animation finish. [Original data](original-data.md)
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

The comparison tools execute original x86 handlers and a compiled C++ probe.
Core tests execute command playback; presentation tests check frames and scenes;
asset tests compare original decoded pixels and audio bytes with the extracted
versions. [Fidelity notes](../baseline/FIDELITY.md) state what this evidence proves
and what remains unverified.
