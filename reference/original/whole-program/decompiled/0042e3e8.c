/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0042e3e8.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0042e3e8(int param_1,LPARAM param_2)

{
  bool bVar1;
  HWND hWnd;
  UINT Msg;
  WPARAM wParam;
  
  bVar1 = FUN_00416e54(*(int *)(param_1 + 4));
  if (bVar1) {
    wParam = 0;
    Msg = 0x447;
    hWnd = (HWND)FUN_00416cbc(*(int **)(param_1 + 4));
    SendMessageA(hWnd,Msg,wParam,param_2);
  }
  return;
}

