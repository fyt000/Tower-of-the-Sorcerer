/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; published entry 004440e8.
 * Inferred types and shared tails require assembly review. */

void FUN_004440e8(int param_1)

{
  undefined4 uVar1;
  int iVar2;
  int *piVar3;
  int *piVar4;
  undefined4 *puVar5;
  undefined4 *puVar6;
  byte bVar7;
  dword dVar8;
  int iVar9;
  int *piVar10;
  undefined4 auStack_20 [4];
  
  bVar7 = 0;
  (**(code **)(*DAT_0048c51c + 0x28))(DAT_0048c51c,*(int *)(*(int *)(param_1 + 0x254) + 0x30) * 2);
  (**(code **)(*DAT_0048c51c + 0x2c))
            (DAT_0048c51c,*(undefined4 *)(*(int *)(param_1 + 0x254) + 0x2c));
  (**(code **)(*DAT_0048c520 + 0x28))
            (DAT_0048c520,*(undefined4 *)(*(int *)(param_1 + 0x254) + 0x30));
  uVar1 = (**(code **)(*DAT_0048c51c + 0x20))();
  (**(code **)(*DAT_0048c520 + 0x2c))(DAT_0048c520,uVar1);
  uVar1 = (**(code **)(*DAT_0048c520 + 0x1c))();
  (**(code **)(*DAT_0048c524 + 0x28))(DAT_0048c524,uVar1);
  uVar1 = (**(code **)(*DAT_0048c51c + 0x20))();
  (**(code **)(*DAT_0048c524 + 0x2c))(DAT_0048c524,uVar1);
  iVar2 = FUN_0041dad8((int)DAT_0048c51c);
  *(undefined4 *)(iVar2 + 0x20) = 0xcc0020;
  iVar2 = FUN_0041dad8((int)DAT_0048c520);
  *(undefined4 *)(iVar2 + 0x20) = 0xcc0020;
  iVar2 = FUN_0041dad8((int)DAT_0048c524);
  *(undefined4 *)(iVar2 + 0x20) = 0xcc0020;
  iVar2 = 0;
  dVar8 = scratch_index;
  piVar3 = (int *)FUN_0041dad8((int)DAT_0048c520);
  FUN_00417e44(*(int **)(param_1 + 0x1b0),piVar3,0,dVar8,iVar2);
  iVar9 = 0;
  iVar2 = scratch_index + 1;
  piVar3 = (int *)FUN_0041dad8((int)DAT_0048c524);
  FUN_00417e44(*(int **)(param_1 + 0x1b0),piVar3,0,iVar2,iVar9);
  iVar2 = *(int *)(*(int *)(param_1 + 0x254) + 0x30);
  iVar9 = *(byte *)(original_hero.floor * 0x7b + 0x4b8936 + original_hero.y * 0xb + original_hero.x)
          - 1;
  piVar3 = (int *)FUN_0041dad8((int)DAT_0048c51c);
  FUN_00417e44(*(int **)(param_1 + 0x1b0),piVar3,0,iVar9,iVar2);
  iVar9 = 0;
  iVar2 = *(byte *)(original_hero.floor * 0x7b + original_hero.y * 0xb + original_hero.x + 0x4b892b)
          - 1;
  piVar3 = (int *)FUN_0041dad8((int)DAT_0048c51c);
  FUN_00417e44(*(int **)(param_1 + 0x1b0),piVar3,0,iVar2,iVar9);
  iVar2 = FUN_0041dad8((int)DAT_0048c524);
  *(undefined4 *)(iVar2 + 0x20) = 0x330008;
  FUN_0040923c(0,0,*(undefined4 *)(*(int *)(param_1 + 0x254) + 0x2c),auStack_20,
               *(undefined4 *)(*(int *)(param_1 + 0x254) + 0x30));
  puVar5 = auStack_20;
  puVar6 = &DAT_0048c53c;
  for (iVar2 = 4; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar6 = *puVar5;
    puVar5 = puVar5 + (uint)bVar7 * -2 + 1;
    puVar6 = puVar6 + (uint)bVar7 * -2 + 1;
  }
  piVar10 = &DAT_0048c53c;
  piVar3 = (int *)FUN_0041dad8((int)DAT_0048c524);
  piVar4 = (int *)FUN_0041dad8((int)DAT_0048c524);
  FUN_0041a530(piVar4,&DAT_0048c53c,piVar3,piVar10);
  iVar2 = FUN_0041dad8((int)DAT_0048c51c);
  *(undefined4 *)(iVar2 + 0x20) = 0xee0086;
  FUN_0040923c(0,0,*(undefined4 *)(*(int *)(param_1 + 0x254) + 0x2c),auStack_20,
               *(undefined4 *)(*(int *)(param_1 + 0x254) + 0x30));
  puVar5 = auStack_20;
  puVar6 = &DAT_0048c53c;
  for (iVar2 = 4; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar6 = *puVar5;
    puVar5 = puVar5 + (uint)bVar7 * -2 + 1;
    puVar6 = puVar6 + (uint)bVar7 * -2 + 1;
  }
  iVar2 = *(int *)(*(int *)(param_1 + 0x254) + 0x30);
  FUN_0040923c(0,iVar2 - neighbor_index,*(undefined4 *)(*(int *)(param_1 + 0x254) + 0x2c),auStack_20
               ,iVar2 * 2 - neighbor_index);
  puVar5 = auStack_20;
  puVar6 = &DAT_0048c52c;
  for (iVar2 = 4; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar6 = *puVar5;
    puVar5 = puVar5 + (uint)bVar7 * -2 + 1;
    puVar6 = puVar6 + (uint)bVar7 * -2 + 1;
  }
  piVar10 = &DAT_0048c53c;
  piVar3 = (int *)FUN_0041dad8((int)DAT_0048c524);
  piVar4 = (int *)FUN_0041dad8((int)DAT_0048c51c);
  FUN_0041a530(piVar4,&DAT_0048c52c,piVar3,piVar10);
  iVar2 = FUN_0041dad8((int)DAT_0048c51c);
  *(undefined4 *)(iVar2 + 0x20) = 0x8800c6;
  piVar10 = &DAT_0048c53c;
  piVar3 = (int *)FUN_0041dad8((int)DAT_0048c520);
  piVar4 = (int *)FUN_0041dad8((int)DAT_0048c51c);
  FUN_0041a530(piVar4,&DAT_0048c52c,piVar3,piVar10);
  iVar2 = FUN_0041dad8((int)DAT_0048c520);
  *(undefined4 *)(iVar2 + 0x20) = 0xcc0020;
  return;
}

