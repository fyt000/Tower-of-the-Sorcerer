# Native C++ MCP mode

`tsw_cli mcp` serves the C++ game over newline-delimited JSON-RPC on stdin/stdout.
It uses the same `Game`, player inputs, original save writer/loader and recorder
as the desktop and headless CLI. The runtime needs no Node, Python, assets,
window or audio device. It is available with `TSW_GUI=OFF`.

Flight requires legal adjacent-stair entry for both `flight_open` and direct
`use_item` travel, in developer mode as well as normal mode. A selector session
blocks other active items. `inventory_items[].usable` includes the Flight
entry condition. Historical recordings made with the unrestricted Flight bug
can diverge under the corrected rules; see the [fidelity audit](fidelity-audit-2026-10-09.md).

From the repository root:

```powershell
./build/cpp/vs/Release/tsw_cli.exe mcp
./build/cpp/vs/Release/tsw_cli.exe mcp --load ./Savedat/save1.dat
./build/cpp/vs/Release/tsw_cli.exe mcp --load ./Savedat/save0.dat --checkpoint
./build/cpp/vs/Release/tsw_cli.exe mcp --developer
```

A client that accepts an `mcpServers` configuration can launch it directly:

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

Use an absolute executable path. File arguments to tools resolve relative to the
server's working directory; absolute save and replay paths are recommended.
Initialization negotiates `2025-11-25`, `2025-06-18`, `2025-03-26` or `2024-11-05`.
The client sends `notifications/initialized` before calling tools/resources.
Stdout contains only protocol messages, and EOF closes the server.

## Python bridge and hot reload

For development, use the stable Python bridge instead of launching the build
output directly. It requires Python 3.10 or later and only uses the standard
library. Configure/build C++ as described in [the C++ README](../cpp/README.md),
then publish a worker from the repository root:

```powershell
python cpp/tools/build_mcp.py --build-dir build/cpp/vs
python cpp/tools/mcp_server.py
```

`build_mcp.py` builds `tsw_cli` in an already configured CMake directory and
publishes it. `--cmake PATH` selects CMake explicitly, and `--config` defaults
to `Release`. For a headless build use `--build-dir build/cpp/core`. To publish
an executable that has already been built:

```powershell
python cpp/tools/mcp_deployment.py build/cpp/vs/Release/tsw_cli.exe
```

Configure the MCP client to keep the Python process running:

```json
{
  "mcpServers": {
    "tower-cpp": {
      "command": "python",
      "args": ["D:/projects/tos-rust/cpp/tools/mcp_server.py"]
    }
  }
}
```

Add `--developer` to the bridge arguments to expose developer observations and
simulations. The bridge also accepts `--load FILE` (`--save` is an alias) and
`--checkpoint` for a raw Fairy save. The startup save is loaded exactly once,
through JSON-RPC so Unicode paths work on Windows. Later workers receive the
live session even if the startup save has been removed.

Publication copies the binary into an immutable
`build/cpp/dist/mcp/versions/<version>/` directory. It probes initialization,
the tool catalog, and private checkpoint/restore before atomically replacing
`build/cpp/dist/mcp/current.json`. A running worker uses its immutable copy, so
Windows does not lock the compiler's output. A failed probe leaves the current
manifest intact. Version directories remain available for rollback; avoid
removing versions still used by bridges.
On Windows, publication and worker startup validate native console PE headers
before launch. Invalid, legacy, GUI or unsupported-architecture images are
rejected as errors without invoking the Windows legacy loader.

Before each public request, the bridge checks the manifest. A new activation
causes it to checkpoint the old worker, start and initialize a candidate,
restore the complete session, and switch only after restoration succeeds.
Requests and mutations execute in one ordered queue. The transfer includes:

- All 51 floors, hero flags/inventory, live monster rows and last encounter.
- Pending commands, combat, speech/shop continuations, merchant offers/costs,
  death/stopped state and visuals.
- Flight selection, original save record/checksum words, recording status and
  history, action feedback, speech log, step count, and all opaque checkpoints
  with their IDs.

Reload works before obtaining the Hero Orb and while a shop or Flight selector
is open. It transfers current state without replaying actions under new code.
Native `.dat` files continue to use the original save format. The private
runtime checkpoint has its own versioned schema, checks developer-mode
compatibility, validates state before committing, and is limited to 128 MiB.
It is temporary migration data, not a persistent save format. A checkpoint
schema change should increment the runtime version; incompatible workers are
rejected while the old worker continues.

The bridge preserves the native tools/resources and adds `mcp_runtime`, a
read-only tool with no arguments. Its result includes bridge/worker PIDs,
worker health/error, active deployment and the last reload outcome. Successful
reloads attach `result._meta.runtime_reload` to the triggering response.
Tool catalogs that change produce `notifications/tools/list_changed`, with
`tools.listChanged` advertised at initialization, following the
[MCP tool-list notification protocol](https://modelcontextprotocol.io/specification/2025-11-25/server/tools).
An identical catalog produces no notification.

An unreadable/invalid manifest leaves a healthy session playable and reports
the publication error in reload metadata. A failed candidate keeps the previous
worker and returns an error for the triggering request before it executes;
subsequent requests continue on the old worker. That deployment is blocked
until the manifest publishes a different activation. A crashed or timed-out
active worker is reported as unavailable; mutations are never retried because
their commit status may be unknown. Reconnect and load a persistent save when
the live session has been lost.

`--manifest FILE` or `TSW_MCP_CURRENT` selects another manifest. It contains
nonempty string fields `version`, `activation`, and `executable`; the executable
may be absolute or relative to the manifest directory. `--timeout-ms` or
`TSW_MCP_TIMEOUT_MS` sets the worker request deadline (default: 15,000 ms).
Worker stderr drains independently, stdout contains only JSON-RPC, and EOF or
a handled shutdown signal closes workers and removes temporary checkpoints.
The native `runtime/checkpoint` and `runtime/restore` methods require
`tsw_cli mcp --runtime-bridge`; the public bridge always denies `runtime/*`.

## Tools and observations

Normal mode exposes ten tools. `--developer` adds `simulate_actions`.
The Python bridge adds `mcp_runtime` to either catalog.

| Tool | Arguments | Behavior |
|---|---|---|
| `game_state` | Optional `map_floor`, `detail` | Compact current-floor destinations by default; remote floors require developer access or an open Flight preview |
| `inspect_tile` | `x`, `y`, optional `map_floor` | Named tile, pickup values and unlocked native combat forecast |
| `plan_path` | `x`, `y` | Directions through apparent road, with an obstacle allowed as the final contact |
| `navigate` | `x`, `y`; optional `floor`, `interact`, `detail` | Execute native walking to a selected destination; activate its event by default; stop on unexpected events |
| `game_action` | `action`, optional `detail` | One native input, with animation/speech settling; summary by default |
| `new_game` | Optional `detail` | New journey and replay recording; compact observation by default |
| `save_game` | Optional `path`, `kind` | Session checkpoint; optionally an original `.dat` and replay companion |
| `load_game` | Exactly one of `checkpoint` or `path`; optional file `kind`, `detail` | Restore a checkpoint or native save; compact by default |
| `replay_game` | Exactly one of `path` or inline `replay`; optional `limit`, `detail` | Reconstruct a JSONL recording or prefix into the live session; compact by default |
| `export_replay` | Optional `path`, `include_replay` | Write a recording and return metadata; without a path, return inline JSONL by default |
| `simulate_actions` | `actions`, at most 1000; optional `detail` | Developer-only execution on a complete native session copy; compact by default |

Coordinates are zero-based, with `(0,0)` at the top left. The board is 11×11;
`map[y * width + x]` indexes a square in full observations. The `detail` argument
selects one of three views:

- `summary`: current hero, sparse inventory, equipment, phase, pending choices,
  save/recording availability and action feedback. Mutations add `changes` with
  stat deltas, changed inventory **values** (including zero on consumption),
  changed tiles on the resulting floor, and `floor_changed`.
- `compact`: summary fields plus `floor.id`, `floor.walkable_rows`,
  `floor.points`, `tile_types`, Wisdom clues and any open Flight preview.
  The 11 row strings use `.` for apparent road and `#` for other squares.
  Each point contains `id`, `x`, `y`, and, when navigation can be planned,
  `reachable` and `walk_steps`. Resolve the point's ID through
  `tile_types["<id>"]` for its name/kind, pickup value, key requirement or
  unlocked enemy forecast. Definitions occur once per type rather than once
  per square. `reachable` means a route through apparent road can contact the
  target; `available` in its type means the hero has the key or can survive the
  known fight. A reachable sealed gate can still refuse contact. Neither
  field predicts undiscovered scripts or damage along the route.
- `full`: the legacy headless fields (`hero`, `inventory`, `map_floor`, `map`,
  `flight`, `dialogue`, `dead`, `status`) plus the detailed fields below.
  Developer mode includes all 51 floors only in this view.

`game_state` defaults to compact; `game_action` and `navigate` default to
summary. A mutation that changes floor automatically returns compact when
summary was requested. Other views can be requested explicitly. Clients that
consume the pre-0.10 state shape should pass `detail: "full"`; its projection
is unchanged. Version 0.11 consolidates the temporary 0.10 `enemy_types` and
per-point descriptions into `tile_types`.

For example, a compact observation can include:

```json
{
  "floor": {
    "id": 4,
    "points": [{"id": 1, "x": 5, "y": 8, "reachable": true, "walk_steps": 3}]
  },
  "tile_types": {
    "1": {"name": "Yellow door", "kind": "door", "key": "yellow", "available": true}
  }
}
```

This is an excerpt; the real response also contains walkable rows and current
hero state. Full observations additionally contain:

- Named `tile_defs`, enemy positions, Hero Orb forecasts, and last defeated enemy.
- Equipment, Sacred Shield protection, cycle factor and later-cycle state.
- Owned items with charges and native usage instructions, Wisdom Orb clues,
  and legal Flight destinations.
- `pending_interaction` with reply IDs, gold costs and affordability, `phase`,
  `steps`, `last_action`, and a
  recent dialogue `log` (at most 100 entries).
- Save availability, file-save readiness and recording availability/input count.

Normal observations present concealed walls/objects as ordinary brick walls,
special road as apparent road, and keep private flags and unpreviewed maps out
of the response. Enemy forecasts and manual saving require the Hero Orb.
Developer full observations add all 51 floors, 33 current shared monster rows,
the named hero state and any pending original commands. Forecasts use
`Game::forecast`, including cycle scaling and Cross/Dragon Slayer rules.

`last_action.accepted` is the native input handler's result; `ok` also detects
movement contacts that leave the board and hero unchanged. Valid refused
contacts remain recorded. `moved` distinguishes opening a door from entering
it. Every input except new_game increments `steps`; a new game resets it.
A recorded native load derives its counter from the resumed history; an
unrecorded native load begins at zero.

Speech advances automatically, as in the existing headless replay. Each
encountered speech is returned in `last_action.messages` (or aggregated into
`navigation.messages`) and retained internally in `log`. Full observations
expose that history; compact and summary omit it.
Shop decisions remain open until a `choose` or `cancel` action. This uses the
original continuations, including their private shop state.

The resources `tos://state`, `tos://rules` and `tos://replay` provide the current
observation, native input schema/save information and active JSONL history.
Successful tools return both `structuredContent` and its JSON text equivalent.
Tool validation/execution failures set `isError`; malformed envelopes, unknown
methods/tools and resources use JSON-RPC errors. Failed actions, replay
reconstruction and native loads preserve the live session.

## Player inputs

Inputs use the existing C++ JSONL contract, for example:

```json
{"type":"move","direction":"up"}
{"type":"choose","choice":"0"}
{"type":"choose","choice":"leave"}
{"type":"use_item","item":"bomb"}
{"type":"use_item","item":"flying_orb","floor":12}
{"type":"flight_open"}
{"type":"flight_up"}
{"type":"flight_down"}
{"type":"flight_confirm"}
{"type":"cancel"}
```

`choose` also accepts `accept`, `hp`, `attack`, `defense` and `0` through `2`.
Only listed choices apply to the current shop. Flight previews retain the
original selection-direction writes; floor 44 is skipped. Door contact opens
the door without moving into its square. Another move enters it.

The existing `save` and `reload` inputs with `kind: "slot"` or `"checkpoint"`
exercise the original serializer in memory. `save_game` and `load_game` provide
actual checkpoints and file persistence. The tool catalog includes the full
action schema and rejects unknown fields or invalid types.

Path planning reads appearances without running the game. It traverses road
and may end with a contact against any target; it never crosses keys, doors,
enemies or NPCs as intermediate squares. Scripts, magic damage and stair
transitions can interrupt a planned route. An unreachable target returns the
closest reachable road prefix and `reached: false`.

For ordinary play, choose an event from compact `floor.points` and call:

```json
{"x": 5, "y": 8, "floor": 4}
```

These are `navigate` arguments. `floor` is an optional stale-coordinate guard;
a mismatch is an error with no mutation. `interact` defaults to true. The
server executes the apparent-road route, contacts the endpoint and, for a
selected door that opens, supplies the second input to enter it. Enemy fights,
pickups, stairs and NPC interactions use the same native inputs as manual
play. Every step remains in the replay. `interact: false` stops at the approach
square for an event; an ordinary road endpoint is still reached.

Navigation never crosses an unselected pickup, enemy, door or NPC. Unlike the
read-only `plan_path`, an unreachable target executes **zero inputs**. It stops
when an intermediate step causes a script, damage or other unexpected state
change, or opens an interaction, changes floor or kills the hero. Concealed
walls remain walls in normal-mode navigation; deliberately contacting a wall
from a clue still uses `game_action`.

The response includes `navigation.target`, `inputs`, aggregated `messages`,
`reached` and a `reason`, such as `arrived`, `ready_to_interact`, `floor_changed`,
`blocked_by_event`, `not_a_destination`, `refused`, `interaction_open`,
`interrupted` or `dead`. For an event, `reached` denotes endpoint contact rather
than occupying its square; for `interact: false`, it denotes reaching the
approach. `changes` covers the whole navigation call. After a scripted map
rearrangement, read compact `game_state` to refresh destinations and type data.

## Saving and restoring

Calling `save_game` without arguments returns:

```json
{"checkpoint":"checkpoint-1","persistent":false}
```

Pass that ID to `load_game` to restore the complete native session, including
an open shop or Flight preview, private continuations, live checksum words,
recording, dialogue log and counter. Checkpoints survive new_game within the
same connection. They expire when the process exits and are limited to 64 per
connection. They are C++ copies, not a separate JSON state/save schema.

For a save that persists after disconnect:

```json
{"path":"D:/games/tower/Savedat/save1.dat","kind":"slot"}
```

These are `save_game` arguments. Load it with the same `path` and `kind` through
`load_game`, or launch `mcp --load FILE`. Kind defaults to `slot`. Kind
`checkpoint` reads/writes the original raw Fairy format; it is distinct from
an opaque **session checkpoint**. A file save requires an idle live game and a
closed Flight selector. Session checkpoints can retain open interactions.

File saves use the unchanged 6,957-byte original format, checksums, backup
behavior and load-time shared-Zeno reconstruction. An active recording writes
`FILE.replay.jsonl` alongside the save. Loading a matching companion resumes
that history, adds the original reload boundary, and discards later moves.
An absent, stale or invalid companion does not prevent loading the game; the
result reports that recording is unavailable. Start a new game or import a
complete replay to begin a reproducible recording again.

Session checkpoints restore an exact native copy. Native file loads deliberately
apply the original load reconstruction and omit transient presentation/history
that the `.dat` format does not store.

## Replay, rewind and takeover

`export_replay` without a path returns the active history as a `replay` string,
input count and byte count. Supply `path` to write the same JSONL and receive
only `path`, `inputs` and `bytes`; set `include_replay: true` to also echo the
text. `include_replay: false` without a path returns metadata only. The history includes refused contacts,
save/reload boundaries and exact Flight inputs, and is compatible with
`tsw_cli replay` and the desktop's **Play replay**.

`replay_game` accepts that string or a JSONL file path. A recording must begin
with `new_game`. `limit` selects the number of inputs to consume, including
that initial new_game; omitting it runs the entire recording. The returned
`replay` object reports `executed`, `total` and `complete`. Successful playback
replaces the session with the resulting game and prefix recording. The next
game_action continues from that position, so export after takeover contains
the consumed prefix plus new decisions. Re-importing with a smaller limit
rewinds through real inputs; no snapshot cache is involved.

The whole JSONL is parsed before committing. Parse errors or execution failures
leave the existing game, recording and checkpoints intact. Recordings are
limited to 100,000 inputs and 8 MiB; each protocol request is limited to 8 MiB.
Replay execution never writes gameplay save files. Recorded save/reload and
automatic Fairy boundaries exercise the original serializer in memory.

The CLI and full replay parser share an incremental JSONL reader with line
numbers; the CLI's `--limit` stops reading at the requested prefix. Recorder
companions and MCP export share the JSONL writer. Headless actions and replay
seek share typed settled execution and feedback; MCP records the outcomes of
the same `ReplayPlayer::seek` used by desktop rewind. Desktop forward playback
continues to leave animations queued for its scheduler.

## Verification

The normal C++ build includes named `[mcp]` Catch2 cases for protocol errors,
observations, concealment, forecasts, dialogue, checkpoints, Flight, native
saves, replay, compact type definitions, destination navigation, interruptions,
complete runtime snapshots and simulation isolation. When Python is available, CTest also
runs `mcp_stdio` against the actual executable, including Unicode filenames,
process restart, native save/load, replay prefix/takeover and CLI parity:

```powershell
./build/cpp/vs/Release/tsw_tests.exe "[mcp]"
python cpp/tools/check_mcp.py --cli ./build/cpp/vs/Release/tsw_cli.exe
python cpp/tools/check_mcp_reload.py --cli ./build/cpp/vs/Release/tsw_cli.exe
```

`mcp_reload` checks the real Python bridge and native workers: stable bridge PID,
worker replacement, exact state/history/checkpoint preservation, normal-mode
reload before the Hero Orb, Unicode startup saves consumed once, open shops
and Flight, ordered mutations, malformed manifests, blocked deployments,
incompatible restore rollback, changed/unchanged catalogs, stderr draining,
publisher probe failures, crash/timeout diagnostics without mutation retries,
and worker cleanup on EOF.

See [the first-ten-floor playtest](cpp-mcp-playtest.md) for a recorded normal-mode
completion, source-backed resource strategy, measured payload savings and the
client catalog-refresh limitation observed during live development.
