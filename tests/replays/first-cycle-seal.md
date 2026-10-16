# First-cycle seal fixtures

Normal native-input recordings from `new_game`, without injected state or
save reloads. All end before 50F ending contact with ATK 409 / DEF 348 and
Zeno sealed to 800/500/100 (hypothetical combat cost 304 HP).

| Recording | Final HP | Gold | Combat margin | Regression purpose |
|---|---:|---:|---:|---|
| `first-cycle-seal.jsonl` | 361 | 1,164 | 57 | Original opening, Octopus/potion and pickup optimizer controls |
| `first-cycle-seal-economy.jsonl` | 361 | 1,330 | 57 | 10,307 inputs; merchant omission/key routing |
| `first-cycle-seal-cashflow.jsonl` | 611 | 1,930 | 307 | 10,758 inputs; key-sale/purchase timing and deferred 41F potion |

The [planner verifier](../../docs/route-planner.md#commands) checks all nine
Octopus rewards, Dragon without Slayer, Sacred Sword, post-Sword farming,
Great Master, both Wings at first 50F arrival, post-gate Bomb seal, preserved
diagonal guards, no HP altar purchases and positive Zeno margin.

Keep older fixtures as optimizer controls. Cashflow combines manual strategy
with bounded experiments; `economy` does not generate those coupled changes.
These are successful reference routes, without an optimality claim.
