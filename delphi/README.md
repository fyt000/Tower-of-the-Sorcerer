# Tower of the Sorcerer — Delphi 2

## Recovery status

All **230 published methods** have Pascal bodies reviewed against complete
original routine extents, including exceptions, switch tables and literals.

| Methods | Result |
|---|---|
| 73 (53,255 code bytes) | Match after verified address relocation |
| 156 | Reviewed English/Japanese VCL differences |
| `madoushi2` | Floor-49 stale summon-record fix |

The current baseline uses English Delphi 2. Original Delphi 2.0J Desktop adds an
IME field and two virtual methods; later fields shift four bytes and virtual
slots also differ. Exact compiler patch and a matching Japanese build remain
unverified. Original forms, icons and calendar tables are preserved; Japanese
calendar initialization is absent from the English RTL.

The floor-49 fix is the sole intentional gameplay change. See
[comparison policy](comparison-policy.json). Whole-EXE equality, complete campaign
coverage, full-window fonts/DPI, drive-combo height and Windows focus/timer
delivery remain unverified. [Research setup](../docs/decompilation.md).

## Compiler setup

Supply local Delphi 2 media containing `DATA.Z` and the
[original research cache](../docs/decompilation.md#prepare-data-and-decompilation).
From the repository root, adjusting paths:

```powershell
git clone https://github.com/lephilousophe/idecomp.git build/research/idecomp
git -C build/research/idecomp checkout bd2b77624b96bb2a4f347518d087126759296a03
python tools/prepare_delphi2_reference.py --media PATH/TO/MEDIA --extractor build/research/idecomp
```

Optional [compiler/IME probes](../tools/delphi2/) reproduce selected byte and
API-trace comparisons with `build_delphi2_reference.py`,
`verify_delphi2_reference.py` and `verify_delphi2_ime.py` in `tools/`.
Absolute-address recovery DLLs are for emulation only. Reports live in
`build/research/delphi2-reports/`. These probes do not establish a matching VCL.
IME verification also requires the DEKO declaration archive/pages named in its script.

## Build and run

```powershell
python tools/reconstruct_delphi_project.py
python tools/build_delphi_game.py --smoke
./tools/run_delphi_game.ps1 -Assets 'C:/path/to/original'
```

Launcher options: `-SkipIntro`, `-Assets PATH`, `-SaveDirectory PATH`. Saves default
to `build/delphi-game/game/savedat`. Explicit assets select portable `TSW12.INI`;
otherwise preferences use the Windows-directory convention.

## Verification

```powershell
python tools/format_delphi.py --check
python tools/reconstruct_delphi_project.py --check
python tools/compare_delphi_routines.py
python tools/verify_delphi_game.py
python tools/verify_delphi_dialogue.py --skip-audio
python tools/verify_delphi_contact.py
python tools/test_delphi_events.py
python tools/test_delphi_routines.py
```

Reports: `build/delphi-game/reports/`. Additional `verify_delphi_*.py` tools cover
UI, graphics, Flight and startup. Use `--audio-smoke` only for audio changes.

Production logic is in `src/GameForms.pas` and its includes; `GameCore.pas` serves
isolated probes. Preserve numeric domains and byte-sized comparisons: Delphi 2
can widen `Ord(enum)` expressions, and typed constants allocate data.

For source cleanup, build and capture **before editing** with
`python tools/compare_delphi_builds.py capture build/delphi-baseline`; rebuild,
then run `python tools/compare_delphi_builds.py check build/delphi-baseline`.
This compares full EXE/DLL images, allowing only PE resource timestamps.
