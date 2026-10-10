# Game architecture

Delphi 2 targets a faithful recovery of the game. C++ is an architecturally
similar rewrite with the same core game logic, plus new features and
quality-of-life improvements. Rust is an independent engine and campaign editor.
See the [Delphi modules](../delphi/README.md#architecture) and
[data formats](original-data.md) for implementation and shared content.

## C++ core

`tsw_core` owns the hero, 51 floors, 33 shared monster rows, inventory and
dialogue continuations. It has no graphics, audio or Windows dependency.
Maps, monsters and dialogue are compiled into `src/original_constants.hpp`.

An action writes state and queues commands; `Game::run_one()` executes one
command. Each record contains an opcode and two 16-bit operands. The newest
record executes first, and callbacks can append further commands. The
interpreter is iterative; combat generates bounded turns instead of storing
an entire fight. Monster rows remain shared, including Zeno's gate/seal changes.

| Files under `cpp/` | Responsibility |
|---|---|
| `include/tsw/game.hpp`, `src/game.cpp` | State, IDs, initialization, movement, interpreter and cycles |
| `src/contact.cpp`, `src/combat.cpp` | Contacts, hazards, forecasts, strikes and rewards |
| `src/items.cpp`, `src/npcs.cpp` | Items, Flight, shops and dialogue |
| `src/floor_checks.cpp`, `src/scenes.cpp` | Floor predicates and event scripts |
| `src/original_save.cpp`, `src/save*.cpp`, `src/rankings.cpp` | Save records, slots, checkpoints and ranking files |

Tile IDs, flag aliases, puzzle sums and script coordinates retain their
comparison meaning. Named constants describe them; comments explain addresses
or ordering where needed. Fixed arrays, RAII and bounds checks contain unsafe
memory behavior without changing those rules.

## Desktop and media

`DesktopSession` applies input and schedules commands on a scaled clock.
`desktop.cpp` owns the window loop; `presentation.cpp` owns raylib rendering
and overlays. Layout uses an 800×558 logical canvas. Window and framebuffer
sizes determine one centered, aspect-preserving rectangle for both drawing
and mouse mapping. The canvas target and font atlases use physical resolution;
Segoe UI font bytes are cached, with raylib's bundled font as fallback.

`assets.cpp` reads the `Data3/Data2/Midi/Wav` layout or extracted PNGs.
BMP/OZ images retain their masks. Ending pictures and the GeneralUser GS bank
are embedded PE resources read by `embedded_media.cpp`. Loading happens before
playback, not per frame.

`audio_mixer.cpp` prepares MIDI, WAVs and synth storage; `audio.cpp` starts
miniaudio. Its callback owns the synth, cursors and effect voices. The game
thread sends an atomic control request and a fixed effect queue. Rendering
takes no locks, performs no I/O and allocates or frees no memory. Track changes
reuse initialized channels, avoiding the synth reset that frees channel storage.
Mute advances playback silently; suspension stops cursors and cue consumption.
Each WAV has sixteen preallocated voices for overlapping effects.

`ReplayPlayer` rebuilds prefixes by applying real inputs to a temporary
`Game`; there is no snapshot cache. Forward playback keeps commands queued
for the session scheduler. Pause freezes commands, animation and audio;
takeover retains the queue and consumed recording prefix. Sparse ranking
records preserve the environment for Fairy decisions. See the
[replay contract](replay-verification.md).

Loading validates temporary state before replacement. Saves omit pending
commands and presentation state; rankings live independently of game slots.
The [save specification](original-data.md#original-saves) owns byte layouts,
checksums, Fairy checkpoint timing and Zeno reconstruction. Desktop preferences
are separate Glaze records in `Savedat/settings.json`.

<a id="native-c-mcp-boundary"></a>
## C++ MCP boundary

`tsw_mcp` adds stdio JSON-RPC to `tsw_cli mcp` without desktop/media dependencies.
Glaze handles transport; the core keeps its types and continuations.
Observations expose named tiles, combat forecasts, items, clues and dialogue.
Developer mode adds raw state and simulations on copied sessions.
CLI, replay and MCP share input execution, recording and prefix reconstruction;
MCP feedback is collected in a temporary session before committing.

In-memory checkpoints copy `Game` and application state. The optional Python
bridge replaces immutable workers through private, versioned runtime RPCs.
`GameState` captures core fields, including private fight/shop state and
checksum words, without adding JSON to the core. Restoration validates a
temporary session; failed candidates leave the previous worker active.
Publication probes a copied worker before replacing the manifest.
Public clients cannot call runtime RPCs. See the [MCP guide](cpp-mcp.md).

## Existing Rust implementation

`tos-core` supplies configurable campaign rules, scripts, commands and
observations. `tos-ui` supplies the shared egui desktop/browser UI and editor.
CLI, headless and MCP adapters use that engine; Node scripts build its clients.
C++ does not import Rust event definitions.

## Verification

| Target | Boundary |
|---|---|
| `tsw_tests` | Catch2 core, save, ranking, replay and MCP cases |
| `tsw_probe` | Research adapter using the game core for handler comparisons |
| `tsw_verify` | DesktopSession, renderer, assets and window fixtures |
| `tsw_audio_tests` | Production mixer output, Debug heap checks and device lifecycle |

Test executables own fixtures and instrumentation. The game has no verification
entry points. [Fidelity notes](../cpp/FIDELITY.md) define what the evidence proves;
[recovery tools](reverse-engineering.md) document comparison workflows.
