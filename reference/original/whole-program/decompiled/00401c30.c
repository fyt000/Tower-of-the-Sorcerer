/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00401c30.
 * Inferred types, shared tails and runtime effects require assembly review. */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00401c30(int param_1)

{
  _DAT_0048a400 = _DAT_0048a400 + 1;
  _DAT_0048a404 = _DAT_0048a404 + ((*(uint *)(param_1 + -4) & 0x7ffffffc) - 4);
  FUN_00402218(param_1);
  return;
}

