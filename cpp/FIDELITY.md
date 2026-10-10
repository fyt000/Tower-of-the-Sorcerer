# Fidelity scope

C++ is an architecturally similar rewrite of the Delphi 2 game, retaining its
core logic while adding features and quality-of-life improvements. Comparisons
check the English **Tower of the Sorcerer 1.2** gameplay decisions, state writes
and command order. Its source derives from recovered Delphi code and assembly,
independently of Rust. [Recovery](../docs/reverse-engineering.md),
[architecture](../docs/architecture.md) and [mechanics](../docs/mechanics.md)
describe the evidence, implementation and nonobvious rules.

## Current evidence

- [Whole-program accounting](../reference/original/whole-program/REVIEW.md)
  inventories code/resources, exports and unresolved ranges. Freshness guards
  establish provenance, not behavioral equality.
- Isolated x86 handlers are compared with the compiled C++ probe. Flight cases
  carry state across callbacks; reports list skipped callees. Unread stale
  `b` operands in HeroStrike/Reward are normalized. The
  [Flight audit](../docs/fidelity-audit-2026-10-09.md) documents its entry/redraw rules.
- Core, replay and MCP tests execute complete queues, long/fatal fights,
  attackable tile variants, dialogue aliases, saves, rankings, cycles and
  gate/seal/wing paths. Time Gate animation and interaction metadata are
  checked against Pascal source.
- Presentation and asset checks cover decoded pixels, masks and scene stages.
  Audio checks render complete tracks, looping and overlapping effects;
  Debug heap hooks require allocation-free prepared rendering. Device tests
  cover initialization, control and shutdown, not audible equivalence.
- Window tests check resize, maximize/restore, framebuffer resolution, font
  detail and pointer mapping. Desktop smoke tests cover pauses, saves and
  ending playback, including an installation with only supplied media.
- Save comparisons cover writer output, wrapping checksums, raw Fairy
  records, load reconstruction, opaque words and invalid records. File I/O
  and VCL calls are mocked; no historical player saves were available.

These are scoped checks, not proof of every branch, pixel, timer duration,
Windows event-delivery path or a full natural campaign. The
[presentation/input review](../reference/original/presentation/REVIEW.md)
distinguishes recovered entries from behavior and framework coverage.

## Correction-log policy

The [tswKai correction log](https://github.com/Z-H-Sun/tswKai/wiki/1.1-%E2%80%90-Run-TSW-Game#corrections-log)
and [patch descriptions](https://github.com/Z-H-Sun/tswKai/wiki/1.2.1-%E2%80%90-Patch-Config#features)
identify cases to investigate. Comparisons use the pinned unpatched executable.
Gameplay quirks remain; memory corruption and audio scheduling faults are
contained. `tools/verify_quirks.py` records those comparisons; optional
tswKai gameplay patches are not enabled.

| Case | Retained behavior or explicit exception |
|---|---|
| 33F trap | Only the upper cell triggers it; entering after clearing guards from below still seals exits. |
| 47F Magician A | Hero-row guard and flat-array horizontal wrapping remain. Index 121, which aliases the next floor landing byte, is rejected. |
| Backside 45F Merchant | Gives unscaled 2,000 HP for 1,000 gold. |
| Sealed Zeno load | Keeps the shared-row reconstruction and extra scaling in the [save specification](../docs/original-data.md#original-saves). |
| Enemy-first Lucky Gold | Income doubles. C++ completion text shows credited gold; Delphi displays the undoubled amount. |
| 40F boss / 50F Thief / backside text | Yellow-door prompt and speech/message IDs remain; VCL positioning differs. |
| Magician A mask | Bitmap pixels remain unchanged; no one-pixel correction. |
| 49F summon | 128 written commands execute. The cursor increment at `0x4637DD` exposes an unwritten stale 129th record, explicitly excluded. |
| Combat overflow / closely spaced audio | Bounded turn generation and cached overlapping voices replace unsafe buffer/scheduling behavior; see [architecture](../docs/architecture.md). |

## Deliberate differences and remaining work

- C++ accumulates forecast damage in 64 bits. At extreme backside values,
  Delphi wraps to signed 32 bits and may admit combat from a negative total;
  C++ uses the wider total for that decision.
- raylib/miniaudio replace VCL rendering, input and device interaction.
  Assets, masks, proportions and scene stages remain; overlays, fonts,
  settings and timing differ. TinySoundFont/GeneralUser GS changes MIDI
  timbre relative to Windows MIDI; uninterrupted playback on every device is
  unverified.
- Hero Orb display omits Cross/Dragon Slayer bonuses while combat includes
  them. **Hero Orb actual damage** optionally uses combat arithmetic, defaults
  off and is a desktop preference outside saves/replay inputs. Item/Orb modal
  gates remain enforced for file actions and Flight.
- Saves retain the 6,957-byte format and raw `save0.dat` checksum words.
  Validation, backups, independent manual/quick/Fairy files and writing Fairy
  checkpoints after completed scenes are application decisions. Manual slots
  use `Savedat/save1.dat`–`save8.dat`, or an explicit save directory.
  Checksums omit map bytes and final hero words; no extension is added.
- Rankings use five compatible 288-byte numeric tables and separate ten-line
  name files, with complete defaults on invalid data. They survive slot loads;
  sparse replay records preserve ranking-dependent decisions. The numeric/name
  pair is written sequentially: failure on the second file can leave mixed data.
- Legacy settings are not imported. Runtime mute persists across loads
  independently of saved music state. Imported idle words 608/612 survive
  without advancing the legacy wall clock; arbitrary-idle byte equality is
  unverified.

Reports live under ignored `build/cpp/`; packages include their evidence.
`tools/verify_original.py` requires current source accounting and rejects
unknown/effectful skipped callees through `comparison_boundary.py`.
Its direct-write scan does not establish absence of aliased or transitive
effects. Packaging checks probe/report hashes.
