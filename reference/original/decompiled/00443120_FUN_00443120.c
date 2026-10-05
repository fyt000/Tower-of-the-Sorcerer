/* Original TSW v1.2, SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779.
 * Function entry 00443120. Ghidra C-like inspection output.
 * Review assembly/probes before treating inferred types or arithmetic as verified.
 */


void FUN_00443120(int param_1)

{
  int *piVar1;
  undefined4 extraout_ECX;
  undefined4 extraout_ECX_00;
  undefined4 extraout_ECX_01;
  undefined4 extraout_ECX_02;
  undefined4 uVar2;
  undefined4 extraout_EDX;
  undefined4 extraout_EDX_00;
  undefined4 extraout_EDX_01;
  undefined4 extraout_EDX_02;
  undefined4 uVar3;
  int *piVar4;

  if (DAT_0048c5d2 == 1) {
    piVar4 = DAT_0048c518;
    piVar1 = (int *)FUN_00421a54(DAT_0048c510);
    FUN_0041a5b8(piVar1,DAT_0048c578,DAT_0048c57c,piVar4);
    uVar2 = extraout_ECX;
    uVar3 = extraout_EDX;
    if (original_hero._48_4_ == 0) {
      if (((original_hero.floor == 0xf) && (original_hero.y * 0xb + original_hero.x == 0x3c)) &&
         ((original_maps[15][62] == 6 && ((int)original_hero._608_4_ < 2)))) {
        FUN_00454a58(param_1);
        original_hero._608_4_ = original_hero._608_4_ + 1;
      }
      if ((((original_hero.floor == 0x23) && (original_hero.y * 0xb + original_hero.x == 0x47)) &&
          (original_maps[35][73] == 6)) && ((int)original_hero._612_4_ < 2)) {
        FUN_00454a58(param_1);
        original_hero._612_4_ = original_hero._612_4_ + 1;
      }
      if (original_hero._352_4_ == 1) {
        scratch_index = 0xfe;
      }
      else if (original_hero._352_4_ == 2) {
        scratch_index = 0x106;
      }
      else if (original_hero._352_4_ == 3) {
        scratch_index = 0x10e;
      }
      else if (original_hero._352_4_ == 4) {
        scratch_index = 0x116;
      }
      door_opened = 1;
      FUN_00443648(param_1);
      piVar4 = DAT_0048c51c;
      piVar1 = (int *)FUN_0041dad8((int)DAT_0048c518);
      FUN_0041a5b8(piVar1,*(int *)(*(int *)(param_1 + 0x254) + 0x2c) * original_hero.x,
                   *(int *)(*(int *)(param_1 + 0x254) + 0x30) * original_hero.y,piVar4);
      uVar2 = extraout_ECX_00;
      uVar3 = extraout_EDX_00;
    }
  }
  else {
    piVar4 = DAT_0048c514;
    piVar1 = (int *)FUN_00421a54(DAT_0048c510);
    FUN_0041a5b8(piVar1,DAT_0048c578,DAT_0048c57c,piVar4);
    uVar2 = extraout_ECX_01;
    uVar3 = extraout_EDX_01;
    if (original_hero._48_4_ == 0) {
      if ((((original_hero.floor == 0xf) && (original_hero.y * 0xb + original_hero.x == 0x3c)) &&
          (original_maps[15][62] == 6)) && ((int)original_hero._608_4_ < 2)) {
        FUN_004548a0(param_1);
        original_hero._608_4_ = original_hero._608_4_ + 1;
      }
      if (((original_hero.floor == 0x23) && (original_hero.y * 0xb + original_hero.x == 0x47)) &&
         ((original_maps[35][73] == 6 && ((int)original_hero._612_4_ < 2)))) {
        FUN_004548a0(param_1);
        original_hero._612_4_ = original_hero._612_4_ + 1;
      }
      if (original_hero._352_4_ == 1) {
        scratch_index = 0xfe;
      }
      else if (original_hero._352_4_ == 2) {
        scratch_index = 0x106;
      }
      else if (original_hero._352_4_ == 3) {
        scratch_index = 0x10e;
      }
      else if (original_hero._352_4_ == 4) {
        scratch_index = 0x116;
      }
      door_opened = 0;
      FUN_00443648(param_1);
      piVar4 = DAT_0048c51c;
      piVar1 = (int *)FUN_0041dad8((int)DAT_0048c514);
      FUN_0041a5b8(piVar1,*(int *)(*(int *)(param_1 + 0x254) + 0x2c) * original_hero.x,
                   *(int *)(*(int *)(param_1 + 0x254) + 0x30) * original_hero.y,piVar4);
      uVar2 = extraout_ECX_02;
      uVar3 = extraout_EDX_02;
    }
  }
  DAT_0048c5d2 = DAT_0048c5d2 ^ 1;
  if (DAT_0048c5c4 == 0) {
    FUN_0044bed8(param_1,uVar3,uVar2);
    DAT_0048c5c4 = 1;
  }
  return;
}
