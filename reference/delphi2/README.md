# Compiler-assisted Delphi 2 reference

This directory retains compiler, library, and recovery evidence. The playable
[Delphi game](../../delphi/README.md) implements all 230 published methods and
uses compiler-allocated storage. Its gameplay and pixel verification limits
are recorded separately.

The supplied English Delphi 2 libraries differ from the game's documented
**Delphi 2.0J Desktop** libraries. The
[comparison report](comparison-report.json) records hashes, normalized operands,
fixtures, and the unresolved ABI difference. The
[IME review](IME-REVIEW.md) explains the localized field and method additions.
The exact compiler/DCU patch build remains unverified.

## Supplied compiler and libraries

`Borland Delphi Client Server Suite 2.0.7z` supplies `DCC32.EXE` (compiler version
9.0), RTL/VCL source, and four separate update DCUs. Base, Forms-update,
System-update, and all-update probes retain those units separately.
Compiler inputs and outputs stay under ignored `build/research/delphi2/`.

Extraction uses [idecomp](https://github.com/lephilousophe/idecomp) pinned at
`bd2b77624b96bb2a4f347518d087126759296a03`. The manifest records archive entries
and extracted hashes; builders reject altered inputs. Source staging uses
CRLF and short relative unit paths for Delphi 2's command-line/source limits.

## First gameplay reconstruction

[RecoveredNeighbor.pas](recovered/RecoveredNeighbor.pas) reconstructs the
neighbor classifier at `0x00451C20` in Pascal. It matches **282 literal bytes**
and **9,216 effects**, covering all byte tile values, three floors, four indices,
and three previous monster-index values. Comparisons check classification,
monster index, and complete writes without skipped calls.

The [RecoveryProbe](probes/RecoveryProbe.dpr) DLL uses fixed game addresses and
must run only in CPU emulation. Matching code does not identify the author's
source text: multiple Pascal expressions can emit the same instructions.

## Library correspondence and the unresolved ABI difference

Eight selected routines match after image addresses and external transfers
are normalized: `TControl.Click`, `TWinControl.CanFocus`, `TTimer.Timer`,
`TTimer.WndProc`, `MakeObjectInstance`, `@InitExe`, `@HandleAnyException`, and
`@HandleFinally`. Object field offsets, constants, and local branches remain
literal. Normalized shape agreement does not authenticate callees or establish
whole-runtime equivalence.

`TButton.CMDialogKey` reads `Self+$106` in the game and `Self+$102` in the
supplied English libraries. None of the update variants resolves this:

| Class | Game | English library |
|---|---:|---:|
| TControl | 168 | 168 |
| TWinControl | 256 | 252 |
| TButton | 268 | 264 |
| TForm | 432 | 428 |
| TTimer | 52 | 52 |

The game's byte-sized `ImeMode` field at `$D4` shifts subsequent fields through
alignment; two additional virtual methods also affect dispatch. A blanket
four-byte offset adjustment cannot reproduce the localized library.

## Framework interactions and verification limits

[RuntimeProbe.dpr](probes/RuntimeProbe.dpr) passes 19 Windows checks per variant
(76 total): control gates, keyboard/click delivery, modal results, callbacks,
timers, and timer exception handling. Emulator fixtures pass 13 game and 52
compiled cases, following internal VCL calls with synthetic input trees and
modeled `GetKeyState`.

`TTimer.Enabled` controls registration; `WndProc` still delivers a posted
`WM_TIMER` after disabling registration if its handler remains assigned.
Compiler correspondence also recovers 27 bytes omitted from the Ghidra listing
at `0x00402FEE..0x00403008`, retained in the
[focused exception span](runtime-spans/00402f4c.asm). This supplement does not
rewrite the earlier whole-program ledger.

The report retains `complete_runtime_baseline_accepted: false` and
`full_pascal_game_recovered: false` for this reference baseline. Mutation tests
reject field, constant, branch, callee, and IME changes. These fixtures do not
establish a natural campaign run, whole-program equality, or pixel equality.

## Reproduction

Run from the repository root with the dependencies in `tools/requirements.txt`.
The supplied archive and pinned executable must be available locally.

```powershell
& 'C:\Program Files\7-Zip\7z.exe' x 'D:\Downloads\Borland Delphi Client Server Suite 2.0.7z' '-obuild/research/delphi2-media' -y
git clone https://github.com/lephilousophe/idecomp.git build/research/idecomp
git -C build/research/idecomp checkout bd2b77624b96bb2a4f347518d087126759296a03
python tools/prepare_delphi2_reference.py --media 'build/research/delphi2-media/Borland Delphi Client Server Suite 2.0' --extractor build/research/idecomp --archive 'D:\Downloads\Borland Delphi Client Server Suite 2.0.7z'
python tools/build_delphi2_reference.py
python tools/verify_delphi2_reference.py
python tools/verify_delphi2_reference.py --check
python tools/test_delphi2_reference.py
```

The builder runs the compiler and private framework probes; `--no-run` skips
probe execution. Recovery DLLs and the game executable are inspected/emulated
as bytes. Additional media and IME reproduction are in [IME-REVIEW.md](IME-REVIEW.md).
