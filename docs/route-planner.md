# Offline route planner

`tsw_route` searches/verifies first-cycle routes through the native engine.
It is optional (`TSW_PLANNER=OFF`) and separate from the live MCP session.

## Build and test

From the repository root, with the [Windows build](../cpp/README.md#build-on-windows)
already configured:

```powershell
cmake -S cpp -B build/cpp/vs -DTSW_PLANNER=ON
cmake --build build/cpp/vs --config Release --target tsw_route tsw_planner_tests
```

Format C++ after building per [AGENTS.md](../AGENTS.md), including `cpp/planner/`.
Then run `ctest --test-dir build/cpp/vs -C Release -L planner -LE audio`.
For headless builds add `-DTSW_GUI=OFF` in a separate build directory.
Windows executable: `build/cpp/vs/planner/Release/tsw_route.exe`.

## Commands

Run `tsw_route --help` for arguments and search limits.

| Command | Purpose |
|---|---|
| `inspect REPLAY [PREFIX]` | Print state at an input boundary |
| `verify REPLAY` | Check the first-cycle seal challenge |
| `search REPLAY PREFIX OUTPUT_PREFIX` | Search toward first 11F/21F arrival |
| `improve REPLAY BOUNDARY OUTPUT.jsonl` | Try earlier stat pickups on 1–20F |
| `economy REPLAY OUTPUT_PREFIX` | Try key detours, bypasses and omitted trades |
| `ledger REPLAY` | Report milestone resources and combat margin |
| `run REPLAY SCRIPT OUTPUT.jsonl` | Execute a route script |
| `rebase ORIGINAL NEW_PREFIX SPLIT OUTPUT.jsonl` | Resume a continuation after a changed prefix |

Boundaries count inputs including `new_game`. Search writes numbered goals or
`-partial.jsonl`; existing files are not overwritten. Exit codes: 0 success,
1 error, 2 bounded search without its goal. Partial results do not satisfy it.

## Route scripts

Coordinates are zero-based; `#` starts comments.

| Command | Action |
|---|---|
| `go X Y` / `room X Y` | Road-only path / route through intervening events |
| `land F [X Y]` | Native Flight landing |
| `move up/down/left/right` | One movement contact |
| `buy -1/0/1/2` | Leave/select offer |
| `item NAME` | Use `warp/magic/elixir/bomb/snow/ascent/descent/mattock/super` |
| `sweep` | Collect reachable free events, retaining healing |

`room` can spend keys and collect items. Failure exports no route. These
strategic commands are unavailable to MCP `run_steps`, which batches explicit
inputs/destinations only.

[Fixtures](../tests/replays/first-cycle-seal.md) retain verified routes and
optimizer regressions. Search is heuristic and bounded; successful verification
proves the challenge assertions, not optimality or complete original-game fidelity.
