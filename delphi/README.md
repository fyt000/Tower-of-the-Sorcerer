# Tower of the Sorcerer — Delphi 2

## Build and run

Prepare the compiler using the [compiler guide](../reference/delphi2/README.md),
supply the original game assets, then run from the repository root:

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

## Recovery status

All **230 published methods** are reconstructed in Pascal and reviewed against
the original machine code. Comparison covers complete routine bodies, including
exception continuations, switch tables and literals. Only verified address
relocations are normalized; VCL field and virtual-call offsets remain differences.

| Reviewed code | Result |
|---|---|
| 73 published methods, 53,255 code bytes | Match after verified relocation |
| 156 published methods | Reviewed English/Japanese VCL differences remain |
| `madoushi2` | Retains the floor-49 fix |

The source-structure differences are resolved, including `doorcheck` and
`roujin`. Matching the original Delphi 2.0J compiler and libraries is expected
to close the VCL differences, but that build remains untested and the original
patch level is unknown. The available compiler is English Delphi 2.

Production logic lives in `GameForms.pas` and its includes; `GameCore.pas` is
for isolated probes. Expanded event writes retain `PushCommand(...)` comments
and `TEventOpcode` names without changing generated instructions or record layout.

Original forms, icons and both Japanese calendar string tables are preserved.
The calendar tables contain weekdays and Meiji–Heisei era definitions;
the English RTL still lacks their Japanese initialization routines.

The **sole intentional gameplay fix** removes an extra floor-49 summon cursor
increment that exposes a stale command inside the buffer. All 128 valid summon
records are preserved. Battle queues, timer/reset handling, inventory scanning
and save rollback retain original behavior, including failure paths. See
[comparison-policy.json](comparison-policy.json).

Whole-EXE equality and complete natural campaign coverage remain unverified.
Drawing/UI checks pass within their measured scope; original drive-combo height,
full-window appearance across fonts/DPI, and actual Windows focus/timer delivery
still need comparison.

## Verification

The current build passes **452 native runtime assertions**, **2,888 non-audio
dialogue/item/battle comparisons**, and **1,526 contact comparisons**. These
include original battle-queue and save-failure behavior; the floor-49 exception
has a separate regression check.

```powershell
python tools/format_delphi.py --check
python tools/reconstruct_delphi_project.py --check
python tools/compare_delphi_routines.py
python tools/verify_delphi_game.py
python tools/verify_delphi_dialogue.py --skip-audio
python tools/verify_delphi_contact.py
python tools/test_delphi_dialogue.py DialogueIntegrityTests.test_floor49_summon_does_not_execute_stale_slot_130
python tools/test_delphi_events.py
python tools/test_delphi_routines.py
python tools/review_delphi_calendar.py
```

Run `format_delphi.py` without `--check` to format. Rebuild after Pascal changes;
add `--audio-smoke` only for audio-related changes. Other `verify_delphi_*.py`
tools cover graphics, Flight, UI, startup and runtime behavior.

Recovered numeric domains are named in `GameState.pas`: map tiles, monster rows,
inventory choices, equipment tiers, facing, movement requests, Flight/stair kinds,
shop modes, speech IDs, text indices and option slots/values. Persisted fields and
event operands retain their original integer types. Enum members are used through
`Ord(...)` on those integer fields; sparse IDs and byte option values use untyped
constants. Delphi 2 can widen byte comparisons involving `Ord(enum)`, and typed
constants allocate data, so neither is a safe substitute for an untyped byte
literal. Inventory choices are one-based, merchant mode is zero, and facing and
movement requests encode up/down differently; these values must not be copied
from the C++ enum declaration order.

For a source-only cleanup, capture a fresh successful build **before editing**,
then compare the rebuilt artifacts with that baseline:

```powershell
python tools/build_delphi_game.py
python tools/compare_delphi_builds.py capture build/my-delphi-baseline
# Edit, format and rebuild the Pascal sources.
python tools/build_delphi_game.py --smoke
python tools/compare_delphi_builds.py check build/my-delphi-baseline
python tools/test_delphi_builds.py
```

The check covers every built EXE/DLL in full, including code, data, resource
payloads, headers, section layouts and BSS sizes. Only corresponding PE resource
directory `TimeDateStamp` fields may differ. It saves the result in
`build/delphi-game/reports/constant-cleanup-comparison.json`. The routine tests
also rebuild an isolated numeric-literal version of the named values and require
the same full-image comparison to pass. Original generated map/reset stores,
unverified offsets, aggregate puzzle totals and unrelated scene operands stay
literal until their domains are established.

Detailed results, byte differences and calendar call traces are generated under
`build/delphi-game/reports/`. Comparison tools accept `--check` for stale reports.
See also [mechanics](../docs/mechanics.md) and the [save layout](../docs/original-data.md#original-saves).
