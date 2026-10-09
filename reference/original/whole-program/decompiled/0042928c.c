/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0042928c.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0042928c(int param_1,WPARAM param_2,int *param_3)

{
  HWND hWnd;
  uint uVar1;
  UINT Msg;
  int *lParam;
  int aiStack_100c [1024];
  
  lParam = aiStack_100c;
  Msg = 0x148;
  aiStack_100c[0] = param_1;
  hWnd = (HWND)FUN_00416cbc(*(int **)(param_1 + 8));
  uVar1 = SendMessageA(hWnd,Msg,param_2,(LPARAM)lParam);
  if (uVar1 == 0xffffffff) {
    uVar1 = 0;
  }
  FUN_004035bc(param_3,aiStack_100c,uVar1);
  return;
}

