# Replay recording, visual playback and CLI

The desktop, headless CLI and [MCP](cpp-mcp.md) use the same JSONL player inputs.
Recordings replay through gameplay and can be watched without their companion
save. [Build, launch and controls](../cpp/README.md#visual-replay-recording-and-headless-cli)
are in the C++ README. Rust replay comparison remains separate work.

## Opt in and save

Recording is off by default. Enable **Settings > Record new games** before a
fresh game, or launch with `--record`. Enabling it during play waits for a new
game or a load with an existing history; disabling stops recording immediately.
`--record` overrides the saved preference for that launch.

Each recorded save gets a `FILE.replay.jsonl` companion: manual
`save1.dat`–`save8.dat`, `quick.save`, or raw Fairy `save0.dat`. It contains the
history from new game through that save. Unsaved inputs remain in memory.
Copy both files when moving a recorded save. **Recording** in the game header
indicates an active history; the binary save format remains unchanged.

## Loading and replacing saves

With recording enabled, a matching companion restores the saved history,
discards the abandoned branch and adds a `reload` boundary. Replay applies the
save serializer and loader in memory, including shared Zeno reconstruction.
A missing, stale, malformed, incomplete or wrong-kind companion leaves the game
load usable but unrecorded. With recording off, companions are ignored.

Replacement preserves `FILE.bak` and its available `.replay.jsonl` companion.
An unrecorded save removes the stale current companion. Recording is staged
before save replacement; a later recording write failure stops recording and
reports that the game was saved. External-overwrite detection uses timestamps,
not content checksums.

Startup loading follows these rules; `--checkpoint` selects a raw Fairy file:

```powershell
./build/cpp/vs/Release/tsw_game.exe --record --load ./Savedat/save3.dat
./build/cpp/vs/Release/tsw_game.exe --record --load ./Savedat/save0.dat --checkpoint
```

## Replay and inspect

**Play replay** accepts save-directory recordings, typed/pasted paths and dropped
files. `--replay FILE` launches directly. Playback runs queued animations and
cutscenes, delays non-choice speech and the ending card, and applies recorded
shop choices. Live gameplay input waits for takeover. A completed replay stays
paused; an invalid sequence pauses with the affected step and error.

A step is one recorded input, including `new_game`, save/reload and sparse
`rankings` updates. Previous/Restart reconstruct a prefix using gameplay;
failure preserves the displayed game. Long prefixes take longer and restart
the music track without reconstructing elapsed MIDI time. Takeover retains the
consumed prefix when recording is enabled, including during an animation.
Watching handles save/reload and Fairy boundaries in memory and writes no game
or ranking files. Keyboard controls are listed in the
[C++ README](../cpp/README.md#visual-replay-recording-and-headless-cli).

CLI commands, from the repository root:

```powershell
./build/cpp/vs/Release/tsw_cli.exe state
./build/cpp/vs/Release/tsw_cli.exe replay FILE --limit 3 --map-floor 2
Get-Content tests/replays/first-floor-door.jsonl | ./build/cpp/vs/Release/tsw_cli.exe headless
```

`state` prints initial JSON; `replay` prints final JSON; `headless` reads JSONL
from stdin and prints after each command. `--limit N` stops reading after N
inputs, so later lines are not validated. Each mode accepts `--load FILE`, plus
`--checkpoint` for a raw Fairy record. Fresh-game recordings need no save file.

Output includes named hero values, inventory, dialogue/shop text, Flight,
death/status and the current map. `--map-floor 0..50` selects another floor.
Stdout contains JSON; invalid input and file errors go to stderr with nonzero
exit status. Gameplay refusals remain inspectable engine outcomes.

## Commands and automatic work

Each line is one object. Required fields, unknown fields and player choices are
validated; object field order is irrelevant.

```jsonl
{"type":"new_game"}
{"type":"move","direction":"up"}
{"type":"use_item","item":"bomb"}
{"type":"use_item","item":"flying_orb","floor":35}
{"type":"choose","choice":"leave"}
```

Directions are `up`, `down`, `left`, `right`; item names appear in CLI inventory.
Choices accept strings `0`, `1`, `2`, `leave`, or aliases `hp`, `attack`,
`defense`, `accept`; the recorder stores indices. Rust offer IDs need an adapter.

Exact Flight inputs are `flight_open`, `flight_up`, `flight_down`,
`flight_confirm`, and `cancel`, with only `type`. They retain preview writes,
reversals and cancellation; direct Flight item use selects monotonically.
`save` and `reload` use `kind: "slot"` or `"checkpoint"` and operate in memory.
These boundary/Flight inputs need Rust support before cross-engine comparison.

A `rankings` record supplies `tables`: five arrays of ten entries, each with
`score`, `hp`, `attack`, `defense`, `name`. The recorder emits updates when the
in-memory Fairy tables change, including custom initial tables. Playback uses
them without reading current ranking files; older recordings use defaults.

Headless execution drains automatic commands, advances non-choice dialogue and
waits for explicit shop choices. Death/stopped states end the drain; a command
budget detects endless queues. Recordings retain gameplay attempts and refused
contacts, omitting frames, input polls, visual acknowledgments and timing.

## Focused checks

```powershell
python cpp/tools/check_replay.py tests/replays/first-floor-door.jsonl tests/replays/first-floor-door.expected.json --cli ./build/cpp/vs/Release/tsw_cli.exe
```

Expected JSON selects fields/map indices; failures identify differing values.
Passing proves those assertions along that path. Use a shorter prefix and a
focused assertion to investigate an interaction.

Catch2 covers inputs, Flight, save/recording branches, prefix reconstruction,
takeover, settings and failure recovery. Desktop checks compare animated and
headless results, save bytes after takeover, and unchanged files during watching.
CTest runs the short door replay and blocked prefix when Python is available.
Fixtures live in `tests/replays/`; generated reports stay in `build/`. Follow
[the audio test rule](../cpp/README.md#validate-and-package) when running tests.
Research probes and raw state setters are separate from replay commands.
