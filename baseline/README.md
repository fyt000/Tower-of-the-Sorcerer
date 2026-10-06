# Original game baseline

A separate C++20 implementation of the installed English **Tower of the Sorcerer
1.2**. It translates the original Delphi game's decisions, floor scripts,
callbacks and command stack into readable source. The existing Rust game is an
independent rewrite and is unchanged by this implementation.

The desktop is playable: movement, combat, puzzles, scripted encounters, NPCs,
shops, all inventory items, stairs, Flight, cycles, saving and Fairy checkpoints.
It uses the original 51 maps, 33 monster rows, dialogue and artwork. There is no
runtime JSON campaign or configurable event system.

**Start the packaged game:**
`dist/tos-original-baseline-0.1-windows-x64/tos_baseline.exe`.
The ZIP beside that directory contains the same executable, assets, soundfont,
licenses and validation reports. Those generated/local files are ignored by Git.

This is a tested baseline for further work, with explicit limits. See
[FIDELITY.md](FIDELITY.md) for executable comparison coverage, preserved quirks,
source addresses and intentional presentation/save differences.

## Technology

- **C++20:** ordinary structs, fixed arrays, enums, functions and explicit
  `switch`, `if` and `for` branches. RAII owns files, textures and audio.
- **raylib 5.5:** the window, 2D canvas, input and audio device. The game canvas
  remains 11×11 cells at the original 40-pixel logical size, with proportional
  scaling and original sprites. The original Data3 stone panels and brown frame
  surround it: stats and item sprites on the left, equipment, keys and the
  last defeated enemy on the right. Dialogue, shops, item details and Hero
  Orb enemy forecasts use overlays.
- **TinySoundFont/TinyMidiLoader:** original MIDI tracks synthesized in the
  audio callback using GeneralUser GS 2.0.3. Audio timing is independent of
  command playback and rendering. MIDI files are parsed outside the callback
  lock, and synth voices are preallocated.
- **Visual Studio 2026 + CMake + vcpkg:** the supplied Windows preset builds
  static x64 dependencies and the static MSVC runtime. Versions/download hashes
  are pinned in the manifest and CMake files.

The application has no direct Win32 calls. Platform-specific code is handled by
raylib and the standard library. The core library has no renderer, audio,
Windows or Rust dependency.

The content preserves the original 800×500 proportions, with a small menu and
status bar added around it. Text uses larger installed Segoe UI Semibold and
Bold fonts when available, with raylib's font as a fallback. No system fonts are copied
into the package. Doors split apart, gates open in quarters, walls slide and
lava turns into road in its original direction. Summon/Bomb masks, battle poses,
hero walking frames, the stair spiral and Vampire transformation are retained.
Capture and ending scenes use the original images, tiled dissolve masks and
wide scene canvas. The ending story and closing card are recovered from embedded
Delphi form pictures; compositor timing is modern. The closing card waits for
Enter, Space or the Continue button before starting the backside tower.

## Build with the installed Windows tools

From this checkout, using the installed setup:

```powershell
$env:VCPKG_ROOT = 'D:/projects/vcpkg'
$cmake = 'C:/Program Files/Microsoft Visual Studio/18/Community/Common7/IDE/CommonExtensions/Microsoft/CMake/CMake/bin/cmake.exe'
$ctest = 'C:/Program Files/Microsoft Visual Studio/18/Community/Common7/IDE/CommonExtensions/Microsoft/CMake/CMake/bin/ctest.exe'
Set-Location baseline
& $cmake --preset windows
& $cmake --build --preset release -j 4
& $ctest --preset release
& ./build-vs/Release/tos_baseline.exe
```

The first configure installs raylib through vcpkg and downloads the pinned
TinySoundFont source and verified soundfont. Later builds reuse them. The preset
selects `Visual Studio 18 2026` and `x64-windows-static`; edit the generator for
another installed Visual Studio version. Debug builds use the `debug` presets.

Original media is loaded from `../web/assets` during development and from
`assets` beside the executable in a package. `--assets DIRECTORY` overrides it.
If local media is missing, extract it from the original installation with the
repository's existing `tools/extract_original.py` script, then run
`python baseline/tools/extract_ui.py` to recover its embedded ending pictures. Generated constants
can be regenerated separately with `python baseline/tools/extract_constants.py`;
this verifies the original executable's SHA-256.

For a headless build with any C++20 compiler and CMake 3.25 or later:

```sh
cmake -S baseline -B baseline/build-headless -DBASELINE_GUI=OFF
cmake --build baseline/build-headless --config Release
ctest --test-dir baseline/build-headless -C Release --output-on-failure
```

This needs no graphics/audio libraries, soundfont or original media. This
delivery was built and tested with MSVC on Windows; other platforms are not yet
verified.

## Controls and saves

| Control | Action |
|---|---|
| Arrows / WASD | Move; hold to repeat |
| Enter / Space | Continue dialogue, accept the first shop choice, or leave the ending card |
| Left inventory sprites | Open item details, then use an active item |
| I | Open/close the full inventory overlay |
| Flight: Up / Down, Enter, Esc | Choose floor, travel, cancel |
| F6 / F7 or Game menu | Open the eight manual save / load slots |
| Save picker: 1–8 or arrows, Enter, Esc | Select a slot, save/replace/load, close |
| F5 / F9 | Quick save / restore |
| F8 | Restore the last completed Fairy checkpoint |
| F2 | Start a new game |
| M | Mute/unmute music and effects |
| Options menu | Music toggle and 1×, 3× or 10× walking and command animation speed |
| Hero Orb: View enemies | Inspect this floor's enemy stats and predicted battle damage |

Shop choices are clickable; Esc cancels a shop. Long dialogue and recorded
Wisdom clues scroll with the mouse wheel.
The Hero Orb overlay supports the mouse wheel, Up/Down and Previous/Next.
The bottom-right panel shows the current battle, then retains the last defeated
enemy's stats and battle damage while walking or changing floors. Its snapshot
uses encounter-time stats; new games and save restores reset presentation state.

The original game has **eight numbered manual slots** (Data 1–8), plus a Fairy
checkpoint. This baseline keeps eight independent `slot-1.save` through
`slot-8.save` files, a separate `quick.save`, and `fairy.save`. Each slot shows
its floor, frontside/backside mode and hero stats. Occupied slots use an explicit
Replace action; their previous contents remain in a `.bak` file. Empty and
unreadable saves are shown separately, and unreadable slots cannot be loaded.
Opening the load picker pauses command playback, including during dialogue;
Esc resumes the pending action. Slot summaries use the same validated decoder
as restoring a game.

Default saves are `%APPDATA%/TosOriginalBaseline` on Windows. Other platforms use
`$XDG_DATA_HOME/tos-original-baseline` or `~/.local/share/tos-original-baseline`.
`--save-dir DIRECTORY` overrides this. Save at rest, after the current command
stack and dialogue complete. Saves are versioned, checked before restoring, and
written through a temporary file with a previous-file backup. They preserve
the normalized shared Zeno row. They do not import the old Delphi `.dat` files
or Rust saves.

The backside uses the recovered red Data3 side panels and the original 44×
monster scaling. Frontside 50F contact starts the ending. Cycle 2 installs the
fixed Zeno row and its gate sequence forces an enemy-first fight. Later cycles
use the current shared row, including a seal applied on 49F after gate entry.
See the Zeno table in [FIDELITY.md](FIDELITY.md) for the resulting combat stats.

## Read the implementation

| File | Responsibility |
|---|---|
| `include/baseline/game.hpp` | Named hero/map state, tile/item/command/callback IDs, public core API |
| `src/game.cpp` | Initialization, movement, iterative command interpreter, cycles |
| `src/contact.cpp` | Tile contact, doors, stairs, hazards, landing direction, music selection |
| `src/combat.cpp` | Forecast, ordinary/forced fights, bounded strike generation, victory records |
| `src/items.cpp` | Explicit item switch, cardinal loops, classifier and Flight callbacks |
| `src/npcs.cpp` | Merchants, altar purchases, old-man/thief/Fairy speech and continuations |
| `src/floor_checks.cpp` | Original post-combat floor switch and numeric puzzle predicates |
| `src/scenes.cpp` | Recovered arrival switch, summons, capture, transformation and ending builders |
| `src/save.cpp` | Validated portable save encoding; no legacy double scaling |
| `src/save_slots.cpp` | Eight numbered paths and validated slot summaries |
| `src/desktop.cpp` | Desktop controls, command pacing, saves and window loop |
| `src/presentation.cpp`, `src/presentation.hpp` | Original panel layout, overlays, sprite animation and scene compositor |
| `src/audio.cpp` | Independent MIDI synthesis and WAV playback |
| `src/presentation_checks.cpp` | Rendered frame boundaries, cutscene playback and UI snapshot checks |
| `src/original_constants.hpp` | Generated original maps, monster rows and dialogue strings |

The original command record still consists of three 16-bit words. `push()`
inserts a record; `commands.back()` executes first. A command may insert more
records, preserving the old callback order. `run_one()` executes one record
without recursively calling a timer. Combat generates one strike at a time,
so even long fights keep a small command stack. Floor scripts stay explicit
functions and branches; the generated constants are data, not a gameplay DSL.

Original floor numbers, cell coordinates, dialogue IDs, flag indices, atlas
frame ranges and numeric-sum puzzle checks are intentionally retained where
they help compare against the decompiler. Tile kinds, items, sounds, door modes,
callback types and important sprite/monster indices have names. Comments
identify source entries and explain ordering or preserved quirks.

The decompiled C-like evidence is in `../reference/original/decompiled`.
The original is **Borland Delphi/VCL**, not C++. A C++ decompiler target would
not recover its original Pascal structure; reviewed C-like output, assembly
and executable probes are suitable inputs to this C++ implementation.

## Validate and package

The core checks run through CTest. The original-machine comparisons require
Python, `pefile`, `capstone` and `unicorn`, and the same hash-pinned original EXE.
`TOS_ORIGINAL_EXE` overrides its default installed path. From the repository root:

```powershell
python baseline/tools/differential.py --probe baseline/build-vs/Release/tos_baseline_probe.exe
python baseline/tools/verify_interactions.py --probe baseline/build-vs/Release/tos_baseline_probe.exe
python baseline/tools/verify_callbacks.py --probe baseline/build-vs/Release/tos_baseline_probe.exe
python baseline/tools/verify_items.py --probe baseline/build-vs/Release/tos_baseline_probe.exe
baseline/build-vs/Release/tos_baseline.exe --audio-test --screenshot baseline/build-vs/midi-test.wav
baseline/build-vs/Release/tos_baseline.exe --smoke fairy --save-dir baseline/build-vs/smoke-saves
baseline/build-vs/Release/tos_baseline.exe --smoke slots --save-dir baseline/build-vs/slot-smoke
python baseline/tools/package.py
```

Smoke modes also include `initial`, `stairs`, `fight`, `capture`, `ending` and `floor10`,
plus `items`, `inventory`, `item`, `enemies`, `shop`, `flight`, `help` and `backside` for UI
inspection. Use an absolute `--screenshot FILE.png` path for a screenshot;
`--visible-smoke` shows the window while checking it. Screenshots capture the
logical canvas independently of desktop DPI. The Fairy smoke verifies autosave
and load. The ending smoke checks that the closing card pauses before continuing
to the backside. The audio test verifies all 17 tracks and writes a six-second sample.
The `slots` smoke writes all eight manual files, pauses a pending command under
the load picker, and restores a later-cycle save through the desktop actions.

GUI builds add `original_presentation` to CTest. It checks all 12 door modes,
both stair phases, all 32 Vampire frames, the capture/ending command sequences
and overlay rendering, with 131 checks including screenshot exports. Standing
poses and both walking poses are compared to the original atlas in all four
directions; held walking is checked at each speed. Enemy-panel checks cover
persistence through movement and hovering. Backside panel edges match the original
red artwork; Zeno variants and save/load pickers have rendered snapshots. Snapshots
and `presentation-report.json` go into `build-vs/presentation-checks`. Run the
same checks manually with `tos_baseline.exe --presentation-test OUTPUT_DIR`.

AddressSanitizer can be enabled with `-DBASELINE_SANITIZERS=ON`. On MSVC, use a
Release core build (`BASELINE_GUI=OFF`) and make the MSVC ASan runtime DLL
available on PATH. GCC/Clang builds also enable undefined-behavior checks.
Neither the regular nor sanitizer build requires the legacy game to run.

The package script copies static binaries, local extracted media, soundfont,
dependency licenses and clean differential reports, writes file hashes, and
creates a ZIP. See [THIRD_PARTY.md](THIRD_PARTY.md) for attribution and pins.
