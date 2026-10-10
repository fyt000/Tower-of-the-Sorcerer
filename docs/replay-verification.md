# Replay recording, visual playback and CLI

The C++ game can optionally record player commands alongside its original-format
saves. `tsw_cli` plays those commands through the real core without a window,
assets or audio. Rust remains independent; cross-engine comparison is later work.
The desktop game also plays those same recordings with its original animations
and cutscenes and a control bar above the canvas.
The original executable and decompiled evidence remain the reference when a C++
result is in doubt.

Glaze automatically serializes replay records and CLI observations and parses
commands from small C++ aggregates. These types stay in the replay implementation; the
core and original binary saves have no JSON dependency. Commands are checked
for required fields, unknown fields and valid player choices. Existing JSONL
recordings remain readable regardless of object field order.

The desktop recorder, headless CLI and [native MCP mode](cpp-mcp.md) share
JSONL parsing/writing and player inputs in `tsw_replay`. Settled execution
returns typed contact outcomes and captured speech for headless clients;
`ReplayPlayer::seek` uses that execution for desktop rewind and MCP prefix
reconstruction. Forward desktop playback still leaves animation commands
queued for its scheduler. CLI prefixes stop reading at `--limit`; MCP validates
the whole recording before replacing its live session.

## Opt in and save

Recording is off by default. Start with `--record`, or enable
**Settings > Record new games** and choose New game. Enabling the option during play waits
for a new game or a load with an existing recording, so a partial history is never
presented as a complete run. Disabling it immediately stops recording. Settings
persist beside the saves in `settings.json`, including recording, audio mute and
separate gameplay/replay speed choices. `--record` overrides the stored preference
for that launch; changing Settings saves the current preferences.

```powershell
./build/cpp/vs/Release/tsw_game.exe --record
```

While recording is active, each manual, quick or automatic Fairy save writes a
companion next to the original file:

| Save | Recording |
|---|---|
| `Savedat/save1.dat` through `save8.dat` | `save1.dat.replay.jsonl` through `save8.dat.replay.jsonl` |
| `Savedat/quick.save` | `quick.save.replay.jsonl` |
| `Savedat/save0.dat` (raw Fairy record) | `save0.dat.replay.jsonl` |

Each companion contains the history from a new game through that save. Moves
since the last save are held in memory until another save. Copy both files when
moving a recorded save. The original 6,957-byte save and raw Fairy formats are
unchanged. The game header shows **Recording** while a history is active.

## Loading and replacing saves

With recording enabled, loading a save with a complete companion resumes that
saved history, discarding actions from the abandoned branch. The recorder adds a
`reload` command at the boundary. Replay uses the original serializer and loader
in memory there, preserving load-time behavior such as shared Zeno reconstruction.
No native save files are injected into a new replay.

If the companion is missing, malformed, incomplete, for the wrong save kind or
older than a subsequently overwritten save, the game still loads normally and
that loaded game remains unrecorded. Saving it produces no new recording. The
opt-in preference is retained for the next fresh game or recorded load. With the
option off, existing companions are ignored.

Replacement keeps `save1.dat.bak` and, when available,
`save1.dat.bak.replay.jsonl` for the previous pair. Saving without an active
history removes the old current companion, preventing it from being attached to
the new save. Writes stage the recording before replacing the save; a later
recording write failure stops recording and reports that the game was saved.
Timestamps detect ordinary external overwrites; they are not a content checksum.

Startup loading follows the same rules. For a raw Fairy file add `--checkpoint`:

```powershell
./build/cpp/vs/Release/tsw_game.exe --record --load ./build/cpp/vs/Release/Savedat/save3.dat
./build/cpp/vs/Release/tsw_game.exe --record --load ./build/cpp/vs/Release/Savedat/save0.dat --checkpoint
```

## Replay and inspect

The startup menu offers **Play replay**. It lists `.jsonl` files in the save
directory and accepts a typed/pasted path or a file dropped on the window. A
recording can be watched on its own; the companion save is not needed. Launch
directly with `tsw_game --replay FILE`.

| Visual control | Keyboard | Behavior |
|---|---|---|
| Pause / Resume | Space | Freeze/resume gameplay, sprite animation and audio |
| Previous | Left | Reconstruct the boundary before the current input, then pause |
| Next | Right | Finish one input and pause; finish the current input if already in progress |
| Restart | Home | Reconstruct the fresh-game boundary and pause |
| Take over | T | Continue playing from the displayed state and current command queue |
| Speed − / + | − / + | Scale replay pacing and animations from 0.25x through 10x |
| Settings / Menu | O / Esc | Open preferences / return to the startup menu |

The speed choices are 0.25x, 0.5x, 1x, 2x, 3x, 5x and 10x. One step is one
recorded command, including the initial `new_game` and save/reload boundaries.
Sparse `rankings` records also count as steps. They restore the in-memory Fairy
tables used by the recorded run and never write ranking files.
Playback drives the desktop's existing command queue; non-choice speech and the
ending card remain visible for a scaled delay before continuing. Shops wait for
their recorded choices. Live gameplay input is blocked until takeover.

Previous and Restart rebuild a prefix in a temporary `Game` with normal actions
and headless settling. A failed reconstruction leaves the displayed game intact.
There are no snapshots, shared-state schemas or hashes. Reconstructing a long
prefix takes proportionally longer and restarts the selected music track; MIDI
elapsed time is not reconstructed. A finished recording remains paused.

When recording is enabled, takeover keeps the played prefix and records later
decisions, including takeover midway through a queued animation. With recording
off it remains unrecorded. Watching reproduces save/reload effects in memory and
does not write manual, Quick or Fairy files. An invalid command sequence pauses
with the affected step and error; restart/previous can return to a valid prefix.

For headless inspection, use the CLI from the repository root:

```powershell
./build/cpp/vs/Release/tsw_cli.exe state
./build/cpp/vs/Release/tsw_cli.exe replay ./build/cpp/vs/Release/Savedat/save1.dat.replay.jsonl
./build/cpp/vs/Release/tsw_cli.exe replay tests/replays/first-floor-door.jsonl --limit 3
./build/cpp/vs/Release/tsw_cli.exe replay FILE --map-floor 2
Get-Content tests/replays/first-floor-door.jsonl | ./build/cpp/vs/Release/tsw_cli.exe headless
```

`replay` prints final JSON values; `--limit N` stops after N input commands.
`headless` reads JSONL from stdin and prints values after each command. `state`
prints the initial values. Each mode can start from an original slot with
`--load FILE`, or a raw Fairy record with `--load FILE --checkpoint`. A normal
recording starts from a fresh game and needs no `--load`.

Output uses named hero values, item counts, dialogue/shop text, Flight selection,
death status and the current map. `--map-floor 0..50` inspects a particular floor
instead. Stdout contains JSON; malformed input and file errors go to stderr with
a nonzero exit code. Gameplay refusals go through the engine and leave inspectable
values and status, without a separate legality model.

## Commands and automatic work

One JSON object is one player command. Ordinary input shares Rust's existing
command shape:

```jsonl
{"type":"new_game"}
{"type":"move","direction":"up"}
{"type":"use_item","item":"bomb"}
{"type":"use_item","item":"flying_orb","floor":35}
{"type":"choose","choice":"leave"}
```

Directions are `up`, `down`, `left`, `right`. Item names appear in the CLI's
`inventory` output. C++ choices accept `0`, `1`, `2` as strings or `leave`;
`hp`, `attack`, `defense` and `accept` are readable aliases. The recorder writes
choice indices, which will need mapping to Rust's offer IDs in a later adapter.

Exact Flight browsing uses `flight_open`, `flight_up`, `flight_down`,
`flight_confirm` and `cancel`, each with just a `type` field. These retain preview
map writes, reversals and cancellation. A direct `use_item` flight follows the
normal monotonic selection route. Save boundaries use
`{"type":"save","kind":"slot"}` or `checkpoint`; loads use `reload` with the
same kind. These C++ boundary commands and exact Flight inputs need corresponding
Rust support before those traces can be compared.

The recorder adds `rankings` records when the five Fairy tables change, including
custom tables at the start of a game. Their `tables` field contains five arrays
of ten entries, each with `score`, `hp`, `attack`, `defense` and `name`. Playback
uses these values instead of rereading the current ranking files. Older recordings
without these records use the default tables. This preserves the Fairy's rank
and save checksum when tables are updated during a run or after recording it.

Headless replay drains the original automatic command queue without animation delays,
continues dialogue with no decision through its real callbacks and leaves shops
for explicit choices. Death and stopped states terminate the drain; the existing
command budget detects an endless queue. Automatic Fairy writes are reproduced
in memory. Desktop recording retains actual gameplay attempts, including refused
contact, but omits input polls, frames, music, visual acknowledgments and timing.
Movement routes are retained without pathfinding or redundant-input filtering.

## Focused checks

The external script checks only the facts named in a scenario's expected JSON:

```powershell
python cpp/tools/check_replay.py tests/replays/first-floor-door.jsonl tests/replays/first-floor-door.expected.json --cli ./build/cpp/vs/Release/tsw_cli.exe
```

Expected objects can select individual fields and map indices. Failures name the
values that differ. Inspect a shorter prefix or add a focused assertion near the
suspected interaction when investigating. There is no shared whole-world state
schema or state hash. Passing checks establishes those facts on that path, not
equality of every hidden field.

Catch2 covers action behavior, Flight writes, death, native save replay, recording
opt-in, prefix reconstruction, takeover, settings persistence, branch restoration,
missing/stale companions and save failure recovery. Desktop checks exercise the
real scheduling, startup menus, frozen animation, single stepping, rewind,
takeover, shops, automatic speech, fatal combat and the ending/backside transition.
They compare animated/headless observations, verify native save bytes after
takeover and check that watching leaves Quick/Fairy files unchanged. Audio tests
compare the resumed sample stream with an uninterrupted reference.
CTest also runs the short door replay and its blocked prefix when Python is
available. Fixtures live under `tests/replays/`; generated checks stay in `build/`.
`tsw_probe` remains a separate research tool; raw state setters are not replay
commands. Comparison logic stays in tests and tools, outside gameplay.
