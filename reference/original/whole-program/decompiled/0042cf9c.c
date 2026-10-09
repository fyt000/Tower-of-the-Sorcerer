/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0042cf9c.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0042cf9c(uint *param_1,uint *param_2,uint **param_3)

{
  int iVar1;
  int *piVar2;
  int *piVar3;
  int iVar4;
  int **ppiVar5;
  int iVar6;
  int iVar7;
  undefined4 extraout_EDX;
  undefined4 extraout_EDX_00;
  undefined4 extraout_EDX_01;
  undefined4 extraout_EDX_02;
  int *in_FS_OFFSET;
  int iStack_50;
  undefined *puStack_4c;
  undefined *puStack_48;
  int iStack_44;
  undefined *puStack_40;
  undefined *puStack_3c;
  undefined4 *local_2c;
  uint *local_28;
  int local_24;
  int local_20;
  tagSIZE local_1c;
  int **local_14;
  undefined local_d;
  uint **local_c;
  uint *local_8;
  
  puStack_3c = &stack0xfffffffc;
  local_2c = (undefined4 *)0x0;
  local_28 = (uint *)0x0;
  puStack_40 = &LAB_0042d273;
  iStack_44 = *in_FS_OFFSET;
  *in_FS_OFFSET = (int)&iStack_44;
  local_d = 0;
  puStack_48 = (undefined *)0x42cfd9;
  local_c = param_3;
  local_8 = param_2;
  local_14 = (int **)FUN_00420b34((int *)&PTR_FUN_0041edfc,CONCAT31((int3)((uint)param_2 >> 8),1),
                                  DAT_0048a6f8);
  puStack_4c = &LAB_0042d24e;
  iStack_50 = *in_FS_OFFSET;
  *in_FS_OFFSET = (int)&iStack_50;
  puStack_48 = &stack0xfffffffc;
  iVar1 = FUN_00421a54((int)local_14);
  FUN_0041a8bc(iVar1);
  piVar2 = (int *)FUN_00421a54((int)local_14);
  FUN_0042c898(piVar2,&local_1c);
  FUN_0042194c(local_14,'\x03');
  FUN_004135d4((int *)local_14,param_1);
  iVar1 = MulDiv(0xb4,local_1c.cx,4);
  FUN_004214f0((int *)local_14,iVar1);
  iVar1 = MulDiv(0x3f,local_1c.cy,8);
  FUN_0042151c((int *)local_14,iVar1);
  FUN_00421dc4(local_14,'\x04');
  piVar2 = FUN_00428174((int *)&PTR_FUN_004259bc,CONCAT31((int3)((uint)extraout_EDX >> 8),1),
                        (int *)local_14);
  (**(code **)(*piVar2 + 0x3c))(piVar2,local_14);
  (**(code **)(*piVar2 + 0x5c))(piVar2,1);
  iVar1 = MulDiv(8,local_1c.cx,4);
  FUN_00413098(piVar2,iVar1);
  iVar1 = MulDiv(8,local_1c.cy,8);
  FUN_004130b8(piVar2,iVar1);
  FUN_004135d4(piVar2,local_8);
  piVar3 = FUN_004285a4((int *)&PTR_FUN_00425fdc,CONCAT31((int3)((uint)extraout_EDX_00 >> 8),1),
                        (int *)local_14);
  (**(code **)(*piVar3 + 0x3c))(piVar3,local_14);
  FUN_00413098(piVar3,piVar2[9]);
  iVar1 = MulDiv(0x13,local_1c.cy,8);
  FUN_004130b8(piVar3,iVar1);
  iVar1 = MulDiv(0xa4,local_1c.cx,4);
  FUN_004130d8(piVar3,iVar1);
  FUN_004286a8(piVar3,0xff);
  FUN_004135d4(piVar3,*local_c);
  FUN_0042886c(piVar3);
  iVar4 = MulDiv(0x29,local_1c.cy,8);
  local_20 = MulDiv(0x32,local_1c.cx,4);
  local_24 = MulDiv(0xe,local_1c.cy,8);
  ppiVar5 = (int **)FUN_0042a310((int *)&PTR_FUN_004271a4,
                                 CONCAT31((int3)((uint)extraout_EDX_01 >> 8),1),(int *)local_14);
  (*(code *)(*ppiVar5)[0xf])(ppiVar5,local_14);
  FUN_00405bf0(0xf07e,(int *)&local_28);
  FUN_004135d4((int *)ppiVar5,local_28);
  ppiVar5[0x42] = (int *)0x1;
  FUN_0042a3e8(ppiVar5,1);
  iVar1 = local_24;
  iVar7 = local_20;
  iVar6 = MulDiv(0x26,local_1c.cx,4);
  (*(code *)(*ppiVar5)[0x13])(ppiVar5,iVar6,iVar4,iVar1,iVar7);
  piVar2 = FUN_0042a310((int *)&PTR_FUN_004271a4,CONCAT31((int3)((uint)extraout_EDX_02 >> 8),1),
                        (int *)local_14);
  (**(code **)(*piVar2 + 0x3c))(piVar2,local_14);
  FUN_00405bf0(0xf07f,(int *)&local_28);
  FUN_004135d4(piVar2,local_28);
  piVar2[0x42] = 2;
  *(undefined *)((int)piVar2 + 0x105) = 1;
  iVar1 = local_24;
  iVar7 = local_20;
  iVar6 = MulDiv(0x5c,local_1c.cx,4);
  (**(code **)(*piVar2 + 0x4c))(piVar2,iVar6,iVar4,iVar1,iVar7);
  iVar7 = FUN_004237dc((int *)local_14);
  if (iVar7 == 1) {
    FUN_004135a4(piVar3,(int *)&local_2c);
    FUN_0040352c((int *)local_c,local_2c);
    local_d = 1;
  }
  *in_FS_OFFSET = iVar1;
  FUN_00402c34((int *)local_14);
  return;
}

