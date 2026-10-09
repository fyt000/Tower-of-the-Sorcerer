/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x004287f0.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_004287f0(int *param_1,byte param_2)

{
  bool bVar1;
  uint wParam;
  HWND hWnd;
  UINT Msg;
  LPARAM lParam;
  
  if (param_2 != *(byte *)((int)param_1 + 0x106)) {
    *(byte *)((int)param_1 + 0x106) = param_2;
    bVar1 = FUN_00416e54((int)param_1);
    if (bVar1) {
      lParam = 0;
      wParam = (uint)param_2;
      Msg = 0xcf;
      hWnd = (HWND)FUN_00416cbc(param_1);
      SendMessageA(hWnd,Msg,wParam,lParam);
    }
  }
  return;
}

