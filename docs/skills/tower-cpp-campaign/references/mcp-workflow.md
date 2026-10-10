# Connected MCP workflow

Use this reference for starting/resuming a game, avoiding redundant tool calls, handling navigation interruptions, or recovering across server updates. Read the current catalog and `docs/cpp-mcp.md` when installed capabilities differ.

## Connection and mode

Prefer the connected `tower_cpp` tools. The official `cpp/tools/mcp_server.py` bridge communicates over STDIO and selects the published native worker; an additional HTTP controller is not needed for ordinary gameplay. The bridge supports deployment hot reload and runtime diagnostics. Updating its own Python code requires a connection restart because a C++ worker reload does not replace the running bridge code.

Inspect `mcp_runtime` for active deployment, worker health and continuation status, then `game_state` for `developer`, cycle, hero, phase, inventory and pending interaction. Publishing a binary and confirming that the connected worker adopted it are separate checks. A fresh connection may contain an initial game rather than the journey held by another process.

Use normal mode for an ordinary campaign. Developer mode exposes private state and adds `simulate_actions`; distinguish that investigation from a normal campaign. Source access does not imply that developer simulation was used.

## Compact interaction

`game_state` defaults to compact: current-floor `points`, shared definitions in `tile_types["<id>"]`, and `walkable_rows` (`.` apparent road, `#` other squares). Coordinates are zero-based on an 11 by 11 board. Read a tool's structured result once; equivalent JSON text is a compatibility representation, not another observation.

Example destination:

```json
{"x": 5, "y": 8, "floor": 4, "interact": true}
```

`floor` rejects stale floor coordinates. Navigation crosses apparent road and requires separately selected intervening events. Default endpoint contact can collect, fight, open a door/shop, trigger a scene or change floors. A selected door is opened and entered; a manual movement contact may only open it. `interact: false` approaches an event without activating it. An unreachable navigation target executes zero inputs.

`navigation.reached` may indicate endpoint contact while the hero remains adjacent. Check `reason`, messages, hero and `changes`, especially after hazards, scripts, refusals, shops or floor transitions. Do not continue a cached sequence through an unexpected result. `plan_path` examines apparent-road geometry and predicts neither script nor hazard costs.

Use `game_action` for listed shop replies and items:

```json
{"action": {"type": "choose", "choice": "1"}}
{"action": {"type": "use_item", "item": "flying_orb", "floor": 9}}
```

Speech settles automatically; a shop waits for a listed reply or cancel. Flight requires a valid adjacent-stair entry. Ordinary stairs and Flight skip floor 44; Wings use different landing rules. Verify the resulting floor and coordinates. A clue-supported concealed wall needs deliberate movement contact rather than ordinary navigation.

Action responses default to summary; floor changes include compact destinations. Reuse updated hero/item/tile deltas and refresh compact state after access changes, scripted rearrangements or when recalculating forecasts. Use `inspect_tile` for a specific missing detail. Repeated Hero Orb activation adds no forecast information once forecasts are unlocked.

Short sequences can be orchestrated through connected calls without a shell proxy, checking each result before the next mutation. Keep fights, purchases and consumable uses explicit; avoid automatic collection/farming policies that ignore halving hazards, Lucky Gold or future item uses.

Handle JSON-RPC `error` and MCP `isError` separately. An error content block can be plain text; do not blindly JSON-parse every message. An error in a custom client is not evidence of a native game defect.

## Updates and recovery

A compatible worker update preserves the session. A healthy worker that rejects an incompatible checkpoint activates with a fresh session. `mcp_runtime` then reports:

```json
{
  "session_continuable": false,
  "recovery_required": true,
  "recovery_tools": ["new_game", "load_game", "replay_game"],
  "last_reload": {"status": "reset", "session_restored": false}
}
```

Observation results also carry continuation metadata. Gameplay, including a stale command that triggers this update, is blocked with `-32003`. Recover through a successful `new_game`, `load_game`, or `replay_game`; `game_action` with a `new_game` input also works. Failed recovery keeps the gate closed. In-memory checkpoint IDs from the discarded session are gone. A worker startup/I/O failure or dead worker is a different condition; inspect runtime diagnostics before assuming reset recovery applies.

A fresh connection has a fresh usable game and can report continuation true; that does not prove the old campaign was restored. Inspect the hero/cycle and explicitly load the chosen evidence when continuing a previous journey.

## Save and replay

Normal saving requires a living hero and Hero Orb. Persistent `.dat` saving needs an idle boundary and closed Flight selector. Use an absolute path and keep its `.dat.replay.jsonl` companion:

```json
{"path": "D:/projects/tos-rust/artifacts/my-run/milestone.dat"}
```

There are at most 64 opaque session checkpoints. They expire at disconnect or incompatible reset. With `path`, saves succeed when checkpoint capacity is full and return `checkpoint: null`; no-path saves hit the limit.

`load_game` accepts a path or one current-session checkpoint ID. File loading uses the original reconstruction rules, so verify later-cycle enemy rows and forecasts afterward. `replay_game` imports a recording beginning with `new_game`, optionally up to a `limit`, and replaces the session on success. Failure preserves it. Validate a proposed branch before deliberately adopting it; replay consistency is not proof of route quality or original-version legality.

`export_replay` with an absolute `path` returns metadata without echoing the whole recording. Save at strategic milestones rather than creating a checkpoint after every trivial input. Keep selected and discarded branches identifiable. Report restarts, rewinds, CLI route tests and any developer simulation accurately.

## Scripted ending contact

First-cycle floor-50 Zeno is `kind: "trigger"`, `interaction: "ending"`, `hp_cost: 0`, `available: true`, without an ordinary enemy forecast. Navigation can contact this trigger. Use the reported interaction kind when handling scripted contacts. Floor 49 and later-cycle Zeno retain their combat rules; do not generalize the first-cycle ending to those encounters.
