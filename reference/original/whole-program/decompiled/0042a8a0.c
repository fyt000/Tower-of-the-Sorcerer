/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0042a8a0.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0042a8a0(int *param_1)

{
  WPARAM wParam;
  HWND hWnd;
  UINT Msg;
  LPARAM lParam;
  
  if (0 < param_1[0x43]) {
    lParam = 0;
    wParam = (param_1[0xb] + param_1[0x43] + -3) / param_1[0x43];
    Msg = 0x195;
    hWnd = (HWND)FUN_00416cbc(param_1);
    SendMessageA(hWnd,Msg,wParam,lParam);
  }
  return;
}

