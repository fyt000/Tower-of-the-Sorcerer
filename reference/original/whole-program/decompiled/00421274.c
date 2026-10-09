/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00421274.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00421274(int *param_1)

{
  bool bVar1;
  LPARAM lParam;
  HWND pHVar2;
  BOOL BVar3;
  UINT Msg;
  WPARAM wParam;
  
  if (DAT_0048a694 == '\0') {
    pHVar2 = (HWND)FUN_00416cbc(param_1);
    BVar3 = IsIconic(pHVar2);
    if (BVar3 != 0) {
      (**(code **)(*param_1 + 0x44))();
    }
  }
  else {
    bVar1 = FUN_00416e54((int)param_1);
    if ((bVar1) && (*(char *)((int)param_1 + 0x115) != '\x03')) {
      lParam = FUN_00422934((int)param_1);
      wParam = 1;
      Msg = 0x80;
      pHVar2 = (HWND)FUN_00416cbc(param_1);
      SendMessageA(pHVar2,Msg,wParam,lParam);
      return;
    }
  }
  return;
}

