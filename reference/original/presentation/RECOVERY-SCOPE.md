# What remains outside the decompilation corpus — 2026-10-09

The whole original executable has **not** been decompiled into a complete,
reviewed source corpus. Recovery of the published UI entries is complete for
the structurally extracted form/method inventory. That narrower statement
must not be used as a whole-program completeness claim.

The subsequent [whole-program accounting](../whole-program/REVIEW.md) now
retains 3,298 machine-entry exports and a partition of every CODE/file byte.
All 102 direct targets listed below have exports in that new corpus. There
are still 14,369 unresolved CODE bytes, 101 bytes of instruction/metadata
conflicts, unresolved indirect delivery and unverified behavior. The table
below describes the earlier gameplay/presentation corpus, which is preserved.

| Scope | Current accounting | Remaining limit |
|---|---|---|
| Serialized form events | All 130 bindings resolve to successful exports | Dynamic event assignment and actual framework delivery are separate |
| Published methods | All 230 entries exported successfully | Constructors, generated methods and other non-published helpers are not covered merely by this inventory |
| Presentation supplement | 240 C-like/assembly pairs, including ten helper/runtime boundaries | Decompiler output still needs assembly and behavioral review |
| Earlier gameplay/presentation corpus | 242 distinct exported entry addresses across those two directories | Overlapping exports and interior entries are not independent gameplay rules |
| Direct targets without an exported entry in those directories | 102 distinct target addresses in retained call edges | All now exported in the separate whole-program corpus; not a count of all executable functions |
| Indirect calls | 856 retained assembly call sites inventoried | Many target identities and downstream callback effects remain unresolved |

The machine-readable list of the 102 direct targets is
`direct_targets_without_exported_entry` in [effect-inventory.json](effect-inventory.json).
It is regenerated and checked by `tools/review_original_presentation.py`.
It includes string, control, file and other linked runtime/library support.
An address without its own export can also be an interior or shared entry;
function boundaries must be checked before calling it a missing function.

Two targets in the broad application-address band are `0x43E6D4` and
`0x43F1B4`, reached by recovered directory-control helpers. The band includes
linked library code. Those two remaining targets do not establish that the
rest of the executable has been recovered.

The separate whole-program corpus expands linked RTL/VCL inspection and
accounts for class/VMT methods, properties, startup, installed exception
continuations, byte gaps and callback candidates. It also detects function
bodies that were incomplete despite successful C decompilation. Windows API
implementations reside outside the pinned EXE, and VCL generates executable
callback trampolines at runtime. Unknown executable regions and indirect
delivery remain explicit; no count of all remaining executable routines is
established and full behavior is not verified by that ledger.

Decompilation, translation and verification are different milestones. Even
exported callbacks retain untested branches, aliases and timer/focus schedules.
See [REVIEW.md](REVIEW.md) for the effects inspected and the current comparison
boundaries; an excluded runtime call is not evidence of equivalent behavior.
