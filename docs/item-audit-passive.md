# Installed-original audit: passive items and equipment

Audited the installed English **Tower of the Sorcerer for Windows 1.2** at
`D:\Program Files (x86)\Tower of the Sorcerer` on 2026-10-04. The installed
`TSW.exe` SHA-256 was independently checked and matches the extracted campaign:

```text
41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779
```

This audit covers Hero Orb, Cross, Dragon Slayer, Lucky Gold, the five sword
tiers and the five shield tiers. Wisdom is covered by the separate executable
evidence in [original-item-evidence.json](../data/original-item-evidence.json)
and the journal implementation. Active item routines have a separate audit.
It does not establish a natural complete playthrough or equality of every
original encounter with the remake.

## Evidence used

- The installed `TSW.txt`, `Readme.txt`, `Tsw.hlp` and the preserved extraction
  [original.json](../data/help/original.json) supply original player-facing
  descriptions. The manual is descriptive evidence, not proof of arithmetic:
  its Warp Staff description, for example, does not establish randomness.
- Disassembly was read directly from the installed PE image with Capstone.
  Addresses below are original virtual addresses at image base `0x400000`.
  Delphi form-field metadata and saved form resources were inspected for the
  save menu and encounter information controls.
- The ten equipment pickup branches and the octopus reward fragment were
  executed in isolated Unicorn memory through
  [original_event_probe.py](../tools/original_event_probe.py). Calls were
  skipped and reported. These probes establish the arithmetic and direct
  state/queue writes in those branches; they do not execute Windows controls,
  string formatting, animation or a full original battle.
- [monsters.rb](../tools/research/monsters.rb) and
  [tswRev.asm](../tools/research/tswRev.asm) are secondary reverse-engineering
  notes. Their comments helped locate routines; claims below distinguish
  those comments from bytes independently read from this installation.
- Rust behavior was checked in the shared core, item help, CLI/MCP and GUI
  save paths. Existing scenario tests support implementation behavior, rather
  than serving as independent evidence for the original game.

## Item-by-item result

| Item | Installed original | Current Rust behavior and result |
| --- | --- | --- |
| Hero Orb (`hero_orb`, tile 36) | Opens the full current-floor battle forecast interface and unlocks the manual Save menu. Neither operation consumes it. | Forecasts are available through shared observation/inspection while owned. This audit found the save requirement was authored but unenforced; it is now enforced for player MCP checkpoints, terminal saves, GUI checkpoints and portable export. Developer saves, runtime replacement and recovery autosaves remain available. |
| Cross (`cross`, tile 39) | Doubles hero attack in battles against Zombie, Zombie Knight and Vampire, while retaining the original base-attack defense gate. | Implemented for the three extracted `undead` enemy rows. Default multiplier is 2 and the base-attack guard remains enabled. Help describes both the multiplier and the guard. Passive and unconsumed. |
| Dragon Slayer (`dragon_slayer`, tile 46) | Doubles hero attack against Dragon, with the same base-attack defense gate. | Implemented on the extracted Dragon row. Default multiplier is 2, guard retained. Passive and unconsumed. |
| Lucky Gold (`lucky_gold`, tile 50) | Doubles ordinary combat reward. Destruction Ball rewards use the raw monster-table reward. Octopus parts halve raw reward before Lucky Gold. | Preview and normal/scripted battle rewards use the multiplier; bombs do not. Tile-specific reward division now reproduces octopus parts. Passive and unconsumed. |
| Iron/Silver/Knight/Holy/Sacred swords (tiles 51–55) | Add 10/20/40/50/100 ATK; update the displayed current sword tier. Existing sword bonuses are not subtracted. Backside pickup gains are ×44. | Correct additive gains and cycle scaling. Every pickup updates the dedicated `weapon` slot, including a lower tier. GUI and MCP show equipment separately from special inventory. Starting gear and save/load do not add bonuses again. |
| Iron/Silver/Knight/Holy shields (tiles 56–59) | Add 10/20/40/50 DEF; update the displayed current shield tier. Existing shield bonuses are not subtracted. Backside pickup gains are ×44. | Correct additive gains and cycle scaling. Every pickup updates the dedicated `shield` slot, including a lower tier. Slot changes never subtract old bonuses. |
| Sacred Shield (`sacred_shield`, tile 60) | Adds 100 DEF and sets a separate persistent flag protecting against adjacent magician damage and opposing sorcerers. Backside gain is ×44. | Correct additive gain and passive magic protection, tracked independently of the current displayed shield. A later lower-shield pickup changes the slot while retaining this ability. GUI shows an active-protection caption, and MCP exposes `abilities.field_magic_protection`. Help does not claim immunity to ordinary attacks. |
| Sacred Sword (`sword_5`, tile 55) | Adds 100 ATK. The sword also appears in the ending story, but the examined first-cycle ending dispatcher does not require the sword inventory slot. | Correct pickup effect. No extra Sacred Sword possession gate was added to the first-cycle ending. Its narrative role is not evidence for an additional gameplay requirement. |

The aliases `monster_book`, `orb_of_flying`, `floor_wand`, `holy_water` and
similar names accepted by the core are compatibility identifiers. They are
not evidence of additional installed-original items. The original fifteen
special items are tiles 36–50; sword and shield tiers are separate equipment.

## Hero Orb: the missing save function was a real gate

The installed text manual and floor-3 old-man dialogue explicitly connect
Hero Orb acquisition to saving. The executable independently confirms it:

1. `TTSW10.itemlive` loads `ESI = 0x4B8688` at `0x450884`.
2. `0x45092B` tests `[ESI + 0x44] == 1`, the Hero Orb slot `0x4B86CC`.
3. `0x450940..0x450946` enables the form field at `+0x338` through
   `0x410378`; `0x45094D..0x450955` disables it otherwise.
4. Original Delphi form-field metadata at file offset `0x4095F` identifies
   `+0x338` as `GameSave1`. The saved form resource around file offset
   `0x12D60A` identifies it as the Save menu, initially disabled.
5. The full forecast-panel routine separately tests `0x4B86CC == 1` at
   `0x48108A`, branching away when the orb is absent.

The original campaign already set `save_requires_hero_orb: true`, but that key
previously had no gameplay consumer. The core now exposes
`Engine::save_unlocked()` and `Engine::ensure_player_save_allowed()`.
Player-facing save commands enforce this gate before allocating or writing a
save point. A rejected player MCP save does not advance the checkpoint ID.
Custom campaigns that omit the rule, or set it to false, retain unrestricted
saving.

`save_json()` and `runtime_checkpoint_json()` intentionally remain
unconditional. The running MCP bridge must preserve an early-game session
before this item is acquired, and GUI recovery autosaves remain a modern
convenience. This does mean restarting the GUI can recover progress before
the original manual-save unlock. The original also disables manual controls
during its modal events; the remake's pending-interaction checkpoint support
is another modern interaction choice, not a claim to copy original menu
availability at every animation frame.

There is a second information-interface distinction. Original
`TTSW10.monshyouji` (`0x44B78C`) is called before the ordinary attack guard at
`0x44A566`. It writes scaled HP, ATK and DEF into the encounter panel's form
fields `+0x3D8`, `+0x3DC` and `+0x3E0` at
`0x44B9DD..0x44BA5F`, without testing the Hero Orb slot. The Hero Orb gates the
full forecast window, not every original display of raw encounter stats.
The remake now records HP, ATK and DEF on actual enemy contact, including an
attempt rejected by the base-attack guard and a fatal encounter. This persisted
`last_encounter` record is available to GUI and MCP without the Hero Orb. The GUI
labels it **Last encounter**, with the enemy's name, floor and coordinates,
separately from hover inspection. A record changes only through another real
contact and survives save/load and worker replacement. Arbitrary tile hover
still does not reveal an uncontacted enemy's stats; projected damage, reward
and survivability remain in the Hero Orb's forecast interface. Keeping the
last contact visible is a modern presentation choice that uses the same
original contact information.

## Cross and Dragon Slayer: multiplication and the original quirk

The original combat dispatch at `0x44A731` selects item-aware calculation
branches by enemy row. Direct table decoding gives:

| Enemy row | Extracted identity | Original branch |
| ---: | --- | --- |
| 12 | Zombie | `0x44A797` |
| 13 | Zombie Knight | `0x44A797` |
| 17 | Vampire | `0x44A7BE` |
| 19 | Dragon | `0x44A7E5` |

The first two branches check the Cross slot `0x4B86D8`; the Dragon branch
checks `0x4B86F4`. They select the doubled calculation at `0x4502D0` when the
corresponding item is owned. At `0x450300..0x450308`, that routine reads hero
attack, doubles it, then subtracts enemy defense. The earlier guard at
`0x44A56B..0x44A588` compares enemy defense with **base** hero attack before
the item-aware branch. An attack that only becomes positive after doubling
therefore remains blocked in this original.

[combat.rs](../crates/tos-core/src/combat.rs) and
[presentation.rs](../crates/tos-core/src/presentation.rs) use the same
applicable item multiplier. The extracted campaign assigns `undead` only to
the three listed rows, and `dragon` to Dragon. This is more precise than the
original clue's descriptive claim about weakening undead: neither monster
attack nor monster HP is actually halved. No missing activation command was
found for these passive powers.

## Equipment: independently probed gains and protection flag

The ten-way pickup jump table is at `0x445C91`. The exact branch starts and
isolated probe outputs were:

| Tier | Sword branch | Shield branch | First-cycle gain | Backside gain |
| --- | --- | --- | ---: | ---: |
| Iron | `0x445CB9` | `0x445FC1` | 10 | 440 |
| Silver | `0x445D55` | `0x44605D` | 20 | 880 |
| Knight | `0x445DF3` | `0x4460FB` | 40 | 1,760 |
| Holy | `0x445E91` | `0x446199` | 50 | 2,200 |
| Sacred | `0x445F29` | `0x446231` | 100 | 4,400 |

Each branch was probed with ATK 321, DEF 456 and sword/shield levels initially
5/5, using cycle factor 0 or 43 and stopping at `0x4462C4` before common
pickup handling. Each increased only its relevant stat by the table amount
and wrote the collected tier, even when it was below the initial tier, to
`0x4B86C4` (sword) or `0x4B86C8` (shield). The skipped calls were
`0x403710`, `0x405B6C` and `[EDI+0xC]`, the string/status formatting paths.
There was no previous-bonus subtraction in the executed branch.

Sacred Shield pickup additionally sets `0x4B872C = 1` at `0x44624A`.
Sorcerer pincer logic checks this flag at `0x44C31D`, and magician damage
branches check it at `0x44C6DB` and `0x44C865`. A lower-tier shield pickup
changes the displayed shield slot but does not clear this protection flag.
The remake retains the collected `sacred_shield` tag internally, while its
dedicated `shield` display slot changes on every pickup. That tag preserves
the appropriate protection after a later lower-tier pickup and is represented
as a known ability in the player observation. Adding an "only the current
equipped Sacred Shield protects" restriction would be incorrect.

The current slot fields are persisted separately from collected tags and from
ATK/DEF totals. Equipment no longer appears in the player-facing special-item
inventory. Legacy saves lacking the fields infer each slot from the last
retained equipment tag of its type; explicit null in a current save remains
empty. This migration changes no statistics. Old saves retained an item ID
only once, so a later recollection of an already retained tier cannot always
be placed in its true original pickup order.

The original start and cycle initializer set the displayed Sacred gear,
while setting or carrying the hero's total stats separately; starting with
Sacred gear does not mean adding another 100 to the authored initial stats.
First-cycle capture clears the Sacred gear and its protection flag.
Backside capture additionally clears special item slots, including Hero
Orb, Cross, Dragon Slayer and Lucky Gold. These branches are also recorded
in [original-cycle-evidence.json](../data/original-cycle-evidence.json) and
represented in the campaign's capture effects.

## Lucky Gold and the corrected octopus body-part reward

The ordinary combat reward calculation reads `0x4B8704`, adds one, and
multiplies the reward at `0x44AB2C..0x44AB33`. This verifies the ordinary ×2
Lucky Gold behavior directly. The Destruction Ball routine does not apply
that multiplier to its raw table reward. The Rust forecast, ordinary battle,
scripted battle and bomb paths correctly retain this distinction.

The initial synthetic reward fragment probe identified a distinction but did
not establish a full encounter. It is superseded by
[the octopus encounter audit](octopus-encounters.md), which executes the actual
dispatcher, battle builder, recursive arithmetic helpers and HP/gold/map queue
handlers. All nine cells use the full original row18 stats of 1,200 HP, 180 ATK
and 20 DEF. Tiles97–103 and105 halve the actual raw reward of100 to50 and clear
only their contacted cell. Bottom-center tile104 grants100 and clears the
entire3×3 footprint. Lucky Gold then doubles50/100 to100/200. Six probes with
an edited odd reward of101 additionally establish floor division before the
Lucky Gold multiplier. Backside scaling multiplies combat stats by44 without
changing gold.

The Rust campaign now configures the eight parts with `reward_divisor: 2`
and no footprint; only104 owns the unconditional footprint clear. Shared
tile forecasts and execution apply the same divisor before Lucky Gold. No
shared octopus HP pool is introduced: after a part is removed, a remaining
part or the whole body still starts a full-stat fight. The reproducible
report in [original-octopus-evidence.json](../data/original-octopus-evidence.json)
lists all bypassed GUI/string paths; it is not a live Windows playthrough.

## Help changes and validation

Owned-item help already accurately identifies Cross, Dragon Slayer, Lucky
Gold and equipment as automatic/unconsumed, reports the attack-defense
guard and distinguishes bomb rewards. Hero Orb help now includes its
manual-save capability. The paired static handbook was updated to describe
Hero saving and Wisdom's 24 first-heard-while-owned clues without adding
acquisition or puzzle spoilers; [original-help.md](original-help.md) records
the adaptation boundary.

Validation completed for these changes:

- Both new `save_gates` core tests passed: actual original Hero gift unlock,
  loss of the item locks saving, custom-rule opt-out and private runtime
  replacement before the Hero Orb.
- All four CLI/MCP unit tests passed, including an initially rejected player
  checkpoint with unchanged state and checkpoint IDs, followed by a valid
  checkpoint after Hero Orb ownership.
- Both static handbook pages regenerated, and
  `python tools/build_help.py --check` passed.
- All eight `equipment_slots` tests passed: authored starting gear without
  bonus duplication, lower-tier display changes with additive gains, persistent
  Sacred protection, explicit empty slots across saves, legacy inference,
  atomic invalid-import rejection, cycle initialization and original capture
  in both cycles, and custom equipment outside weapon/shield slots retained
  in visible inventory.
- The UI library's 23 tests passed, including dedicated equipment following
  the visible animation state and contact information separated from hovered
  enemies, with English/Chinese label coverage.

GUI build and integrated reload checks are part of the containing change's
validation. The evidence here is not a claim to have driven the installed
Windows game or completed either game's full tower.
