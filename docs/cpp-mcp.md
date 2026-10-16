# C++ MCP

`tsw_cli mcp` serves JSON-RPC over stdin/stdout without media or a window.
Example client configuration, using your checkout's absolute executable path:

```json
{
  "mcpServers": {
    "tower-cpp": {
      "command": "C:/path/to/checkout/build/cpp/vs/Release/tsw_cli.exe",
      "args": ["mcp"]
    }
  }
}
```

Optional startup flags: `--load FILE`, `--checkpoint` (raw Fairy file),
`--developer` (private observations and simulation). Paths otherwise resolve
against the server working directory. Custom clients must initialize, then send
`notifications/initialized`; EOF closes the server.

## Tools and observations

The [tool catalog implementation](../cpp/src/mcp.cpp) defines argument schemas.

| Tools | Purpose |
|---|---|
| `game_state`, `inspect_tile`, `plan_path` | Observe state, tile or apparent-road route |
| `navigate`, `run_steps`, `game_action` | Destination contact, guarded batch or single player input |
| `new_game` | Start a journey and recording |
| `save_game`, `load_game` | Session checkpoint or persistent file |
| `replay_game`, `export_replay` | Import/export JSONL history |
| `simulate_actions` | Developer-only execution on a session copy |

Coordinates are 0–10 from top left. `detail: compact` returns `floor.points`,
`tile_types["<id>"]` and `walkable_rows` (`.` road, `#` blocked). `summary` gives
state/deltas; `full` adds detailed maps/logs. Observations default compact,
mutations summary; floor changes return compact destinations.

Normal mode conceals secrets and unpreviewed floors; forecasts/manual saves
require the Hero Orb. `reachable` describes geometry, not safety; forecasts
exclude movement hazards/scripts. First-cycle 50F Zeno is an ending trigger,
not ordinary combat. Actions use the [replay input contract](replay-verification.md#commands-and-automatic-work).
Resources: `tos://state`, `tos://rules`, `tos://replay`.

## Navigation and batches

```json
{"x":5,"y":8,"floor":4,"interact":true}
```

`floor` guards stale coordinates. Navigation crosses apparent road and contacts
only the selected endpoint; doors are opened and entered. `interact: false`
stops at an event's approach. Unreachable navigation executes nothing; `plan_path`
can return a closest prefix. Concealed walls require deliberate movement input.
Inspect `navigation.reason`, messages and changes after scripts/hazards; endpoint
contact can leave the hero adjacent.

`run_steps` accepts 1–32 explicit steps, each with expected `floor` and either
`type: navigate` plus coordinates, or `type: action` plus a native input.
It rejects resets/saves/reloads and validates syntax before execution. It stops
on mismatch, refusal, damage, death, transition, interruption or an open shop/
Flight selector. Successful inputs remain committed; inspect `batch.reason`,
`executed_steps`, `stopped_at` and per-step results before resuming.

## Saves and replay

`save_game` without `path` returns an opaque checkpoint ID; up to 64 survive
within the connection. `load_game` accepts exactly one checkpoint or path.
For persistent files use absolute `path` and `kind: slot` (default) or
`checkpoint` (Fairy format). File saves require idle state and closed Flight.
At capacity, file saves still work with `checkpoint: null`. Copy replay companions
with files; [original save layout](original-data.md#original-saves).

`replay_game` accepts exactly one file `path` or inline `replay`, optionally
`limit`. It validates the whole recording before replacing the session with
that prefix. Failures preserve it. `export_replay` returns inline history unless
`path` is supplied; `include_replay` controls echoing. Limits: 100,000 inputs,
8 MiB per recording/request.

## Bridge and worker updates

For hot reload, configure C++, then publish and run the Python 3.10+ bridge:

```powershell
python cpp/tools/build_mcp.py --build-dir build/cpp/vs
python cpp/tools/mcp_server.py
```

Configure the client with `python` and the bridge's absolute path. It watches
`build/cpp/dist/mcp/current.json`; compatible workers preserve the session.
`mcp_runtime` reports deployment/health. Incompatible transfer starts fresh with
`recovery_required: true`; recover using `new_game`, `load_game` or `replay_game`.
Old checkpoint IDs expire. Startup/transfer failure retains a healthy old worker;
crashes/timeouts need persistent recovery. Mutations are not retried.

Overrides: `--manifest` / `TSW_MCP_CURRENT`, `--timeout-ms` / `TSW_MCP_TIMEOUT_MS`.
Bridge-code updates need a reconnect; catalog changes may need client refresh.
MCP tool failures use `isError`; JSON-RPC envelope/method errors use `error`.

Checks: `cpp/tools/check_mcp.py` and `check_mcp_reload.py`, each with
`--cli PATH/tsw_cli.exe`.
