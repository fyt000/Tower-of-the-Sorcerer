/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0042a62c.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_0042a62c(int param_1,WPARAM param_2)

{
  HWND hWnd;
  LRESULT LVar1;
  undefined4 uVar2;
  undefined4 extraout_EDX;
  UINT Msg;
  LPARAM lParam;
  
  lParam = 0;
  Msg = 0x199;
  hWnd = (HWND)FUN_00416cbc(*(int **)(param_1 + 8));
  LVar1 = SendMessageA(hWnd,Msg,param_2,lParam);
  if (LVar1 == -1) {
    uVar2 = FUN_004074cc(0x408a3c,CONCAT31((int3)((uint)extraout_EDX >> 8),1),0xf00c);
    FUN_004031f8(uVar2);
  }
  return;
}

