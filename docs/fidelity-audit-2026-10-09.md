# Flight fidelity audit — 9 October 2026

The campaign is stopped. The recorded first-ten-floor route and subsequent
floor-19 route used the invalid Flight behavior and are not evidence of a
faithful original playthrough. Their saved files remain preserved under
`artifacts/cpp-mcp-first10/` and `artifacts/cpp-mcp-full50/`; no repaired run has
been substituted for that history.

## What was recovered, and what was missed

The relevant behavior **was already decompiled** from the pinned English TSW
1.2 executable, SHA-256
`41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779`.
The failure was in translation and verification boundaries.

1. [Flight entry, 0x481E80](../reference/original/decompiled/00481e80_FUN_00481e80.c)
   resets the direction and stair marker, checks possession, scans cardinal
   neighbors through [0x44C9F0](../reference/original/decompiled/0044c9f0_FUN_0044c9f0.c),
   and opens the selector only when the final classification is stairs (19).
   Otherwise it displays message 20. C++ opened the selector with only an
   idle/possession check. Direct Flight also bypassed this entry contract.
2. [Map drawing, 0x442C38](../reference/original/decompiled/00442c38_FUN_00442c38.c)
   starts by clearing hero offset 664, the highest-floor stair marker. Flight
   entry and both previews call it. C++ omitted that mutation because the
   helper was treated as presentation. Walking near stairs could leave an old
   marker, which then affected landing.
3. [Confirm, 0x44EAF4](../reference/original/decompiled/0044eaf4_confirm_flight.c)
   contains the direction-flip branch that C++ had translated. A matching
   isolated branch did not establish a matching sequence: its incoming state
   was wrong. The previous explanation that the shortcut followed original
   behavior was therefore incorrect.

The original does not track access to each stair or room with a separate visited
flag. Its protections here are the opening check, the explored-floor ceiling,
and the marker reset before selection/confirmation. Successful travel to the
highest floor in the reproduced sequences lands at that floor's normal upward
arrival square, rather than the opposite staircase.

The neighbor scan is ordered north, west, east, south. Some classified tiles
override an earlier stair classification; road and ordinary wall do not. The
fix preserves this detail rather than using an unrestricted `any(stairs)` test.

## What the old comparison actually established

The old item report contained 2,067 passing comparisons:

- 468 invoked Flight confirmation with direction and marker seeded directly.
- Four invoked a preview callback, while skipping map drawing.
- Zero invoked the original Flight opening handler.

The test proved that selected handlers produced matching hero values, map
changes and command sequences from the supplied states, with the disclosed
calls excluded. It did **not** establish that a player could legally reach those
states, that opening restrictions matched, or that consecutive callbacks
preserved the same state. Skipping map drawing also removed the relevant
mutation from the original side of the test, so the comparison oracle shared
the port's omission.

The overall 4,610 count was real isolated comparison coverage, but was
overinterpreted as broader gameplay fidelity. Larger byte/coordinate matrices
inside the same incomplete boundary cannot recover a missing caller or callee.

The Catch2 tests compounded the problem. Flight checkpoint tests used a room
containing no stairs and expected opening to succeed. A replay test expected
another item to work during a Flight preview. Those were internally consistent
tests of incorrect behavior, not independent original-game evidence.

## Additional findings from the deeper review

| Finding | Evidence and disposition |
|---|---|
| Other active items worked during Flight | Entry calls 0x450758, which disables Hero/Wisdom/Flight and active item controls and the keyboard gate. Replay now refuses item use and reopening during a selector session. Original control setter instructions are followed with inert controls in the Flight test. |
| Wing travel omitted the redraw reset | Both successful wing branches in 0x450BC5 call 0x442C38. Both now clear the marker. Item comparisons start with a nonzero marker, so omitting the reset fails. Refused wings retain the marker. |
| Dialogue continuation omitted the redraw reset | Stage 13 of 0x44DA10 calls map drawing. The port now clears the marker. The callback suite previously watched offset 664 but never compared it; it now asserts it. |
| Deferred floor change omitted the redraw reset | Opcode 11 of 0x4526C0 changes the floor and calls map drawing. Its C++ Teleport callback now clears the marker. |
| Loading stopped before an effectful refresh | The old save emulator stopped at the call to 0x454DE8, then resumed only its Zeno reconstruction fragment. It therefore missed the refresh's map redraw. File loads now clear the marker after decoding. Save comparisons execute the refresh body and map draw, then compare the original writer against the refreshed live state. |
| A supposedly presentational dialogue helper has a death branch | 0x449E18 can change music and produce death commands when continuation stage is 9. Callback comparisons now follow the helper instead of skipping it. The ordinary NPC scenarios still match. Full original death/timer/input sequencing remains outside those isolated scenarios; C++ fatal cancellation has separate command playback tests. |
| Rendering helpers share scratch globals | 0x4433A4, 0x443808, 0x454C10, inventory/key drawing and related helpers write scratch operands. Reviewed presentation exclusions are documented explicitly. A lack of direct hero/map writes does not itself prove arbitrary transitive or aliased effects are harmless. |

The loading correction changes the old synthetic “byte-exact round trip”
expectation for a save containing a nonzero stair marker: the original refresh
changes that live field before the next write. The file format, original
checksum arithmetic and preservation of opaque words remain checked. Runtime
session snapshots are distinct from file loading and preserve an open selector
and its preview state.

## Verification changes

`cpp/tools/verify_flight.py` compares 1,670 stages against original instructions:

- 605 entry cases: every board coordinate, all four directions and a diagonal
  control, including boundaries that must not wrap through flat map storage.
- 1,024 priority cases: all 256 tile bytes in each of the four scan positions.
- Three possession cases, including the original exact-one condition.
- Eight complete selector routes, comparing opening, each preview and final
  confirmation; bounds refusal, highest-floor return, direction reversal,
  35F and 44F behavior are included.
- Six direct travel routes compared with the corresponding original opening
  and monotonically previewed sequence.

Original emulator memory is carried between callbacks; intermediate direction
and marker values are not reconstructed from C++ or hand-seeded. The original
control enable setters are followed. VCL rendering/device/message delivery
still use disclosed exclusions. C++ keeps the preview floor separately from
the physical hero floor; comparisons account for that representation change.

The item and callback suites follow the map draw and assert nonzero-to-zero
resets. The save suite follows the original load refresh rather than only its
last gameplay fragment. New Catch2/MCP regressions cover invalid entry, direct
travel, highest-floor round trips, cancellation, same-floor confirmation,
modal item refusal, observation usability and reload reset. Existing Flight
checkpoint/migration fixtures now have legal adjacent stairs.

`cpp/tools/comparison_boundary.py` audits skipped targets against explicit
exclusions. Unknown direct/indirect targets and direct named writes to hero,
maps, monsters, dialogue continuation or command state fail the audit. Its
CTest self-test verifies rejection of the two effectful helpers that exposed
this failure and of unknown calls. This source scan is a safeguard, not a
replacement for assembly review: aliasing and transitive effects are not
automatically proved safe.

Run the complete retained comparison pipeline with:

```powershell
python cpp/tools/verify_original.py --probe build/cpp/vs/Release/tsw_probe.exe
```

It regenerates all seven reports, checks their boundaries, and records the
compiled probe hash and each report hash in `build/cpp/reports/original-suite.json`.
Packaging requires this evidence, the Flight report, matching hashes and
reviewed exclusions. Passing an older subset cannot authorize a package's
fidelity claim.

Final validation passed the MSVC Release build, all-source C++ formatting,
all 86 non-audio CTest checks, and all 6,280 retained original comparison
cases/stages. Audio tests were excluded because these changes do not touch
audio. The local MCP worker was published and reloaded successfully. A
read-only comparison before and after migration confirmed identical hero
state, all floors and monster rows, inventory, Flight selection, steps,
recording history count, action feedback, log and pending commands. The
session remains at 19F (5,2), HP 186, attack 70, defense 65, gold 46, with
1,729 recorded inputs. Its Flight item now reports `usable: false` at that
non-stair position. No campaign input was applied to check the deployment.

## Confidence limits

The targeted Flight discrepancy and the additional named reset omissions are
reproduced from original instructions and corrected. The retained comparisons
cover sampled handlers and the newly composed Flight/load sequences. They do
not establish all possible natural event sequences across 50 floors, exact
Delphi timing, every modal input transition, or resolved targets for every
indirect VCL call. A legal full-tower campaign remains outstanding; the stopped
recording cannot satisfy it.
