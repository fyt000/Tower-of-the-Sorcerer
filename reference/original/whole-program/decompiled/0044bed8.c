/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0044bed8.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0044bed8(int param_1,undefined4 param_2,undefined4 param_3)

{
  uint uVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  undefined4 extraout_ECX;
  undefined4 extraout_EDX;
  dword dVar5;
  int iVar6;
  
  if (original_hero.red_keys + original_hero.blue_keys + original_hero.yellow_keys == 0) {
    FUN_00413500(*(int **)(param_1 + 0x408),0,param_3);
  }
  else {
    (**(code **)(*DAT_0048c520 + 0x28))(DAT_0048c520,*(int *)(*(int *)(param_1 + 0x254) + 0x30) * 2)
    ;
    (**(code **)(*DAT_0048c520 + 0x2c))(DAT_0048c520,*(int *)(*(int *)(param_1 + 0x254) + 0x2c) * 3)
    ;
    scratch_index = original_hero.red_keys;
    neighbor_index = original_hero.blue_keys;
    DAT_0048c560 = original_hero.yellow_keys;
    dVar5 = 0;
    do {
      DAT_0048c54c = (int)dVar5 % 6;
      DAT_0048c550 = (int)dVar5 / 6;
      if (scratch_index == 0) {
        if (neighbor_index == 0) {
          if (DAT_0048c560 == 0) {
            DAT_0048c564 = 3;
          }
          else {
            DAT_0048c564 = 2;
            DAT_0048c560 = DAT_0048c560 + -1;
          }
        }
        else {
          DAT_0048c564 = 1;
          neighbor_index = neighbor_index - 1;
        }
      }
      else {
        DAT_0048c564 = 0;
        scratch_index = scratch_index - 1;
      }
      iVar4 = *(int *)(param_1 + 0x254);
      uVar1 = *(uint *)(iVar4 + 0x30);
      iVar2 = (int)uVar1 >> 1;
      if (iVar2 < 0) {
        iVar2 = iVar2 + (uint)((uVar1 & 1) != 0);
      }
      iVar2 = iVar2 * DAT_0048c550;
      door_opened = dVar5;
      iVar6 = DAT_0048c564;
      piVar3 = (int *)FUN_0041dad8((int)DAT_0048c520);
      uVar1 = *(uint *)(iVar4 + 0x2c);
      iVar4 = (int)uVar1 >> 1;
      if (iVar4 < 0) {
        iVar4 = iVar4 + (uint)((uVar1 & 1) != 0);
      }
      FUN_00417e44(*(int **)(param_1 + 0x1c4),piVar3,iVar4 * DAT_0048c54c,iVar6,iVar2);
      dVar5 = dVar5 + 1;
    } while (dVar5 != 0x18);
    FUN_0041c160(*(int *)(*(int *)(param_1 + 0x408) + 0xac),DAT_0048c520);
    FUN_00413500(*(int **)(param_1 + 0x408),CONCAT31((int3)((uint)extraout_EDX >> 8),1),extraout_ECX
                );
  }
  return;
}

