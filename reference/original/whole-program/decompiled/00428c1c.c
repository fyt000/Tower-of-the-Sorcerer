/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00428c1c.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_00428c1c(int *param_1,undefined4 param_2,undefined4 param_3)

{
  HWND hWnd;
  uint uVar1;
  undefined4 extraout_ECX;
  undefined4 extraout_ECX_00;
  int nIndex;
  
  if ((*(char *)(param_1 + 0x42) != '\0') && ((*(byte *)((int)param_1 + 0x36) & 1) == 0)) {
    nIndex = -0x10;
    hWnd = (HWND)FUN_00416cbc(param_1);
    uVar1 = GetWindowLongA(hWnd,nIndex);
    param_3 = extraout_ECX;
    if ((uVar1 & 4) == 0) {
      FUN_0042886c(param_1);
      param_3 = extraout_ECX_00;
    }
  }
  FUN_00416288(param_1,param_2,param_3);
  return;
}

