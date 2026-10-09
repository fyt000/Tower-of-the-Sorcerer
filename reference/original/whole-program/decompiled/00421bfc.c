/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00421bfc.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00421bfc(int *param_1,int *param_2,undefined4 param_3)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  undefined4 uVar5;
  HMENU pHVar6;
  HWND pHVar7;
  HMENU pHVar8;
  undefined4 extraout_ECX;
  undefined4 extraout_ECX_00;
  undefined4 extraout_ECX_01;
  undefined4 extraout_ECX_02;
  undefined4 extraout_ECX_03;
  undefined4 extraout_EDX;
  int iVar9;
  
  if ((param_2 != (int *)0x0) &&
     (iVar2 = FUN_00423bbc(DAT_0048a6fc), param_3 = extraout_ECX, -1 < iVar2 + -1)) {
    iVar9 = 0;
    do {
      iVar3 = FUN_00423bb0(DAT_0048a6fc,iVar9);
      param_3 = extraout_ECX_00;
      if ((param_2 == *(int **)(iVar3 + 0x128)) &&
         (piVar4 = (int *)FUN_00423bb0(DAT_0048a6fc,iVar9), param_3 = extraout_ECX_01,
         param_1 != piVar4)) {
        uVar5 = FUN_0040753c(0x41117c,CONCAT31((int3)((uint)extraout_EDX >> 8),1),0xf0c0,0,
                             &stack0xffffffe8);
        FUN_004031f8(uVar5);
        param_3 = extraout_ECX_02;
      }
      iVar9 = iVar9 + 1;
      iVar2 = iVar2 + -1;
    } while (iVar2 != 0);
  }
  if ((int *)param_1[0x4a] != (int *)0x0) {
    FUN_00410c40((int *)param_1[0x4a],0);
    param_3 = extraout_ECX_03;
  }
  param_1[0x4a] = (int)param_2;
  if ((param_2 == (int *)0x0) ||
     ((FUN_0040e570((int)param_2,(int)param_1,param_3), (*(byte *)(param_1 + 7) & 0x10) == 0 &&
      (*(char *)((int)param_1 + 0x115) == '\x03')))) {
    bVar1 = FUN_00416e54((int)param_1);
    if (bVar1) {
      pHVar6 = (HMENU)0x0;
      pHVar7 = (HWND)FUN_00416cbc(param_1);
      SetMenu(pHVar7,pHVar6);
    }
  }
  else if (((*(char *)(param_1[0x4a] + 0x34) == '\0') && (*(char *)((int)param_1 + 0x11a) != '\x01')
           ) || ((*(byte *)(param_1 + 7) & 0x10) != 0)) {
    bVar1 = FUN_00416e54((int)param_1);
    if (bVar1) {
      pHVar6 = (HMENU)(**(code **)(*(int *)param_1[0x4a] + 0x2c))();
      pHVar7 = (HWND)FUN_00416cbc(param_1);
      pHVar8 = GetMenu(pHVar7);
      if (pHVar6 != pHVar8) {
        pHVar6 = (HMENU)(**(code **)(*(int *)param_1[0x4a] + 0x2c))();
        pHVar7 = (HWND)FUN_00416cbc(param_1);
        SetMenu(pHVar7,pHVar6);
      }
      iVar2 = FUN_00416cbc(param_1);
      FUN_00410c40(param_2,iVar2);
    }
  }
  else if ((*(char *)((int)param_1 + 0x11a) != '\x01') &&
          (bVar1 = FUN_00416e54((int)param_1), bVar1)) {
    pHVar6 = (HMENU)0x0;
    pHVar7 = (HWND)FUN_00416cbc(param_1);
    SetMenu(pHVar7,pHVar6);
  }
  if (*(char *)((int)param_1 + 0x119) != '\0') {
    FUN_004227b8(param_1,'\x01');
  }
  FUN_00421b44(param_1);
  return;
}

