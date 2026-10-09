/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00443648.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00443648(int param_1)

{
  undefined4 uVar1;
  int *piVar2;
  int iVar3;
  undefined4 extraout_ECX;
  undefined4 extraout_ECX_00;
  undefined4 extraout_ECX_01;
  undefined4 extraout_EDX;
  undefined4 extraout_EDX_00;
  undefined4 extraout_EDX_01;
  undefined4 *puVar4;
  undefined4 *puVar5;
  byte bVar6;
  int iVar7;
  undefined4 local_20 [4];
  
  bVar6 = 0;
  FUN_0040923c(0,0,*(undefined4 *)(*(int *)(param_1 + 0x254) + 0x2c),local_20,
               *(undefined4 *)(*(int *)(param_1 + 0x254) + 0x30));
  puVar4 = local_20;
  puVar5 = &DAT_0048c53c;
  for (iVar3 = 4; iVar3 != 0; iVar3 = iVar3 + -1) {
    *puVar5 = *puVar4;
    puVar4 = puVar4 + (uint)bVar6 * -2 + 1;
    puVar5 = puVar5 + (uint)bVar6 * -2 + 1;
  }
  FUN_00402c34(DAT_0048c51c);
  FUN_00402c34(DAT_0048c520);
  FUN_00402c34(DAT_0048c524);
  DAT_0048c51c = (int *)FUN_0041d718(0x4193b4,CONCAT31((int3)((uint)extraout_EDX >> 8),1),
                                     extraout_ECX);
  DAT_0048c520 = (int *)FUN_0041d718(0x4193b4,CONCAT31((int3)((uint)extraout_EDX_00 >> 8),1),
                                     extraout_ECX_00);
  DAT_0048c524 = (int *)FUN_0041d718(0x4193b4,CONCAT31((int3)((uint)extraout_EDX_01 >> 8),1),
                                     extraout_ECX_01);
  (**(code **)(*DAT_0048c51c + 0x28))
            (DAT_0048c51c,*(undefined4 *)(*(int *)(param_1 + 0x254) + 0x30));
  (**(code **)(*DAT_0048c51c + 0x2c))
            (DAT_0048c51c,*(undefined4 *)(*(int *)(param_1 + 0x254) + 0x2c));
  uVar1 = (**(code **)(*DAT_0048c51c + 0x1c))();
  (**(code **)(*DAT_0048c520 + 0x28))(DAT_0048c520,uVar1);
  uVar1 = (**(code **)(*DAT_0048c51c + 0x20))();
  (**(code **)(*DAT_0048c520 + 0x2c))(DAT_0048c520,uVar1);
  uVar1 = (**(code **)(*DAT_0048c51c + 0x1c))();
  (**(code **)(*DAT_0048c524 + 0x28))(DAT_0048c524,uVar1);
  uVar1 = (**(code **)(*DAT_0048c51c + 0x20))();
  (**(code **)(*DAT_0048c524 + 0x2c))(DAT_0048c524,uVar1);
  iVar3 = FUN_0041dad8((int)DAT_0048c51c);
  *(undefined4 *)(iVar3 + 0x20) = 0xcc0020;
  iVar3 = FUN_0041dad8((int)DAT_0048c520);
  *(undefined4 *)(iVar3 + 0x20) = 0xcc0020;
  iVar3 = FUN_0041dad8((int)DAT_0048c524);
  *(undefined4 *)(iVar3 + 0x20) = 0xcc0020;
  iVar7 = 0;
  iVar3 = *(byte *)(original_hero.floor * 0x7b + 0x4b8936 + original_hero.y * 0xb + original_hero.x)
          - 1;
  piVar2 = (int *)FUN_0041dad8((int)DAT_0048c51c);
  FUN_00417e44(*(int **)(param_1 + 0x1b0),piVar2,0,iVar3,iVar7);
  iVar7 = 0;
  iVar3 = scratch_index - 0x42;
  piVar2 = (int *)FUN_0041dad8((int)DAT_0048c520);
  FUN_00417e44(*(int **)(param_1 + 0x1b0),piVar2,0,iVar3,iVar7);
  iVar7 = 0;
  iVar3 = scratch_index - 0x41;
  piVar2 = (int *)FUN_0041dad8((int)DAT_0048c524);
  FUN_00417e44(*(int **)(param_1 + 0x1b0),piVar2,0,iVar3,iVar7);
  puVar4 = &DAT_0048c53c;
  puVar5 = &DAT_0048c52c;
  for (iVar3 = 4; iVar3 != 0; iVar3 = iVar3 + -1) {
    *puVar5 = *puVar4;
    puVar4 = puVar4 + (uint)bVar6 * -2 + 1;
    puVar5 = puVar5 + (uint)bVar6 * -2 + 1;
  }
  FUN_0044439c();
  return;
}

