# Tower of the Sorcerer — C++

## Build on Windows

Use a Visual Studio developer shell with the C++ workload, Windows SDK, CMake,
clang-format, Python and vcpkg. From the repository root:

```powershell
$env:VCPKG_ROOT = 'C:/path/to/vcpkg'
$env:TOS_ORIGINAL_EXE = 'C:/path/to/original/TSW.exe'
python -m pip install pefile pillow
Set-Location cpp
cmake --preset windows
cmake --build --preset release -j 4
rg --files src include tests -g '*.cpp' -g '*.hpp' | ForEach-Object { clang-format -i --style=file $_ }
ctest --preset release -LE audio
& ../build/cpp/vs/Release/tsw_game.exe
```

The EXE must be the supported English 1.2 version. Alternatively configure
`-DTSW_ORIGINAL_EXE=PATH`. [Presets](CMakePresets.json) include ASan builds.

Headless build (C++23, CMake 3.25+), from the repository root:

```sh
cmake -S cpp -B build/cpp/core -DTSW_GUI=OFF
cmake --build build/cpp/core --config Release
ctest --test-dir build/cpp/core -C Release -LE audio --output-on-failure
```

## Android and browser builds

[Android APK and WebAssembly build guide](../docs/cross-platform.md) covers SDK
setup, asset extraction and commands. Both ports build only the game and its
runtime libraries. The browser build uses Emscripten with vcpkg, keeps saves in
IndexedDB, and offers exact save-file downloads. Android packages an ARM64 APK
(or x86-64 for an emulator), with saves in app-private storage and tap-to-walk
enabled for a fresh installation.

## Run and controls

Run beside the original `Data3/`, `Data2/`, `Midi/` and `Wav/` folders, or pass
`--assets DIRECTORY`. Preserve the original EXE when replacing an installation.
`--load FILE` starts from a save; `--save-dir DIRECTORY` overrides `Savedat/`.

| Control | Action |
|---|---|
| Arrows / WASD | Walk; hold to repeat |
| Map click | Blink or walk/contact a destination when the corresponding control is enabled |
| Enter / Space | Continue dialogue or ending |
| Item click / I | Inspect/use items / open inventory |
| Flight: Up/Down, Enter, Esc | Preview, travel, cancel |
| F6 / F7 | Manual save/load; select slot with 1–8 or arrows |
| F5 / F9 / F8 | Quick save / quick restore / Fairy checkpoint |
| F2 / M / R | New game / mute / rankings |
| Esc | Close overlay or open main menu |

Keyboard and touch directions step immediately, then repeat after a 250 ms hold
at 120 ms intervals, independently of animation speed. Menus and dialogue require
releasing a held direction before walking again. Above 1x, repeated sound effects
are consolidated, crossfaded and shortened; music and effect pitch retain their
normal playback rate.

Settings has Game, Controls, Replay and Language tabs. Controls groups Mouse walking,
Blink mode and Touch controls; Replay groups recording and playback speed. Game includes
music, animation speed, Item collection, Realtime Hero Orb and bonus-aware **Hero Orb actual damage**.
Mouse walking and both Orb options default off. Mouse
routes stop at unexpected events/hazards; other inputs cancel the route.
**Blink mode is for experienced players only** and defaults off. It takes precedence
over Mouse walking and enables map clicks by itself. Like TSWH5, it instantly crosses
connected event-free floor, or blinks beside the selected event and makes one normal
contact. It never crosses intervening doors, monsters, pickups, hidden tunnels or
hazards; when a safe blink is unavailable it falls back to ordinary mouse walking.
Adjacent clicks use ordinary contact. See the [source comparison](../docs/blink-mode.md).
Enable **Item collection** under **Settings → Game → Quality of life** to show the
two collection buttons and their background beneath the inventory. It defaults off.
The buttons use the original key, gem and potion sprites with a pixel collection arrow.
They provide **Zuck all** and **Zuck all except potion**.
The crossed-out potion badge identifies the second action; hover for names and explanations.
Each activation collects safely reachable pickups on the current floor and makes their
icons fly to the hero, who stays in place. The second button preserves both red and
blue potions; skipped potions remain barriers. Collection never opens doors, fights,
reveals hidden passages, crosses hazards or changes floors. It is available without
enabling Mouse walking or Blink mode. See [collection and replay notes](../docs/collection-qol.md).
See [languages](locales/README.md) for catalog IDs and `--language` overrides.

## Saves and replay

Manual slots are `save1.dat`–`save8.dat`, quick save is `quick.save`, and the
Fairy checkpoint is `save0.dat`. Saves retain the original format; replacement
keeps a `.bak`. Invalid loads preserve the running game. Rankings persist
independently; settings are in `settings.json`.

Copy `.replay.jsonl` and `.achievements.json` companions with a save to retain
recording and achievement history. Missing/invalid achievement history hides
unverified history-dependent awards without blocking loading.

Choose **Play replay** or pass `--replay FILE`. Enable **Record new games** or
`--record` before starting. [Replay controls, CLI and format](../docs/replay-verification.md).
Blink and collection record ordinary native movements, so replays show walking.

## Development

`tsw_core` owns state and the reverse-order command queue. Desktop, CLI, replay
and [MCP](../docs/cpp-mcp.md) share the input executor. Core logic is split among
`game.cpp`, `contact.cpp`, `combat.cpp`, `items.cpp`, `npcs.cpp`, `floor_checks.cpp`
and `scenes.cpp`; persistence uses `original_save.cpp` and `save*.cpp`.

Preserve command layout/order, numeric enum values and serialized keys
(`settings.cpp`, `runtime_schema.hpp`). Renderer resource owners must die before
the graphics context. Clang-format owns layout; see [AGENTS.md](../AGENTS.md)
for formatting and audio-test rules.

See [mechanics](../docs/mechanics.md), [fidelity](FIDELITY.md),
[research comparisons](../docs/decompilation.md#verification), and the optional
[route planner](../docs/route-planner.md).

## Validate and package

`tsw_tests` covers core/saves/replay/MCP; `tsw_verify` covers presentation/assets.
Packaging requires fresh research comparisons and renderer/window reports:

```powershell
python cpp/tools/package.py --original-dir "C:/path/to/original"
```

Output: `build/packages/`. [Dependency notices](THIRD_PARTY.md).
