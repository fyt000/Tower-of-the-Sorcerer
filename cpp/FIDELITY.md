# C++ fidelity

[Mechanics](../docs/mechanics.md) records retained rules and quirks;
[data and recovery](../docs/original-data.md) describes the comparison workflow.

## Deliberate differences and remaining work

- raylib rendering and synthesized MIDI replace VCL and Windows MCI. Original
  assets and scene stages remain, but overlays, fonts, settings, timing and
  MIDI timbre differ.
- C++ uses 64-bit forecast damage. The original wraps signed 32-bit arithmetic,
  which can change combat admission at extreme values.
- Bounded combat queues and bounds checks contain unsafe memory behavior.
  The 49F summon executes its written commands and omits the cursor increment
  that exposes an unwritten stale command in the original.
- **Hero Orb actual damage** optionally includes Cross/Dragon Slayer bonuses
  in forecasts. It is off by default and is a desktop preference.
- Mouse walking is opt-in (default: off), routes through apparent floor and contacts only the clicked
  event. Hidden floor triggers remain concealed and stop the route when reached;
  doors and hidden walls receive one contact per click. Steps use native movement
  handlers and replay inputs.
- **Realtime Hero Orb** is opt-in (default: off). Owning the Orb unlocks compact
  on-map monster stats and forecasts, following the actual-damage preference.
  This changes presentation only; hovered values remain exact.
- Saves retain the original format, with validation, backups and separate
  manual, quick and Fairy files. Fairy checkpoints are written after their
  scenes complete. Rankings persist independently of game saves; their numeric
  and name files are written separately.
- Legacy preferences are not imported. Mute is independent of saved music
  state, and the legacy idle clock is not advanced.

## Verification

Original-handler comparisons check gameplay decisions, state writes, command
order and saves against the pinned, unpatched executable. Composed Flight
comparisons carry state between callbacks and include redraw effects. Skipped
calls and execution boundaries are recorded in generated reports.

Core, replay and MCP tests exercise input sequences and persistence. Separate
presentation, asset, window and audio checks cover those systems. Run audio
checks only for audio-related changes, following the repository test rules.

These checks do not establish complete branch coverage, pixel or audible
identity, Windows event timing, or every natural campaign sequence. Decompiler
inventories establish what was recovered, not behavioral equality.
Reports stay under ignored `build/cpp/`; packaging checks their freshness.

Native-input campaign recordings and their expected results are checked in
under [tests/replays](../tests/replays/first-cycle-seal.md). The optional
[planner verifier](../docs/route-planner.md#commands) replays those fixtures
and checks the complete seal challenge.
