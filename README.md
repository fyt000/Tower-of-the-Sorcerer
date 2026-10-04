# Tower of the Sorcerer · Rust

A browser and terminal remake of the installed English **Tower of the Sorcerer 1.2** by Oz & Kenichi. A deterministic Rust engine powers the WebAssembly browser build, interactive CLI, JSON headless mode, and a stdio MCP server. The browser combines the original pixel art with a responsive modern interface.

The original installation is read only. The user's Cocos2d-x implementation is a reference and has not been copied into this project.

## Run the browser version

The Rust toolchain, `wasm32-unknown-unknown` target, Node dependencies, and Chromium test browser were installed on this machine. From this directory:

```powershell
npm run build
npm start
```

Open **http://127.0.0.1:8080**. Move with arrow keys or WASD; hover or tap a monster for its Rust-calculated damage forecast. The directional controls also work on touch devices. Progress automatically saves to browser storage. The game menu imports/exports portable saves and loads custom JSON campaigns.

**Save game** creates a separate checkpoint; **Restore saved checkpoint** in the game menu returns to it. Autosave preserves the current session independently, so reloading the page does not erase that checkpoint after a fatal battle.

The build produces `target/release/tos.exe` and `web/pkg/tos_wasm_bg.wasm`. The complete `web/` directory can also be hosted on any static web server with the `.wasm` MIME type `application/wasm`. No backend is required for browser play. Do not open `index.html` through `file://`; WebAssembly and campaign fetching require HTTP.

For another port: `npm start -- --port 8090`. Keep the server stopped while rebuilding its native executable on Windows.

On a fresh development machine install [Rust](https://rust-lang.org/tools/install/) and Node.js, then:

```powershell
rustup target add wasm32-unknown-unknown
rustup component add rustfmt clippy
npm ci
npm run build
```

The build script resolves the Rust binaries in the standard Cargo directory and installs the `wasm-bindgen-cli` version matching `Cargo.lock` if necessary. The local prebuilt binding generator speeds up builds on this machine.

## Native and AI interfaces

```powershell
.\target\release\tos.exe play
.\target\release\tos.exe state
.\target\release\tos.exe validate
.\target\release\tos.exe headless
.\target\release\tos.exe replay .\examples\opening.jsonl
.\target\release\tos.exe mcp
```

Native modes embed the campaign, so the executable can run outside the checkout. Use `--campaign PATH` to override it and `--save PATH` to restore a save. `tos --help` lists options. Interactive terminal play accepts WASD, `inspect X Y`, `choose ID`, `use ITEM [FLOOR]`, `save PATH`, and `quit`.

Headless mode reads one JSON command per line and emits the complete state after every command. For example:

```json
{"type":"move","direction":"up"}
{"type":"move","direction":"left"}
{"type":"choose","choice":"leave"}
{"type":"use_item","item":"flying_orb","floor":1}
```

The MCP server uses [standard newline-delimited JSON-RPC over stdio](https://modelcontextprotocol.io/specification/2025-11-25/basic/transports). Stdout contains only protocol messages. Its seven tools are:

| Tool | Purpose |
| --- | --- |
| `game_state` | Read map, stats, items, dialog, flags, and enemy forecasts |
| `inspect_tile` | Inspect coordinates and forecast combat without acting |
| `game_action` | Commit one move, response, cancellation, or item action |
| `simulate_actions` | Try a route on a copy; preserve the live session |
| `save_game` | Export a portable JSON save |
| `load_game` | Restore a matching save |
| `new_game` | Reset the session |

Resources `tos://state` and `tos://campaign` expose the session and configuration. Each server process owns one independent session. A typical MCP client entry is:

```json
{
  "mcpServers": {
    "tower-of-the-sorcerer": {
      "command": "D:\\projects\\tos-rust\\target\\release\\tos.exe",
      "args": ["mcp"]
    }
  }
}
```

## Configure the game

Edit `data/campaign.json`, then rebuild. The browser can also import another campaign without rebuilding. Floors, tile IDs, enemies, pickups, stat gains, altar rules, position-specific NPC offers, stair links, and event triggers/effects are data. See [docs/configuration.md](docs/configuration.md) for examples and the event model.

Saves preserve changed maps, event flags and counters, global altar purchases, pending interactions, visited floors, item charges, and staged enemy statistics. A stable campaign fingerprint rejects saves made for a different ruleset, avoiding silent corruption after configuration changes.

## Original data and fidelity

The repository includes 51 original 11×11 maps (floor 0 through 50), all 33 original monster stat rows, 268 original dialogue strings, 97 configured progression events, 41 position-specific NPC interactions, and extracted artwork. The extraction recognizes constant byte assignments in the Delphi executable without launching the original game. Source checksums, addresses, and confidence notes are retained in `data/extraction-manifest.json`, [docs/original-data.md](docs/original-data.md), and [docs/mechanics.md](docs/mechanics.md).

Ordinary combat preserves hero-first damage, the fatal equality boundary, Cross/Dragon Slayer multipliers and the original base-attack guard. Items use verified original behavior, including Elixir's `10×ATK + 5×DEF`, Warp Staff charges, same-coordinate wings, Lucky Gold, and the distinct bomb reward. Original progression is translated into persistent data-driven events; event evidence and remaining fidelity boundaries are recorded with the data. See the final verification notes in `docs/mechanics.md` before treating this as a proven byte-for-byte recreation of every original sequence or a verified full optimal playthrough.

To repeat asset/map/stat extraction from your installation:

```powershell
python -m pip install -r tools/requirements.txt
python tools/extract_original.py --source "D:\Program Files (x86)\Tower of the Sorcerer"
```

The extractor preserves an existing edited campaign. Its explicit `--regenerate-campaign` flag resets the campaign to extracted defaults. Event and NPC configuration files are maintained separately and merged by the extractor where supported.

## Verify

```powershell
cargo test --workspace
cargo clippy --workspace --all-targets -- -D warnings
npm run build
npm run test:mcp
# With npm start running in another terminal:
npm run test:browser
```

Browser tests use headless Playwright Chromium, with no desktop/computer-use automation. They exercise real WebAssembly, keyboard and touch inputs, damage forecasts, NPC choices, keys, persistence, save files, custom campaigns, and invalid imports. Screenshots are written to `test-results/`.

The MCP integration test also drives 46 actual opening actions through the protocol, verifies the original capture and escape, and records `examples/opening.jsonl`. It replays those same actions through CLI replay and JSON headless modes and compares the resulting player state. Native late-game tests isolate boss and ending transitions with scenario saves; they are separate evidence from a complete unassisted tower solution.

## Layout

| Directory | Responsibility |
| --- | --- |
| `crates/tos-core` | Platform-independent deterministic game rules and save validation |
| `crates/tos-wasm` | Small WebAssembly binding around the same engine |
| `crates/tos-cli` | Terminal, JSONL, replay, MCP, and local web server |
| `web` | HTML/CSS and canvas presentation; no duplicated game rules |
| `data` | Editable campaign and extracted original evidence |
| `tools` | Repeatable extraction and build helpers |
| `tests` | Browser and MCP integration checks |

Rust/JavaScript code written for this remake is MIT licensed. Original game assets, dialogue, and map data remain the work of Oz & Kenichi and are excluded from that license. Bundled fonts use the SIL Open Font License; their licenses are in `web/fonts/`. See [THIRD_PARTY.md](THIRD_PARTY.md).
