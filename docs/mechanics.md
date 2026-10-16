# Game mechanics

## Combat and items

Attack must penetrate defense before Cross/Dragon Slayer bonuses apply.
Ordinary combat is hero-first; forced combat is enemy-first without those
bonuses. Hits round up; fatal strikes cancel later rewards. Monster HP/attack/
defense scale by cycle. Lucky Gold doubles ordinary rewards; Bomb uses base gold.
[Extreme-value arithmetic differs in C++](../cpp/FIDELITY.md).

Stairs and Flight skip 44F; Wings can reach it. Flight requires adjacent-stair
entry, uses ordered cardinal classification (later neighbors can override a
stair), and is limited by `highest_floor`. Other active items are disabled.

Map redraw clears the highest-floor stair marker on Flight open/successful
preview, successful Wings, deferred floor changes, dialogue stage 13 and file
load. Refused Wings preserve it; session checkpoints retain selector state.
Refused doors still run floor checks. Puzzles retain numeric-sum predicates
and original command order.

## Cycles and rankings

First-cycle 50F contact starts the ending. Cycle 2 retains HP/attack/defense,
resets gold/items and scales by 44. Later cycles also preserve gold, items,
acquisition flags and explored ceiling. Capture has separate cycle branches.

| Backside 50F Zeno, before loading | HP | Attack | Defense |
|---|---:|---:|---:|
| Cycle 2 fixed row | 44,000 | 27,500 | 5,500 |
| Later, restored | 352,000 | 220,000 | 44,000 |
| Later, re-sealed | 35,200 | 22,000 | 4,400 |

The 24F gate multiplies sealed Zeno's row by ten. Cycle 2 then installs the fixed
row and queues forced combat; later cycles use ordinary contact. Re-sealing on
49F remains effective when returning by Wing. Cycle-2 50F contact reinstalls
base `1000/625/125` before combat. [Loading rebuilds rows from flags](original-data.md#original-saves).

Rankings compare score, then HP, then wrapping signed
`attack + defense - previous HP > previous attack`. First-cycle submissions
use the insertion position cached at contact. Rankings survive game loads.

## Retained quirks

| Case | Behavior |
|---|---|
| 33F trap | Only upper cell triggers; clearing guards from below still seals exits. |
| 47F Magician A | Hero-row guard and flat-array horizontal wrapping remain; C++ rejects out-of-floor indices. |
| Backside 45F Merchant | Unscaled 2,000 HP for 1,000 gold. |
| Enemy-first Lucky Gold | Income doubles; Delphi displays base gold, C++ credited gold. |

See [Delphi recovery status](../delphi/README.md#recovery-status) for its retained fix.
