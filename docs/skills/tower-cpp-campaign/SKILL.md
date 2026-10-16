---
name: tower-cpp-campaign
description: Play or investigate Tower of the Sorcerer through tower_cpp MCP, budgeting combat, keys and items and preserving campaign continuation.
---

# Tower C++ Campaign

Use one connected `tower_cpp` session as authoritative. Check `mcp_runtime`
when available, then compact `game_state` for deployment, mode, cycle and actual
journey. Separate processes can hold different games.

Choose a progression/equipment milestone. Select `floor.points`, resolve IDs
through `tile_types`, and use guarded `navigate(x,y,floor)` for road travel and
endpoint contact. Use `game_action` for shop choices, items and concealed-wall
contacts. Inspect returned changes, messages, interactions and navigation reason
before continuing. Refresh compact state after scripts/access changes; request
full detail only for diagnostics.

`reachable` describes geometry; forecasts exclude movement hazards and scripts.
Budget the whole approach, forced sequence and return, with HP strictly above
total damage. Keep fights, purchases and consumables deliberate.

Read [campaign considerations](references/campaign-considerations.md) for opening,
economy, item and ending decisions; read [MCP workflow](references/mcp-workflow.md)
for continuation, interruption or worker recovery. Reassess costs in the active
build/cycle. A successful route is evidence of feasibility, not optimality.

| Rule to investigate | Repository source |
|---|---|
| Combat/bonuses | `cpp/src/combat.cpp` |
| Pickups, doors, hazards | `cpp/src/contact.cpp` |
| Offers, altars, clues | `cpp/src/npcs.cpp` |
| Flight/items | `cpp/src/items.cpp` |
| Traps, formations, endings | `cpp/src/scenes.cpp`, `cpp/src/floor_checks.cpp` |
| Capture/cycles | `cpp/src/game.cpp` |
| Base maps/enemies | `cpp/src/original_constants.hpp` |

Preserve user constraints on purchases, rewinds and campaign boundary. Report
restarts, tested branches and developer simulation explicitly; do not replace
the live journey with an unreviewed candidate. Investigate suspected defects
with current source and a minimal reproduction; helper errors and surprising
mechanics are not by themselves server defects.

At milestones retain build/session, cycle, stats/gold, colored keys, protection,
reserved items, next objective and absolute save/replay paths. Before ending,
check worthwhile remaining stats, cheap gold, purchases and the unused 3% boost.
Distinguish reaching 50F, completing its ending and advancing a cycle; stop at
the requested boundary.
