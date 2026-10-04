# Shared Rust interface and platform boundaries

`tos-core` owns the complete deterministic simulation: movement, path planning,
combat, shops, items, event predicates, tower cycles, inspection gates and save
validation. It has no graphics, audio, browser, filesystem or wall-clock dependency.
The CLI, JSONL headless runner and stdio MCP server all use this engine directly.

`tos-ui` implements the game interface and campaign editor in Rust using
[eframe/egui](https://docs.rs/eframe/0.36.2/eframe/). Desktop runs a native window
with OpenGL; WebAssembly uses WebGL in a single canvas. The same Rust code handles
layout, keyboard/touch/pointer input, tile painting, sprite animation, battle
turns, conversations, journal, settings, language switching and the visual editor.
The browser's handwritten JavaScript only initializes the generated WebAssembly
module. There is no native WebView or second game UI to keep synchronized.

## Simulation and presentation

Each command commits the deterministic result immediately and emits an ordered
`last_action.presentation` timeline. This timeline contains movement, combat
parameters, tile changes, original dialogue, waits, sound cues and cinematics.
The graphical client retains the previous visual state and plays those events
in order before accepting the next gameplay input. An AI/headless client can
ignore their duration and continue immediately. Animations never apply damage,
grant items or rewrite the saved map: those effects belong to the engine.

Combat events include the starting HP, damage per strike, retaliation count and
first-strike order. This lets the GUI display alternating hits and the arithmetic
without recalculating a separate combat rule. Original event extraction retains
ordered guard movements, dialogue and audio cues rather than collapsing them to
a final map. Original wait records do not encode a portable number of milliseconds;
the remake's presentation durations remain tunable approximations.

Click routes use `Engine::path_to`. Only clear road can be an intermediate square.
A selected enemy, door, pickup, NPC or staircase can be the final action. An
unreachable target yields the clear-road prefix nearest that square; it cannot
make the hero cross an intervening enemy or door. Floor changes and conversations
interrupt a queued route. MCP's `plan_path` exposes the same read-only planner.

## Native functionality

The native `tos-ui` executable provides the full graphical game and editor,
including original textures, both hero walking frames, enemy animation, scripted
events, dialogue, sound effects, music, language switching and resizable/DPI-aware
layout. It uses local asset files and Rodio for sound output. It embeds the default
campaign but loads art, music and fonts at runtime, keeping original media out of
the executable and the source repository. `--campaign`, `--assets-root` and
`--editor` support alternate content and direct editor launch.

Native saves use the same portable JSON as browser/CLI/MCP. They are stored in
the user's application-data directory under `tos-rust`; `TOS_STORAGE_DIR` can
redirect that location for tests or portable deployments. Browser saves use
`localStorage`. Checkpoints and autosaves are separate. A campaign fingerprint
rejects an incompatible save before any state is mutated.

The small `platform` module handles byte loading, persistence and JSON export.
The audio module decodes the extracted WAV files and synthesizes MIDI to PCM in
Rust. WebAudio and Rodio play the same PCM. The synthesizer retains score notes,
timing and instrument programs, but its oscillator timbres approximate the old
hardware MIDI sound bank. The current synthesizer ignores MIDI controllers,
including sustain and expression, and pitch bend; it renders at most 180 seconds
per score into mono PCM. It is a portable music implementation rather than an
exact emulation of Windows MIDI output. Original WAV effects are used directly.

## What an Android build would require

There is no Android package in this pass. The Rust simulation, presentation,
editor, localization, sprite processing and MIDI synthesis are already reusable.
[Eframe 0.36.2 exposes Android activity backends](https://docs.rs/eframe/0.36.2/eframe/#feature-flags)
through `android-game-activity` and `android-native-activity`; its
[Android-only `NativeOptions.android_app` field](https://docs.rs/eframe/0.36.2/src/eframe/epi.rs.html#394-402)
passes the activity handle to the event loop. This gives the project a concrete
platform port path. No Android entry point, package, or device behavior is
implemented or verified here.

The remaining Android work is concrete:

1. Add an `android_main` activity entry point, a `cdylib` build target, and the
   chosen Eframe/Winit activity feature; pass the received activity handle to
   `NativeOptions.android_app`. Configure the NDK, Android targets, manifest and
   APK/AAB build. [Winit's Android integration guide](https://docs.rs/winit/0.30.13/winit/platform/android/)
   documents the matching activity glue version and the different packaging
   requirements of NativeActivity and GameActivity.
2. Load extracted assets and the Chinese font from Android assets instead of
   desktop paths, and map persistence/export/import to Android app storage and
   the document picker. Do not package proprietary assets into a public release
   by default.
3. Connect audio to the Android-supported output backend and handle activity
   pause/resume, audio focus and interrupted playback.
4. Test touch input, portrait layout, safe areas, high DPI, virtual keyboards,
   back navigation, and background/resume save behavior on actual devices.
5. Profile GPU usage, memory used by PCM/font caches and startup time on mobile;
   adjust loading and synthesis as necessary before shipping.

Desktop and browser verification does not establish those Android lifecycle and
device behaviors. The platform boundary keeps that future work contained while
the game and editor remain a single Rust implementation.
