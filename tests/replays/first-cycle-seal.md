# First-cycle seal fixture

`first-cycle-seal.jsonl` is a normal native-input recording from `new_game`,
created by search-assisted, manually guided play on 2026-10-14. It contains no
save reloads or injected game state. It ends on 50F (4,5), before ending contact,
with HP 361 / ATK 409 / DEF 348 and Zeno sealed to 800/500/100. Hypothetical combat
costs 304 HP, leaving 57.

The route collects all nine Octopus rewards, defeats Dragon without Dragon
Slayer, obtains Sacred Sword, farms and heals before Great Master, reaches 50F,
descends, completes the 49F seal with Bomb, and ascends. It preserves all four
diagonal guards and makes no HP altar purchases. This is a successful reference
route, not a claimed optimum.

The optional `tsw_planner_tests` target uses this fixture to test the original
Octopus omission, potion deferral, final challenge boundaries and automatic
early pickup improvements. The fixture deliberately retains the earlier
opening so the optimizer has a stable measurable regression case.

See [the planner guide](../../docs/route-planner.md) for commands, algorithm
details, expected early improvements and the distinction between search and
manual strategy.

`first-cycle-seal-economy.jsonl` is the subsequently verified 10,307-input
economic improvement, also made entirely from normal native inputs. It keeps
the same final HP, stats, equipment and seal, with 1,330 gold instead of 1,164.
At first 11F arrival it has HP736, gold291 and Y4/B1/R0; at first 21F arrival it
has HP1880, gold613 and Y7/B1/R0. It skips the 200-gold 38F yellow-key bundle by
omitting a 34-gold optional 12F side trip and changing later door routing.
The original fixture remains unchanged for optimizer regressions. Tests verify
both complete routes and exercise the merchant-omission search independently.

`first-cycle-seal-cashflow.jsonl` is the 10,758-input continuation of that work.
It finishes with HP611 / ATK409 / DEF348 / gold1930 and no keys, leaving a
307-HP hypothetical sealed-Zeno margin. It preserves the 11F/21F improvements.
Three earlier yellow-key sales fund an earlier 920-gold defense purchase;
the required 31F key bundle remains affordable with one gold left. The 38F
bundle replaces those three keys for 200. Five later surplus keys are sold.
The earlier defense saves 176 HP at its original checkpoint. Another purchase
timing change saves 10 HP at its comparison checkpoint, and the 41F (0,0)
potion is deferred until after the halving traps, adding 250 HP at the finish.

This fixture combines a manually proposed sale schedule with bounded native
experiments on purchase timing and potion deferral. The `economy` command does
not yet generate those coupled changes. Tests verify both the complete seal
contract and the timing-sensitive funding/potion sequence; the older fixtures
remain intact as controls for their respective optimizers.
