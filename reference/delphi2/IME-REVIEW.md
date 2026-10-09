# Delphi 2 media and IME reconstruction — 2026-10-09

The installed game's documentation identifies **Borland Delphi 2.0J Desktop**
as its compiler product. The additional media and online research are useful,
but none supplies a verified exact original VCL build. The four-byte class-size
difference now has a concrete explanation: the original has an IME mode field
and associated virtual methods absent from the supplied English library sources. A public
Delphi 2 declaration reference corroborates the original enum and method
structure, and two independently reconstructed Pascal helpers now compile to
matching code. This is library recovery evidence, not an additional confirmed
C++ gameplay discrepancy.

## Installed documentation identifies the Japanese edition

The user's installation-documentation finding was verified locally in
`D:\Program Files (x86)\Tower of the Sorcerer\Readme.txt`, line 8:

```text
[Programmed with]    Borland Delphi 2.0J Desktop
```

Readme SHA-256:
`f7158dfa7b93b771e8fd83de9efc90979911d8ab71610ac4969236d6c40cb361`.
The same document identifies game version 1.2 and executable `TSW12.EXE`.
The installed executable is named `TSW.exe`; its SHA-256 matches the pinned
research executable:
`41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779`.
The readme is product-attribution evidence accompanying that installation;
it does not by itself authenticate a compiler/DCU patch build.

This resolves the product/edition question: the documented target is Japanese
Delphi 2.0J Desktop. That attribution agrees with the independently observed
IME field, enum, virtual methods and helper code. The Japanese library variant
explains the IME layout difference; the Desktop versus Client/Server product
tier alone does not. We still need matching library inputs or a verified
reconstruction to establish complete library correspondence and the exact
patch/build level. The supplied English System 2.01 update does not supply the
missing IME support.

## What the additional downloads actually change

The [media comparison report](media-review.json) retains package/payload hashes,
key compiler/DCU hashes, native observations and original/candidate fixtures.

| Supplied input | Verified result |
|---|---|
| `Borland Delphi Desktop 2.0(1).7z` | Contains a Desktop `DATA.Z` with 1,095 records; 304 selected compiler/library/doc files extracted |
| `2.0 Desktop_Borland_Delphi_2.iso` | Its `DATA.Z` is byte-identical to the Desktop archive's payload |
| `Borland Delphi for Windows 32.ver.2.0.English.7z` | Its `DATA.Z` is byte-identical to those other two inputs |
| `System.dcu.ver.2.01.English.zip` | `SYSTEM.DCU` is byte-identical to the update already present in the earlier Client/Server archive |

Shared Desktop payload SHA-256:
`569ac47bc2edcbaaa137cabb2a2971cbdda4a4ff47dab048cf1eaca3c1ab8ecd`.
The supplied System update SHA-256 is
`88a8ec820d6de46441e09c2879d1b5891be53d67cf3df477f75ebe054605817a`.
Package filenames are not authentication of release provenance.

The Desktop compiler and several DCUs differ from the earlier Client/Server
inputs. We compiled the same framework probe against Desktop base units and
against Desktop with the supplied 2.01 System overlay. Both builds/run succeed:
**38 native checks and 26 emulator fixtures** pass. Both reproduce eight of the
nine selected normalized runtime shapes and both retain the mismatch:

| Class | Original | Desktop base | Desktop + supplied System update |
|---|---:|---:|---:|
| TControl | 168 | 168 | 168 |
| TWinControl | 256 | 252 | 252 |
| TButton | 268 | 264 | 264 |
| TForm | 432 | 428 | 428 |
| TTimer | 52 | 52 | 52 |

The original neighbor-classifier reconstruction also compiles with this
different compiler to **all 282 original bytes**, with **9,216 matching effect
comparisons**. That is still the same one gameplay routine, not another newly
recovered game rule or independent full-game validation.

The System ZIP's bundled README describes changes to file-sharing modes and
memory-suballocator bookkeeping. The supplied update demonstrably does not fix
the VCL layout. These observations do not establish whether the original uses
some other part of a complete 2.01 release.

## Why the layout differs

The existing original RTTI inventory already contains the decisive information.
Our previous focused compiler analysis failed to correlate it with the class
size mismatch. No new decompilation was needed to expose this field.

| Evidence in pinned TSW.exe | Interpretation |
|---|---|
| TWinControl HelpContext field at `$D0` | Same location as English source |
| TForm and multiple input controls publish ImeMode at `$D4` | Added mode field before the keyboard events |
| OnKeyDown at `$D8`, OnKeyPress at `$E0`, OnKeyUp at `$E8` | Four-byte shift after the new byte field and alignment |
| TButton OnEnter at `$F0`, OnExit at `$F8` | The shift persists through the inherited event fields |
| Constructor instruction at `0x00414424` writes zero to byte `[Self+$D4]` | Initializes mode to ordinal zero |
| VMT slot `$78` points to `0x00415DA4` | Reads the mode field and calls the IME status helper |
| VMT slot `$7C` points to `0x00415DBC` | Tests disabled mode and calls the enable helper |

Relevant retained original spans are
[constructor](../original/whole-program/decompiled/004143c4.asm),
[mode setter](../original/whole-program/decompiled/00415da4.asm),
[mode resetter](../original/whole-program/decompiled/00415dbc.asm),
[status helper](../original/whole-program/decompiled/0040ee88.asm),
[enable helper](../original/whole-program/decompiled/0040ee6c.asm), and
[dynamic API initialization](../original/whole-program/decompiled/0040efa0.asm).

The executable dynamically binds IME functions rather than listing them in its
PE imports. The initializer loads `imm32.dll` and resolves context, conversion,
open-status and release APIs; it also obtains the legacy enable function from
`user32`. Looking only at import names would miss these dependencies.

The original field is one byte. Delphi's field alignment moves the following
method-pointer event to the next four-byte boundary. This explains the size
shift. It also adds two virtual methods: blindly adjusting field offsets would
leave the method table and IME behavior incomplete.

## What the online search supplied

The most useful discovery is Hideaki Tominaga/DEKO's
[Diff.chm declaration reference](https://ht-deko.com/tech053.html#DIFFCHM).
The author describes it as a comparison of Delphi units across versions 1
through 2007, generated from declarations. Its linked ZIP downloads successfully.
We extracted five HTML pages with 7-Zip; no CHM viewer or executable was launched.

ZIP SHA-256:
`9d998eaa662e6f22b28f12eeb73934d5e42279a77243cf0856b3f6ab9c0ae968`.
CHM SHA-256:
`3280a5a17fa7de0164c810518caaaf110d54e86960468c07e70f3437f9d22cc9`.
Downloaded documents remain in ignored `build/research/ime-web/`.

Its Delphi 2 Controls page lists the **same nine enum members in the same
ordinal order** as the original executable. The TWinControl page gives
`FImeFlag` as the backing field and declares the mode setter/resetter as virtual.
The separate IMECtrl page supplies names and signatures corresponding to the
two standalone original helpers. These are unusually strong declaration
matches. They are not implementation bodies or original-build DCUs, and the
archive alone does not authenticate which localized release its inputs used.

Its Delphi 3 page changes the enum order and expands the values, agreeing with
the broader distinction shown by
[modern official VCL documentation](https://docwiki.embarcadero.com/Libraries/Florence/en/Vcl.Controls.TImeMode).
A later IME implementation cannot be substituted by name alone.

[Microsoft's public IME sample](https://github.com/microsoft/Windows-classic-samples/blob/main/Samples/Win7Samples/winui/input/ime/imeapps/Mode.c)
provides useful API usage and conversion-mask context. The supplied Client/Server
media already contains `source/RTL/WIN/IMM.PAS`, so we also have period Pascal
API declarations. Neither replaces the original helper's actual branch ordering,
loading policy or call effects. Microsoft's
[ImmSetConversionStatus documentation](https://learn.microsoft.com/en-us/windows/win32/api/immdev/nf-immdev-immsetconversionstatus)
also describes focus-related behavior changes beginning with Windows 8, which
matters when defining the environment for a fidelity claim.

Bob Swart's own
[Delphi 3-to-2 conversion utility page](https://drbob42.com/tools/convert2.htm)
treats IME properties as Delphi 3 additions for its target libraries. Together
with our English media, this reinforces why edition/locale and library contents
must be checked rather than assuming every product named Delphi 2 has the same
declarations. Its property-stripping utility would discard original metadata,
so it is useful as historical evidence rather than a reconstruction tool here.

No exact Delphi 2 IME-enabled VCL source/DCU distribution was established in
this search. The installed documentation now identifies Japanese Delphi 2.0J
Desktop as the target product; its exact compiler/DCU patch build remains
unverified.

## Reconstruction and verification achieved

[RecoveredIme.pas](recovered/RecoveredIme.pas) was reconstructed from the pinned
original code. It contains ordinary Pascal conditions, typed API-pointer calls
and a case statement, with no assembly implementation or original-code blob.
Public declarations corroborate the interface; implementations were recovered
from the executable.

| Reconstructed span | Verified correspondence |
|---|---|
| Enable helper at `0x0040EE6C` | **27/27 literal bytes match** |
| Status dispatcher at `0x0040EE88` | **253-byte span matches after six explicit local jump-table address relocations**, including its 20-byte table |
| Mode comparisons | **264 cases pass**, covering all nine defined values, invalid ordinals 9/255, missing library, missing context, three conversion/sentence scenarios, API success/failure results |
| Enable comparisons | **12 cases pass**, including absent function pointer and multiple return values |

The [IME report](ime-review.json) retains source/build/artifact hashes, every
relocated operand, original/candidate API traces and the public-declaration
correspondence. Unlike the broader runtime shape check, this comparison keeps
all API pointer slots literal and preserves local jump-table destination offsets.
The tests compare ordered API calls, their arguments, returns and output values,
and reject unexpected non-stack writes. The models represent Windows calls;
they are not real input-method tests on the original OS. False-return fixtures
still supply output values, as enumerated in the report. The dynamic loader,
missing individual API pointers with a loaded module, notifications, real focus
and VCL integration remain outside this verification.

The source uses original absolute global addresses only for emulation. Its DLL
must never be called in an ordinary native process. Delphi 2 crashed when the
API slots were declared as absolute procedural variables in the initial
experiment; pointer slots with typed calls compile successfully and emit the
corresponding code.

Nine adversarial comparison tests now pass. The three added tests demonstrate
that changing a local IME jump-table target, swapping an API slot, or changing
a conversion constant is detected. The target/constant mutations also change
observed API effects. Complete runtime and game recovery flags remain false.

## Recommendation for the full project

A compiler-assisted Pascal reconstruction is a strong direction if original
Windows fidelity is the priority. The two supplied compilers can reproduce a
gameplay routine literally, and the missing IME helper implementation can be
recovered despite not having exact VCL source. This is better evidence for the
approach than a passing count of selected C++ comparisons.

Build it as a verified reference project, progressing toward the whole game.
First integrate the IME declarations, original class field/method layouts and
recovered helpers into a consistently rebuilt VCL. Then reconstruct one
complete game form with its original resources and an input/action/timer/dialog
flow, including Flight eligibility and landing. Measure state writes and
transitive effects as well as code correspondence. Preserve visibly missing
implementations rather than generating empty callbacks to make the project
compile. Progressively widen coverage until the whole project is recovered.

The author's exact source text and exact choice of Pascal if/case syntax are
not uniquely recoverable. Equivalent source texts can produce the same machine
instructions. A meaningful target is complete correspondence of executable
branches, state effects, helper calls, data and resources, with every difference
and uncovered path recorded. Pixel equality needs original assets and a fixed
Windows/DPI/font/theme/palette environment, controlled input/timer sequencing,
and image comparisons. The language alone cannot certify it.

At this review's checkpoint, the work had not started a replacement game,
established pixel equality or found another C++ gameplay discrepancy. It resolved
the field-offset question and demonstrated a practical method for recovering
part of the unavailable library variant. The user subsequently accepted omitted
IME behavior and authorized the [native Delphi reconstruction](../../delphi/README.md),
whose separate inventory and comparisons record the new project's progress.

## Reproduction

Use the existing pinned extraction tool and keep each media package separate.
After extracting the three Desktop inputs and System ZIP to the subdirectories
enumerated by `tools/review_delphi2_media.py`, run from the repository root:

```powershell
& C:\Python314\python.exe tools/prepare_delphi2_reference.py --media 'build/research/delphi2-additional-media/desktop7z/Borland Delphi Desktop 2.0' --extractor build/research/idecomp --archive 'D:\Downloads\Borland Delphi Desktop 2.0(1).7z' --output build/research/delphi2-desktop
& C:\Python314\python.exe tools/review_delphi2_media.py
& C:\Python314\python.exe tools/review_delphi2_media.py --check
```

Download the linked ZIP from DEKO's page, verify its hash above and extract
`Diff.chm` into `build/research/ime-web/`. Extract only the selected HTML files:

```powershell
& 'C:\Program Files\7-Zip\7z.exe' x build/research/ime-web/Diff.chm '-obuild/research/ime-web/docs' -y 'Diff\2\VCL\Controls.html' 'Diff\2\VCL\Controls.TWinControl.html' 'Diff\2\VCL\IMECtrl.html' 'Diff\2\VCL\Forms.TForm.html' 'Diff\3\VCL\Controls.html'
& C:\Python314\python.exe tools/verify_delphi2_ime.py
& C:\Python314\python.exe tools/verify_delphi2_ime.py --check
& C:\Python314\python.exe tools/test_delphi2_reference.py
```

The compiler and private framework probes run natively; recovery DLLs and the
original game are read/executed only as bytes in emulation. All Borland inputs,
downloaded documentation and compiled binaries stay in ignored `build/`.
