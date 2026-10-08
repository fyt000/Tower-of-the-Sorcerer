# Tower of the Sorcerer

This repository recovers and reimplements the English **Tower of the Sorcerer
for Windows 1.2** by Oz & Kenichi.

The current goal is a readable, faithful C++ implementation of the original
Delphi game. Its core retains the original branches, loops, shared monster
state, callbacks and command order, with named types and constants. Decompiled
code and the unpatched original executable are the evidence. Gameplay quirks
are preserved; unsafe memory access and audio/rendering engine problems are
fixed. Future features can build on this reference.

The earlier Rust rewrite remains an independent implementation. Its architecture
is available for replay, terminal play and other experiments. It is not the
specification for the C++ game.

| Directory | Contents |
|---|---|
| `cpp/` | C++23 game, `tsw` namespace, Glaze replay serialization, raylib graphics, miniaudio device, TSF/TML music, Catch2 tests |
| `rust/` | Rust workspace, browser/native UI, Node tools and integration tests |
| `reference/original/` | Ghidra exports, source index and recovered UI evidence |
| `data/` | Shared extraction evidence and Rust campaign/localization data |
| `tools/` | Original executable/data extraction and Ghidra research tools |
| `docs/` | Game architecture, original formats, mechanics and research workflow |
| `build/` | Ignored C++/Rust builds, downloaded dependencies, reports, test output and packages |

Start with the [C++ build and controls](cpp/README.md),
[architecture](docs/architecture.md),
[decompilation and comparison workflow](docs/reverse-engineering.md), and
[fidelity coverage](cpp/FIDELITY.md).
[Original data](docs/original-data.md), [game rules](docs/mechanics.md), and
[attribution](THIRD_PARTY.md) cover the supporting details.
The C++ startup menu offers New game, Load game, Play replay and persistent
Settings using the original opening artwork. The
[replay recorder, visual playback and CLI](docs/replay-verification.md) support
recording C++ player actions, watching with pause/step/rewind/takeover controls
and checking explicit gameplay values with a separate test script.
The [native C++ MCP mode](docs/cpp-mcp.md) exposes player observations, inspection,
actions, original-format saves and replay import/export through `tsw_cli mcp`.
An optional Python bridge hot-reloads immutable C++ workers while preserving
the complete session, including open shops, Flight, recordings and checkpoints.

The original installation is read only during development and tests. Decompiled
exports are inspection evidence, not the author's original source. Local media
and packages are excluded from Git.

## Rust setup

Rust, Node.js and Python are needed for the earlier rewrite. From the repository root:

```powershell
python -m pip install -r tools/requirements.txt
python tools/setup_assets.py --source "D:/Program Files (x86)/Tower of the Sorcerer"
Set-Location rust
npm ci
rustup target add wasm32-unknown-unknown
npm run build
npm run start:native
# Browser: npm start, then http://127.0.0.1:8080/
```

`npm run editor` opens the campaign editor. `npm run check` runs Rust tests and
Clippy; `npm run test:browser`, `npm run test:native` and `npm run test:mcp` run
integration checks. Cargo output is in `build/rust/target/`; Node tools put
reports and packages in `build/rust/`. Extracted Rust media stays in
`rust/web/assets/`, and Node's installed dependencies stay in `rust/node_modules/`.
