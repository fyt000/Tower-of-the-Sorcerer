# C++ MCP playtest — 9 October 2026

This report records an interface benchmark and a floors 1–10 run made before
the Flight correction. **The route used invalid Flight behavior and is not
evidence of a faithful playthrough.** See the [Flight audit](fidelity-audit-2026-10-09.md).
The saved artifacts remain historical; no corrected campaign has replaced them.

## Retained run

A normal-mode stdio worker defeated Skeleton A, collected the rewards and
entered floor 11 with HP 754, attack 32, defense 33, gold 287 and keys 3/0/0.
It had Iron Sword/Shield and two altar purchases; the next altar price was 80.
Source knowledge guided the route, and one replay rewind changed a key-spending
branch. Developer-mode exploration preceded the normal-mode run.

Local, ignored evidence under `artifacts/cpp-mcp-first10/`:

- [Replay](../artifacts/cpp-mcp-first10/normal-first10-cleared.jsonl): 1,014 inputs.
- [Save](../artifacts/cpp-mcp-first10/normal-first10-cleared.dat) and
  [companion](../artifacts/cpp-mcp-first10/normal-first10-cleared.dat.replay.jsonl).
- [Measurements](../artifacts/cpp-mcp-first10/measurements.json): payload sizes,
  navigation totals and save/replay checks.

The CLI reproduced the recorded hero, inventory and map; save reload resumed
the companion. These checks establish replay consistency for that version,
not legality under the corrected Flight rules. Strategy material in the
[campaign skill](skills/tower-cpp-campaign/SKILL.md) and
[early-game reference](skills/tower-cpp-campaign/references/first-ten-floors.md)
must be reassessed where it depends on those landings.

## Interface findings

Destination navigation replaced per-step requests while preserving player
choices about enemies, doors and resource spending. After the last rewind,
181 navigation calls executed 600 inputs: about 70% fewer movement requests.
All steps stayed in the replay. Current behavior and arguments are documented
in [the MCP guide](cpp-mcp.md).

Compact state responses share tile definitions; action summaries return deltas
and feedback. Measurements compare UTF-8 payload bytes at identical states or
equivalent actions, excluding duplicate JSON-RPC representations:

| Response | Previous default | Compact/summary default | Reduction |
|---|---:|---:|---:|
| Normal initial state | 3,130 | 2,970 | 5.1% |
| Normal floor 11 state | 8,912 | 4,225 | 52.6% |
| Normal movement | 8,914 | 726 | 91.9% |
| Developer movement | 28,739 | 725 | 97.5% |
| File replay export | 44,595 | 117 | 99.7% |

Full observations matched the previous worker in the measured states. These
are historical byte measurements, not current performance or model-token counts.

## Remaining integration limits

- The bridge announced a changed tool catalog, but the active host retained
  old schemas. Reconnect or refresh when newly published tools are missing.
- Responses include both `structuredContent` and equivalent JSON text for
  compatibility. Host handling determines whether both enter model context.
- Action summaries do not refresh cached reachability or all forecasts;
  request compact state after scenes or when those values are needed.

At this checkpoint, stdio, bridge reload, navigation, save/replay parity and
compact/full projection checks passed. Detailed results remain in the linked
measurements. Campaign validity is limited by the Flight finding above.
