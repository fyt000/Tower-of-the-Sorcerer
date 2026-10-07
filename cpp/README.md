# Original game baseline

A separate C++20 translation of the original English **Tower of the Sorcerer
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

A headless core build needs C++20 and CMake 3.25 or later. Tests use Catch2 3.13;
CMake fetches the pinned source when no installed Catch2 package is available:

```sh
cmake -S cpp -B build/cpp/core -DTSW_GUI=OFF
cmake --build build/cpp/core --config Release
ctest --test-dir build/cpp/core -C Release --output-on-failure
```

Use `-DBUILD_TESTING=OFF` to build the core and research probe without Catch2.

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

## Controls and saves

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
| Options menu | 1×, 3× or 10× walking and animation speed |

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

## Validate and package

CTest discovers each named Catch2 core case and runs the MIDI, renderer and asset
checks separately. The core cases use the actual `Game` API and complete command
playback. When the extracted PNGs are available, CTest also compares both asset
layouts and runs the renderer with PNGs. Run a subset directly with
`../build/cpp/vs/Release/tsw_tests.exe "[combat]"`; the runner supports named tests,
tags, expression/value diagnostics and standard report formats.
[The research workflow](../docs/reverse-engineering.md) describes the original
executable comparisons. Useful desktop checks include:

```powershell
../build/cpp/vs/Release/tsw_game.exe --smoke ending --save-dir ../build/cpp/vs/smoke-saves
../build/cpp/vs/Release/tsw_game.exe --smoke slots --save-dir ../build/cpp/vs/smoke-saves
../build/cpp/vs/Release/tsw_game.exe --audio-test --screenshot ../build/cpp/vs/midi-test.wav
../build/cpp/vs/Release/tsw_game.exe --audio-device-test
../build/cpp/vs/Release/tsw_game.exe --window-test ../build/cpp/vs/window-checks
python tools/package.py --original-dir "D:/Program Files (x86)/Tower of the Sorcerer"
```

All C++ sources, headers and tests follow `cpp/.clang-format`, including the
generated original constants. After regenerating constants, format that header
again. From `cpp/`, format the complete C++ tree with:

```powershell
$formatter = 'C:/Program Files/Microsoft Visual Studio/18/Community/VC/Tools/Llvm/x64/bin/clang-format.exe'
rg --files src include tests -g '*.cpp' -g '*.hpp' | ForEach-Object { & $formatter -i --style=file $_ }
```

Packaging creates `build/packages/tower-of-the-sorcerer-0.8-windows-x64/TSW.exe` and a ZIP
with the original media layout, licenses and validation reports. The packaged
EXE can also be copied alone into an existing original installation. The smaller
`build/packages/tower-of-the-sorcerer-0.8-drop-in.zip` contains the EXE, usage notes and
licenses for that deployment.

Packaging requires the original comparisons from the research workflow in
`build/cpp/reports/`, plus the CTest renderer, asset and window reports from the
selected build. Those generated reports are excluded from Git.
