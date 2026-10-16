# Presentation and input review — 2026-10-09

This dated audit records original-code extraction and C++ presentation checks.
Current Pascal recovery and routine comparisons are documented in the
[Delphi README](../../../delphi/README.md#recovery-status).

The old boundary between gameplay and presentation was unsound. Form handlers
select legal actions, drawing can reset gameplay fields, timers dispatch
commands, and dialogue code chooses continuations. Visual checks cannot
establish that those state transitions were translated.

## Recovery gap and new inventory

The initial export covered 106 functions Ghidra detected in a chosen range,
then individually recovered callbacks and save helpers. It was never reconciled
against Delphi's serialized form events and published method tables. A detected
function count was not an inventory of callable behavior.

| Form | Components | Published methods | Serialized event bindings |
|---|---:|---:|---:|
| Main game, TTSW10 | 185 | 201 | 106 |
| Ranking, TForm2 | 76 | 14 | 9 |
| Directory chooser, TForm4 | 10 | 7 | 7 |
| About, TAboutBox | 12 | 8 | 8 |
| Unused dialog, TOKBottomDlg | 4 | 0 | 0 |
| Total | 287 | 230 | 130 |

**100 published entries had no old export; 94 are serialized event handlers.**
This includes wrappers, settings, ranking, and ancillary forms, not 100 missing
gameplay rules. The unused dialog has no serialized handlers or class type
information in the executable.

All 130 bindings now resolve to successful exports. The new corpus contains
240 C-like/assembly pairs: 230 published methods and ten helpers/runtime
boundaries. The large `moncheck` export succeeded with a longer timeout.
No failed export is counted as complete. See [EVENTS.md](EVENTS.md),
[ui-manifest.json](ui-manifest.json), the [method index](decompiled/INDEX.md),
and [runtime supplement](RUNTIME.md). Old exports remain available.
The [recovery scope](RECOVERY-SCOPE.md) lists what is still outside the retained
decompilation corpus; published-entry completeness is not whole-EXE completeness.

Published control fields are also recovered. Formerly anonymous `form+0x334`
is GameLoad1, `+0x338` is GameSave1, and `+0x328` is Option1. The field table
identifies the buttons, images, and timers used in the decompiled conditions.

## Confirmed discrepancies corrected

### Original Hero Orb display

The row builder `0x44F26C` calls display arithmetic `0x44FF0C`, which calls
`0x45031C`. It uses ordinary ATK minus monster DEF and does not read Cross or
Dragon Slayer. Combat has separate bonus logic. Our screen reused the combat
forecast and therefore changed the original displayed values.

For a Zombie with HP 260, ATK 85, DEF 5, hero ATK 100 and DEF 20, the original
Orb displays **130** damage even with Cross. Actual bonus-assisted combat takes
**65**. For Dragon with hero ATK 600 and DEF 300, the original Orb displays
**1,200**, while Slayer-assisted combat takes **300**. This is an original
display quirk, not a change to combat rules.

By default, the screen uses `Game::orb_forecast`; combat and MCP actual battle forecasts
continue to use `Game::forecast`. New comparisons execute the original row
builder and record integer-to-string arguments rather than assert values from
a copied formula. **528 comparisons** cover 33 rows, both cycles, penetration
thresholds, zero incoming damage, and bonus possession.
The optional **Hero Orb actual damage** desktop QOL setting defaults off and
selects `Game::forecast` only for the displayed rows when enabled. It is the
only QOL setting, persists as a desktop preference, and has an enabled-QOL
hover explanation. Combat rules and native save state are independent of it.

### Native file actions through modal panels

`0x450758` disables GameLoad1/GameSave1, movement, and active item controls.
Item openers, Hero Orb, Wisdom, and Flight enter this gate. Desktop shortcuts
and direct dispatch could still reach native file actions through item and Orb
panels even when the rendered control was hidden.

Desktop native file actions now share a modal guard, shortcuts/menu buttons
respect it, and the replay/player Flight path rejects native save/reload while
its selector is open. MCP native loads match its existing native-save selector
guard. Complete session checkpoints remain separate tooling operations.

Nine original consumable open/cancel chains establish the original file-control
gate. Desktop smoke tests attempt save/load through Flight, Hero Orb, and item
confirmation panels and check unchanged file bytes and hero state. Those gate
checks are distinct from comparisons of item effects.

## Reviewed effects and call chains

| Family | Original behavior inspected | Disposition and evidence |
|---|---|---|
| Map draw, `0x442C38` | Resets hero word 664 before drawing | Followed in original comparisons; retained Flight/load/continuation fixes. Never a harmless skip. |
| Sprites/compositing, `0x4433A4..0x44439C` | Reads hero/maps, reuses scratch globals, clones and writes graphic objects | Explicit graphics exclusions. No named hero write does not prove purity; allocation/virtual graphic behavior remains outside the emulator. |
| Movement/keyboard/direction buttons | Writes coordinates/facing and invokes contact; keyboard entry checks Option1 and event cursor | Existing contact/arrival/queue comparisons remain. Wrapper targets now accounted for; all input interleavings are not established. |
| Stairs/facing helpers | Produce stair commands and set facing | Existing stair and Flight sequence comparisons retained. |
| Idle Timer1, `0x443120` | Alternates frames; increments saved words 608/612 on floors 15/35 | Twelve original guard/saturation probes; saved presentation-state limit below. |
| Event Timer2, `0x45265C` | Runs up to two dispatcher steps; stops on empty cursor; conditionally reenables controls | Full callback recovered. C++ uses iterative execution; legacy timing is not claimed equivalent. |
| Repeat Timer3, `0x461760` | Repeats movement or changes selected Flight floor; skips 44; redraws | Full callback recovered. Explicit previews compared; held-button interleavings remain a boundary. |
| Item confirmation | Published entry is `0x450BA0`; old `0x450BC5` starts inside setup | All 2,067 item/Flight cases pass with active items now executed from the real confirmation entry through return. Opening eligibility remains separate. |
| Consumable open/cancel | Tests ownership, sets selected operand, disables/reenables controls | Nine original memory-carrying open/cancel chains. Old fragment tests skipped these callers. |
| Wisdom and 24 clue buttons | Uses 24 noncontiguous clue words; buttons set word 668; close clears it | Existing hint/save mapping matches. Modern UI combines clues into one dialogue, without the original nested focus lifecycle. |
| Dialogue `0x449E18` / continuation `0x44DA10` | Death/retry branch, delayed Hero Orb acquisition, continuation flags and story queue work | Existing effectful comparisons retained; two original death branches with explicit modeled Yes/No replies added. Windows dialog delivery excluded. |
| Merchant/altar accept/leave | Changes stats/items/gold, queues work, removes panels, reenables controls | Existing comparisons retained; newly exported cancel/leave callbacks complete entry accounting. |
| Startup/load refresh | Initializes controls; reconstructs Zeno and redraws | Save oracle follows full refresh. Startup/settings/window callbacks now inspectable. |
| Ending/title/restart | Timer4 terminal branch resets cycle fields; append hides panels and starts Timer2 | Effectful callbacks recovered. Existing ending/cycle/desktop replay checks retained; all timer schedules not compared. |
| About/ranking/directory/settings | Ancillary UI and preferences/ranking/directory I/O | Exported separately from campaign equivalence. Original custom rankings/settings/directory UI are not implemented by the modern port. |

Button-focus VMT slot `+0x80` was checked against the actual published button
classes. It resolves to `0x416C60`, a focus routine, rather than a gameplay
click. Subsequent VCL/Windows focus delivery remains a framework boundary.
A register expression alone cannot identify an indirect call's meaning.

## Opaque save state examined

Timer1's counters were already decompiled but never compared as presentation
behavior. At floor 15 cell 60, with Road under the hero and word 48 zero, word
608 goes 0 → 1 → 2, then stops. Floor 35 cell 71 does the same to word 612.
Nonzero word 48 suppresses the updates. The helpers repaint the defeated large
monster area. The recovered direct uses are initialization, idle redraw, and
bulk save/checksum operations; further aliased uses are not disproved.

The port preserves imported counters but does not advance them according to
Delphi idle time. **Exact original save bytes after arbitrary idle timing are
not established**, even though encoding/decoding and the tested refresh match.
These are not newly discovered equipment, floor-access, or combat flags.

| Byte offset | Observed direct uses | Limit |
|---:|---|---|
| 48 | Timer1 animation suppression; set/reset by combat, Flight, prologue, dispatcher | C++ models transient visual/busy state separately; arbitrary imported transient state is not equivalent. |
| 356 | Original sound-effect preference, dispatcher and load refresh | Modern sound preferences are separate. No audio code changed and no audio tests ran in this audit. |
| 608, 612 | Repaint counters above | Saved bytes depend on idle timer execution. |
| 668 | Wisdom clue-reading mode; suppresses normal continuation/death prompt until close | Native-save controls disabled during the panel. Seeded nonzero fixtures do not establish save reachability. |
| 680 | Initial activation assigns 12 | Retained as opaque; gameplay use not established. |
| 52, 336, 604, 644, 648, 652, 672, 676 | No direct named use outside initialization in this corpus | Dynamic indexing, aliases, and bulk routines may still touch them. |

## Comparison meaning and remaining coverage

Earlier comparisons were useful evidence for arithmetic, command production,
and effects of the callbacks actually executed. The coverage claim was too
broad: supplied callback state did not prove legal player entry, and skipped
drawing could mutate state needed by the next callback. A passing count could
not repair that missing entry/continuation boundary.

This review adds an independent entry inventory, memory-carrying sequences,
numeric display arguments, explicit prompt replies, skipped call-site
addresses, and a stale-inventory check in the full pipeline. Original-only
checks are separately labeled, not inflated into C++ agreement counts.

The inventory reports named writes and direct reachable writers, and exposes
**856 indirect call sites** in retained assembly bodies. Those are sites, not
856 missing rules or distinct runtime targets. An allowlisted operand or a
RTL/VCL label remains an exclusion, not proof of harmless callbacks or return
values. The remaining direct targets in the broad application-address band
are directory-control helpers `0x43E6D4` and `0x43F1B4`; that band includes
linked library code. Automatic inventory never classifies a routine as pure
just because it lacks named writes.

The most valuable remaining coverage is real framework delivery and
input/timer interleavings: hold/release movement and Flight, focus/default
buttons and Enter, Wisdom nested close/continue, retry responses, interrupted
refresh and ending transitions. No additional floor-access bypass was
established here. That is a bounded finding, not proof of every interaction.

## Reproduction

Original SHA-256:
`41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779`.

```powershell
python tools/extract_original_ui.py
```

Run `RecoverPresentation.java` in the existing Ghidra project with the
`published-methods.tsv` input, presentation `decompiled` output, and a matching
EXE path. It checks both the supplied file and imported program hashes. The
project's old import path is stale; `build/research/TSW.exe` is the hash-matching
copy used here. Run `RecoverUiRuntime.java` with the same output directory for
the runtime supplement. The original installation remains untouched.

```powershell
python tools/review_original_presentation.py
python tools/review_original_presentation.py --check
python cpp/tools/verify_original.py
```

The pipeline includes `verify_presentation.py`, which writes
`build/cpp/reports/ui-sequence-report.json`, separate from the renderer's
`presentation-report.json`. Packaging checks probe/report hashes, boundary
policy, and presentation inventory. C++ validation uses `ctest -LE audio` as
required when no audio code/assets/configuration changed.
