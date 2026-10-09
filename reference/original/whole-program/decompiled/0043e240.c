/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0043e240.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0043e240(int param_1,undefined4 param_2,LONG *param_3)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  uint uVar5;
  int iVar6;
  LPCSTR lpchText;
  HDC hdc;
  int iVar7;
  uint uVar8;
  RECT *pRVar9;
  undefined4 *in_FS_OFFSET;
  int *piVar10;
  UINT format;
  undefined4 uStack_58;
  undefined *puStack_54;
  undefined *puStack_50;
  undefined *local_40;
  int local_3c [4];
  int local_2c [4];
  RECT local_1c;
  int *local_c;
  undefined4 local_8;
  
  puStack_50 = &stack0xfffffffc;
  local_40 = (undefined *)0x0;
  pRVar9 = &local_1c;
  for (iVar7 = 4; iVar7 != 0; iVar7 = iVar7 + -1) {
    pRVar9->left = *param_3;
    param_3 = param_3 + 1;
    pRVar9 = (RECT *)&pRVar9->top;
  }
  puStack_54 = &LAB_0043e37a;
  uStack_58 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_58;
  local_c = *(int **)(param_1 + 0x104);
  local_8 = param_2;
  FUN_0041a664(local_c,&local_1c);
  iVar7 = 0x10;
  piVar1 = (int *)(**(code **)(**(int **)(param_1 + 0x100) + 0x14))
                            (*(int **)(param_1 + 0x100),local_8);
  if (piVar1 != (int *)0x0) {
    iVar7 = (**(code **)(*piVar1 + 0x20))();
    iVar2 = (**(code **)(*piVar1 + 0x1c))();
    piVar10 = local_2c;
    iVar3 = (**(code **)(*piVar1 + 0x20))();
    FUN_00409258(0,0,iVar3,piVar10,iVar2);
    piVar10 = local_2c;
    iVar2 = (**(code **)(*piVar1 + 0x1c))();
    iVar2 = iVar2 + -1;
    piVar4 = (int *)FUN_0041dad8((int)piVar1);
    uVar5 = FUN_0041a924(piVar4,0,iVar2);
    iVar2 = (**(code **)(*piVar1 + 0x1c))();
    piVar4 = local_3c;
    iVar3 = (**(code **)(*piVar1 + 0x20))();
    iVar6 = (**(code **)(*piVar1 + 0x1c))();
    uVar8 = (local_1c.top + local_1c.bottom) - iVar6;
    iVar6 = (int)uVar8 >> 1;
    if (iVar6 < 0) {
      iVar6 = iVar6 + (uint)((uVar8 & 1) != 0);
    }
    FUN_00409258(local_1c.left + 2,iVar6,iVar3,piVar4,iVar2);
    FUN_0041a32c(local_c,local_3c,(int)piVar1,uVar5,piVar10);
  }
  local_1c.left = iVar7 + local_1c.left + 6;
  format = 0x824;
  pRVar9 = &local_1c;
  iVar7 = -1;
  (**(code **)(**(int **)(param_1 + 0x100) + 0xc))(*(int **)(param_1 + 0x100),local_8,&local_40);
  lpchText = FUN_00403814(local_40);
  hdc = (HDC)FUN_0041a950(*(int **)(param_1 + 0x104));
  DrawTextA(hdc,lpchText,iVar7,pRVar9,format);
  *in_FS_OFFSET = uStack_58;
  puStack_50 = &LAB_0043e381;
  puStack_54 = (undefined *)0x43e379;
  FUN_004034dc((int *)&local_40);
  return;
}

