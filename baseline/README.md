# Original game baseline

A separate C++20 translation of the original English **Tower of the Sorcerer
1.2**. The purpose is faithful, readable game logic that can serve as a baseline
for later work. The original is Delphi/VCL; its C-like decompiler output and
machine code supply the evidence for this implementation.

The core uses explicit structs, enums, functions, switches, branches and loops.
The original callback IDs and three-word command stack retain their order.
raylib handles the desktop, rendering and audio device; TinySoundFont synthesizes
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
Set-Location baseline
& $cmake --preset windows
& $cmake --build --preset release -j 4
& $ctest --preset release
& ./build-vs/Release/tos_baseline.exe
```

The preset selects static x64 dependencies and the static MSVC runtime. CMake
pins dependency versions and download hashes. To use another original EXE path
after configuring, pass `-DBASELINE_ORIGINAL_EXE=PATH` when configuring again.
The original must match the supported 1.2 executable hash.

A headless core build needs only C++20 and CMake 3.25 or later:

```sh
cmake -S baseline -B baseline/build-headless -DBASELINE_GUI=OFF
cmake --build baseline/build-headless --config Release
ctest --test-dir baseline/build-headless -C Release --output-on-failure
```

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

Saves use `%APPDATA%/TosOriginalBaseline`; `--save-dir DIRECTORY` overrides it.
Save after the current action finishes. Eight manual files, `quick.save` and
`fairy.save` are independent. Replacement keeps a `.bak`, restores validate
before changing the live game, and the load picker pauses pending commands.

F7 also discovers `Savedat/save1.dat` through `save8.dat` beside the original
media, and `.dat` files in your chosen save directory. Your own slot file takes
precedence when both exist. Loading leaves the original file untouched; saving
that slot writes to your user save folder.

New files use the exact original **6,957-byte format**, including its checksums.
No monster table or extension is added. Loading rebuilds the shared Zeno row
using the original seal/cycle rules, including the legacy backside scaling quirk.
Earlier C++ `TOSB` v1 saves also import, with the same monster reconstruction;
the next save writes original records. [Save layout and behavior](../docs/original-data.md)
describe the fields and validation limits.

Open an arbitrary historical file, or convert an earlier C++ file for the old game:

```powershell
./build-vs/Release/tos_baseline.exe --load "D:/saved-games/save3.dat"
./build-vs/Release/tos_baseline.exe --load "D:/saved-games/quick.save" --export-original "D:/saved-games/save1.dat"
```

The export command exits without opening the GUI. To use a new save with the old
EXE, copy it into the original `Savedat/` folder as `save1.dat` through `save8.dat`.
Its file extension and the replacement executable's filename do not affect decoding.

## Validate and package

CTest covers the core and original-media renderer. When the extracted PNGs are
available, it also compares both asset layouts and runs the renderer with PNGs.
[The research workflow](../docs/reverse-engineering.md) describes the original
executable comparisons. Useful desktop checks include:

```powershell
./build-vs/Release/tos_baseline.exe --smoke ending --save-dir build-vs/smoke-saves
./build-vs/Release/tos_baseline.exe --smoke slots --save-dir build-vs/smoke-saves
./build-vs/Release/tos_baseline.exe --audio-test --screenshot build-vs/midi-test.wav
python tools/package.py --original-dir "D:/Program Files (x86)/Tower of the Sorcerer"
```

Packaging creates `dist/tos-original-baseline-0.3-windows-x64/TSW.exe` and a ZIP
with the original media layout, licenses and validation reports. The packaged
EXE can also be copied alone into an existing original installation. The smaller
`dist/tos-original-baseline-0.3-drop-in.zip` contains the EXE, usage notes and
licenses for that deployment.
