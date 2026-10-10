# Tower of the Sorcerer

Implementations and source recovery for the English **Tower of the Sorcerer
for Windows 1.2** by Oz & Kenichi.

The Delphi 2 project aims for a faithful recovery of the game. C++ is an
architecturally similar rewrite with the same core game logic, plus new
features and quality-of-life improvements. Rust is an independent rewrite.

| Implementation | Start here |
|---|---|
| Delphi 2 recovery with VCL forms and MCI audio | [Build, run and tools](delphi/README.md) |
| C++23 rewrite, desktop UI and headless CLI/MCP | [Build, run and controls](cpp/README.md) |
| Rust rewrite with desktop/browser UI and campaign editor | [Build and run](rust/README.md) |

| Guide | Contents |
|---|---|
| [Architecture](docs/architecture.md) | Modules and implementation decisions |
| [Mechanics](docs/mechanics.md) | Nonobvious game rules and retained quirks |
| [Data formats](docs/original-data.md) | Maps, assets, saves and rankings |
| [Fidelity](cpp/FIDELITY.md) | Known differences and verification limits |
| [Replay and CLI](docs/replay-verification.md) | Recording, playback and assertions |
| [MCP](docs/cpp-mcp.md) | Tools, observations and worker hot reload |
| [Recovery tools](docs/reverse-engineering.md) | Extraction and comparison workflow |

Recovered evidence lives in `reference/`; shared content in `data/`; research
tools in `tools/`. Builds, dependencies, reports and packages go under ignored
`build/`. Development reads the game installation without modifying it.
Decompiled exports are evidence, not the authors' source. See
[attribution](THIRD_PARTY.md).
