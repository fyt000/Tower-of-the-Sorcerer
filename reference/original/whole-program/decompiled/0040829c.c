/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0040829c.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0040829c(int param_1,undefined4 *param_2)

{
  int iVar1;
  uint uVar2;
  undefined3 uVar4;
  int iVar3;
  undefined4 *puVar5;
  int iVar6;
  
  puVar5 = param_2;
  for (uVar2 = (uint)*(ushort *)(param_1 + 10 + (uint)*(byte *)(param_1 + 1)); uVar2 != 0;
      uVar2 = uVar2 - 1) {
    *puVar5 = 0;
    puVar5 = puVar5 + 1;
  }
  do {
    uVar4 = (undefined3)(uVar2 >> 8);
    iVar1 = param_1 + 2 + CONCAT31(uVar4,*(undefined *)(param_1 + 1));
    iVar3 = CONCAT31(uVar4,*(undefined *)(iVar1 + 10));
    uVar2 = (uint)*(ushort *)(iVar1 + 0xb + iVar3);
    if (uVar2 != 0) {
      iVar6 = iVar1 + 0xd + iVar3;
      do {
        iVar3 = CONCAT31((int3)((uint)iVar3 >> 8),*(undefined *)(iVar6 + 0x1a));
        if (param_2[*(ushort *)(iVar6 + 0x18)] == 0) {
          param_2[*(ushort *)(iVar6 + 0x18)] = iVar6;
        }
        iVar6 = iVar6 + 0x1b + iVar3;
        uVar2 = uVar2 - 1;
      } while (uVar2 != 0);
    }
    param_1 = *(int *)(iVar1 + 4);
    uVar2 = 0;
  } while (param_1 != 0);
  return;
}

