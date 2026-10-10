---
name: tower-cpp-campaign
description: "Play and investigate Tower of the Sorcerer through the connected tower_cpp MCP. Use compact observations, destination navigation, combat breakpoints, key and item budgeting, persistent saves and session recovery; reassess strategy from current state without treating past routes as optimal."
---

# Tower C++ Campaign

Use the connected `tower_cpp` service for ordinary play. Let the server handle walking while choosing fights, doors, purchases and item uses deliberately. Plan toward an equipment, access or progression milestone, then revise the plan from observed results.

## Evidence and scope

A first-cycle campaign reached the floor-50 ending through normal inputs, restarts and replay reconstruction. Completion shows that the selected history worked; it establishes neither an optimal route nor ideal purchases, item timing or equipment order. Earlier failed branches and bailout HP purchases are lessons about planning, not recommendations to repeat.

Read [early-area considerations](references/first-ten-floors.md) when planning the opening climb and floor-10 arena. It provides decision criteria, not a prescribed route.

Reassess all numeric thresholds, access routes and item effects against the active build, live cycle, equipment and current forecasts. Source knowledge, live observations, tested branches and proposed strategies are different kinds of evidence. Do not describe a source-derived or merely completed route as optimal.

## Connected MCP workflow

At the start, read `mcp_runtime` when available and compact `game_state`. Verify the active deployment, normal/developer mode, continuation status and actual journey before acting. Separate server processes can hold different games even when they use the same repository or executable. Use one connection as the authoritative session.

Select an event from `floor.points`; resolve its ID through `tile_types`. Use `navigate(x,y,floor)` for walking and endpoint contact. Use `game_action` for listed shop choices, item uses and deliberate contacts with concealed walls. Read returned stats, tile changes, messages, pending interaction and navigation reason before continuing. Reuse summaries; refresh compact state when access, forecasts or scripts need reassessment. Reserve full observations for a specific diagnostic need.

`reachable` is geometric access, and `available` describes the selected interaction. Neither budgets the whole journey. Combat forecasts and `plan_path` exclude movement magic, pincers and scripted effects. Plan those costs separately, including the return route.

For connection checks, interruption semantics, saves, replay and update recovery, read [MCP workflow](references/mcp-workflow.md). Prefer connected tool calls over an extra shell/HTTP controller for gameplay. A helper can organize observations or test a justified branch, but its assumptions and errors are separate from the native game.

## Strategy principles

- **Choose the milestone before the fights.** Name what a fight opens or funds. Revisit earlier floors after equipment or stat gains; optional fights that are affordable now can be much cheaper later. Avoid clearing an area just because it is reachable.
- **Account for Lucky Gold.** Leaving optional enemies alive can increase later ordinary-combat rewards, including enemies that already cost zero HP. Fight them earlier when their access or gold is needed to reach a more valuable milestone. Bomb rewards use base gold, even with Lucky Gold; include the forgone bonus in the route's economy.
- **Treat HP as a route budget.** Include required fights, movement hazards, scripts and the way back. Survival needs HP strictly above lethal damage. Distinguish total supplies from supplies accessible before the blocker. Delay optional potions until after known HP-halving effects when the lower-HP passage remains survivable; automatic pickup collection can make this worse.
- **Compare red and blue gems at current breakpoints.** Attack is especially valuable when it penetrates defense or removes an enemy strike. Defense can win when many strikes remain or several necessary enemies become harmless. Compare total damage saved across the next required encounters, subtract each gem room's access cost, then recompute after every upgrade. There is no fixed color priority.
- **Budget keys by color and access.** Reserve keys for the intended milestone, including the merchant's door, exit and item access. Price rooms sequentially using keys spent and recovered, fights, supplies and later access. Consider actual merchant offers and stock, delayed equipment routes, and Mattock wall bypasses before declaring a shortage.
- **Buy a concrete improvement.** Merchant HP is generally poor value; altar HP also advances the shared purchase count and raises later stat prices. Consider HP spending only after checking lower-damage routes, deferred supplies, upgrades and revisits, and identify the specific survival blocker it resolves. A bailout for an inefficient route does not establish a good purchase.
- **Acquire and use items as separate decisions.** Reserve consumables for a named blocker. Compare their immediate return with other uses, including key savings, avoided fights and lost future supplies. Super Mattock needs a planned floor and worthwhile return, plus its price and merchant access; availability alone is not a reason to buy it early.
- **Compare shield strategies, then prioritize the chosen objective.** Compare bombing with fighting the guards after any needed upgrades; weigh HP and hazard costs, shield timing, gold rewards and the Bomb's value elsewhere. Once the Sacred Shield is the chosen objective, make obtaining it the top priority throughout preparation and travel. Take detours only when they are needed for access or survival, and identify how they enable the shield route. Budget the required keys, access item, guards and movement hazards together; defer optional side trips for fights, supplies or exploration until protected. Neither the acquisition method nor its timing is established as optimal by the completed attempt.
- **Check traps and formation puzzles before committing.** Budget all forced encounters, and inspect clues or the relevant predicate before killing every guard. An enemy's individual forecast cannot establish that a trapped sequence is survivable or that clearing all enemies preserves a puzzle solution.

When a route repeatedly needs rescue spending or cannot fund its next access, compare a rewind/restart with continuing. Use the user's authorization and scope; do not hide restarts or replace the live journey with an unreviewed candidate.

## Mechanics worth checking

Read [campaign considerations](references/campaign-considerations.md) when planning consumables, later first-cycle objectives, gem/altar comparisons or cycle transitions. It records relevant mechanics and illustrative observations, not a prescribed route.

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

Treat documented game quirks as intended mechanics unless new evidence establishes a defect. Distinguish a helper failure from a server failure. Base any suspected issue on current behavior, source and a minimal reproduction; a difference from the agent's expectation is insufficient.
