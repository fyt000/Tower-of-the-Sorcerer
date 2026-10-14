# Tower of the Sorcerer — Delphi 2

## Build and run

Prepare the compiler under `build/research/delphi2/` using the
[compiler guide](../reference/delphi2/README.md), install
`tools/requirements.txt`, and supply game assets. From the repository root:

```powershell
python -m pip install -r tools/requirements.txt
python tools/reconstruct_delphi_project.py
python tools/build_delphi_game.py --smoke
.\tools\run_delphi_game.ps1
```

Launcher options: `-SkipIntro`, `-Assets PATH`, `-SaveDirectory PATH`.
Defaults are `D:\Program Files (x86)\Tower of the Sorcerer` for assets and
`build/delphi-game/game/savedat` for saves. Passing `--assets` to `Tower.exe`
uses portable `TSW12.INI` beside the executable; without it, settings use
the Windows-directory convention. Explicit save paths override folder selection.

## Architecture

| Module | Responsibility |
|---|---|
| [GameState.pas](src/GameState.pas) | Persisted records, options, globals and event storage |
| [GameCore.pas](src/GameCore.pas), [Gameplay.pas](src/Gameplay.pas) | Classification, combat arithmetic, field access and clues |
| [GameForms.pas](src/GameForms.pas), `*Methods.inc`, [EventScenes.inc](src/EventScenes.inc) | VCL handlers, floor triggers and story scripts |
| [GameGraphics.pas](src/GameGraphics.pas), [GameContent.pas](src/GameContent.pas) | Canvases, masks, monster tables and render order |
| [Persistence.pas](src/Persistence.pas), [Audio.pas](src/Audio.pas) | Saves/rankings and MCI routing |
| [GameInstance.pas](src/GameInstance.pas) | Duplicate-launch check |
| [generated/](src/generated/) | DFM bindings, fields, initialization and layouts |

Original form resources and icons are embedded unchanged. Component and
published-handler names are serialization keys. Unknown persisted fields use
`WordN`, where `N` is their byte offset. Signed arithmetic wraps at 32 bits;
story commands execute newest first. See [mechanics](../docs/mechanics.md)
and the [save layout](../docs/original-data.md#original-saves).

## Known differences and limits

- The supplied English Delphi 2 libraries differ from the original Japanese
  edition, including IME support and message resources. Accepted differences
  are recorded in [comparison-policy.json](comparison-policy.json).
- Oversized battles stream turns, invalid slot loads preserve the running
  state, and the 49F summon omits an unwritten stale command.
- Some control styling and geometry differ. Graphics, fonts, DPI, focus and
  timer delivery are not exhaustively compared.
- Handler comparisons and seeded integration scenarios do not establish
  binary equality or every natural campaign sequence.

## Formatting and verification

The formatter wrapper uses [pasfmt.toml](pasfmt.toml), caches a pinned release
under `build/`, and formats includes in their enclosing context:

```powershell
python tools/format_delphi.py
python tools/format_delphi.py --check
python tools/reconstruct_delphi_project.py --check
```

`build_delphi_game.py --smoke` builds and runs native checks. Add `--audio-smoke`
only for audio-related changes. Tools under `tools/` compare the game with the
original executable:

| Tools | Purpose |
|---|---|
| `verify_delphi_game.py`, `verify_delphi_runtime.py` | Gameplay and connected runtime behavior |
| `verify_delphi_entry.py`, `verify_delphi_startup.py` | Program entry and settings |
| `verify_delphi_graphics.py`, `verify_delphi_flight.py`, `verify_delphi_ui.py` | Rendering, Flight and controls |
| `test_delphi_*.py` | Regressions and comparison integrity |
| `compare_delphi_binary.py`, `audit_delphi_exception_paths.py` | Binary differences and exception paths |

Comparison tools accept `--check` for stale reports. Regenerate bindings and
rebuild after source changes; generated output stays in `build/`.
