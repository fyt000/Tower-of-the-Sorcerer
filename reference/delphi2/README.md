# Compiler-assisted Delphi 2 reconstruction — 2026-10-09

The locally supplied `Borland Delphi Client Server Suite 2.0.7z` is useful.
Its compiler runs on this Windows host, its RTL/VCL Pascal sources are present,
and one high-level gameplay reconstruction compiles to the original routine's
literal machine bytes. This is a working research baseline, not a recovered
complete Pascal game project or a claim to the author's original source text.

The subsequent [Delphi game](../../delphi/README.md) embeds the forms unchanged,
implements all 230 published methods, and uses normal compiler-allocated storage.
Its tests cover gameplay, persistence, rankings, core routines, and modal gates.
Its reports retain the limits on exhaustive equivalence and pixel comparisons.
This compiler-probe report and its library mismatches describe the earlier
research baseline.

The [comparison report](comparison-report.json) retains both successful checks
and library incompatibilities. The original game installation and campaign
state are untouched. No installer, IDE, original game process or recovery DLL
was launched; only the compiler and the small native framework probe ran.

The subsequent [additional-media and IME review](IME-REVIEW.md) explains the
four-byte layout shift using an original IME field already retained in RTTI,
tests the newly supplied Desktop media and System update, and corroborates
Delphi 2 IME declarations against a public reference. Two reconstructed IME
helpers now have byte correspondence and 276 modeled API-trace comparisons.
The installed readme identifies **Borland Delphi 2.0J Desktop** as the original
compiler product. The exact compiler/DCU patch build and a complete rebuilt
library remain unverified; the IME review retains the documentation provenance.

## Supplied compiler and libraries

- Input archive SHA-256:
  `2917f047c10ab8f9bb611ac3b547e7a6e19c7ac0fb5ba92c58b3dc6b8b990992`.
- The embedded InstallShield 3 `DATA.Z` contains 1,676 file records. We extracted
  492 compiler, library, documentation and source files into ignored `build/`.
- `DCC32.EXE` identifies itself as **Delphi for Win32 Version 9.0**, the compiler
  version used by the Delphi 2 product. It compiles both test projects here.
- Sources include `System.pas`, `Forms.pas`, `Controls.pas`, `StdCtrls.pas` and
  `ExtCtrls.pas`. Their paths, lengths and hashes are retained in the report.
- The four separately bundled update DCUs remain separate from the base units.
  Base, Forms-only, System-only and all-update variants were built and run.
  Their different CODE hashes confirm that the selected updates affect builds.
- Compiler, Borland source and DCUs stay under `build/research/delphi2/`; these
  research inputs are not copied into the versioned reconstructed source tree.

Extraction uses the inspected Python
[idecomp](https://github.com/lephilousophe/idecomp) implementation at commit
`bd2b77624b96bb2a4f347518d087126759296a03`. No installer is needed. The local
extraction manifest includes every archive file record and hashes every
extracted baseline/update file. The builder checks these hashes before use.

## First gameplay reconstruction

[RecoveredNeighbor.pas](recovered/RecoveredNeighbor.pas) is a readable Pascal
reconstruction of original entry `0x00451C20`, the neighbor tile classifier.
It uses Pascal `case` statements, map indexing and integer division; it embeds
no original instruction blob and has no assembly implementation.

| Evidence | Result | Scope |
|---|---|---|
| Compilation | Delphi 2 compiler succeeds | Reconstructed unit and isolated DLL probe |
| Literal routine bytes | **282/282 match exactly** | No address normalization or opcode masking for this routine |
| Effect comparisons | **9,216/9,216 agree** | Every byte tile value, three floors, four indices, three previous monster-index values |
| Effects observed | Classification, monster index and complete writes to those state variables | No calls are skipped; unexpected non-stack writes fail the comparison |
| Source identity | Not established | Multiple Pascal texts can compile to the same bytes; comments, local names and removed code are not recoverable from that result |

Absolute state addresses deliberately reproduce the original for emulator
comparisons. The [RecoveryProbe](probes/RecoveryProbe.dpr) DLL is read as PE
bytes, never loaded natively. The unit must not be called in an ordinary native
process: those original game addresses are not its allocated state.

Branch ordering matters to the emitted code. Moving the tile-13 case after the
monster case produces the original branch layout. This is a concrete example
of compiling candidate source to refine recovery without changing the intended
behavior to match a mistaken reimplementation.

## Library correspondence and the unresolved ABI difference

In every tested variant, eight of nine selected routines agree after image
addresses and external relative transfers are normalized:

- `TControl.Click`, `TWinControl.CanFocus`;
- `TTimer.Timer`, the complete `TTimer.WndProc`;
- `MakeObjectInstance`;
- `System.@InitExe`, `@HandleAnyException`, `@HandleFinally`.

This comparison retains object field offsets, scalar constants and internal
branch offsets. The report enumerates every masked operand. Address-normalized
shape agreement supports correspondence but does not establish callee identity,
library purity or whole-runtime equivalence.

`TButton.CMDialogKey` **does not match**: the original reads the active flag at
`Self+$106`; the archive library uses `Self+$102`. Class sizes independently
corroborate the discrepancy:

| Class | Original EXE | All four archive variants |
|---|---:|---:|
| TControl | 168 | 168 |
| TWinControl | 256 | 252 |
| TButton | 268 | 264 |
| TForm | 432 | 428 |
| TTimer | 52 | 52 |

The archive's update units do not resolve this difference. Subsequent review
correlates it with the original ImeMode field at `$D4`, absent from the supplied
English source, and two extra virtual IME methods. The installed documentation
identifies Japanese Delphi 2.0J Desktop, consistent with that IME support. The
exact patch/build remains unverified; do not call the supplied libraries an
exact original VCL build or apply a blanket four-byte offset adjustment.
See the [IME evidence and recovery](IME-REVIEW.md).

## Tests that now exercise framework interactions

[RuntimeProbe.dpr](probes/RuntimeProbe.dpr) runs **19 native behavioral checks**
per library variant, 76 successful checks in total. It constructs private
controls and hidden callback/timer windows without showing a game window.
Checks include enabled/hidden parent gates, Escape and Enter delivery, modifier
keys, direct click behavior, modal-result effects, generated callback procedures,
actual Windows timer dispatch and timer exception recovery through
`Application.OnException`.

The separate emulator fixtures execute actual VCL machine code from the
original EXE and from each compiled baseline. **13 original fixtures and 52
compiled fixtures pass**, including dynamic method lookup and nested callbacks.
Internal VCL calls are followed, not skipped. Windows `GetKeyState` is explicitly
modeled as no physical Shift/Ctrl pressed; input trees and observer callbacks
are synthetic. These fixtures are not a natural full-game input run.

One meaningful interaction is that `TTimer.Enabled` governs timer registration,
but `TTimer.WndProc` itself does not recheck Enabled when a `WM_TIMER` arrives.
The native probe posts a timer message after disabling registration and observes
the callback. The original machine-code fixture does the same. With the handler
removed, no callback occurs. This is evidence about VCL delivery, not a newly
confirmed discrepancy in the C++ game.

Compiler correspondence also exposes **27 instruction bytes** inside
`@HandleAnyException` that were absent from the retained Ghidra instruction
listing: `0x00402FEE..0x00403008`. They are now retained in a complete
[focused runtime span](runtime-spans/00402f4c.asm) and enumerated in the report.
The earlier whole-program ledger is preserved; its 14,369 unresolved-byte count
describes that snapshot. This supplement is new corroborated evidence, not an
automatic claim that the remainder of its unknown bytes have been decoded.

## Route to a complete Pascal reconstruction

1. Resolve library/layout differences and map RTL/VCL routines to verified
   source/library versions. Keep mismatched and ambiguous matches explicit.
2. Recover project/unit boundaries, global declarations, class fields, types,
   method signatures, original form resources and assets. The existing RTTI,
   published-method and DFM inventories supply part of this information.
3. Reconstruct gameplay routines in Pascal against the pinned original EXE,
   compiling small groups and comparing complete routine spans. Account for
   helper calls, aliases, shared epilogues and exception continuations.
4. Compare behavior over input/focus/timer sequences, dialogs, save/load and
   failing I/O. Observe state writes and transitive effects in addition to
   return values. Native reference-library checks complement original-executable
   fixtures; they do not replace them.
5. Assemble the complete project only as implementations become recoverable.
   An empty callback or generated declaration that compiles is not recovered
   gameplay. Missing functions must stay visibly missing.

A whole-file EXE diff is insufficient during reconstruction: link order,
addresses, alignment, resources, build flags and library variants can change
the file. Compare scoped code with explicit relocation rules and compare
behavior independently. A byte-identical routine is strong local evidence;
passing selected fixtures cannot certify interactions outside their scope.

The earlier 6,808 C++ comparisons are unchanged. These new measurements do not
turn those comparisons into proof of a complete campaign or whole program.

## Reproduction

Run from the repository root with Python containing `pefile`, `capstone` and
`unicorn`. On this host that is `C:\Python314\python.exe`.

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

The builder uses short relative unit paths and CRLF staging copies because
Delphi 2's command-line/source readers have legacy limits. Tracked Pascal
sources remain unchanged by staging. All build logs, manifests, DCUs, maps,
EXEs and DLLs remain under ignored `build/`.

The comparison tool's successful exit verifies these measured fixtures and
artifact consistency. The report explicitly records
`complete_runtime_baseline_accepted: false` and
`full_pascal_game_recovered: false`. Six adversarial checks verify that field,
constant, branch and gameplay mutations are detected and that the recorded ABI
mismatch cannot be silently advertised as a complete accepted baseline. The
subsequent IME work adds three adversarial tests, bringing the total to nine.
