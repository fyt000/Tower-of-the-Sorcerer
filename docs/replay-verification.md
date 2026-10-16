# Replay and CLI

## Recording and saves

Enable **Settings → Record new games** or `--record` before a new game. During
play, enabling waits for a new game or a load with existing history; disabling
stops immediately. Each recorded save gets `FILE.replay.jsonl`; copy both files.

With recording enabled, loading a matching companion resumes its history and
adds a `reload` boundary. Missing/invalid/stale companions allow an unrecorded
load. Replacement preserves `.bak` and its available companion; an unrecorded
save removes stale current history. Replay boundaries use save reconstruction
in memory and write no game/ranking files.

## Visual playback

Choose **Play replay** or pass `--replay FILE`; no companion save is needed.

| Key | Action |
|---|---|
| Space | Pause/resume |
| Left / Right | Previous/next input boundary |
| Home | Restart paused |
| T | Take over |
| − / + | Speed |
| O / Esc | Settings / main menu |

Rewind reconstructs a prefix. Takeover retains that prefix when recording is
enabled. Completion pauses; invalid sequences pause at the failed input.

## CLI

From the repository root:

```powershell
./build/cpp/vs/Release/tsw_cli.exe state
./build/cpp/vs/Release/tsw_cli.exe replay FILE --limit 3 --map-floor 2
Get-Content FILE | ./build/cpp/vs/Release/tsw_cli.exe headless
```

`state` prints initial JSON; `replay` prints final JSON; `headless` prints after
each input. `--load FILE` accepts a slot; add `--checkpoint` for raw Fairy data.
`--limit N` counts inputs including `new_game` and does not validate later lines.
Errors go to stderr with nonzero status; refusals remain gameplay outcomes.

## Commands and automatic work

JSONL contains one input object per line:

```jsonl
{"type":"new_game"}
{"type":"move","direction":"up"}
{"type":"use_item","item":"bomb"}
{"type":"use_item","item":"flying_orb","floor":35}
{"type":"choose","choice":"leave"}
```

Directions: `up/down/left/right`. Items use CLI inventory names. Choices accept
`0/1/2/leave` or `hp/attack/defense/accept`. Exact Flight inputs are `flight_open`,
`flight_up`, `flight_down`, `flight_confirm`, `cancel`. `save/reload` use
`kind: slot/checkpoint` in memory. `rankings` supplies five tables of ten
`score/hp/attack/defense/name` records.

Automatic commands/dialogue settle until a choice, stop or death. Attempts and
refused contacts are recorded; frames, polls and elapsed timing are omitted.
The [input implementation](../cpp/src/replay.cpp) defines validation.

## Focused checks

```powershell
python cpp/tools/check_replay.py tests/replays/first-floor-door.jsonl tests/replays/first-floor-door.expected.json --cli ./build/cpp/vs/Release/tsw_cli.exe
```

Expected JSON selects asserted fields/map indices. Campaign fixtures are in
[tests/replays](../tests/replays/first-cycle-seal.md). See [MCP](cpp-mcp.md) for
session import/export.
