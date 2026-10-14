# Delphi 2 compiler reference

The original game identifies Delphi 2.0J Desktop; the supplied English libraries
have different IME and class layouts. The exact original compiler patch remains
unverified.

- [comparison-report.json](comparison-report.json): compiler inputs, code
  comparisons and framework probes.
- [IME review](IME-REVIEW.md): localized fields, methods and recovery evidence.
- [RecoveredNeighbor.pas](recovered/RecoveredNeighbor.pas): a gameplay routine
  reconstructed in Pascal and compared with the executable.

## Reproduction

`Borland Delphi Client Server Suite 2.0.7z` supplies the compiler, RTL/VCL source
and update DCUs. The extractor is pinned; manifests record input hashes and
builders reject altered files. Compiler inputs and output stay under ignored
`build/research/delphi2/`.

Run from the repository root with dependencies from `tools/requirements.txt`.
Adjust the local archive path as needed; the pinned original executable must
also be available locally.

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
probe execution. The fixed-address [RecoveryProbe](probes/RecoveryProbe.dpr)
DLL is for CPU emulation only.

## Library correspondence and the unresolved ABI difference

Selected runtime routines match after image addresses and external transfers
are normalized. Object offsets, constants and local branches remain literal.
This does not establish whole-runtime equivalence or identify the author's
Pascal source.

The original `TWinControl` includes an `ImeMode` field and additional virtual
methods absent from the English libraries. Alignment shifts later fields;
a blanket four-byte adjustment cannot reproduce the localized library.
See the [IME review](IME-REVIEW.md) for layouts and reproduction details.

Game build instructions and verification are in the [Delphi README](../../delphi/README.md).
