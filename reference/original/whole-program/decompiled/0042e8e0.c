/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0042e8e0.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_0042e8e0(int param_1,WPARAM param_2,int *param_3)

{
  HWND hWnd;
  uint uVar1;
  UINT Msg;
  undefined4 *lParam;
  undefined4 uStack_100c;
  
  lParam = &uStack_100c;
  uStack_100c = CONCAT22((short)((uint)param_1 >> 0x10),0x1000);
  Msg = 0xc4;
  hWnd = (HWND)FUN_00416cbc(*(int **)(param_1 + 8));
  uVar1 = SendMessageA(hWnd,Msg,param_2,(LPARAM)lParam);
  if (((&stack0xffffeff2)[uVar1] == '\r') && ((&stack0xffffeff3)[uVar1] == '\n')) {
    uVar1 = uVar1 - 2;
  }
  FUN_004035bc(param_3,&uStack_100c,uVar1);
  return;
}

