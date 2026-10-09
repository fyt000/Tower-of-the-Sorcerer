/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00480a90.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00480a90(int param_1)

{
  undefined4 uVar1;
  int iVar2;
  int *piVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  byte bVar6;
  dword dVar7;
  int iVar8;
  undefined4 auStack_1c [4];
  
  bVar6 = 0;
  if (DAT_0048c568 == 1) {
    (**(code **)(*DAT_0048c51c + 0x28))(DAT_0048c51c,*(int *)(*(int *)(param_1 + 0x254) + 0x30) * 2)
    ;
    (**(code **)(*DAT_0048c51c + 0x2c))
              (DAT_0048c51c,*(undefined4 *)(*(int *)(param_1 + 0x254) + 0x2c));
  }
  else if (DAT_0048c568 == 2) {
    (**(code **)(*DAT_0048c51c + 0x28))
              (DAT_0048c51c,*(undefined4 *)(*(int *)(param_1 + 0x254) + 0x30));
    (**(code **)(*DAT_0048c51c + 0x2c))(DAT_0048c51c,*(int *)(*(int *)(param_1 + 0x254) + 0x2c) * 2)
    ;
  }
  else if (DAT_0048c568 == 3) {
    (**(code **)(*DAT_0048c51c + 0x28))
              (DAT_0048c51c,*(undefined4 *)(*(int *)(param_1 + 0x254) + 0x30));
    (**(code **)(*DAT_0048c51c + 0x2c))(DAT_0048c51c,*(int *)(*(int *)(param_1 + 0x254) + 0x2c) * 2)
    ;
  }
  else if (DAT_0048c568 == 4) {
    (**(code **)(*DAT_0048c51c + 0x28))(DAT_0048c51c,*(int *)(*(int *)(param_1 + 0x254) + 0x30) * 2)
    ;
    (**(code **)(*DAT_0048c51c + 0x2c))
              (DAT_0048c51c,*(undefined4 *)(*(int *)(param_1 + 0x254) + 0x2c));
  }
  (**(code **)(*DAT_0048c520 + 0x28))
            (DAT_0048c520,*(undefined4 *)(*(int *)(param_1 + 0x254) + 0x30));
  (**(code **)(*DAT_0048c520 + 0x2c))
            (DAT_0048c520,*(undefined4 *)(*(int *)(param_1 + 0x254) + 0x2c));
  uVar1 = (**(code **)(*DAT_0048c520 + 0x1c))();
  (**(code **)(*DAT_0048c524 + 0x28))(DAT_0048c524,uVar1);
  uVar1 = (**(code **)(*DAT_0048c520 + 0x20))();
  (**(code **)(*DAT_0048c524 + 0x2c))(DAT_0048c524,uVar1);
  iVar2 = FUN_0041dad8((int)DAT_0048c51c);
  *(undefined4 *)(iVar2 + 0x20) = 0xcc0020;
  iVar2 = FUN_0041dad8((int)DAT_0048c520);
  *(undefined4 *)(iVar2 + 0x20) = 0xcc0020;
  iVar2 = FUN_0041dad8((int)DAT_0048c524);
  *(undefined4 *)(iVar2 + 0x20) = 0xcc0020;
  iVar2 = 0;
  dVar7 = scratch_index;
  piVar3 = (int *)FUN_0041dad8((int)DAT_0048c520);
  FUN_00417e44(*(int **)(param_1 + 0x1b0),piVar3,0,dVar7,iVar2);
  iVar2 = 0;
  dVar7 = scratch_index;
  piVar3 = (int *)FUN_0041dad8((int)DAT_0048c524);
  FUN_00417e44(*(int **)(param_1 + 0x40c),piVar3,0,dVar7,iVar2);
  iVar8 = 0;
  iVar2 = 5;
  piVar3 = (int *)FUN_0041dad8((int)DAT_0048c51c);
  FUN_00417e44(*(int **)(param_1 + 0x1b0),piVar3,0,iVar2,iVar8);
  if (DAT_0048c568 == 1) {
    iVar2 = *(int *)(*(int *)(param_1 + 0x254) + 0x30);
    iVar8 = 5;
    piVar3 = (int *)FUN_0041dad8((int)DAT_0048c51c);
    FUN_00417e44(*(int **)(param_1 + 0x1b0),piVar3,0,iVar8,iVar2);
  }
  else if (DAT_0048c568 == 2) {
    iVar8 = 0;
    iVar2 = 5;
    piVar3 = (int *)FUN_0041dad8((int)DAT_0048c51c);
    FUN_00417e44(*(int **)(param_1 + 0x1b0),piVar3,*(int *)(*(int *)(param_1 + 0x254) + 0x2c),iVar2,
                 iVar8);
  }
  else if (DAT_0048c568 == 3) {
    iVar8 = 0;
    iVar2 = 5;
    piVar3 = (int *)FUN_0041dad8((int)DAT_0048c51c);
    FUN_00417e44(*(int **)(param_1 + 0x1b0),piVar3,*(int *)(*(int *)(param_1 + 0x254) + 0x2c),iVar2,
                 iVar8);
  }
  else if (DAT_0048c568 == 4) {
    iVar2 = *(int *)(*(int *)(param_1 + 0x254) + 0x30);
    iVar8 = 5;
    piVar3 = (int *)FUN_0041dad8((int)DAT_0048c51c);
    FUN_00417e44(*(int **)(param_1 + 0x1b0),piVar3,0,iVar8,iVar2);
  }
  if (DAT_0048c568 == 1) {
    FUN_0040923c(0,neighbor_index,*(undefined4 *)(*(int *)(param_1 + 0x254) + 0x2c),auStack_1c,
                 *(int *)(*(int *)(param_1 + 0x254) + 0x30) + neighbor_index);
    puVar4 = auStack_1c;
    puVar5 = &DAT_0048c52c;
    for (iVar2 = 4; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar5 = *puVar4;
      puVar4 = puVar4 + (uint)bVar6 * -2 + 1;
      puVar5 = puVar5 + (uint)bVar6 * -2 + 1;
    }
  }
  else if (DAT_0048c568 == 2) {
    iVar2 = *(int *)(*(int *)(param_1 + 0x254) + 0x2c);
    FUN_0040923c(iVar2 - neighbor_index,0,iVar2 * 2 - neighbor_index,auStack_1c,
                 *(undefined4 *)(*(int *)(param_1 + 0x254) + 0x30));
    puVar4 = auStack_1c;
    puVar5 = &DAT_0048c52c;
    for (iVar2 = 4; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar5 = *puVar4;
      puVar4 = puVar4 + (uint)bVar6 * -2 + 1;
      puVar5 = puVar5 + (uint)bVar6 * -2 + 1;
    }
  }
  else if (DAT_0048c568 == 3) {
    FUN_0040923c(neighbor_index,0,*(int *)(*(int *)(param_1 + 0x254) + 0x2c) + neighbor_index,
                 auStack_1c,*(undefined4 *)(*(int *)(param_1 + 0x254) + 0x30));
    puVar4 = auStack_1c;
    puVar5 = &DAT_0048c52c;
    for (iVar2 = 4; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar5 = *puVar4;
      puVar4 = puVar4 + (uint)bVar6 * -2 + 1;
      puVar5 = puVar5 + (uint)bVar6 * -2 + 1;
    }
  }
  else if (DAT_0048c568 == 4) {
    iVar2 = *(int *)(*(int *)(param_1 + 0x254) + 0x30);
    FUN_0040923c(0,iVar2 - neighbor_index,*(undefined4 *)(*(int *)(param_1 + 0x254) + 0x2c),
                 auStack_1c,iVar2 * 2 - neighbor_index);
    puVar4 = auStack_1c;
    puVar5 = &DAT_0048c52c;
    for (iVar2 = 4; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar5 = *puVar4;
      puVar4 = puVar4 + (uint)bVar6 * -2 + 1;
      puVar5 = puVar5 + (uint)bVar6 * -2 + 1;
    }
  }
  FUN_0044439c();
  return;
}

