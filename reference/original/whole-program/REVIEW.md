# Whole-program accounting and runtime review — 2026-10-09

Whole-executable bookkeeping is now retained. Complete recovery of original
Pascal source, discovery of every executable path, and behavioral equivalence
remain unestablished. The campaign is stopped. This work reads the pinned EXE,
performs temporary analysis in a read-only Ghidra project, and writes research
artifacts. It does not launch the game, alter its installation, or reload MCP.

## What is now accounted for

The original SHA-256 is
`41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779`.
Ghidra 11.0.3, x86 little-endian 32-bit analysis, supplies the retained
[analysis snapshot](analysis-snapshot.json). The separate
[discovery snapshot](discovery-snapshot.json) is the input to structural
recovery. Keeping both makes the discovery/expansion boundary reproducible.

| Evidence | Result | Meaning and limit |
|---|---:|---|
| Machine entry exports | 3,298 C-like/assembly pairs, zero decompiler failures | Includes runtime functions, exception stubs, continuations and shared entries; not 3,298 independent Pascal procedures or game rules |
| Independently rooted entries | 3,250, all resolve to exports | Call/flow targets, class methods, property accessors, supported callback candidates and installed exception entries |
| Class metadata | 133 classes; 549 property records; 281 published fields | VMT ancestry, methods, managed fields and class/property RTTI parsed with no reported parse failures |
| Other referenced RTTI | 74 records | Ordinal, enum, set, string and event signatures; not a claim that every type has RTTI |
| Exception registration | 362 installed stack-frame sites | FS registration decoded independently of Ghidra's data-reference annotations |
| Previously unexported targets | All 102 have new exports | Closes the earlier retained-corpus direct-target gap |
| Detected direct transfers | 12,378 records; 11,998 encode CALL | The remaining records are tail/overridden flows reported as calls by Ghidra; counts are not branch coverage |
| Complete CODE assembly | 482,247 decoded instruction bytes checked against the EXE | Includes bytes outside function bodies and the 101-byte metadata conflict |
| Whole file | All 1,237,504 file bytes partitioned; eight PE sections, 312 imports, 90 resources inventoried | CODE gets a byte ledger; other sections get structural accounting, not full semantic review |

The [index](INDEX.md), [ledger](ledger.json), [byte partition](byte-ledger.tsv),
[complete instruction listing](CODE.asm), and
[structural inventory](structural-inventory.json) contain the evidence.
Every C and assembly export has a hash. Assembly instructions are compared
with the corresponding original machine bytes, and their ownership/body
boundaries are checked separately.

The CODE virtual size is **556,692 bytes**. Ghidra imported **557,056 bytes**,
including **364 bytes of file padding**. The padding is kept out of the
virtual-byte denominator. The virtual partition is:

| Classification | Bytes |
|---|---:|
| Decoded instructions outside metadata conflicts | 482,146 |
| Structurally validated Delphi metadata | 50,850 |
| Switch data corroborated against original case targets | 2,508 |
| Defined data whose role is not fully reviewed | 6,718 |
| Unresolved bytes | 14,369 |
| Instruction/Delphi-metadata conflict | 101 |
| Total virtual CODE | 556,692 |

Decoded bytes are not automatically correctly decoded. Undefined bytes are
not automatically instructions. The ledger keeps that distinction. The
initial snapshot had 106,117 undefined imported CODE bytes; metadata parsing
and justified flow recovery reduced the *unresolved ledger category*, without
relabeling every unknown byte as code or harmless data.

## Runtime identification without a Delphi installation

Subsequent compiler-assisted work with a locally supplied Delphi 2 archive is
retained separately in [the Delphi reference review](../../delphi2/README.md).
The later [IME and additional-media review](../../delphi2/IME-REVIEW.md)
correlates the class-size shift with the original ImeMode field already present
in this inventory and two virtual IME methods. A public Delphi 2 declaration
reference corroborates the interface; two Pascal helper reconstructions have
matching code and 276 modeled API-trace comparisons. The installed readme
identifies Borland Delphi 2.0J Desktop, consistent with the IME evidence; its
exact compiler/DCU patch build remains unverified. This supplements the
runtime review without changing this snapshot's ledger or establishing another
C++ gameplay discrepancy.
The compiler runs and one reconstructed Pascal gameplay routine reproduces its
282 original instruction bytes exactly. The archive VCL is only a partial
match: three relevant class sizes differ by four bytes and button keyboard
handling uses different offsets. Its compiled reference also corroborates 27
runtime instruction bytes absent from this retained Ghidra snapshot, which
remain enumerated in the supplement. The accounting numbers above describe
this snapshot and are not silently revised by those subsequent observations.

The strongest compiler evidence is **Delphi 2**, rather than Delphi 7:

- TControl's VMT layout uses instance size at `VMT-0x18`, with size `0xA8`.
  TForm is `0x1B0`; the main TTSW10 class is `0x490`.
- Class/property tables and the negative lifecycle slots consistently fit
  the Delphi-2 layout over the recovered class inventory.
- Startup calls `0x403420`, which matches IDR's `System.@InitExe` byte shape;
  the following startup initialization chain agrees with IDR's Delphi-2
  unit-discovery logic.

This is strong family/version evidence, not identification of an exact
compiler patch or library build. Later system knowledge bases also match many
shared routines; aggregate signature counts cannot identify the compiler.

Public [IDR](https://github.com/crypto2011/IDR) recognition records were fetched
at commit `03f38fc0b2e5b972c644e0c80a24872c447aa5b7`. The repository's
[license](IDR-LICENSE.txt), URLs, sizes and SHA-256 hashes are retained. The
extracted Delphi-2 KB contains 13,307 procedure records. **1,226 records** have
at least one qualifying byte-shape match in this executable. Aliases and
multiple addresses remain explicit. These are recognition metadata and masked
machine-code shapes, not purchased Delphi source or an IDE.

Most relevant RTL/VCL machine code is already statically linked into the EXE.
Its import table contains nine Windows DLLs and no Delphi runtime packages.
That allows inspection of the original runtime without installing Delphi.
Dynamic loading, Windows implementations and generated executable code remain
separate boundaries. A Delphi 7 installation would not by itself resolve them
and would not supply a matching Delphi-2 source baseline.

## Concrete gaps found by the wider review

### Successful C decompilation did not imply a complete assembly export

Some named functions had been created before their instructions were decoded.
For example, `dialogue_continue` and `toroad2` had one-byte recorded bodies.
The real item confirmation entry `0x450BA0` initially had a 37-byte recorded
body while its C-like output followed the larger routine. The old artificial
entry `0x450BC5` split its setup. `ExportOriginal.java` created that fragment
without first establishing its independent entry or complete body.

The new corpus removes only that known unrooted fragment, recomputes decoded
flow bodies, and reconciles decompiler basic blocks and switch destinations.
Item confirmation now has **3,989 instruction bytes** in its assembly export;
`moncheck` has **26,011**. Their earlier tiny listing bodies did not represent
the code visible in C. The historical corpora remain unchanged so that the
failure is inspectable. Boundary repairs and decompiler/body conflicts are
retained in the manifest and ledger.

This matters even where emulator comparisons executed the underlying machine
bytes correctly: a source/assembly count or body-based static review could
still omit branches. Export success, byte recovery, translation and testing
are separate milestones.

### Windows callbacks bypass a direct-call graph

[TTimer's constructor](decompiled/0042c314.c) passes `0x42C390` to
[AllocateHWnd](decompiled/0041fe08.c), which installs a generated procedure
through SetWindowLong. [TTimer.WndProc](decompiled/0042c390.asm) detects
`WM_TIMER` (`0x113`) and dispatches dynamic method ID `0xFFF6`. The TTimer
dynamic table resolves that ID to [Timer](decompiled/0042c48c.c), which reads
the `OnTimer` method pair at offsets `0x2C/0x30`. This registration was absent
from ordinary direct-call closure.

[MakeObjectInstance](decompiled/0041fd4c.c) allocates executable memory with
VirtualAlloc and emits callback trampolines. [StdWndProc](decompiled/0041fd24.c)
then invokes a stored code/self pair. Accounting for file bytes cannot account
for all generated code or establish when Windows delivers a callback.

### Exception recovery was another disconnected entry family

The Delphi runtime [HandleAnyException](decompiled/00402f4c.asm) obtains a
registered handler pointer, adds five, and jumps to the continuation.
[HandleFinally](decompiled/00403140.asm) follows the same five-byte stub
convention for cleanup. These edges are absent from ordinary call graphs.
The recognizer now decodes the actual FS registration sequence, including
different frame registers, and retains both handler and supported continuation
roots. Typed exception tables remain an explicit additional layout boundary.

One concrete recovered continuation is
[the Fairy ranking fallback at 0x479EAE](decompiled/00479eae.c): it displays
“Version of Ranking data is old” and constructs temporary ranking data after
the failure path. About 2.3 KiB of that path had remained outside the normal
function listing. Successful-I/O fixtures do not test this continuation.
Recovery here does not establish a newly discovered C++ gameplay discrepancy;
it establishes a previously missing review surface.

### Enabled controls and keyboard delivery still matter

[TControl.Click](decompiled/00413eac.c) invokes its stored event pair without
performing the full user-entry eligibility check. Directly starting a click
handler therefore bypasses framework delivery conditions.
[The button dialog-key handler](decompiled/0042a480.asm) checks Enter/Escape,
button state and [CanFocus](decompiled/00416c2c.c), including parent visibility
and enablement, before dispatching a click. The corresponding class dynamic
entry is independently recovered. [Perform](decompiled/00413cb8.c) routes a
message through a VMT slot; [the application loop](decompiled/00424d6c.c)
also performs message filtering before Windows dispatch.

These are concrete reasons that isolated callback agreement did not establish
legal entry, timer schedules, focus transfer, default-button behavior or
transitive state effects. Runtime recognition does not make such calls pure.

## What remains open

- **14,369 unresolved CODE bytes** and **101 bytes of metadata/instruction
  conflicts** remain enumerated by address and hash. No complete-code claim is
  made for them. Another 6,718 bytes are defined data with unreviewed roles.
- **6,780 decoded bytes lie outside function bodies.** They appear in the
  complete assembly listing, but ownership and calling context need review.
- **397 exports contain decompiler warnings.** Success means output was
  produced; warnings can involve globals, types, control flow or shared tails.
- **881 decompiler block/body ownership conflicts** are retained, especially
  where exception continuations and runtime tails share code. They are not 881
  missing gameplay rules, and competing entries are not deleted blindly.
- Of **2,067 indirect-transfer sites**, 311 resolve to named Windows import
  boundaries, 66 have recovered switch candidates, and **1,690** retain unknown
  targets or delivery context. Static identification of some timer/click
  targets does not resolve every invocation of those instructions.
- There are 70 decompiler switch records; 58 layouts are corroborated against
  original table bytes. The remaining layouts/case ordering remain visible.
- Dynamic callback assignment, exception aliases, generated trampolines,
  external Windows behavior and full natural campaign progression remain
  outside exhaustive verification. No additional floor-access bypass was
  established by this accounting work.

The next behavioral review should prioritize timer/input sequences and
focus/default-button gates, then failed file/ranking I/O and interrupted
continuations. Each should execute the original entry, preserve state across
callbacks, observe downstream effects, and compare the complete sequence.
The retained **6,808** comparisons remain bounded evidence for their listed
scenarios; these research exports add zero behavioral agreement cases.

## Reproduction and guards

With the pinned EXE at `build/research/TSW.exe` and the existing Ghidra project:

```powershell
python tools/fetch_idr_recognition.py
python tools/account_original_program.py --check
python tools/review_whole_program.py --check
python tools/test_whole_program_accounting.py
```

The fetcher verifies every pinned source/signature file and the extracted KB;
it reuses a valid cache. 7-Zip is required only for extraction, not a Delphi IDE.
Use `--check` to verify the existing cache without downloading.

To regenerate, run `account_original_program.py`, then use Ghidra's
analyzeHeadless launcher with `-process TSW.exe -readOnly -noanalysis`,
`-scriptPath tools/ghidra`, and these post-scripts/arguments:

```text
RecoverWholeProgram.java WHOLE/roots.tsv WHOLE/metadata.tsv WHOLE/decompiled reuse-unchanged
InventoryWholeProgram.java WHOLE/analysis-snapshot.json
```

Use absolute paths; WHOLE is `reference/original/whole-program`. The first
analysis can start with `InventoryWholeProgram.java`, then pass that snapshot
to the accounting script. Subsequent passes retain expanded discovery evidence
and close newly exposed direct roots. The `reuse-unchanged` option restores
retained flow evidence and reuses an export only when its pinned hash, complete
assembly and body match. Project mutations are discarded by `-readOnly`.
The historical annotated project and source recovery scripts supply the
baseline names/arrival override; a fresh import can infer different boundaries.

The ledger guard rejects image drift, stale roots/metadata, unmatched export
sets, altered C/assembly, instructions that differ from the EXE, incomplete
decoded-byte partitions and truncated function bodies. Six adversarial checks
exercise signature mutation/ambiguity, export drift, missing byte ranges,
truncated bodies and freshness. They are accounting checks, not game tests.
The full original comparison pipeline now checks and records the whole-program
ledger hash before running its suites. No C++ behavior changed in this phase;
audio tests are excluded as required.
