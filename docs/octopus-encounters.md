# Original Giant Octopus encounter evidence

This audit reads the installed English Tower of the Sorcerer for Windows 1.2
executable at `D:\Program Files (x86)\Tower of the Sorcerer\TSW.exe`. Its SHA-256
is `41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779`.
The installation was not modified or launched.

## What the player actually fights

The Giant Octopus occupies nine map cells. The first-frame tile IDs form this
3×3 layout:

```text
97   98   99
100  101  102
103  104  105
```

**Tile 104, the bottom-center cell, is the whole-creature encounter. The other
eight are individual body-part encounters. Every one uses the same full combat
stats; only the reward and cells removed differ.** The monster-table row at
`0x489910 + 18 × 16` contains **1,200 HP, 180 ATK, 20 DEF, 100 gold**.

| Contacted map tile | HP / ATK / DEF | Reward | Successful battle removes |
| --- | --- | --- | --- |
| 97–103 or 105 | 1,200 / 180 / 20 | 50 gold | Only the contacted cell |
| 104 | 1,200 / 180 / 20 | 100 gold | All nine cells |

Lucky Gold doubles those rewards to 100 and 200 respectively. The body-part
reward is integer-halved before applying Lucky Gold, so an edited odd raw
reward would round down before multiplication. The backside tower scales all
three combat stats by 44 while leaving the reward unchanged: 52,800 HP,
7,920 ATK, 880 DEF, and still 50 or 100 gold before Lucky Gold.

Defeating one body part does not weaken the remaining parts, preserve a shared
remaining HP value, or reduce the later whole-creature encounter. Each contact
starts another full fight against row 18. For example, a hero with 420 ATK and
100 DEF takes three strikes to deal 1,200 damage; the two counterattacks cost
160 HP. That cost applies to a body part as well as to the whole creature.
Fighting tile 103 and then tile 104 therefore costs two such fights and yields
50 + 100 gold, with the second fight finally removing the remaining octopus.

Only the bottom-center victory queues the whole-creature drawing operation.
The original writes road into all nine locations unconditionally; it does not
filter them by their current tile ID. In the authored floor the footprint
contains only octopus cells or cells cleared in an earlier body-part fight.

## Executable branches and independent probes

The ordinary movement dispatcher `handan` selects `taisen` for octopus cells at
`0x4445ad..0x4445b3`, via `0x448fa0`. The battle builder at `0x44a480` selects
sprite marker `0xd8` for tile IDs 97–105 (`0x44a506`), then subtracts `0xc6`
to select monster-table row 18. It reads full scaled HP at
`0x44a5a6..0x44a5be`. Its calculation helper `0x450064` delegates hero-strike
count to the recursive ordinary helper `0x45031c`; there is no octopus limb
HP/ATK/DEF adjustment in those calculations.

After queuing the ordinary reward, the tile-specific branch at
`0x44ab6e..0x44aea2` halves it for 97–103 and 105. Tile 104 bypasses the
halving. The reward queue handler at `0x452deb..0x452e04` multiplies that queued
value by `Lucky Gold + 1` and adds it to hero gold. This avoids the mistake of
calling a synthetic input value of 300 the octopus's actual base reward: the
installed row's actual base reward is 100.

The queue builder initially schedules one map write for the contacted cell.
For row 18 it tests **tile 104 exactly** at `0x44aeea..0x44af01`, replaces that
write, and adds the other eight writes at `0x44af07..0x44b0e1`. Opcode 17's
handler at `0x4541a9..0x4541c5` performs the actual map-byte writes. The same
tile-104 test changes the first battle-overlay operation to opcode 14 at
`0x44b3f1..0x44b415`. Opcode 14's handler calls `takowork1` (`0x4548a0`) and
`takowork2` (`0x454a58`), which draw road into the other eight locations of the
two animation buffers; these are visual operations, rather than additional
combat calculations.

Run the reproducible read-only audit:

```powershell
python tools/audit_original_octopus.py
python tools/audit_original_octopus.py --check
```

The report is saved as
[original-octopus-evidence.json](../data/original-octopus-evidence.json). The
script executes 34 encounters plus 18 atlas-ID dispatcher/mapping probes:

- All nine first-frame cells, with and without Lucky Gold.
- Bottom-row cells under backside scaling, with and without Lucky Gold.
- Whole-creature and other-body-part encounters after a previous part is gone.
- An attack blocked by enemy defense, and a fatal fight.
- An edited odd gold reward of 101, verifying integer division before Lucky
  Gold through the actual queued reward handler.
- Every ID from 97 through 114 at the dispatcher and stat-row mapping boundary.

The encounters execute the real `handan`, `taisen`, recursive arithmetic
helpers, and the coordinate-write fragment of `idou`. They then execute the
actual opcode 4/5 HP handlers, opcode 7 gold handler and opcode 17 map handler
in original queue order. Each report lists followed calls, skipped calls,
bypassed visual/string paths, queue counts, final HP/gold, and actual map
changes. Assertions check the stated stats, damage, reward and clearing.

Windows drawing, strings, timer scheduling, unrelated movement-hazard
callbacks and opcode-11 quest callbacks are not executed. The audit is an
isolated branch replay, not a live Windows playthrough. The full rendering
sequence and post-combat quest logic need their own evidence if changed.

## Alternate frames and a separate movement finding

Tiles 106–114 are the corresponding alternate animation pictures. Original
floor map bytes contain IDs 97–105; the renderer adds nine when drawing its
second buffer. The old combat routine **does not normalize 106–114 to
97–105**. Directly injecting such an alternate frame into its map dispatches
to battle but leaves the sprite marker stale, producing an invalid row in a
clean probe. That is not evidence for nine more valid encounter types. The
Rust editor may treat them as inert decoration or explicitly normalize them
as an editor convenience; neither should be described as the original map
representation.

The probe also corrects an earlier animation-audit interpretation: `taisen`
calls `idou` once the base attack penetrates enemy defense, **before checking
whether total battle damage is fatal**. A fatal original encounter consequently
moves the hero onto the enemy cell, although it queues no reward or map clear.
An attack that cannot penetrate defense keeps the approach position. This
finding is distinct from the body-part reward correction.

## What the original Hero Orb list reveals

The stock executable's Hero Orb list **does not explain the extra part
rewards**. Its current-floor scanner at `0x481753..0x481819` selects octopus
row 18 only when it sees **tile 104**. It skips the other eight octopus tiles,
97–103 and 105. The row builder at `0x44f26c` deduplicates by monster-table
row and shows the monster name, scaled **Life, Offense, Defense**, and
**Expected damage**. It does not display a gold reward column. These English
labels are original form strings 214, 215, 216 and 184, respectively.

The numeric row builder reads the HP/ATK/DEF table fields and calls the
ordinary strike-count helper through `0x44ff0c`. With hero attack 420 and
defense 100 it submits 1,200, 180, 20 and 160 to the original integer-to-string
routine. Changing Lucky Gold or changing the octopus's raw reward from 100
to 101 changes none of those four values. The replay records no reads of the
row's gold field. Because parts use the same combat stats, the 160 damage is
also their actual damage in that example, but the original list provides no
separate part row or indication of the 50-gold reward.

Run the focused reproducible audit with:

```powershell
python tools/audit_original_octopus_forecast.py
python tools/audit_original_octopus_forecast.py --check
```

Its [forecast evidence](../data/original-octopus-forecast-evidence.json)
contains eleven scanner probes, five numeric row probes, and labels extracted
directly from the installed executable. The probes execute the scanner,
row-construction control flow and recursive combat arithmetic, while skipping
and listing Windows drawing, string, allocation and control calls. This is
evidence for the original list's selected rows and submitted numeric fields,
not a screenshot or a live GUI run.

The researched `tools/research/monsters.rb` belongs to **tswKai3**, an external
enhancement. Its detailed hover/status-bar formatter explicitly halves
octopus-part gold, but that is a richer mod interface, not the stock Hero Orb
list in this installation. The remake likewise provides richer per-cell
forecasts with actual gold rewards. It retains its configured 50/100 reward
distinction instead of copying the original list's omission.

## Configuration boundary for the remake

The encounter distinctions now belong to per-tile configuration, rather than
to a special case on the enemy name. The eight body-part definitions set
`reward_divisor: 2` and have no footprint. Tile 104 retains the full reward and
owns the 3×3 footprint with `clear_all: true`, reproducing its unconditional
road writes. Other footprints retain their existing tile-ID filter by default.
`reward_divisor` must be a positive integer on an enemy tile; an omitted divisor
or explicit 1 has the same canonical serialization. Invalid/null/fractional
values are rejected before gameplay.

Shared tile inspection, current-floor Hero Orb forecasts and battle execution
resolve the same tile-adjusted enemy reward before Lucky Gold. All nine cells
share full scaled stats and the ordinary battle formula. A custom campaign can
use any positive divisor with any enemy row; the behavior does not depend on
the original octopus name or tile ID. The original extractor regenerates these
same definitions.

[octopus.rs](../crates/tos-core/tests/octopus.rs) checks all nine contact cells
with/without Lucky Gold, repeated part then whole-creature fights, save/load,
the backside and odd-reward rules, generic custom enemy/divisor execution,
configuration validation, unconditional footprint writes and blocked/fatal
encounters. These are scenarios on the imported original floor, not a claim
that an agent has completed an unassisted campaign.
