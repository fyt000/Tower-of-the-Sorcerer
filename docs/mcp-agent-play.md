# MCP observations and agent playthrough audit

The engine can already execute every ordinary player input needed for a
playthrough: four-direction movement, conversation/shop choice, cancellation,
item use and reset. The main gap was the information boundary. The old MCP
surface exposed authoring data that solved discoveries before the agent played.
The new player observation deliberately describes what a player can see, while
the diagnostic snapshot remains available to the renderer, editor and developer
profile.

This audit inspected the Rust engine, imported campaign and progression tests.
It does **not** establish that a fresh agent can finish the complete tower.
The existing late-game tests deliberately place or strengthen the hero using
edited saves; their comments explicitly distinguish those scenarios from an
unassisted complete run (`original_campaign.rs:1–3`, `progression.rs:1–4`).

## Findings and changes

| Finding | Evidence in the previous surface | Player-facing treatment |
| --- | --- | --- |
| Hidden and scripted walls were distinguishable without touching them. | `Engine::snapshot`, `lib.rs:138`, serialized raw board IDs and every tile definition. Campaign IDs 9 and 10 were named `Secret wall` and `Scripted wall` (`campaign.json:7105`, `7115`). `Engine::inspect`, `lib.rs:153–166`, concealed a hidden wall's name/kind but retained its ID. | `player_observation` and `inspect_player_tile` normalize original brick IDs 8/9/10 to the same ordinary wall ID, name and sprite. Custom hidden walls use the corresponding ordinary wall appearance. Discovery still requires a real bump. |
| Scripted roads were labeled as triggers. | Complete `tile_defs` disclosed the `trigger` kind and source tile IDs, including future/unseen definitions. | Road triggers use their ordinary floor appearance. Only definitions used by the observed board are returned. |
| Campaign resources supplied puzzle solutions directly. | The previous `tos://campaign` resource serialized all floors, enemies, events, conditions, effects and location-specific conversations. | The default player profile excludes the raw campaign resource; the explicit developer profile is for inspecting those internals. |
| Portable saves supplied unseen floor maps and internal progress. | `Save`, `persistence.rs:19–37`, contains every floor, flags, event/shop counters and enemy overrides; `save_game` exported the JSON. | Default player checkpoints must remain server-side and be referenced by opaque IDs. Raw import/export belongs to developer workflows. |
| Editable saves allowed artificial progress. | `load_json` validates campaign identity, shape and numeric bounds, not whether a state is reachable through gameplay (`persistence.rs:51–119`). Tests intentionally use this to isolate scenarios. | A checkpoint restore in player mode restores a server-created state; accepting arbitrary edited JSON would bypass the playthrough. |
| Internal flags and presentation payloads disclosed bookkeeping. | Snapshot flags and extensible cinematic fields exposed identifiers, source metadata, raw tile IDs and offscreen map edits. | The player projection uses explicit field allowlists, strips flags/dialogue IDs/arbitrary cinematic metadata, normalizes visible tile changes and omits offscreen changes. Authored speech and inscriptions remain readable. |
| Clone simulation allowed cost-free probing of unknown events. | `simulate_actions` cloned the full hidden state and returned the actual consequences of up to 1000 proposed actions. A hidden-wall search could be performed without any committed exploration. | Simulation belongs to the explicit developer profile. A player can use real actions and checkpoints, under the same knowledge boundary as a human player. |

The shared forecast-menu gate already behaved correctly: `forecasts_unlocked`
(`lib.rs:274–283`) checks the Hero Orb, and both snapshot monster forecasts and
tile inspection respect it. The new projection retains that gate. It also
removes unearned numerical monster details from battle animation payloads.
Damage actually suffered remains visible through the resulting hero statistics
and battle log. The later original-item audit found an original raw-stat
encounter panel available before Hero. The engine now records those HP/ATK/DEF
values on actual contact, including a blocked or fatal encounter, and exposes
them in `last_encounter` independently of the gated full forecast menu.

## What an agent can learn without an answer key

The whole current floor is visible in the graphical game, so showing that same
board is appropriate; walls do not create a fog-of-war rule. The observation
states the zero-based, top-left coordinate convention and row-major indexing.
It provides current stats, keys, held items/charges, visible pickups and their
current gains, visited floors, current dialogue choices, costs/affordability,
unlocked combat forecasts and the committed action result.

The campaign already contains useful authored hints. For example, an old man
talks about four tunnels (`campaign.json:19437`), another describes a time on a
clock (`19563`), and later dialogue discusses an inaccessible floor (`19640`)
and symmetry (`19654`). The player API should deliver these words only when
the conversation or paid message is actually encountered. It should not
translate the clue into coordinates, event conditions, a matching wall label,
an automatic secret detector or a recommended puzzle action.

A hidden wall can be found by combining an encountered hint with the visible
geometry, choosing a candidate and moving into it. `move_player` runs bump
events before collision handling (`navigation.rs:92`), and a hidden wall becomes
road when touched (`116–118`). The revealed board and discovery message are
legitimate evidence. An ordinary wall returns a blocked result and does not
move the hero. The existing route planner permits an obstacle as the final
action, so it can guide the agent to an attempted wall without classifying the
wall as secret (`navigation.rs:11–79`).

This information boundary preserves the *opportunity* to solve riddles. It
cannot guarantee that an agent will infer the intended solution instead of
trying every accessible wall. Ordinary blocked bumps do not cost HP or steps,
so exhaustive physical probing remains a rule-valid strategy. The user
explicitly accepts this player behavior. No probe budget or extra penalty is
introduced.

## Original items and completed information improvements

The [original item audit](original-item-audit.md) subsequently checked the
installed executable, manual, and existing reverse-engineering sources. The
original journal is the **Wisdom Orb's 24-entry hint memory**, rather than a
universal dialogue transcript. The Rust inventory tag previously lacked that
behavior. It now records only original hints first heard while owning the orb,
including paid merchant information, persists them independently of the
100-entry activity log, and returns them in original clue order. Public access
requires ownership, earlier speech is not backfilled, and a new cycle clears
the memory. Item activation opens the same hints in GUI and MCP. The dedicated
Journal panel previews recent actions and opens all retained activity in a
scrollable popup; its owned Wisdom shortcut opens the item's hint review.

Owned-item usage records now supply descriptions, activation commands,
permitted floor targets, restrictions, consumption, and charges. Help follows
the actual item dispatch and excludes acquisition locations and puzzle advice.
The audit also corrected original wall classifications, cardinal Bomb/Crystal
range, empty-use consumption, Flight selection, and the Hero manual-save gate.
Private hot-reload checkpoints remain available before Hero.

The observation also reports the persisted `last_encounter`: an actual contacted
enemy's name, HP, ATK and DEF, with floor and coordinates. This information is
available before owning the Hero Orb, matching the original encounter panel;
inspection of an arbitrary enemy still requires the Orb for forecasts. The GUI
labels this record **Last encounter** and presents it separately from selected
tile inspection. Contact includes attempts blocked by enemy defense and fatal
encounters. No gold, predicted damage, or survivability is added to that record.

Current equipment is exposed through separate `player.weapon`, `player.shield`
and `equipment` metadata slots rather than special inventory entries. A lower
tier pickup still becomes the current displayed weapon or shield, while its
stat gain is additive. The `abilities.field_magic_protection` field records
Sacred Shield's persistent collected ability after a later lower-shield pickup.
Legacy saves without slot fields infer the last retained equipment tag of each
type without adding stats. Old saves lack recollection order, so an already
retained item's later pickup cannot always be reconstructed exactly.

## Remaining ergonomics opportunities

1. **Provide safe route execution.** Committing one move per MCP call is
   sufficient but expensive across 50 floors. A route tool could execute a
   bounded direction list and stop at the first blocker, combat, pickup,
   dialogue, hazard, floor transition or unexpected board change. Return the
   consumed prefix and the observation at the stop. Do not execute an entire
   precomputed route after a scripted teleport or a newly revealed event.

2. **Make path planning outcomes explicit.** `path_to` returns an empty or
   partial direction list for several different cases: already at target,
   out-of-bounds target, pending conversation, ended game or unreachable target.
   Return `reaches_target`, final coordinate and a reason. Current planning is
   geometric only; it does not certify that apparently clear road avoids magic
   damage or a scripted event. Label that limitation rather than promising a
   safe route or exposing hidden triggers as hazards.

3. **Separate action attempts from movement steps.** The `steps` field is not
   an all-purpose action cost. Shop choices, item uses, blocked moves and some
   scripted redirections do not increment it. Any shortest-playthrough or
   fewest-tool-calls metric needs an independent action counter with an explicit
   definition; the solver should not assume `steps` equals command count.

4. **Preserve explored map knowledge explicitly if useful.** The player view
   currently includes the current floor and visited floor IDs, so the agent
   must retain prior observations itself. A remembered-map API could return a
   cached last-observed board for visited floors. It must not silently update
   distant floors from the authoritative world state when an offscreen event
   changes them.

These are optional follow-ups. None requires exposing event conditions, hidden
wall identities, or authored puzzle answers. A fresh complete autonomous run
remains the strongest outstanding validation; optimization work is deferred.

## Validation added

`crates/tos-core/tests/player_observation.rs` covers:

- Identical public identities for ordinary, hidden and scripted bricks, followed
  by legitimate hidden-passage discovery through played moves.
- Current-board-only definitions, concealed trigger markers and no unvisited
  floor titles, NPC scripts, source identifiers, internal flags or offers.
- Dialogue becoming visible on interaction, affordable/unaffordable choices and
  the Hero Orb forecast gate before and after an actual reward choice.
- Authored speech and visible inscriptions surviving timeline filtering, with
  private cinematic metadata and offscreen tile changes removed.
- Hidden/scripted brick masking across all 51 imported original floor records.

These tests establish the player observation boundary for the covered cases.
A later acceptance test should run a fresh agent against the **default player
profile**, record every real action and observation, and replay the committed
trace from the initial state without edited saves. That would test playthrough
sufficiency and reveal missing hints or engine progression defects that
scenario tests cannot establish.
