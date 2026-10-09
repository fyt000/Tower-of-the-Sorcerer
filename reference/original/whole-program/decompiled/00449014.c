/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00449014.
 * Inferred types, shared tails and runtime effects require assembly review. */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void syounin(int param_1)

{
  uint uVar1;
  int *piVar2;
  int iVar3;
  undefined4 extraout_ECX;
  undefined4 extraout_ECX_00;
  undefined4 uVar4;
  undefined4 extraout_ECX_01;
  undefined4 extraout_ECX_02;
  undefined4 extraout_ECX_03;
  undefined4 extraout_ECX_04;
  int extraout_EDX;
  undefined4 extraout_EDX_00;
  undefined4 extraout_EDX_01;
  undefined4 extraout_EDX_02;
  undefined4 extraout_EDX_03;
  undefined4 *in_FS_OFFSET;
  undefined4 uStack_20;
  undefined *puStack_1c;
  undefined *puStack_18;
  uint *local_8;
  
  puStack_18 = &stack0xfffffffc;
  local_8 = (uint *)0x0;
  puStack_1c = &LAB_004496ed;
  uStack_20 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_20;
  FUN_004135d4(*(int **)(param_1 + 0x1d0),(uint *)&DAT_00449704);
  FUN_00450758(param_1);
  FUN_00419e4c(*(int **)(*(int *)(param_1 + 0x1cc) + 0x44),(uint)DAT_00489b9d);
  if (DAT_00489ba4 == '\0') {
    FUN_004130f8(*(int **)(param_1 + 0x1cc),200);
    FUN_004130d8(*(int **)(param_1 + 0x1cc),0x17e);
    FUN_004130b8(*(int **)(param_1 + 0x1cc),0x2d);
    FUN_00413098(*(int **)(param_1 + 0x1cc),0x81);
  }
  else if (DAT_00489ba4 == '\x01') {
    FUN_004130f8(*(int **)(param_1 + 0x1cc),0xfa);
    FUN_004130d8(*(int **)(param_1 + 0x1cc),0x1de);
    FUN_004130b8(*(int **)(param_1 + 0x1cc),0x38);
    FUN_00413098(*(int **)(param_1 + 0x1cc),0xa1);
  }
  uVar1 = *(uint *)(*(int *)(param_1 + 0x254) + 0x30);
  iVar3 = (int)uVar1 >> 1;
  if (iVar3 < 0) {
    iVar3 = iVar3 + (uint)((uVar1 & 1) != 0);
  }
  FUN_004130b8(*(int **)(param_1 + 0x1d0),
               ((*(int *)(*(int *)(param_1 + 0x1cc) + 0x28) +
                *(int *)(*(int *)(param_1 + 0x1cc) + 0x30)) - (*(int **)(param_1 + 0x1d0))[0xc]) -
               iVar3);
  uVar1 = *(uint *)(*(int *)(param_1 + 0x254) + 0x2c);
  iVar3 = (int)uVar1 >> 1;
  if (iVar3 < 0) {
    iVar3 = iVar3 + (uint)((uVar1 & 1) != 0);
  }
  FUN_00413098(*(int **)(param_1 + 0x1d0),
               ((*(int *)(*(int *)(param_1 + 0x1cc) + 0x24) +
                *(int *)(*(int *)(param_1 + 0x1cc) + 0x2c)) - (*(int **)(param_1 + 0x1d0))[0xb]) -
               iVar3);
  uVar1 = *(uint *)(*(int *)(param_1 + 0x254) + 0x30);
  iVar3 = (int)uVar1 >> 1;
  if (iVar3 < 0) {
    iVar3 = iVar3 + (uint)((uVar1 & 1) != 0);
  }
  FUN_004130b8(*(int **)(param_1 + 0x1d8),
               ((*(int *)(*(int *)(param_1 + 0x1cc) + 0x28) +
                *(int *)(*(int *)(param_1 + 0x1cc) + 0x30)) - (*(int **)(param_1 + 0x1d8))[0xc]) -
               iVar3);
  uVar1 = *(uint *)(*(int *)(param_1 + 0x254) + 0x2c);
  iVar3 = (int)uVar1 >> 1;
  if (iVar3 < 0) {
    iVar3 = iVar3 + (uint)((uVar1 & 1) != 0);
  }
  FUN_00413098(*(int **)(param_1 + 0x1d8),
               ((*(int *)(*(int *)(param_1 + 0x1cc) + 0x24) +
                *(int *)(*(int *)(param_1 + 0x1cc) + 0x2c)) - (*(int **)(param_1 + 0x1d8))[0xb]) -
               iVar3);
  uVar1 = *(uint *)(*(int *)(param_1 + 0x254) + 0x30);
  iVar3 = (int)uVar1 >> 1;
  if (iVar3 < 0) {
    iVar3 = iVar3 + (uint)((uVar1 & 1) != 0);
  }
  FUN_004130b8(*(int **)(param_1 + 0x1d4),
               ((*(int *)(*(int *)(param_1 + 0x1cc) + 0x28) +
                *(int *)(*(int *)(param_1 + 0x1cc) + 0x30)) - (*(int **)(param_1 + 0x1d4))[0xc]) -
               iVar3);
  uVar1 = *(uint *)(*(int *)(param_1 + 0x254) + 0x2c);
  iVar3 = (int)uVar1 >> 1;
  if (iVar3 < 0) {
    iVar3 = iVar3 + (uint)((uVar1 & 1) != 0);
  }
  FUN_00413098(*(int **)(param_1 + 0x1d4),
               (*(int *)(*(int *)(param_1 + 0x1d8) + 0x24) - (*(int **)(param_1 + 0x1d4))[0xb]) -
               iVar3);
  _DAT_0048c5cc = 0;
  dialogue_continue_stage = 0;
  switch(original_hero.floor) {
  case 2:
    DAT_0048c5a0 = 0x1d;
    scratch_index = 0;
    DAT_0048c598 = 0x2a;
    DAT_0048c59c = 0x36;
    bomb_gold = 0;
    DAT_0048c56c = 0x5c;
    break;
  case 6:
    DAT_0048c5a0 = 2;
    scratch_index = 1;
    DAT_0048c598 = 0x2b;
    DAT_0048c59c = 0x37;
    bomb_gold = 0x32;
    DAT_0048c56c = 0x41;
    break;
  case 7:
    DAT_0048c5a0 = 3;
    scratch_index = 2;
    DAT_0048c598 = 0x2c;
    DAT_0048c59c = 0x38;
    bomb_gold = 0x32;
    DAT_0048c56c = 0x42;
    break;
  case 0xc:
    if (original_hero.x == 1) {
      DAT_0048c5a0 = 4;
      scratch_index = 3;
      DAT_0048c598 = 0x2d;
      DAT_0048c59c = 0x39;
      bomb_gold = 800;
      DAT_0048c56c = 0x43;
    }
    else if (original_hero.x == 9) {
      scratch_index = 4;
      DAT_0048c598 = 0x2e;
      bomb_gold = 1000;
    }
    break;
  case 0xf:
    DAT_0048c5a0 = 5;
    scratch_index = 5;
    DAT_0048c598 = 0x2f;
    DAT_0048c59c = 0x3b;
    bomb_gold = 200;
    DAT_0048c56c = 0x44;
    break;
  case 0x1c:
    scratch_index = 6;
    DAT_0048c598 = 0x30;
    bomb_gold = 0;
    break;
  case 0x1f:
    DAT_0048c5a0 = 0xb;
    scratch_index = 7;
    DAT_0048c598 = 0x31;
    DAT_0048c59c = 0x3d;
    bomb_gold = 1000;
    DAT_0048c56c = 0x4a;
    break;
  case 0x26:
    DAT_0048c5a0 = 0xf;
    scratch_index = 8;
    DAT_0048c598 = 0x32;
    DAT_0048c59c = 0x3e;
    bomb_gold = 200;
    DAT_0048c56c = 0x4e;
    break;
  case 0x27:
    DAT_0048c5a0 = 0x11;
    scratch_index = 9;
    DAT_0048c598 = 0x33;
    DAT_0048c59c = 0x3f;
    bomb_gold = 2000;
    DAT_0048c56c = 0x50;
    break;
  case 0x2d:
    DAT_0048c5a0 = 0x14;
    scratch_index = 10;
    DAT_0048c598 = 0x34;
    DAT_0048c59c = 0x40;
    bomb_gold = 1000;
    DAT_0048c56c = 0x53;
    break;
  case 0x2f:
    DAT_0048c5a0 = 0x16;
    scratch_index = 0xb;
    DAT_0048c598 = 0x35;
    DAT_0048c59c = 0x41;
    bomb_gold = 4000;
    DAT_0048c56c = 0x55;
  }
  DAT_0048c560 = 0;
  iVar3 = (&original_hero.hp)[DAT_0048c598] + -1;
  if ((&original_hero.hp)[DAT_0048c598] == 0) {
    uVar4 = extraout_ECX;
    if (scratch_index < 0xc) {
      piVar2 = *(int **)(*(int *)(param_1 + 0x44c) + 0x100);
      (**(code **)(*piVar2 + 0xc))(piVar2,scratch_index + 0xf6,&local_8);
      FUN_004135d4(*(int **)(param_1 + 0x1cc),local_8);
      uVar4 = extraout_ECX_00;
      iVar3 = extraout_EDX;
    }
    FUN_00413500(*(int **)(param_1 + 0x1cc),CONCAT31((int3)((uint)iVar3 >> 8),1),uVar4);
    FUN_00413500(*(int **)(param_1 + 0x1d4),CONCAT31((int3)((uint)extraout_EDX_00 >> 8),1),
                 extraout_ECX_01);
    FUN_00413500(*(int **)(param_1 + 0x1d8),CONCAT31((int3)((uint)extraout_EDX_01 >> 8),1),
                 extraout_ECX_02);
    if (original_hero.floor == 2) {
      FUN_0041353c(*(int **)(param_1 + 0x1d8),'\0');
    }
    (**(code **)(**(int **)(param_1 + 0x1d4) + 0x80))();
  }
  else if (iVar3 == 0) {
    if ((&original_hero.hp)[DAT_0048c59c] == 0) {
      piVar2 = *(int **)(*(int *)(param_1 + 0x44c) + 0x100);
      (**(code **)(*piVar2 + 0xc))(piVar2,DAT_0048c56c + -1,&local_8);
      FUN_004135d4(*(int **)(param_1 + 0x1cc),local_8);
      if (original_hero.wisdom_orb == 0) {
        (&original_hero.hp)[DAT_0048c59c] = 1;
      }
      else if (original_hero.wisdom_orb == 1) {
        (&original_hero.hp)[DAT_0048c59c] = 2;
      }
      FUN_00413500(*(int **)(param_1 + 0x1cc),CONCAT31((int3)((uint)extraout_EDX_02 >> 8),1),
                   extraout_ECX_03);
      FUN_00413500(*(int **)(param_1 + 0x1d0),CONCAT31((int3)((uint)extraout_EDX_03 >> 8),1),
                   extraout_ECX_04);
      (**(code **)(**(int **)(param_1 + 0x1d0) + 0x80))();
    }
    else if ((&original_hero.hp)[DAT_0048c59c] - 1U < 2) {
      if (original_hero.floor == 2) {
        DAT_0048c5a0 = 0x1d;
        FUN_00449e18(param_1);
      }
      else {
        DAT_0048c5a0 = 0x1c;
        FUN_00449e18(param_1);
      }
    }
  }
  *in_FS_OFFSET = uStack_20;
  puStack_18 = &LAB_004496f4;
  puStack_1c = (undefined *)0x4496ec;
  FUN_004034dc((int *)&local_8);
  return;
}

