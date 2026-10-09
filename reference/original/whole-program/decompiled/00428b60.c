/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00428b60.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_00428b60(int *param_1)

{
  HWND pHVar1;
  uint uVar2;
  UINT Msg;
  WPARAM wParam;
  int nIndex;
  LPARAM lParam;
  
  (**(code **)(*param_1 + -0x10))();
  if (DAT_0048a694 != '\0') {
    nIndex = -0x10;
    pHVar1 = (HWND)FUN_00416cbc(param_1);
    uVar2 = GetWindowLongA(pHVar1,nIndex);
    if ((uVar2 & 4) == 0) {
      lParam = 0;
      wParam = 3;
      Msg = 0xd3;
      pHVar1 = (HWND)FUN_00416cbc(param_1);
      SendMessageA(pHVar1,Msg,wParam,lParam);
    }
  }
  return;
}

