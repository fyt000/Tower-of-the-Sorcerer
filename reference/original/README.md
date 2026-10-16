# Original source evidence

This directory retains decompiled code, assembly and resource evidence from
English **Tower of the Sorcerer for Windows 1.2**, a Borland Delphi/VCL game.

- [Gameplay source index](decompiled/INDEX.md) and [call map](decompiled/CALLS.md).
- [Presentation/input review](presentation/REVIEW.md): forms, event bindings
  and framework boundaries.
- [Whole-program accounting](whole-program/REVIEW.md): executable inventory,
  runtime recognition and unresolved regions.
- [Data and recovery guide](../../docs/original-data.md): extraction and
  comparison workflows.
- [Current Delphi source recovery](../../delphi/README.md): reconstructed Pascal,
  routine-level byte comparisons, build and verification.

Decompiler output is evidence, not the authors' source. Addresses use image base
`0x400000`; inferred fields, register arguments and indirect calls must be checked
against assembly. The repaired arrival export supersedes the incomplete initial
`0046cb1c_ichicheck.c`, which remains in the corpus for comparison.
