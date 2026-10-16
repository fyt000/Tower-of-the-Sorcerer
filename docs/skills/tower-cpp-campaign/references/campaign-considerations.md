# Campaign decisions

Verify costs and access against the current build, cycle and forecasts.

## Opening and combat

First-cycle capture resets HP to 400 and attack/defense to 10, removing equipment.
Plan from actual post-capture access. Early sword/shield upgrades can make return
visits cheaper; inspect 6F/7F key offers and budget the full 10F arena sequence
before triggering its rearrangement.

Without special bonuses, ordinary damage is
`max(enemy_attack-defense,0) * (ceil(enemy_hp/(attack-enemy_defense))-1)`.
Attack must penetrate before Cross/Dragon Slayer bonuses; forced combat is
enemy-first without them. Forecasts exclude movement magic, pincers and scripts.
Compare red/blue gains across required encounters, subtract access costs and
recompute after upgrades; no fixed color priority applies.

## Gold, purchases and keys

- Get Lucky Gold before bulk optional farming when access is worthwhile. Then
  promptly sweep cheap earlier gems/enemies and revisit after upgrades. Include
  doors, hazards and return costs; preserve puzzle enemies. Do not defer these
  sweeps until the ending.
- Collect cheap gold now; buy stats for a concrete breakpoint. Shared altar
  purchase index `n` starts at zero: price `10*(n*n+n+2)`, HP gain
  `100*(n+1)*cycle_factor`, attack `2*area*cycle_factor`, defense
  `4*area*cycle_factor`, with `area=(floor+10)/10` integer division.
  Higher altars give more stats at the same price; weigh waiting costs.
  Pickup scaling instead uses `(floor+9)/10`.
- Avoid HP purchases until routes, supplies, gems/equipment and authorized
  rewinds are evaluated; HP also raises the next altar price. Preserve any
  explicit no-HP-purchase constraint.
- Reserve colored keys sequentially, including merchant access and exits.
  Avoid the 1,000-gold yellow-key trade when stock, net-positive key rooms,
  alternate entrances, Mattock or an authorized rewind are cheaper.
- Delay the 2F old man's one-time `floor(stat*3/100)` boost until planned stat
  gains, unless early use resolves a worthwhile blocker. Apply before the last
  difficult fight/ending. Check whether earlier uncollected equipment still
  adds stats despite a higher held tier.

## Items and late objectives

| Decision | Costs/mechanics to check |
|---|---|
| Mattock / Super Mattock | Adjacent/floor-wide walls; compare key savings and supplies, including 37F warehouses, against purchase/access cost. |
| Sacred Shield | Separate 44F access plan, e.g. verified Wing landing from 43F; compare fighting guards with Bomb. Once chosen, focus preparation and defer costly hazard rooms until protected. |
| Bomb | Base gold only; with Lucky Gold it forfeits half the guards' ordinary-combat income. Verify targets, standing square and gate predicate. |
| Protection | Shield blocks adjacent magician damage/pincers, not ordinary combat or every script. |
| Warp / Wings | Failed Warp can consume a charge; refused Wing preserves it. Reserve for verified blockers/landings. |
| Snow Crystal | Reusable, clears adjacent lava; advance/use repeatedly. Consider Dragon Slayer → 35F Dragon → Snow → 13F Sacred Sword dependencies. |
| Potions | Defer optional healing past HP-halving effects when survivable; collect useful stats separately. |
| 49F seal | Verify native formation; preserve corner guards while resolving cardinal guards when the predicate requires it. |

47F Magician A can retreat and charge repeated movement magic. Price approach
and return, not only combat. Compare room entrances before opening both.
Before a hard fight/ending, check cheap gems, doubled gold, useful purchases and
the reserved boost; explain omissions rather than claiming an unchecked sweep.

First-cycle 50F ending carries HP/attack/defense into factor 44 while resetting
gold/keys/items. Stop at the requested boundary; later cycles/load reconstruction
have different rules. See [mechanics](../../../mechanics.md).
