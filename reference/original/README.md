# Original source evidence

This directory retains evidence from the supported English **Tower of the
Sorcerer for Windows 1.2**. The original is Borland Delphi/VCL. C-like decompiler
exports are inspection aids; the compilable, readable implementation is the
separate [C++ implementation](../../cpp/README.md).

- [Source index](decompiled/INDEX.md): initial 106-function export, ten recovered
  callbacks/helpers and repaired arrival switch.
- [Call map](decompiled/CALLS.md): exported routine relationships and unresolved calls.
- [Research workflow](../../docs/reverse-engineering.md): supported executable,
  Ghidra scripts, translation rules and executable comparisons.
- [Fidelity scope](../../cpp/FIDELITY.md): passing evidence and remaining limits.

The original installation is read only. Source addresses use image base
`0x400000`; inferred fields, register arguments and indirect calls must be checked
against assembly. The repaired arrival export supersedes the incomplete initial
`0046cb1c_ichicheck.c`, which remains in the corpus for comparison.
