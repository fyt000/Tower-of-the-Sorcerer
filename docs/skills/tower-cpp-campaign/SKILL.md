---
name: tower-cpp-campaign
description: "Play and investigate Tower of the Sorcerer through the connected tower_cpp MCP. Use compact observations, destination navigation, combat breakpoints, key and item budgeting, persistent saves and session recovery; reassess strategy from current state without treating past routes as optimal."
---

# Tower C++ Campaign

Use the connected `tower_cpp` service for ordinary play. Let the server handle walking while choosing fights, doors, purchases and item uses deliberately. Plan toward an equipment, access or progression milestone, then revise the plan from observed results.

## Evidence and scope

Treat a completed campaign as evidence that its route worked, without assuming optimal purchases, item timing or equipment order. Write reusable recommendations and mechanics separately from any particular campaign's history.

Read [early-area considerations](references/first-ten-floors.md) when planning the opening climb and floor-10 arena. It provides decision criteria, not a prescribed route.

Reassess all numeric thresholds, access routes and item effects against the active build, live cycle, equipment and current forecasts. Source knowledge, live observations, tested branches and proposed strategies are different kinds of evidence. Do not describe a source-derived or merely completed route as optimal.

## Connected MCP workflow

At the start, read `mcp_runtime` when available and compact `game_state`. Verify the active deployment, normal/developer mode, continuation status and actual journey before acting. Separate server processes can hold different games even when they use the same repository or executable. Use one connection as the authoritative session.

Select an event from `floor.points`; resolve its ID through `tile_types`. Use `navigate(x,y,floor)` for walking and endpoint contact. Use `game_action` for listed shop choices, item uses and deliberate contacts with concealed walls. Read returned stats, tile changes, messages, pending interaction and navigation reason before continuing. Reuse summaries; refresh compact state when access, forecasts or scripts need reassessment. Reserve full observations for a specific diagnostic need.

`reachable` is geometric access, and `available` describes the selected interaction. Neither budgets the whole journey. Combat forecasts and `plan_path` exclude movement magic, pincers and scripted effects. Plan those costs separately, including the return route.

For connection checks, interruption semantics, saves, replay and update recovery, read [MCP workflow](references/mcp-workflow.md). Prefer connected tool calls over an extra shell/HTTP controller for gameplay. A helper can organize observations or test a justified branch, but its assumptions and errors are separate from the native game.

## Strategy principles

- **Choose the milestone before the fights.** Name what a fight opens or funds. Revisit earlier floors after equipment or stat gains; optional fights that are affordable now can be much cheaper later. Avoid clearing an area just because it is reachable.
- **Acquire Lucky Gold, then sweep while fights are cheap.** Try obtaining Lucky Gold before bulk optional farming when its access cost is reasonable. Once acquired, promptly revisit accessible floors for gems and doubled ordinary-combat gold when fights cost zero or almost no HP. Repeat useful sweeps after equipment or stat gains make more rooms cheap; do not postpone them until the ending. Include doors, movement hazards, scripts and the return route in each room's cost, and preserve enemies needed for puzzles. Before Lucky Gold, defer optional enemies unless their access or gold enables a more valuable milestone. Bomb rewards use base gold even with Lucky Gold.
- **Treat HP as a route budget.** Include required fights, movement hazards, scripts and the way back. Survival needs HP strictly above lethal damage. Distinguish total supplies from supplies accessible before the blocker. Delay optional potions until after known HP-halving effects when the lower-HP passage remains survivable; automatic pickup collection can make this worse.
- **Compare red and blue gems at current breakpoints.** Attack is especially valuable when it penetrates defense or removes an enemy strike. Defense can win when many strikes remain or several necessary enemies become harmless. Compare total damage saved across the next required encounters, subtract each gem room's access cost, then recompute after every upgrade. There is no fixed color priority.
- **Budget keys by color and access.** Reserve keys for the intended milestone, including the merchant's door, exit and item access. Price rooms sequentially using keys spent and recovered, fights, supplies and later access. Try to avoid buying a single yellow key for 1,000 gold: check cheaper merchant stock, rooms that return more keys than they consume, alternative approaches and Mattock bypasses first. Compare the purchase with the stat upgrade that gold could fund, and consider an authorized rewind when the shortage comes from earlier key spending.
- **Buy a concrete improvement.** Merchant HP is generally poor value; altar HP also advances the shared purchase count and raises later stat prices. Consider HP spending only after checking lower-damage routes, deferred supplies, upgrades and revisits, and identify the specific survival blocker it resolves. A bailout for an inefficient route does not establish a good purchase.
- **Collect gold early; time stat purchases by need.** Sweep cheap doubled gold promptly after Lucky Gold, then hold it until an upgrade reaches a useful combat breakpoint or enables progression. Favor higher-area altars when waiting is affordable: the shared purchase count sets the price, so an early purchase can consume a cheap upgrade for a smaller gain. Reassess after free gems and equipment, reserve funds for planned access items, and buy early only when the immediate benefit justifies doing so. Before a cycle transition, try converting the remaining usable budget into carrying stats; avoid purchases merely to empty the balance.
- **Try leaving the 3% boost until late.** Reserve the floor-2 old man's one-time attack/defense boost until after the planned gem sweeps, equipment and affordable altar upgrades. Each gain is truncated to an integer, so early use can discard much of its potential. Revisit him before the final difficult fight or ending. Take it earlier only when the immediate gain resolves a concrete access or survival breakpoint worth that tradeoff.
- **Acquire and use items as separate decisions.** Reserve consumables for a named blocker. Compare their immediate return with other uses, including key savings, avoided fights and lost future supplies. Super Mattock needs a planned floor and worthwhile return, plus its price and merchant access; availability alone is not a reason to buy it early.
- **Compare shield strategies, then prioritize the chosen objective.** Compare bombing with fighting the guards after any needed upgrades; weigh HP and hazard costs, shield timing, gold rewards and the Bomb's value elsewhere. Once the Sacred Shield is the chosen objective, keep preparation focused on obtaining it. Safe sweeps on earlier floors after Lucky Gold can fund that preparation; defer rooms whose movement hazards or combat remain expensive until protected. Budget the required keys, access item, guards and movement hazards together, and reassess the chosen acquisition method and timing.
- **Check traps and formation puzzles before committing.** Budget all forced encounters, and inspect clues or the relevant predicate before killing every guard. An enemy's individual forecast cannot establish that a trapped sequence is survivable or that clearing all enemies preserves a puzzle solution.

When a route repeatedly needs rescue spending or cannot fund its next access, compare a rewind/restart with continuing. Use the user's authorization and scope; do not hide restarts or replace the live journey with an unreviewed candidate.

## Mechanics worth checking

Read [campaign considerations](references/campaign-considerations.md) when planning Lucky Gold sweeps, the delayed 3% boost, consumables, later first-cycle objectives, gem/altar comparisons or cycle transitions. It records mechanics and recommendations to try, not a prescribed route.

When the repository is available, read only the implementation needed to settle a rule. In `D:/projects/tos-rust`:

| Question | Source |
|---|---|
| Combat, penetration, forced fights and item multipliers | `cpp/src/combat.cpp` |
| Pickups, doors, stairs and movement hazards | `cpp/src/contact.cpp` |
| Merchant offers, stock, altar purchases and clues | `cpp/src/npcs.cpp` |
| Flight, Mattocks, Bomb, Wings, Warp and Snow Crystal | `cpp/src/items.cpp` |
| Traps, arrivals, formations, gates and endings | `cpp/src/scenes.cpp`, `cpp/src/floor_checks.cpp` |
| Capture, cycles and carry/reset rules | `cpp/src/game.cpp` |
| Maps, landings and base enemy rows | `cpp/src/original_constants.hpp` |
| Tool observations, saves and session updates | `docs/cpp-mcp.md`, `cpp/src/mcp_observation.cpp`, `cpp/tools/mcp_server.py` |

Normal play conceals secrets and gates forecasts/saves behind the Hero Orb. Developer simulation is a separate capability; identify its use when reporting an investigation or run.

## Reporting and continuation

Keep a compact milestone note: active session/build and cycle, HP/attack/defense/gold, keys by color, equipment/protection, reserved items, next objective, remaining access costs, unresolved rules and absolute save/replay paths. Preserve the save's replay companion for continuation.

Report completion from native outcomes and retained evidence. Visiting floor 50, reaching its ending and advancing a cycle are distinct claims. Stop at the user's requested campaign boundary; first-cycle completion does not authorize playing later cycles.

Before the irreversible ending, check for remaining worthwhile gems, cheap gold, affordable stat purchases and the unused 3% boost. This is a final verification of sweeps begun earlier, not a reason to delay them. Account for access costs and deliberate omissions rather than claiming all resources were collected without checking.

Treat documented game quirks as intended mechanics unless new evidence establishes a defect. Distinguish a helper failure from a server failure. Base any suspected issue on current behavior, source and a minimal reproduction; a difference from the agent's expectation is insufficient.
