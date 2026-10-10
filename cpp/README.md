# Tower of the Sorcerer — C++

C++23 rewrite of the English **Tower of the Sorcerer 1.2**, with architecture
similar to the Delphi 2 game and the same core game logic, plus new features
and quality-of-life improvements. See
[architecture](../docs/architecture.md) for module responsibilities and
[fidelity notes](FIDELITY.md) for evidence and known differences.

## Build on Windows

Use a Visual Studio 2026 developer shell with the C++ workload, Windows SDK,
CMake, CTest, clang-format and Python on PATH, plus vcpkg.
Python with `pefile` and Pillow extracts ending pictures at build time; the game
has no Python dependency. From the repository root:

```powershell
$env:VCPKG_ROOT = 'D:/projects/vcpkg'
$env:TOS_ORIGINAL_EXE = 'D:/Program Files (x86)/Tower of the Sorcerer/TSW.exe'
python -m pip install pefile pillow
Set-Location cpp
cmake --preset windows
cmake --build --preset release -j 4
ctest --preset release -LE audio
& ../build/cpp/vs/Release/tsw_game.exe
```

The configured source EXE must match the supported 1.2 hash. Change its path with
`-DTSW_ORIGINAL_EXE=PATH` when configuring again. Build outputs and downloaded
dependencies stay under `build/`; `asan` presets select MSVC AddressSanitizer.

Headless builds need C++23 and CMake 3.25+. Pinned Glaze and Catch2 sources are
fetched when installed packages are unavailable:

```sh
cmake -S cpp -B build/cpp/core -DTSW_GUI=OFF
cmake --build build/cpp/core --config Release
ctest --test-dir build/cpp/core -C Release -LE audio --output-on-failure
```

`-DBUILD_TESTING=OFF` omits test runners and `tsw_verify`.

## Original folder compatibility

Run the executable beside `Data3/`, `Data2/`, `Midi/` and `Wav/`, using any EXE
filename. BMP/OZ assets load directly; ending pictures and the MIDI soundfont
are embedded. The source EXE is needed only for builds and research. Preserve it
as `TSW.original.exe` when replacing an installed game.

Extracted PNGs are also supported. `--assets DIRECTORY` selects either layout;
otherwise lookup checks the executable directory, its `assets/` subdirectory,
then development locations. An invalid explicit path is an error. Game saves
and ranking tables are compatible; legacy preferences are not imported.

## Audio and window behavior

M mutes music and effects. New/load actions restart the selected track; track
zero in a save disables music. The first-floor MIDI starts with about three
seconds of silence. The 800×558 canvas scales proportionally with the window
and DPI; artwork uses point filtering. [Desktop and media architecture](../docs/architecture.md#desktop-and-media)
describes the renderer and audio implementation.

## Startup, controls and saves

The startup menu offers **New game**, **Load game**, **Play replay** and
**Settings**. Select with the mouse or Up/Down and Enter. Returning home pauses
the session and offers **Continue**. `--load FILE` enters a saved game directly.

Settings live in `Savedat/settings.json` or `--save-dir DIRECTORY`. They cover
game/replay speed, recording, mute and **Hero Orb actual damage**. That QOL option
is off by default; enabling it includes Cross and Dragon Slayer bonuses in Orb
forecasts. Its badge explains the active option.

| Control | Action |
|---|---|
| Arrows / WASD | Walk; hold to repeat |
| Enter / Space | Continue dialogue or the ending card |
| Left item sprites / I | Inspect or use items / open inventory |
| Flight: Up / Down, Enter, Esc | Preview, travel, cancel |
| F6 / F7 | Eight manual save / load slots |
| Slot picker: 1–8 or arrows, Enter, Esc | Select, confirm, close |
| F5 / F9 / F8 | Quick save / quick restore / Fairy checkpoint |
| F2 / M | New game / mute |
| R / Game > Rankings | Open Fairy rankings |
| Esc | Main menu or close the current overlay |

Shop choices are clickable; Esc cancels. Dialogue and Wisdom clues scroll with
the wheel. The enemy panel retains the last defeated enemy's encounter stats.

Saves live beside the executable in `Savedat/`, overridden by `--save-dir`:
`save1.dat`–`save8.dat`, independent `quick.save`, and Fairy `save0.dat`.
Save after the current action finishes. Replacement keeps a `.bak`; loads
validate before changing the game. No other directories or old filenames are
searched. Manual/quick saves retain the 6,957-byte checksummed format; Fairy
checkpoints retain raw checksum words. [Save layout and reconstruction](../docs/original-data.md)
covers Zeno loading rules and checkpoint validation.

Fairy rankings have ten entries for each of 10F, 20F, 25F, 40F and 49F. Qualifying
first-cycle encounters allow name submission. Left/Right selects a category,
Enter submits, and Esc closes. **Reset category** confirms before restoring its
defaults. Tables use `option1.dat`–`option5.dat` and corresponding
`option11.dat`–`option51.dat` name files in the save directory: 288-byte numeric
records and ten CRLF name lines. Invalid files use the complete default table.
Rankings survive game loads and new cycles; replay watching cannot change them.

## Visual replay, recording and headless CLI

Choose **Play replay** to select, paste or drop a JSONL file, or launch with
`--replay FILE`. Enable **Record new games** or `--record` before a fresh game.
[Recording, save companions and CLI](../docs/replay-verification.md) documents
branch restoration, playback behavior and the JSONL contract.

| Replay control | Action |
|---|---|
| Space | Pause/resume gameplay, animation and audio |
| Left / Right | Reconstruct the previous boundary / finish one input, then pause |
| Home | Restart paused |
| T | Take over, including an animation in progress |
| − / + | Change replay and animation speed |
| O / Esc | Settings / main menu |

Replay speeds are 0.25x, 0.5x, 1x, 2x, 3x, 5x and 10x. Controls also appear in
the top bar. `tsw_cli` is built even with `TSW_GUI=OFF` and needs no media or
audio device. From the repository root:

```powershell
./build/cpp/vs/Release/tsw_game.exe --replay tests/replays/first-floor-door.jsonl
./build/cpp/vs/Release/tsw_cli.exe state
./build/cpp/vs/Release/tsw_cli.exe replay tests/replays/first-floor-door.jsonl --limit 3
```

## Native MCP mode

```powershell
./build/cpp/vs/Release/tsw_cli.exe mcp
```

[MCP tools and bridge operation](../docs/cpp-mcp.md) covers observations,
navigation, saves, replay, developer mode and worker hot reload.

## Validate and package

Run `ctest -LE audio` unless changes touch audio code, assets, dependencies or
configuration. The audio label also covers desktop scenarios that open a device;
renderer/window checks remain available. From `cpp/`:

```powershell
../build/cpp/vs/Release/tsw_tests.exe "[combat]"
../build/cpp/vs/Release/tsw_verify.exe --window ../build/cpp/vs/window-checks
```

After a successful build, format all C++ sources, headers and tests, including
generated constants, with `cpp/.clang-format`:

```powershell
rg --files src include tests -g '*.cpp' -g '*.hpp' | ForEach-Object { clang-format -i --style=file $_ }
```

`tsw_game --screenshot FILE` captures the initial frame. Test fixtures, reports
and screenshots belong under `tests/` and `build/`. [Replay checks](../docs/replay-verification.md#focused-checks)
and [the research workflow](../docs/reverse-engineering.md) describe their tools.

```powershell
python tools/package.py --original-dir "D:/Program Files (x86)/Tower of the Sorcerer"
```

Packaging requires current research comparisons in `build/cpp/reports/` and
CTest renderer/asset/window reports. It creates
`build/packages/tower-of-the-sorcerer-0.9-windows-x64/` and its full-media ZIP;
`tower-of-the-sorcerer-0.9-drop-in.zip` contains the EXE, usage notes and licenses
for an existing installation. See [third-party notices](THIRD_PARTY.md).
