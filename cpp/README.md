# Tower of the Sorcerer — C++

- [Mechanics](../docs/mechanics.md) and [fidelity notes](FIDELITY.md): game rules,
  intentional differences and verification limits.
- [Replay and CLI](../docs/replay-verification.md): recording, playback and inputs.
- [MCP](../docs/cpp-mcp.md): client setup, tools and worker reload.
- [Original data and recovery](../docs/original-data.md): assets, saves and comparisons.

## Build on Windows

Use a Visual Studio developer shell matching [the CMake presets](CMakePresets.json),
with the C++ workload, Windows SDK, CMake, clang-format, Python and vcpkg.
Python with `pefile` and Pillow extracts ending pictures during the build.
From the repository root:

```powershell
$env:VCPKG_ROOT = 'D:/projects/vcpkg'
$env:TOS_ORIGINAL_EXE = 'D:/Program Files (x86)/Tower of the Sorcerer/TSW.exe'
python -m pip install pefile pillow
Set-Location cpp
cmake --preset windows
cmake --build --preset release -j 4
rg --files src include tests -g '*.cpp' -g '*.hpp' | ForEach-Object { clang-format -i --style=file $_ }
ctest --preset release -LE audio
& ../build/cpp/vs/Release/tsw_game.exe
```

The source EXE must match the supported 1.2 hash. Override its path with
`-DTSW_ORIGINAL_EXE=PATH` when configuring. Build output and dependencies stay
under `build/`; `asan` presets select MSVC AddressSanitizer.

Headless builds need C++23 and CMake 3.25+. From the repository root:

```sh
cmake -S cpp -B build/cpp/core -DTSW_GUI=OFF
cmake --build build/cpp/core --config Release
ctest --test-dir build/cpp/core -C Release -LE audio --output-on-failure
```

Glaze and Catch2 are fetched if installed packages are unavailable.
`-DBUILD_TESTING=OFF` omits test runners and `tsw_verify`.

## Run and controls

Run `tsw_game.exe` beside the original `Data3/`, `Data2/`, `Midi/` and `Wav/`
folders, or select assets with `--assets DIRECTORY`. Extracted PNGs also work.
Ending pictures and the MIDI soundfont are embedded. When replacing an installed
EXE, preserve the original as `TSW.original.exe`.

The startup menu offers **New game**, **Load game**, **Play replay** and
**Settings**. Use the mouse or Up/Down and Enter. Esc returns to the menu;
**Continue** resumes the session. `--load FILE` starts from a save.

| Control | Action |
|---|---|
| Arrows / WASD | Walk; hold to repeat |
| Enter / Space | Continue dialogue or the ending card |
| Click an item / I | Inspect or use items / open inventory |
| Flight: Up / Down, Enter, Esc | Preview, travel, cancel |
| F6 / F7 | Eight manual save / load slots |
| Slot picker: 1–8 or arrows, Enter, Esc | Select, confirm, close |
| F5 / F9 / F8 | Quick save / quick restore / Fairy checkpoint |
| F2 / M | New game / mute |
| R / Game > Rankings | Open Fairy rankings |
| Esc | Main menu or close the current overlay |

Shop choices are clickable; Esc cancels. Dialogue and Wisdom clues scroll
with the wheel. Settings include speeds, recording, mute and **Hero Orb actual
damage**, an optional forecast that includes Cross and Dragon Slayer bonuses.

**Settings → Language** offers original English, original Japanese, English
retranslated from Japanese, simplified Chinese retranslated from Japanese, and
simplified Chinese translated from current English. Chinese item and monster
names follow TSWH5. Use `--language ja`, `en-ja`, `zh-Hans-ja`, `zh-Hans-en` or `en`
to override the saved language for one launch. See the
[translation sources and catalogs](locales/README.md) for extracted text and
alignment notes.

## Saves and recording

Saves and `settings.json` live in `Savedat/` beside the executable, overridden
by `--save-dir DIRECTORY`. Manual slots use `save1.dat`–`save8.dat`, quick save
uses `quick.save`, and the Fairy checkpoint uses `save0.dat`. Save after the
current action finishes. Replacement keeps a `.bak`; invalid loads preserve
the running game.

Game saves and Fairy ranking tables retain their original formats. Rankings
survive game loads and new cycles. Legacy preferences are not imported.
See [data formats](../docs/original-data.md#original-saves) for file layouts.

## Visual replay, recording and headless CLI

Choose **Play replay** or launch with `--replay FILE`. Enable **Record new
games** or `--record` before a fresh game. Recorded saves have a
`.replay.jsonl` companion; copy both files when moving a save.

| Replay control | Action |
|---|---|
| Space | Pause/resume |
| Left / Right | Previous boundary / finish the next input, then pause |
| Home | Restart paused |
| T | Take over |
| − / + | Change speed |
| O / Esc | Settings / main menu |

`tsw_cli` works without media or an audio device. From the repository root:

```powershell
./build/cpp/vs/Release/tsw_cli.exe state
./build/cpp/vs/Release/tsw_cli.exe replay tests/replays/first-floor-door.jsonl --limit 3
./build/cpp/vs/Release/tsw_cli.exe mcp
```

See [replay and CLI](../docs/replay-verification.md) for recording rules and
[MCP](../docs/cpp-mcp.md) for client configuration.

## Development

`tsw_core` owns game state and executes queued commands without graphics,
audio or Windows dependencies. Actions append opcode/operand records, executed
newest first. Combat produces bounded turns. `DesktopSession` schedules these
commands; CLI, replay and MCP share input execution.

| Files under `cpp/` | Responsibility |
|---|---|
| `include/tsw/game.hpp`, `src/game.cpp` | State, movement, command interpreter and cycles |
| `src/contact.cpp`, `src/combat.cpp`, `src/items.cpp`, `src/npcs.cpp` | Encounters, combat, items and dialogue |
| `src/floor_checks.cpp`, `src/scenes.cpp` | Floor triggers and story scripts |
| `src/original_save.cpp`, `src/save*.cpp`, `src/rankings.cpp` | Persistence |
| `src/desktop.cpp`, `src/presentation.cpp`, `src/assets.cpp` | Window loop, rendering and media |
| `src/audio.cpp`, `src/audio_mixer.cpp` | Audio device and prepared MIDI/effect playback |

## Validate and package

After a successful build, run the formatting command above from `cpp/`.
Run `ctest -LE audio` unless changes touch audio code, assets, dependencies or
configuration. See [AGENTS.md](../AGENTS.md) for the repository rules.

`tsw_tests` covers the core, saves, replay and MCP; `tsw_verify` checks desktop
presentation and assets. Research comparisons use `tsw_probe`, as described
in the [recovery guide](../docs/original-data.md#comparison-workflow).
Fixtures belong under `tests/`, generated reports under `build/`.

Packaging requires current research comparisons and CTest renderer, asset and
window reports. From the repository root:

```powershell
python cpp/tools/package.py --original-dir "D:/Program Files (x86)/Tower of the Sorcerer"
```

Packages go under `build/packages/`, with full-media and drop-in ZIPs.
See [third-party notices](THIRD_PARTY.md) for attribution and licenses.
