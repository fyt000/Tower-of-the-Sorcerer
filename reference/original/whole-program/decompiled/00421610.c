/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00421610.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_00421610(int **param_1,int *param_2)

{
  int **ppiVar1;
  bool bVar2;
  HRGN hRgn;
  HWND pHVar3;
  HRGN pHVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  HANDLE pvVar8;
  int *piVar9;
  BOOL BVar10;
  
  iVar5 = *param_2;
  if (iVar5 - 6U < 3) {
    if (DAT_00489584 == '\0') {
      return;
    }
    if ((*param_2 == 7) && ((*(byte *)(param_1 + 7) & 0x10) == 0)) {
      pHVar3 = (HWND)0x0;
      if (*(char *)((int)param_1 + 0x11a) == '\x02') {
        pvVar8 = FUN_00421984((int)param_1);
        if (pvVar8 != (HANDLE)0x0) {
          piVar9 = (int *)FUN_00421984((int)param_1);
          pHVar3 = (HWND)FUN_00416cbc(piVar9);
        }
      }
      else {
        ppiVar1 = (int **)param_1[0x43];
        if ((ppiVar1 != (int **)0x0) && (param_1 != ppiVar1)) {
          pHVar3 = (HWND)FUN_00416cbc((int *)ppiVar1);
        }
      }
      if (pHVar3 != (HWND)0x0) {
        SetFocus(pHVar3);
        return;
      }
    }
    goto LAB_00421805;
  }
  if (iVar5 != 0xc) {
    if (iVar5 == 0x46) {
      if (DAT_00421818 == (*(byte *)(param_1 + 7) & DAT_00421814)) {
        if (((byte)(*(char *)((int)param_1 + 0x11b) - 1U) < 2) &&
           (*(char *)((int)param_1 + 0x116) != '\x02')) {
          *(uint *)(param_2[2] + 0x18) = *(uint *)(param_2[2] + 0x18) | 2;
        }
        if ((*(char *)((int)param_1 + 0x11b) == '\x01') ||
           (*(char *)((int)param_1 + 0x11b) == '\x03')) {
          *(uint *)(param_2[2] + 0x18) = *(uint *)(param_2[2] + 0x18) | 1;
        }
      }
      goto LAB_00421805;
    }
    if (1 < iVar5 - 0x85U) goto LAB_00421805;
  }
  bVar2 = FUN_00416e54((int)param_1);
  if ((((bVar2) && (*(char *)((int)param_1 + 0x115) == '\x03')) &&
      (*(char *)((int)param_1 + 0xc5) != '\0')) && (DAT_00489578 != (code *)0x0)) {
    if (*param_2 == 0xc) {
      hRgn = CreateRectRgn(0,0,(int)param_1[0xb],(int)param_1[0xc]);
      pHVar4 = hRgn;
      pHVar3 = (HWND)FUN_00416cbc((int *)param_1);
      GetWindowRgn(pHVar3,pHVar4);
      BVar10 = 0;
      pHVar4 = CreateRectRgn(0,0,0,0);
      pHVar3 = (HWND)FUN_00416cbc((int *)param_1);
      SetWindowRgn(pHVar3,pHVar4,BVar10);
      FUN_0041549c(param_1,param_2);
      BVar10 = 0;
      pHVar3 = (HWND)FUN_00416cbc((int *)param_1);
      SetWindowRgn(pHVar3,hRgn,BVar10);
      iVar5 = GetSystemMetrics(7);
      iVar6 = GetSystemMetrics(8);
      iVar7 = GetSystemMetrics(4);
      pHVar4 = CreateRectRgn((int)param_1[9] + iVar5 + 2,(int)param_1[10] + iVar6 + 1,
                             (int)param_1[9] + (int)param_1[0xb] + iVar5 * -2,
                             (int)param_1[10] + iVar7 + iVar6 + -1);
      FUN_00416cbc((int *)param_1);
      (*DAT_00489578)();
      DeleteObject(pHVar4);
      return;
    }
    FUN_00416cbc((int *)param_1);
    iVar5 = (*DAT_00489578)();
    param_2[3] = iVar5;
    return;
  }
LAB_00421805:
  FUN_0041549c(param_1,param_2);
  return;
}

