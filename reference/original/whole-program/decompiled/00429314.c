/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00429314.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_00429314(int param_1,undefined *param_2)

{
  undefined *lParam;
  HWND hWnd;
  LRESULT LVar1;
  undefined4 uVar2;
  undefined4 extraout_EDX;
  UINT Msg;
  WPARAM wParam;
  
  lParam = FUN_00403814(param_2);
  wParam = 0;
  Msg = 0x143;
  hWnd = (HWND)FUN_00416cbc(*(int **)(param_1 + 8));
  LVar1 = SendMessageA(hWnd,Msg,wParam,(LPARAM)lParam);
  if (LVar1 < 0) {
    uVar2 = FUN_004074cc(0x411138,CONCAT31((int3)((uint)extraout_EDX >> 8),1),0xf0a6);
    FUN_004031f8(uVar2);
  }
  return;
}

