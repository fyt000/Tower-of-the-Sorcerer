# Campaign considerations

These are mechanics and planning examples from the first-cycle playtest and current source. They are not an optimal route, a recommendation to reproduce the completed history, or numeric targets for a different cycle/build. The successful history used restarts/reconstruction and still contained inefficient decisions.

## Combat breakpoints and purchases

For ordinary combat without special bonuses, attack must exceed enemy defense:

```text
hero_hits = ceil(enemy_hp / (attack - enemy_defense))
damage = max(enemy_attack - defense, 0) * (hero_hits - 1)
```

Survival requires damage strictly below current HP. Native forecasts incorporate cycle scaling and relevant passive items. Penetration is checked before Cross/Dragon Slayer attack multipliers. Forced combat is enemy-first and omits those bonuses. Movement magic, pincers and scripts require separate budgets.

Compare actual red/blue outcomes for the next necessary encounters. In one observed first-cycle state, a red +5 gem removed a Dark Knight strike and saved 171 HP, while blue +5 saved 20 HP. At a different final blocker, attack +10 reduced Great Magic Master damage to 7,238, while defense +20 reduced it to 7,102. These examples show why priority changes; their stats and outcomes are not universal thresholds. Recompute after each pickup and include the fight/key costs to access it.

The shared altar purchase index `n` starts at zero. Cost is `10*(n*n+n+2)`: 20, 40, 80, 140, 220, ... . Any choice advances the count. Gains are HP `100*(n+1)*cycle_factor`, attack `2*area*cycle_factor`, defense `4*area*cycle_factor`, where altar `area=(floor+10)/10` uses integer division. Higher-area altars give larger stat gains at the same next price, but postponing an upgrade can itself cost HP. Pickup scaling uses `(floor+9)/10` instead.

The completed history bought 1,200 HP for 1,340 gold and 1,300 HP for 1,580 gold on floor 32. Those purchases rescued the chosen route at 47 and 82 HP. Their necessity under a better route was not established. Do not encode them as required progression or justify HP spending solely because that attempt eventually finished.

## Keys and item timing

Merchant offers can resolve shortages; inspect their actual stock, price and access doors rather than assuming a repeatable blue-key source. A route funded the 4,000-gold Super Mattock but initially omitted the blue key required to reach its merchant. Budgeting price alone was insufficient.

Mattock breaks adjacent walls; Super Mattock breaks a floor's walls. Compare a key bypass with the alternative supplies and progression opened by the same item. The observed ordinary Mattock use on floor 37 opened supplies including two blue keys; Super Mattock later opened more warehouses, including the Bomb. That is evidence of an available use, not proof that floor 37 or that timing is always best.

Bomb removes eligible adjacent monsters and uses their base gold rewards. Lucky Gold doubles ordinary combat rewards, not Bomb rewards; this is intended. With Lucky Gold, bombing the shield guards yields half the gold of defeating those same guards in ordinary combat. Include that forgone income in the budget for later upgrades. Compare the HP saved and earlier protection with fighting after stat/equipment upgrades, the preparation and travel costs of each route, and the Bomb's value at another blocker. Before a Bomb plan, verify eligible targets, standing square, gate predicate and remaining access.

Ordinary stairs/Flight skip floor 44, so Sacred Shield acquisition needs a separate access plan whichever way the guards are handled. The playtest used an Ascent Wing from floor 43 at a verified Road landing. The Wing collection trip on floor 45 cost 1,200 HP before protection; whether a different access plan avoids some/all of that was not established. Once the shield is chosen as the objective, keep preparation and travel focused on obtaining it. Every detour should resolve a concrete access or survival requirement; defer unrelated exploration and optional resource trips until protected.

The Sacred Shield prevents adjacent magician movement damage and Sorcerer pincers. It does not make ordinary enemy combat harmless; check other scripted effects individually. Returning afterward can substantially change the economics of gem/supply rooms.

Keep a Wing for a verified landing and a Warp charge for an actual blocker. Failed Warp use can consume a charge; a refused Wing landing preserves the Wing. Floor-47 Magician A can retreat and repeatedly charge movement magic. Budget these mechanics when choosing an approach and return route.

Snow Crystal is reusable and changes adjacent lava. It can require repeated use while advancing a corridor; acquisition alone does not clear the entire floor. Confirm whether an item is passive, reusable or consumed before treating it as a one-time activation.

## Supplies, formations and late milestones

Defer optional potions until after known HP-halving effects if the approach remains survivable. One corrected branch postponed the floor-43 1,000-HP potion and used only one of two floor-48 upper blue doors, retaining a needed blue key. This illustrates timing and access budgeting, not a preferred fixed route.

Formation puzzles can require leaving enemies alive. In the recorded first-cycle floor-49 seal, the four cardinal guards were killed while four corner guards remained. Verify current clues, positions and the predicate before clearing the room; distinguish ordinary combat from the boss state after the seal.

The first-cycle playtest obtained Dragon Slayer from floor 49, Snow Crystal after the floor-35 Dragon, and Sacred Sword through floor-13 lava. Use this dependency information as a hypothesis to verify in the current state. It does not establish the ideal order of every intervening fight, supply or equipment purchase.

## Cycles and interpreting observations

First-cycle floor-50 contact starts the ending and advances to the backside tower. The observed transition retained HP/attack/defense, reset gold/keys/inventory and set cycle factor 44. Later cycles and native save reconstruction have different rules; consult `docs/mechanics.md`, `cpp/src/game.cpp` and the current contact/scene implementation instead of copying a first-cycle budget.

Bomb's base gold, Warp/Wing consumption differences, movement hazards and Flight/landing behavior are intended mechanics. Check source, live deltas, current tool descriptions and user clarification before labeling unexpected behavior a defect. Multiple adjacent hazards can contribute to one step's HP loss; messages and aggregate stat deltas are different evidence. Use both when budgeting or investigating the result.
