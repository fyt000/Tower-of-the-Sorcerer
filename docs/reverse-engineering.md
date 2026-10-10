# Original source recovery and verification

The reference target is English **Tower of the Sorcerer for Windows 1.2**,
`TSW.exe`, with image base `0x400000`. Its hash and recovered classes are in the
[structural inventory](../reference/original/whole-program/structural-inventory.json).
The installed documentation identifies Delphi 2.0J Desktop; the exact compiler
and library patch remain unverified. See the [compiler guide](../reference/delphi2/README.md).

| Evidence | Coverage |
|---|---|
| [Presentation audit](../reference/original/presentation/REVIEW.md) | Five form resources; all 130 serialized event bindings resolve to source and assembly |
| [Whole-program audit](../reference/original/whole-program/REVIEW.md) | PE/CODE byte ledger and 3,298 machine-entry exports, including runtime and exception continuations |
| [Source index](../reference/original/decompiled/INDEX.md), [call map](../reference/original/decompiled/CALLS.md) | Gameplay entries and reviewed caller relationships |
| [C++ fidelity scope](../cpp/FIDELITY.md) | Behavioral comparisons, accepted differences, and remaining coverage limits |

Published-entry accounting does not establish complete Windows callback or
branch coverage. The whole-program ledger records unresolved bytes, ambiguous
ownership, indirect calls, and incomplete listing bodies. IDR recognition data
supplies names and byte shapes, not Pascal implementation source.

The program entry is a separate recovery boundary. `verify_delphi_entry.py`
compares normal launch and duplicate launch, including warning text, foreground
request, form order and exit. It executes entry decisions with Windows/VCL
observers; native process tests exercise the window-class check and warning.
`build_delphi_game.py --smoke` runs both. Unit initialization and complete
framework delivery remain outside this comparison.

## What the decompiler supplies

Ghidra exports inspection code. Review assembly for register arguments,
indirect calls, dynamic strings, and aliased flags before translating it.
`_140_4_` denotes decimal byte offset 140; `field_0x140` denotes hexadecimal.
The recovered arrival export repairs a missed two-level switch and supersedes
the incomplete initial export retained beside it.

From the repository root, use Ghidra's headless launcher with `tools/ghidra`:

```text
analyzeHeadless PROJECT_DIR original-tsw -import ORIGINAL_DIR/TSW.exe -scriptPath tools/ghidra -postScript ExportOriginal.java reference/original/decompiled
analyzeHeadless PROJECT_DIR original-tsw -process TSW.exe -noanalysis -scriptPath tools/ghidra -postScript RecoverArrival.java reference/original/decompiled/0046cb1c_arrival_recovered.c
analyzeHeadless PROJECT_DIR original-tsw -process TSW.exe -noanalysis -scriptPath tools/ghidra -postScript RecoverCallbacks.java reference/original/decompiled
analyzeHeadless PROJECT_DIR original-tsw -process TSW.exe -noanalysis -scriptPath tools/ghidra -postScript RecoverSaves.java reference/original/decompiled
```

`extract_original_ui.py`, `RecoverPresentation.java`, `RecoverUiRuntime.java`,
and `review_original_presentation.py` reproduce the presentation inventory.
The linked audits document their arguments and whole-program Ghidra commands.
Check the pinned IDR data and byte accounting with:

```powershell
python tools/fetch_idr_recognition.py
python tools/account_original_program.py --check
python tools/review_whole_program.py --check
python tools/test_whole_program_accounting.py
```

## Translate and compare

Preserve state-write timing, arithmetic, callback operands, and reversed command
insertion. Document intentional safety and presentation changes. The editable
Rust campaign is separate from the executable-derived constants.

After building C++, run the comparison pipeline from the repository root:

```powershell
python -m pip install -r tools/requirements.txt
$env:TOS_ORIGINAL_EXE = 'D:/Program Files (x86)/Tower of the Sorcerer/TSW.exe'
python cpp/tools/verify_original.py --probe build/cpp/vs/Release/tsw_probe.exe
```

The pipeline checks evidence freshness and combines `differential.py` with
`verify_interactions.py`, `verify_callbacks.py`, `verify_items.py`,
`verify_saves.py`, `verify_quirks.py`, `verify_flight.py`, and
`verify_presentation.py`. Each also accepts `--probe` for a focused comparison.
The tools emulate hash-pinned x86 handlers with Unicorn and compare state with
`tsw_probe.exe`; reports and fixtures are written under ignored `build/cpp/`.
The probe accepts `set`, `tile`, `call`, `input`, `step`, `trace`, and `snapshot`
commands through stdin/stdout.

Comparisons must record skipped calls and stopped execution ranges. A drawing
helper can change gameplay state: `0x442C38` also clears gameplay fields. Carrying
memory between callbacks and following that redraw exposed the Flight fault
documented in the [Flight audit](fidelity-audit-2026-10-09.md). Isolated fixture
counts do not establish a complete campaign, raster equality, or all framework
delivery paths; those boundaries are recorded in the linked fidelity report.

Refresh compiled maps, monsters, and text with
`python cpp/tools/extract_constants.py ORIGINAL_TSW.exe`. The C++ build uses
`cpp/tools/extract_ui.py` for embedded ending images and the eight Save/Load
menu pairs. See [data formats and asset extraction](original-data.md).
