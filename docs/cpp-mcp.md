# C++ MCP mode

`tsw_cli mcp` serves newline-delimited JSON-RPC over stdin/stdout. It shares the
gameplay, saves and recording used by the desktop and headless CLI, works with
`TSW_GUI=OFF`, and needs no window, media, audio device, Node or Python.

```powershell
./build/cpp/vs/Release/tsw_cli.exe mcp
./build/cpp/vs/Release/tsw_cli.exe mcp --load ./Savedat/save1.dat
./build/cpp/vs/Release/tsw_cli.exe mcp --load ./Savedat/save0.dat --checkpoint
./build/cpp/vs/Release/tsw_cli.exe mcp --developer
```

Client configuration (replace the example checkout path with your local path):

```json
{
  "mcpServers": {
    "tower-cpp": {
      "command": "D:/projects/Tower-of-the-Sorcerer/build/cpp/vs/Release/tsw_cli.exe",
      "args": ["mcp"]
    }
  }
}
```

Use absolute executable/file paths; tool file arguments otherwise resolve against
the server working directory. Send `notifications/initialized` after initialization and before tools or
resources. Stdout contains protocol messages only; EOF closes the server.

## Python bridge and hot reload

The bridge needs Python 3.10+ with the standard library. After
[configuring C++](../cpp/README.md#build-on-windows), publish from the repository
root and launch the bridge:

```powershell
python cpp/tools/build_mcp.py --build-dir build/cpp/vs
python cpp/tools/mcp_server.py
```

`build_mcp.py` builds/publishes `tsw_cli`; `--cmake PATH` selects CMake,
`--config` defaults to `Release`, and headless builds can use
`--build-dir build/cpp/core`. Publish an already built binary with:

```powershell
python cpp/tools/mcp_deployment.py build/cpp/vs/Release/tsw_cli.exe
```

Configure the client to launch `python` with argument
`D:/projects/Tower-of-the-Sorcerer/cpp/tools/mcp_server.py`, adjusted to your
checkout path. Bridge options include
`--developer`, `--load FILE` (`--save` alias), and `--checkpoint`. A startup save
is loaded once, using JSON-RPC for Unicode paths; replacement workers receive
the live session.

Published workers live in immutable version directories under
`build/cpp/dist/mcp/`. The bridge watches `current.json` and transfers the live
session before the next request when the active worker changes. Successful
restoration preserves game state, pending interactions, recording and session
checkpoints. Keep versions that running bridges still use.

The bridge adds read-only `mcp_runtime` for worker health and reload outcomes.
A compatible update continues the session. A schema/version/mode mismatch
starts a fresh session and reports `recovery_required: true`; gameplay waits
for `new_game`, `load_game` or `replay_game`. Old session checkpoint IDs expire,
so use a persistent save or replay for recovery.

Invalid manifests leave a healthy worker running. Candidate startup or transfer
failure leaves the previous worker active and fails the triggering request.
Crashed or timed-out workers require recovery from a persistent save; mutations
are not retried because their commit status may be unknown.

Use `--manifest FILE` / `TSW_MCP_CURRENT` to select a manifest and
`--timeout-ms` / `TSW_MCP_TIMEOUT_MS` to set the request deadline. Private
session-transfer RPCs are unavailable to public clients. Schema changes require
a new runtime version. Tool catalog changes trigger a notification, but some
clients need an explicit refresh or reconnect.

## Tools and observations

The live tool catalog defines arguments and validation. `--developer` adds
`simulate_actions`; the optional bridge adds `mcp_runtime`.

| Tool | Arguments | Behavior |
|---|---|---|
| `game_state` | Optional `map_floor`, `detail` | Observe; remote floors require developer access or an open Flight preview |
| `inspect_tile` | `x`, `y`, optional `map_floor` | Tile, pickup values and unlocked combat forecast |
| `plan_path` | `x`, `y` | Read-only apparent-road route, allowing final obstacle contact |
| `navigate` | `x`, `y`; optional `floor`, `interact`, `detail` | Walk to/contact a selected destination |
| `run_steps` | 1–32 explicit `steps`; optional `detail` | Batch guarded navigation/actions, stopping at decisions or interruptions |
| `game_action` | `action`, optional `detail` | Apply one input and settle animations/speech |
| `new_game` | Optional `detail` | Start a journey and recording |
| `save_game` | Optional `path`, `kind` | Session checkpoint or persistent save |
| `load_game` | Exactly one of `checkpoint`, `path`; optional `kind`, `detail` | Restore checkpoint/file |
| `replay_game` | Exactly one of `path`, `replay`; optional `limit`, `detail` | Reconstruct recording/prefix into the session |
| `export_replay` | Optional `path`, `include_replay` | Return/write history and metadata |
| `simulate_actions` | `actions` (at most 1000), optional `detail` | Execute on an isolated session copy |

Coordinates are zero-based on an 11×11 board; full maps use `map[y * width + x]`.
`detail` selects:

- `summary`: hero, sparse inventory/equipment, phase, choices, save/recording
  readiness and feedback. Mutation `changes` includes stat deltas, changed item
  values (zero after consumption), resulting-floor tile changes and `floor_changed`.
- `compact`: summary plus `floor.id`, `walkable_rows`, `points`, `tile_types`,
  Wisdom clues and Flight preview. Row strings use `.` for apparent road,
  `#` otherwise. Points have `id`, `x`, `y`, and available route information
  `reachable`/`walk_steps`; resolve names, values, key requirements and forecasts
  through `tile_types["<id>"]`.
- `full`: legacy hero/inventory/map/Flight/dialogue/status fields, detailed
  tile/enemy/equipment/item/clue data, interactions, step count, last action,
  recent speech log (100 entries), and save/recording metadata. Developer mode
  also exposes all 51 floors, shared monster rows, hero flags and pending commands.

`game_state`, new/load/replay/simulation default to compact; action/navigation
use summary. A floor-changing mutation upgrades summary to compact. Legacy
clients can request `full`. `reachable` describes apparent-road contact;
`available` describes a key, known survivable fight, or recognized ending trigger.
Routes do not predict scripts or damage, and sealed gates may refuse contact.

On first-cycle floor 50, both Zeno frames are reported as `kind: "trigger"`,
`interaction: "ending"`, `hp_cost: 0`, and `available: true`, even without the
Hero Orb. This contact starts the ending and carries HP into the next cycle;
it has no enemy combat forecast. Floor 49 and later-cycle Zeno retain enemy
statistics and combat forecasts.

Normal mode conceals walls/objects as brick and special roads as road, and hides
private flags/unpreviewed maps. Enemy forecasts and manual saves require the
Hero Orb. Forecasts include cycle and Cross/Dragon Slayer rules.

`last_action.accepted` reports the input handler result; `ok` also detects
unchanged movement contacts. `moved` distinguishes opening a door from entry.
Refused contacts remain recorded. Inputs increment `steps`; new game resets it.
Recorded file loads derive it from history, unrecorded loads start at zero.
Automatic speech appears in `last_action.messages` or `navigation.messages`;
full observations expose the retained log. Shops wait for `choose` or `cancel`.

Resources are `tos://state`, `tos://rules` (input schema/save information), and
`tos://replay`. Successful tools return `structuredContent` and equivalent JSON
text. Tool validation/execution failures use `isError`; invalid envelopes or
unknown methods/tools/resources use JSON-RPC errors. Failed execution,
reconstruction and file loads preserve the live session.

## Player inputs

`game_action.action` uses the [JSONL command contract](replay-verification.md#commands-and-automatic-work).
The catalog rejects unknown fields/types. Flight requires adjacent-stair entry
in both modes; an open selector blocks other active items and
`inventory_items[].usable` reflects entry legality. Preview direction writes
are retained and floor 44 is skipped. See [mechanics](mechanics.md) for the
entry and redraw rules.

`plan_path` traverses apparent road and allows an event only at the endpoint.
An unreachable target returns the closest road prefix and `reached: false`.
`navigate` instead executes zero inputs when unreachable. For example:

```json
{"x":5,"y":8,"floor":4}
```

`floor` guards stale coordinates without mutation. `interact` defaults to true:
contact the selected endpoint and enter a door after opening it. False stops
at an event's approach square; road endpoints are still reached. Navigation
never crosses unselected pickups, doors, enemies or NPCs. It stops on unexpected
state changes, scripts/damage, interactions, floor changes or death. Concealed
walls require deliberate `game_action` contact.

`navigation` contains `target`, executed `inputs`, aggregated `messages`,
`reached` and `reason`; response `changes` covers the whole call. Reasons include
`arrived`, `ready_to_interact`,
`floor_changed`, `blocked_by_event`, `not_a_destination`, `refused`,
`interaction_open`, `interrupted`, `dead`. Event arrival means contact; with
`interact: false`, it means reaching the approach. Refresh `game_state` after
scripted rearrangements. A manual door contact opens it; the next move enters.

## Saving and restoring

`save_game` without arguments returns an opaque session ID, for example
`{"checkpoint":"checkpoint-1","persistent":false}`. `load_game` with that ID
restores the exact session, including open interactions, recording and feedback.
Up to 64 checkpoints survive new game within the connection and expire at exit.
File saves also create a session checkpoint while capacity remains. At the limit,
no-path saves fail, while file saves still succeed and return `checkpoint: null`;
existing session checkpoints remain available for loading.

For persistence, call `save_game`/`load_game` with
`{"path":"D:/games/tower/Savedat/save1.dat","kind":"slot"}`. Kind defaults to
`slot`; `checkpoint` selects the raw Fairy format, distinct from an opaque
session checkpoint. File saves require an idle game and closed Flight selector.
The compatible 6,957-byte format omits transient interaction/history state and
applies load-time Zeno reconstruction; see [save layout](original-data.md).

Active recording writes `FILE.replay.jsonl`; a matching load resumes history
and adds its reload boundary. Missing/invalid companions allow loading but
report recording unavailable. [Recording rules](replay-verification.md#loading-and-replacing-saves)
cover branches, backups and freshness. Start a new game or import a complete
replay to obtain reproducible recording again.

## Replay, rewind and takeover

`export_replay` returns inline `replay`, `inputs`, `bytes` by default. With `path`,
it writes JSONL and returns metadata; `include_replay: true` also echoes text.
Without a path, `include_replay: false` returns metadata only.

`replay_game` accepts inline JSONL or a file beginning with `new_game`. `limit`
counts consumed inputs, including new game; omission runs all. The returned
`replay` reports `executed`, `total`, `complete`. Success replaces the session
and recording with that prefix; subsequent inputs take over and extend it.
Re-import a shorter prefix to rewind. The whole file is validated before commit;
errors leave game, recording and checkpoints intact.

Limits are 100,000 inputs and 8 MiB per recording/request. Replay writes no game
save files; save/reload/Fairy boundaries run in memory. [Replay documentation](replay-verification.md)
covers input/ranking records, CLI prefix behavior and desktop playback.

## Verification

From the repository root:

```powershell
./build/cpp/vs/Release/tsw_tests.exe "[mcp]"
python cpp/tools/check_mcp.py --cli ./build/cpp/vs/Release/tsw_cli.exe
python cpp/tools/check_mcp_reload.py --cli ./build/cpp/vs/Release/tsw_cli.exe
```

Catch2 checks protocol, visibility, navigation, saves/replay and isolation.
CTest's `mcp_stdio` checks process/file behavior; `mcp_reload` checks transfer,
rollback, catalogs, crash/timeouts and worker cleanup. Follow the
[audio test rule](../cpp/README.md#validate-and-package) for broader runs.

## Explicit step batches and offline planner scripts

`run_steps` reduces round trips for an already chosen sequence. It uses the
same native actions and apparent-road navigation as `game_action`/`navigate`;
it does not link the offline planner or run its macro language.

```json
{
  "steps": [
    {"type": "navigate", "floor": 1, "x": 4, "y": 9},
    {"type": "action", "floor": 1,
     "action": {"type": "move", "direction": "left"}}
  ],
  "detail": "summary"
}
```

Every step requires the expected current `floor`. A navigation step accepts
`x`, `y`, and optional `interact`. An action step accepts the normal native
`action` object, except resets, saves and reloads. Batches have 1–32 steps;
all syntax is validated before any input executes. Loops, nested batches,
file paths, arbitrary code and planner commands are not accepted.

Execution stops on a floor mismatch, refused action, interrupted navigation,
HP loss, death, floor/cycle change, or an open shop/Flight interaction. A shop
opening stops even if a purchase was supplied as the next step: inspect the
returned offer, then submit the explicit choice in a subsequent call. A
`flight_confirm` can be supplied in a later call after inspecting Flight.
Explicitly selected pickups and opened doors can complete normally.

Successful inputs remain in the session and native replay; this is not a
rollback or dry-run API. The response includes final state, aggregate changes,
and `batch.complete`, `batch.reason`, `batch.executed_steps`, `batch.stopped_at`
(zero-based, or -1 on completion), and per-step results. An executed navigation
can stop partway, so inspect its result before deciding where to resume.
`batch.complete` is false on an interruption even if it occurred in the final
requested step. A malformed request executes nothing.

Keep strategic commands such as planner `room`, `sweep` and search offline:
they can choose intervening fights, spend keys and collect supplies using
planner knowledge. An MCP batch contains only destinations and inputs already
chosen by the caller, with the ordinary observation and interaction boundary.
