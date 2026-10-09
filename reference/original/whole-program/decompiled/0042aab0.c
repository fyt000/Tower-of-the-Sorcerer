/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0042aab0.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0042aab0(int *param_1,WPARAM param_2)

{
  WPARAM WVar1;
  HWND hWnd;
  UINT Msg;
  LPARAM lParam;
  
  WVar1 = FUN_0042aa80(param_1);
  if (param_2 != WVar1) {
    lParam = 0;
    Msg = 0x197;
    hWnd = (HWND)FUN_00416cbc(param_1);
    SendMessageA(hWnd,Msg,param_2,lParam);
  }
  return;
}

