# C++ fidelity

## Deliberate differences and remaining work

- raylib and synthesized MIDI replace VCL/MCI; fonts, overlays, timing and timbre differ.
- Manual direction repeat uses real time. Above 1x, effects consolidate duplicates and fade tails sooner.
- Forecasts use 64-bit damage; original signed 32-bit overflow can change extreme-value combat admission.
- Bounds checks and bounded combat queues contain unsafe original behavior. The 49F stale summon record is omitted.
- Mouse walking, Realtime Hero Orb and bonus-aware Orb forecasts are optional and default off.
- Saves keep the original format with validation/backups. Fairy checkpoints are written after the scene; rankings persist independently.
- Legacy preferences are not imported. Saved idle-animation counters are preserved but not advanced on the original clock.

## Verification

[Original-handler comparisons](../docs/decompilation.md#verification) check
state writes, commands and saves against the unpatched EXE. Core, replay, MCP,
renderer and asset tests cover their respective paths; reports stay in `build/`.
Packaging checks freshness. Follow [AGENTS.md](../AGENTS.md) for test scope.

These checks establish neither complete branch/campaign coverage nor pixel,
audio or Windows-timing identity. [Mechanics](../docs/mechanics.md) records
retained quirks; [replay fixtures](../tests/replays/first-cycle-seal.md) provide
campaign regressions. Passing a route does not establish optimality.
