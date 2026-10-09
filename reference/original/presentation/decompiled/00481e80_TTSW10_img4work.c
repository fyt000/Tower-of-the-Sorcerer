/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; published entry 00481e80.
 * Inferred types and shared tails require assembly review. */

void FUN_00481e80(int param_1,undefined4 param_2,undefined4 param_3)

{
  int extraout_ECX;
  int extraout_ECX_00;
  int extraout_ECX_01;
  int extraout_ECX_02;
  int extraout_ECX_03;
  int iVar1;
  undefined4 extraout_ECX_04;
  undefined4 extraout_ECX_05;
  undefined4 extraout_ECX_06;
  undefined4 extraout_ECX_07;
  undefined4 extraout_ECX_08;
  undefined4 uVar2;
  dword dVar3;
  dword extraout_EDX;
  dword extraout_EDX_00;
  dword extraout_EDX_01;
  dword extraout_EDX_02;
  undefined4 extraout_EDX_03;
  undefined4 extraout_EDX_04;
  undefined4 extraout_EDX_05;
  undefined4 extraout_EDX_06;
  undefined4 extraout_EDX_07;
  undefined4 uVar4;
  
  original_hero._632_4_ = 0;
  original_hero._664_4_ = 0;
  DAT_0048c564 = 2;
  DAT_0048c56c = 0xffffffff;
  monster_index = 0xffffffff;
  FUN_0044b78c(param_1,param_2,param_3);
  if (original_hero.flight_orb == 1) {
    FUN_00450758(param_1);
    tile_class_or_message = 0;
    scratch_index = original_hero.y * 0xb + original_hero.x;
    dVar3 = scratch_index - 0xb;
    iVar1 = extraout_ECX;
    if (original_hero.y - 1U < 10) {
      neighbor_index = dVar3;
      FUN_0044c9f0();
      iVar1 = extraout_ECX_00;
      dVar3 = extraout_EDX;
    }
    neighbor_index = scratch_index - 1;
    if (original_hero.x - 1U < 10) {
      FUN_0044c9f0();
      iVar1 = extraout_ECX_01;
      dVar3 = extraout_EDX_00;
    }
    neighbor_index = scratch_index + 1;
    if ((uint)original_hero.x < 10) {
      FUN_0044c9f0();
      iVar1 = extraout_ECX_02;
      dVar3 = extraout_EDX_01;
    }
    neighbor_index = scratch_index + 0xb;
    if ((uint)original_hero.y < 10) {
      FUN_0044c9f0();
      iVar1 = extraout_ECX_03;
      dVar3 = extraout_EDX_02;
    }
    if (tile_class_or_message == 0x13) {
      if (original_hero._360_4_ != 0) {
        FUN_00431188(*(int **)(param_1 + 0x2d8),dVar3,iVar1);
      }
      FUN_00442c38(param_1);
      FUN_0044cb34(param_1);
      original_hero._48_4_ = 1;
      FUN_00413500(*(int **)(param_1 + 0x1e0),CONCAT31((int3)((uint)extraout_EDX_03 >> 8),1),
                   extraout_ECX_04);
      FUN_0041353c(*(int **)(param_1 + 0x1e0),'\x01');
      uVar2 = extraout_ECX_05;
      uVar4 = extraout_EDX_04;
      if (original_hero.floor == original_hero._20_4_) {
        FUN_0041353c(*(int **)(param_1 + 0x1e0),'\0');
        uVar2 = extraout_ECX_06;
        uVar4 = extraout_EDX_05;
      }
      FUN_00413500(*(int **)(param_1 + 0x1e4),CONCAT31((int3)((uint)uVar4 >> 8),1),uVar2);
      FUN_0041353c(*(int **)(param_1 + 0x1e4),'\x01');
      uVar2 = extraout_ECX_07;
      uVar4 = extraout_EDX_06;
      if (original_hero.floor < 2) {
        FUN_0041353c(*(int **)(param_1 + 0x1e4),'\0');
        uVar2 = extraout_ECX_08;
        uVar4 = extraout_EDX_07;
      }
      FUN_00413500(*(int **)(param_1 + 0x1e8),CONCAT31((int3)((uint)uVar4 >> 8),1),uVar2);
      (**(code **)(**(int **)(param_1 + 0x1e8) + 0x80))();
    }
    else {
      tile_class_or_message = 0x14;
      FUN_00450880(param_1);
      FUN_0044cb34(param_1);
    }
  }
  return;
}

