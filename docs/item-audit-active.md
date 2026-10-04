# Active-item audit against the installed original

Audited on 2026-10-04 against the user's English Tower of the Sorcerer for Windows 1.2 at `D:\Program Files (x86)\Tower of the Sorcerer`. The installation was read without launching or modifying it. The executable SHA-256 was independently rechecked:

```text
41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779
```

This report covers the ten active special items. The three orbs and twelve further special items total fifteen; Sword and Shield occupy two additional original inventory slots. Passive-item and Wisdom audits are separate. These are developer-facing evidence notes and can contain details deliberately omitted from owned-item help.

## Sources and confidence

The installed `TSW.txt` special-items section and the recovered `Tsw.hlp` topics introduce Flight Orb, Mattock, Elixir, Destruction Ball and Warp Staff. They describe broad intent, omit several other items, and do not establish exact bounds, eligibility or failure consumption. The raw extracted help is retained in [original.json](../data/help/original.json); source checksums and extraction are documented in [original-help.md](original-help.md). The manual describes Warp Staff travel vaguely, whereas executable instructions establish a deterministic mirror.

Exact rules below come from disassembly of the installed executable with `pefile` and Capstone, and selected isolated Unicorn probes based on [original_event_probe.py](../tools/original_event_probe.py). Addresses are executable virtual addresses. The recovered research/mod files were useful for finding routine names, but the conclusions were checked against the installed binary rather than assuming modified routines had original behavior.

**High confidence** means direct instructions establish the stated rule, supported by isolated probes where noted. Probes stopped at `0x451B42`, before the Delphi use-handler cleanup. For neighbor tests they followed classifier `0x451C20`, Mattock queue helper `0x451B98`, Bomb queue helper `0x44BC34`, and Snow queue helper `0x451D3C`. GUI, string construction, audio, rendering and animation helpers were skipped. Queue inspection proves targets and writes; it does not prove the complete Windows UI, rendering timing or all quest interactions were reproduced.

## Item-by-item comparison

| Item | Installed original and direct evidence | Finding and current result |
| --- | --- | --- |
| Flight Orb | Reusable; initiation checks four adjacent cells for a staircase at `0x481ED6..0x481F59`. Selectors stay between floor 1 and the dedicated highest-stair counter (`0x4B869C`), at `0x44ED1F..0x44ED8F` and `0x44ED97..0x44EE42`; they skip floor 44 at `0x44ED32..0x44ED43` and `0x44EDB2..0x44EDC3`. Directional landing uses the two floor-header bytes at `0x44EBB4..0x44EBF7`. Choosing the unchanged floor without an arrow leaves the original position because direction zero bypasses that landing block. | **Fixed:** the remake previously allowed any individually visited floor, including 0/44, and moved the hero to a stair landing even on an unchanged destination. Original mode now publishes the actual supported floor list, uses a saved stair counter, excludes 0/44, and preserves coordinates on an unchanged floor. Verified selector world updates now use the authored callbacks below. Confidence: high for these selection and landing rules. |
| Magic Mattock | Four immediate cardinal neighbors only, at `0x450DFF..0x450F20`. Each is classified by `0x451C20`; class 1 is assigned only to original tile 8 at `0x451C46..0x451C7E`. The item slot is cleared unconditionally at `0x450F27`. | **Fixed:** previously any semantic wall could be removed, including scripted walls and creature body cells, and an empty use retained the Mattock. Original campaign now permits only tile 8 and always consumes it after use. Custom campaigns retain configurable semantic walls. Confidence: high. |
| Destruction Ball / Bomb | Four immediate cardinal neighbors, not diagonals, at `0x450FDA..0x451115`. Eligible families are tile ranges 61–90, 93–96, 133–144 and 147–158 in classifier `0x451C20..0x451D39`. Gold reads the raw monster-table reward (`0x48991C + 16 × row`) at `0x45101D..0x45102B` and analogous neighbor blocks. The item clears at `0x451127`. Its queued `(11,5,0)` later invokes post-combat checking at `0x4533E4..0x4533F6`. | **Fixed:** previously the entire surrounding 3 × 3 area was affected and an empty use retained the Bomb. Current behavior affects only cardinal neighbors and consumes the Bomb even if none are eligible. Raw rewards without Lucky Gold or backside multiplication already matched. Large creatures are excluded by the classifier; no giant footprint should be partially removed by this item. Confidence: high. |
| Magic Elixir | `0x450D13..0x450D26` computes `10 × ATK + 5 × DEF`; `0x450D89..0x450D96` adds it to HP and clears the slot. No extra backside multiplier is applied to that result. | **Matched:** the remake uses the same formula and consumes the item. Its bounded/saturating statistic arithmetic is an explicit import/simulation guard rather than reproduction of arbitrary original 32-bit overflow. Confidence: high. |
| Warp Staff | Pickup assigns three charges at `0x445B16`. Use decrements before testing the destination (`0x4511B3`). Destination index is `120 - (11y + x)` at `0x4511C3..0x4511E0`, giving `(10 - x, 10 - y)`. Only road tile 6 is accepted (`0x4511F7`). Blocked travel leaves position unchanged after consuming the charge. | **Matched:** three charges, same-floor mirror, ordinary-passage landing and blocked-use consumption. The final charge removes the usable inventory entry in the remake; original availability checks positive charges at `0x482343..0x48234A`. Confidence: high. |
| Ascent Wing | `0x4513E4..0x451418` rejects floor 50 or a destination other than road 6 at identical coordinates on the next floor. The item clears only after the successful test and then increments current floor at `0x451427`. | **Matched:** move up exactly one floor, including floor 43 → 44; keep coordinates; consume only on successful ordinary-passage landing. Flight's highest-stair counter does not advance. Confidence: high. |
| Descent Wing | `0x451543..0x451589` rejects current floor 0 or a destination other than road 6 one floor down. `0x45158F..0x4515A0` consumes only after success and decrements current floor. | **Matched:** move down exactly one floor, including floor 1 → 0; keep coordinates; consume only on successful landing. Flight's highest-stair counter does not advance. Confidence: high. |
| Snow Crystal | `0x4516DE..0x45184F` checks only four immediate cardinal neighbors. Classifier class 3 is original lava tile 13 (`0x451C4B..0x451C4E`, `0x451D2F`). Helper `0x451D3C` queues a single `(17,index,6)` write per affected neighbor. Opcode 17 at `0x4541A9..0x4541C5` writes exactly that one cell; it does not recurse. The Snow Crystal slot remains unchanged. | **Fixed:** the remake previously flood-filled all connected lava. Current behavior cools only immediate cardinal lava and remains reusable. No adjacent lava leaves world and inventory unchanged. Confidence: high. |
| Magic Key | Clears its slot before scanning (`0x4518E8`). The whole floor is scanned from index 120 to 0 at `0x45194D..0x4519F0`, accepting only yellow-door tile 1 at `0x45196A`. | **Fixed:** door color/scope already matched; empty use previously kept the item. Current use consumes it even on a floor with no yellow doors and spends no ordinary keys. Blue/red doors and gate cells remain excluded. Confidence: high. |
| Super Magic Mattock | Clears its slot before scanning (`0x4519FD`). The whole floor is scanned at `0x451A62..0x451B3C`, accepting only wall tile 8 at `0x451A8A`. | **Fixed:** original wall scope already largely matched, but empty use retained the item and custom campaigns were coupled to tile 8. Current original mode removes only tile 8 and consumes even on an empty floor; optional wall ranges preserve custom wall IDs. Confidence: high. |

The original item-selection routines enable Mattock, Bomb, Magic Key and Super Mattock based on the ownership slot, without a target-availability guard. Relevant selectors begin at `0x482128`, `0x482234`, `0x482770` and `0x48287C`. Therefore the unconditional slot clears above represent reachable empty uses, not merely dead handler branches.

## Flight counter and transport context

The original highest-stair counter advances on normal ascent when the new current floor exceeds it (`0x444E0F..0x444E21`). Ordinary descent does not raise it (`0x444FA1..0x444FE3`). Both capture branches explicitly reset it to 2 at `0x4655EA` and `0x46565B`. The fresh tower initializes it to floor 1. Reaching another floor by a wing does not write this counter.

The remake now preserves `highest_stair_floor` in saves and runtime checkpoints, advances it only on normal ascent, resets it through the validated `set_highest_stair_floor` capture effect, and resets it with the tower for a new cycle. Legacy saves which omitted the counter use their highest visited floor as a compatibility approximation; they cannot reconstruct historical stair-vs-wing travel exactly. Original selection is enabled only by `rules.flying_original_selection`; custom campaigns without it keep their existing visited-floor semantics.

Owned-item help provides `allowed_floors` and refers to the selector without naming excluded hidden floors or puzzle solutions. The GUI uses that same list, and MCP receives the same item help. A source-based audit can state the exact exclusion while early-game player help preserves discovery.

The original Flight UI also performs world updates beyond ordinary destination/landing rules. The remake now defines a changed direct destination as the shortest monotonic sequence of original Up/Down selections followed by OK. The following verified callbacks are authored in `rules.floor_travel_callbacks`, validated and compiled at campaign import, and enabled with `flying_original_selection`. No original Flight cancellation operation has been established; its observed controls are Up, Down and OK. See [flight-context-audit.md](flight-context-audit.md) and [the executable probes](../tools/audit_original_flight.py).

| Context | Installed instructions | Current implementation and boundary |
| --- | --- | --- |
| Upward preview reaches floor 35 | `0x44EDDF..0x44EDF7` checks `F35(3,8) + F2(10,10) == 27` and changes F2(10,10) to road 6. | A successful upward direct jump crossing 35 applies the exact numeric guard. Downward travel does not. |
| Confirming after pressing an arrow | `0x44EB2B..0x44EB69` removes fairy tile 23 at F25(5,6) and/or F49(5,1) when the arrow-direction state is nonzero and selected floor is not that fairy's floor. It does not compare source and destination. | A changed destination applies these guarded removals. A same-floor command models OK without arrows. Original roundtrip preview paths are not exposed. This does not use the ordinary fairy interaction callback; score/checkpoint/rank behavior remains separate fidelity work. |
| Highest counter is 29 and confirmed destination is lower | `0x44EC04..0x44EC1E` clears F29(5,3) and F29(5,2), and places **Thief** tile 21 at F29(6,1). Normal downstairs has a related branch at `0x444FBC..0x444FDC`. | Changed Flight destinations below 29 with the exact stair bound 29 apply the writes. Normal stair descent 29→28 applies the same relocation. Wings do not. The broader F29/F35 thief interaction/digging storyline is still missing and is not supplied by these writes. |

These callbacks reproduce the directly verified control writes under the stated direct-destination model. They do not claim the missing F29/F35 thief storyline, arbitrary selector roundtrips, or fairy scoring/checkpoint behavior is implemented. [flight_callbacks.rs](../crates/tos-core/tests/flight_callbacks.rs) covers the upward selection interval and exact sum, fairy guard/exceptions, exact stair bound, normal descent versus wings, same-floor/rejected use, save/runtime preservation, malformed authored data, and player-observation secrecy.

## Isolated probe observations

The use-handler probes filled an isolated 11 × 11 floor with road 6, supplied deliberate neighboring tiles and inventory slots, and followed only the four audited gameplay classifiers/queue helpers. Installed files were never written.

| Probe | Observed original result |
| --- | --- |
| Elixir: HP 100, ATK 10, DEF 5 | HP became 225; Elixir slot became 0. |
| Mattock with adjacent IDs 8, 10, 9 and 98 | Only ID 8 passed class 1 and generated a removal/reveal queue; the item slot became 0. |
| Bomb with four cardinal Slimes and one diagonal Slime | Exactly four opcode-17 road writes, at indices 49, 59, 61 and 71 from hero index 60; raw Slime gold totaled 4; item slot became 0. |
| Snow Crystal with four cardinal lava cells plus connected distant/diagonal lava | Exactly four opcode-17 road writes at those same cardinal indices; Snow Crystal slot stayed 1. No distant/diagonal write was queued. |
| Warp Staff with blocked mirror landing | Three charges became two; hero position stayed unchanged. |
| Ascent Wing with clear landing | Floor 1 became 2, coordinates stayed (5,5), item slot became 0. |
| Descent Wing from floor 1 with clear landing | Floor became 0, coordinates stayed (5,5), item slot became 0. |
| Empty Mattock, Bomb, Magic Key or Super Mattock | Each respective item slot became 0 without an eligible map target. |

Skipped calls across these probes included Delphi strings (`0x403710`, `0x40369C`, `0x405B6C` and indirect string-list calls), control methods (`0x413500`), redraw/status/item controls (`0x442C38`, `0x44CB34`, `0x450880`), timer enabling (`0x44BC0C`) and visual blend building (`0x4660D0`). Bomb's raw reward writes, consumable clears, wing floor/position writes, and blocked Warp decrement were executed; full visual/event-queue playback was not.

To inspect a rule independently, use the same installed PE image rather than a differently patched executable:

```python
import capstone, pefile
pe = pefile.PE(r"D:\Program Files (x86)\Tower of the Sorcerer\TSW.exe")
image = pe.get_memory_mapped_image()
decoder = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
start, end = 0x4516AB, 0x4518E6  # Snow Crystal use branch
for instruction in decoder.disasm(image[start - 0x400000:end - 0x400000], start):
    print(hex(instruction.address), instruction.mnemonic, instruction.op_str)
```

The focused remake regression suite is [active_items.rs](../crates/tos-core/tests/active_items.rs). It verifies diagonal/distant exclusions, special-wall protection, empty consumption, configurable custom wall IDs, exact Flight input/selection, wings vs stair unlocking, same-floor landing, hidden-floor help secrecy, legacy/invalid save counters, runtime checkpoint preservation, and actual original capture in both first/backside cycles. [item_help.rs](../crates/tos-core/tests/item_help.rs) verifies command/help consistency, aliases, dynamic rules and script secrecy. These are transition tests rather than an unassisted full-game playthrough.
