# Decompilation and recovery

Target: English **Tower of the Sorcerer for Windows 1.2**, image base `0x400000`.
Supported EXE SHA-256:
`41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779`.

Git contains readable implementations, tools, reviewed boundaries and fixtures.
See [Delphi recovery status](../delphi/README.md#recovery-status) and
[C++ fidelity](../cpp/FIDELITY.md). Generated evidence stays local.

## Prepare data and decompilation

Use the original installation, Python dependencies, Ghidra **11.0.3** with its
required Java runtime, and 7-Zip. From the repository root:

```powershell
python -m pip install -r tools/requirements.txt
python tools/prepare_research.py --source ORIGINAL_DIRECTORY
python tools/prepare_research.py --source ORIGINAL_DIRECTORY --decompile --ghidra GHIDRA_DIRECTORY
python tools/prepare_research.py --check --decompile
```

Omit `--decompile` for data extraction only. Preparation verifies the EXE,
recovers events, then assembles a new campaign. Existing editable campaigns and
interactions are preserved; `extract_original.py --regenerate-campaign` explicitly
rebuilds a campaign. Preserve manually adjusted exports before regeneration.

Tools default to `build/research/TSW.exe`; override with `TOS_ORIGINAL_EXE`.
Asset paths use `TOS_ASSETS`, otherwise the executable's directory. Extraction
and build commands also accept explicit source/asset paths.

| Local output | Content |
|---|---|
| `build/research/TSW.exe` | Verified original copy |
| `data/` | Maps, monsters, dialogue, events and campaign inputs |
| `build/research/decompilation/decompiled/` | Initial gameplay exports |
| `build/research/decompilation/presentation/` | Forms, event bindings, published-method exports and effect inventory |
| `build/research/decompilation/whole-program/` | C/assembly exports, `CODE.asm`, byte ledger, class metadata and analysis snapshots |
| `build/research/ghidra-*` | Separate persistent Ghidra project |

The [pipeline](../tools/prepare_research.py) iterates structural roots until
stable and checks instruction bytes against the EXE. IDR inputs are pinned in
[tools/idr-inputs.json](../tools/idr-inputs.json). Existing analyst projects are
not modified. Fresh analysis can change names/boundaries; regeneration does not
establish behavioral equivalence. Original assets remain read-only.

## Reading the evidence

Published methods and serialized events identify application entries, not every
runtime path. Check inferred types, register arguments and indirect calls against
assembly. Include exception continuations, switch tables and literal pools.
The real item-confirmation entry is `0x450BA0`; old `0x450BC5` is interior.
Use the repaired `0x46CB1C` arrival export instead of its incomplete initial export.

Drawing at `0x442C38` resets gameplay state. Timers, focus and dialogue can also
change legal actions or continuations. Windows callback trampolines and exception
roots escape ordinary call graphs; direct handler tests bypass framework delivery.

The 2026-10-09 accounting snapshot exported 3,298 machine entries. It retained
14,369 unresolved CODE bytes, 101 instruction/metadata-conflict bytes and 1,690
indirect transfers with unknown target/delivery context. These are analysis
limits, not missing Pascal-method counts. Inspect generated ledgers for addresses.

## Verification

```powershell
python tools/account_original_program.py --check
python tools/review_whole_program.py --check
python tools/test_whole_program_accounting.py
python cpp/tools/verify_original.py --probe build/cpp/vs/Release/tsw_probe.exe
```

The C++ suite compares emulated original handlers with the compiled probe and
records excluded calls in `build/cpp/reports/`. Isolated agreement does not prove
complete campaign or Windows scheduling equivalence. Follow [AGENTS.md](../AGENTS.md)
for audio-test scope. Delphi build/comparison commands are in its README.
