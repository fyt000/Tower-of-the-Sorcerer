/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x004286a8.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_004286a8(int *param_1,WPARAM param_2)

{
  bool bVar1;
  HWND hWnd;
  UINT Msg;
  LPARAM lParam;
  
  if (param_2 != param_1[0x40]) {
    param_1[0x40] = param_2;
    bVar1 = FUN_00416e54((int)param_1);
    if (bVar1) {
      lParam = 0;
      Msg = 0xc5;
      hWnd = (HWND)FUN_00416cbc(param_1);
      SendMessageA(hWnd,Msg,param_2,lParam);
    }
  }
  return;
}

