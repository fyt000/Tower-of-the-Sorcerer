# Tower of the Sorcerer

Implementations and source recovery for the English **Tower of the Sorcerer
for Windows 1.2** by Oz & Kenichi.

| Project | Focus | Start here |
|---|---|---|
| Delphi 2 | Closest reconstruction of the original game | [Build, run and tools](delphi/README.md) |
| C++ | Desktop UI, headless CLI/MCP and quality-of-life features | [Build, run and controls](cpp/README.md) |
| Rust | Desktop/browser UI and campaign editor | [Build and run](rust/README.md) |

## Documentation

- **Playing and building:** use the implementation READMEs above. The C++ README
  also links to its [replay/CLI](docs/replay-verification.md),
  [MCP](docs/cpp-mcp.md) and [fidelity](cpp/FIDELITY.md) guides.
- **Game rules and formats:** [mechanics](docs/mechanics.md) and
  [original data and recovery](docs/original-data.md).
- **Source evidence:** [decompilation](reference/original/README.md) and
  [Delphi compiler reference](reference/delphi2/README.md).

Shared content lives in `data/`, research tools in `tools/`, and generated
output in ignored `build/`. The original installation is read only.
See [attribution](THIRD_PARTY.md) for original-game and dependency notices.
