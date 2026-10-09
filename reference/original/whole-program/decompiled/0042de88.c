/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0042de88.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0042de88(int param_1,undefined4 *param_2)

{
  bool bVar1;
  uint wParam;
  HWND hWnd;
  UINT Msg;
  
  FUN_0042de6c(param_1,param_2);
  bVar1 = FUN_00416e54(*(int *)(param_1 + 4));
  if (bVar1) {
    wParam = (uint)(*(char *)(param_1 + 8) == '\0');
    Msg = 0x43a;
    hWnd = (HWND)FUN_00416cbc(*(int **)(param_1 + 4));
    SendMessageA(hWnd,Msg,wParam,(LPARAM)param_2);
  }
  return;
}

