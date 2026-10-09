/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00442c38.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00442c38(int param_1)

{
  int iVar1;
  int *piVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  
  original_hero._664_4_ = 0;
  iVar4 = 1;
  do {
    uVar3 = (uint)*(byte *)((int)&original_monsters[0x20].gold + iVar4 + 3);
    iVar5 = *(int *)(*(int *)(param_1 + 0x254) + 0x2c);
    DAT_0048c54c = (int)(uVar3 * iVar5) % (iVar5 * 0xb);
    iVar5 = *(int *)(*(int *)(param_1 + 0x254) + 0x30);
    DAT_0048c550 = ((int)(uVar3 * iVar5) / (iVar5 * 0xb)) * iVar5;
    iVar1 = *(byte *)(original_hero.floor * 0x7b + 0x4b8936 +
                     (uint)*(byte *)((int)&original_monsters[0x20].gold + iVar4 + 3)) - 1;
    DAT_0048c570 = iVar4;
    iVar5 = DAT_0048c550;
    piVar2 = (int *)FUN_0041dad8(DAT_0048c514);
    FUN_00417e44(*(int **)(param_1 + 0x1b0),piVar2,DAT_0048c54c,iVar1,iVar5);
    DAT_0048c5a8 = (uint)*(byte *)(original_hero.floor * 0x7b + 0x4b8936 +
                                  (uint)*(byte *)((int)&original_monsters[0x20].gold +
                                                 DAT_0048c570 + 3));
    FUN_00454c10();
    iVar1 = (*(byte *)(original_hero.floor * 0x7b + 0x4b8936 +
                      (uint)*(byte *)((int)&original_monsters[0x20].gold + DAT_0048c570 + 3)) - 1) +
            door_opened;
    iVar5 = DAT_0048c550;
    piVar2 = (int *)FUN_0041dad8(DAT_0048c518);
    FUN_00417e44(*(int **)(param_1 + 0x1b0),piVar2,DAT_0048c54c,iVar1,iVar5);
    iVar4 = iVar4 + 1;
  } while (iVar4 != 0x7a);
  return;
}

