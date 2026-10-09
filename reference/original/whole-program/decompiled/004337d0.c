/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x004337d0.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_004337d0(int **param_1)

{
  int **ppiVar1;
  uint extraout_ECX;
  undefined4 extraout_EDX;
  
  ppiVar1 = param_1;
  if (*(char *)((int)param_1 + 0x115) == '\x03') {
    for (; (ppiVar1 != (int **)0x0 && (ppiVar1[0x34] == (int *)0x0)); ppiVar1 = (int **)ppiVar1[8])
    {
    }
    if (ppiVar1 == (int **)0x0) {
      FUN_0042a370(param_1);
      return;
    }
    FUN_0042524c(DAT_0048a6f8,(ULONG_PTR)ppiVar1[0x34]);
  }
  else if (*(char *)((int)param_1 + 0x115) == '\x06') {
    ppiVar1 = FUN_0041fffc(param_1);
    if (ppiVar1 == (int **)0x0) {
      FUN_0042a370(param_1);
      return;
    }
    FUN_004235d8((int *)ppiVar1,extraout_EDX,extraout_ECX);
  }
  else {
    FUN_0042a370(param_1);
  }
  return;
}

