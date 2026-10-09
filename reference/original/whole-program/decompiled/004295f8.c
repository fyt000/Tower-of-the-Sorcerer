/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x004295f8.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_004295f8(int *param_1,byte param_2)

{
  uint wParam;
  HWND hWnd;
  UINT Msg;
  LPARAM lParam;
  
  lParam = 0;
  wParam = (uint)param_2;
  Msg = 0x14f;
  hWnd = (HWND)FUN_00416cbc(param_1);
  SendMessageA(hWnd,Msg,wParam,lParam);
  return;
}

