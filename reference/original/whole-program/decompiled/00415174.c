/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00415174.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00415174(int **param_1)

{
  undefined4 uVar1;
  
  if (param_1[0x30] != (int *)0x0) {
    uVar1 = FUN_00416c74((int)param_1);
    FUN_00415130((int *)param_1);
    FUN_004152ac(param_1);
    if (((char)uVar1 != '\0') && (param_1[0x30] != (int *)0x0)) {
      SetFocus((HWND)param_1[0x30]);
    }
  }
  return;
}

