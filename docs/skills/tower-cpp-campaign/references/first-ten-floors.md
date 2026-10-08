# Tested first-cycle strategy: floors 1-10

This route was tested on 2026-10-09 through normal-mode native MCP inputs. It defeated the floor-10 boss and entered floor 11. It used source knowledge and one replay rewind to correct key spending. It is a successful baseline, not a demonstrated optimum or a strategy for later floors/backside cycles.

## Early milestones

1. Complete the opening capture and prison escape. First-cycle capture resets HP to 400 and attack/defense to 10 and removes equipment, while preserving keys, gold and items in that branch. Access before capture is constrained by the corridor; do not assume the whole first floor can be cleared with the initial high stats.
2. Collect the floor-3 top-room supplies: five yellow keys, one blue key and three blue potions totaling 600 HP. Prioritize reaching the floor-5 Iron Sword before expensive optional side fights. The tested run reached the sword with 754 HP and zero altar purchases.
3. Reveal the sword-room secret wall at **floor 5 `(8,10)`**. From the accessible approach `(7,10)`, a deliberate right movement contacts it; after it opens, navigation can cross the road to the sword at `(10,10)`. Its gain is +10 attack. Check the actual approach and board if playing a changed map or cycle.
4. Use cheap gems and a targeted attack upgrade to open the climb. The tested purchases were floor-4 **attack +2 for 20 gold**, then **defense +4 for 40 gold**. Their timing is a baseline to compare, not a requirement for every run. The next global purchase remains 80 gold.
5. Prioritize the floor-9 Iron Shield before optional skeleton cleanup. Its secret entrance is the wall at **`(9,4)`**; deliberately contact it from an accessible adjacent square, then route to the shield at `(8,6)`. Its gain is +10 defense. Avoid paying for unnecessary side fights to enter this room.

At attack 23 in this first area, a Bat requires two hits, a Priest four, Skeleton C three and Skeleton B five. These are examples of attack breakpoints; current native forecasts are the deciding evidence.

## Keys, potions and purchases

Reserve colored keys for the next mandatory access before opening optional rooms. The floor-4 middle supplies provide three yellow keys behind one door; the floor-6 upper cluster provides four yellow keys behind its access route. Inspect remaining enemies/doors before pricing either room.

After sword and shield gains, return for supplies or optional gold when the damage cost has fallen. Price a potion room by HP gained minus its sequential entry cost, plus its keys/stat/access effects. Running yellow keys down to zero too early caused the discarded branch in this playtest.

The floor-6 merchant sells a blue key for 50 gold. The floor-7 merchant offers five yellow keys for 50 gold, and reaching that room costs a blue key. These trades can solve a shortage, but the successful baseline needed no merchant trades and no altar HP purchases. It used 60 gold on stats in total.

Saving a purchase can improve its later value: the floor-4 altar grants +2 attack/+4 defense, while the floor-12 altar grants +4 attack/+8 defense for the same next global price. Compare this benefit against the HP lost while postponing an upgrade. Do not turn the baseline's merchant avoidance into a rule for later areas.

## Floor-10 preparation

The red key can be obtained from floor 8's right-side guarded section. Budget its access before spending the last blue/yellow keys. Arriving on floor 10 through the lower-left stairs does not itself trigger the arena scene.

A native Flight landing rule avoids spending two yellow keys to walk from the lower-left compartment to the center. If floor 10 is the highest explored floor and it was reached via upward stairs, flying to floor 9 and then ascending back to 10 uses floor 10's down landing **`(5,9)`**, rather than its up landing `(0,9)`. Verify the observed landing. From floor 9's lower-left descending landing, a remaining potion at `(1,9)` supplied +50 HP in this run.

With two yellow keys reserved and current stats **attack 28, defense 30**, the tested right-side preparation was:

| Selected floor-10 endpoint | Result at those stats |
|---|---|
| Priest `(7,10)` | 4 HP damage |
| Yellow door `(8,8)` | Spend one yellow key |
| Skeleton B `(9,6)` | 66 HP damage |
| Red gem `(9,5)` | Attack becomes 29 |
| Yellow door `(10,8)` | Spend one yellow key |
| Blue potion `(10,10)` | +200 HP |

Native navigation can reach the second door through the room's lower road; the side Skeleton C enemies do not need to be fought. This preparation gave a net +130 HP, raising HP from 545 to 675. Use current forecasts if resources or stats differ.

## Arena, boss and rewards

Open the central red door at `(5,8)`. Contacting the trigger at `(5,4)` rearranges the guards and closes the arena. Refresh compact state after the scene and select the new enemy coordinates.

At **attack 29, defense 30**, six Skeleton C cost `6*24 = 144 HP`, two Skeleton B cost `2*66 = 132 HP`, and Skeleton A costs 245 HP. The known combat total is **521 HP**, with no potion between these arena fights. The run entered with 675 HP and finished combat with 154 HP. Current enemy availability cannot substitute for budgeting the whole sequence.

Defeat the eight arena guards, then inspect the opened boss route. The observed boss position after the scene was `(5,0)`. Boss victory opens routes and creates three yellow keys, three blue potions, three red gems and three blue gems. The Fairy contact at `(5,2)` clears the central obstruction and records its checkpoint. Collect the rewards before advancing: +600 HP, +3 attack, +3 defense and three yellow keys.

The baseline then entered floor 11 with **754 HP, attack 32, defense 33, 287 gold, three yellow keys, zero blue/red keys**, Iron Sword, Iron Shield, Hero Orb, Wisdom Orb and Flight Orb. It had two altar purchases, zero merchant trades and zero HP purchases.

## Resume evidence and scope

Repository: `D:/projects/tos-rust`.

- Native save: `artifacts/cpp-mcp-first10/normal-first10-cleared.dat`.
- Save companion: `artifacts/cpp-mcp-first10/normal-first10-cleared.dat.replay.jsonl`.
- Full recording: `artifacts/cpp-mcp-first10/normal-first10-cleared.jsonl` (1,014 native inputs).
- Earlier milestone: `artifacts/cpp-mcp-first10/normal-iron-sword.dat`.

Combine each path with the repository root when calling tools. After restart, inspect the active state and load this evidence only when the task is to resume or examine that run.

**Planning from floor 11 starts afresh.** The baseline proves that these first ten floors can be completed with this resource balance. It does not prove that the same purchase timing, damage thresholds, key reserves, equipment order or avoidance of trades is appropriate beyond that point. Inspect the new area, current cycle and forecasts, and read the relevant source before extending the strategy.
