# Tower of the Sorcerer

C++ remake and Delphi source recovery for the English **Tower of the Sorcerer
for Windows 1.2** by Oz & Kenichi.

This project is largely AI-generated. AI agents perform most implementation and
recovery work. I provide technical direction and look for unslop opportunities.

[Download the original English game from Vector](https://www.vector.co.jp/soft/win95/game/se093259.html).

| Project | Focus | Start here |
|---|---|---|
| C++ | A faithful rewrite with bug fixes and quality-of-life improvements | [Build, run and controls](cpp/README.md) |
| Delphi 2 | The most faithful readable recovery of the TSW 1.2 source, targeting routine-level byte equivalence | [Recovery status, build and tools](delphi/README.md) |

## Documentation

- **Playing and building:** use the implementation READMEs above. The C++ README
  also links to its [replay/CLI](docs/replay-verification.md),
  [MCP](docs/cpp-mcp.md) and [fidelity](cpp/FIDELITY.md) guides.
- **Game rules and formats:** [mechanics](docs/mechanics.md) and
  [original data and recovery](docs/original-data.md).
- **Source evidence:** [decompilation](reference/original/README.md) and
  [Delphi compiler reference](reference/delphi2/README.md).

The [research tools](tools/) extract game data, run Ghidra decompilation, and
compare recovered routines with the original executable. Follow the
[research setup guide](docs/research-cache.md) to run them against your TSW 1.2
installation.
See [attribution](THIRD_PARTY.md) for original-game and dependency notices.

## Special thanks

Special thanks to **Lisa Li's father**, who helped me solve the puzzles on the
last ten floors when I was in third grade.
