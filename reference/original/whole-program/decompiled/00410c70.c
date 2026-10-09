/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00410c70.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00410c70(int *param_1)

{
  undefined4 uVar1;
  
  if (param_1[9] != 0) {
    uVar1 = FUN_00410bdc(param_1);
    if ((char)uVar1 != '\0') {
      DrawMenuBar((HWND)param_1[9]);
    }
  }
  return;
}

