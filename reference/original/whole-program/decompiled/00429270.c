/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00429270.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00429270(int param_1)

{
  HWND hWnd;
  UINT Msg;
  WPARAM wParam;
  LPARAM lParam;
  
  lParam = 0;
  wParam = 0;
  Msg = 0x146;
  hWnd = (HWND)FUN_00416cbc(*(int **)(param_1 + 8));
  SendMessageA(hWnd,Msg,wParam,lParam);
  return;
}

