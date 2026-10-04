# Tower of the Sorcerer · Rust

A Rust remake of the installed English **Tower of the Sorcerer 1.2** by Oz &
Kenichi. A deterministic engine powers the browser, native desktop GUI,
terminal, JSON headless mode and stdio MCP server. The game interface and visual
campaign editor are shared Rust code, using Eframe/Egui with WebGL in the browser
and OpenGL in the desktop window. Handwritten browser JavaScript is only a
startup loader.

The original installation is read only. The user's Cocos2d-x project has not
been copied into this implementation. The private development remote is
[fyt000/tos-rust](https://github.com/fyt000/tos-rust).

## Run

The toolchain, local assets and test browser are already installed on this
machine. From the checkout:

```powershell
npm run build
npm start
```

Open **http://127.0.0.1:8080/**. To launch the graphical desktop game or editor:

```powershell
npm run start:native
npm run editor
# Direct executable, including explicit language/content options:
.\target\release\tos-ui.exe --language zh-CN
.\target\release\tos-ui.exe --editor --campaign .\data\campaign.json
```

The native game includes the same map, inventory, journal, dialogue, animations,
audio, settings and editor as the browser. `--assets-root PATH` overrides the
folder containing `assets/` and `fonts/`; `--save PATH` imports a portable save.
The default campaign is embedded, so native play does not need a web server.

Use arrow keys or WASD, or click a destination on the
map. Click routes traverse clear road and stop at intervening obstacles. A
directly selected enemy, door, pickup, NPC or stair can be the final action;
the route never silently fights or opens obstacles on the way. Conversations
and floor changes interrupt the route. Walking accepts subsequent input without
an overlay or a direction-button panel. Conversations and choices appear inside
the game board. Enter/Space advances scripted dialogue;
**Skip animation** skips presentation while preserving the engine's result.

**Settings** switches English/Simplified Chinese, sound/music, volume and
animation speed. Browser audio starts after the first input. Original WAV
effects play directly; extracted MIDI is synthesized in Rust, with approximate
instrument timbres. Battles play `taisen.wav` on each actual hero or enemy strike,
with the impact pose and displayed HP calculation following that strike's phases.
The hero alternates the original walking poses while moving and returns to the
distinct standing pose after the next ambient tick. Monsters and NPCs alternate
their original sprite poses in the same cell. Stairs cover the outgoing floor
with crossed swords in the original spiral order, then reveal the incoming floor.
The floor-3 capture includes Zeno's apparition, the title-to-vortex transition,
the sacred-sword incantation, and the prison wake-up. The floor-10 guard march,
Vampire transformation and later scripted scenes use the same ordered engine
timeline in browser and native builds.

Detailed enemy stats and forecasts require the **Orb of the Hero**, received
from the floor-3 old man. Orb of Wisdom is a different item. This gate also
applies to CLI/MCP inspection and state snapshots.

Completing the first cycle automatically enters the backside tower. Hero
HP/ATK/DEF carry over unchanged. Applicable enemy and treasure combat stats,
altar gains and flat magic damage become **×44**; gold rewards and prices do
not. Cycle/reset/capture rules are configurable and backed by executable evidence.

For another server port, use `npm start -- --port 8090`. Stop a release server
before rebuilding `tos.exe` on Windows. To host elsewhere, deploy the complete
generated `web/` directory over HTTP, serving `.wasm` as `application/wasm`.
Browser play has no backend requirement. The generated GUI module is
`web/pkg/tos_ui_bg.wasm`.

## One-time setup from a fresh clone

Install stable Rust, Node.js and Python 3. Rust edition 2024 and Eframe's MSRV
must be supported by the selected toolchain. On Windows, either use the MSVC
toolchain with Visual Studio C++ Build Tools or a GNU toolchain with its native
binutils. This machine uses GNU Rust and WinLibs:

```powershell
# GNU Windows toolchain support, if needed:
winget install --id BrechtSanders.WinLibs.POSIX.UCRT --exact
rustup target add wasm32-unknown-unknown
rustup component add rustfmt clippy
npm ci
python -m pip install -r tools/requirements.txt
python tools/setup_assets.py --source "D:\Program Files (x86)\Tower of the Sorcerer"
npm run build
```

The setup script extracts sprites/WAV/MIDI from your installation and downloads
the OFL-licensed Noto Sans SC font from Google's official font repository. It
preserves an existing edited campaign and event/NPC configuration. Run it once
per clone; it is not a runtime dependency. Use `--font-only` for just the font or
`--skip-font` for just extraction.

**Extracted images and audio are ignored by Git**, as are the downloaded Chinese
font, binaries, WebAssembly output, test screenshots and local packages. The
repository tracks extraction tools, editable data, evidence and attribution.
The build script resolves Cargo/WinLibs and installs a `wasm-bindgen-cli` version
matching `Cargo.lock` when necessary.

For a local portable desktop folder:

```powershell
npm run package:native
.\dist\native\tos-ui.exe
```

The ignored `dist/native/` folder contains the GUI executable and adjacent local
assets/fonts. It can run from another working directory. Original media retain
their authors' rights; packaging locally does not grant redistribution rights.

## Saves

Every accepted game command autosaves. Browser saves, selected custom campaign
and settings use `localStorage`, scoped to the site's origin. **Save game**
creates a separate checkpoint; **Restore checkpoint** returns to it even after
later autosaves or a fatal fight. Native saves use the user's application-data
folder under `tos-rust`; `TOS_STORAGE_DIR` overrides it.

Settings can export a portable JSON save and import pasted JSON. Both graphical
targets also accept dropped save/campaign JSON files. Save validation is atomic:
bad imports leave the current game intact. A campaign fingerprint rejects
incompatible revisions. The two known previous bundled original revisions are
migrated conservatively, including cached campaigns and checkpoints, while
preserving the backside cycle and player progress. Original save and campaign
copies remain under `tos-rust:save:recovery` and `tos-rust:campaign:recovery`;
unknown or custom revisions remain strictly checked.

## Visual campaign editor

Open **Campaign editor** in either game or run `npm run editor`. It edits a
separate draft and offers:

- Floor painting, a searchable tile palette, floor duplication, titles and
  stair landings, with undo/redo.
- Enemy HP/ATK/DEF/gold and special properties.
- Tile/item definitions, starting player stats, combat/backside rules, NPCs,
  shop offers, event triggers, conditions and ordered effects.
- Validation, play-testing the draft and JSON export. An advanced JSON panel
  preserves access to custom fields; ordinary map and enemy editing uses forms.

Exported `campaign.json` can be imported into either graphical target or supplied
to CLI/MCP. To change the checkout's default, save it as `data/campaign.json` and
rebuild. Merely opening editor panels leaves the campaign unchanged. Refer to
[configuration.md](docs/configuration.md) for the complete data contract and
[architecture.md](docs/architecture.md) for the shared UI and future Android work.

English and Simplified Chinese dictionaries are in `data/locales/`, including
all 268 extracted original dialogue entries, UI labels, entity names and generated
journal messages. Unknown custom prose retains its authored language. The Chinese
font remains a separate local runtime asset.

## CLI, headless and MCP

```powershell
.\target\release\tos.exe play
.\target\release\tos.exe state
.\target\release\tos.exe validate
.\target\release\tos.exe headless
.\target\release\tos.exe replay .\examples\opening.jsonl
.\target\release\tos.exe mcp
```

These modes embed the campaign and need no art, audio or GUI. Use `--campaign PATH`
for custom data and `--save PATH` to resume; `tos --help` lists options. Terminal
play accepts WASD, `inspect X Y`, `choose ID`, `use ITEM [FLOOR]`, `save PATH` and
`quit`. Headless mode reads one JSON command per line and emits state after each:

```json
{"type":"move","direction":"up"}
{"type":"choose","choice":"leave"}
{"type":"use_item","item":"flying_orb","floor":1}
```

The MCP server uses newline-delimited JSON-RPC over stdio. Its eight tools are:

| Tool | Purpose |
| --- | --- |
| `game_state` | Map, player, dialogue, flags and unlocked enemy forecasts |
| `inspect_tile` | Inspect a square without acting; respects the Hero Orb gate |
| `plan_path` | Read-only click-route planner, shared with the GUI |
| `game_action` | Commit a move, choice, cancellation or item action |
| `simulate_actions` | Try actions on a copy without changing the session |
| `save_game` | Export a portable save |
| `load_game` | Restore a matching validated save |
| `new_game` | Reset the session |

Resources `tos://state` and `tos://campaign` expose state and configuration.
Stdout contains only protocol messages. Each server owns an independent session.
A client configuration for this checkout is:

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

## Evidence and verification

The original campaign contains 51 original 11×11 maps (floors 0–50), 33 monster
rows, 268 original dialogue strings, 100 progression events and 41 positioned
NPC interactions. Extraction/probe tools recover executable tables and scripted
queues without modifying the installation. Addresses, checksums and confidence
notes are retained in `data/` and [original-data.md](docs/original-data.md).

[mechanics.md](docs/mechanics.md) documents combat/item formulas, traps, gate and
backside evidence, including exactly 43 moving-tile records in the floor-10
Skeleton scene. [animation-evidence.md](docs/animation-evidence.md) records the
walking/standing/damage artwork, per-strike audio, mask composition and stair
ordering. Presentation duration is configurable; original Windows timer
granularity is not emulated. The executable audit covers all 51 initialized
floor records and all 56 initialized special-road sites.

The first-cycle ending still uses a compact modern victory/credits presentation
followed by the verified backside reset. Its original 1,098-record raster sequence
has been audited, but its complete artwork composition has not been reproduced.
This boundary concerns ending presentation; the noncombat first-cycle completion,
carried stats and subsequent cycle reset are implemented and scenario-tested.
The MIDI synth does not reproduce the old sound bank or all controllers/pitch
bend. Original fairy score/rank tables and its automatic checkpoint interface
remain unimplemented. Later-cycle Zeno's original double-scaling bug is deliberately
normalized; the original floor-45 merchant's unscaled HP reward is retained.

Run the checks with:

```powershell
npm run check
npm run build
npm run test:mcp
npm run test:native
# With npm start running:
npm run test:browser
```

`check` runs the Rust workspace tests and native/wasm Clippy with warnings denied.
Browser checks use headless Playwright and actual canvas pointer/keyboard input;
native screenshots use Eframe's renderer hook. No computer-use testing is needed.
Screenshots and reports are written to ignored `test-results/`.

The MCP test drives 46 natural opening actions through capture and escape and
compares CLI replay/headless results. Late-game, traps and cycle branches also
have explicit scenario tests. Those are separate evidence from a complete
unassisted fifty-floor playthrough, which has not been validated.

## Source layout and licenses

| Directory | Responsibility |
| --- | --- |
| `crates/tos-core` | Deterministic rules, path planner, saves and presentation events |
| `crates/tos-ui` | Shared Rust game/editor, graphics, audio and platform adapters |
| `crates/tos-cli` | Terminal, JSONL, replay, MCP and local web server |
| `crates/tos-wasm` | Lightweight engine binding for external browser clients |
| `web` | Startup shell, generated wasm and ignored local runtime media |
| `data` | Editable campaign, bilingual dictionaries and original evidence |
| `tools` | Extraction, toolchain-aware build and packaging helpers |
| `tests` | Browser/native/MCP integration checks |

Remake code is MIT licensed. Original game media, dialogue and maps remain the
work of Oz & Kenichi and are excluded from that license. Fonts use the SIL Open
Font License. See [THIRD_PARTY.md](THIRD_PARTY.md).
