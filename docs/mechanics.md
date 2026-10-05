# Original-game mechanics and evidence

This project targets the installed English **Tower of the Sorcerer for Windows 1.2**, by Oz and Kenichi. It must not silently substitute the rules of the common Flash remakes. No implementation or configuration from the user's Cocos2d-x project was copied.

## Evidence and confidence

The primary local sources are `D:\Program Files (x86)\Tower of the Sorcerer\TSW.txt`, `Readme.txt`, and the installed `TSW.exe`. Executable addresses below are virtual addresses with image base `0x400000`. They describe the original executable before any patches. The `CODE` section maps RVA `0x1000` to file offset `0x400`; use the PE section table for other sections.

The [tswKai reverse-engineering project](https://github.com/Z-H-Sun/tswKai) documents original-game memory layouts and quirks. Its [combat analysis](https://github.com/Z-H-Sun/tswKai/blob/main/monsters.rb), [altar calculations](https://github.com/Z-H-Sun/tswKai/blob/main/tswMPExt.rb), and [event-interpreter notes](https://github.com/Z-H-Sun/tswKai/blob/main/tswBGM.asm) were used to locate original routines. No upstream implementation is imported into the Rust engine.

An extracted map or dialogue is not proof that every associated event has been implemented. Event builders were also executed in an isolated x86 emulator against the original executable and extracted maps. The probe skips calls, records the skipped targets, and reports map reads, map writes, generated event records, and monster-table mutations. Called helpers were inspected separately when they affect gameplay. This is evidence for the translated transitions, rather than a claim that a complete original playthrough has been reproduced. Backside reset, capture, scaling and ending branches have separate executable evidence and scenario tests; original scoring and a natural full-tower playthrough remain unverified.

## Deterministic combat

The installed manual states that the player strikes first and attacks alternate until one participant reaches zero HP. There is no random combat component.

For an ordinary monster, let `H`, `A`, and `D` be its HP, attack, and defense. Let `a` and `d` be the player's attack and defense. The original rejects an attack when **base** `a <= D`. Otherwise:

```text
effective_player_attack = a * applicable_item_multiplier
damage_per_player_hit   = effective_player_attack - D
enemy_retaliations     = (H - 1) / damage_per_player_hit  [integer division]
damage_per_retaliation = max(A - d, 0)
total_damage           = enemy_retaliations * damage_per_retaliation
```

Victory requires current player HP to exceed total damage. HP equal to total damage is lethal. The Cross doubles effective attack against Zombie, Zombie Knight, and Vampire. Dragon Slayer doubles effective attack against Dragon. The base-attack restriction applies even with either item: this original-game quirk must be configurable if a corrected ruleset is offered. Lucky Gold doubles normal battle rewards.

Special encounters can attack before the hero; those must use a separate combat mode. Ordinary enemy predictions cannot stand in for scripted boss encounters.

## World and movement

Maps contain an 11 by 11 tile grid. The original executable stores 51 records, including floor 0, at a stride of 123 bytes: two stair-arrival metadata bytes, followed by 121 tile IDs. Stairs normally bypass hidden floor 44, while Ascent Wing can reach it from floor 43.

Ordinary movement is orthogonal. A colored door consumes one matching key. Gates use monster/event conditions instead of keys. Secret wall tiles become passages when touched; ordinary walls block movement. Scripted encounters may change walls, gates, enemies, and pickups on the current floor or another floor.

Orb of Flight is reusable and restricted to an adjacent stair. Original floor selection spans floor 1 through the highest floor reached by ordinary upward stairs, excluding floor 44; intervening floors need not have been individually visited. The landing position follows stair-arrival metadata. Custom campaigns can instead use previously visited floors through `rules.flying_original_selection = false`. [The Flight audit](flight-context-audit.md) documents this selector and its hidden map callbacks.

## Magic hazards

An adjacent Magician A deals 200 HP and an adjacent Magician B deals 100 HP. Contributions from multiple orthogonal neighbors add. Being between two opposing Sorcerers (Magic Sergeants) removes half the current HP, rounded upward: 1000 becomes 500, 1001 becomes 500, and 1 becomes 0. Horizontal and vertical pairs count; single, diagonal and L-shaped neighbors do not. Sacred Shield protects against these magical hazards, including after collecting a lower shield for its display slot. Hazard calculations happen on the actual committed step; rejected movement must not inflict damage.

On floor 47, adjacent Magician A also retreats one cell away from the hero if its destination is ordinary road. Damage resolves before retreat. Sacred Shield suppresses damage but still permits retreat. Original routine `mazyutu1` at `0x44C5C4` incorrectly tests the hero's row for horizontal moves and permits row wrapping at the left/right boundary. The bundled campaign uses corrected independent x/y bounds; `rules.magician_retreat.bounds = "original"` can reproduce the historical behavior within valid board memory. [The tswKai comparison](tswkai-audit.md) includes direct queue and mask evidence.

## Altar economy

There is one global count of successful altar purchases, shared by all altars. With `n` previous purchases, the next purchase costs:

```text
gold_cost = 10 * (n*n + n + 2)
HP_gain   = 100 * (n + 1)
ATK_gain  = 2 * area
DEF_gain  = 4 * area
```

The altar areas are 1, 2, 4, and 5 on floors 4, 12, 32, and 46 respectively. Thus the first costs are 20, 40, 80, 140, and 220 gold. HP increases with purchase count, independently of altar area. The selected gain is applied, gold is deducted, then the shared purchase count increases.

The original includes distinct merchants with fixed trades and one-use availability. The floor-28 merchant buys yellow keys for 100 gold each. Trades must be attached to NPC instances; a universal shop cannot reproduce their behavior.

## Pickups and equipment

Red potions provide 50 HP, blue potions provide 200 HP, and each gem provides 1 ATK or DEF before area scaling. Their area multiplier is `ceil(floor / 10)` for the five ordinary tower areas. First-cycle potion values are consequently 50/200 on floors 1–10, 100/400 on floors 11–20, and 250/1000 on floors 41–50.

The five swords and shields add **10, 20, 40, 50, and 100** ATK or DEF. Equipment gains are additive; the original routine does not subtract the previous weapon's bonus. In particular, the Holy tier provides 50, rather than the 80 found in some remakes. These values were recovered from the pickup branches of `TTSW10.handan` in the original executable. The Sacred Shield also grants protection against adjacent magic hazards. Backside cycles multiply these pickup gains by the configurable cycle multiplier, originally 44.

The player has separate `weapon` and `shield` display slots, and the GUI shows
them beside the hero statistics. Every equipment pickup replaces its display
slot, including a lower tier, while adding its stat bonus to the accumulated
total. Starting gear and restored slots do not apply bonuses again. Equipment
does not appear in the special-item inventory. Collected tags remain internal
for authored conditions and persistent abilities: Sacred Shield's magic
protection remains active after collecting a lower shield, with an explicit GUI
caption when its displayed slot has changed. Capture clears both slots; a new
cycle starts with the authored Sacred gear while carrying total stats.

Save files preserve the current slots, including explicit empty slots. For
legacy saves lacking these fields, load infers each slot from the last retained
equipment tag of that type. This recovers ordinary pickup order, but old saves
did not record repeated collection of an already retained item, so their exact
most-recent tier cannot always be recovered. Migration does not alter stats.

Before the Hero Orb is acquired, actual enemy contact still records the original
encounter information: name, HP, ATK and DEF. The GUI's **Last encounter** panel
keeps that contacted enemy and its location separate from tile hover inspection.
The record survives save/load and worker replacement, and changes on another
real encounter, including a blocked attack or a fatal fight. Hovering an unseen
enemy does not supply these stats; gold, projected damage and survivability
remain part of Hero Orb forecasting.

The campaign begins at 1000 HP, 100 ATK, and 100 DEF with the Sacred Sword and Sacred Shield. First-cycle capture on floor 3 changes HP/ATK/DEF to 400/10/10 and removes that equipment; backside capture preserves those stats and clears all special inventory. It does not reset keys or gold in the examined original routine. Orb of the Hero is obtained from the floor-3 old man, Orb of Flight from the floor-1 pickup, and Orb of Wisdom from floor 6.

## Special items verified directly in the executable

The original holds three orbs and twelve further special items. Item slots at `0x4B86C4` are Sword, Shield, Hero Orb, Wisdom Orb, Flight Orb, Cross, Elixir, Mattock, Destruction Ball, Warp Staff, Ascent Wing, Descent Wing, Dragon Slayer, Snow Crystal, Magic Key, Super Mattock, and Lucky Gold.

| Item | Original effect | Direct evidence |
|---|---|---|
| Elixir | Add `10*ATK + 5*DEF` HP and consume item. | `0x450D13` to `0x450D96` |
| Magic Mattock | Remove the four neighboring ordinary walls; consume item. | `0x450DA7` to `0x450F27` |
| Destruction Ball | Destroy eligible enemies in the four cardinal neighboring cells, award the raw monster-table gold, consume item even if no target is destroyed. | `0x450F31` to `0x451127` |
| Warp Staff | Mirror coordinates to `(10-x, 10-y)` on the same floor; destination must be ordinary road. A charge is consumed before the destination check. | `0x4511B3` to `0x4513DF` |
| Ascent Wing | Move one floor upward at the same coordinates if the destination is ordinary road; consume only on success. | `0x4513E4` to `0x45153E` |
| Descent Wing | Move one floor downward at the same coordinates if the destination is ordinary road; consume only on success. Floor 0 is reachable from floor 1. | `0x451543` to `0x4516A6` |
| Snow Crystal | Cool only the four cardinal neighboring lava cells into road. Remains available after use. | `0x4516AB` to `0x4518E1`, single-cell helper `0x451D3C` |
| Magic Key | Open every yellow door on the current floor; consume item. Blue, red, and gate tiles are excluded. | `0x4518E6` to `0x4519F6` |
| Super Mattock | Remove all ordinary walls on the current floor; consume item. | `0x4519FB` to `0x451B42` |

The bomb classifier at `0x451C20` accepts monster tile ranges `61..90`, `93..96`, `133..144`, and `147..158`. It excludes Dragon, Giant Octopus, Zeno, and Great Magic Master. It does not apply Lucky Gold to the bomb reward in the examined routine. Preserve that distinction from normal combat. Large creatures need their occupied tiles cleared together by their dedicated encounter logic.

The same classifier treats only original tile **8** as ordinary brick. Mattock
and Super Mattock exclude tile 10's scripted wall and tile 9's hidden wall.
Mattock, Destruction Ball, Magic Key, and Super Mattock consume on an empty
confirmed use. See [the original item audit](original-item-audit.md) for the
Wisdom memory, Hero save gate, Flight selector, and corrections established by
the later executable audit.

## Campaign-event reconstruction

The original runs a stack of three-word records `(opcode, A, B)` at `0x48C74C`; the cursor lives at `0x48C5AC`. Records execute in reverse insertion order. Examples documented in the original-game mod are waits `(0,0,0)`, audio `(1,...,...)`, dialogue `(10, dialogue_id, 0)`, and tile replacement `(6, index, tile_id)`.

Input and interaction dispatch occurs in `TTSW10.handan`. The capture sequence begins at `TTSW10.opening2`, `0x464048`. Post-combat progression is handled by `TTSW10.moncheck`, `0x4664E4`.

| Floor | Post-combat event branch address |
|---|---|
| 2 | `0x4665A1` |
| 8 | `0x466814` |
| 10 | `0x466901` |
| 11 | `0x46763C` |
| 14 | `0x467729` |
| 15 | `0x46783E` |
| 17 | `0x467A3B` |
| 20 | `0x467DF8` |
| 25 | `0x46887E` |
| 30 | `0x468D0F` |
| 32 | `0x468F4D` |
| 33 | `0x469A08` |
| 34 | `0x469B98` |
| 35 | `0x469F53` |
| 38 | `0x46A2A2` |
| 40 | `0x46A2D3` |
| 41 | `0x46AB37` |
| 44 | `0x46AF38` |
| 45 | `0x46B02B` |
| 48 | `0x46B20C` |
| 49 | `0x46B2F2` |
| 50 | `0x46BFA8` |

The captured original dialogue establishes a staged floor-10 Skeleton encounter, floor-20 Vampire encounter, floor-25 Great Magic Master encounter, floor-40 Golden Knight waves, and floor-49 decoy Zeno. Floor 24 later provides a time-and-space gate to the real floor-50 ending. A successful original first-cycle ending involves the Sacred Sword and Zeno's staff; simply defeating the first monster placed on floor 50 is not an accurate ending.

**Dialogue indices differ between interfaces.** Opcode 10 uses one-based IDs: `roujin` decrements its queue parameter at `0x44A255` before reading the zero-based Delphi string list. Direct NPC hint lookup uses zero-based indices. Queue records 5, 17, and 55 append original strings 57, 58, and 59 respectively. Fairy queue records 16, 22, 24, 40, and 47 retain the score overlay instead of looking up an ordinary string. Keeping these distinctions avoids shifted boss speeches and an incorrect early-game hint at the end of the game.

`data/events.json` currently contains 103 original-derived campaign events. Their coverage includes capture and prison escape; guarded doors and rewards; the floor-10 Skeleton staging; the floor-15 thief's Octopus bypass; Vampire and Great Magic Master encounters; the floor-23 closing-wall puzzle; the floor-30 and floor-33 traps; the floor-32 stair ambush and retreat; the floor-42 Zeno/Knight execution scene; all thirteen forced floor-40 wave fights and the Golden Knight's retreat; the floor-39 clock-door puzzle; concealed floor-12, floor-16, floor-19, and floor-41 discoveries; the floor-43 magician trap; the floor-48 caster gate; the floor-49 dice seal, decoy, and rewards; and the princess doll/time-gate ending.

The floor-49 seal leaves the four corner Sorcerers alive, removes the four edge Sorcerers, and retains Zeno in the center. Direct execution then mutates Zeno's HP/ATK/DEF from 8000/5000/1000 to 800/500/100. This is represented by a persisted enemy override rather than a second hard-coded monster.

The floor-33 Ghost Soldier trap has two entrances, `(9,4)` and `(9,6)`, sharing one event count. Entering either closes the two gates while any original guard survives; defeating all four opens both gates. An already-cleared room stays open on late entry. The original initializer omits the lower trigger and its post-combat branch mishandles that route; the corrected campaign incorporates tswKai's lower-entrance repair and prevents the late-entry seal.

The floor-39 clock puzzle requires opening only the top and right yellow doors of the clock (indices 14 and 38). Either order reveals Warp Staff tile 43 at `(3,3)`, which grants three charges on pickup. It does not grant a wing. Opening an additional clock door prevents the pattern. Save/load retains the first opening and the one-time reward.

The floor-50 Thief at `(4,8)` uses zero-based dialogue 263, queued as original opcode-10 ID 264. His greeting has no map or stat effect. The interaction now shows that actual greeting rather than an extraction placeholder.

The princess interaction checks whether the Great Magic Master on floor 25 is gone and then creates the gate at floor 24 `(5,0)`. Entering that gate runs the extracted floor-50 narrative sequence and leaves the game active. Touching Zeno on floor 50 completes the first cycle without combat. The original `handan` branch at `0x4463A1..0x446473` checks the current cycle, queues the ending cinematic, and finally queues opcode 11/subcode 6 to reset for replay. The configured `next_cycle` effect reproduces that automatic transition into the backside tower after the presentation sequence.

Direct eligibility inspection found no Sacred Sword inventory, highest-floor, or decoy-victory gate. The tile dispatcher at `0x4444B7` routes princess tiles 27/28 directly to `0x445397`; `0x4453C9` checks only floor-25 boss cell `0x4B9575` for road 6 before creating the floor-24 portal. The floor-24 handler tests the seal-restoration flag and cycle flags, rather than additional first-cycle eligibility. This permissive original path allows portal access after the floor-25 boss, even before completing every later floor. Adding a strict full-tower requirement would change the original rules and should be an explicit campaign variant. The Sacred Sword appears in the story dialogue. `data/event-ending-disassembly.txt` preserves the exact dispatch, eligibility, and completion instructions.

Floor-change instructions update the active floor before subsequent tile instructions; Zeno's ending tile is therefore placed on floor 50, not floor 24.

The fairy callback `0x478F0C` calculates a score and rank, writes an automatic checkpoint, and removes the fairy. It does not grant HP/ATK/DEF or teleport the hero. The remake provides its modern continue interaction and general saving, but does not yet reproduce original score/rank tables or automatic fairy checkpoint files.

For maintainability, these effects are translated to campaign data with explicit triggers, conditions, ordered effects, and persistent event flags. The browser, CLI, and MCP call the same transition engine so that a recorded action list reproduces the same state.

The authored extraction tools are `tools/original_event_probe.py` and `tools/extract_original_events.py`. They require Python packages `pefile`, `capstone`, and `unicorn`; the game itself has no runtime dependency on them. Run the event generator after the map/dialogue extractor. Set `TOS_ORIGINAL_EXE` to probe a different location containing the same original executable. Generated `events.json` remains separate from editable `campaign.json`; campaign regeneration imports it along with `interactions.json`.

## Fidelity boundaries to retain in reports

There are several distinct popular remakes with different potion values, trades, cross semantics, equipment values, and endings. Any unverified inferred behavior should be documented as inferred. A complete map extraction plus general movement/combat does not by itself establish a verified full-original playthrough. Original data, native transition scenarios, browser tests, and a natural action replay are different kinds of evidence and should be reported separately. Fairy score/rank tables, exact original pixel/timer animation timing, and a complete natural first-cycle route remain separate validation work. The configured backside reset and multiplier are directly supported by executable evidence; modern presentation timing intentionally differs from the original Delphi timers.


## Enemy information unlock

Detailed monster stats and damage forecasts require **Orb of the Hero** (`hero_orb`). The floor-3 old man rewards it, once, and original dialogue entry 11 explains its forecasting ability. At `0x48108A`, the original forecast-panel routine tests item slot `0x4B86CC == 1` before displaying it. Orb of Wisdom is a different item on floor 6; it does not unlock the monster forecast. `rules.forecast_requires_item` makes the gate configurable and the shared snapshot/inspection API must enforce it before presenting any numerical monster detail.

## Backside / replay cycles

The reset instruction handler at `0x453415..0x453457` sets `0x4B8904` from 0 to **43** after the first ending. Calculation routines use `factor + 1`, hence a multiplier of **44**. A later ending leaves 43 in place and sets `0x4B8908` to 1. The multiplier remains 44 on the third and later cycles; it does not grow exponentially.

`TTSW10.syokidata1` at `0x455CB8` resets the tower maps, floor and landing position to floor 1 `(5,10)`, keys, event variables, altar visits, and sword/shield levels to Sacred. It skips the initial `1000/100/100` HP/ATK/DEF writes when the factor is nonzero, preserving the hero's exact ending stats. The stronger tower is therefore a challenge using carried strength: **the hero's stats are not multiplied by 44 at the ending**. Gold and special items are cleared for entry into cycle 2. The original later-cycle flag retains gold and special items at entry into cycles 3 and later; the next floor-3 capture clears the specials again. The remake's default configuration preserves that gold distinction while clearing inventory at capture.

Backside enemy HP/ATK/DEF, potions, gems, equipment bonuses, fixed magician damage, and all altar stat gains use ×44. Monster gold, bomb gold, keys, merchant prices and altar prices do not. The old man's 3% attack/defense gift remains a percentage of current stats. Sorcerer pincer damage remains half of current HP. The floor-45 merchant's unscaled 2000 HP gift is an original bug retained by its explicit interaction data; editing that reward is a campaign variant.

Floor-3 capture has separate cycle behavior: in cycle 1, set `400/10/10` and steal Sacred gear; in backside cycles, keep HP/ATK/DEF and steal all special items and gear. Keys and gold survive capture. Conditional effects in `capture_on_floor_3` encode that difference.

Floor-50 Zeno becomes a fight in the backside tower. The second-cycle normalized row is `1000 HP / 625 ATK / 125 DEF`, becoming `44000 / 27500 / 5500` during battle. Entering the time gate in cycle 2 makes him march from `(5,4)` through `(5,5)` to `(5,6)` and force an enemy-first battle. Third and later cycles restore the full normalized row `8000 / 5000 / 1000`, becoming `352000 / 220000 / 44000`; those cycles retain ordinary contact combat at `(5,4)`. The gold reward remains 500 before Lucky Gold. Defeating him invokes the ending and another replay reset.

The original's later-cycle restoration can multiply the global row before battle applies its own multiplier, producing double scaling. The remake persists normalized overrides and scales once when resolving an encounter. Portal entry and repeatable contact preparation restore the appropriate row even after a weakened floor-49 seal or an older save. Repeated save/load does not compound those values. The floor-45 merchant still gives the original flat 2000 HP for 1000 gold in every cycle; tswKai's 88000-HP backside trade is a documented economy variant, not the bundled default.

`tools/extract_original_cycles.py` regenerates `data/original-cycle-evidence.json`: executable-emulated first/second/later initializer outputs, disassembly of the reset/capture/Zeno branches, the item gate, audio mappings, and the entire floor-10 trap queue. The probe supplies recognizable test stats and verifies carried HP, reset keys, second-cycle gold reset, later-cycle gold retention, and exactly 43 guard-motion records.

## Preserved event presentation

The event converter retains original waits, audio cues, moving tiles and materialization masks. Opcode 12 moves the existing tile from A to B and replaces A with road; `move_tile` combines that gameplay effect with an interpolated sprite movement. Opcode 9 is a temporary masked image, not a map write: atlas cells 166–182 are dither masks over a separate color image. Its following `(0,6,color_tile)` record supplies that image. The converter retains the target coordinates, mask sequence, color tile and underlying tile; drawing those mask cells as visible purple magic artwork changes the original effect. Opcode 11 scene operations become `cinematic` effects. Original waits are retained with configurable modern durations, and repeated raster instructions are compacted into presentation spans. The engine applies the deterministic result immediately for headless/MCP clients and supplies a timeline for the shared GUI.

The trap remembered as a golden skeleton is floor **10**. Its original encounter routine queues the Skeleton boss's speech, opens two temporary passages, moves the boss upward, closes four gates, and marches eight Skeleton guards into formation. The recovered queue has **43** tile movements, 176 wait records, and 48 sound records. Floor 9 contains no corresponding staged Skeleton trap in the initializer/step handlers.

The floor-3 capture builders (`mevent` at `0x46397C`, materialization helper `0x461A0C`, and `opening2` at `0x464048`) contain a cutscene. Zeno materializes at `(4,6)` using masks 166–182 over color tile 91, two tiles above the hero at `(4,8)`. After the two speeches, the original loads `title05.bmp`. Sixteen scan instructions with parameters 232–247 apply mask cells 167–182 across the screen, transitioning the title into `open1.bmp`, the dark vortex. Parameters 100–405 then reveal `open2.bmp` downward, displaying the sacred-sword incantation. Finally the prison reset at `opening31`, `0x4653B8`, steals equipment, applies the cycle-dependent stat change, moves the hero to floor 2, and starts the wake-up dialogue. These are distinct configured `title`, `scan`, and `capture` stages; they are no longer replaced by a ring around the hero. Their modern durations remain configurable. The queue contains no opcode-12 guard movements.

Opcode 11/subcode 4 on floor 20 is the Vampire's 32-frame transformation, not an ordinary redraw. The event retains the original nine body cells and delays their replacement until the transformation span ends. Floor 49's subcodes 2 and 3 place Zeno and the surrounding Sorcerers and call materialization helpers; those masks are now retained too. Opcode 13 tile replacement calls `0x4660D0`, which queues sixteen blend steps. The converter represents this as a `tile_reveal` span followed by the final tile write. Subcodes 13, 14 and 15 hide controls or preserve a raster background; they are not unconditional victory or credits events, and subcode 14 is also used during capture.

`tools/audit_original_events.py` writes `data/original-event-audit.json` by probing every initialized special-road tile across all 51 floor records. All **56** such sites have a configured event. The report additionally verifies capture's title and text-scan stages, all 43 floor-10 movements, the 32 floor-20 transformation records, and the eight floor-49 materialization targets. Later scenarios cover the floor-15 thief tunnel, floor-23 closing walls, floor-25 boss, floors 30/33 traps, thirteen floor-40 forced battles and retreat, floor-43 magician trap, floor-48 gate, floor-49 seal, and the floor-24 time gate. This is evidence for these branches and presentation spans, not proof of every possible dynamic map state or a natural full-tower playthrough. Fairy score/rank tables and the exact ending raster artwork sequence remain separate fidelity work.

Stair changes use the original spiral ordering: 121 outgoing cover cells followed by 121 incoming reveal cells, with `kai.wav`. The `kaidanwork` builder at `0x442DC8` selects Timer2 intervals of 2/6/10 ms for High/Medium/Low; its interpreter processes two records per tick and coalesces paired cell records. Windows timer granularity prevents treating this nominal timing as exact elapsed time. The default shared-GUI span is a configurable 450 ms. Scripted prison capture uses a separate fade; the time gate's rapid floor progression does not play the stair sound on every intermediate floor.

Ordinary combat uses six original event records per strike, with sound at the first phase, the attack overlay at one third, and HP calculation at two thirds. Timer2 intervals are 150/250/350 ms, giving nominal strikes of 450/750/1050 ms. The campaign defaults to High's 450 ms and exposes `rules.presentation.combat_strike_ms`. Each battle presentation records a `hit_sound` cue for the GUI to play on every actual strike; the engine does not also queue a duplicate standalone battle sound. Lethal encounters truncate the turn counts at the actual killing blow.

Audio opcode 1 uses A=1 `open.wav`, 2 `get.wav`, 3 `taisen.wav`, 4 `zeno.wav`, 5 music-start, 6 music-stop, 7 `3f.wav`, 8 `20f.wav`, 9 `kai.wav`, and 10 `kai2.wav`. The last four are literal filenames selected by the dispatch at `0x452850..0x4529AF`; the first four use their dedicated Delphi media-player controls. Preserve scene audio ordering and avoid restarting overlapping copies on every wait frame.


The original ambient MIDI selection is configurable in `rules.audio.floor_music`. `soundcheck` at `0x47C8F8` selects floor 0 → `a_027xgw`, floors 1–10 → `b_067xgw`, 11–20 → `b_058xgw`, 21–30 → `b_110xgw`, 31–40 → `a_118xgw`, 41–49 → `a_019xgw`, and 50 → `b_018xgw`. Scene/boss MIDI IDs are retained separately in `rules.audio.music_cues`. `tools/extract_original_cycles.py` follows the original `soundplay` jump table at `0x47C304` and reads all 17 Delphi MIDI filename constants, preserving reproducible evidence instead of guessed floor music.
