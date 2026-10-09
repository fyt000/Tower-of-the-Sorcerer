/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0042882c.
 * Inferred types, shared tails and runtime effects require assembly review. */

undefined4 FUN_0042882c(int *param_1,undefined4 param_2,undefined4 param_3)

{
  HWND hWnd;
  UINT Msg;
  undefined4 *wParam;
  LPARAM lParam;
  undefined4 local_8;
  
  wParam = &local_8;
  lParam = 0;
  Msg = 0xb0;
  local_8 = param_3;
  hWnd = (HWND)FUN_00416cbc(param_1);
  SendMessageA(hWnd,Msg,(WPARAM)wParam,lParam);
  return local_8;
}

