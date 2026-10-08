# Original game baseline

A separate C++23 translation of the original English **Tower of the Sorcerer
1.2**. The purpose is faithful, readable game logic that can serve as a baseline
for later work. The original is Delphi/VCL; its C-like decompiler output and
machine code supply the evidence for this implementation.

The core uses explicit structs, enums, functions, switches, branches and loops.
The original callback IDs and three-word command stack retain their order.
raylib handles graphics; miniaudio owns the audio device; TinySoundFont synthesizes
the original MIDI tracks. There is no runtime JSON campaign or event framework.
Read [the architecture](../docs/architecture.md) and [fidelity notes](FIDELITY.md)
for the implementation boundaries and evidence.

## Build on Windows

Use Visual Studio 2026 with the C++ workload, CMake, Windows SDK and vcpkg.
Python with `pefile` and Pillow is used at build time to recover the two ending
pictures stored in the original EXE. The game itself has no Python dependency.
From the repository root:

```powershell
$env:VCPKG_ROOT = 'D:/projects/vcpkg'
$env:TOS_ORIGINAL_EXE = 'D:/Program Files (x86)/Tower of the Sorcerer/TSW.exe'
$cmake = 'C:/Program Files/Microsoft Visual Studio/18/Community/Common7/IDE/CommonExtensions/Microsoft/CMake/CMake/bin/cmake.exe'
$ctest = 'C:/Program Files/Microsoft Visual Studio/18/Community/Common7/IDE/CommonExtensions/Microsoft/CMake/CMake/bin/ctest.exe'
python -m pip install pefile pillow
Set-Location cpp
& $cmake --preset windows
& $cmake --build --preset release -j 4
& $ctest --preset release
& ../build/cpp/vs/Release/tsw_game.exe
```

Builds, reports and dependencies live under the repository root `build/`.
The `asan` configure/build/test presets enable MSVC AddressSanitizer in
`build/cpp/asan/`. The preset selects static x64 dependencies and the static MSVC runtime. CMake
pins dependency versions and download hashes. To use another original EXE path
after configuring, pass `-DTSW_ORIGINAL_EXE=PATH` when configuring again.
The original must match the supported 1.2 executable hash.

A full or headless build needs a C++23 compiler and CMake 3.25 or later.
Replay serialization uses Glaze 7.2.2; tests use Catch2 3.13. CMake fetches
pinned sources when installed packages are unavailable:

```sh
cmake -S cpp -B build/cpp/core -DTSW_GUI=OFF
cmake --build build/cpp/core --config Release
ctest --test-dir build/cpp/core -C Release --output-on-failure
```

Use `-DBUILD_TESTING=OFF` to omit Catch2 runners and the desktop verification executable.
The game and its libraries contain no test fixtures or verification code.

## Original folder compatibility

The Windows executable can keep any filename, including `TSW.exe`, and run beside the
original `Data3/`, `Data2/`, `Midi/` and `Wav/` folders. It loads the original
BMP and `.oz` files directly, preserving their filenames and masks. The ending
pictures and MIDI soundfont are embedded, so no conversion, `assets/` directory,
external soundfont or original EXE is needed at runtime.

Keep the original EXE as `TSW.original.exe` if replacing it; it remains the
input for decompilation and future builds. Development and tests do not overwrite
the installed game. Compatibility covers media, folder layout and original
`.dat` game saves. Original rankings and settings are not imported.

The extracted PNG layout is also supported: place it in `assets/` beside the
executable, or use `--assets DIRECTORY` with either layout. Selection checks the
executable's directory first, then its `assets/` directory, then the development
original/extracted locations. An explicit invalid path reports an error.

## Audio and window behavior

The audio callback owns the synth and playback cursors. The game thread publishes
track/pause/mute state through a lock-free atomic value and queues effects in a
fixed ring. MIDI messages, 256 synth voices, 16 channels and WAV samples are
loaded before the device starts. Track changes and loops reset channels in place;
the callback takes no mutex and allocates or frees no memory. Each WAV has 16
preallocated overlapping voices. TSF/TML and GeneralUser GS remain pinned; music
is synthesized during playback rather than cached as a full PCM soundtrack.

A new game starts music before its first frame, and new/load actions restart the
selected track even if it has the same ID. The original first-floor MIDI includes
roughly three seconds of silence before its first notes. A save with music track
zero retains the original disabled-music setting. M mutes both music and effects.

The 800×558 logical canvas fits the window while retaining its proportions.
Its render target uses the displayed physical pixel resolution. Fonts are
rasterized at the required pixel size and positioned on pixel boundaries; they
remain sharp when the canvas grows or shrinks. Original artwork retains point
filtering. Rendering queries window and framebuffer sizes every frame; maximize,
restore and DPI changes share the same mapping as mouse input.

## Startup, controls and saves

Startup shows the original tower background with a plain text menu on the left:
**New game**, **Load game**, **Play replay** and **Settings**. Use the mouse or Up/Down and Enter.
Returning to the main menu pauses gameplay and adds **Continue game** or
**Continue replay**. Load game shows the eight original slots plus Quick and Fairy
restore buttons. `--load FILE` and `--replay FILE` enter their respective modes directly.

Settings persist in `Savedat/settings.json`, or the directory selected by `--save-dir`.
They cover walking/animation speed, replay/animation speed, recording and audio mute.
These are replacement-game preferences; original settings are not imported.

| Control | Action |
|---|---|
| Arrows / WASD | Walk; hold to repeat |
| Enter / Space | Continue dialogue or the ending card |
| Left item sprites / I | Inspect or use items / open inventory |
| Flight: Up / Down, Enter, Esc | Preview, travel, cancel |
| F6 / F7 | Eight manual save / load slots |
| Slot picker: 1–8 or arrows, Enter, Esc | Select, save/replace/load, close |
| F5 / F9 / F8 | Quick save / quick restore / Fairy checkpoint |
| F2 / M | New game / mute music and effects |
| Esc | Main menu, or close/cancel the current overlay |
| Options / Settings | Game speed, replay speed, audio and opt-in recording |

Shop choices are clickable; Esc cancels a shop. Long dialogue and Wisdom clues
scroll with the mouse wheel. Hero Orb forecasts have their own overlay. The
bottom-right panel retains the last defeated enemy's encounter-time stats.

Saves use `Savedat/` beside the executable; `--save-dir DIRECTORY` overrides it.
Save after the current action finishes. Eight manual files, `quick.save` and
the original Fairy `save0.dat` are independent. Replacement keeps a `.bak`, restores validate
before changing the live game, and the load picker pauses pending commands.

F6 and F7 write and read the same `save1.dat` through `save8.dat` files in that
directory. Replacing the original EXE therefore shares its existing slots
directly. There is no separate slot type, import step, AppData search or lookup
of older C++ filenames. Reading a slot leaves it unchanged; saving replaces that
file and retains its previous contents as a `.bak`.

Manual and quick files use the exact original **6,957-byte format**, including its checksums.
No monster table or extension is added. Loading rebuilds the shared Zeno row
using the original seal/cycle rules, including the legacy backside scaling quirk.
Fairy checkpoints use the same two records in `Savedat/save0.dat`, written
without refreshing the checksum words, as in the original. F8 reads that raw
checkpoint with bounds validation. [Save layout and behavior](../docs/original-data.md)
describe both record uses and validation limits.

Open a specific manual or quick save file:

```powershell
../build/cpp/vs/Release/tsw_game.exe --load "D:/saved-games/save3.dat"
```

Numbered saves have the format, filename and location the original EXE expects. The replacement
executable's filename does not affect saving or loading.

## Visual replay, recording and headless CLI

Enable **Settings > Record new games** before starting a game, or start with
`--record` to override the stored preference for that launch. While recording,
manual, quick and Fairy saves each get a
`.replay.jsonl` companion. With the option enabled, loading that save resumes its
saved history. Loading a save without a companion leaves that loaded game
unrecorded, including later saves. Turning the option off stops recording immediately.
Keep a save and its companion together when copying them. Original save bytes
and raw Fairy handling remain unchanged.

Choose **Play replay** to select a `.jsonl` recording from the save directory,
paste/type its path, or drop it onto the window. Explorer's quoted paths work too.
Playback uses the real command scheduler and original animations/cutscenes.
Non-choice dialogue and the ending card continue after a short display delay;
shops execute the choices recorded by the player. Watching runs save and reload
boundaries in memory, preserving the original save behavior.

| Replay control | Action |
|---|---|
| Space | Pause/resume commands, sprite animation and audio |
| Left / Right | Previous command boundary / finish one command, then pause |
| Home | Restart from the initial boundary, paused |
| T | Take over the current game, including an animation in progress |
| − / + | Change replay and animation speed |
| O / Esc | Settings / main menu |

The same controls appear in the top bar. Speeds are **0.25x, 0.5x, 1x, 2x, 3x,
5x and 10x**. A step means one recorded input, including new-game and save/load
boundaries; it is not one animation frame. Next finishes an input already in
progress. Previous reconstructs the earlier prefix through real gameplay instead
of storing snapshots, so long rewinds can take longer. A completed replay stays
paused for inspection or takeover. Playback failures show the affected step.

Takeover keeps the consumed prefix when recording is enabled; later saves write
that prefix plus the new decisions. With recording off it continues unrecorded.
Watching does not overwrite manual, Quick or Fairy saves. Rewinding restarts the
selected music track rather than restoring its elapsed MIDI time.

```powershell
./build/cpp/vs/Release/tsw_game.exe --replay tests/replays/first-floor-door.jsonl
```

`tsw_cli` is a separate headless executable, built even with `TSW_GUI=OFF`. It needs
no assets, soundfont or audio device. From the repository root:

```powershell
./build/cpp/vs/Release/tsw_cli.exe state
./build/cpp/vs/Release/tsw_cli.exe replay ./build/cpp/vs/Release/Savedat/save1.dat.replay.jsonl
./build/cpp/vs/Release/tsw_cli.exe replay tests/replays/first-floor-door.jsonl --limit 3
```

The CLI prints readable JSON values and can inspect remote map tiles with
`--map-floor N`. Its `headless` mode accepts commands on stdin and prints values
after each one. [Recording behavior, commands and focused checks](../docs/replay-verification.md)
describe save branching, original reload behavior and the external assertion tool.
The Rust comparison adapter is later work; the C++ recorder does not impose a
common internal representation on either engine.

## Native MCP mode

`tsw_cli mcp` serves the C++ game directly over stdio, including visible state,
tile inspection, Hero Orb forecasts, dialogue choices/clues, destination
navigation, save/load and JSONL replay import/export. Compact observations group
event descriptions and forecasts by type; routine actions return resource and
tile changes. `detail: "full"` provides raw maps, history and item usage help.
`--developer` additionally enables native diagnostics, all-floor observations
in full detail and isolated action simulations. It uses the same core,
original save format and player inputs as the desktop, with no Node runtime:

```powershell
./build/cpp/vs/Release/tsw_cli.exe mcp
./build/cpp/vs/Release/tsw_cli.exe mcp --load ./Savedat/save1.dat
./build/cpp/vs/Release/tsw_cli.exe mcp --developer
```

Session checkpoints can retain open shops and Flight previews. Supply a path to
save an original `.dat` with a replay companion for persistence after disconnect.
Replays can run a whole recording or a prefix, followed by live takeover.
For hot reload, publish a worker and configure the client to launch the Python
bridge (Python 3.10+, standard library only):

```powershell
python cpp/tools/build_mcp.py --build-dir build/cpp/vs
python cpp/tools/mcp_server.py --developer
```

Republishing replaces the worker before its next request while the bridge stays
connected. The complete session transfers, including open shops, Flight,
recording and checkpoint IDs. Workers run immutable executable copies, allowing
rebuilds on Windows. `mcp_runtime` exposes deployment, process IDs and reload
health. Failed candidates retain the old worker; actions are never retried.
[MCP tools, observations, client configuration and save/replay behavior](../docs/cpp-mcp.md)
describe the native interface and Python publication/reload workflow.

## Validate and package

Catch2 runs core cases in `tsw_tests` and offline playback cases in `tsw_audio_tests`.
The audio tests drive the same `AudioMixer` used by the native device callback:
complete MIDI tracks and loops, startup, pause/resume, mute, same-track restart,
WAV overlap and queue bursts. Queue tests also exercise concurrent producer/consumer
use and unsigned index rollover. The MSVC Debug runner uses the CRT debug heap
hook to check allocations, reallocations and frees during prepared rendering;
that hook exists only in the test source. Release and ASan run the functional tests.
The native-device case checks initialization, control changes and shutdown,
without asserting audible output or adding diagnostic fields to playback.

`tsw_verify` owns renderer, window, asset and desktop scenario checks. Its fixtures,
assertions, reports and generated screenshots live under `tests/` and `build/`.
Desktop scenarios use the same `DesktopSession` actions and command scheduling as
the game, including menus, persistent settings, replay stepping/rewind/takeover,
death, shops, dialogue, ending pauses and Fairy checkpoint writes. Replay tests
compare animated and headless observations, native save bytes after takeover,
and save files before and after watching. Audio tests check that replay suspension
freezes both music and effect cursors.
Both verification executables are built only with `BUILD_TESTING=ON`.

CTest discovers each named Catch2 case and invokes the desktop checks separately.
When the extracted PNGs are available, it also compares both asset layouts and
runs the renderer with PNGs. The runners support named tests, tags, value diagnostics
and standard report formats. Useful commands from `cpp/`:

```powershell
../build/cpp/vs/Release/tsw_tests.exe "[combat]"
../build/cpp/vs/Release/tsw_audio_tests.exe "[playback]"
../build/cpp/vs/Release/tsw_audio_tests.exe "[device]"
& $cmake --build --preset debug -j 4
../build/cpp/vs/Debug/tsw_audio_tests.exe "[allocation]"
../build/cpp/vs/Release/tsw_verify.exe --smoke all --output ../build/cpp/vs/desktop-checks
../build/cpp/vs/Release/tsw_verify.exe --window ../build/cpp/vs/window-checks
python tools/package.py --original-dir "D:/Program Files (x86)/Tower of the Sorcerer"
```

The game accepts ordinary asset/save/load options and `--screenshot FILE` to capture
its initial frame. Verification flags and injected fixtures belong to `tsw_verify`.
[The research workflow](../docs/reverse-engineering.md) describes the separate
`tsw_probe` adapter and original executable comparisons.

All C++ sources, headers and tests follow `cpp/.clang-format`, including the
generated original constants. After a successful build, run clang-format across the complete C++ tree.
`SeparateDefinitionBlocks: Always` inserts blank lines between definitions,
including inline member functions; ordinary declarations retain compact spacing.
Format generated constants after regenerating them as well. From `cpp/`, format the complete C++ tree with:

```powershell
$formatter = 'C:/Program Files/Microsoft Visual Studio/18/Community/VC/Tools/Llvm/x64/bin/clang-format.exe'
rg --files src include tests -g '*.cpp' -g '*.hpp' | ForEach-Object { & $formatter -i --style=file $_ }
```

Packaging creates `build/packages/tower-of-the-sorcerer-0.9-windows-x64/TSW.exe` and a ZIP
with the original media layout, licenses and validation reports. The packaged
EXE can also be copied alone into an existing original installation. The smaller
`build/packages/tower-of-the-sorcerer-0.9-drop-in.zip` contains the EXE, usage notes and
licenses for that deployment.

Packaging requires the original comparisons from the research workflow in
`build/cpp/reports/`, plus the CTest renderer, asset and window reports from the
selected build. Those generated reports are excluded from Git.
