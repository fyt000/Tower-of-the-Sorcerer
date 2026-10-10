# Tower of the Sorcerer — Delphi 2

This Object Pascal project aims for a faithful recovery of the Windows 1.2
game using Delphi 2 VCL forms, bitmap atlases and Windows MCI audio. It includes
endings, subsequent cycles, eight save slots, five ranking categories and
persistent options.

## Build and run

Prepare the compiler under `build/research/delphi2/` using the
[compiler guide](../reference/delphi2/README.md), install
`tools/requirements.txt`, and supply game assets. From the repository root:

```powershell
python tools/reconstruct_delphi_project.py
python tools/build_delphi_game.py --smoke
.\tools\run_delphi_game.ps1
```

Launcher options: `-SkipIntro`, `-Assets PATH`, `-SaveDirectory PATH`.
Defaults are `D:\Program Files (x86)\Tower of the Sorcerer` for assets and
`build/delphi-game/game/savedat` for saves. Passing `--assets` to `Tower.exe`
uses portable `TSW12.INI` beside the executable and creates save directories;
without it, settings use the Windows-directory convention. Explicit save paths
override folder selection.

Startup checks for a `TTSW10` window, including one from a renamed or copied
executable. A second launch shows the game's warning, requests foreground
activation of that window and exits before settings or game-form creation.
The check retains the simultaneous-start race before either main window exists.

## Architecture

| Module | Responsibility |
|---|---|
| [GameState.pas](src/GameState.pas) | Persisted records, options, globals and event storage |
| [GameCore.pas](src/GameCore.pas), [Gameplay.pas](src/Gameplay.pas) | Classification, combat arithmetic, field access and clues |
| [GameForms.pas](src/GameForms.pas), `*Methods.inc`, [EventScenes.inc](src/EventScenes.inc) | VCL handlers, floor triggers and story scripts |
| [GameGraphics.pas](src/GameGraphics.pas), [GameContent.pas](src/GameContent.pas) | Canvases, masks, monster tables and render order |
| [Persistence.pas](src/Persistence.pas), [Audio.pas](src/Audio.pas) | Saves/rankings and MCI routing |
| [GameInstance.pas](src/GameInstance.pas) | Window-class startup check and duplicate-launch warning |
| [generated/](src/generated/) | DFM bindings, fields, initialization and layouts |

Five DFM resources and application icons are embedded unchanged. Class,
component and published-handler names are DFM serialization keys.
Unknown persisted fields use `WordN`, where `N` is their byte offset.
The [save specification](../docs/original-data.md#original-saves) describes
the 6,957-byte map/hero records, checksums and raw Fairy checkpoints.

Signed arithmetic wraps at 32 bits. Penetration is checked separately from
total damage; an overflowing negative total is displayed and compared with HP
as signed. Story commands are six-byte opcode/operand records, executed newest
first. Some animation opcodes consume a paired record; dialogue waits for
confirmation. The 30,000-command queue streams oversized battles one turn at
a time. Restart and load cancel battle continuations.

Slots are validated in temporary records. Ranking load failure restores the
complete default table and names. VCL raster operations apply bitmap masks;
MCI routes eight WAV effects and seventeen MIDI tracks. Audio failure leaves
gameplay running. `EMULATOR_ADDRESSES` maps globals to fixed addresses only
in the comparison DLL; the application and storage probe use allocated globals.

## Known differences and limits

- English Delphi 2 VCL lacks Japanese IME support and has different RTL/VCL
  message resources. Accepted field/dispatch offsets are in
  [comparison-policy.json](comparison-policy.json).
- The 49F summon omits the cursor increment at `$004637DD` that exposes an
  unwritten stale 129th command. Comparisons report this mismatch.
- Oversized fights stream turns; corrupt/truncated slot loads preserve state.
  Portable startup keeps long paths as logical settings lines.
- The bottom message line uses an enabled, read-only control with fixed gray
  background and white text. Disabled Windows edits force gray text and hide
  messages against the recovered gray background.
- The drive selector realizes heights 24 and 19 after requesting 20 in two
  font modes; this geometry difference is unresolved.
- Walk, door, tile-slide, vampire and ending pixels are not exhaustively
  compared. Whole-window fonts, DPI, focus and timer delivery are outside scope.
- Seeded integration cases reach the ending and next-cycle reset. They do not
  prove a full natural campaign, binary equality or all exception paths.

## Formatting and verification

[pasfmt 0.7.0](https://github.com/integrated-application-development/pasfmt)
uses [pasfmt.toml](pasfmt.toml). The wrapper caches a checksum-pinned Windows
release under ignored build output and formats includes in their enclosing
context. Generators use the same formatter.

```powershell
python tools/format_delphi.py
python tools/format_delphi.py --check
python tools/reconstruct_delphi_project.py --check
```

Tools below live in `tools/`. Comparison tools accept `--check` for stale
reports; regenerate and rebuild after source changes. Outputs stay in `build/`.

| Tools | Purpose |
|---|---|
| `build_delphi_game.py --smoke`, `verify_delphi_runtime.py` | Build, harnesses, coverage and connected runtime evidence |
| `verify_delphi_entry.py`, `test_delphi_entry.py` | Both program-entry paths, duplicate-launch calls and comparison integrity |
| `build_delphi_game.py --smoke --audio-smoke` | MCI checks; run only for audio-related changes |
| `test_delphi_events.py`, `verify_delphi_game.py` | Scene queues, arithmetic, writes, resources and modal gates |
| `verify_delphi_graphics.py`, `verify_delphi_flight.py` | Raster operations, display and Flight sequences |
| `verify_delphi_startup.py`, `verify_delphi_ui.py` | Settings, exceptions, controls, fonts, menus and timers |
| `test_delphi_{game,graphics,startup,ui}.py` | Deliberate mutations that check comparison integrity |
| `compare_delphi_binary.py`, `audit_delphi_exception_paths.py` | Section/resource differences and exception continuations |

The [recovery workflow](../docs/reverse-engineering.md) owns reference-data
preparation and comparison procedures.
