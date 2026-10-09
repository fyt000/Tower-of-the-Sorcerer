/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x004124b0.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_004124b0(int **param_1)

{
  int *piVar1;
  HWND hWnd;
  int **ppiVar2;
  
  ReleaseCapture();
  DAT_00489320 = (int **)0x0;
  if (param_1 != (int **)0x0) {
    piVar1 = FUN_00402c7c(param_1,(int *)&PTR_FUN_004118e4);
    ppiVar2 = param_1;
    if ((char)piVar1 == '\0') {
      if (param_1[8] == (int *)0x0) {
        return;
      }
      ppiVar2 = (int **)param_1[8];
      DAT_00489320 = param_1;
    }
    hWnd = (HWND)FUN_00416cbc((int *)ppiVar2);
    SetCapture(hWnd);
  }
  return;
}

