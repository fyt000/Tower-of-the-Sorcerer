---
name: tower-cpp-campaign
description: "Play Tower of the Sorcerer through the tower_cpp MCP using destination navigation, compact observations, combat forecasts, key budgeting and persistent saves. Includes a tested first-cycle floors 1-10 strategy and guidance for reassessing later floors and cycles."
---

# Tower C++ Campaign

Use the native `tower_cpp` MCP to make strategic choices while the server handles ordinary walking. Plan for the next equipment, resource or progression milestone, then update the plan from observed results.

## Scope of the strategy

The recorded strategy has been playtested only on **first-cycle floors 1-10**, ending on floor 11. Read [the early-game reference](references/first-ten-floors.md) when playing that section or reviewing its route. Its coordinates, enemy damage, two altar purchases and merchant avoidance describe that particular tested route.

For floors 11 onward, backside rounds or further cycles, establish a new plan from current state, native forecasts, clues and relevant source. Equipment, monster scaling, hazards, scripts, merchants and carry/reset rules can change the economics. Early-game experience is evidence for a hypothesis, not proof of a later-game strategy.

## Efficient MCP usage

1. Start with `game_state` using its compact default. Read the current hero, `cycle`, inventory, phase and pending interaction before deciding whether to continue or load a requested save. Preserve an existing journey unless the task calls for a new one.
2. Select an event from `floor.points`. Resolve its numeric `id` through `tile_types["<id>"]` for the name, kind, pickup gain, key color or `enemy.forecast`. Coordinates run from 0 to 10, with `(0,0)` at the top left. `walkable_rows` uses `.` for apparent road and `#` for other squares.
3. Use `navigate` for movement and endpoint contact. Choose intervening pickups, fights and doors individually; the server routes through apparent road. Routine action responses are summaries, and floor transitions include the next floor's compact view.
4. Read `navigation.reason`, `messages`, hero and `changes` after acting. Stop and revise the plan when a script, hazard or unexpected result interrupts it. Refresh compact state after map rearrangement, when access has changed, or when new stats require updated forecasts. Avoid reading the same full observation after every step.

Example tool arguments:

```json
{"x": 5, "y": 8, "floor": 4, "interact": true}
```

`floor` guards against stale coordinates. `interact` defaults to true: the endpoint can fight, collect, open a shop or change floors. Selected doors receive both native contacts to open and enter. `interact: false` stops at an event's approach square. An unreachable target executes zero movement inputs.

`reachable` describes geometric access to contact a point; type-level `available` describes a known fight's survivability or key possession. Neither guarantees that the whole route is safe. A sealed gate can be reachable and still refuse contact. For event endpoints, `navigation.reached` can mean successful contact while the hero remains adjacent.

Use `game_action` for shop choices, items and deliberate single-step contacts:

```json
{"action": {"type": "choose", "choice": "1"}}
{"action": {"type": "use_item", "item": "flying_orb", "floor": 9}}
{"action": {"type": "move", "direction": "right"}}
```

Choose only a listed shop reply ID. Speech settles automatically; shops remain open for a reply or cancel. Normal navigation preserves concealed walls, so approach a wall supported by a clue/source and deliberately contact it with a movement input. Avoid probing every wall.

Hero Orb forecasts are already present when `forecasts_unlocked` is true; repeatedly using the orb adds no forecasting information. Use `inspect_tile` for one missing detail. Reserve `detail: "full"` for a concrete diagnostic need. `plan_path` is useful for examining a route, while `navigate` is the ordinary execution tool.

Flight uses native direction and stair-landing rules. Confirm the resulting coordinates rather than assuming a destination always uses the same entrance. Native stairs and Flight skip floor 44; wing behavior differs.

## Resource planning

- **Choose the next milestone first.** Compare routes to equipment, a necessary key supply, the next area or a required encounter. Defer optional fights when an upcoming upgrade will reduce their cost, unless their reward enables that upgrade now.
- **Evaluate a room sequentially.** Account for keys spent and recovered, entry fights, potion gains, stat gains and subsequent access. Recompute damage after a gem or equipment pickup; a sum of stale forecasts can misprice the route. Keep a reserve for the next known mandatory colored doors.
- **Buy meaningful breakpoints.** Compare an upgrade's damage savings across the next required fights. Attack matters when it removes enemy strikes; defense saves HP on remaining strikes. A native forecast marked survivable covers that one fight, not an entire locked sequence.
- **Preserve future options without hoarding blindly.** HP, keys, gold, consumables and the global altar purchase count all matter. A purchase can be correct when it opens better equipment or prevents a bottleneck. Merchant and HP purchases are valid options; their absence in the tested first ten floors is not a general rule.
- **Budget trapped sequences before triggering them.** Include all known guards, boss fights and movement hazards, then preserve enough HP to survive strictly. Reinspect the board and clues after scenes before acting on old coordinates.

Altar purchase `n` costs `10*(n*n+n+2)`, starting with `n=0`: **20, 40, 80, 140, 220, ...**. Each choice increases the same global count. Native gains are HP `100*(n+1)*cycle_factor`, attack `2*area*cycle_factor`, defense `4*area*cycle_factor`, with altar `area=(floor+10)/10` using integer division. Waiting for a higher-area altar can improve stat gains at the same next price, but weigh that against the route's current HP cost. Pickup area instead uses `(floor+9)/10`.

For ordinary first-cycle combat without special item bonuses, attack must exceed enemy defense, and:

```text
hits = ceil(enemy_hp / (attack - enemy_defense))
damage = max(enemy_attack - defense, 0) * (hits - 1)
```

Survival requires damage strictly below current HP. Use native forecasts for scaled stats and item effects. Forced combat gives the enemy the opening strike and ignores ordinary Cross/Dragon Slayer bonuses; movement magic and scripted damage also need separate accounting.

## Reassess later floors and cycles

When entering a new area or round, inspect live cycle factor, equipment/protection, inventory, accessible supplies, enemy types, shops and clues. Determine the next necessary encounter and equipment milestone before choosing purchases. Recalculate attack breakpoints and key reserves from those enemies, rather than carrying over first-area numeric thresholds.

When a puzzle or rule changes the route, read only its relevant implementation. The repository is `D:/projects/tos-rust`:

| Question | Source |
|---|---|
| Combat, scaled rows, first strike, item multipliers | `cpp/src/combat.cpp` |
| Pickups, doors, altar price, stairs, movement hazards | `cpp/src/contact.cpp` |
| Merchant offers, purchases, NPC gifts and clues | `cpp/src/npcs.cpp` |
| Flight, consumables and passive items | `cpp/src/items.cpp` |
| Arrival scenes, traps, boss formations and endings | `cpp/src/scenes.cpp` |
| Guard predicates, gates and scripted rewards | `cpp/src/floor_checks.cpp` |
| Capture and cycle initialization/carry rules | `cpp/src/game.cpp` |
| Original maps, landings and monster rows | `cpp/src/original_constants.hpp` |

`docs/mechanics.md` summarizes retained original rules, including later-cycle save reconstruction. `docs/cpp-mcp.md` documents tool usage. Treat observed gameplay, source-derived rules and untested strategy proposals as distinct evidence. Developer observations and `simulate_actions` are available only in developer mode; identify their use when reporting a run.

## Save, resume and retain learning

Use `save_game` with an **absolute path** at a useful milestone. Normal-mode saving requires a living hero with the Hero Orb; a native file save also needs an idle boundary and closed Flight selector. The `.dat` and `.dat.replay.jsonl` companion preserve continuation across restarts. A no-path opaque session checkpoint expires when the connection ends.

```json
{"path": "D:/projects/tos-rust/artifacts/my-run/floor20.dat"}
```

Load a requested native save with `load_game` using its path. `replay_game` imports the full recording or a `limit` prefix and permits takeover from there. Native file reload applies original reconstruction rules; exact session copies and replay reconstruction have different uses. For later-cycle encounters whose shared monster rows change on native load, verify the post-load forecast.

Export recordings with `export_replay({"path":"<absolute path>"})`; its file metadata is enough for routine use. Retain checkpoints before a risky strategic experiment when allowed by the task. Record any rewind or developer simulation honestly and retain evidence for completion claims.

When adding discoveries to this skill, label the floor range, cycle, relevant starting resources and whether the route was actually tested. Keep a compact milestone note with current resources, next objective, unresolved rule and save/replay paths so a future session can resume planning efficiently.
