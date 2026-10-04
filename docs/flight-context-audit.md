# Original Flight controls and quest updates

The original Flight Orb opens an elevator-like interface. The player clicks
**Up** or **Down** to browse one floor at a time, seeing each selected floor,
then clicks **OK** to place the hero at its landing. The remake instead takes
a destination in one command. The previous caveat meant that the original
performs some world updates in those menu buttons, and the direct destination
command previously skipped them. It was not a restriction on where the orb can
fly.

This audit reads the installed v1.2 executable without launching or modifying
it. Its SHA-256 is
`41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779`.
Run `python tools/audit_original_flight.py` to reproduce twelve isolated original
Flight-control probes, seven normal-stair probes, three Sword-state probes and the direct disassembly in
`data/original-flight-evidence.json`. The shared probe skips every helper call,
listing the targets. The results establish direct map writes, selector values
and landing coordinates; they do not emulate Windows rendering or fairy
score/checkpoint handling.

## The actual updates

| Control and original guard | Original effect | Current Rust coverage |
| --- | --- | --- |
| Up preview changes 34 to 35; F35 `(3,8)` plus F2 `(10,10)` tile values equal 27 (`0x44EDD8..0x44EDFD`) | Clears F2 `(10,10)` to passage. The common intended state is completed F35 tunnel tile 6 and thief tile 21 remaining on F2. This cleanup happens while browsing, before OK. Down preview 36 to 35 does not perform this check. | Implemented for successful upward direct jumps spanning selector floor 35, with the exact numeric guard. |
| OK with nonzero last arrow direction; selected floor is not 25, and F25 `(5,6)` is fairy tile 23 (`0x44EB2B..0x44EB49`) | Removes that post-boss fairy. | Implemented for changed direct destinations, except the fairy’s own floor. |
| Same guard for selected floor not 49 and F49 `(5,1)` fairy (`0x44EB4A..0x44EB68`) | Removes that post-boss fairy. | Implemented for changed direct destinations, except the fairy’s own floor. |
| OK with nonzero direction, highest normal-stair floor exactly 29, selected destination less than 29 (`0x44EC04..0x44EC24`) | Clears F29 `(5,3)` and `(5,2)`; places the **Thief**, tile 21, at F29 `(6,1)`. This is NPC relocation, not a merchant spawning. | Implemented for changed Flight destinations with the exact bound and destination checks, and for normal stairs 29→28 (`0x444FBC..0x444FE2`). Wings do not invoke it. |

The F29 relocation is a **world transition event shared by stairs and Flight**.
Its placement inside Flight's OK handler is an original implementation detail,
not a requirement for the player to use a special menu sequence. A direct Flight
command should perform it as part of the successful transition, and the remake
does so before ordinary floor-entry events. It is not an unconditional arrival
event: normal stairs require destination 28, Flight permits any destination below
29, and both require the highest normal-stair floor to remain exactly 29. The
normal-stair probes verify the matching writes and the highest/destination guards.

The fairy checks do not compare the original source floor with the destination.
The selector temporarily writes the current-floor variable as the player
browses. Any nonzero last arrow state enables these checks, including a
roundtrip through the selector that returns to its starting floor. The earlier
audit's wording “final floor differs” was too broad; the actual tests are
selected floor not equal to that particular fairy's floor.

With no arrows pressed, direction remains zero. OK preserves hero coordinates,
does not remove those fairies, and does not relocate the thief. With arrows
pressed, the last arrow direction determines the chosen stair landing. There
is additional highest-floor handling that can reverse that direction to choose
the existing stair.

## Original ascent guard and the boundary of intent

Normal ascent contains a different guard for the F2 thief cleanup. After raising
the highest floor, `0x444E26` compares the value at `0x4B8714` with **35** before
testing the same F35/F2 tile-sum guard. That address is the Holy Sword collected
flag: its pickup adds 50 attack, sets displayed sword tier 4, and writes **1**
there at `0x445EAA`. The fresh-state initializer also writes **0** to that slot
through the stat-base alias `[edx + 0x8C]` at `0x455DB5`, with `edx = 0x4B8688`.
The item-retaining reset skips this clear and preserves its existing value.
Save loading restores the containing stat block, including this slot. None of
these examined paths assigns a floor number to it; its ordinary collected
value is 1. This establishes which state the comparison reads, including the
base-relative alias, without claiming a proof over every possible indirect
write or externally edited save.

The isolated ascent probes set current floor 35, previous highest 34, and a
completed tunnel. Flag values 0 and 1 leave the F2 thief unchanged; an explicitly
synthetic flag value 35 permits the cleanup. All three update the highest floor
to 35. Normal ascent back into 35 after it is already unlocked also skips this
cleanup, because the enclosing branch only runs when raising the highest floor.
Flight's Up-preview branch checks the actual selected floor against 35 and can
perform the cleanup on a later visit.

Flight's Up button cannot select 35 while the highest-stair counter is only 34.
It can select 35 once that counter is 35, even though the normal-ascent cleanup
does not run on a return visit. The selector consults that counter rather than a
per-floor visited list. Ordinary ascent therefore makes the bound resemble
"floors already reached," while arriving with a wing does not raise the bound.
The tunnel-completion map guard supplies an additional quest-progress condition.

These instructions prove the different trigger behavior, but do not establish
the designer's intent. The Sword-versus-floor comparison looks inconsistent
with the ordinary meaning of that slot; calling it a typo was an inference,
not a verified fact. A deliberate requirement to revisit the completed tunnel
through Flight remains compatible with the observed behavior. The remake keeps
the verified Flight trigger and does not add cleanup to every ascent or arrival
at F35.

## Cancellation boundary

The original Flight interface exposes Up, Down and OK controls, rather than a
demonstrated cancel operation. The original Escape-key branch at
`0x461076..0x4610A2` only closes the item-selection picker when its own picker
state is one. The recovered `tswMP.rb` enhancement's `abandon()` exits Flight
by clicking OK, rather than rolling the preview back. Therefore a hypothetical
preview/cancel sequence should not be presented as verified original behavior.

## Significance for a playthrough

Fairy cleanup removes a scoring/checkpoint encounter after leaving its boss
area; it does not grant stats or open the next stairs. The thief relocation and
tunnel cleanup belong to the later thief storyline and can change who the
player can talk to and where a passage has opened. Their verified control writes
are now implemented. The broader thief storyline is separate missing campaign
behavior, rather than a purely visual difference in item controls.

There is a broader related gap: the imported interaction for F29 `(5,3)` is
still “Talk to the thief to continue.” The events only implement his prison
escape and F15 tunnel. Merely adding Flight's three cell writes does not
implement the F29/F35 thief dialogue and digging sequence. The original thief
dispatcher at `0x465E86..0x46604D` uses dialogue queue records 27/28/29 on F29
and 32/33 on F35. Its quest-state callbacks need a separate audit before those
sequences can be claimed complete.

## Implemented direct-command semantics

The destination command treats a changed destination as the shortest monotonic
series of original Up/Down selections followed by OK:

- On an upward jump spanning preview floor 35, apply the original guarded
  tunnel cleanup.
- On successful confirmation of a changed destination, apply the original
  fairy cleanup and highest-floor-29 thief relocation.
- A same-floor command corresponds to OK without pressing arrows and leaves
  those contextual updates untouched.
- Apply the matching thief relocation to normal downstairs from 29 to 28.

These are an explicit interface adaptation, not exact reproduction of every
possible roundtrip through the original menu. A precise preview interface could
later expose its intermediate state and last direction, but it is unnecessary
for ordinary direct jumps. The campaign rules describe the world updates as
validated typed data, so custom towers are not coupled to fixed original
coordinates. All callback
effects require the original-selection rule to be enabled. They execute only
after a valid landing is resolved, before floor-entry events, keeping rejected
travel from partially changing the world. Upward preview callbacks run before
confirmation callbacks regardless of their authored list order.

`rules.floor_travel_callbacks` contains `when`, optional `tile_sum`, and `writes`.
The `when.type` values are `upward_flight_preview` (with `floor`),
`flight_confirm` (optional `except_floor`, `below_floor`, `highest_stair_floor`),
and `stairs_down` (with `from_floor`, `to_floor`, optional `highest_stair_floor`).
A `tile_sum` gives `cells: [{floor,x,y}]` and an exact numeric `equals`. Each
write supplies `{floor,x,y,tile}` and optional `if_tile`. Unknown fields, invalid
floors/coordinates and undefined write/guard tiles are rejected at import.
Only guarded tile writes are supported; these are not general scripts.

The seven focused tests in `crates/tos-core/tests/flight_callbacks.rs` cover the
interval, exact sum, fairy exceptions, stair bound, stairs versus wings,
same-floor/rejected flights, save/runtime persistence, input validation,
original-mode opt-in and player-observation secrecy. Twenty-two original x86 probes
establish the behavior independently of the Rust tests.
