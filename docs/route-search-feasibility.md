# Route search and provable optimization

The shipped Rust game can be searched as a deterministic planning problem. It already has the most difficult architectural prerequisite: one headless transition function with a complete, cloneable state. Finding a useful route is a realistic next project. Proving a globally optimal route through all 50 stories is possible in principle, but its practical running time is not established by this review. No full solver or natural full-tower solution was executed for this assessment.

There are two separate tasks: an internal oracle can optimize against the complete authored world; a playing agent must discover that world through the same observations and experiments available to a player. An oracle's solution does not prove that an agent can infer a hidden passage from dialogue. The private search API should therefore stay separate from player-facing MCP tools.

## Define the result before searching

“Optimal” requires a goal and an objective. Different reasonable definitions give different routes:

| Goal/objective | Meaning and consequence |
| --- | --- |
| Reach the first ending alive | A reachability problem; any reproducible successful route is sufficient. |
| Reach the first ending with the fewest commands | A shortest-path problem with each gameplay command assigned cost 1. This is a useful first exact prototype. |
| Reach the first ending with the fewest moves | Shops and item use need explicit costs, possibly 0; use a search that supports zero-cost edges. The existing `steps` field is not a general count of all commands. |
| Maximize ending HP | Delaying stat-dependent rewards and elixir use becomes part of the objective. Exploring an optional room may be worthwhile. |
| Maximize ending attack, defense, HP and gold | These conflict. Use a specified ordering/weighted score, or return a Pareto frontier rather than asserting one best route. |
| Complete a specified number of backside cycles | Include that cycle horizon explicitly. Replay regenerates the tower and carries strength forward. |

In the default campaign, `status == "won"` is **not** the first-ending goal. [`Engine::next_cycle`](../crates/tos-core/src/lib.rs) resets the world and increments `cycle` because `rules.backside.enabled` is true. A first-cycle search should detect the transition from cycle 1 to cycle 2 and record the stats immediately before reset if the objective uses ending gold or inventory. Entering floor 50 alone also does not complete the adventure. The current 1,000-cycle safety cap is an implementation guard; it is not a useful definition of game completion.

The original fairy score/rank tables have not been implemented, as documented in [original-data.md](original-data.md) and [mechanics.md](mechanics.md). A solver cannot claim to optimize the original game's rank until that scoring function is recovered and encoded.

## The existing state is sufficient

[`Engine`](../crates/tos-core/src/lib.rs) owns the campaign, compiled scripts, save and last action. `Engine::execute(Command)` is the common transition function for GUI, CLI and MCP. There is no game-time, graphics or random-number dependency in the core. Presentation waits emit messages; they do not postpone simulation effects. [`Command`](../crates/tos-core/src/command.rs) supplies four moves, interaction choices, item use, cancel and new game. [`save_json` / `load_json`](../crates/tos-core/src/persistence.rs) already support branching and replay, while `Engine: Clone` can produce a branch directly.

For a search from a legitimate initial state, keep the following future-relevant variables:

| Variable | Why it affects a continuation |
| --- | --- |
| Player floor, x, y | Available moves, magic fields, item targets and stair landings. |
| HP, attack, defense, gold and three key counts | Survival, combat damage, prices and doors. |
| Inventory and item charges | Passive combat bonuses, hazard immunity, consumables and the Warp Staff's remaining uses. |
| Every floor's current tile array | Cleared enemies/doors, pickups, concealed passages, moved entities and spawned gates/rewards. |
| Visited floors | The Orb of Flying can reach only visited floors. |
| Flags | Script and offer conditions, staged interactions. |
| Fired events | Once-only events must not run again. The current engine consults counter-key presence for this purpose. |
| Shop visits and once-offer markers | All altars share one purchase counter; it changes prices and HP gains. Individual one-use gifts/trades also have markers. |
| Pending interaction and its tile location | Movement is blocked during a conversation, and choices apply to that location. |
| Enemy overrides | Location events change boss rows before combat; base enemy definitions alone are insufficient. |
| Cycle and status | Stat scaling, reset behavior and terminal states. |

The save schema records these fields. A displayed snapshot alone is not the solver state: it omits counters and enemy overrides, and normally describes only the current floor's tiles. The solver must use a private complete-state representation.

Log strings, animation payloads and `last_action` do not control future gameplay. They can be excluded from search identity. Keep accumulated objective cost as a label on the node. Excluding `steps` is valid for the current transition rules, which do not test it; preserve its value separately if it is a reported objective. Normalize inventory as a set only after confirming that the intended objective does not depend on display order. Fired-event counters can become bits under the current presence-only rule, but shop counts cannot all be discarded. This is a semantic projection, not simply a hash of `snapshot()` or the complete save JSON.

The authored campaign fingerprint and a solver/rules version should accompany every result. A hash used to deduplicate nodes must compare full canonical state on collisions. The save fingerprint identifies a campaign revision but is not itself a mathematical proof that no hash collision can occur.

## Size of the shipped problem

These counts come from `data/campaign.json` in this checkout, counted by tile kind and recursively inspected script records:

| Component | Count |
| --- | ---: |
| Floors and geometry | 51 × 11 × 11 = 6,171 cells |
| Defined tiles / enemy rows | 166 / 33 |
| Initial enemy cells | 487 |
| Initial ordinary doors / special gates | 290 / 24 |
| Initial keys | 192: 169 yellow, 20 blue, 3 red |
| Initial potions / gems / equipment / loose items | 118 / 61 / 10 / 6 |
| Initial hidden-wall cells | 51 |
| Initial ordinary walls / lava | 2,176 / 98 |
| Initial staircase cells | 92 |
| Events | 100, all once-only |
| Location-specific interaction overrides | 41 |
| Authored offers | 15, plus three generated altar choices |
| Script tile writes / tile movements / forced battles | 238 / 135 / 13 |

There are 1,215 initial cells containing an enemy, ordinary door, pickup or concealed passage. Treating each as an independent untouched/removed bit would produce `2^1215 ≈ 10^366` combinations before considering resources, position, scripted state or wall tools. This is an illustrative **overcount of possible combinations**, not a lower bound on reachable states: geometry, resources, monster footprints and events rule out many combinations. It nevertheless explains why enumerating every pickup subset is not a practical baseline.

Some facts make the fixed campaign substantially easier than its loose input limits suggest. All 100 events are once-only, the campaign has no custom item scripts, and the only authored stat comparison is the repeatable yellow-key sale's `yellow >= 1`. There are no `stat_at_most` conditions in the shipped data. Many long cutscenes create only one deterministic successor, rather than hundreds of search choices.

Even the repeatable economy has a small useful bound for a first-cycle search. Summing gold across every initial enemy cell gives 17,832; enemy-producing `set_tile` records add a deliberately generous 2,734. Count all of these at double reward, add the one-use 1,000-gold gift, and suppose every initially available yellow key, scripted yellow key and one-use bundle is sold for 100 gold:

```text
2 × (17,832 + 2,734) + 1,000 + 100 × (169 + 13 + 12) = 61,532
```

This overcounts enemies belonging to shared footprints, mutually incompatible events, consumed door keys and key bundles that cost gold. It is a conservative positive-resource budget, not the gold of an actual route. The repeatable merchant buys a key for 1,000 gold and the sale returns 100, so that loop cannot increase this budget. Enemy overrides keep their gold reward at 500. Bomb rewards do not exceed the double-reward allowance.

The total cost of `n` altar purchases is `10 × (n(n−1)(n+1)/3 + 2n)`. Even spending the entire loose bound at altars permits at most 26 purchases: 26 cost 59,020, whereas 27 cost 66,060. This gives a much more useful search limit than the billion-point stat envelope. It does **not** establish which purchases or areas are optimal, and the bound must be regenerated if campaign content changes or the search crosses into another cycle.

Storing all 6,171 cells as `u16` already uses 12,342 bytes per node; a million copies require over 12 GB for map payload alone. The current derived `Engine::clone` also clones campaign and compiled scripts. Large search should share those immutable structures and use interned maps, persistent pages or compact deltas; a small correctness prototype can start with engine clones.

## Exact search and useful pruning

For the fixed shipped campaign and a bounded cycle goal, reachable gameplay state is finite: map cells and authored IDs are finite, numeric fields use bounded integer types/saturation, and scripted transitions terminate because event re-entry is stopped by once markers. Therefore exhaustive search decides reachability and can establish an optimum for a defined objective. This is a theoretical guarantee, not a promise of tractable execution. Custom campaigns allow repeatable events and recursive forced battles, so a general-purpose solver also needs to establish transition termination or enforce a clearly reported model restriction.

Use the engine as the transition oracle. The ordinary battle formula is simple:

```text
hit = attack × applicable item multiplier − enemy defense
retaliations = floor((enemy HP − 1) / hit)       [hero strikes first]
damage = retaliations × max(enemy attack − defense, 0)
survival requires damage < player HP
```

But [`combat.rs`](../crates/tos-core/src/combat.rs) also applies the base-attack guard and configurable first-strike rule. [`events.rs`](../crates/tos-core/src/events.rs) applies boss overrides and forced ambush strikes. [`navigation.rs`](../crates/tos-core/src/navigation.rs) applies adjacent magician damage and sorcerer pincer damage after accepted walking. Reimplementing only the formula would miss important routes and deaths.

The following pruning is suitable for an exact prototype:

- Deduplicate identical canonical future-state projections, retaining the lowest accumulated command cost. For terminal-resource optimization, retain the appropriate objective labels as well.
- Drop dead states, terminal states outside the requested goal, and transitions that change neither semantic state nor relevant cost. A blocked move can still fire a bump event before it is blocked, so decide this from the resulting state, not from `last_action.ok` alone.
- Use uniform-cost search for nonnegative edge costs. A* with heuristic zero has the same proof properties; a stronger heuristic must be a proven lower bound. Manhattan distance is not globally admissible when stairs, warps or event teleports can shorten a route.
- Prune a branch whose accumulated minimum-command cost already exceeds a known successful route. More ambitious resource/death bounds need their own optimistic relaxations; a currently fatal enemy may become safe after a stat pickup or purchase.
- Represent all choices of a pending conversation, including `leave` and `cancel`. In this engine `leave` may apply NPC effects and trigger events, while `cancel` dismisses without applying them. They are distinct transitions.

Resource dominance is promising, but it must be justified. For the fixed campaign and a monotone terminal objective, compare two states with **the same** position, maps, flags, fired events, shop/offer markers, inventory, charges, visited floors, boss overrides, pending interaction and cycle. If one has at least as much HP/attack/defense/gold/each key and no greater route cost, it is a candidate to dominate the other. Combat damage and the remaining HP after the pincer operation are monotone; the fixed stat-reset capture and positive percentage gift also preserve this ordering. The only stat-gated offer needs one yellow key. A campaign-specific monotonicity argument can make this a safe Pareto pruning rule. Keep it disabled until that argument and focused counterexample tests accompany implementation.

The same rule is unsafe for arbitrary campaigns: `StatAtMost` can reward a weaker player or gate an essential transition. Comparing different worlds is also unsafe even for the original. A defeated enemy can grant gold or unlock an event; consuming a gem changes both stats and future pickup opportunities; a previously opened door changes reachability; a greater altar counter increases later prices. “Higher attack on the same floor” and “more cleared tiles” are not sufficient dominance criteria.

Collapsing movement into reachable regions is valuable only in proven inert areas. `path_to` accepts `Trigger` tiles as intermediate road and does not model their event effects or movement hazards. It is a click-route helper, not an optimizer. A correct compressed solver should find side-effect-free, hazard-free roads, preserve exact walking distance if distance is the objective, and stop macro actions at every encounter, stair, hazard or scripted site. Replay every macro through individual engine commands and stop if a script relocates the player, opens a conversation or changes cycle/status. Do not assume that any walk over road is free or reversible.

Ten-floor area decomposition is a heuristic, not automatically an exact dynamic program. Backtracking, globally priced altars, tools, hidden routes and carried resources couple areas. Exact decomposition would require retaining every relevant boundary state and its Pareto labels, not one locally best route per area.

## Preserve discovery while evaluating agents

A full-state optimizer knows which apparent wall is traversable because it reads authored tile kinds and events. A discovery agent receives an observation history: visible maps, conversations, legal actions, failed bumps and discovered changes. A single shortest path through the real map is therefore an omniscient result.

If a puzzle-preserving optimum is required, define a set of possible worlds and an observation function. A policy maps observation history/belief state to an action. After a failed bump, successful passage or dialogue, remove worlds inconsistent with that observation. Then optimize a worst-case objective over the remaining possibilities, or expected cost under an explicit prior. Without a specified world set/prior, there is no unique mathematical answer to “the best way to discover a hidden wall.” Natural-language riddles also need either human/agent interpretation or an explicitly formal clue semantics.

The straightforward product boundary is:

- Player MCP exposes observations, dialogue and action consequences, with secrets remaining concealed until discovered.
- A private solver/debug API exposes complete checkpoints, branches and campaign structure for testing and offline research.
- An agent evaluation records a natural action trace from a fresh game and distinguishes no-spoiler discovery from source-assisted play. Private save editing and the oracle are excluded from the discovery run.

This allows an exact solver to check solvability, detect regressions and measure an agent's resource waste without revealing the puzzle solution to that agent. Source-based proofs and discovery performance should be reported separately.

## Recommended prototype and proof output

Build a small internal `tos-solver` crate or feature, initially solving tiny fixtures and a bounded opening/prison objective. Keep the current engine as the only transition implementation. The minimum useful interface is approximately:

```rust
// Private/offline interfaces; not spoiler-bearing player MCP tools.
fn checkpoint(&self) -> SearchState;
fn state_key(&self) -> CanonicalKey;
fn candidate_commands(&self) -> Vec<Command>;
fn transition(&self, command: &Command) -> Transition;
fn search(start: SearchState, spec: GoalAndObjective, limits: SearchLimits)
    -> SearchResult;
```

`candidate_commands` must be finite and complete for the selected model: four moves, available interaction IDs plus `leave`/`cancel`, owned item IDs, and every valid flying destination (visited floors). Include attempts against apparently ordinary walls in a discovery model. New game and arbitrary save loading are environment controls, not playthrough actions. `Transition` should include cycle-completion facts before the automatic reset when the objective needs them.

Return the campaign identity, model restrictions, goal/objective, an action trace, final/checkpoint states, expanded/generated/pruned counts, time/memory limits and a clear result classification:

- **Solved, unproven:** a natural replay succeeds, but unexplored branches can improve it.
- **Optimal under the stated model:** a solution is replayed and the frontier's lower bound rules out every better solution, or the necessary finite search is exhausted.
- **Unsatisfiable under the stated model:** exhaustive search establishes no goal state.
- **Incomplete:** a budget was reached; report the incumbent and bound without claiming optimality or unsatisfiability.

A successful replay validates a route, not its optimality. Independently checking a shortest-path proof requires the search bounds/exhaustion argument and any abstraction/dominance assumptions. Since [`original_campaign.rs`](../crates/tos-core/tests/original_campaign.rs) explicitly uses scenario saves for much late-game coverage, those tests do not supply a natural end-to-end route or an optimality certificate today.

After the small prototype matches brute-force fixture results, measure transition throughput, canonical-state count, memory and Pareto-front growth at progressively larger milestones. Those measurements determine whether full-tower exact search is practical, whether better certified reductions are needed, or whether a heuristic route finder is the useful first deliverable. The current code makes the experiment possible without changing the game's puzzle mechanics.
