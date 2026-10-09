/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0042f544.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0042f544(int *param_1,char param_2)

{
  uint wParam;
  HWND hWnd;
  UINT Msg;
  LPARAM lParam;
  
  if (param_2 != *(char *)(param_1 + 0x54)) {
    *(char *)(param_1 + 0x54) = param_2;
    lParam = 1;
    wParam = (uint)*(byte *)(param_1 + 0x54);
    Msg = 0x43f;
    hWnd = (HWND)FUN_00416cbc(param_1);
    SendMessageA(hWnd,Msg,wParam,lParam);
  }
  return;
}

