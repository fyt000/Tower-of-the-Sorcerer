# Original game data and recovery

The reference target is English **Tower of the Sorcerer for Windows 1.2**.
Recovered evidence is indexed in [reference/original](../reference/original/README.md).
The original installation is read only; generated output belongs in `build/`.

## Assets and extraction

The supported EXE supplies **51 floor records, 33 monster rows, and 268
text strings**. A floor record contains two stair-landing bytes followed by
121 row-major tile IDs. C++ compiles these constants from the executable.

| Input | Content |
|---|---|
| `TSW.exe` map initializer | Floor layouts and stair landings |
| Monster table at file offset `0x88D10` | Shared HP, attack, defense, and gold rows |
| Delphi form string list | Dialogue and status text |
| `Data3/Chtable.oz`, `Chtableb.oz` | BMP sprite atlas and background masks |
| `Data3/*.bmp` | Panels, titles, and red backside variants |
| `Data2/End*.bmp` | Ending animation frames |
| `Midi/*.mid`, `Wav/*.wav` | Music and effects |
| `TTSW10.Image21`, `Image33` | Embedded ending story and card |

The C++ GUI uses Data3 artwork at a 40-pixel logical tile size and loads the
installation's media directly. PNG extraction supports the Rust UI and asset
comparisons; the alternate Data artwork and display preferences belong to the
Delphi game.

Delphi uses Windows MCI for MIDI; C++ synthesizes the same files with
TinySoundFont and embedded GeneralUser GS. Their playback can sound different.

Run extraction from the repository root:

```powershell
python -m pip install -r tools/requirements.txt
python tools/extract_original.py --source "D:/Program Files (x86)/Tower of the Sorcerer"
python cpp/tools/extract_ui.py --exe "D:/Program Files (x86)/Tower of the Sorcerer/TSW.exe"
```

`extract_original.py` preserves an existing editable Rust campaign unless
`--regenerate-campaign` is supplied. Source hashes are in
[extraction-manifest.json](../data/extraction-manifest.json); the form manifest
records bitmap hashes and reviewed offsets. Extracted media and executables
are excluded from Git. `extract_help.py` maintains Rust help from `TSW.txt` and
`Tsw.hlp`. Attribution and dependency licenses are in
[THIRD_PARTY.md](../THIRD_PARTY.md).

## Original saves

`Savedat/save1.dat` through `save8.dat` are little-endian records without a
header or serialized monster table. Writer entry: `0x47EADC`; loader: `0x47E7D4`.

| File offset | Bytes | Content |
|---|---:|---|
| `0` | 6,273 | 51 floor records |
| `6,273` | 684 | 171 signed 32-bit hero/state words |
| Total | **6,957** | Save record |

Hero byte offset 628 must be `-4`. Offsets 656 and 660 hold wrapping 32-bit
sums over the first 164 words: ordinary and alternating
`+word0 -word1 +word2 ...`. These checks exclude maps and the final hero words.
The C++ loader additionally validates mapped fields, tiles, and coordinate
bounds before replacing state, and preserves unmapped words when rewriting.
Trailing bytes are ignored, matching the fixed-size reads.

Loading rebuilds Zeno's shared HP/ATK/DEF row from cycle and seal flags:
unsealed `8000/5000/1000`; sealed `800/500/100 × (cycle_factor_minus_one + 1)`.
Combat applies cycle scaling again, preserving the backside load quirk.
Other monster rows come from constants.

The Fairy writes the same records to `Savedat/save0.dat` without updating
checksum words; recovery reads them without a checksum gate. The C++ checkpoint
is written after her scene finishes. F8 restores it with field and bounds
validation, while numbered slots require valid checksums. Slots use the
executable's `Savedat` directory or explicit `--save-dir`; see
[controls and saves](../cpp/README.md).

## Rankings

Fairy rankings have ten entries for each of 10F, 20F, 25F, 40F and 49F.
`option1.dat`–`option5.dat` hold 288-byte numeric records; matching
`option11.dat`–`option51.dat` files hold ten CRLF-separated names. C++ keeps
these in the save directory and restores a complete default table on invalid
input. Rankings are separate from game slots.

## Source recovery

Executable hashes and classes are recorded in the
[structural inventory](../reference/original/whole-program/structural-inventory.json).
Addresses use image base `0x400000`. The
[presentation review](../reference/original/presentation/REVIEW.md) and
[whole-program accounting](../reference/original/whole-program/REVIEW.md)
index recovered entries and unresolved regions. Compiler preparation is in
the [Delphi compiler guide](../reference/delphi2/README.md).

Ghidra output is an inspection aid. Check assembly for register arguments,
indirect calls, strings and aliased state before translating it. Preserve
state-write timing, arithmetic and reversed command insertion. A drawing
helper can also change gameplay state; comparisons must follow those effects.

Use Ghidra's headless launcher with scripts from `tools/ghidra`:

```text
analyzeHeadless PROJECT_DIR original-tsw -import ORIGINAL_DIR/TSW.exe -scriptPath tools/ghidra -postScript ExportOriginal.java reference/original/decompiled
analyzeHeadless PROJECT_DIR original-tsw -process TSW.exe -noanalysis -scriptPath tools/ghidra -postScript RecoverArrival.java reference/original/decompiled/0046cb1c_arrival_recovered.c
analyzeHeadless PROJECT_DIR original-tsw -process TSW.exe -noanalysis -scriptPath tools/ghidra -postScript RecoverCallbacks.java reference/original/decompiled
analyzeHeadless PROJECT_DIR original-tsw -process TSW.exe -noanalysis -scriptPath tools/ghidra -postScript RecoverSaves.java reference/original/decompiled
```

The linked reviews document presentation and whole-program extraction.
Check their retained accounting from the repository root:

```powershell
python tools/fetch_idr_recognition.py
python tools/account_original_program.py --check
python tools/review_whole_program.py --check
python tools/test_whole_program_accounting.py
```

## Comparison workflow

The [Delphi README](../delphi/README.md#formatting-and-verification) lists its
comparison tools. After building C++, run its original-handler suite from
the repository root:

```powershell
python -m pip install -r tools/requirements.txt
$env:TOS_ORIGINAL_EXE = 'D:/Program Files (x86)/Tower of the Sorcerer/TSW.exe'
python cpp/tools/verify_original.py --probe build/cpp/vs/Release/tsw_probe.exe
```

The suite emulates pinned x86 handlers and compares them with the compiled
probe. It checks evidence freshness and records skipped calls and execution
boundaries in `build/cpp/reports/`. Composed tests carry state between callbacks;
isolated handler agreement does not establish a complete campaign. Unknown
or effectful skipped calls are rejected, but aliased and transitive effects
still need assembly review. See [C++ fidelity](../cpp/FIDELITY.md) for limits.

Refresh compiled maps, monsters and text with
`python cpp/tools/extract_constants.py ORIGINAL_TSW.exe`. The C++ build uses
`cpp/tools/extract_ui.py` for embedded ending images and save/load menu resources.
