# Original executable and tswKai comparison

This audit compares the bundled campaign with the installed English TSW 1.2
executable and the corrections documented by
[tswKai](https://github.com/Z-H-Sun/tswKai). The sources establish several real
original defects, several missing remake branches, and a separate set of
presentation improvements. A listed correction is not automatically a new
gameplay requirement.

## Reproducible sources

The comparison uses these pinned inputs:

| Input | Identity |
| --- | --- |
| Installed `TSW.exe` | SHA-256 `41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779` |
| `tools/research/tswKai` | Commit `08e5af7c8f3e4d1696ccd5725d745e87b989bff6` |
| `tools/research/tswKai.wiki` | Commit `9d5fd2f0b3589835a7c9e870bc232d80d0a8cf55` |

The upstream repository was cloned with
`gh repo clone Z-H-Sun/tswKai tools/research/tswKai`; the wiki was cloned
separately. These research checkouts are ignored by Git. The original installed
game and its artwork are read-only. No upstream executable or binary patch was
run or installed.

Primary references are the requested
[Corrections Log](https://github.com/Z-H-Sun/tswKai/wiki/%C2%A71.1-%E2%80%90-%E8%BF%90%E8%A1%8C%E9%AD%94%E5%A1%94%E6%B8%B8%E6%88%8F#%E4%BF%AE%E6%AD%A3%E4%BA%8B%E9%A1%B9),
the wiki's [Patch Config](https://github.com/Z-H-Sun/tswKai/wiki/1.2.1-%E2%80%90-Patch-Config),
and pinned source files
[tswMod.asm](https://github.com/Z-H-Sun/tswKai/blob/08e5af7c8f3e4d1696ccd5725d745e87b989bff6/tswMod.asm),
[tswMod.rb](https://github.com/Z-H-Sun/tswKai/blob/08e5af7c8f3e4d1696ccd5725d745e87b989bff6/tswMod.rb),
[tswRev.asm](https://github.com/Z-H-Sun/tswKai/blob/08e5af7c8f3e4d1696ccd5725d745e87b989bff6/tswRev.asm),
[monsters.rb](https://github.com/Z-H-Sun/tswKai/blob/08e5af7c8f3e4d1696ccd5725d745e87b989bff6/monsters.rb),
and [dmg.dll.c](https://github.com/Z-H-Sun/tswKai/blob/08e5af7c8f3e4d1696ccd5725d745e87b989bff6/tswMPExt/dmg.dll.c).
The committed audit report includes exact original-byte matches rather than
relying on the wiki description alone.

Run these tools from the repository root after extracting the original data:

```powershell
python tools/audit_original_events.py
python tools/audit_original_animations.py
python tools/audit_original_mechanics.py
npm run check
npm run test:animations
npm run test:mcp
npm run test:native
npm run test:browser
```

The Python tools require `pefile`, `capstone`, `unicorn` and Pillow.
`TOS_ORIGINAL_EXE` can select another path containing the same executable.
The mechanics audit verifies the executable hash and research commit IDs before
using its addresses. GUI tests require the rebuilt game served on port 8080;
`TOS_URL` can select another URL.

## Assessment of reported corrections

| Upstream issue | Evidence and assessment | Remake behavior |
| --- | --- | --- |
| 33F trap entered from below | Real defect. The original upper entrance is trigger tile 7, while the lower is ordinary road 6. Upstream's original bytes match the installed setup and cleanup branches. A controlled late upper entry also queues both gates closed after all guards are gone. | Both entrances share one once event. Gates close only while an original guard survives, then both open after all four defeats. Save/load preserves that shared count. |
| 47F Magician A retreat | Real coordinate defect. `0x44C5C4` uses a hero-row test for horizontal moves and linear indices that wrap across columns. Probes reproduce both row wrapping directions and suppressed top-row retreat. | Restore retreat with independent x/y bounds, after hazard damage. Sacred Shield suppresses damage but preserves retreat. An optional original-bounds rule retains the historical valid-board behavior. |
| 49F extra appearance event | Real queue defect. The extra cursor increment at `0x4637DD` matches upstream's original bytes. Since records are reused, the cursor can expose an old record. | Extract explicit ordered effects into a fresh bounded action timeline; no reused stack pointer or phantom slot. Existing materialization tests cover the intended eight Sorcerers. |
| Battles around 2500 rounds | Real capacity defect in the fixed original event buffer. The number depends on records queued, including sound and animation records. | Store one battle presentation with strike counts rather than allocating records per round. A 3000-strike regression verifies exact damage, reward, and bounded presentation size. |
| 50F repeated backside scaling | Real save/load stat-restoration defect. `0x455B78` includes the cycle-factor calculation in global-row restoration, although battle calculation already scales its temporary row. This is separate from the intentional gate reversal of the 49F seal. | Persist normalized enemy overrides and resolve cycle scaling once. Retain shared-row seal/gate arithmetic and its order-dependent weaker later-cycle 50F route; cycle 2 assigns its distinct fixed row. |
| Lucky Gold first-strike reward text | Real display defect. The original display branch at `0x47FF54` matches upstream's correction signature; it does not establish a missing actual reward. | The same resolved reward drives player gold, activity text, battle presentation and history. A full 13-fight 40F ambush with Lucky Gold verifies all 1400 gold and each displayed reward. |
| 40F yellow-door completion prompt | Real display defect; original bytes at `0x4740BE` match the identified prompt branch. | Report the actual ambush outcomes and scripted continuation rather than an unrelated door message. |
| Magician A mask displaced one pixel | Real artwork defect. The original masks for cells 151/152 exactly match upstream's corrected artwork when shifted right one pixel. | Correct only the recognized original mask signatures at load. A unit test compares independent packed silhouettes and corrected hashes, verifies idempotence, and preserves custom/already-corrected artwork. |
| 50F Thief / backside magic text | The original Thief builder queues one-based dialogue 264, meaning zero-based string 263, with no map/stat effect. The remake had retained a generic placeholder at that location. Backside magic messages must describe actual scaled damage. | Restore the original Thief greeting and retain actual committed damage in magic presentation/activity messages. |
| 45F merchant gives only 2000 HP in backside | The flat 2000 addition is directly present at `0x44E3D7`. Missing scaling is plausible, but treating it as a correction changes the tower economy and routes. | Retain 2000 HP for 1000 gold in every cycle. A once-only trade regression covers cycles 1, 2 and 3. The upstream 88000-HP trade is an explicit alternative, not assumed original behavior. |
| BGM/WAV options restored from a save | Settings behavior, separate from combat or hidden events. | Rust UI preferences are stored separately from engine saves; loading progress does not import original Delphi settings. |
| Prologue option, faster timers, tweening, keyboard delay, colors, window placement, shortcuts and loading during scenes | Presentation and usability changes; they do not establish additional tower events. | Use the shared Rust UI, ordered timelines, independent settings and modern timing. Original exact timer latency and all tswKai keyboard shortcuts are not reproduced. |

## Hidden mechanics and additional restored branches

Opposing Magic Sergeants/Sorcerers remove the larger half of current HP when
the hero commits a step between them. The original half-HP handler
`0x4541CE..0x4541DF` directly produces `1000 → 500`, `1001 → 500`, and `1 → 0`.
Native scenarios cover both axes, incorrect single/diagonal/L-shaped patterns,
rejected movement, Sacred Shield, and a later lower shield replacing its visible
slot. Magician neighbor damage remains additive and scales with the backside
multiplier.

The 39F three-o'clock yellow-door pattern is an original hidden event.
The EXE calls `doorcheck` on refused openings too: opening either hand with the
last key and bumping the other with zero keys reveals Warp Staff at `(3,3)`.
The second door remains closed and the hero stays outside. The ordinary
two-key solution still works in both orders. The reward is tile 43 with three
charges. Original-derived scenarios cover both routes, save/restore, absence
of duplicates and invalid extra clock openings. The same handler also arms
43F's trap on a no-key contact; its next road entry activates the trap.

The comparison uncovered a missing **second-cycle 50F ambush** in this remake.
With legitimate portal and cycle flags, the original queue moves Zeno
`(5,4) → (5,5) → (5,6)` and queues an enemy-first battle at the final square.
The translated event now preserves that branch and its ending trigger. His
normalized second-cycle HP/ATK/DEF are `1000/625/125`, resolved as
`44000/27500/5500`. Third and later cycles retain ordinary contact combat and
the current shared row, normally `8000/5000/1000`, resolved as
`352000/220000/44000`. Our earlier fixed-row contact preparation incorrectly
erased a seal applied after the gate. The 49F handler actually divides current
stats once per active seal; the gate clears the flag and multiplies them back.
Gate → seal → wing return therefore keeps `800/500/100` in later cycles.
Seventy-two chained EXE scenarios and gameplay routes cover the two orders,
resealing after gate restoration, cycles 1–4, truncation, and save/restore.
This includes delaying the actual 49F decoy fight until after gate entry:
the original seal arithmetic precedes corner removal for loot, while the
reward queue replaces the seal speech. Those callbacks now share the same
floor-check stage so reward cleanup cannot erase that re-seal.

Dynamic gates exposed an independent animation issue: an extracted tile-reveal
record could say its starting tile was road even after an earlier event closed
the gate. Execution now takes `from_tile` from the current map. Native 33F
scenarios and a rendered gate test with an intentionally stale header verify
that the opening starts from the actual closed gate.

## Coverage and boundaries

The original event audit checks all 51 initialized floor records and every one
of the 56 initialized special-road sites. All have configured events. It also
enumerates direct callers of the event dispatcher, scene builder, post-combat
handler and movement hazard helper, so stairs and ordinary movement are visible
as separate entry paths. The campaign now has 106 events and retains previous
event IDs. Coverage includes the restored 32F/42F stair scenes,
guarded rewards, capture, thief branches, staged bosses, 23F closing walls,
30F/33F traps, all thirteen
40F forced battles, clock doors, hidden NPCs, caster gates, 49F sealing/decoy,
princess/time-gate eligibility, and cycle-specific endings. Alternative trigger
positions extend coverage without invalidating old event IDs.

The animation audit separately checks twelve tile modes, altar eyes, all sixteen
wall-collapse frames, bomb/magic queues, post-combat branches on all 51 floors,
and four scripted-wall sites. GUI pixel tests verify doors, altar eye changes,
both pickaxes, bomb dissolution, dynamic gates and alternating impact phases.
GUI scenario checks cover magician movement, recovered scene sequences and
migration from published campaign/save revisions; native scenarios cover the
scripted-wall triggers and ordered effects. Engine saves and private MCP runtime
checkpoints retain the typed action timeline and progress.

The queue probes skip and report GUI/audio calls; they do not execute a complete
Windows gameplay session. Exact original timer latency, fairy score/rank tables,
fairy automatic checkpoint files, exact ending raster artwork, and a natural
complete first-cycle route remain separate fidelity work. The upstream artwork
also changes some Octopus cells; those differences were not imported without a
separate interpretation. The earlier audit missed the floor-32 Golden Knight
because he is absent from the initialized map: `handan` at `0x444E8B` calls
`mevent` and `ichicheck` immediately after the first upward stair arrival.
The recovered branch creates him, queues thirteen approach moves and an
enemy-first battle; its post-combat handler queues thirteen retreat moves and
returns the Thief from floor 29 to floor 2. The adjacent stair branch at
`0x444EAF` also restores floor 42's Zeno/Knight execution scene. The audit now
checks these callbacks with their once flags both unset and set, their helper
materialization masks, and floor 40's existing five-move Knight retreat.
Magic queue operands also retain their actual underlying sprite: the floor-42
execution overlays the Knight, and Zeno's time-gate appearance overlays the
Thief rather than road.
Floor 47's ordinary-movement hazard helper is recorded separately from these
stair callbacks and special-road sites. This audit therefore does not claim
every dynamically reachable map state is proven or that all tswKai QoL features
have been ported.
