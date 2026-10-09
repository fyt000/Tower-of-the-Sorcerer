/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0041549c.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0041549c(int **param_1,int *param_2)

{
  int iVar1;
  bool bVar2;
  int **ppiVar3;
  undefined4 uVar4;
  int *piVar5;
  HWND pHVar6;
  HWND pHVar7;
  int aiStack_1c [2];
  int local_14 [2];
  
  iVar1 = *param_2;
  if (iVar1 < 0x85) {
    if (iVar1 == 0x84) {
      FUN_00413ce8(param_1,param_2);
      if (param_2[3] != -1) {
        return;
      }
      FUN_004052e0(param_2[2],local_14);
      FUN_00413278((int *)param_1,local_14,aiStack_1c);
      piVar5 = FUN_00415350((int)param_1,aiStack_1c,0);
      if (piVar5 == (int *)0x0) {
        return;
      }
      param_2[3] = 1;
      return;
    }
    if (iVar1 == 7) {
      ppiVar3 = FUN_0041fffc(param_1);
      if ((ppiVar3 != (int **)0x0) &&
         (uVar4 = FUN_00422478((int *)ppiVar3,(int *)param_1), (char)uVar4 == '\0')) {
        return;
      }
    }
    else if (iVar1 == 8) {
      if ((*(byte *)((int)param_1 + 0x36) & 0x20) != 0) {
        return;
      }
    }
    else if (iVar1 == 0x1f) {
      pHVar6 = (HWND)FUN_00416cbc((int *)param_1);
      pHVar7 = GetCapture();
      if (((pHVar6 == pHVar7) && (DAT_00489320 != (int *)0x0)) &&
         (param_1 == (int **)DAT_00489320[8])) {
        FUN_00413cb8(DAT_00489320,0x1f,0,0);
      }
    }
  }
  else if (iVar1 - 0x100U < 9) {
    bVar2 = FUN_00413b6c((int)param_1);
    if (bVar2) {
      return;
    }
  }
  else if ((iVar1 - 0x200U < 10) && (bVar2 = FUN_00415410((int *)param_1,param_2), bVar2)) {
    return;
  }
  FUN_00413ce8(param_1,param_2);
  return;
}

