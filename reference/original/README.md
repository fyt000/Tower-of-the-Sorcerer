# Original interaction source reference

This directory holds source evidence for reviewing the installed **English
Windows Tower of the Sorcerer 1.2**. The separate, runnable C++20 original-game
baseline is in [baseline](../../baseline/README.md), with executable comparison
results and limits in [its fidelity notes](../../baseline/FIDELITY.md). The Rust
rewrite remains independent and its architecture is unchanged.

The original image has SHA-256
`41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779`.
All addresses below are virtual addresses at image base `0x400000`.
Analysis reads that image without modifying it.

## Start here

| Source | What it makes explicit | Verified original behavior |
|---|---|---|
| [C++ baseline](../../baseline/README.md) | Readable complete core, iterative command interpreter and raylib desktop | 4,216 isolated original-machine comparisons; regression, sanitizer and desktop checks described in its fidelity notes |
| [doors.cpp](doors.cpp) | Key decision, unconditional door callback, reversed queue order | 39F one-key clock shortcut; both hand orders; ordinary opening/refusal; 43F no-key trap arming |
| [bomb.cpp](bomb.cpp) | Tile classifier, cardinal bounds, gold, consumption, dissolve records, deferred floor check | Immune and susceptible tile families; all 256 tile inputs; all 121 hero coordinates; raw rewards; one callback after a complete use |
| [zeno.cpp](zeno.cpp) | Shared row, seal flag, division, gate restoration and cycle-specific contact | 49F `/= 10`; time gate `*= 10`; gate-before-seal route; resealing after restoration; second-cycle fixed-row exception |
| [mechanics.hpp](mechanics.hpp) | Named state fields and three-word queue records | Memory addresses used by the above routines |
| [decompiled/INDEX.md](decompiled/INDEX.md) | Broader C-like original function bodies, including interaction dispatch, NPC speech/Continue, step and floor checks | Exported code for inspection; branches are **not** all manually verified |
| [decompiled/CALLS.md](decompiled/CALLS.md) | Linked direct calls, including callees outside the exported address range | Static inventory; Delphi indirect calls and callbacks need separate review |

The small C++ files reconstruct the listed fields and branches. They omit
Delphi controls, localized status-string construction and pixel rendering.
The vector represents the command stack's order, not the original buffer's
capacity. Stack insertion and execution have opposite orders. They retain
literal numeric-sum checks where present; the Rust clock event expresses the
equivalent predicate for reachable original clock states. Synthetic balanced
non-door sums are recorded separately in the executable audit.

The initial generated C-like corpus contains **106 detected functions** entering
`0x440000..0x488FFF`, with no decompilation failures. Ten separately recovered
callbacks/item helpers and a repaired arrival-switch export supplement it and preserve the wider
control flow and unresolved helpers. Ghidra infers signatures and types from
Borland Delphi machine code. Register arguments, dynamic strings, unknown
globals and casts still need
assembly checks. Naming one command record at the stack base does not assert
its capacity. Decompiled source is an inspection aid, not recovered source
from the original author or a compilable replacement game.

The generated `original_maps[51][123]` view includes **two header bytes per
floor**. Its `[floor][index + 2]` is the same cell as `State::tiles[index]`
in the cleaned source and `tiles[y * 11 + x]` in Rust. `original_monsters`
contains 33 rows of four signed 32-bit fields; Zeno uses row 15 at
`0x489A00`. The hero structure names only reviewed fields, leaving unknown
bytes explicit. `cycle_factor_minus_one` is the original scaling value
(0 or 43), not the modern cycle number; `later_cycle` separates cycle 2
from cycles 3 and later.

## Interaction order that matters

| Entry path | Original flow | Rust representation |
|---|---|---|
| Colored-door contact | `handan` key decision → `doorcheck` even on refusal → opening/refusal queue | `DoorAttempted` runs on either outcome; successful opening presentation precedes callback rewards |
| Ordinary or forced battle | Victory clears the target and rewards gold → `moncheck` | Per-victim `EnemyDefeated`, then floor-wide `PostCombat` |
| Bomb | Classify all cardinal neighbors → write complete gold and consume → dissolve north/west/east/south → one queued `moncheck` | Clear all victims and commit reward/consumption before callbacks; one `PostCombat`, including empty use |
| 49F seal | Pattern sums → if seal flag clear, set it and divide current shared row → queue speech | Repeatable pattern event; conditional `MultiplyEnemy(1,10)` and persisted flag |
| 49F decoy death | Seal arithmetic runs before reward records clear the corners; the reward builder replaces the seal speech queue | Seal and loot share `PostCombat` in original order; dead-decoy seal retains arithmetic without extra speech |
| 24F time gate | If sealed, clear flag and multiply current row by ten → cycle-2 fixed row → 50F sequence | Conditional `MultiplyEnemy(10,1)`; no fixed reset for cycles 1 or 3+ |
| 50F Zeno contact | Cycle 1 ending; cycle 2 assigns fixed row; cycles 3+ battle current shared row | Later contact retains a seal applied after gate entry |

For the ordinary `8000/5000/1000` row, seal → gate returns full stats.
Gate → seal → return by Ascent Wing keeps `800/500/100`; later-cycle encounter
scaling makes those `35200/22000/4400`. Clearing the seal flag at the gate permits a new seal
on another valid 49F post-combat check. Second-cycle contact instead assigns
`1000/625/125`. First-cycle 50F contact ends the cycle without ordinary combat.
This event arithmetic is separate from the original save/load double-scaling
defect that the Rust engine normalizes.

Delaying the **49F decoy fight** until after the gate is a concrete way to
re-seal: the gate first restores the full row; decoy victory then checks the
still-valid edges/corners and divides that row before clearing the corners
for loot. Returning by wing keeps the weaker 50F row. A per-victim loot
callback before the floor check loses this interaction, even with shared-row
arithmetic implemented. Regression scenarios now defeat that full-strength
decoy, verify the re-seal and reward cleanup, and return using real wings.

## Evidence and regression coverage

Run the read-only original probes from the repository root:

```powershell
python tools/audit_original_door_bomb.py
python tools/audit_original_zeno.py
```

They require `pefile`, `capstone` and `unicorn`. `TOS_ORIGINAL_EXE` can select
another installation of the same hash-pinned image.

- [original-door-bomb-audit.json](../../data/original-door-bomb-audit.json)
  records 2,362 builder/classifier scenarios, skipped helper calls,
  disassembly, clock examples and Rust-consumed oracles.
- [original-zeno-audit.json](../../data/original-zeno-audit.json) records 72
  chained event-order cases across cycles 1–4, arbitrary current rows,
  truncation, invalid-pattern rejection, decoy-death queue replacement and
  shared-row write sites.
- Rust regressions in `original_campaign`, `active_items`,
  `event_presentation` and `backside` execute the real commands, including
  wings, refused door contact, re-sealing and save/restore. Browser animation
  tests render both one-key clock routes. GUI migration tests preserve old
  progress while recovering a seal only when an old weak row and seal count
  establish it; old event-order history cannot be reconstructed.

The probes stop before Delphi timer playback and disclose skipped calls.
The Zeno cases carry actual stat/flag writes between isolated handlers;
they do not simulate natural full-tower routes. Source export, branch probes,
Rust scenarios and a natural playthrough are separate kinds of evidence.
The separate C++ checks also cover default Fairy score/ranking and completed
checkpoint saves. Remaining limits include a complete altered-state branch
inventory, custom legacy ranking files, exact compositor timing and a full
natural tower route. Source and executable comparisons do not prove 100% of
all possible behavior.

## Regenerating the broader source export

Use the official Ghidra 11.0.3 release and JDK 17 or later. The installed image
is recognized as `x86:LE:32:default:borlanddelphi`. With Ghidra on your machine,
substitute its actual path and choose an ignored project directory:

```powershell
& '<Ghidra>/support/analyzeHeadless.bat' `
  'tools/research/ghidra-project' original-tsw `
  -import 'tools/research/TSW.exe' `
  -analysisTimeoutPerFile 300 -max-cpu 2 `
  -scriptPath 'tools/ghidra' `
  -postScript ExportOriginal.java 'reference/original/decompiled'
```

`tools/research/TSW.exe` is an unchanged local analysis copy, excluded from
Git. Windows Ghidra's batch launcher handles a path without parentheses more
reliably than the original installation path. To re-export an existing project,
replace `-import … -analysisTimeoutPerFile 300` with
`-process TSW.exe -noanalysis`. The exporter pins the hash, names verified
state addresses and handlers, lists its function-address scope in the index,
and reports decompilation failures explicitly.

The initial arrival export missed a two-level computed jump. Recover it and the
indirect Delphi callbacks in the same analysis project:

```powershell
& '<Ghidra>/support/analyzeHeadless.bat' `
  'tools/research/ghidra-project' original-tsw -process TSW.exe -noanalysis `
  -scriptPath 'tools/ghidra' -postScript RecoverArrival.java `
  'reference/original/decompiled/0046cb1c_arrival_recovered.c'
& '<Ghidra>/support/analyzeHeadless.bat' `
  'tools/research/ghidra-project' original-tsw -process TSW.exe -noanalysis `
  -scriptPath 'tools/ghidra' -postScript RecoverCallbacks.java `
  'reference/original/decompiled'
```

The recovered arrival file supersedes the incomplete `0046cb1c_ichicheck.c` for
reviewing floor-specific branches. The original is Borland Delphi/VCL. Changing
the decompiler's display language to C++ would not recover the author's Pascal
source; the compilable modern implementation is the separately reviewed C++
translation.
