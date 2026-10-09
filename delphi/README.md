# Native Delphi reconstruction — 2026-10-10

This project reconstructs the original Windows game as ordinary Pascal using
the supplied English Delphi 2 compiler and VCL. The user accepted the unavailable
Japanese IME behavior and its individually proven layout consequences. The
pinned executable and retained decompilation/assembly are the authority. The
implementation does not call the C++ game or embed original gameplay machine
code.

**The project compiles, but it is not a complete playable game.** There are
52 implemented published method bodies and 178 explicitly unrecovered bodies
among the 230 published methods. An implemented body can still call an
unrecovered dependency. The inventory's `implemented-awaiting-comparison` status
does not certify a complete call chain. Every missing body raises
`EUnrecoveredMethod` with its original address.

Main activation now has a recovered body, including its installation-data
fallback. Its comparison currently stops before graphics initialization. Option
application, state/UI startup, the event dispatcher, movement/contact, complete
combat, other items and story callbacks, save/load, and sound paths still need
implementation and comparison. Use the hidden harnesses for measured behavior;
normal development-game activation can reach real installation/settings I/O and
then an unrecovered dependency.

## Source and original content

| File | Purpose |
|---|---|
| [Tower.dpr](Tower.dpr) | Native Win32 application project |
| [OriginalState.pas](src/OriginalState.pas) | Exact 684-byte hero, 6,273-byte maps, 528-byte monster table, six-byte commands, scalar/string state and settings-file storage |
| [OriginalCore.pas](src/OriginalCore.pas) | 18 recovered core procedures: initialization, classification, landing facing, strike arithmetic and command builders |
| [OriginalForms.pas](src/OriginalForms.pas) | Original form classes, modal gates, recovered wrappers and explicit missing-method boundary |
| [OriginalGraphics.pas](src/OriginalGraphics.pas) | Original bitmap globals and raster composition |
| [GraphicsMethods.inc](src/GraphicsMethods.inc) | Graphics initialization, map spiral traversal and both hero animation frames |
| [FlightMethods.inc](src/FlightMethods.inc) | Monster/status display and Flight opener, previews and confirmation |
| [StartupMethods.inc](src/StartupMethods.inc) | Activation body, including the original installation/settings exception path |
| [UiMethods.inc](src/UiMethods.inc) | Key/inventory rendering, main animation timer and special-tile drawing, About/data-holder activation, and two explicitly bounded presentation prefixes |
| [OriginalContent.pas](src/OriginalContent.pas) | Loads exact original monster and render-order tables from resources |
| [generated/](src/generated/) | Restricted-grammar initialization/layout/hints, declarations, missing bodies, form checks and recovery inventory |
| [FormSmoke.dpr](tests/FormSmoke.dpr) | Hidden native forms, every serialized binding/field/method, and real VCL modal gates |
| [GraphicsSmoke.dpr](tests/GraphicsSmoke.dpr) | Real native image lists, canvases, bitmaps and monster labels |
| [StartupIOSmoke.dpr](tests/StartupIOSmoke.dpr) | Hidden real-VCL memo/name/file boundaries using private build-directory fixtures |
| [UISmoke.dpr](tests/UISmoke.dpr) | Native control/font/menu/property witnesses, staged presentation fixtures and ten isolated bitmap captures |
| [CoreRecoveryProbe.dpr](tests/CoreRecoveryProbe.dpr) | Original-address and production-storage DLLs, executed only in emulation |

All five original binary DFM resources are embedded unchanged, preserving their
component properties, event names, text and pictures. The original application
icon and icon-group payloads are also copied exactly, and the application title
is `Tower of the Sorcerer Ver1.2`. Main, About, ranking and data-holder forms are
created in the original entry-point order; the unused template dialog is not
eagerly created. Two exact content tables
are embedded: 33 monster records and the 121-cell render order. Compiled resource
hashes are checked, rather than only extraction-directory hashes.

Cycle initialization restores all 51 floor records and landing metadata in the
original assignment order: 6,439 assignments and four conditions. Graphics
layout has 499 property assignments and 27 signed-half expressions; the hint
tail has 46 hints and 31 ShowHint assignments. Generation rejects unsupported
decompiler statements or expressions. The actual graphics initializer loads
the supplied Data/Data3 assets and slices 218 main sprites, 159 ending sprites
and four key sprites into real VCL image lists.

Native builds use linker-owned storage. `ORIGINAL_ADDRESSES` is exclusively an
emulator probe; that DLL must never be loaded or called natively. A second DLL
uses normal production storage and is compared independently.

Command storage provisions 30,000 records, but the original declared bound is
not authenticated. Comparisons exercise and guard a seeded 512-record prefix;
maximum-queue behavior remains unverified.

## Accepted IME difference

[comparison-policy.json](comparison-policy.json) retains the authorization and
the observed IME field/method/helper family. Each referenced layout difference
has specific evidence: the four-byte form-field displacement, Memo.Lines
`$118 → $114`, ListBox.Items `$100 → $FC`, and Button.SetFocus's virtual slot
`$80 → $78`. The focus target must remain `TWinControl.SetFocus`; bitmap virtual
targets are also authenticated.

The separate `TButton.CMDialogKey` check accepts exactly two operands: Active
`$106 → $102` and Cancel `$105 → $101`. Scalar constants, branch bytes and all
four external callee identities remain checked. There is no blanket offset or
virtual-slot masking, skipped gameplay callback, or ignored game-state effect.
Earlier library mismatches remain recorded; they are not reclassified as passes.

## Measurements and limits

| Retained report | Passing scope |
|---|---|
| [Core/form comparison](comparison-report.json) | 30,120 core comparisons: 15,060 fixtures against each of two compiled storage variants; 384 real native modal-gate comparisons; 13 linked-framework comparisons |
| [Graphics comparison](graphics-comparison-report.json) | 1,848 instruction/effect comparisons against both Tower.exe and GraphicsSmoke.exe; 11,094,272 native pixels against independent original-operation replay |
| [Flight comparison](flight-comparison-report.json) | 1,940 body/sequence comparisons, including 1,296 sequences that carry state from the real opening gate |
| [Startup comparison](startup-comparison-report.json) | 105 installation/settings-prefix comparisons, recovered exception fallback, real old/new memo getter/clear bodies, and hidden native I/O witnesses |
| [UI comparison](ui-comparison-report.json) | 12,397 body/prefix comparisons: 6,263 against UISmoke.exe and 6,134 against production Tower.exe; 1,592 supported native property witnesses; 679,616 isolated bitmap pixels; two unresolved combo-box height witnesses |
| [Unmasked binary accounting](binary-comparison-report.json) | Literal PE-section bytes and complete changed-byte rows, exact resource identities/payloads, decoded string differences and relocated original content tables; this is not an equivalence pass |

Core comparisons require complete exercised state, nested core entry order and
interleaved write address/width/value/order to agree. Unexpected CPU writes
outside tracked state and private stack fail. Neighbor classification has 282
literal matching bytes in the original-address build; instruction equality is
not established for the remaining procedures.

Native form checks verify 130 event bindings, 279 published component fields and
230 method lookups. This proves wiring/layout in the checked forms; it does not
count missing implementations as recovered behavior. The linked-framework
fixtures execute actual button/message/dynamic dispatch and timer library
paths, with only Windows GetKeyState and the observer event modeled.

Graphics effect comparisons cover all 51 floors, all byte tile values, both
layouts/cycle frame sets, all four facings, and screen-width boundary fixtures.
Native pixel checks cover populated atlas cells, key/frame bitmaps, floors 1 and
49 in both animation frames, all four hero facings, and all 33 monster portraits
plus the cleared display. Four native layout/cycle configurations run. Unwritten
atlas tails are excluded. Control bounds and recorded monster text/visibility
also agree. The pixel oracle independently replays original drawing requests
using RGB operations; it is **not an original native screenshot oracle**.
Whole-window/DPI/font/theme/input/timer equivalence remains unproven.

Flight sequences start at the real opener: 216 open successfully and 1,080 stop
at its gate. Successful sequences cover direct confirmation, up/down and
down/up; no state is reseeded between stages. They include absent/nonstandard
Orb values, adjacent stairs, highest-floor limits, special-floor skips, landing
metadata, cleanup, labels, button gates and requested timers. The queued commands
are compared but the dispatcher is not yet implemented. Focus/timer delivery
and input-event reachability remain outside this scope. BGM-enabled paths still
call unrecovered sound methods and are excluded, not accepted as differences.

Startup prefix fixtures stop at `syokidata0` without replacing that game callee.
They cover successful INI/bitmap loading, INI and bitmap failures, fallback save
failure, missing/truncated option files and close failure. Windows/file/VCL I/O
has explicit observer boundaries. Injected failures enter the actual
old/compiled handler through its installed Delphi catch frame; native OS
exception dispatch/unwinding and uncaught-error cleanup remain unverified.
Requests, option bytes, paths, names and ordered game writes are compared; raw
runtime file records containing handles/private pointers are excluded.

The independent native I/O harness also exposed why logical file lines cannot
be assumed to match TMemo.Lines: the original streamed hidden memo wraps long
names. Its physical-line witnesses feed the Windows-message boundary consumed
by the real old/new memo getters. Native fixtures include empty/4/10/11/255/256/
300-byte ASCII names, fallback memo roundtrip, missing-file/save-directory
failures, exact option reads and preservation of unread bytes after short reads.
Other fonts, DPI, encodings and arbitrary long input are not certified.

Twenty-four mutation tests protect the comparison boundaries: eight core/form,
six graphics/Flight/focus, four startup/handler/memo and six UI/raw-resource tests. Deliberate field,
callee, resource, command, gate, layout, raster, pixel and exception-handler
corruptions are rejected. The documented IME operand changes are accepted.

UI comparisons exercise the original key order, 24 key slots, negative counts,
all equipment cases and independently populated item slots, including values
other than one. Main timer comparisons carry state through three ticks in
1,728 sequences per compiled variant. They check all four facings, invalid
facings, frozen state, frame toggling, lazy key rendering and the two-tick
floor-15/floor-35 special-tile counter gates. About comparisons include timer
and icon clicks carried through seven interaction stages for each font choice.
The data-holder activation preserves the original Button2 focus request.

`ApplyOriginalFontPrefix` stops before timer configuration at `$0047F5A8`.
`PrepareOriginalVisualPrefix` stops before the first media setter at `$00431C8C`.
These helpers are linked only by the test harness. Full `optionl1` and
`syokidata2` remain explicit missing methods in production. A prefix comparison
does not certify its caller, sound setup, cleanup or subsequent startup.

The UI fixture entry addresses are checked against the published method table.
During this work, an erroneous fixture address for `image2onclick` was corrected
from `$004340B8` to `$004340B4`. Both retained `image1onclick` assembly exports
omit its final setter/return; the whole-program export also misdecodes a CALLF
at `$004340B0`. The comparison authenticates the complete 31-byte body directly
from the pinned executable, including the real setter at `$004340AC` and return
at `$004340B2`. The incomplete exports remain intact as evidence.

Native UI pixels cover both title frames, sword, shield, Hero Orb and key display
at both sizes, compared with independent replay of original drawing requests.
Fonts are checked by requested/native point size, not glyph pixels. Full-window
captures are all rejected by the foreground/occlusion safeguards on this run:
14 views are recorded as skipped, and only the ten isolated bitmaps are retained.
Ranking and template views remain design-resource fixtures with no recovered
activation claim. The source does not certify whole-window pixels.

Native data-holder font changes cause `DriveComboBox1` to realize heights 24 and
19 after the original code requested height 20 in two modes. The observer models
setter requests; original native combo geometry is not measured. Both mismatches
remain explicit unresolved witnesses, outside the 1,592 supported passing
properties. They are not accepted IME differences or silently counted as passes.

The original About panel's DFM contains `Color = clNone` (`$1FFFFFFF`) and its
labels have black font color. The user's original-game screenshot shows the
black panel and thief icon. The recovered click handler explicitly switches
from ProgramIcon to Image1 (the thief), hiding Image2. These properties and
handlers are preserved. Whether an old/new Windows API change explains the
black panel is not established; `clNone` is not automatically treated as a
transparent panel by this old VCL. No readability QOL is introduced here.

## Raw binary accounting

`compare_delphi_binary.py` compares every section at literal section-relative
offsets, including UI, pointers, relocation bytes, padding and IME operands.
The ignored `build/delphi-game/binary-diff/raw-sections.diff.jsonl` retains every
changed 16-byte row with its old/new hex bytes. Applying these rows reconstructs
each candidate section exactly. Section RVAs, virtual sizes, headers, entry
points and timestamps are reported separately; zero-length BSS file data does
not prove equal storage layout.

The current raw CODE sizes are 557,056 versus 310,784 bytes (virtual sizes
556,692 versus 310,544). CODE, DATA, imports, relocations, `.rdata` and `.rsrc`
differ. The reconstruction remains incomplete, and raw differences are not
automatically categorized as harmless address changes. Per-function semantic
comparisons remain necessary because CODE mixes runtime, UI and gameplay, and
linker placement changes embedded addresses even for equivalent routines.

By resource identity, 70 original payloads match exactly, including all five
DFMs and both icon resources. Eighteen string-table blocks differ and two are
missing, producing 262 differing/missing string-table slots, of which 249 contain
text (13 absent slots are empty). Decoded samples include
Japanese original RTL/VCL messages versus English compiler messages; the missing
blocks contain Japanese weekday and era strings. These are recorded discrepancies
beyond the narrowly accepted IME operands. Two added resources hold the exact
original monster/render-order tables relocated from original DATA/CODE storage.
The 282-byte `ClassifyNeighbor` body in the original-address core DLL also
matches literally. None of these facts establishes whole-EXE equality.

## Exception continuations and decompilation accounting

The new [exception-path inventory](../reference/original/whole-program/exception-paths/inventory.json)
links the published methods' installed Delphi exception frames to their
continuations. It finds 64 frames, all with instructions omitted from the
parent-method export. Most omitted instructions exist elsewhere in the retained
extraction; this is an ownership/control-flow issue, not 64 newly missing bodies.

For example, activation's fallback is already decompiled as
[`root_004429e6`](../reference/original/whole-program/decompiled/004429e6.c),
but its parent `formactivate` export does not express that catch body. The audit
connects the handler at `$004429E1` to the fallback and retains separate assembly
evidence. A score-loading indirect transfer at `$00438C7D` is absent from the
exported instruction-address union and remains unresolved; indirect dispatch is
not guessed. Calls are retained rather than inlined, typed/unknown handlers are
unresolved, and the audit does not establish full exception coverage.

Every comparison report continues to record `full_game_recovered: false` and
`pixel_equivalence_established: false`. Neither all detected functions exported,
all form methods declared, nor selected fixtures passing implies whole-program
semantic recovery or recovery of the author's unique original source.

## Build and verification

The extracted compiler must exist under `build/research/delphi2/`; see
[compiler preparation](../reference/delphi2/README.md). Python requires pefile,
capstone, unicorn, Pillow and NumPy. On this host:

```powershell
& C:\Python314\python.exe tools/reconstruct_delphi_project.py
& C:\Python314\python.exe tools/build_delphi_game.py --smoke
& C:\Python314\python.exe tools/verify_delphi_game.py
& C:\Python314\python.exe tools/verify_delphi_graphics.py
& C:\Python314\python.exe tools/verify_delphi_flight.py
& C:\Python314\python.exe tools/verify_delphi_startup.py
& C:\Python314\python.exe tools/verify_delphi_ui.py
& C:\Python314\python.exe tools/compare_delphi_binary.py
& C:\Python314\python.exe tools/audit_delphi_exception_paths.py
& C:\Python314\python.exe tools/test_delphi_game.py
& C:\Python314\python.exe tools/test_delphi_graphics.py
& C:\Python314\python.exe tools/test_delphi_startup.py
& C:\Python314\python.exe tools/test_delphi_ui.py
& C:\Python314\python.exe tools/reconstruct_delphi_project.py --check
```

The comparison and audit commands also accept `--check` to reject stale retained
reports. A source change requires rebuilding; generated-source changes require
regeneration. `--assets PATH` selects another original installation directory.

Ignored build artifacts include the development EXE/map, two isolated core DLLs,
hidden smoke EXEs/logs, four native graphics fixture directories, private startup
I/O files, isolated UI bitmaps, raw section delta rows and a build report with source/staging/compiler/artifact/log/asset
hashes. Tracked source uses normal newlines; the builder stages CRLF copies for
the legacy compiler. No installer or original game process is run by these
commands. The UI harness briefly shows its own test forms for guarded captures;
it does not drive the original game. The form harness's missing-method test uses the dispatcher, so it
does not invoke normal activation or installation I/O.

## Remaining implementation order

1. Recover option application and `syokidata2`, then compare the complete startup
   chain, including sound setup and failure paths.
2. Recover Flight's originating input handlers and dispatcher/timer delivery,
   plus BGM-enabled paths, carrying state through each real entry.
3. Recover movement/contact, complete combat, remaining items and floor/story
   callbacks. Keep every unsupported call as a failing boundary.
4. Recover original save/load/checkpoint/settings/rankings with successful and
   failing I/O, including the unresolved score-loading dispatch.
5. Reconcile remaining published, unnamed, runtime and exception paths with the
   whole-program ledger, then measure native input/focus/timer sequences and
   full-window pixels in a fixed environment.
