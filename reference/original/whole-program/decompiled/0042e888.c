/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0042e888.
 * Inferred types, shared tails and runtime effects require assembly review. */

LRESULT root_0042e888(int param_1)

{
  HWND pHVar1;
  LRESULT LVar2;
  LRESULT LVar3;
  UINT UVar4;
  WPARAM WVar5;
  LPARAM LVar6;
  LPARAM lParam;
  
  LVar6 = 0;
  WVar5 = 0;
  UVar4 = 0xba;
  pHVar1 = (HWND)FUN_00416cbc(*(int **)(param_1 + 8));
  LVar2 = SendMessageA(pHVar1,UVar4,WVar5,LVar6);
  lParam = 0;
  LVar6 = 0;
  WVar5 = LVar2 - 1;
  UVar4 = 0xbb;
  pHVar1 = (HWND)FUN_00416cbc(*(int **)(param_1 + 8));
  WVar5 = SendMessageA(pHVar1,UVar4,WVar5,LVar6);
  UVar4 = 0xc1;
  pHVar1 = (HWND)FUN_00416cbc(*(int **)(param_1 + 8));
  LVar3 = SendMessageA(pHVar1,UVar4,WVar5,lParam);
  if (LVar3 == 0) {
    LVar2 = LVar2 + -1;
  }
  return LVar2;
}

