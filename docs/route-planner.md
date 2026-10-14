# Native route planner

`tsw_route` is an optional offline planning tool for the first cycle of Tower of
the Sorcerer. It searches early-floor event orders, executes explicit route
scripts, improves pickup timing and campaign key economy in an existing replay,
and verifies the 50F seal challenge. Every candidate uses the existing `tsw_core` and `tsw_replay`
libraries. The planner never assigns stats, edits maps, or substitutes its own
combat rules.

This is a bounded planning workbench, not a general autonomous tower solver or
an optimality proof. The complete seal solution used machine search **and**
human-directed strategy. The superseded experimental artifacts have been
removed. The final save and verification live in `artifacts/final-run/`;
regression recordings live in `tests/replays/`.

## Build and test

From the repository root, in an existing Windows build:

```powershell
cmake -S cpp -B build/cpp/vs -DTSW_PLANNER=ON
cmake --build build/cpp/vs --config Release --target tsw_route tsw_planner_tests
ctest --test-dir build/cpp/vs -C Release -L planner -LE audio --output-on-failure
```

For a headless build on another platform:

```sh
cmake -S cpp -B build/cpp/planner -DTSW_GUI=OFF -DTSW_PLANNER=ON
cmake --build build/cpp/planner --target tsw_route tsw_planner_tests
ctest --test-dir build/cpp/planner -L planner -LE audio --output-on-failure
```

This uses the project's existing dependency setup. CMake links targets directly;
there are no machine-specific include paths, library paths or compiler flags in
the planner. `TSW_PLANNER` defaults to `OFF`; ordinary game/MCP builds need not
include it. The Windows commands above were exercised; other platforms use the
same portable C++ code and CMake targets but have not been tested for this change.

The planner owns a separate `cpp/planner/` CMake component, with its own
`src/`, `include/`, and `tests/` directories. Its executable is emitted under
`build/cpp/vs/planner/Release/`; neither `tsw_game` nor `tsw_cli` links it.

After a successful C++ build, apply the repository's formatting instructions
and format the planner's C++ files with the same parent `.clang-format`.
These changes do not touch audio, so exclude audio tests from broader runs too.

## What the commands do

Run `tsw_route --help` for the full syntax. Examples below use PowerShell:

```powershell
$route = 'build/cpp/vs/planner/Release/tsw_route.exe'
$baseline = 'tests/replays/first-cycle-seal.jsonl'

# Check the complete challenge, including all nine Octopus rewards.
& $route verify $baseline

# Inspect the first arrival on 21F in the reference route.
& $route inspect $baseline 2864

# Explore event orders from a replay prefix. Bounds are explicit.
& $route search $baseline 53 artifacts/opening `
  --goal 11 --purchases 1 --width 128 --depth 120 --seconds 60

# A short positive smoke example from a prepared 10F arena checkpoint.
& $route search $baseline 1505 artifacts/arena `
  --goal 11 --purchases 1 --width 4 --depth 8 --seconds 30

# Find an earlier gem/equipment pickup and validate the full continuation.
& $route improve $baseline 2864 artifacts/improved-1.jsonl --seconds 30
& $route verify artifacts/improved-1.jsonl

# Explore economic alternatives against the entire seal continuation.
& $route economy artifacts/improved-3.jsonl artifacts/economy `
  --seconds 60 --rounds 4 --width 12
& $route ledger artifacts/economy-1.jsonl

# Execute a hand-authored continuation, or reconnect a changed prefix.
& $route run artifacts/prefix.jsonl artifacts/continuation.macros artifacts/continued.jsonl
& $route rebase $baseline artifacts/new-prefix.jsonl 2864 artifacts/rejoined.jsonl
```

All counts refer to native input records, with the initial `new_game` as record
one. They are not walking steps or event counts. Existing output files are never
overwritten. Search exports `PREFIX-N.jsonl` for goals or `PREFIX-partial.jsonl`
when no goal was found. Exit 0 means success, 1 means invalid input/an error, and
2 means the bounded search stopped without a goal. A partial replay is not a
solution. None of these commands changes the connected game session.

## How the early search works

The search currently targets first arrival at **11F or 21F**. A node contains a
native game state and a persistent chain of the inputs that reached it.

1. **Generate events.** Consider enemies, doors, pickups, shops, stairs and
   deliberate secret-wall contacts. If Flight is available, enumerate its
   reachable landings through actual selector inputs. Stat purchases branch
   into attack or defense choices, subject to the total purchase cap.
2. **Propose walking paths.** Road paths stop at the selected event. Room paths
   can cross intervening events and use heuristic costs for fights, keys and
   movement hazards. These costs choose a path; they do not decide whether it
   is legal or survivable.
3. **Execute the proposal in the native engine.** Run and settle every input,
   including scripts, forced encounters, key consumption and pickups. Reject
   death or an unexpected path interruption. There is no projected HP added to
   a candidate.
4. **Consolidate free pickups and fights.** The early search can collect free
   events to reduce equivalent visit permutations. The script runner preserves
   potions by default; on late floors a sweep also rejects any HP change.
   Octopus's mouth is never automatically swept while outer parts remain.
5. **Compare equivalent states.** A full serialized state key contains maps,
   monster rows, items and relevant progression fields. Hash-table collisions
   are resolved by comparing the full keys. On early floors, positions in the
   same road component can share a key; late positions remain distinct because
   walking itself may cost HP. Within a key, retain resource combinations not
   dominated in HP, ATK, DEF, gold, keys and purchase count.
6. **Keep a bounded frontier.** Rank by equipment, access progress, resources
   and survival. Distribute the beam across purchase histories and reached
   floors, with both progress and survival orderings. Discarded candidates do
   not get recorded as explored states that could suppress future branches.

The ranking includes tower-specific milestones such as the 10F arena and
11F/17F equipment. These are strategy hints, not game mechanics. A wider beam
does not guarantee a better result under the same time budget. Room-path
weights, automatic early collection, the candidate generator, ranking and
search limits all restrict what can be discovered. Failure to find a goal is
not evidence that the goal is impossible.

## How replay improvement works

`improve` examines stat pickups already present before the specified comparison
boundary. At earlier decision points on the same floor, it tries taking one of
those pickups first and returning to the original position. It then executes
the original continuation, skipping redundant door-opening contacts when a
detour has already opened that door.

A candidate is accepted only when:

- At the comparison boundary it has strictly more HP, the same board and
  monster rows, and the same other hero resources/progression (facing is ignored).
- Its entire remaining replay survives and reaches the same final progression
  state with at least the original final HP.
- Replaying the exported input history reproduces the candidate state.

This is a local search over earlier pickups, not an exhaustive search over all
routes or spending decisions. One invocation keeps the best single insertion.
Repeated passes can combine improvements. This deliberately distinguishes
better resource efficiency from simply buying more stats or collecting extra
potions before the comparison point. It can add walking inputs.

## Verified opening improvements

The baseline is the complete, manually guided winning seal replay in
`tests/replays/first-cycle-seal.jsonl`. Three pickup-order passes found:

| Milestone | Baseline HP | Improved HP | Other resources |
|---|---:|---:|---|
| First 11F arrival | 635 | **687 (+52)** | ATK 30 / DEF 34 / gold 286 / Y3 B1 R0 / 1 purchase |
| First 21F arrival | 1,723 | **1,799 (+76)** | ATK 80 / DEF 86 / gold 608 / Y6 B1 R0 / 6 purchases |
| Final sealed 50F | 361 | **361** | ATK 409 / DEF 348 / gold 1,164 / Y5 B0 R0 / 15 purchases |

The first insertion takes the 3F gem at `(1,8)` earlier, adding 51 HP by 21F.
The second takes the 15F gem at `(0,0)` earlier for another 24 HP. The third takes
the 1F gem at `(6,3)` earlier for another 1 HP. The improved route has 10,029
native inputs versus 9,937, a cost of 92 extra inputs. A fourth pass finds no
further gain in this neighborhood. Later percentage hazards round away the HP
gain, so the final Zeno survival margin remains 57 HP.

To reproduce all three insertions, using fresh output filenames:

```powershell
& $route improve $baseline 2864 artifacts/improved-1.jsonl --seconds 30
& $route improve artifacts/improved-1.jsonl 2904 artifacts/improved-2.jsonl --seconds 30
& $route improve artifacts/improved-2.jsonl 2924 artifacts/improved-3.jsonl --seconds 30
& $route verify artifacts/improved-3.jsonl
```

Those shifted boundary counts reflect the added walking inputs. This is a
measured improvement to the early route, not a claim of a globally optimal
opening or a larger final combat margin.

## How campaign economy improvement works

An arrival at 11F or 21F is a useful checkpoint, but it cannot determine the
future value of a key. A blue key can avoid a later purchase, open a healing
room, or be unnecessary because another entrance is already accessible. A
five-key bundle also has a different marginal cost from five independent keys.
The original `search` command still uses heuristic checkpoint weights; its
output should not be described as the best campaign economy.

`economy` instead starts from a complete, verified seal route and explores:

1. **Omitted key trades**, including merchants visited after 21F.
2. **Door bypasses and omitted side trips**, reconnecting to a later point on
   the same floor through actual roads. The local window is at most 240 inputs.
3. **Earlier key acquisition**, trying remaining keys at floor arrivals, stat
   changes and door decisions, collecting other road-accessible keys in the
   room, then returning to the original position.

These changes can combine over successive rounds. The continuation tries to
preserve doors that the new route leaves closed, finding another native path
to the next original road square or event. A required fight or pickup is
executed through the engine. Shops, stairs and item uses remain explicit
boundaries. This is more flexible than requiring the same walking trace.

Skipping a one-time merchant also changes subsequent contacts: the merchant
offers the trade again instead of supplying a hint. The continuation explicitly
declines such incidental offers. Without that handling, a shop waiting for
input was incorrectly reported as a walking failure.

Every retained alternative passes the **complete challenge verifier**, including
Dragon, Sword, post-Sword farming, Master, Octopus rewards, Wings, seal formation
and hypothetical Zeno survival. The search records independent HP, stats, gold
and key axes at 11F, 21F and the finish. It compares resource dominance only
when the native board and progression identities at all three checkpoints
match. Equal key counts with different unopened rooms are not equivalent.

The bounded frontier keeps representatives for gold, survival and different
key reserves, and always retains the starting route as candidate zero. There
is no fixed gold bonus per key in this pass. Output indices are alternatives,
not an ordering from globally best to worst. `ledger` reports milestone
resources, blue/red door openings, merchant transactions and final margin.

This remains a local, bounded search. It does not invent an arbitrary new
late-game strategy or change altar allocations. It can miss a combination
whose intermediate route fails before a second necessary edit is made. It
uses one weighted room-path proposal per target, so rejecting a proposal does
not prove that all paths fail. Time limits affect which candidates are explored.

### Verified combined result

The economic pass found that a 12F side trip spent two yellow keys to collect
34 gold from two optional fights. Omitting it, and routing later visits around
retained doors, allows the 38F three-yellow-key trade to be declined. The trade
costs 200 gold, so the net improvement is **166 gold**. This is a measured
purchase saving, not an assumed price assigned to a spare key.

Combining that result with further pickup timing improvements gives the
recording in `tests/replays/first-cycle-seal-economy.jsonl`:

| Milestone | Original winning route | Previous pickup improvement | Combined economic route |
|---|---|---|---|
| 11F HP | 635 | 687 | **736 (+101 from original)** |
| 11F gold / keys Y,B,R | 286 / 3,1,0 | 286 / 3,1,0 | **291 / 4,1,0** |
| 21F HP | 1,723 | 1,799 | **1,880 (+157 from original)** |
| 21F gold / keys Y,B,R | 608 / 6,1,0 | 608 / 6,1,0 | **613 / 7,1,0** |
| Final gold | 1,164 | 1,164 | **1,330 (+166)** |
| Key merchant spending | 1,500 | 1,500 | **1,300 (−200)** |
| Final HP / ATK / DEF | 361 / 409 / 348 | same | same |
| Hypothetical Zeno margin | 57 HP | 57 HP | 57 HP |

Attack and defense remain 30/34 at 11F and 80/86 at 21F; the route still makes
15 stat altar purchases and zero HP altar purchases. Its 10,307 inputs cost
370 more than the original and 278 more than the earlier improved route,
mostly extra walking. Later percentage hazards erase the additional early HP,
but the early survival improvement and the saved gold are both real.

The earlier +76 HP was a useful improvement. It became the starting point for
this further **+81 HP at 21F**, rather than being discarded. Alternating the
economic neighborhood with pickup timing search exposed improvements that
neither pass found alone. The complete strategy remains analysis-led and
search-assisted; the new economic and pickup changes were found automatically
within these documented neighborhoods.

```powershell
& $route verify tests/replays/first-cycle-seal-economy.jsonl
& $route ledger tests/replays/first-cycle-seal-economy.jsonl
```

A subsequent manually scripted cash-out confirmed that all five final yellow
keys can be sold before Master. Buying the still-unused 38F three-key bundle
for 200 and reselling it for 300 adds another 100 profit. The verified branch
finishes with 1,930 gold and no keys, with the same HP, stats and seal. This
terminal sale policy is not yet generated by `economy`; the maintained fixture
above preserves the automatically improved route before that cash-out.
Before Master the cash-out branch has 830 gold, so it is still 1,590 short of
the next 2,420-gold altar purchase. The later Master and Bomb rewards explain
the larger final balance. This illustrates why minimizing merchant spending
alone is not an economic objective.

A subsequent cash-flow experiment is retained as
`tests/replays/first-cycle-seal-cashflow.jsonl`. Selling one key on the first
28F visit and two after the 2F gold gift provides 300 gold before the 38F bundle
replaces the three keys for 200. That funds the existing 920-gold defense
purchase earlier, while still leaving one gold after the required 31F trade.
At the original defense-purchase checkpoint it saves 176 HP. A separate
retiming of the 1840-gold attack purchase saves another 10 HP at its checkpoint.
Deferring the 41F (0,0) potion until after the late halvings then increases final
HP from361 to611 and the sealed-Zeno survival margin from57 to307, with the same
1930 gold. The same potion deferral on the previous terminal-cash-out route
fails; the improvements have to be evaluated together.

The sale schedule was proposed manually. Offline experiments generated earlier
purchase visits and potion-deferral detours using `run`/`rebase`, rejecting
unfunded trades, blocked paths, deaths and failed full-challenge continuations.
Those experiments are not yet part of `economy`. They search local edits to a
known route, not arbitrary new strategies. A fixed-route stat-allocation check
also found no better surviving allocation; that does not establish global
optimality. The new fixture and its cash-flow regression preserve the tested
result without overstating what the maintained optimizer can discover.

## Explicit route scripts

Scripts use zero-based coordinates. `#` begins a comment.

| Command | Meaning |
|---|---|
| `go X Y` | Walk to a road square using the road graph. |
| `room X Y` | Propose access through intervening fights/doors/pickups to an event. |
| `land F [X Y]` | Choose a native Flight landing, optionally requiring coordinates. |
| `move up/down/left/right` | One deliberate native contact. |
| `buy -1/0/1/2` | Leave or select a native shop option. |
| `item NAME` | Use `warp`, `magic`, `elixir`, `bomb`, `snow`, `ascent`, `descent`, `mattock`, or `super`. |
| `sweep` | Collect locally reachable free events while retaining healing. |

The executor validates syntax and coordinates and reports the failing line.
It exports nothing on failure. A successful `room` command can consume multiple
keys and collect intervening potions; inspect its resource summary. A script
is an explicit strategy, not a search result or proof of optimality. In
particular, the author must preserve puzzle formations and budget return paths.

## What actually solved the seal challenge

The original result was **not found by an unattended end-to-end search**.

- The user identified the missing Octopus rewards and emphasized that Dragon
  and Great Master must be separate milestones.
- Search explored stat allocations, equipment/access routes and local
  continuations. Native replay tools made those experiments fast and repeatable.
- Assistant analysis assembled the final strategy: defeat Dragon, take Sacred
  Sword, farm and prepare the 49F formation, defer healing until after pincers,
  then defeat Master. Keep one cardinal guard until after the 50F gate, Bomb it
  from an adjacent safe square, and ascend with enough HP for hypothetical combat.
- The engine and independent verifier established that this composed strategy
  works. The new pickup optimizer independently found the early improvements
  above within its explicitly defined search neighborhood.

Calling the original experiment a complete autonomous solver would overstate
its capability. This package makes the useful machinery reviewable and its
limits explicit. The late prototype files were removed during consolidation; the verified
result and maintained regression tests remain.

## Code and regression coverage

| File | Responsibility |
|---|---|
| `cpp/planner/include/tsw/planner.hpp` | Public routes, search bounds and tool API |
| `cpp/planner/src/planner_internal.hpp` | Internal nodes, policies and path structures |
| `cpp/planner/src/planner_engine.cpp` | Native navigation, event generation, state equivalence and ranking |
| `cpp/planner/src/planner_search.cpp` | Bounded beam traversal and diversity |
| `cpp/planner/src/planner_routes.cpp` | Replay validation, scripts, rebasing and pickup-order improvement |
| `cpp/planner/src/planner_economy.cpp` | Full-continuation economic search and transaction/milestone reporting |
| `cpp/planner/src/planner_verify.cpp` | Independent assertions for this campaign's full challenge contract |
| `cpp/planner/src/route_cli.cpp` | CLI parsing, errors and output handling |
| `cpp/planner/tests/planner_tests.cpp` | Native fixture and planning regressions |

The verifier is intentionally a regression contract for this challenge: it
also checks all nine Octopus rewards at zero damage, zero HP altar purchases,
Dragon without Dragon Slayer, post-Sword farming, both Wings at first 50F
arrival, a post-gate Bomb seal, preserved diagonals, and positive combat margin.
It is stricter than a generic “can this route finish the game?” predicate.
