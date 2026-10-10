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

Client configuration:

```json
{
  "mcpServers": {
    "tower-cpp": {
      "command": "D:/projects/tos-rust/build/cpp/vs/Release/tsw_cli.exe",
      "args": ["mcp"]
    }
  }
}
```

Use absolute executable/file paths; tool file arguments otherwise resolve against
the server working directory. Initialization supports `2025-11-25`, `2025-06-18`,
`2025-03-26` and `2024-11-05`. Send `notifications/initialized` before tools or
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
`D:/projects/tos-rust/cpp/tools/mcp_server.py`. Bridge options include
`--developer`, `--load FILE` (`--save` alias), and `--checkpoint`. A startup save
is loaded once, using JSON-RPC for Unicode paths; replacement workers receive
the live session.

Publication probes initialization, catalog and checkpoint/restore before
atomically replacing `build/cpp/dist/mcp/current.json`. Workers use immutable
copies in `versions/<version>/`, allowing Windows rebuilds. Failed publication
leaves the manifest intact; keep versions that running bridges use. Windows
launches require a supported console PE executable.

Before each public request, a changed activation transfers the complete session
to a candidate: maps/hero/monster/ranking state, pending commands and shop/Flight
continuations, presentation, recording, feedback/log/counter, and checkpoint IDs.
The bridge verifies candidate initialization before switching and preserves
the session when restoration succeeds.
Mutations remain ordered; transfer does not replay inputs under the new code.
Private migration data is versioned and limited to 128 MiB. Compatible sessions
continue unchanged. A structured schema/version/mode incompatibility activates
the healthy new worker with a fresh session instead of blocking the update.
Increment the runtime version when changing that schema; older schemas do not
need migration support.

After that reset, `mcp_runtime` reports `session_continuable: false`,
`recovery_required: true`, and `recovery_tools: ["new_game", "load_game", "replay_game"]`.
The last reload has `status: "reset"`, `session_restored: false`, and the mismatch
reason. Observation results also carry the continuation flag in `_meta`.
Gameplay requests, including the request that triggered the update, return
`-32003` without executing until a successful new game, file load or replay.
`game_action` with `{ "type": "new_game" }` also recovers. Failed recovery keeps
the gate closed; old opaque checkpoint IDs expire. Persistent saves/replays
remain available for deliberate loading under the new build.

The bridge adds read-only `mcp_runtime`, reporting PIDs, worker health/error,
deployment and last reload outcome. Successful reloads attach
`result._meta.runtime_reload`. A changed catalog emits
`notifications/tools/list_changed`; unchanged catalogs do not. Initialization
advertises `tools.listChanged`, following the
[MCP protocol](https://modelcontextprotocol.io/specification/2025-11-25/server/tools).

Invalid manifests keep a healthy session running and report reload metadata.
A candidate startup, I/O or unclassified restore failure returns an error before
the triggering request executes; later requests use the old worker. That activation stays blocked until another
is published. Crashed/timed-out workers become unavailable; mutations are never
retried because commit status may be unknown. Reconnect from a persistent save.

`--manifest FILE` or `TSW_MCP_CURRENT` overrides the manifest. Its nonempty
`version`, `activation`, `executable` strings allow an executable path relative
to the manifest directory. `--timeout-ms` or `TSW_MCP_TIMEOUT_MS` overrides the
15,000 ms request deadline. Stderr drains independently; EOF/shutdown closes
workers and removes temporary checkpoints. Private `runtime/checkpoint` and
`runtime/restore` require `mcp --runtime-bridge`; the public bridge denies
`runtime/*`.

## Tools and observations

Normal mode has ten tools; `--developer` adds `simulate_actions`. The bridge
adds `mcp_runtime`.

| Tool | Arguments | Behavior |
|---|---|---|
| `game_state` | Optional `map_floor`, `detail` | Observe; remote floors require developer access or an open Flight preview |
| `inspect_tile` | `x`, `y`, optional `map_floor` | Tile, pickup values and unlocked combat forecast |
| `plan_path` | `x`, `y` | Read-only apparent-road route, allowing final obstacle contact |
| `navigate` | `x`, `y`; optional `floor`, `interact`, `detail` | Walk to/contact a selected destination |
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
are retained and floor 44 is skipped. Older recordings that used unrestricted
Flight can diverge; see [known differences](../cpp/FIDELITY.md).

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
Some clients need an explicit catalog refresh after tool-list changes.
