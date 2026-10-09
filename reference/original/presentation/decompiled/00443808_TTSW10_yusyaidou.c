/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; published entry 00443808.
 * Inferred types and shared tails require assembly review. */

void FUN_00443808(int param_1)

{
  int iVar1;
  int *piVar2;
  int *piVar3;
  
  iVar1 = *(int *)(*(int *)(param_1 + 0x254) + 0x2c);
  if (iVar1 < 0) {
    iVar1 = iVar1 + 3;
  }
  if ((int)neighbor_index % (iVar1 >> 2) == 0) {
    if (original_hero._352_4_ == 1) {
      scratch_index = 0xb8;
      door_opened = 0;
      FUN_00443de8(param_1);
    }
    else if (original_hero._352_4_ == 2) {
      scratch_index = 0xc0;
      door_opened = 0;
      FUN_00443c08(param_1);
    }
    else if (original_hero._352_4_ == 3) {
      scratch_index = 200;
      door_opened = 0;
      FUN_00443a34(param_1);
    }
    else if (original_hero._352_4_ == 4) {
      scratch_index = 0xd0;
      door_opened = 0;
      FUN_004440e8(param_1);
    }
    piVar3 = DAT_0048c51c;
    piVar2 = (int *)FUN_0041dad8(DAT_0048c514);
    FUN_0041a5b8(piVar2,DAT_0048c54c,DAT_0048c550,piVar3);
  }
  else {
    if (original_hero._352_4_ == 1) {
      scratch_index = 0xba;
      door_opened = 1;
      FUN_00443de8(param_1);
    }
    else if (original_hero._352_4_ == 2) {
      scratch_index = 0xc2;
      door_opened = 1;
      FUN_00443c08(param_1);
    }
    else if (original_hero._352_4_ == 3) {
      scratch_index = 0xca;
      door_opened = 1;
      FUN_00443a34(param_1);
    }
    else if (original_hero._352_4_ == 4) {
      scratch_index = 0xd2;
      door_opened = 1;
      FUN_004440e8(param_1);
    }
    piVar3 = DAT_0048c51c;
    piVar2 = (int *)FUN_0041dad8(DAT_0048c518);
    FUN_0041a5b8(piVar2,DAT_0048c54c,DAT_0048c550,piVar3);
  }
  if (*(dword *)(*(int *)(param_1 + 0x254) + 0x2c) == neighbor_index) {
    if (original_hero._352_4_ == 1) {
      scratch_index = 0xba;
      door_opened = 1;
      FUN_00443de8(param_1);
    }
    else if (original_hero._352_4_ == 2) {
      scratch_index = 0xc2;
      door_opened = 1;
      FUN_00443c08(param_1);
    }
    else if (original_hero._352_4_ == 3) {
      scratch_index = 0xca;
      door_opened = 1;
      FUN_00443a34(param_1);
    }
    else if (original_hero._352_4_ == 4) {
      scratch_index = 0xd2;
      door_opened = 1;
      FUN_004440e8(param_1);
    }
    piVar3 = DAT_0048c51c;
    piVar2 = (int *)FUN_0041dad8(DAT_0048c518);
    FUN_0041a5b8(piVar2,DAT_0048c54c,DAT_0048c550,piVar3);
  }
  return;
}

