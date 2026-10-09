/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0044b78c.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0044b78c(int param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 uVar1;
  int *piVar2;
  int *piVar3;
  undefined4 extraout_ECX;
  undefined4 extraout_ECX_00;
  undefined4 extraout_ECX_01;
  undefined4 extraout_ECX_02;
  undefined4 extraout_EDX;
  undefined4 extraout_EDX_00;
  undefined4 extraout_EDX_01;
  undefined4 extraout_EDX_02;
  undefined4 uVar4;
  int iVar5;
  undefined4 *puVar6;
  undefined4 *puVar7;
  undefined4 *in_FS_OFFSET;
  byte bVar8;
  int iVar9;
  int iVar10;
  undefined4 uStack_30;
  undefined *puStack_2c;
  undefined *puStack_28;
  uint *local_18;
  undefined4 local_14 [4];
  
  bVar8 = 0;
  puStack_28 = &stack0xfffffffc;
  local_18 = (uint *)0x0;
  puStack_2c = &LAB_0044bbfd;
  uStack_30 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_30;
  FUN_00413500(*(int **)(param_1 + 0x404),0,param_3);
  DAT_0048c54c = 0;
  DAT_0048c550 = 0;
  if ((int)monster_index < 0) {
    FUN_004291c8(*(int ***)(param_1 + 0x3d8),'\0');
    FUN_004291c8(*(int ***)(param_1 + 0x3dc),'\0');
    FUN_004291c8(*(int ***)(param_1 + 0x3e0),'\0');
    FUN_0044b6f4(param_1);
    (**(code **)(*DAT_0048c524 + 0x2c))
              (DAT_0048c524,*(undefined4 *)(*(int *)(param_1 + 0x254) + 0x2c));
    (**(code **)(*DAT_0048c524 + 0x28))
              (DAT_0048c524,*(undefined4 *)(*(int *)(param_1 + 0x254) + 0x30));
    iVar9 = 0;
    iVar5 = 0xa2;
    piVar2 = (int *)FUN_0041dad8((int)DAT_0048c524);
    FUN_00417e44(*(int **)(param_1 + 0x1b0),piVar2,0,iVar5,iVar9);
    if (DAT_00489ba4 == '\0') {
      FUN_004130b8(*(int **)(param_1 + 0x404),0xe6);
      FUN_00413098(*(int **)(param_1 + 0x404),*(int *)(*(int *)(param_1 + 0x1c0) + 0x24) + 0x2e);
      uVar1 = extraout_ECX_01;
      uVar4 = extraout_EDX_01;
    }
    else {
      uVar1 = extraout_ECX_00;
      uVar4 = extraout_EDX_00;
      if (DAT_00489ba4 == '\x01') {
        FUN_004130b8(*(int **)(param_1 + 0x404),0x120);
        FUN_00413098(*(int **)(param_1 + 0x404),*(int *)(*(int *)(param_1 + 0x1c0) + 0x24) + 0x3a);
        uVar1 = extraout_ECX_02;
        uVar4 = extraout_EDX_02;
      }
    }
    piVar2 = DAT_0048c524;
    piVar3 = (int *)FUN_0042c150(*(int *)(param_1 + 0x404),uVar4,uVar1);
    FUN_0041a5b8(piVar3,0,0,piVar2);
    FUN_004135d4(*(int **)(param_1 + 0x3e4),DAT_004b867c);
    piVar2 = *(int **)(*(int *)(param_1 + 0x44c) + 0x100);
    (**(code **)(*piVar2 + 0xc))(piVar2,0xd6,&local_18);
    FUN_004135d4(*(int **)(param_1 + 0x3d8),local_18);
    piVar2 = *(int **)(*(int *)(param_1 + 0x44c) + 0x100);
    (**(code **)(*piVar2 + 0xc))(piVar2,0xd7,&local_18);
    FUN_004135d4(*(int **)(param_1 + 0x3dc),local_18);
    piVar2 = *(int **)(*(int *)(param_1 + 0x44c) + 0x100);
    (**(code **)(*piVar2 + 0xc))(piVar2,0xd8,&local_18);
    FUN_004135d4(*(int **)(param_1 + 0x3e0),local_18);
  }
  else {
    (**(code **)(*DAT_0048c51c + 0x2c))
              (DAT_0048c51c,*(undefined4 *)(*(int *)(param_1 + 0x254) + 0x2c));
    (**(code **)(*DAT_0048c51c + 0x28))
              (DAT_0048c51c,*(undefined4 *)(*(int *)(param_1 + 0x254) + 0x30));
    uVar1 = (**(code **)(*DAT_0048c51c + 0x20))();
    (**(code **)(*DAT_0048c520 + 0x2c))(DAT_0048c520,uVar1);
    uVar1 = (**(code **)(*DAT_0048c51c + 0x1c))();
    (**(code **)(*DAT_0048c520 + 0x28))(DAT_0048c520,uVar1);
    uVar1 = (**(code **)(*DAT_0048c51c + 0x20))();
    (**(code **)(*DAT_0048c524 + 0x2c))(DAT_0048c524,uVar1);
    uVar1 = (**(code **)(*DAT_0048c51c + 0x1c))();
    (**(code **)(*DAT_0048c524 + 0x28))(DAT_0048c524,uVar1);
    FUN_004291c8(*(int ***)(param_1 + 0x3d8),'\x01');
    FUN_004291c8(*(int ***)(param_1 + 0x3dc),'\x01');
    FUN_004291c8(*(int ***)(param_1 + 0x3e0),'\x01');
    FUN_0044b6f4(param_1);
    iVar5 = 0;
    if (monster_index < 0x12) {
      iVar5 = monster_index * 2 + 0x3c;
    }
    else if (monster_index == 0x12) {
      iVar5 = 0x67;
    }
    else if (monster_index == 0x13) {
      iVar5 = 0x79;
    }
    else if (monster_index - 0x14 < 0xd) {
      iVar5 = monster_index * 2 + 0x5c;
    }
    iVar10 = 0;
    iVar9 = 0xa2;
    piVar2 = (int *)FUN_0041dad8((int)DAT_0048c51c);
    FUN_00417e44(*(int **)(param_1 + 0x1b0),piVar2,0,iVar9,iVar10);
    iVar10 = 0;
    iVar9 = iVar5;
    piVar2 = (int *)FUN_0041dad8((int)DAT_0048c520);
    FUN_00417e44(*(int **)(param_1 + 0x1b0),piVar2,0,iVar9,iVar10);
    iVar9 = 0;
    piVar2 = (int *)FUN_0041dad8((int)DAT_0048c524);
    FUN_00417e44(*(int **)(param_1 + 0x40c),piVar2,0,iVar5,iVar9);
    FUN_0040923c(0,0,*(undefined4 *)(*(int *)(param_1 + 0x254) + 0x2c),local_14,
                 *(undefined4 *)(*(int *)(param_1 + 0x254) + 0x30));
    puVar6 = local_14;
    puVar7 = &DAT_0048c53c;
    for (iVar5 = 4; iVar5 != 0; iVar5 = iVar5 + -1) {
      *puVar7 = *puVar6;
      puVar6 = puVar6 + (uint)bVar8 * -2 + 1;
      puVar7 = puVar7 + (uint)bVar8 * -2 + 1;
    }
    puVar6 = &DAT_0048c53c;
    puVar7 = &DAT_0048c52c;
    for (iVar5 = 4; iVar5 != 0; iVar5 = iVar5 + -1) {
      *puVar7 = *puVar6;
      puVar6 = puVar6 + (uint)bVar8 * -2 + 1;
      puVar7 = puVar7 + (uint)bVar8 * -2 + 1;
    }
    FUN_0044439c();
    if (DAT_00489ba4 == '\0') {
      FUN_004130b8(*(int **)(param_1 + 0x404),0xe6);
      FUN_00413098(*(int **)(param_1 + 0x404),*(int *)(*(int *)(param_1 + 0x1c0) + 0x24) + 0x2e);
    }
    else if (DAT_00489ba4 == '\x01') {
      FUN_004130b8(*(int **)(param_1 + 0x404),0x120);
      FUN_00413098(*(int **)(param_1 + 0x404),*(int *)(*(int *)(param_1 + 0x1c0) + 0x24) + 0x3a);
    }
    FUN_0041c160(*(int *)(*(int *)(param_1 + 0x404) + 0xac),DAT_0048c51c);
    FUN_004135d4(*(int **)(param_1 + 0x3e4),DAT_004b867c);
    FUN_00405b6c(original_monsters[monster_index].hp * (original_hero.cycle_factor_minus_one + 1),
                 (int *)&local_18);
    FUN_004135d4(*(int **)(param_1 + 0x3d8),local_18);
    FUN_00405b6c(original_monsters[monster_index].attack *
                 (original_hero.cycle_factor_minus_one + 1),(int *)&local_18);
    FUN_004135d4(*(int **)(param_1 + 0x3dc),local_18);
    FUN_00405b6c(original_monsters[monster_index].defense *
                 (original_hero.cycle_factor_minus_one + 1),(int *)&local_18);
    FUN_004135d4(*(int **)(param_1 + 0x3e0),local_18);
    FUN_00413500(*(int **)(param_1 + 0x404),CONCAT31((int3)((uint)extraout_EDX >> 8),1),extraout_ECX
                );
  }
  *in_FS_OFFSET = uStack_30;
  puStack_28 = &LAB_0044bc04;
  puStack_2c = (undefined *)0x44bbfc;
  FUN_004034dc((int *)&local_18);
  return;
}

