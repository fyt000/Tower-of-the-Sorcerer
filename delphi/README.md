# Tower of the Sorcerer — Delphi 2

The Windows game uses Object Pascal, Delphi 2 VCL forms, bitmap atlases, and
Windows MCI audio. It includes gameplay, story events, endings, subsequent
cycles, eight save slots, five ranking categories, and persistent options.

## Build and run

The extracted Delphi 2 compiler must be available under `build/research/delphi2/`;
see [compiler preparation](../reference/delphi2/README.md). Install the Python
dependencies from `tools/requirements.txt` and provide the game installation's
assets. Run these commands from the repository root:

```powershell
python tools/reconstruct_delphi_project.py
python tools/build_delphi_game.py --smoke
.\tools\run_delphi_game.ps1
```

The launcher accepts `-SkipIntro`, `-Assets PATH`, and `-SaveDirectory PATH`.
Its default asset directory is `D:\Program Files (x86)\Tower of the Sorcerer`.
Saves default to `build/delphi-game/game/savedat`. Folder selection persists in
`TSW12.INI` beside the executable; an explicit save directory overrides it.

Passing `--assets` to `Tower.exe` selects portable settings and creates missing
save directories. Starting without that argument uses the installed game's
Windows-directory `TSW12.INI` convention.

## Architecture

| Module | Responsibility |
|---|---|
| [GameState.pas](src/GameState.pas) | Persisted records, options, shared gameplay state, and event storage |
| [GameCore.pas](src/GameCore.pas), [Gameplay.pas](src/Gameplay.pas) | Tile classification, combat arithmetic, field access, and clue mapping |
| [GameForms.pas](src/GameForms.pas) and the `*Methods.inc` files | VCL event handlers grouped by gameplay, story, startup, menus, graphics, and persistence |
| [EventScenes.inc](src/EventScenes.inc) | Floor arrival scenes, guard triggers, and boss rewards |
| [GameGraphics.pas](src/GameGraphics.pas), [GameContent.pas](src/GameContent.pas) | Shared rendering canvases and embedded monster/render-order tables |
| [Persistence.pas](src/Persistence.pas) | Save validation, checksums, rankings, and default score tables |
| [Audio.pas](src/Audio.pas) | MIDI filenames, floor music selection, and playback observations |
| [generated/](src/generated/) | DFM bindings, record fields, initialization, hints, and control layouts |

The five binary DFM resources and application icons are embedded unchanged.
Class, component, and published handler names remain serialization keys; those
names cannot be changed independently of the DFM. Other units, helpers, and
state types use names based on their purpose. Routine addresses and serialized
field offsets are indexed by the comparison tools.

Each floor record contains two landing bytes followed by an 11 × 11 map.
The hero record contains 171 little-endian 32-bit words. Together the map and
hero records form a 6,957-byte save. Fields whose meaning is unknown retain
`WordN` names, where `N` is their persisted byte offset. Signed arithmetic wraps
at 32 bits because combat and file checksums depend on that behavior.

Story commands are six-byte records containing an opcode and two operands.
The dispatcher executes them newest first; several animation opcodes consume
a paired operand record. Dialogue pauses the dispatcher until confirmation.
Queues hold 30,000 commands. Battles that exceed this capacity generate one
turn at a time; restart and load cancel pending battle continuations.

Save slots are checked in temporary records before replacing game state.
Fairy checkpoints use the raw record format and may retain stale checksums.
Ranking files contain a 288-byte numeric table and a separate ten-line name
file. Invalid ranking data restores the complete default table and names.

Rendering uses the supplied `Data` and `Data3` bitmap atlases. Sprite masks are
combined with VCL canvas raster operations. Audio uses eight WAV effect routes
and seventeen MIDI tracks through MCI; device or media failures leave gameplay
running.

The `EMULATOR_ADDRESSES` compiler define is confined to the comparison DLL.
It maps game globals to fixed addresses for CPU emulation. The application
and a second probe use normal compiler-allocated storage.

## Known differences and limits

- The English Delphi 2 VCL lacks Japanese IME support. The accepted field and
  dispatch offsets are documented in [comparison-policy.json](comparison-policy.json).
  Its RTL/VCL messages also differ from the Japanese library's string resources.
- The 49F summon omits the stray queue increment at `$004637DD`, which could
  expose an unwritten stale command. Scene comparisons report this raw mismatch.
- Oversized battles use bounded turn generation. Corrupt or truncated slot
  saves preserve the current game state. Portable startup keeps long paths as
  logical lines rather than wrapping them in the internal settings memo.
- In two font modes, the folder dialog's drive selector realizes heights of
  24 and 19 after a request for 20. These remain unresolved geometry differences.
- Walking, door, tile-slide, vampire, and ending animations lack exhaustive
  pixel comparisons. Whole-window font, DPI, focus, and timer delivery are also
  outside the established comparison scope.
- Integration tests use seeded game states and execute the ending through the
  next-cycle reset. They do not establish an uninterrupted campaign playthrough,
  whole-program binary equality, or exhaustive exception-path equivalence.

## Formatting and verification

[pasfmt 0.7.0](https://github.com/integrated-application-development/pasfmt)
formats every `.pas`, `.dpr`, and `.inc` file using [pasfmt.toml](pasfmt.toml).
The wrapper downloads the checksum-pinned Windows release into ignored build
output when it is absent. Include fragments are formatted in their enclosing
record, type, statement, or unit context. Source generators use the same formatter.

```powershell
python tools/format_delphi.py
python tools/format_delphi.py --check
python tools/reconstruct_delphi_project.py --check
```

| Tool | Purpose |
|---|---|
| `build_delphi_game.py --smoke` | Build the application and run form, graphics, startup, UI, gameplay, persistence, and ranking harnesses |
| `build_delphi_game.py --smoke --audio-smoke` | Add MCI audio checks when changes touch audio code, assets, dependencies, or configuration |
| `verify_delphi_runtime.py` | Check source coverage and collect connected gameplay/save/ranking/audio evidence |
| `test_delphi_events.py` | Compare scene queues and state with the reference executable in CPU emulation |
| `verify_delphi_game.py` | Compare core arithmetic, state writes, resources, and modal gates |
| `verify_delphi_graphics.py`, `verify_delphi_flight.py` | Compare raster operations and pixels, monster display, and Flight sequences |
| `verify_delphi_startup.py`, `verify_delphi_ui.py` | Compare settings/exception handling, controls, fonts, menus, and timer behavior |
| `test_delphi_game.py`, `test_delphi_graphics.py`, `test_delphi_startup.py`, `test_delphi_ui.py` | Verify that comparison checks detect deliberate mutations |
| `compare_delphi_binary.py` | Account for literal section and resource differences |
| `audit_delphi_exception_paths.py` | Locate exception continuations omitted from method exports |

Tool paths are relative to `tools/`. Comparison commands accept `--check` to
reject stale reports. Reports and executable artifacts are generated under
ignored `build/`; they are not source files. Regenerate and rebuild after source
changes before running comparisons. Compiler and reference-data preparation
tools remain documented in the [compiler guide](../reference/delphi2/README.md)
and [reverse-engineering workflow](../docs/reverse-engineering.md).
