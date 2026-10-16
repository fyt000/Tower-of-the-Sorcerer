# Game mechanics

## Combat and items

Penetration is checked before Cross/Dragon Slayer bonuses. A penetrating hit
deals effective attack minus scaled defense; required hits round up. Ordinary
combat is hero-first. Forced combat is enemy-first and omits those bonuses.
A fatal strike cancels later rewards. See the
[arithmetic difference](../cpp/FIDELITY.md#deliberate-differences-and-remaining-work)
at extreme backside values.

Shared monster HP, attack and defense scale by the cycle factor. Victory
applies Lucky Gold; Bomb uses raw rewards and its tile classifier. Octopus
parts are separate encounters; mouth and Dragon head victories have body
cleanup rules.

Stairs and Flight skip 44F; wings can reach it. Normal stairs set the Flight
ceiling. Refused doors still run floor checks. Flight uses an ordered cardinal
scan: a later classified neighbor can override a stair result. Its ceiling is
`highest_floor`, and other active items are disabled during selection.

Opening Flight and successful previews clear the highest-floor stair marker
through map redraw. Direct Flight input performs that same sequence; returning
to the highest floor uses its upward arrival square. Successful wings,
deferred floor changes, dialogue stage 13 and file-load refresh also clear
the marker. Refused wings preserve it; in-memory session checkpoints retain
selector state without performing a file-load refresh.

## Floors, dialogue and cycles

Floor puzzles retain numeric-sum predicates and command order. Dialogue flags
share their continuation state, including the 2F gift at slot 18 and first
42F arrival at slot 51.

First-cycle 50F Zeno contact starts the ending. Cycle 2 retains HP/attack/defense,
resets gold/items and uses a factor of 44. Cycle 3 onward also preserves gold,
items, acquisition flags and the explored ceiling. Capture has separate
frontside/backside stat and inventory branches.

| Backside 50F Zeno, without an intervening load | HP | Attack | Defense |
|---|---:|---:|---:|
| Cycle 2 fixed row | 44,000 | 27,500 | 5,500 |
| Later cycle, restored row | 352,000 | 220,000 | 44,000 |
| Later cycle, re-sealed row | 35,200 | 22,000 | 4,400 |

The 24F gate removes a seal by multiplying the shared row by ten. Only cycle 2
then installs the fixed row and queues enemy-first combat; later cycles use
ordinary contact. Re-sealing on 49F remains effective when returning by wing.
Backside victory finishes its closing commands before the next cycle.
Loading reconstructs monster rows from flags, including extra scaling for
sealed Zeno on the backside; repeated loads do not multiply an existing row.
The exact rows and checksum/checkpoint rules belong to the
[save specification](original-data.md#original-saves).
Cycle-2 50F contact reinstalls its `1000/625/125` row before combat.

Fairy rankings use five independent ten-entry tables. Compare score, then HP,
then strictly compare wrapping signed 32-bit
`attack + defense - previous HP > previous attack`. First-cycle qualifying
entries can be submitted after dialogue, using the insertion position cached
at contact. Ranking tables survive slot loads.

## Retained quirks

Comparisons use the unpatched original executable. These rules are intentional:

| Case | Behavior |
|---|---|
| 33F trap | Only the upper cell triggers it; entry after clearing guards from below still seals exits. |
| 47F Magician A | The hero-row guard and flat-array horizontal wrapping remain. C++ rejects an index beyond the floor tiles. |
| Backside 45F Merchant | Gives unscaled 2,000 HP for 1,000 gold. |
| Enemy-first Lucky Gold | Income doubles. Delphi displays the undoubled amount; C++ displays the credited gold. |

The implementations' safety and presentation differences are documented in
the [Delphi README](../delphi/README.md#recovery-status) and
[C++ fidelity notes](../cpp/FIDELITY.md).
