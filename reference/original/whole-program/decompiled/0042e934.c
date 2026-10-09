/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0042e934.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0042e934(int param_1,WPARAM param_2,undefined *param_3)

{
  HWND pHVar1;
  WPARAM WVar2;
  LRESULT LVar3;
  undefined *lParam;
  int lParam_00;
  UINT UVar4;
  WPARAM wParam;
  LPARAM LVar5;
  
  if (-1 < (int)param_2) {
    LVar5 = 0;
    UVar4 = 0xbb;
    pHVar1 = (HWND)FUN_00416cbc(*(int **)(param_1 + 8));
    WVar2 = SendMessageA(pHVar1,UVar4,param_2,LVar5);
    if (WVar2 != 0xffffffff) {
      LVar5 = 0;
      UVar4 = 0xc1;
      wParam = WVar2;
      pHVar1 = (HWND)FUN_00416cbc(*(int **)(param_1 + 8));
      LVar3 = SendMessageA(pHVar1,UVar4,wParam,LVar5);
      lParam_00 = LVar3 + WVar2;
      UVar4 = 0xb1;
      pHVar1 = (HWND)FUN_00416cbc(*(int **)(param_1 + 8));
      SendMessageA(pHVar1,UVar4,WVar2,lParam_00);
      lParam = FUN_00403814(param_3);
      WVar2 = 0;
      UVar4 = 0xc2;
      pHVar1 = (HWND)FUN_00416cbc(*(int **)(param_1 + 8));
      SendMessageA(pHVar1,UVar4,WVar2,(LPARAM)lParam);
    }
  }
  return;
}

