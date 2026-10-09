/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00416924.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00416924(int param_1,int param_2,int param_3)

{
  bool bVar1;
  BOOL BVar2;
  int iVar3;
  int **ppiVar4;
  int *piVar5;
  int iVar6;
  
  if (*(HWND *)(param_1 + 0xc0) != (HWND)0x0) {
    BVar2 = IsWindowVisible(*(HWND *)(param_1 + 0xc0));
    if (BVar2 != 0) {
      bVar1 = true;
      goto LAB_0041694e;
    }
  }
  bVar1 = false;
LAB_0041694e:
  if (bVar1) {
    ScrollWindow(*(HWND *)(param_1 + 0xc0),param_2,param_3,(RECT *)0x0,(RECT *)0x0);
  }
  iVar3 = FUN_00414ccc(param_1);
  if (-1 < iVar3 + -1) {
    iVar6 = 0;
    do {
      ppiVar4 = (int **)FUN_00414c9c(param_1,iVar6);
      piVar5 = FUN_00402c7c(ppiVar4,(int *)&PTR_FUN_004118e4);
      if (((char)piVar5 == '\0') || (ppiVar4[0x30] == (int *)0x0)) {
        ppiVar4[9] = (int *)((int)ppiVar4[9] + param_2);
        ppiVar4[10] = (int *)((int)ppiVar4[10] + param_3);
      }
      else if (!bVar1) {
        SetWindowPos((HWND)ppiVar4[0x30],(HWND)0x0,(int)ppiVar4[9] + param_2,
                     (int)ppiVar4[10] + param_3,(int)ppiVar4[0xb],(int)ppiVar4[0xc],0x14);
      }
      iVar6 = iVar6 + 1;
      iVar3 = iVar3 + -1;
    } while (iVar3 != 0);
  }
  FUN_00414ac8(param_1);
  return;
}

