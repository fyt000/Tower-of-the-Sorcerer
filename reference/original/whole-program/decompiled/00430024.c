/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00430024.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00430024(int *param_1)

{
  int extraout_ECX;
  undefined4 extraout_EDX;
  
  FUN_0040e8d4((int)param_1);
  if (((*(byte *)(param_1 + 7) & 0x10) == 0) && (*(char *)((int)param_1 + 0x211) != '\0')) {
    FUN_00430f20(param_1,extraout_EDX,extraout_ECX);
  }
  return;
}

