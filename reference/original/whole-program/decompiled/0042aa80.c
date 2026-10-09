/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0042aa80.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0042aa80(int *param_1)

{
  HWND hWnd;
  UINT Msg;
  WPARAM wParam;
  LPARAM lParam;
  
  lParam = 0;
  wParam = 0;
  Msg = 0x18e;
  hWnd = (HWND)FUN_00416cbc(param_1);
  SendMessageA(hWnd,Msg,wParam,lParam);
  return;
}

