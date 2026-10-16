# Decompilation corpus scope

This inventory describes the retained decompilation evidence. Current Pascal
recovery, including all 230 published methods, is documented in the
[Delphi README](../../../delphi/README.md#recovery-status).

| Scope | Retained evidence | Limit |
|---|---|---|
| Serialized form events | All 130 bindings resolve to successful exports | Dynamic event assignment and actual framework delivery are separate |
| Published methods | All 230 entries exported successfully | Constructors, generated methods and other non-published helpers are not covered merely by this inventory |
| Presentation supplement | 240 C-like/assembly pairs, including ten helper/runtime boundaries | Decompiler output still needs assembly and behavioral review |
| Earlier gameplay/presentation corpus | 242 distinct exported entry addresses across those two directories | Overlapping exports and interior entries are not independent gameplay rules |
| Indirect calls | 856 retained assembly call sites inventoried | Many target identities and downstream callback effects remain unresolved |

The [whole-program corpus](../whole-program/REVIEW.md) contains 3,298
machine-entry exports, including all 102 direct targets missing from the
earlier corpus. Their historical list remains in
[effect-inventory.json](effect-inventory.json).

The whole-program analysis snapshot retains 14,369 unresolved CODE bytes and
101 bytes of instruction/metadata conflicts. These are executable-accounting
limits, not counts of missing Pascal game methods. Windows API implementations,
runtime-generated callbacks and actual focus/timer delivery require separate
verification. See the [presentation audit](REVIEW.md) for its tested scope.
