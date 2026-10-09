/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0042f58c.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_0042f58c(int *param_1)

{
  LPARAM lParam;
  HWND hWnd;
  UINT Msg;
  WPARAM wParam;
  
  root_00416384(param_1);
  lParam = FUN_00419b00(param_1[0x12]);
  wParam = 0;
  Msg = 0x443;
  hWnd = (HWND)FUN_00416cbc(param_1);
  SendMessageA(hWnd,Msg,wParam,lParam);
  return;
}

