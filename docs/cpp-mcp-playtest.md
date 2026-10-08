# C++ MCP first-ten-floor playtest and interface review

Completed on 2026-10-09, using the public native stdio MCP. The final worker
reports native MCP version **0.11**. The connected Python bridge was also
updated and retained the completed game through hot reload.

For reusable play guidance, see the versioned
[campaign skill](skills/tower-cpp-campaign/SKILL.md) and its
[tested early-game reference](skills/tower-cpp-campaign/references/first-ten-floors.md).
The strategy's tested scope is first-cycle floors 1-10; later floors and cycles
require a fresh assessment.

## Outcome and reproducible evidence

The run defeated Skeleton A on floor 10, collected the boss rewards and
entered floor 11. It finished with:

| Resource | Value |
|---|---:|
| HP | 754 |
| Attack / defense | 32 / 33 |
| Gold | 287 |
| Yellow / blue / red keys | 3 / 0 / 0 |
| Equipment | Iron Sword / Iron Shield |
| Altar purchases | 2: attack +2 for 20 gold, defense +4 for 40 gold |
| HP purchases / merchant trades | 0 / 0 |
| Next altar price | 80 gold |

The playtest initially explored through the enabled developer-mode MCP.
The completion evidence comes from a fresh **normal-mode** worker, with no
simulation tool or direct state edits. Source knowledge guided decisions,
including secret-wall contacts and Flight landings. One replay rewind corrected
an inefficient yellow-key branch; this was disclosed during the attempt.
The resulting route is reproducible, but it is not a claim of optimal play or
an uninterrupted first attempt.

Artifacts under `artifacts/cpp-mcp-first10/`:

- [Completed native save](../artifacts/cpp-mcp-first10/normal-first10-cleared.dat)
  and [save companion](../artifacts/cpp-mcp-first10/normal-first10-cleared.dat.replay.jsonl).
- [Completed replay](../artifacts/cpp-mcp-first10/normal-first10-cleared.jsonl):
  1,014 native inputs, 35,283 bytes, including save and automatic checkpoint boundaries.
- [Measurements and verification results](../artifacts/cpp-mcp-first10/measurements.json)
  retain the measured payload sizes, navigation totals and save/replay checks.
- `normal-iron-sword.dat` preserves the earlier sword milestone at 754 HP with
  zero altar purchases. `normal-before-floor10.dat` preserves the late preparation stage.

Artifacts are local playtest outputs and are ignored by Git. The completed
recording, useful checkpoints and small measurement result are retained for
continuation and inspection. Exploratory saves, discarded branches, detailed
request traces and temporary playtest/measurement helpers were removed after
review. The request trace began from an imported prefix and included a rewound
branch; navigation totals describe the observed requests rather than every input
in the full recording. The recording is the evidence for the completed route.

The headless CLI reproduced the final hero, inventory and current map from
the exported replay. Loading the 6,957-byte native save produced the same
gameplay state and resumed its recording companion. The successful replay was
imported into the originally enabled MCP session, which is now on floor 11.
The connector's developer observation setting remains as it was configured;
the imported recording itself was played in normal mode.

## Removing navigation overhead

The original interface made the agent request a path, inspect its directions,
then send individual movement actions. Each step returned the whole observation.
This spent requests and context on the mechanical route between strategic choices.
The game decisions are combat order, equipment timing, keys, purchases, clues and
resource reserves. Ordinary movement can be handled in the MCP layer.

Implemented in [mcp.cpp](../cpp/src/mcp.cpp) and
[mcp_observation.cpp](../cpp/src/mcp_observation.cpp):

```json
{"x": 5, "y": 8, "floor": 4, "interact": true}
```

These are `navigate` arguments. The server finds a route through apparent road,
executes native inputs and contacts the chosen endpoint. It also supplies the
second contact required to enter an opened door. An intervening key, enemy,
door or NPC needs its own selected destination. This preserves the ordering
decisions that can change the run's resource balance.

An unreachable target executes zero inputs. `interact: false` reaches the
approach square for an event. Optional `floor` rejects stale coordinates.
Navigation stops on an unexpected intermediate script or damage, an open shop,
death or a floor transition. Its response aggregates messages and reports how
many native inputs ran and why navigation stopped. All steps remain in the
recording, so save/replay behavior stays reproducible.

The observed trace contains 269 navigation calls executing 971 native inputs,
including the discarded branch and refused requests. After the last rewind,
181 navigation calls executed 600 native inputs: **about 70% fewer movement
requests** than issuing one request per native input. This comparison excludes
any additional old `plan_path` requests. One navigation call executed 29 inputs.
It measures observed request aggregation, not a theoretically minimal route.

## Output organization and measured savings

The new defaults return only the current-floor decision data:

- `game_state`: compact. `floor.walkable_rows` identifies apparent road;
  `floor.points` lists event coordinates and geometric reachability.
  `tile_types["<id>"]` stores each name, kind, pickup value, key requirement
  and unlocked enemy forecast once per type.
- `navigate` and `game_action`: summary. Current hero/resources, pending choices,
  aggregated feedback and `changes` replace a repeated map/history dump.
  Floor transitions automatically return compact destinations.
- `new_game`, load, replay and developer simulation: compact by default.
- `detail: "full"`: retains the previous projection, including developer
  tower diagnostics, raw maps, history and item usage explanations.
- File replay export: metadata only by default. `include_replay: true`
  explicitly includes the recording; no-path export retains its inline default.

`changes.stats` contains deltas; `changes.inventory` contains new values,
including zero for a consumed item. Changed tiles use coordinates and visible
IDs. Concealed walls remain walls in normal mode. `reachable` means the target
can be contacted geometrically, while type-level `available` reflects a known
fight forecast or possessed key. A sealed gate may be reachable and still refuse
contact. Forecast availability requires the Hero Orb in normal mode.

The table measures UTF-8 bytes of the JSON **payload**, once, at identical states
or equivalent native actions. The previous immutable worker was used for the
baseline. The retained measurement result also records complete JSON-RPC sizes,
which include both protocol representations. These are byte reductions, not
exact model-token counts.

| Situation | Previous default | New default | Reduction |
|---|---:|---:|---:|
| Normal initial floor 1 state | 3,130 | 2,970 | 5.1% |
| Normal completed floor 11 state | 8,912 | 4,225 | 52.6% |
| Normal routine movement response | 8,914 | 726 | 91.9% |
| Developer initial floor 1 state | 25,111 | 3,903 | 84.5% |
| Developer completed floor 11 state | 28,737 | 4,224 | 85.3% |
| Developer routine movement response | 28,739 | 725 | 97.5% |
| File export, inline versus metadata | 44,595 | 117 | 99.7% |

The untouched normal floor has no accumulated history or forecasts, so its
savings are naturally smaller. The first compact implementation was actually
larger there (4,115 bytes); consolidating all event descriptions into the type
catalog removed that regression. It now includes destination/reachability data
while remaining smaller than the earlier response.

Full observations matched the old worker exactly on initial and completed
states in both normal and developer modes. Clients consuming the legacy shape
must request `detail: "full"`. The temporary 0.10 `enemy_types` field was
consolidated into `tile_types` in 0.11. See [the API documentation](cpp-mcp.md).

## Mechanics and resource strategy from source

### Combat rewards breakpoint planning

[Game::forecast in combat.cpp](../cpp/src/combat.cpp) computes ordinary combat
using scaled monster stats and an opening hero strike. In the first cycle,
without special item multipliers:

```text
hero_hit = attack - enemy_defense
hero_hits = ceil(enemy_hp / hero_hit)
damage = max(enemy_attack - defense, 0) * (hero_hits - 1)
```

Attack must strictly exceed enemy defense, and surviving a battle requires
`damage < current_hp`. Forced fights give the enemy the opening strike and
ignore Cross/Dragon Slayer bonuses. The exact native forecast should be used
for encounters with those items or later-cycle scaling.

Attack gains matter when they remove an enemy strike. For example, attack 23
needs two hits against a Bat, four against a Priest, three against Skeleton C
and five against Skeleton B. Defense saves HP on each remaining enemy strike.
Choose an upgrade by its effect on the next necessary group of enemies, rather
than treating all +1 attack or defense as equal.

### Preserve global altar purchases

[The altar contact](../cpp/src/contact.cpp) uses global purchase count `n`
(zero before the first purchase): `10 * (n*n + n + 2)`. Prices are
**20, 40, 80, 140, 220, ...**. [The purchase handler](../cpp/src/npcs.cpp)
grants HP `100*(n+1)*cycle`, attack `2*area*cycle` or defense `4*area*cycle`,
where altar area is integer division `(floor+10)/10`.

The floor-4 altar gives +2 attack or +4 defense. The floor-12 altar gives
+4 attack or +8 defense at the same next global price. The completed run leaves
the third purchase at 80 gold rather than increasing it with early HP buys.
Buying earlier can still be worthwhile if it saves enough HP or opens equipment;
the tested route used two early upgrades, not a blanket prohibition on spending.

### Equipment before optional combat

[Pickup handling](../cpp/src/contact.cpp) gives first-area gems +1, potions
50/200 HP and Iron Sword/Shield +10 attack/defense. Potion/gem area is
`(floor+9)/10`, so it differs from altar area at a multiple of ten.

The productive early route is:

1. Complete the opening capture and prison escape. The first-cycle
   [capture callback](../cpp/src/game.cpp) resets HP to 400 and attack/defense
   to 10 and removes equipment; it preserves keys, gold and items in that branch.
   The initial corridor constrains what can be collected before capture.
2. Take the accessible floor-3 top-room supplies: five yellow keys, one blue key
   and 600 HP, then prioritize reaching the floor-5 Iron Sword. Defer costly side
   fights until its +10 attack reduces them. This run reached the sword at
   754 HP before spending any altar gold.
3. Use attack breakpoints and cheap gems to unlock the climb. Secure the
   floor-9 Iron Shield through its secret-wall entrance before most optional
   skeleton cleanup. Hidden-wall coordinates are supported by the
   [original map constants](../cpp/src/original_constants.hpp); normal-mode
   observation and navigation intentionally preserve their concealed appearance.
4. Collect potions and optional gold after equipment lowers the entry cost where
   practical. Spend a key on a room for its net gain and future access, reserving
   enough keys for the next mandatory corridor. The floor-4 middle supplies and
   floor-6 upper supplies can replenish yellow keys. A potion can be profitable
   even behind a fight, but exhausting keys before the next gate caused this
   playtest's rewind.
5. Avoid unnecessary early merchant trades. [Merchant offers](../cpp/src/npcs.cpp)
   include a 50-gold blue key on floor 6 and five yellow keys for 50 gold on floor 7;
   reaching the latter room also costs a blue key. Reserve those options for an
   actual route shortfall. The final run used neither.

### Budget the floor-10 arena before triggering it

[The floor-10 scene](../cpp/src/scenes.cpp) rearranges six Skeleton C and two
Skeleton B into the arena when its trigger is contacted. At attack 29 and
defense 30, they cost `6*24 + 2*66 = 276 HP`. Skeleton A then costs 245 HP.
The total known ordinary-combat budget is **521 HP**, with no intermediate
arena potions.

The run entered that fight with 675 HP and emerged with 154 HP. Its preparation
used the native [Flight rule](../cpp/src/items.cpp): ascending to the highest
floor reverses the landing choice when that floor was reached by upward stairs.
For floor 10, the two landings are `(0,9)` and `(5,9)`, stored in the original
maps. Flying to floor 9 and back therefore reached the center without spending
two yellow keys on the lower-left corridor. The floor-9 landing also permitted
collecting a remaining red potion for +50 HP.

Those two saved keys bought access to the right-side potion room. A Priest cost
4 HP, Skeleton B cost 66 HP, the red gem gave +1 attack, and the blue potion
gave +200 HP: a net +130 HP from the 545-HP preparation state. No side Skeleton C
fight was needed for that route.

[The guard/reward checks](../cpp/src/floor_checks.cpp) open the boss gate after
the arena soldiers fall, then create three yellow keys, three blue potions,
three red gems and three blue gems after the boss. Their collection raised the
run to 754 HP, 32 attack, 33 defense and three yellow keys before entering floor 11.
The Fairy contact removes the central obstruction and records its checkpoint.

This strategy preserves gold and the next altar price. Further optimization
should compare total damage saved by different purchase timings and equipment
routes; the playtest does not prove that both early altar buys are essential.

## Technical findings and remaining improvements

No engine crash, broken native save/replay or stuck shop was observed during
the completed first-ten-floor run. Destination refusals were explainable by
intervening events or concealed walls. Flight landings that initially appeared
surprising are original game rules, not a teleportation bug.

One integration limitation remains: the bridge emitted
`notifications/tools/list_changed` and reported `tools_changed: true`, but this
active chat retained its original tool schemas and did not expose `navigate`
as a newly callable named tool during the turn. The updated native worker was
tested through an actual stdio client, and the successful state was transferred
back to the enabled connector. Refreshing/reconnecting the connector's catalog
is needed if the chat still lacks the new tool. The C++ server and bridge-side
notification behavior are covered by integration tests; the host's metadata
cache is outside this repository.

Development also demonstrated the Windows executable lock when a direct MCP
helper still ran from the compiler output path. Closing that helper released
the lock. The configured immutable-worker bridge retained its session and
hot-reloaded successfully with a stable bridge PID, so the bridge is the useful
development entry point.

Further improvements, in descending practical priority:

1. **Consume one protocol representation in the host.** Responses retain both
   `structuredContent` and identical JSON text in `content` for compatibility.
   Complete JSON-RPC bytes are roughly twice the single-payload figures. Whether
   both become model context depends on the MCP host. Avoiding duplicate context
   in the client would help without weakening the readable server schema.
2. **Optional ordered destinations with interruption.** A list of explicitly
   selected points could collect a chosen reward row in one request, stopping
   before any unexpected event. Keep key spending and combat selection explicit;
   automatic clearing of a room would conceal strategic decisions.
3. **Small refreshed destination deltas.** Summary responses update tiles and
   resources, but they do not recompute the client's cached reachability/type
   catalog. A revision plus newly reachable points/new definitions could remove
   some follow-up state reads. For now, request compact state after scenes or
   when refreshed forecasts are needed.
4. **Machine-readable purchase effects.** Shop choices currently have IDs,
   readable labels, cost and affordability. Explicit `stat`, `gain`, and
   `next_price` fields would make resource comparisons easier without parsing
   labels or revisiting source formulas.
5. **Dedicated compact/summary construction.** The current implementation skips
   the developer all-floor dump unless full is requested, but still builds some
   legacy current-floor fields before projecting the smaller view. A direct
   builder could reduce CPU work. No CPU bottleneck was measured in this run.

## Validation

- Release C++ build passed. All C++ sources, headers and tests were then formatted
  with `cpp/.clang-format`, following the workspace instructions.
- `[mcp]`: **26 cases, 1,913 assertions passed**.
- Headless `ctest -LE audio`: **76/76 passed**, including actual stdio MCP and
  Python bridge hot reload. Audio checks were excluded because no audio work
  was part of these changes.
- New checks cover grouped type definitions, compact defaults, native navigation
  and replay parity, both door contacts, intervening-event refusal, stale-floor
  rejection, scripted capture interruption, hazard damage, shops and metadata
  replay export. Legacy fidelity checks explicitly request full observations.
- The completed replay, native save reload and old/full observation parity were
  verified during measurement; the results are retained in `measurements.json`.
- Published worker: `2026-10-08T18-04-22-405722Z-b0be0a3e6140-25aeabdc`.
  Bridge PID 7920 stayed active; worker PID changed to 79680;
  `session_restored: true`, `tools_changed: true`, with no worker error.
