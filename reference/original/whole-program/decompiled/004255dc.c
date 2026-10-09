/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x004255dc.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_004255dc(int param_1)

{
  bool bVar1;
  HWND pHVar2;
  BOOL BVar3;
  int nCmdShow;
  
  if (*(int *)(param_1 + 0x60) != 0) {
    bVar1 = FUN_00416e54(*(int *)(param_1 + 0x60));
    if (bVar1) {
      pHVar2 = (HWND)FUN_00416cbc(*(int **)(param_1 + 0x60));
      BVar3 = IsWindowVisible(pHVar2);
      if (BVar3 != 0) {
        nCmdShow = 0;
        pHVar2 = (HWND)FUN_00416cbc(*(int **)(param_1 + 0x60));
        ShowWindow(pHVar2,nCmdShow);
      }
    }
  }
  return;
}

