/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00482664.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00482664(int param_1)

{
  uint uVar1;
  undefined4 extraout_ECX;
  undefined4 extraout_ECX_00;
  int iVar2;
  undefined4 extraout_EDX;
  undefined4 extraout_EDX_00;
  
  if (original_hero.snow_crystal == 1) {
    FUN_00450758(param_1);
    selected_item = 0xc;
    uVar1 = *(uint *)(*(int *)(param_1 + 0x254) + 0x30);
    iVar2 = (int)uVar1 >> 1;
    if (iVar2 < 0) {
      iVar2 = iVar2 + (uint)((uVar1 & 1) != 0);
    }
    FUN_004130f8(*(int **)(param_1 + 0x2cc),iVar2);
    FUN_004130d8(*(int **)(param_1 + 0x2cc),*(int *)(*(int *)(param_1 + 0x254) + 0x2c) * 2);
    uVar1 = *(uint *)(*(int *)(param_1 + 0x254) + 0x2c);
    iVar2 = (int)uVar1 >> 1;
    if (iVar2 < 0) {
      iVar2 = iVar2 + (uint)((uVar1 & 1) != 0);
    }
    FUN_00413098(*(int **)(param_1 + 0x2cc),*(int *)(*(int *)(param_1 + 0x278) + 0x24) - iVar2);
    FUN_004130b8(*(int **)(param_1 + 0x2cc),
                 *(int *)(*(int *)(param_1 + 0x278) + 0x28) +
                 *(int *)(*(int *)(param_1 + 0x278) + 0x30));
    FUN_004130f8(*(int **)(param_1 + 0x2d0),*(undefined4 *)(*(int *)(param_1 + 0x2cc) + 0x30));
    FUN_004130d8(*(int **)(param_1 + 0x2d0),*(undefined4 *)(*(int *)(param_1 + 0x2cc) + 0x2c));
    FUN_00413098(*(int **)(param_1 + 0x2d0),*(undefined4 *)(*(int *)(param_1 + 0x2cc) + 0x24));
    FUN_004130b8(*(int **)(param_1 + 0x2d0),
                 *(int *)(*(int *)(param_1 + 0x2cc) + 0x28) +
                 *(int *)(*(int *)(param_1 + 0x2cc) + 0x30));
    FUN_00413500(*(int **)(param_1 + 0x2cc),CONCAT31((int3)((uint)extraout_EDX >> 8),1),extraout_ECX
                );
    FUN_00413500(*(int **)(param_1 + 0x2d0),CONCAT31((int3)((uint)extraout_EDX_00 >> 8),1),
                 extraout_ECX_00);
    (**(code **)(**(int **)(param_1 + 0x2cc) + 0x80))();
  }
  return;
}

