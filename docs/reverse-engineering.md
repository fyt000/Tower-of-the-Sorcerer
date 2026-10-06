# Original source recovery and verification

The target is the installed English **Tower of the Sorcerer for Windows 1.2**,
`TSW.exe`, built with Borland Delphi/VCL. Its SHA-256 is:

```text
41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779
```

Addresses refer to image base `0x400000`. The original installation is read only;
research creates exports, extracted data and test artifacts in this repository.
Keep an untouched original EXE or backup even when using the replacement game.

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
compare them with `tos_baseline_probe.exe`. They pin the original hash and list
skipped VCL/RTL/device calls. From the repository root, after building C++:

```powershell
python -m pip install pefile capstone unicorn pillow
$env:TOS_ORIGINAL_EXE = 'D:/Program Files (x86)/Tower of the Sorcerer/TSW.exe'
python baseline/tools/differential.py --probe baseline/build-vs/Release/tos_baseline_probe.exe
python baseline/tools/verify_interactions.py --probe baseline/build-vs/Release/tos_baseline_probe.exe
python baseline/tools/verify_callbacks.py --probe baseline/build-vs/Release/tos_baseline_probe.exe
python baseline/tools/verify_items.py --probe baseline/build-vs/Release/tos_baseline_probe.exe
python baseline/tools/verify_saves.py --probe baseline/build-vs/Release/tos_baseline_probe.exe
python baseline/tools/verify_quirks.py --probe baseline/build-vs/Release/tos_baseline_probe.exe
```

Add complete playback tests for interactions between builders and callbacks.
Renderer checks and asset comparisons are separate from core logic comparisons;
passing one does not establish the others. [Current coverage](../baseline/FIDELITY.md)
records the limits, including the outstanding full natural tower playthrough.

The generated maps/monster/dialogue constants can be refreshed with
`python baseline/tools/extract_constants.py ORIGINAL_TSW.exe`. The build recovers
the two embedded ending BMPs through `baseline/tools/extract_ui.py`; its manifest
also records the original eight paired Save/Load menu items.
