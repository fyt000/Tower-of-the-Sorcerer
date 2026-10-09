/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00428eac.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_00428eac(int param_1,WPARAM param_2)

{
  HWND pHVar1;
  WPARAM WVar2;
  LRESULT LVar3;
  UINT UVar4;
  WPARAM wParam;
  LPARAM LVar5;
  
  LVar5 = 0;
  UVar4 = 0xbb;
  WVar2 = param_2;
  pHVar1 = (HWND)FUN_00416cbc(*(int **)(param_1 + 8));
  WVar2 = SendMessageA(pHVar1,UVar4,WVar2,LVar5);
  if (-1 < (int)WVar2) {
    LVar5 = 0;
    param_2 = param_2 + 1;
    UVar4 = 0xbb;
    pHVar1 = (HWND)FUN_00416cbc(*(int **)(param_1 + 8));
    LVar3 = SendMessageA(pHVar1,UVar4,param_2,LVar5);
    if (LVar3 < 0) {
      LVar5 = 0;
      UVar4 = 0xc1;
      wParam = WVar2;
      pHVar1 = (HWND)FUN_00416cbc(*(int **)(param_1 + 8));
      LVar3 = SendMessageA(pHVar1,UVar4,wParam,LVar5);
      LVar3 = LVar3 + WVar2;
    }
    UVar4 = 0xb1;
    pHVar1 = (HWND)FUN_00416cbc(*(int **)(param_1 + 8));
    SendMessageA(pHVar1,UVar4,WVar2,LVar3);
    WVar2 = 0;
    UVar4 = 0xc2;
    LVar5 = DAT_004896a8;
    pHVar1 = (HWND)FUN_00416cbc(*(int **)(param_1 + 8));
    SendMessageA(pHVar1,UVar4,WVar2,LVar5);
  }
  return;
}

