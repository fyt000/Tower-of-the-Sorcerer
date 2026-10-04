# Original item audit

This audit reads the installed English **Tower of the Sorcerer for Windows
v1.2** at `D:\Program Files (x86)\Tower of the Sorcerer`. The installation is
read-only. Its executable SHA-256 is
`41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779`.

Evidence includes the installed `TSW.txt`, the extracted WinHelp topics in
`data/help/original.json`, the imported dialogue and campaign data, existing
reverse-engineering notes under `tools/research`, and direct executable
disassembly and isolated Unicorn probes. `tools/audit_original_items.py`
reproduces the Wisdom gate/recording/reset checks and writes
`data/original-item-evidence.json`. Probe helper calls are skipped and reported;
these probes establish direct branches, memory writes, and control enable
requests, not Windows rendering or a complete original-game playthrough.

## Orb of Wisdom

The previous Rust implementation granted the `wisdom_orb` inventory tag but
treated it as an always-active item. The existing Journal panel displayed the
last 100 action messages. It did **not** implement the original hint memory.
The first proposed durable journal also needed correction: recording every
conversation and cinematic regardless of item ownership is broader than the
original item.

The original has 24 hint buttons, corresponding to dialogue IDs **62 through
85**. It records first hearing in dedicated old-man and merchant state slots.
`0x449CAD..0x449CDD` and `0x449654..0x449684` write **1** without Wisdom or
**2** with Wisdom. Previously handled speech follows another branch. The item
pickup at `0x445A80` sets the ownership slot, without upgrading old hint states.
The menu at `0x48198C..0x481E7D` requires ownership and enables each hint only
when its state is **2**. Replay selects the original clue string through
`0x44A1DA..0x44A219`.

Consequently:

- Only designated old-man clues and merchant information can enter the
  original Wisdom memory. A merchant's unpaid offer is not its later clue.
- A hint first heard before obtaining Wisdom is not recovered automatically
  afterward. An agent may still remember the original conversation itself.
- Repeated hearings do not create duplicate entries. Buttons use fixed clue
  order, rather than chronological order.
- Wisdom is reusable and must be activated to open its original menu.
- The clue slots are inside the original saved state block. The initializer
  clears all 24 slots on a new cycle, including later cycles. Losing ownership
  hides the menu; ownership and remembered clues are separate state.

The shared Rust engine now models this first-hearing distinction, persists
recorded clues, orders original entries by clue ID, gates public access on
ownership, and clears the memory on a tower-cycle reset. `use_item` with
`wisdom_orb` emits a journal presentation. GUI and player MCP read the same
public records. Private dialogue IDs remain in saves, while player records
contain only encountered title, text, floor, position, and cycle.

The dedicated Journal panel shows a compact preview of the three latest
actions. Open log (also available from the header's book button) opens a
scrollable modal containing all retained activity entries, up to 100. Its
heading and Close control remain outside the scrolling content. While Wisdom
is owned, a Wisdom hints shortcut activates the same item action as clicking
the orb in inventory. Hint text remains in that separate item review. This
is a presentation convenience; it does not grant additional hints. Custom
campaigns without `wisdom_dialogue_range` record
their NPC speech while Wisdom is owned, using first hearing by location/text.
They do not automatically record arbitrary cinematics or event messages.

## Item coverage and corrections

All 15 original special-item identities have Rust behavior. Having a dispatch
branch did not guarantee original fidelity; the following comparisons found
several concrete differences. The detailed active/passive evidence is in
[item-audit-active.md](item-audit-active.md) and
[item-audit-passive.md](item-audit-passive.md).

| Item | Audited behavior and resulting implementation |
| --- | --- |
| Hero Orb | Forecast menu requires ownership (`0x48108A`). Original manual-save menu also requires it (`0x45092B..0x450962`). The declared Rust save rule was previously unenforced; GUI manual checkpoints/exports, terminal saves, and player MCP checkpoints now enforce it. |
| Wisdom Orb | Original first-heard hint memory was missing. Implemented as described above. |
| Flight Orb | Original floor selector spans 1 through the highest stair floor and skips 44; it cannot select 0. Selecting the current floor without changing the selector leaves position unchanged. The original campaign now tracks this separate counter, including capture/reset, instead of allowing arbitrary visited floors. Changed direct destinations also execute the guarded selector world updates through authored callbacks. |
| Cross | Passive attack multiplier for the original undead families; base attack must still exceed enemy defense. Configurable multiplier remains shared by real combat and forecasts. |
| Dragon Slayer | Passive attack multiplier for dragons, with the same base-attack guard. |
| Lucky Gold | Passive doubled normal combat gold. Bomb rewards use raw monster-table gold, without the multiplier. |
| Elixir | Adds `10 × ATK + 5 × DEF` HP and consumes the item. Already matched the original. |
| Magic Mattock | Breaks ordinary brick in four cardinal directions. Corrected the original classification to tile 8, excluding scripted/decorative/hidden walls. Empty use still consumes the item. |
| Destruction Ball | Destroys susceptible enemies only in four cardinal directions, with raw gold rewards. Corrected the prior 3×3 radius. Empty use still consumes the item. |
| Warp Staff | Mirrors coordinates through the floor center. Requires ordinary road; a charge is spent before checking whether landing is blocked. Three charges by default. Already matched the original. |
| Ascent / Descent Wings | Move one floor at the same coordinates; ordinary road required. Consume only on success. Descent can reach floor 0. Already matched the original. |
| Snow Crystal | Cools only immediately adjacent lava in four cardinal directions and remains reusable. Corrected the prior connected-region flood fill. |
| Magic Key | Opens all yellow doors on the floor. Empty use still consumes the item; corrected the previous no-op retention. |
| Super Mattock | Removes all ordinary brick on the floor. Uses the same corrected wall classification and consumes even when no wall can be removed. |
| Swords / shields | All five tiers apply the original additive stat gains, scaled in backside cycles. Every pickup updates the dedicated current weapon or shield slot, including a lower tier. Sacred Shield's field-magic protection remains a separate persistent collected ability. GUI and MCP show equipment separately from special-item inventory. |

Owned-item help now describes activation, permitted targets, restrictions,
consumption, and charges. It is shared by GUI tooltips and MCP inventory
observations. It contains neither acquisition locations nor puzzle solutions.

## Deliberate adaptations and limits

Autosave remains a remake convenience available from the start. It is distinct
from the Hero Orb-gated manual checkpoint/export action. Internal `save_json`
and worker runtime checkpoints remain unconditional so process replacement can
preserve the session before the player earns the item. Developer-profile save
export remains diagnostic access.

The remake activates consumable items directly instead of reproducing the
original use/cancel confirmation window. Tool help makes the original empty-use
consumption explicit. Flight's highest stair floor is saved separately;
ascending with a Wing does not silently unlock that destination for Flight.
Legacy saves have no such counter, so their fallback derives it from prior
visited floors as a compatibility approximation. Historical Wing versus stair
travel cannot be reconstructed exactly from those saves.

The original displays raw enemy HP/ATK/DEF on actual enemy contact before the
Hero Orb; its full forecast menu is item-gated. The Rust engine now records
that actual contact, including a blocked or fatal attack, and preserves it
across save/load and MCP worker replacement. GUI presents a separate **Last
encounter** panel, and MCP exposes the same contacted stats. Arbitrary hover
inspection still requires the Hero Orb for forecasts. The persistent panel is
a modern presentation convenience using the original contact information;
it does not reveal uncontacted enemies or add reward/damage predictions.

Current weapon and shield slots are saved independently from accumulated
ATK/DEF and collected tags. A lower-tier pickup changes its slot while adding
its stat gain; starting gear and restoration do not reapply bonuses. Capture
clears both slots, and cycle initialization restores the authored starting
gear. Sacred Shield's protection survives a later lower-shield pickup,
represented by the GUI's active-protection caption and MCP's known ability
field. Legacy saves lacking current-slot fields infer each slot from the last
retained equipment tag, without changing stats. Their exact most-recent tier
cannot always be recovered after recollection because old saves did not keep
that pickup order.

Flight's direct destination command now models the shortest monotonic sequence
of original Up/Down selections followed by OK, including the verified guarded
world updates in those controls. These callbacks use validated authored data;
custom campaigns are not coupled to original floor coordinates. The matching
normal stair descent relocation is also implemented. A same-floor command
corresponds to OK without arrows and preserves position and those updates.
The original supports selector roundtrips with a last-arrow state, which this
direct interface does not expose. The larger F29/F35 thief dialogue and digging
storyline, and original fairy score/checkpoint files, remain separate gaps. See
[the focused Flight audit](flight-context-audit.md) for exact instructions and
the executable probes.
[The octopus encounter audit](octopus-encounters.md) now resolves the prior
body-part concern: eight parts use full combat stats but half raw gold and
single-cell removal; bottom-center104 uses full gold and clears the whole
creature. Per-tile configuration, forecasts and actual battles implement the
same behavior, including Lucky Gold, backside scaling and integer rounding.
The original Hero Orb list selects only the bottom-center tile104 and displays
name, HP/ATK/DEF and expected damage; it has no gold reward column or separate
part entries. The focused forecast replay linked in that audit confirms this
from the installed scanner, row builder and original form labels. The remake's
per-cell gold forecasts are a richer interface, as is the external tswKai3
enhancement's detailed hover/status-bar display.

Scenario tests and executable probes validate the listed item rules. They do
not establish a fresh, unassisted, complete campaign playthrough or certify
that every original UI/timing quirk has been reproduced. Route optimization is
deferred; no solver or new wall-probing penalty is introduced by this work.
