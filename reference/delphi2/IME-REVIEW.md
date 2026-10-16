# Delphi 2 media and IME reference

The installation's `Readme.txt` identifies **Borland Delphi 2.0J Desktop**.
Its localized IME support explains the class-layout difference from the supplied
English libraries. The exact compiler/DCU patch build remains unverified.
The playable [Delphi game](../../delphi/README.md) uses the accepted English
VCL difference; this directory retains the separate IME recovery evidence.

## Installed documentation identifies the Japanese edition

The installed `Readme.txt`, line 8, names Delphi 2.0J Desktop in its
`[Programmed with]` field. Its SHA-256 is
`f7158dfa7b93b771e8fd83de9efc90979911d8ab71610ac4969236d6c40cb361`.
This attribution agrees with the executable's IME enum, field, virtual methods,
and helper code. The Japanese locale explains the difference; Desktop versus
Client/Server product tier alone does not. The readme does not authenticate a
specific compiler patch.

## What the additional downloads actually change

[media-review.json](media-review.json) records package/payload hashes,
compiler/DCU differences, layouts, and fixture results.

| Supplied input | Finding |
|---|---|
| `Borland Delphi Desktop 2.0(1).7z` | Desktop compiler/library payload |
| `2.0 Desktop_Borland_Delphi_2.iso` | Same `DATA.Z` bytes as the Desktop archive |
| `Borland Delphi for Windows 32.ver.2.0.English.7z` | Same `DATA.Z` bytes as both inputs above |
| `System.dcu.ver.2.01.English.zip` | Same `SYSTEM.DCU` as the Client/Server archive's separate update |

Desktop base and System-overlay probes pass **38 Windows checks and 26 emulator
fixtures**. They reproduce eight of the nine normalized runtime shapes and keep
the same four-byte class-size difference listed in the
[compiler guide](README.md#library-correspondence-and-the-unresolved-abi-difference).
Both compilers emit all 282 neighbor-classifier bytes and pass the same 9,216
effects. The System update changes file sharing/suballocator code; it does not
supply the missing IME support.

## Why the layout differs

| Executable evidence | Meaning |
|---|---|
| `TWinControl.HelpContext` at `$D0` | Matches English source |
| Published `ImeMode` at `$D4` | Added byte field before keyboard events |
| `OnKeyDown/$D8`, `OnKeyPress/$E0`, `OnKeyUp/$E8` | Alignment shifts subsequent fields by four bytes |
| `TButton.OnEnter/$F0`, `OnExit/$F8` | Inherited event shift continues |
| Constructor at `0x00414424` writes zero to `[Self+$D4]` | Default mode ordinal zero |
| VMT `$78` → `0x00415DA4`, `$7C` → `0x00415DBC` | Additional mode setter/resetter methods |

Retained spans: [constructor](../original/whole-program/decompiled/004143c4.asm),
[setter](../original/whole-program/decompiled/00415da4.asm),
[resetter](../original/whole-program/decompiled/00415dbc.asm),
[status helper](../original/whole-program/decompiled/0040ee88.asm),
[enable helper](../original/whole-program/decompiled/0040ee6c.asm), and
[API initializer](../original/whole-program/decompiled/0040efa0.asm).

The initializer dynamically loads `imm32.dll` and resolves context,
conversion, open-status, and release APIs, plus a legacy enable function from
`user32`. PE imports alone omit these dependencies. Matching the localized
library requires both field and virtual-method layouts.

## Public declaration reference

[DEKO's Diff.chm reference](https://ht-deko.com/tech053.html#DIFFCHM) corroborates
the nine enum values in ordinal order, `FImeFlag`, virtual setter/resetter
methods, and standalone helper signatures. Its archive and extracted-page
hashes are in [ime-review.json](ime-review.json). It contains declarations,
not implementation bodies or authenticated game-build DCUs; later Delphi enum
orders differ.

Period `IMM.PAS` declarations are present in the supplied compiler source.
[Microsoft's IME sample](https://github.com/microsoft/Windows-classic-samples/blob/main/Samples/Win7Samples/winui/input/ime/imeapps/Mode.c)
and [conversion-status documentation](https://learn.microsoft.com/en-us/windows/win32/api/immdev/nf-immdev-immsetconversionstatus)
provide API context, including focus-related behavior changes from Windows 8.
The executable's branches and API effects determine the recovered implementation.

## Reconstruction and verification achieved

[RecoveredIme.pas](recovered/RecoveredIme.pas) uses Pascal conditions, a case
statement, and typed API-pointer calls reconstructed from the executable.

| Span/check | Result |
|---|---|
| Enable helper `0x0040EE6C` | 27 literal bytes match |
| Status dispatcher `0x0040EE88` | 253-byte span matches after six explicit jump-table relocations, including its 20-byte table |
| Mode comparisons | 264 cases: nine defined values, invalid 9/255, missing library/context, conversion/sentence scenarios, API success/failure |
| Enable comparisons | 12 cases: absent function pointer and multiple return values |

The [IME report](ime-review.json) retains every relocation and ordered API
trace: arguments, returns, outputs, and unexpected-write checks. API pointer
slots and local destination offsets remain literal. False-return fixtures
still supply the recorded output values. Mutation tests detect changed table
targets, API slots, and conversion constants.

The DLL uses absolute globals only for emulation. Pointer slots with typed
calls compile in Delphi 2; absolute procedural-variable declarations caused a
compiler crash. The modeled API traces do not establish real input-method
behavior. Dynamic loading, individually missing APIs with a loaded module,
notifications, real focus, VCL integration, and whole-window pixels remain
outside these checks.

## Reproduction

Use the [pinned extraction setup](README.md#reproduction), keeping packages
separate. Extract the Desktop inputs and System ZIP to the directories listed
in `tools/review_delphi2_media.py`, then run from the repository root:

```powershell
python tools/prepare_delphi2_reference.py --media 'build/research/delphi2-additional-media/desktop7z/Borland Delphi Desktop 2.0' --extractor build/research/idecomp --archive 'D:\Downloads\Borland Delphi Desktop 2.0(1).7z' --output build/research/delphi2-desktop
python tools/review_delphi2_media.py
python tools/review_delphi2_media.py --check
```

Download `diff.zip` from DEKO's linked page, verify the hash in `ime-review.json`,
and extract `Diff.chm` into `build/research/ime-web/`. Extract these pages:

```powershell
& 'C:\Program Files\7-Zip\7z.exe' x build/research/ime-web/Diff.chm '-obuild/research/ime-web/docs' -y 'Diff\2\VCL\Controls.html' 'Diff\2\VCL\Controls.TWinControl.html' 'Diff\2\VCL\IMECtrl.html' 'Diff\2\VCL\Forms.TForm.html' 'Diff\3\VCL\Controls.html'
python tools/verify_delphi2_ime.py
python tools/verify_delphi2_ime.py --check
python tools/test_delphi2_reference.py
```

The compiler/private framework probes run on Windows; recovery DLLs and original
instruction comparisons run in emulation. Inputs, downloaded documentation,
and binaries stay under ignored `build/`.
