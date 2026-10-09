/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00422f2c.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_00422f2c(int *param_1,int param_2)

{
  BOOL BVar1;
  HWND pHVar2;
  int nCmdShow;
  
  if (*(int *)(param_2 + 8) == 1) {
    pHVar2 = (HWND)FUN_00416cbc(param_1);
    BVar1 = IsIconic(pHVar2);
    if (BVar1 == 0) {
      pHVar2 = (HWND)FUN_00416cbc(param_1);
      BVar1 = IsZoomed(pHVar2);
      if (BVar1 == 0) {
        *(undefined *)((int)param_1 + 0x117) = 1;
      }
      else {
        *(undefined *)((int)param_1 + 0x117) = 3;
      }
    }
    else {
      *(undefined *)((int)param_1 + 0x117) = 2;
    }
    (**(code **)(*param_1 + -0x10))(param_1,param_2);
    return;
  }
  if (*(int *)(param_2 + 8) == 3) {
    if (*(char *)((int)param_1 + 0x117) != '\0') {
      nCmdShow = *(int *)((uint)*(byte *)((int)param_1 + 0x117) * 4 + 0x4895d4);
      pHVar2 = (HWND)FUN_00416cbc(param_1);
      ShowWindow(pHVar2,nCmdShow);
      *(undefined *)((int)param_1 + 0x117) = 0;
      return;
    }
  }
  else {
    (**(code **)(*param_1 + -0x10))(param_1,param_2);
  }
  return;
}

