# Native route planner

`tsw_route` is an optional offline tool for exploring and verifying first-cycle
routes. It shares the C++ game and replay libraries and executes candidates
through the native engine. It does not modify the connected game session.

## Build and test

After [configuring C++](../cpp/README.md#build-on-windows), enable the planner in
the existing Windows build:

```powershell
cmake -S cpp -B build/cpp/vs -DTSW_PLANNER=ON
cmake --build build/cpp/vs --config Release --target tsw_route tsw_planner_tests
ctest --test-dir build/cpp/vs -C Release -L planner -LE audio --output-on-failure
```

For a separate headless build:

```sh
cmake -S cpp -B build/cpp/planner -DTSW_GUI=OFF -DTSW_PLANNER=ON
cmake --build build/cpp/planner --config Release --target tsw_route tsw_planner_tests
ctest --test-dir build/cpp/planner -C Release -L planner -LE audio --output-on-failure
```

`TSW_PLANNER` defaults to `OFF`. The component lives in
[cpp/planner](../cpp/planner/README.md); the game and MCP do not depend on it.
Follow the repository's formatting instructions after a successful build,
including the planner's C++ files.

## Commands

Run `tsw_route --help` for complete syntax and defaults.

| Command | Purpose |
|---|---|
| `inspect REPLAY [PREFIX]` | Replay through an input count and print the state. |
| `verify REPLAY` | Check the complete first-cycle 50F seal challenge. |
| `search REPLAY PREFIX OUTPUT_PREFIX` | Search event orders from a replay prefix toward first arrival at 11F or 21F. |
| `improve REPLAY BOUNDARY OUTPUT.jsonl` | Try earlier stat pickups on floors 1–20, preserving resources at the comparison boundary and validating the full continuation. |
| `economy REPLAY OUTPUT_PREFIX` | Try key detours, door bypasses and omitted key trades against the complete seal continuation. |
| `ledger REPLAY` | Report milestone resources, merchant transactions, key spending and final combat margin. |
| `run REPLAY SCRIPT OUTPUT.jsonl` | Execute a route script after a replay. |
| `rebase ORIGINAL NEW_PREFIX SPLIT OUTPUT.jsonl` | Resume the original continuation after a changed prefix. |

`PREFIX`, `BOUNDARY` and `SPLIT` count native input records, including the
initial `new_game` as record one.

These PowerShell examples use committed recordings. Search and improvement
commands create new files under the local `artifacts/` directory; choose fresh
output names for repeated runs.

```powershell
$route = 'build/cpp/vs/planner/Release/tsw_route.exe'
$baseline = 'tests/replays/first-cycle-seal.jsonl'

& $route verify $baseline
& $route verify tests/replays/first-cycle-seal-economy.jsonl
& $route verify tests/replays/first-cycle-seal-cashflow.jsonl
& $route inspect $baseline 2864
& $route ledger tests/replays/first-cycle-seal-cashflow.jsonl

& $route search $baseline 1505 artifacts/arena `
  --goal 11 --purchases 1 --width 4 --depth 8 --seconds 30

& $route improve $baseline 2864 artifacts/improved.jsonl --seconds 30
& $route verify artifacts/improved.jsonl

& $route economy $baseline artifacts/economy `
  --seconds 60 --rounds 4 --width 12
```

Search writes `OUTPUT_PREFIX-N.jsonl` for goals or
`OUTPUT_PREFIX-partial.jsonl` when it finds no goal. Economy writes numbered
candidates and retains the starting route at index zero. Existing output files
are never overwritten.

Exit codes are 0 for success, 1 for invalid input or an error, and 2 when bounded
search stops without reaching its goal. A partial replay does not satisfy the
requested goal.

## Route scripts

Scripts use zero-based coordinates. `#` starts a comment. Supply the script
file and input replay when using `run`; supply a changed input replay when using
`rebase`.

| Script command | Action |
|---|---|
| `go X Y` | Walk to a road square through the road graph. |
| `room X Y` | Seek a route through intervening events to the destination. |
| `land F [X Y]` | Choose a native Flight landing, optionally requiring coordinates. |
| `move up/down/left/right` | Make one native movement contact. |
| `buy -1/0/1/2` | Leave or select a shop option. |
| `item NAME` | Use `warp`, `magic`, `elixir`, `bomb`, `snow`, `ascent`, `descent`, `mattock` or `super`. |
| `sweep` | Collect locally reachable free events while retaining healing. |

The executor validates syntax and coordinates and reports the failing line.
It exports no route on failure. A successful `room` command can spend multiple
keys and collect intervening items; inspect its resource summary.

## Verification and search limits

The [committed replay fixtures](../tests/replays/first-cycle-seal.md) document
the reference recordings and expected results. `verify` checks all nine Octopus
rewards, Dragon without Dragon Slayer, Sacred Sword, post-Sword farming,
Great Master, both Wings at first 50F arrival, a post-gate Bomb seal, preserved
diagonal guards, zero HP altar purchases and positive hypothetical Zeno combat
margin. This is a contract for the seal challenge.

Search uses heuristic walking costs, event priorities and a bounded frontier.
The time, width, depth and purchase limits restrict what it can discover.
Pickup and economy improvement make local edits to an existing route and check
its continuation. The economy command does not generate arbitrary late-game
strategies or coupled purchase-timing and healing changes.

A passing verification establishes that a recording satisfies those checks in
the current engine. It does not establish optimality or agreement with every
behavior of the original executable.
