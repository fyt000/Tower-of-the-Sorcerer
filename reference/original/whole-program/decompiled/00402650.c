/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00402650.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00402650(int param_1)

{
  int iVar1;
  
  if (param_1 != 0) {
    iVar1 = (*(code *)PTR_FUN_00489008)();
    if (iVar1 == 0) {
      FUN_004026d0(1);
      return;
    }
  }
  return;
}

