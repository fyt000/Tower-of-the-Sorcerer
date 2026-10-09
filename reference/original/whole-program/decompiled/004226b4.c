/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x004226b4.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_004226b4(int *param_1)

{
  HWND pHVar1;
  HWND pHVar2;
  
  if (((int *)param_1[0x43] != (int *)0x0) && (param_1[0x4c] == 0)) {
    param_1 = (int *)param_1[0x43];
  }
  pHVar1 = (HWND)FUN_00416cbc(param_1);
  SetFocus(pHVar1);
  pHVar1 = (HWND)FUN_00416cbc(param_1);
  pHVar2 = GetFocus();
  if (pHVar1 == pHVar2) {
    FUN_00413cb8(param_1,0xb029,0,0);
  }
  return;
}

