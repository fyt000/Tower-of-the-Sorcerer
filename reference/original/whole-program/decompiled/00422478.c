/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00422478.
 * Inferred types, shared tails and runtime effects require assembly review. */

undefined4 FUN_00422478(int *param_1,int *param_2)

{
  int **ppiVar1;
  bool bVar2;
  byte bVar3;
  HWND pHVar4;
  int *piVar5;
  uint uVar6;
  undefined extraout_CL;
  undefined extraout_CL_00;
  undefined extraout_CL_01;
  undefined extraout_CL_02;
  undefined extraout_DL;
  undefined extraout_DL_00;
  undefined extraout_DL_01;
  undefined extraout_DL_02;
  undefined2 extraout_var;
  undefined2 extraout_var_00;
  undefined2 extraout_var_01;
  int *piVar7;
  undefined4 *in_FS_OFFSET;
  undefined4 uVar8;
  code *pcVar9;
  
  DAT_00489588 = DAT_00489588 + 1;
  if (param_1[0x4c] == 0) {
    if (param_1 == param_2) {
      param_1[0x43] = 0;
    }
    else {
      param_1[0x43] = (int)param_2;
    }
  }
  *(int **)(DAT_0048a6fc + 0x3c) = param_2;
  *(int **)(DAT_0048a6fc + 0x40) = param_1;
  FUN_00409b2c(*(undefined4 **)(DAT_0048a6fc + 0x2c),(int)param_1);
  FUN_00409aa8(*(int **)(DAT_0048a6fc + 0x2c),0,param_1);
  if ((*(byte *)((int)param_2 + 0x36) & 0x20) != 0) {
    return 0;
  }
  *(byte *)((int)param_2 + 0x36) = DAT_004226ac | *(byte *)((int)param_2 + 0x36);
  pcVar9 = thunk_FUN_00403140;
  uVar8 = *in_FS_OFFSET;
  *in_FS_OFFSET = &stack0xffffffe0;
  piVar5 = *(int **)(DAT_0048a6fc + 0x4c);
  if (param_1 != piVar5) {
    if (piVar5 != (int *)0x0) {
      pHVar4 = (HWND)FUN_00416cbc(piVar5);
      *(undefined4 *)(DAT_0048a6fc + 0x4c) = 0;
      bVar2 = FUN_0041f9ec(pHVar4,0xb001);
      if (!bVar2) {
        FUN_00403298(bVar2,extraout_DL,extraout_CL,uVar8,pcVar9);
        return 0;
      }
    }
    *(int **)(DAT_0048a6fc + 0x4c) = param_1;
    pHVar4 = (HWND)FUN_00416cbc(param_1);
    bVar2 = FUN_0041f9ec(pHVar4,CONCAT22(extraout_var,0xb000));
    if (!bVar2) {
      FUN_00403298(bVar2,extraout_DL_00,extraout_CL_00,uVar8,pcVar9);
      return 0;
    }
  }
  if (param_1[0x44] == 0) {
    param_1[0x44] = (int)param_1;
  }
  if ((int *)param_1[0x44] != param_2) {
    while (bVar2 = thunk_FUN_00414ad5(param_1[0x44],(int)param_2), !bVar2) {
      pHVar4 = (HWND)FUN_00416cbc((int *)param_1[0x44]);
      param_1[0x44] = *(int *)(param_1[0x44] + 0x20);
      bVar2 = FUN_0041f9ec(pHVar4,CONCAT22(extraout_var_00,0xb01b));
      if (!bVar2) {
        FUN_00403298(bVar2,extraout_DL_01,extraout_CL_01,uVar8,pcVar9);
        return 0;
      }
    }
    while (piVar5 = param_2, (int *)param_1[0x44] != param_2) {
      do {
        piVar7 = piVar5;
        piVar5 = (int *)piVar7[8];
      } while ((int *)piVar7[8] != (int *)param_1[0x44]);
      param_1[0x44] = (int)piVar7;
      pHVar4 = (HWND)FUN_00416cbc(piVar7);
      bVar2 = FUN_0041f9ec(pHVar4,CONCAT22(extraout_var_01,0xb01a));
      if (!bVar2) {
        FUN_00403298(bVar2,extraout_DL_02,extraout_CL_02,uVar8,pcVar9);
        return 0;
      }
    }
    for (ppiVar1 = (int **)param_2[8]; ppiVar1 != (int **)0x0; ppiVar1 = (int **)ppiVar1[8]) {
      piVar5 = FUN_00402c7c(ppiVar1,(int *)&PTR_FUN_0041ea24);
      if ((char)piVar5 != '\0') {
        FUN_0042087c((int *)ppiVar1,param_2);
      }
    }
    FUN_00413cb8(param_1,0xb007,0,param_2);
    piVar5 = (int *)param_1[0x57];
    if ((piVar5 != (int *)0x0) && (piVar5 != param_2)) {
      FUN_00413cb8(piVar5,0xb02a,0,0);
    }
  }
  *in_FS_OFFSET = uVar8;
  uVar6 = (uint)DAT_004226ac;
  bVar3 = (byte)~uVar6 & *(byte *)((int)param_2 + 0x36);
  *(byte *)((int)param_2 + 0x36) = bVar3;
  return CONCAT31((int3)(~uVar6 >> 8),bVar3);
}

