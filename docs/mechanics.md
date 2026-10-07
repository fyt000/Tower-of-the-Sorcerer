# Rules retained by the C++ baseline

This is a compact guide to decisions that matter when checking original behavior.
The implementation and decompiled source remain the detailed specification.
See [fidelity coverage](../cpp/FIDELITY.md) for the tested limits.

## Combat and items

Attack penetration is checked before applying ordinary-battle Cross/Slayer
bonuses. A penetrating hit deals effective attack minus scaled enemy defense;
required hits round up. Ordinary combat starts with the hero, while forced
combat starts with the enemy and ignores those bonuses. Fatal combat stops at
the killing strike and cancels later rewards.

Monster rows are shared and their HP/attack/defense scale by the current cycle
factor. Victory uses the row's gold, with Lucky Gold's multiplier. Bomb uses raw
rewards and its original tile classifier. Octopus parts remain separate encounters;
the mouth and Dragon head clear their original body cells on victory.

Item consumption, refused attempts and cardinal bounds retain their original
branches. Stairs and Flight skip floor 44; wings can reach it. Normal-stair
travel sets the Flight ceiling, while wings preserve that distinction. Door
checks run even when contact is refused for lack of a key.

## Floors, dialogue and cycles

Floor puzzles preserve the original numeric-sum predicates and command order.
Dialogue continuation flags retain their aliases, including the 2F gift at slot
18 and first 42F arrival at slot 51. Gifts, purchases and recorded hearing are
shared with their original continuation state rather than duplicated flags.

First-cycle 50F Zeno contact starts the ending. The second cycle carries hero
stats, resets gold/items and uses the backside factor of 44. Further cycles
preserve gold, items, acquisition flags and explored ceiling as in the initializer.
Capture has separate frontside/backside stat and inventory branches.

| Backside 50F Zeno | HP | Attack | Defense |
|---|---:|---:|---:|
| Cycle 2 fixed row | 44,000 | 27,500 | 5,500 |
| Later cycle, restored row | 352,000 | 220,000 | 44,000 |
| Later cycle, re-sealed row | 35,200 | 22,000 | 4,400 |

The 24F gate removes an existing seal by multiplying the shared row by ten,
then installs the fixed row only in cycle 2 and queues an enemy-first fight.
Later cycles leave Zeno for ordinary contact. A new 49F seal after gate entry
remains effective when returning to 50F with a wing. Backside victory plays its
closing commands before starting the next cycle.

Saving does not serialize monster rows. As in the original load routine,
unsealed Zeno is rebuilt as `8000/5000/1000`; sealed Zeno is rebuilt as
`800/500/100 × (cycle_factor_minus_one + 1)`. Combat then applies its usual
cycle factor again. This legacy backside load quirk is retained; repeated loads
reconstruct from flags rather than multiplying the already loaded row. The
cycle-2 50F contact branch reinstalls its fixed `1000/625/125` row before combat.
The table above describes live gate/seal gameplay without that intervening load.
Fairy checkpoints are saved after their completed scene; custom original ranking
files are not imported.
