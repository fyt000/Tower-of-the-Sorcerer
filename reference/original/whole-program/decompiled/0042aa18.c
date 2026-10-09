/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0042aa18.
 * Inferred types, shared tails and runtime effects require assembly review. */

bool FUN_0042aa18(int *param_1,WPARAM param_2)

{
  HWND hWnd;
  int iVar1;
  undefined4 uVar2;
  undefined4 extraout_EDX;
  UINT Msg;
  LPARAM lParam;
  
  lParam = 0;
  Msg = 0x187;
  hWnd = (HWND)FUN_00416cbc(param_1);
  iVar1 = SendMessageA(hWnd,Msg,param_2,lParam);
  if (iVar1 == -1) {
    uVar2 = FUN_004074cc(0x4089bc,CONCAT31((int3)((uint)extraout_EDX >> 8),1),0xf00c);
    iVar1 = FUN_004031f8(uVar2);
  }
  return iVar1 != 0;
}

