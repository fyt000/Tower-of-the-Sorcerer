/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0042a5d4.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0042a5d4(int param_1,WPARAM param_2,int *param_3)

{
  HWND hWnd;
  uint uVar1;
  undefined4 uVar2;
  undefined4 extraout_EDX;
  UINT Msg;
  int *lParam;
  int aiStack_100c [1024];
  
  lParam = aiStack_100c;
  Msg = 0x189;
  aiStack_100c[0] = param_1;
  hWnd = (HWND)FUN_00416cbc(*(int **)(param_1 + 8));
  uVar1 = SendMessageA(hWnd,Msg,param_2,(LPARAM)lParam);
  if ((int)uVar1 < 0) {
    uVar2 = FUN_004074cc(0x408a3c,CONCAT31((int3)((uint)extraout_EDX >> 8),1),0xf00c);
    uVar1 = FUN_004031f8(uVar2);
  }
  FUN_004035bc(param_3,aiStack_100c,uVar1);
  return;
}

