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

Orb of Flight is reusable, restricted to an adjacent stair, and restricted to floors already visited. The landing position follows stair-arrival metadata, not a generic nearest-walkable-tile search.

## Magic hazards

An adjacent Magician A deals 200 HP and an adjacent Magician B deals 100 HP. Contributions from multiple orthogonal neighbors add. Being between two opposing Sorcerers removes half the current HP, rounded upward. Sacred Shield protects against these magical hazards. Hazard calculations need to happen on the actual committed step; rejected movement must not inflict damage.

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

The campaign begins at 1000 HP, 100 ATK, and 100 DEF with the Sacred Sword and Sacred Shield. First-cycle capture on floor 3 changes HP/ATK/DEF to 400/10/10 and removes that equipment; backside capture preserves those stats and clears all special inventory. It does not reset keys or gold in the examined original routine. Orb of the Hero is obtained from the floor-3 old man, Orb of Flight from the floor-1 pickup, and Orb of Wisdom from floor 6.

## Special items verified directly in the executable

The original holds three orbs and twelve further special items. Item slots at `0x4B86C4` are Sword, Shield, Hero Orb, Wisdom Orb, Flight Orb, Cross, Elixir, Mattock, Destruction Ball, Warp Staff, Ascent Wing, Descent Wing, Dragon Slayer, Snow Crystal, Magic Key, Super Mattock, and Lucky Gold.

| Item | Original effect | Direct evidence |
|---|---|---|
| Elixir | Add `10*ATK + 5*DEF` HP and consume item. | `0x450D13` to `0x450D96` |
| Magic Mattock | Remove the four neighboring ordinary walls; consume item. | `0x450DA7` to `0x450F27` |
| Destruction Ball | Destroy eligible adjacent enemies, award the raw monster-table gold, consume item. | `0x450F31` to `0x451127` |
| Warp Staff | Mirror coordinates to `(10-x, 10-y)` on the same floor; destination must be ordinary road. A charge is consumed before the destination check. | `0x4511B3` to `0x4513DF` |
| Ascent Wing | Move one floor upward at the same coordinates if the destination is ordinary road; consume only on success. | `0x4513E4` to `0x45153E` |
| Descent Wing | Move one floor downward at the same coordinates if the destination is ordinary road; consume only on success. Floor 0 is reachable from floor 1. | `0x451543` to `0x4516A6` |
| Snow Crystal | Cool neighboring lava regions into road. Remains available after use. | `0x4516AB` to `0x4518E1` |
| Magic Key | Open every yellow door on the current floor; consume item. Blue, red, and gate tiles are excluded. | `0x4518E6` to `0x4519F6` |
| Super Mattock | Remove all ordinary walls on the current floor; consume item. | `0x4519FB` to `0x451B42` |

The bomb classifier at `0x451C20` accepts monster tile ranges `61..90`, `93..96`, `133..144`, and `147..158`. It excludes Dragon, Giant Octopus, Zeno, and Great Magic Master. It does not apply Lucky Gold to the bomb reward in the examined routine. Preserve that distinction from normal combat. Large creatures need their occupied tiles cleared together by their dedicated encounter logic.

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

`data/events.json` currently contains 100 original-derived campaign events. Their coverage includes capture and prison escape; guarded doors and rewards; the floor-10 Skeleton staging; the floor-15 thief's Octopus bypass; Vampire and Great Magic Master encounters; the floor-23 closing-wall puzzle; the floor-30 and floor-33 traps; all thirteen forced floor-40 wave fights and the Golden Knight's retreat; the floor-39 clock-door puzzle; concealed floor-12, floor-16, floor-19, and floor-41 discoveries; the floor-43 magician trap; the floor-48 caster gate; the floor-49 dice seal, decoy, and rewards; and the princess doll/time-gate ending.

The floor-49 seal leaves the four corner Sorcerers alive, removes the four edge Sorcerers, and retains Zeno in the center. Direct execution then mutates Zeno's HP/ATK/DEF from 8000/5000/1000 to 800/500/100. This is represented by a persisted enemy override rather than a second hard-coded monster.

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

Floor-50 Zeno becomes a normal fight in the backside tower. At `0x4463B3`, the second-cycle branch sets the normalized enemy row to `1000 HP / 625 ATK / 125 DEF`, which becomes `44000 / 27500 / 5500` during battle; the gold reward remains 500. Defeating him invokes the ending and another replay reset. The original's later-cycle row restoration can apply the multiplier twice, a bug independently documented by [tswKai's author](https://github.com/Z-H-Sun/tswKai/blob/main/strings.rb). The configurable remake keeps the normalized row stable for all backside cycles instead of reproducing that double-scaling bug.

`tools/extract_original_cycles.py` regenerates `data/original-cycle-evidence.json`: executable-emulated first/second/later initializer outputs, disassembly of the reset/capture/Zeno branches, the item gate, audio mappings, and the entire floor-10 trap queue. The probe supplies recognizable test stats and verifies carried HP, reset keys, second-cycle gold reset, later-cycle gold retention, and exactly 43 guard-motion records.

## Preserved event presentation

The event converter now retains original waits, audio cues, and moving tiles. Opcode 12 moves the existing tile from A to B and replaces A with road; `move_tile` combines that gameplay effect with an interpolated sprite movement. Opcode 9 is a temporary magic overlay, not a map write. Opcode 11 title, fade, capture and ending operations become `cinematic` effects. Original waits are retained with configurable modern durations, and repeated raster fade instructions are compacted into a single presentation span. The engine applies the deterministic result immediately for headless/MCP clients and supplies a timeline for the shared GUI.

The trap remembered as a golden skeleton is floor **10**. Its original encounter routine queues the Skeleton boss's speech, opens two temporary passages, moves the boss upward, closes four gates, and marches eight Skeleton guards into formation. The recovered queue has **43** tile movements, 176 wait records, and 48 sound records. Floor 9 contains no corresponding staged Skeleton trap in the initializer/step handlers.

The floor-3 capture builders (`mevent` at `0x46397C`, magic helper `0x461A0C`, and `opening2` at `0x464048`) emit magic overlays, speech and fade/capture operations. They do not contain opcode-12 guard movements. The remake retains that scene order and uses original overlay sprite cells 166–182 with modern rings/fades; it does not claim exact original raster effects. Dialogue reveal, battle flashes, walking interpolation and floor transitions likewise use modern configurable timing.

Audio opcode 1 uses A=1 `open.wav`, 2 `get.wav`, 3 `taisen.wav`, 4 `zeno.wav`, 5 music-start, 6 music-stop, 7 `3f.wav`, 8 `20f.wav`, 9 `kai.wav`, and 10 `kai2.wav`. The last four are literal filenames selected by the dispatch at `0x452850..0x4529AF`; the first four use their dedicated Delphi media-player controls. Preserve scene audio ordering and avoid restarting overlapping copies on every wait frame.


The original ambient MIDI selection is configurable in `rules.audio.floor_music`. `soundcheck` at `0x47C8F8` selects floor 0 → `a_027xgw`, floors 1–10 → `b_067xgw`, 11–20 → `b_058xgw`, 21–30 → `b_110xgw`, 31–40 → `a_118xgw`, 41–49 → `a_019xgw`, and 50 → `b_018xgw`. Scene/boss MIDI IDs are retained separately in `rules.audio.music_cues`. `tools/extract_original_cycles.py` follows the original `soundplay` jump table at `0x47C304` and reads all 17 Delphi MIDI filename constants, preserving reproducible evidence instead of guessed floor music.
