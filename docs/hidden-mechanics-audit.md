# Original Windows hidden mechanics and dialogue callbacks

This audit compares the original 50-floor Windows game with the claims in
[Moegirl's 魔塔 article](https://zh.moegirl.org.cn/%E9%AD%94%E5%A1%94), viewed at
revision date 2026-09-11 01:32. It excludes other towers, H5 changes and Flash
adaptations. The article mixes PC-98, Windows and Flash behavior; it supplies
investigation questions rather than expected test results.

The reference is the installed English `TSW.exe` v1.2, SHA-256
`41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779`.
It is read without launching or patching the original process. The existing
[tswKai comparison](tswkai-audit.md) pins the cloned upstream and wiki commits
and separately assesses their corrections.

## Additional omissions repaired

| Mechanic | Executable evidence | Result in the remake |
| --- | --- | --- |
| Initial 2F prison Thief | `touzoku` at `0x465900` queues dialogue 4 (zero-based 3) and wall-opening record `(13,67,7)`. Continue stage 14 at `0x44DCAC` moves him through indices `68→67→66→77`. | Actual first speech, wall collapse and three movements to `(0,7)`; the second conversation is available there. |
| 2F departure | The second speech combines strings 4 and 57. Continue stage 15 at `0x44DDF4` queues `77→88→99`, then clears 99. | Actual second speech, two further movements and departure. Pending conversations survive save/load. |
| Returned 2F Thief opens Dragon bypass | The speech handler selects strings 5/6 using `0x4B8808`. Continue stage 16 at `0x44DF94` writes 35F `(3,8)=6`, `(4,9)=21`, and sets the flag. | Continuing the first speech opens the tunnel and places the 35F Thief once. Repeat speech is remembered. |
| 29F tunnel speeches | Initial `(5,3)` has string 26. Stair/Flight descent relocates the Thief to `(6,1)`; strings 27/28 use `0x4B8860`, set by Continue stage 38. | All three speeches restored. Completion does not depend on 23F walls. |
| 35F first/repeat speech | Strings 31/32 use `0x4B8870`, set by Continue stage 42. The speech handler clears the returned 2F Thief; the 42F arrival builder later clears the 35F Thief. | Both speeches, remembered repeat state and both removals restored. |
| Precleared 40F troops | `ichicheck` at `0x46CB1C` recreates each of twelve troops when its original cell is road 6. Untouched maps write none; precleared maps restore the troops and retain the same thirteen forced battles. | Conditional restoration precedes the march. Preclearing one or all twelve troops still incurs all thirteen enemy-first fights and rewards. The Knight is not recreated by these writes. |
| Princess before/after 25F boss | `handan` at `0x445397` always queues strings **24 then 25** and places Thief tile 21 at 50F `(5,4)`. Only the six 24F corridor/portal writes depend on the 25F center being road. | Actual speech order; revisiting after boss victory opens the gate. Eligibility applies only to the gate writes. |
| 50F Thief's location and reachability | Princess writes index 49, not 92. `touzoku` queues one-based 264, zero-based 263, without world/stat changes. The time gate transforms that same tile into Zeno. | Thief at `(5,4)`, reachable with Ascent Wing before taking the gate. Invented border NPC `(4,8)` removed. Known old GUI saves repair placement without replacing existing Zeno. |

The previous greeting fix verified the speech handler but inferred the NPC
coordinate from the authored event. The new regression creates him through
the doll, uses Ascent Wing from 49F, opens the real conversation, restores a
pending save and verifies that Continue preserves the world and player.

## Mechanics cross-check

| Original Windows mechanic | Evidence and implementation status |
| --- | --- |
| Nine Octopus victories on 15F | Eight individual parts have full stats and 50 gold each; the bottom-center mouth has 100 gold and clears the creature. Parts first, mouth last yield 500 raw gold, or 1000 with Lucky Gold. Existing executable/engine evidence and the new nine-victory regression agree. |
| Octopus retreat gate | Approach queues gate-close mode 5 at `(5,8)`. The engine closes it, then reopens it and creates the Mattock after mouth victory. |
| Solid Dragon body on 35F | Tiles 115–123 form the body; only 122 is attackable. Other occupied cells block walking and Mattock removal. Snow Crystal is absent initially and appears after victory. Existing real-map regression verifies this. |
| Four hidden passages on 36F | Twenty tile-9 cells form four five-cell passages. The new regression walks all twenty and checks saved discovery. |
| Sacred Sword gate on 48F | Special road `(0,0)` creates Sorcerer 93. His death queues gate-opening mode 4 at `(7,7)`. Real-map regression verifies both phases. |
| Red resources on 25F/26F | Boss victory creates five red-key tiles 30; 26F has four red doors, tile 3. Regression defeats the boss, collects five keys and opens four doors, leaving one. |
| Medium Gate-Keeper gold | Original table reward is 100, preserved in imported enemy data. The Flash value 50 is not used. |
| Knight challenge on 32F | Upward stair callback, rather than initialized special road. Restored in the preceding commit: approach, speech, first strike, retreat and Thief returned to 2F. |
| Knight on 40F/42F | Thirteen 40F forced battles and retreat; once-only upward 42F arrival materializes Zeno/four guards, executes the Knight, speaks and departs. Covered by progression and GUI scenarios. |
| Magician A on 47F | Ordinary walking calls `mazyutu1`, `0x44C5C4`. Damage precedes retreat. Sacred Shield prevents damage **but preserves retreat**. Corrected x/y bounds prevent historical row wrapping. |
| Magic Sergeant pincer / 49F seal | Opposing cardinal Sorcerers leave `floor(HP/2)`: `1001→500`, `1→0`. Enemy-cell entry incurs a pincer on each of the four edge kills without Sacred Shield. New real-map scenarios check four halvings and protection after a lower shield replaces the displayed shield. |
| Dice seal and Dragon Slayer | The edge/corner sums trigger signed division of the **current shared** Zeno HP/ATK/DEF by ten, once per active seal flag, without requiring center Zeno. The time gate clears that flag and multiplies the row back. Gate → seal → wing return retains the weaker later-cycle 50F row; cycle 2 assigns fixed stats. Seventy-two chained EXE cases and real wing routes cover ordering, truncation and saves. Delayed decoy victory re-seals before its loot clears the corners, replacing the seal speech queue. The same `PostCombat` stage now preserves that ordering and grants Dragon Slayer. |
| Warp Staff / clock puzzle | Three charges, center reflection, no HP payment. The 39F puzzle grants Staff tile 43. Its callback runs even on zero-key refusal: one hand opened with the last key, then contact with the other, reveals the Staff without opening that second door. Both hand orders and save/restore are covered. |
| 43F no-key door callback | `doorcheck` changes index 7 to special road while index 8 is guardian tile 93, including on a refused opening. The hero remains outside; the next step activates the magician trap. Newly translated as a typed door-attempt event. |
| Snow Crystal | Reusable on adjacent lava in 13F and 26F, matching the Windows-specific article section. Its later single-use assertion does not match this executable. |
| Elixir | Executable formula is **10×ATK + 5×DEF**; consume item and add that HP. The article reverses the coefficients. Existing probes and tests use the executable formula. |
| Cross / Dragon Slayer / Lucky Gold | Cross doubles hero attack against Zombie, Zombie Knight and Vampire; Slayer doubles it against Dragon. Lucky Gold doubles normal/forced battle rewards, but not Bomb rewards. Covered. |
| Bomb boss immunity and callback order | Classifier `0x451C20` rejects Zeno, Octopus, Dragon and Great Magic Master; it accepts Vampire and Golden Knight. Eligibility follows tile families, rather than a general boss label. A full use clears the four eligible cardinal neighbors, awards raw gold, consumes the Bomb, then calls `moncheck` once even with zero victims. Execution dissolves north/west/east/south. The door/Bomb audit covers all 256 tile inputs and all 121 hero positions. The article's unrestricted Bomb/final-Zeno claim does not match this image. |
| First-cycle 50F ending | Contact queues ending/reset without ordinary combat. Already reproduced. |
| Later-cycle 50F defeat | Followed original normal-combat arithmetic yields death at HP 1000 and postcombat at HP 500000 with ATK 10000/DEF 5000. Universal automatic advancement after a loss is unsupported. The separate scripted second-cycle first-strike arithmetic is outside this probe; do not generalize to that path. |
| Replay items and gold | `syokidata1`, `0x455CB8`, clears items/gold for cycle 2 but preserves them at **cycle 3 and later** reset. Capture subsequently strips items again. Existing Rust behavior agrees; the article's cycle-4 threshold does not. |
| Fairy score/checkpoints | Modern acknowledgement and general saving are implemented. Original score/rank tables and automatic Fairy checkpoint behavior remain unfinished. |

## Why these were missed

The initial audit used special-road coverage as the main event inventory.
All 56 initialized sites were accounted for, but incoming callbacks through
stairs, ordinary walking, dynamic NPCs, Continue, Flight and reset were not
all accounted for. The 47F retreat and 32F/42F arrivals exposed that boundary.

NPC import also assumed events supplied every speech. Correct IDs survived
with generic text, even where no matching speech event existed. This lost
the 50F greeting and several Thief branches. Continue uses a different
routine from the speech builder, losing the Dragon tunnel and prison
departure. The 40F restoration requires an already changed map, so probing
the untouched initializer cannot observe it. Direct write tracking helps,
but cannot replace altered-state branch probes.

The next audit exposed two further assumptions: successful movement had been
treated as the only door callback, losing the 39F shortcut and 43F refused-door
branch; the seal had been translated as a fixed row and the later-cycle boss
contact as a reset, losing shared-state ordering. Bomb also ran floor-wide
checks per victim, although the EXE defers one check until all dissolves finish.
Typed `door_attempted`, `post_combat` and `multiply_enemy` operations now express
these distinctions in campaign data. The original door, Bomb and Zeno routines
have [readable source and a broader decompiler index](../reference/original/README.md).
Exported branches still need review and state-sensitive probes; a source export
alone does not certify every interaction.

The probe now records direct writes, skipped/followed calls and verified
Delphi stack cleanup, and rejects instruction-budget exhaustion. The new
audit scans Continue stages 10–278 in default state: map/queue operations
occur at 14/15/16, and heard-dialogue flags at 11–67. It separately checks
the relevant Thief stages on their actual floors. This is a bounded scan,
not proof of every flag combination.

## Readable reconstruction and runtime boundaries

The [source reference](../reference/original/README.md) now includes cleaned
door/Bomb/Zeno routines and a broader C-like export of the dispatcher, queue
interpreter and callbacks, with a direct-call inventory. Language translation
alone cannot establish coverage. The useful unit is an address-annotated
handler with callers, read/write sets, branch predicates and differential
executable scenarios. Earlier missed operations reduce to the following
reference behavior:

```cpp
// Continue state 16, 0x44DF94, separate from the speech builder.
floor[35][8 * 11 + 3] = ROAD;
floor[35][9 * 11 + 4] = THIEF;
thief_tunnel_started = true; // 0x4B8808

// Each of twelve 40F troop starting cells, before the march.
if (floor[40][troop.cell] == ROAD)
    floor[40][troop.cell] = troop.original_tile;
```

Retain the Rust runtime. `events.rs` and `content.rs` compile campaign
behavior into validated triggers, conditions, effects and typed tiles/rules.
String keys at JSON/save/API/editor boundaries and content IDs are
appropriate; gameplay should use compiled behavior instead of ad hoc JSON
lookups. Research scripts translate address/tile data at the import boundary.
Tests use mechanic names (`hidden_mechanics`, `progression`, tile transitions),
not an undefined category of animation "gaps".

A completeness claim needs a handler/branch inventory across movement,
stairs, NPC speech **and Continue**, merchants, items, postcombat, Flight
and reset, including precleared maps and prior flags. A natural full first
cycle and replay route remain separate integration evidence. This audit
does not claim that all things are now considered.

## Reproduction and limits

```text
python tools/extract_original_events.py
python tools/audit_original_hidden_mechanics.py
python tools/audit_original_events.py
python tools/audit_original_mechanics.py
python tools/audit_original_door_bomb.py
python tools/audit_original_zeno.py
npm run check
npm run test:animations
```

Campaign integration imports regenerated events and interactions; see
[original-data.md](original-data.md) before regenerating authored fields.
Evidence is in `data/original-hidden-mechanics-audit.json`. Rust scenarios
are in `hidden_mechanics.rs`, `original_campaign.rs`, `progression.rs`,
`octopus.rs`, `active_items.rs`, `backside.rs` and GUI migration tests.
GUI/audio calls are skipped by isolated probes; cleanup preserves the ABI
of followed arithmetic helpers. Original Delphi drawing/timers, ending
raster artwork, Fairy scoring/checkpoints, full reachable-state coverage
and an unassisted complete route remain fidelity limits.
