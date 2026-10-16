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
installation's media directly. PNG extraction into `build/assets/` supports the
C++ fallback loader and asset comparisons. The alternate Data artwork and display
preferences belong to the Delphi game.

Delphi uses Windows MCI for MIDI; C++ synthesizes the same files with
TinySoundFont and embedded GeneralUser GS. Their playback can sound different.

Run extraction from the repository root:

```powershell
python -m pip install -r tools/requirements.txt
python tools/prepare_research.py --source "D:/Program Files (x86)/Tower of the Sorcerer"
```

`extract_original.py` preserves the existing `data/campaign.json` research fixture
unless `--regenerate-campaign` is supplied. Campaign, event and interaction JSON
remain inputs to recovery audits and Delphi checks; the C++ runtime uses its
compiled constants and game logic. These JSON files are local generated inputs,
not tracked source. The preparation command recovers events before assembling a
new campaign; existing editable campaigns are preserved. Source identity is in
[extraction-manifest.json](../data/extraction-manifest.json); the form manifest
records bitmap hashes and reviewed offsets. Extracted media and executables
are excluded from Git. `extract_help.py` preserves original help evidence from
`TSW.txt` and `Tsw.hlp` in `data/help/original.json`.
Attribution and dependency licenses are in
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

The [Delphi recovery status](../delphi/README.md#recovery-status) records the
current Pascal reconstruction, routine comparisons and remaining limits.
All 230 published methods have recovered bodies and reviewed boundaries.

Recovery tools use a local copy of the supported original executable at
`build/research/TSW.exe`. Prepare it from your installation before running the
accounting or Delphi comparison tools:

```powershell
New-Item -ItemType Directory -Force build/research | Out-Null
Copy-Item -LiteralPath 'D:/Program Files (x86)/Tower of the Sorcerer/TSW.exe' -Destination build/research/TSW.exe
```

The extracted source, assembly, manifests and machine reports under `reference/`
are ignored local caches. Authored review documents, Pascal probes and recovery
policies remain tracked. Use [research cache setup](research-cache.md) for the
preparation command and [the compiler guide](../reference/delphi2/README.md#reproduction)
for Delphi compiler inputs. Evidence links in this guide resolve after preparation.

Executable hashes and classes are recorded in the
[structural inventory](../reference/original/whole-program/structural-inventory.json).
Addresses use image base `0x400000`. The
[presentation review](../reference/original/presentation/REVIEW.md) and
[whole-program accounting](../reference/original/whole-program/REVIEW.md)
retain the earlier decompilation inventories and unresolved executable regions.
Compiler preparation is in the [Delphi compiler guide](../reference/delphi2/README.md).

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

The [Delphi README](../delphi/README.md#verification) lists its
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
