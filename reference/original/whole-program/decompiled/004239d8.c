/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x004239d8.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_004239d8(int *param_1)

{
  HWND hWnd;
  UINT Msg;
  WPARAM wParam;
  LPARAM lParam;
  
  lParam = 0;
  wParam = 0;
  Msg = 0xb021;
  hWnd = (HWND)FUN_00416cbc(param_1);
  PostMessageA(hWnd,Msg,wParam,lParam);
  return;
}

