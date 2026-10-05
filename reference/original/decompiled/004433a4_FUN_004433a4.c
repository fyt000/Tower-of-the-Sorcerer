/* Original TSW v1.2, SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779.
 * Function entry 004433a4. Ghidra C-like inspection output.
 * Review assembly/probes before treating inferred types or arithmetic as verified.
 */


void FUN_004433a4(int param_1)

{
  int *piVar1;
  int *piVar2;

  if (original_hero._352_4_ == 1) {
    neighbor_index = *(int *)(*(int *)(param_1 + 0x254) + 0x2c) * original_hero.x;
    DAT_0048c560 = *(int *)(*(int *)(param_1 + 0x254) + 0x30) * original_hero.y;
    scratch_index = 0xfa;
    door_opened = 1;
    FUN_00443648(param_1);
    piVar2 = DAT_0048c51c;
    piVar1 = (int *)FUN_0041dad8(DAT_0048c518);
    FUN_0041a5b8(piVar1,neighbor_index,DAT_0048c560,piVar2);
    scratch_index = 0xfc;
    door_opened = 0;
    FUN_00443648(param_1);
    piVar2 = DAT_0048c51c;
    piVar1 = (int *)FUN_0041dad8(DAT_0048c514);
    FUN_0041a5b8(piVar1,neighbor_index,DAT_0048c560,piVar2);
    return;
  }
  if (original_hero._352_4_ == 2) {
    neighbor_index = *(int *)(*(int *)(param_1 + 0x254) + 0x2c) * original_hero.x;
    DAT_0048c560 = *(int *)(*(int *)(param_1 + 0x254) + 0x30) * original_hero.y;
    scratch_index = 0x102;
    door_opened = 1;
    FUN_00443648(param_1);
    piVar2 = DAT_0048c51c;
    piVar1 = (int *)FUN_0041dad8(DAT_0048c518);
    FUN_0041a5b8(piVar1,neighbor_index,DAT_0048c560,piVar2);
    scratch_index = 0x104;
    door_opened = 0;
    FUN_00443648(param_1);
    piVar2 = DAT_0048c51c;
    piVar1 = (int *)FUN_0041dad8(DAT_0048c514);
    FUN_0041a5b8(piVar1,neighbor_index,DAT_0048c560,piVar2);
    return;
  }
  if (original_hero._352_4_ == 3) {
    neighbor_index = *(int *)(*(int *)(param_1 + 0x254) + 0x2c) * original_hero.x;
    DAT_0048c560 = *(int *)(*(int *)(param_1 + 0x254) + 0x30) * original_hero.y;
    scratch_index = 0x10a;
    door_opened = 1;
    FUN_00443648(param_1);
    piVar2 = DAT_0048c51c;
    piVar1 = (int *)FUN_0041dad8(DAT_0048c518);
    FUN_0041a5b8(piVar1,neighbor_index,DAT_0048c560,piVar2);
    scratch_index = 0x10c;
    door_opened = 0;
    FUN_00443648(param_1);
    piVar2 = DAT_0048c51c;
    piVar1 = (int *)FUN_0041dad8(DAT_0048c514);
    FUN_0041a5b8(piVar1,neighbor_index,DAT_0048c560,piVar2);
    return;
  }
  if (original_hero._352_4_ == 4) {
    neighbor_index = *(int *)(*(int *)(param_1 + 0x254) + 0x2c) * original_hero.x;
    DAT_0048c560 = *(int *)(*(int *)(param_1 + 0x254) + 0x30) * original_hero.y;
    scratch_index = 0x112;
    door_opened = 1;
    FUN_00443648(param_1);
    piVar2 = DAT_0048c51c;
    piVar1 = (int *)FUN_0041dad8(DAT_0048c518);
    FUN_0041a5b8(piVar1,neighbor_index,DAT_0048c560,piVar2);
    scratch_index = 0x114;
    door_opened = 0;
    FUN_00443648(param_1);
    piVar2 = DAT_0048c51c;
    piVar1 = (int *)FUN_0041dad8(DAT_0048c514);
    FUN_0041a5b8(piVar1,neighbor_index,DAT_0048c560,piVar2);
  }
  return;
}
