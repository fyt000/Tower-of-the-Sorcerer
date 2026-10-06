# Tower of the Sorcerer

This repository has two independent implementations of the English **Tower of the
Sorcerer for Windows 1.2** by Oz & Kenichi.

Our current goal is a readable, reliable baseline of the original game. The
**C++20 implementation in `baseline/`** translates the decompiled Delphi logic,
keeps its branches and command order, and checks the result against the original
executable. It is the reference for future changes and features.

The **Rust implementation in `crates/`** is an earlier independent rewrite. Its
architecture remains in place for experiments such as replay and terminal play.
Agreement with the C++ baseline must be established through comparisons; Rust
campaign definitions are not the specification for the original game.

## Start here

- [Build, run and use the C++ game](baseline/README.md)
- [Game architecture and implementation boundaries](docs/architecture.md)
- [Decompilation target, source recovery and comparison workflow](docs/reverse-engineering.md)
- [Original data and asset formats](docs/original-data.md)
- [Preserved game rules](docs/mechanics.md)
- [Fidelity coverage and deliberate differences](baseline/FIDELITY.md)
- [Attribution and dependencies](THIRD_PARTY.md)

## Repository layout

| Path | Purpose |
|---|---|
| `baseline/` | Faithful C++ core, raylib desktop, tests and packaging |
| `reference/original/decompiled/` | C-like Ghidra exports, source index and call map |
| `reference/original/*.cpp` | Small reviewed examples of doors, Bomb and shared Zeno state |
| `tools/ghidra/` | Export and recovery scripts for the original executable |
| `tools/extract_original.py`, `data/` | Original constants and extraction evidence; Rust campaign data |
| `crates/` | Independent Rust engine and UI |
| `web/` | Rust browser launcher, local media and player help |
| `docs/` | Current architecture, original data, rules and research workflow |

The original installation is read only during development. Extracted media,
dependency downloads, build trees and distributions are local generated files
and are excluded from Git. Decompiled evidence is retained alongside the
compilable C++ implementation; it is not the original author's source code.

## Existing Rust setup

The Rust application remains available through the existing Node build scripts.
It requires Rust, Node.js and the WebAssembly target; the build scripts manage
the matching `wasm-bindgen` tool. From the repository root:

```powershell
npm ci
rustup target add wasm32-unknown-unknown
python -m pip install -r tools/requirements.txt
python tools/extract_original.py --source "D:/Program Files (x86)/Tower of the Sorcerer"
python tools/setup_assets.py
npm run build
npm run start:native
# Browser: npm start, then open http://127.0.0.1:8080/
```

`npm run editor` starts its campaign editor. `npm run check` runs the Rust checks;
`npm run test:browser` and `npm run test:mcp` cover the browser and MCP clients.
The Rust engine, editor and configurable campaign are separate from the C++
baseline's hard-coded original logic.
