# Flight fidelity audit — 9 October 2026

Flight entry and redraw effects were omitted from C++. The floors 1–10 and
floor-19 routes used that invalid behavior and remain excluded from faithful
campaign evidence. Their artifacts are preserved under
`artifacts/cpp-mcp-first10/` and `artifacts/cpp-mcp-full50/`; no corrected run
has replaced them.

## Cause and correction

The relevant routines were already decompiled. Translation and comparison
boundaries missed their effects:

| Routine | Missed behavior | Correction |
|---|---|---|
| [Flight entry, 0x481E80](../reference/original/decompiled/00481e80_FUN_00481e80.c) | C++ checked idle/possession without the adjacent-stair scan | Selector and direct travel now use the entry contract |
| [Neighbor scan, 0x44C9F0](../reference/original/decompiled/0044c9f0_FUN_0044c9f0.c) | Eligibility depends on the final classification, not any adjacent stair | Preserve north/west/east/south priority; some later tiles override stairs, road/wall do not |
| [Map draw, 0x442C38](../reference/original/decompiled/00442c38_FUN_00442c38.c) | Drawing clears hero offset 664, the highest-floor stair marker | Entry and previews clear it before confirmation |
| [Confirm, 0x44EAF4](../reference/original/decompiled/0044eaf4_confirm_flight.c) | The translated direction flip received stale incoming state | Compose entry, previews and confirmation in tests |

Flight uses an explored-floor ceiling, not per-room visited flags. Corrected
highest-floor return sequences land at the normal upward arrival square.
Other active items are disabled while the selector is open.

The deeper review found the same redraw reset missing from successful wings,
dialogue stage 13, deferred floor changes and file-load refresh. All now clear
the marker; refused wings preserve it. Load tests follow the refresh rather
than jumping directly to its Zeno reconstruction fragment. Rewriting a save
with a nonzero marker therefore reflects the refreshed live value. Runtime
session snapshots preserve selector state because they are not file loads.

The dialogue helper at `0x449E18` also has a death branch at continuation 9.
Comparisons now follow that helper. Rendering helpers write shared scratch
operands, so their exclusions need explicit review even when no direct hero
or map write appears.

## Why earlier tests missed it

The old item suite's 2,067 comparisons included 468 seeded confirmations,
four previews with map drawing skipped, and no Flight entry calls. Skipping
the effectful draw made the comparison agree with the omission. Catch2 fixtures
also expected Flight to open without stairs and other items to work during
preview. Those fixtures tested the port's behavior rather than independent
game evidence.

Isolated handler agreement did not establish legal reachability or correct
caller/callee sequences. Increasing cases within the same boundary could not
detect the missing effects.

## Verification changes

`cpp/tools/verify_flight.py` compares 1,670 stages:

- 605 entry cases covering coordinates, cardinal neighbors and boundaries.
- 1,024 priority cases covering each byte value in each scan position.
- Three possession cases, including the exact-one condition.
- Eight composed selector routes and six direct-travel routes, including
  refusal, direction reversal, highest-floor return, 35F and 44F.

Emulator state carries between callbacks. The suite follows control setters
and compares intermediate marker/direction values; disclosed VCL rendering,
device and message-delivery exclusions remain. C++ stores the preview floor
separately from the physical hero floor, which comparisons account for.

Item, callback and save suites now follow redraw/refresh effects and assert
marker resets. Catch2/MCP regressions cover entry refusal, modal item refusal,
travel, cancellation, same-floor confirmation, usability and reload reset.

`cpp/tools/comparison_boundary.py` rejects unknown skipped targets and direct
named writes to gameplay state. Its self-test rejects the two effectful helpers
that exposed this omission. Aliased and transitive effects still require
assembly review.

Regenerate the retained comparison suite with:

```powershell
python cpp/tools/verify_original.py --probe build/cpp/vs/Release/tsw_probe.exe
```

The suite records probe/report hashes and reviewed exclusions in
`build/cpp/reports/original-suite.json`. Packaging requires current evidence,
including Flight coverage. The repaired worker preserved the stopped 19F
session during reload; no campaign input was used to validate deployment.

## Confidence limits

The named omissions are reproduced and corrected. Coverage includes sampled
handlers and composed Flight/load sequences, with separate command-playback
checks for fatal cancellation. It does not establish every natural campaign
sequence, modal transition, indirect VCL target or Delphi timing behavior.
A legal full-tower campaign remains outstanding.
