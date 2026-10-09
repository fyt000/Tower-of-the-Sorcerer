# Original source recovery and verification

The [presentation/input audit](../reference/original/presentation/REVIEW.md)
adds structural recovery of five Delphi form resources, published methods and
control fields. All 130 serialized event bindings now resolve to recovered
source and assembly. This is distinct from complete branch or Windows callback
coverage. `tools/extract_original_ui.py`, `RecoverPresentation.java`,
`RecoverUiRuntime.java`, and `tools/review_original_presentation.py` reproduce
the recovery and its effect inventory; the full comparison pipeline checks
that inventory for staleness.
The [recovery scope](../reference/original/presentation/RECOVERY-SCOPE.md)
distinguishes complete published-entry accounting from unexported runtime
targets, indirect calls and the absence of a whole-executable recovery claim.

The [whole-program audit](../reference/original/whole-program/REVIEW.md) adds a
complete file/CODE byte ledger and 3,298 machine-entry exports, including
linked runtime and exception continuations. It records unresolved bytes and
indirect delivery explicitly. Successful C decompilation was found to coexist
with empty/tiny listing bodies; the new exporter reconciles decompiler blocks,
switch destinations and checked original instruction bytes. Full recovery of
every executable path and behavioral equivalence remain unestablished.

The target is the installed English **Tower of the Sorcerer for Windows 1.2**,
`TSW.exe`, built with Borland Delphi/VCL. Class layout and startup/runtime
recognition provide strong **Delphi 2** evidence, without establishing the
exact compiler/library patch. Its SHA-256 is:

```text
41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779
```

Addresses refer to image base `0x400000`. The original installation is read only;
research creates exports, extracted data and test artifacts in this repository.
Keep an untouched original EXE or backup even when using the replacement game.

Public IDR recognition data is pinned by commit, URL, size and hash, and stays
in the ignored research cache. It supplies names and byte shapes, not original
Delphi Pascal sources. No purchased Delphi IDE is needed for this analysis.
Run `python tools/fetch_idr_recognition.py`, then
`python tools/account_original_program.py --check` and
`python tools/review_whole_program.py --check` to reproduce/check the retained
accounting. `tools/test_whole_program_accounting.py` checks mutation,
ambiguity, truncated bodies and evidence freshness. Ghidra reproduction and
remaining callback/runtime boundaries are documented in the whole-program
audit. The full comparison pipeline checks and records the ledger hash.

## What the decompiler supplies

Ghidra exports C-like inspection code, not compilable game source or recovered
Pascal. Changing its output language to C++ would not recover Delphi's original
names or structure. Review assembly for inferred signatures, register arguments,
indirect calls, dynamic strings and flag aliases before translating behavior.
For example, `_140_4_` is decimal byte offset 140; `field_0x140` is hexadecimal.

The initial export covers 106 detected functions entering `0x440000..0x488FFF`.
`RecoverCallbacks.java` adds ten indirect callbacks/item helpers, and
`RecoverArrival.java` repairs a missed two-level switch at `0x46CB1C`.
`RecoverSaves.java` adds the shared writer, eight save callbacks and seven
previously missed load callbacks (16 functions); the shared loader was already exported.
[The source index](../reference/original/decompiled/INDEX.md) and
[call map](../reference/original/decompiled/CALLS.md) locate the evidence.
Small reviewed door, Bomb and Zeno translations remain under `reference/original/`.

Use Ghidra's headless launcher with `tools/ghidra` as its script directory:

```text
analyzeHeadless PROJECT_DIR original-tsw -import ORIGINAL_DIR/TSW.exe -scriptPath tools/ghidra -postScript ExportOriginal.java reference/original/decompiled
analyzeHeadless PROJECT_DIR original-tsw -process TSW.exe -noanalysis -scriptPath tools/ghidra -postScript RecoverArrival.java reference/original/decompiled/0046cb1c_arrival_recovered.c
analyzeHeadless PROJECT_DIR original-tsw -process TSW.exe -noanalysis -scriptPath tools/ghidra -postScript RecoverCallbacks.java reference/original/decompiled
analyzeHeadless PROJECT_DIR original-tsw -process TSW.exe -noanalysis -scriptPath tools/ghidra -postScript RecoverSaves.java reference/original/decompiled
```

Use absolute paths when invoking the launcher from another working directory.
The recovered arrival export supersedes the initial incomplete
arrival file, which is retained as evidence of the missed analysis.

## Translate and compare

Translate a reviewed routine into named C++ state and explicit branches. Preserve
its state-write timing, loops, callback operands and reversed command insertion.
Keep meaningful original quirks in the core; document intentional safety or
presentation changes. The Rust campaign is not an oracle for original behavior.

The Python comparison tools run isolated original x86 handlers with Unicorn and
compare them with `tsw_probe.exe`. They pin the original hash and list
skipped VCL/RTL/device calls. From the repository root, after building C++:

```powershell
python -m pip install pefile capstone unicorn pillow
$env:TOS_ORIGINAL_EXE = 'D:/Program Files (x86)/Tower of the Sorcerer/TSW.exe'
python cpp/tools/differential.py --probe build/cpp/vs/Release/tsw_probe.exe
python cpp/tools/verify_interactions.py --probe build/cpp/vs/Release/tsw_probe.exe
python cpp/tools/verify_callbacks.py --probe build/cpp/vs/Release/tsw_probe.exe
python cpp/tools/verify_items.py --probe build/cpp/vs/Release/tsw_probe.exe
python cpp/tools/verify_saves.py --probe build/cpp/vs/Release/tsw_probe.exe
python cpp/tools/verify_quirks.py --probe build/cpp/vs/Release/tsw_probe.exe
python cpp/tools/verify_flight.py --probe build/cpp/vs/Release/tsw_probe.exe
python cpp/tools/verify_presentation.py --probe build/cpp/vs/Release/tsw_probe.exe
# Preferred complete pipeline, with skipped-call audit and evidence hashes:
python cpp/tools/verify_original.py --probe build/cpp/vs/Release/tsw_probe.exe
```

`cpp/src/probe.cpp` is a research-only stdin/stdout adapter linked to
`tsw_core` and the player-input layer. Commands such as `set`, `tile`, `call`, `input`, `step`, `trace` and
`snapshot` let these scripts configure and observe the same state as the
emulated original. The injected data lives in test instances and emulator
memory; the installed EXE and media remain untouched. Some fixtures intentionally
construct altered maps or extreme stats to expose a branch or unsafe access.
Reports distinguish skipped calls and explicit safety exceptions.
Generated comparison reports and save fixtures stay under `build/cpp/`.

Do not classify a helper as harmless from its UI role or name. Audit its state
writes and dependencies before excluding it. `0x442C38` draws the map **and
clears gameplay state**; skipping it caused a Flight bug despite thousands of
passing isolated comparisons. Test caller eligibility and complete sequences,
carry original memory between callbacks, and assert all watched gameplay fields.
Record stopped execution ranges as well as skipped calls: the former save test
stopped before a refresh and thereby missed the same reset. See the
[Flight audit](fidelity-audit-2026-10-09.md) for evidence, repairs and limits.

Catch2 core cases cover complete playback between builders and callbacks.
Renderer checks and asset comparisons are separate from core logic comparisons;
passing one does not establish the others. [Current coverage](../cpp/FIDELITY.md)
records the limits, including the outstanding full natural tower playthrough.

The generated maps/monster/dialogue constants can be refreshed with
`python cpp/tools/extract_constants.py ORIGINAL_TSW.exe`. The build recovers
the two embedded ending BMPs through `cpp/tools/extract_ui.py`; its manifest
also records the original eight paired Save/Load menu items.
