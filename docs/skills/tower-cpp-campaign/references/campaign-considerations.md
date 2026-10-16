# Campaign considerations

Use these mechanics and recommendations to try when planning a campaign. Verify costs, access and forecasts in the active build and cycle; no fixed route or stat target is assumed.

## Combat breakpoints and purchases

For ordinary combat without special bonuses, attack must exceed enemy defense:

```text
hero_hits = ceil(enemy_hp / (attack - enemy_defense))
damage = max(enemy_attack - defense, 0) * (hero_hits - 1)
```

Survival requires damage strictly below current HP. Native forecasts incorporate cycle scaling and relevant passive items. Penetration is checked before Cross/Dragon Slayer attack multipliers. Forced combat is enemy-first and omits those bonuses. Movement magic, pincers and scripts require separate budgets.

Compare actual red/blue outcomes for the next necessary encounters. Attack can remove an enemy strike or enable penetration; defense can save HP across many remaining strikes or make several fights free. Recompute after each pickup and include the fight/key costs to access it. Avoid using a fixed color priority or buying an upgrade without checking its concrete effect.

The shared altar purchase index `n` starts at zero. Cost is `10*(n*n+n+2)`: 20, 40, 80, 140, 220, ... . Any choice advances the count. Gains are HP `100*(n+1)*cycle_factor`, attack `2*area*cycle_factor`, defense `4*area*cycle_factor`, where altar `area=(floor+10)/10` uses integer division. Higher-area altars give larger stat gains at the same next price, but postponing an upgrade can itself cost HP. Pickup scaling uses `(floor+9)/10` instead.

Try to avoid HP purchases. Check cheap gems, equipment, deferred potions, lower-damage routes and an authorized rewind before treating bought HP as necessary. HP purchases also advance the shared altar price. When the user rules out HP purchases or prefers rewinds, preserve that constraint instead of rescuing a weak route with spending.

## Lucky Gold sweeps and the 3% boost

Try acquiring Lucky Gold before clearing large numbers of optional enemies. Once it is acquired, start sweeping accessible earlier floors for gems and doubled ordinary-combat gold as soon as fights cost zero or almost no HP. Do this during progression, so free stat gains reduce later costs and banked gold remains available for useful purchases; avoid postponing the sweep to a final cleanup. A cheap gem room or gathering cheap gold for a planned upgrade or access item can be useful milestones themselves.

Track remaining gem rooms, cheap enemies, key costs and the next altar price. Take accessible stat gains before fights they can make cheaper, then recalculate and revisit rooms newly made cheap. Include approach and return hazards, forced fights and puzzle predicates: a zero-damage ordinary-combat forecast alone does not make a room free. After Lucky Gold, preserve a monster for a concrete puzzle or access reason rather than continuing to defer its gold without a purpose.

Collect cheap gold promptly, but choose stat purchase timing deliberately. Hold it until an attack/defense upgrade reaches a useful combat breakpoint, unlocks progression or saves enough HP across the planned encounters to justify buying now. If the fights already cost zero or almost no HP and the upgrade changes no relevant breakpoint, try completing the cheap sweep without spending. Collect accessible free gems and equipment, then reassess which purchase is useful; affordability alone is not a reason to buy.

Favor higher-area altars when reaching them without the purchase is affordable. Each early purchase advances the shared price count while granting the current area's smaller gain, so waiting can preserve a cheaper purchase for a larger later gain. Compare that benefit with the HP and access costs of waiting. Keep gold available for planned access items. Once a worthwhile purchase is identified, check cheap remaining gold sources if the balance is slightly short. Before the cycle transition, try converting the remaining usable gold into stats that carry over; avoid surplus keys, unused items or HP purchases merely to empty the balance.

The floor-2 old man's one-time boost adds `floor(attack * 3 / 100)` attack and `floor(defense * 3 / 100)` defense. Try leaving that conversation until after the planned equipment, gem sweeps and affordable altar upgrades. Check the integer gains at the proposed timing. Early use on small base stats can yield little and cannot be repeated after later upgrades. Apply it before the last difficult fight or the ending once planned stat gains are collected; use it earlier only for an identified breakpoint whose immediate benefit warrants the lost later gain.

Try revisiting uncollected earlier equipment as well as gems. Check whether it still grants additive stats even when a higher equipment tier is held, and verify retained protection after pickup rather than dismissing the item by tier name alone.

## Keys and item timing

Merchant offers can resolve shortages; inspect their actual stock, price and access doors rather than assuming a repeatable blue-key source. Check alternative approaches to a merchant before assuming one particular door or key color is required. Budget both the item's price and its access.

Try to avoid the repeatable 1,000-gold single-yellow-key trade. Compare cheaper remaining merchant stock, accessible keys, rooms with a positive net key return, wall bypasses and an authorized rewind of earlier key spending. Calculate keys spent and recovered in order, including the exit and reserved progression doors. Compare the trade's gold cost with the next altar upgrade before committing.

Mattock breaks adjacent walls; Super Mattock breaks a floor's walls. Compare a key bypass with the alternative supplies and progression opened by the same item. Try evaluating floor-37 warehouses as a use for a Mattock, using the live room contents and entry geometry. Compare the net gems, keys, supplies and access with the purchase price and the upgrades that gold could otherwise buy; avoid buying Super Mattock without a worthwhile planned use.

Bomb removes eligible adjacent monsters and uses their base gold rewards. Lucky Gold doubles ordinary combat rewards, not Bomb rewards; this is intended. With Lucky Gold, bombing the shield guards yields half the gold of defeating those same guards in ordinary combat. Include that forgone income in the budget for later upgrades. Compare the HP saved and earlier protection with fighting after stat/equipment upgrades, the preparation and travel costs of each route, and the Bomb's value at another blocker. Before a Bomb plan, verify eligible targets, standing square, gate predicate and remaining access.

Ordinary stairs/Flight skip floor 44, so Sacred Shield acquisition needs a separate access plan whichever way the guards are handled. Try evaluating an Ascent Wing from floor 43 at a verified Road landing, including the Wing's collection and return costs. Once the shield is chosen as the objective, keep preparation focused on obtaining it. Safe earlier-floor sweeps after Lucky Gold can fund that preparation; defer rooms whose hazards or fights are still expensive until protected.

The Sacred Shield prevents adjacent magician movement damage and Sorcerer pincers. It does not make ordinary enemy combat harmless; check other scripted effects individually. Returning afterward can substantially change the economics of gem/supply rooms.

Keep a Wing for a verified landing and a Warp charge for an actual blocker. Failed Warp use can consume a charge; a refused Wing landing preserves the Wing. Floor-47 Magician A can retreat and repeatedly charge movement magic. Budget these mechanics when choosing an approach and return route.

Snow Crystal is reusable and changes adjacent lava. It can require repeated use while advancing a corridor; acquisition alone does not clear the entire floor. Confirm whether an item is passive, reusable or consumed before treating it as a one-time activation.

## Supplies, formations and late milestones

Defer optional potions until after known HP-halving effects if the approach remains survivable. Try comparing both entrances to supply rooms before spending keys, and leave a second entrance closed when one already gives sufficient access. Keep potion timing separate from gem and gold sweeps: beneficial stat gains need not be postponed with HP pickups.

Formation puzzles can require leaving enemies alive. For the first-cycle floor-49 seal, check the four cardinal guards and four corner guards against the native clue or predicate before fighting. Try preserving the corners while defeating the cardinal guards when the current rule supports that formation; verify the resulting boss state before combat.

Try evaluating Dragon Slayer from floor 49, Snow Crystal after the floor-35 Dragon, and Sacred Sword through floor-13 lava as an equipment dependency chain. Verify availability, doors, combat and return costs in the current state. Before a remaining hard fight, check cheap uncollected gems and equipment, gold that can fund a useful upgrade, and the reserved 3% boost instead of settling for barely enough HP.

Before committing to the ending, verify remaining stat opportunities and explain deliberate omissions. This final check should catch gaps in earlier sweeps. Avoid treating a floor-49 victory as proof that the native floor-50 access and ending are complete; inspect the remaining gate and scene requirements.

## Cycles and interpreting observations

First-cycle floor-50 ending contact advances to the backside tower, retaining HP/attack/defense, resetting gold/keys/inventory and setting cycle factor 44. Verify the live transition and stop at the requested campaign boundary. Later cycles and native save reconstruction have different rules; consult `docs/mechanics.md`, `cpp/src/game.cpp` and the current contact/scene implementation instead of copying a first-cycle budget.

Bomb's base gold, Warp/Wing consumption differences, movement hazards and Flight/landing behavior are intended mechanics. Check source, live deltas, current tool descriptions and user clarification before labeling unexpected behavior a defect. Multiple adjacent hazards can contribute to one step's HP loss; messages and aggregate stat deltas are different evidence. Use both when budgeting or investigating the result.
