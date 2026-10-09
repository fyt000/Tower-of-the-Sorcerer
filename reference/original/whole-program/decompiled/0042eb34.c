/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0042eb34.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_0042eb34(int param_1,WPARAM param_2)

{
  HWND pHVar1;
  WPARAM WVar2;
  UINT UVar3;
  WPARAM wParam;
  LPARAM LVar4;
  undefined *lParam;
  LRESULT LStack_10;
  
  if (-1 < (int)param_2) {
    LVar4 = 0;
    UVar3 = 0xbb;
    WVar2 = param_2;
    pHVar1 = (HWND)FUN_00416cbc(*(int **)(param_1 + 8));
    WVar2 = SendMessageA(pHVar1,UVar3,WVar2,LVar4);
    if (WVar2 != 0xffffffff) {
      LVar4 = 0;
      param_2 = param_2 + 1;
      UVar3 = 0xbb;
      pHVar1 = (HWND)FUN_00416cbc(*(int **)(param_1 + 8));
      LStack_10 = SendMessageA(pHVar1,UVar3,param_2,LVar4);
      if (LStack_10 == -1) {
        LVar4 = 0;
        UVar3 = 0xc1;
        wParam = WVar2;
        pHVar1 = (HWND)FUN_00416cbc(*(int **)(param_1 + 8));
        LStack_10 = SendMessageA(pHVar1,UVar3,wParam,LVar4);
        LStack_10 = LStack_10 + WVar2;
      }
      UVar3 = 0xb1;
      pHVar1 = (HWND)FUN_00416cbc(*(int **)(param_1 + 8));
      SendMessageA(pHVar1,UVar3,WVar2,LStack_10);
      WVar2 = 0;
      UVar3 = 0xc2;
      lParam = PTR_LAB_004897e8;
      pHVar1 = (HWND)FUN_00416cbc(*(int **)(param_1 + 8));
      SendMessageA(pHVar1,UVar3,WVar2,(LPARAM)lParam);
    }
  }
  return;
}

