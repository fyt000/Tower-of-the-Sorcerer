/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; published entry 0044f26c.
 * Inferred types and shared tails require assembly review. */

void FUN_0044f26c(int param_1)

{
  undefined *puVar1;
  byte *pbVar2;
  int *piVar3;
  undefined4 extraout_ECX;
  undefined4 extraout_ECX_00;
  undefined4 extraout_ECX_01;
  undefined4 extraout_ECX_02;
  undefined4 extraout_ECX_03;
  undefined4 extraout_ECX_04;
  undefined4 extraout_ECX_05;
  int iVar4;
  undefined4 extraout_EDX;
  undefined4 extraout_EDX_00;
  undefined4 extraout_EDX_01;
  undefined4 extraout_EDX_02;
  undefined4 extraout_EDX_03;
  undefined4 extraout_EDX_04;
  undefined4 extraout_EDX_05;
  undefined4 *in_FS_OFFSET;
  int iVar5;
  uint **ppuVar6;
  undefined4 uStack_24;
  undefined *puStack_20;
  undefined *puStack_1c;
  undefined4 *local_c;
  uint *local_8;
  
  puStack_1c = &stack0xfffffffc;
  local_8 = (uint *)0x0;
  local_c = (undefined4 *)0x0;
  puStack_20 = &LAB_0044fef1;
  uStack_24 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_24;
  monster_index = neighbor_index;
  DAT_0048c560 = 0;
  if (((DAT_0048c5b0 != 1) && (DAT_0048c5b0 < 8)) && (iVar4 = DAT_0048c5b0 + -1, 0 < iVar4)) {
    pbVar2 = &DAT_00489908;
    do {
      if (*pbVar2 == neighbor_index) {
        DAT_0048c560 = 1;
      }
      pbVar2 = pbVar2 + 1;
      iVar4 = iVar4 + -1;
    } while (iVar4 != 0);
  }
  if (DAT_0048c560 == 0) {
    puVar1 = &stack0xfffffffc;
    if (DAT_0048c5b0 < 8) {
      iVar4 = 0;
      if (neighbor_index < 0x12) {
        iVar4 = neighbor_index * 2 + 0x3c;
      }
      else if (neighbor_index == 0x12) {
        iVar4 = 0x67;
      }
      else if (neighbor_index == 0x13) {
        iVar4 = 0x79;
      }
      else if (neighbor_index - 0x14 < 0xd) {
        iVar4 = neighbor_index * 2 + 0x5c;
      }
      iVar5 = 0;
      piVar3 = (int *)FUN_0041dad8((int)DAT_0048c524);
      FUN_00417e44(*(int **)(param_1 + 0x1b0),piVar3,0,iVar4,iVar5);
      puVar1 = puStack_1c;
      switch(DAT_0048c5b0) {
      case 1:
        FUN_0041c160(*(int *)(*(int *)(param_1 + 0x428) + 0xac),DAT_0048c524);
        FUN_00413500(*(int **)(param_1 + 0x428),CONCAT31((int3)((uint)extraout_EDX >> 8),1),
                     extraout_ECX);
        puVar1 = puStack_1c;
        break;
      case 2:
        FUN_0041c160(*(int *)(*(int *)(param_1 + 0x42c) + 0xac),DAT_0048c524);
        FUN_00413500(*(int **)(param_1 + 0x42c),CONCAT31((int3)((uint)extraout_EDX_00 >> 8),1),
                     extraout_ECX_00);
        puVar1 = puStack_1c;
        break;
      case 3:
        FUN_0041c160(*(int *)(*(int *)(param_1 + 0x430) + 0xac),DAT_0048c524);
        FUN_00413500(*(int **)(param_1 + 0x430),CONCAT31((int3)((uint)extraout_EDX_01 >> 8),1),
                     extraout_ECX_01);
        puVar1 = puStack_1c;
        break;
      case 4:
        FUN_0041c160(*(int *)(*(int *)(param_1 + 0x434) + 0xac),DAT_0048c524);
        FUN_00413500(*(int **)(param_1 + 0x434),CONCAT31((int3)((uint)extraout_EDX_02 >> 8),1),
                     extraout_ECX_02);
        puVar1 = puStack_1c;
        break;
      case 5:
        FUN_0041c160(*(int *)(*(int *)(param_1 + 0x438) + 0xac),DAT_0048c524);
        FUN_00413500(*(int **)(param_1 + 0x438),CONCAT31((int3)((uint)extraout_EDX_03 >> 8),1),
                     extraout_ECX_03);
        puVar1 = puStack_1c;
        break;
      case 6:
        FUN_0041c160(*(int *)(*(int *)(param_1 + 0x43c) + 0xac),DAT_0048c524);
        FUN_00413500(*(int **)(param_1 + 0x43c),CONCAT31((int3)((uint)extraout_EDX_04 >> 8),1),
                     extraout_ECX_04);
        puVar1 = puStack_1c;
        break;
      case 7:
        FUN_0041c160(*(int *)(*(int *)(param_1 + 0x440) + 0xac),DAT_0048c524);
        FUN_00413500(*(int **)(param_1 + 0x440),CONCAT31((int3)((uint)extraout_EDX_05 >> 8),1),
                     extraout_ECX_05);
        puVar1 = puStack_1c;
      }
    }
    puStack_1c = puVar1;
    switch(DAT_0048c5b0) {
    case 1:
      FUN_0044b6f4(param_1);
      FUN_004135d4(*(int **)(param_1 + 0x294),DAT_004b867c);
      piVar3 = *(int **)(*(int *)(param_1 + 0x44c) + 0x100);
      (**(code **)(*piVar3 + 0xc))(piVar3,0xd6,&local_8);
      FUN_00403658((int *)&local_8,(undefined4 *)&DAT_0044ff08);
      ppuVar6 = &local_8;
      FUN_00405b6c(original_monsters[monster_index].hp * (original_hero.cycle_factor_minus_one + 1),
                   (int *)&local_c);
      FUN_00403658((int *)ppuVar6,local_c);
      FUN_00403658((int *)&local_8,(undefined4 *)&DAT_0044ff08);
      ppuVar6 = &local_8;
      piVar3 = *(int **)(*(int *)(param_1 + 0x44c) + 0x100);
      (**(code **)(*piVar3 + 0xc))(piVar3,0xd7,&local_c);
      FUN_00403658((int *)ppuVar6,local_c);
      FUN_00403658((int *)&local_8,(undefined4 *)&DAT_0044ff08);
      ppuVar6 = &local_8;
      FUN_00405b6c(original_monsters[monster_index].attack *
                   (original_hero.cycle_factor_minus_one + 1),(int *)&local_c);
      FUN_00403658((int *)ppuVar6,local_c);
      FUN_00403658((int *)&local_8,(undefined4 *)&DAT_0044ff08);
      ppuVar6 = &local_8;
      piVar3 = *(int **)(*(int *)(param_1 + 0x44c) + 0x100);
      (**(code **)(*piVar3 + 0xc))(piVar3,0xd8,&local_c);
      FUN_00403658((int *)ppuVar6,local_c);
      FUN_00403658((int *)&local_8,(undefined4 *)&DAT_0044ff08);
      ppuVar6 = &local_8;
      FUN_00405b6c(original_monsters[monster_index].defense *
                   (original_hero.cycle_factor_minus_one + 1),(int *)&local_c);
      FUN_00403658((int *)ppuVar6,local_c);
      FUN_004135d4(*(int **)(param_1 + 0x298),local_8);
      FUN_0044ff0c(param_1);
      FUN_004135d4(*(int **)(param_1 + 0x2f0),DAT_004b8678);
      break;
    case 2:
      FUN_0044b6f4(param_1);
      FUN_004135d4(*(int **)(param_1 + 0x29c),DAT_004b867c);
      piVar3 = *(int **)(*(int *)(param_1 + 0x44c) + 0x100);
      (**(code **)(*piVar3 + 0xc))(piVar3,0xd6,&local_8);
      FUN_00403658((int *)&local_8,(undefined4 *)&DAT_0044ff08);
      ppuVar6 = &local_8;
      FUN_00405b6c(original_monsters[monster_index].hp * (original_hero.cycle_factor_minus_one + 1),
                   (int *)&local_c);
      FUN_00403658((int *)ppuVar6,local_c);
      FUN_00403658((int *)&local_8,(undefined4 *)&DAT_0044ff08);
      ppuVar6 = &local_8;
      piVar3 = *(int **)(*(int *)(param_1 + 0x44c) + 0x100);
      (**(code **)(*piVar3 + 0xc))(piVar3,0xd7,&local_c);
      FUN_00403658((int *)ppuVar6,local_c);
      FUN_00403658((int *)&local_8,(undefined4 *)&DAT_0044ff08);
      ppuVar6 = &local_8;
      FUN_00405b6c(original_monsters[monster_index].attack *
                   (original_hero.cycle_factor_minus_one + 1),(int *)&local_c);
      FUN_00403658((int *)ppuVar6,local_c);
      FUN_00403658((int *)&local_8,(undefined4 *)&DAT_0044ff08);
      ppuVar6 = &local_8;
      piVar3 = *(int **)(*(int *)(param_1 + 0x44c) + 0x100);
      (**(code **)(*piVar3 + 0xc))(piVar3,0xd8,&local_c);
      FUN_00403658((int *)ppuVar6,local_c);
      FUN_00403658((int *)&local_8,(undefined4 *)&DAT_0044ff08);
      ppuVar6 = &local_8;
      FUN_00405b6c(original_monsters[monster_index].defense *
                   (original_hero.cycle_factor_minus_one + 1),(int *)&local_c);
      FUN_00403658((int *)ppuVar6,local_c);
      FUN_004135d4(*(int **)(param_1 + 0x2a0),local_8);
      FUN_0044ff0c(param_1);
      FUN_004135d4(*(int **)(param_1 + 0x2f4),DAT_004b8678);
      break;
    case 3:
      FUN_0044b6f4(param_1);
      FUN_004135d4(*(int **)(param_1 + 0x2a4),DAT_004b867c);
      piVar3 = *(int **)(*(int *)(param_1 + 0x44c) + 0x100);
      (**(code **)(*piVar3 + 0xc))(piVar3,0xd6,&local_8);
      FUN_00403658((int *)&local_8,(undefined4 *)&DAT_0044ff08);
      ppuVar6 = &local_8;
      FUN_00405b6c(original_monsters[monster_index].hp * (original_hero.cycle_factor_minus_one + 1),
                   (int *)&local_c);
      FUN_00403658((int *)ppuVar6,local_c);
      FUN_00403658((int *)&local_8,(undefined4 *)&DAT_0044ff08);
      ppuVar6 = &local_8;
      piVar3 = *(int **)(*(int *)(param_1 + 0x44c) + 0x100);
      (**(code **)(*piVar3 + 0xc))(piVar3,0xd7,&local_c);
      FUN_00403658((int *)ppuVar6,local_c);
      FUN_00403658((int *)&local_8,(undefined4 *)&DAT_0044ff08);
      ppuVar6 = &local_8;
      FUN_00405b6c(original_monsters[monster_index].attack *
                   (original_hero.cycle_factor_minus_one + 1),(int *)&local_c);
      FUN_00403658((int *)ppuVar6,local_c);
      FUN_00403658((int *)&local_8,(undefined4 *)&DAT_0044ff08);
      ppuVar6 = &local_8;
      piVar3 = *(int **)(*(int *)(param_1 + 0x44c) + 0x100);
      (**(code **)(*piVar3 + 0xc))(piVar3,0xd8,&local_c);
      FUN_00403658((int *)ppuVar6,local_c);
      FUN_00403658((int *)&local_8,(undefined4 *)&DAT_0044ff08);
      ppuVar6 = &local_8;
      FUN_00405b6c(original_monsters[monster_index].defense *
                   (original_hero.cycle_factor_minus_one + 1),(int *)&local_c);
      FUN_00403658((int *)ppuVar6,local_c);
      FUN_004135d4(*(int **)(param_1 + 0x2a8),local_8);
      FUN_0044ff0c(param_1);
      FUN_004135d4(*(int **)(param_1 + 0x2f8),DAT_004b8678);
      break;
    case 4:
      FUN_0044b6f4(param_1);
      FUN_004135d4(*(int **)(param_1 + 0x2ac),DAT_004b867c);
      piVar3 = *(int **)(*(int *)(param_1 + 0x44c) + 0x100);
      (**(code **)(*piVar3 + 0xc))(piVar3,0xd6,&local_8);
      FUN_00403658((int *)&local_8,(undefined4 *)&DAT_0044ff08);
      ppuVar6 = &local_8;
      FUN_00405b6c(original_monsters[monster_index].hp * (original_hero.cycle_factor_minus_one + 1),
                   (int *)&local_c);
      FUN_00403658((int *)ppuVar6,local_c);
      FUN_00403658((int *)&local_8,(undefined4 *)&DAT_0044ff08);
      ppuVar6 = &local_8;
      piVar3 = *(int **)(*(int *)(param_1 + 0x44c) + 0x100);
      (**(code **)(*piVar3 + 0xc))(piVar3,0xd7,&local_c);
      FUN_00403658((int *)ppuVar6,local_c);
      FUN_00403658((int *)&local_8,(undefined4 *)&DAT_0044ff08);
      ppuVar6 = &local_8;
      FUN_00405b6c(original_monsters[monster_index].attack *
                   (original_hero.cycle_factor_minus_one + 1),(int *)&local_c);
      FUN_00403658((int *)ppuVar6,local_c);
      FUN_00403658((int *)&local_8,(undefined4 *)&DAT_0044ff08);
      ppuVar6 = &local_8;
      piVar3 = *(int **)(*(int *)(param_1 + 0x44c) + 0x100);
      (**(code **)(*piVar3 + 0xc))(piVar3,0xd8,&local_c);
      FUN_00403658((int *)ppuVar6,local_c);
      FUN_00403658((int *)&local_8,(undefined4 *)&DAT_0044ff08);
      ppuVar6 = &local_8;
      FUN_00405b6c(original_monsters[monster_index].defense *
                   (original_hero.cycle_factor_minus_one + 1),(int *)&local_c);
      FUN_00403658((int *)ppuVar6,local_c);
      FUN_004135d4(*(int **)(param_1 + 0x2b0),local_8);
      FUN_0044ff0c(param_1);
      FUN_004135d4(*(int **)(param_1 + 0x2fc),DAT_004b8678);
      break;
    case 5:
      FUN_0044b6f4(param_1);
      FUN_004135d4(*(int **)(param_1 + 0x2b4),DAT_004b867c);
      piVar3 = *(int **)(*(int *)(param_1 + 0x44c) + 0x100);
      (**(code **)(*piVar3 + 0xc))(piVar3,0xd6,&local_8);
      FUN_00403658((int *)&local_8,(undefined4 *)&DAT_0044ff08);
      ppuVar6 = &local_8;
      FUN_00405b6c(original_monsters[monster_index].hp * (original_hero.cycle_factor_minus_one + 1),
                   (int *)&local_c);
      FUN_00403658((int *)ppuVar6,local_c);
      FUN_00403658((int *)&local_8,(undefined4 *)&DAT_0044ff08);
      ppuVar6 = &local_8;
      piVar3 = *(int **)(*(int *)(param_1 + 0x44c) + 0x100);
      (**(code **)(*piVar3 + 0xc))(piVar3,0xd7,&local_c);
      FUN_00403658((int *)ppuVar6,local_c);
      FUN_00403658((int *)&local_8,(undefined4 *)&DAT_0044ff08);
      ppuVar6 = &local_8;
      FUN_00405b6c(original_monsters[monster_index].attack *
                   (original_hero.cycle_factor_minus_one + 1),(int *)&local_c);
      FUN_00403658((int *)ppuVar6,local_c);
      FUN_00403658((int *)&local_8,(undefined4 *)&DAT_0044ff08);
      ppuVar6 = &local_8;
      piVar3 = *(int **)(*(int *)(param_1 + 0x44c) + 0x100);
      (**(code **)(*piVar3 + 0xc))(piVar3,0xd8,&local_c);
      FUN_00403658((int *)ppuVar6,local_c);
      FUN_00403658((int *)&local_8,(undefined4 *)&DAT_0044ff08);
      ppuVar6 = &local_8;
      FUN_00405b6c(original_monsters[monster_index].defense *
                   (original_hero.cycle_factor_minus_one + 1),(int *)&local_c);
      FUN_00403658((int *)ppuVar6,local_c);
      FUN_004135d4(*(int **)(param_1 + 0x2b8),local_8);
      FUN_0044ff0c(param_1);
      FUN_004135d4(*(int **)(param_1 + 0x300),DAT_004b8678);
      break;
    case 6:
      FUN_0044b6f4(param_1);
      FUN_004135d4(*(int **)(param_1 + 700),DAT_004b867c);
      piVar3 = *(int **)(*(int *)(param_1 + 0x44c) + 0x100);
      (**(code **)(*piVar3 + 0xc))(piVar3,0xd6,&local_8);
      FUN_00403658((int *)&local_8,(undefined4 *)&DAT_0044ff08);
      ppuVar6 = &local_8;
      FUN_00405b6c(original_monsters[monster_index].hp * (original_hero.cycle_factor_minus_one + 1),
                   (int *)&local_c);
      FUN_00403658((int *)ppuVar6,local_c);
      FUN_00403658((int *)&local_8,(undefined4 *)&DAT_0044ff08);
      ppuVar6 = &local_8;
      piVar3 = *(int **)(*(int *)(param_1 + 0x44c) + 0x100);
      (**(code **)(*piVar3 + 0xc))(piVar3,0xd7,&local_c);
      FUN_00403658((int *)ppuVar6,local_c);
      FUN_00403658((int *)&local_8,(undefined4 *)0x0);
      ppuVar6 = &local_8;
      FUN_00405b6c(original_monsters[monster_index].attack *
                   (original_hero.cycle_factor_minus_one + 1),(int *)&local_c);
      FUN_00403658((int *)ppuVar6,local_c);
      FUN_00403658((int *)&local_8,(undefined4 *)&DAT_0044ff08);
      ppuVar6 = &local_8;
      piVar3 = *(int **)(*(int *)(param_1 + 0x44c) + 0x100);
      (**(code **)(*piVar3 + 0xc))(piVar3,0xd8,&local_c);
      FUN_00403658((int *)ppuVar6,local_c);
      FUN_00403658((int *)&local_8,(undefined4 *)&DAT_0044ff08);
      ppuVar6 = &local_8;
      FUN_00405b6c(original_monsters[monster_index].defense *
                   (original_hero.cycle_factor_minus_one + 1),(int *)&local_c);
      FUN_00403658((int *)ppuVar6,local_c);
      FUN_004135d4(*(int **)(param_1 + 0x2c0),local_8);
      FUN_0044ff0c(param_1);
      FUN_004135d4(*(int **)(param_1 + 0x304),DAT_004b8678);
      break;
    case 7:
      FUN_0044b6f4(param_1);
      FUN_004135d4(*(int **)(param_1 + 0x2c4),DAT_004b867c);
      piVar3 = *(int **)(*(int *)(param_1 + 0x44c) + 0x100);
      (**(code **)(*piVar3 + 0xc))(piVar3,0xd6,&local_8);
      FUN_00403658((int *)&local_8,(undefined4 *)&DAT_0044ff08);
      ppuVar6 = &local_8;
      FUN_00405b6c(original_monsters[monster_index].hp * (original_hero.cycle_factor_minus_one + 1),
                   (int *)&local_c);
      FUN_00403658((int *)ppuVar6,local_c);
      FUN_00403658((int *)&local_8,(undefined4 *)&DAT_0044ff08);
      ppuVar6 = &local_8;
      piVar3 = *(int **)(*(int *)(param_1 + 0x44c) + 0x100);
      (**(code **)(*piVar3 + 0xc))(piVar3,0xd7,&local_c);
      FUN_00403658((int *)ppuVar6,local_c);
      FUN_00403658((int *)&local_8,(undefined4 *)&DAT_0044ff08);
      ppuVar6 = &local_8;
      FUN_00405b6c(original_monsters[monster_index].attack *
                   (original_hero.cycle_factor_minus_one + 1),(int *)&local_c);
      FUN_00403658((int *)ppuVar6,local_c);
      FUN_00403658((int *)&local_8,(undefined4 *)&DAT_0044ff08);
      ppuVar6 = &local_8;
      piVar3 = *(int **)(*(int *)(param_1 + 0x44c) + 0x100);
      (**(code **)(*piVar3 + 0xc))(piVar3,0xd8,&local_c);
      FUN_00403658((int *)ppuVar6,local_c);
      FUN_00403658((int *)&local_8,(undefined4 *)&DAT_0044ff08);
      ppuVar6 = &local_8;
      FUN_00405b6c(original_monsters[monster_index].defense *
                   (original_hero.cycle_factor_minus_one + 1),(int *)&local_c);
      FUN_00403658((int *)ppuVar6,local_c);
      FUN_004135d4(*(int **)(param_1 + 0x2c8),local_8);
      FUN_0044ff0c(param_1);
      FUN_004135d4(*(int **)(param_1 + 0x308),DAT_004b8678);
    }
    if (DAT_0048c5b0 < 8) {
      (&DAT_00489907)[DAT_0048c5b0] = (undefined)neighbor_index;
      DAT_0048c5b0 = DAT_0048c5b0 + 1;
    }
  }
  *in_FS_OFFSET = uStack_24;
  puStack_1c = &LAB_0044fef8;
  puStack_20 = (undefined *)0x44fef0;
  FUN_004034fc((int *)&local_c,2);
  return;
}

