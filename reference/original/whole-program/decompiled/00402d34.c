/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00402d34.
 * Inferred types, shared tails and runtime effects require assembly review. */

undefined4 FUN_00402d34(int param_1,byte *param_2)

{
  byte bVar1;
  int iVar2;
  int iVar3;
  byte bVar4;
  undefined2 *puVar5;
  int iVar6;
  
  iVar2 = 0;
  iVar6 = 0;
  bVar4 = *param_2;
  do {
    puVar5 = *(undefined2 **)(param_1 + -0x24);
    if (puVar5 != (undefined2 *)0x0) {
      iVar6 = CONCAT22((short)((uint)iVar6 >> 0x10),*puVar5);
      puVar5 = puVar5 + 1;
      do {
        bVar1 = *(byte *)(puVar5 + 3);
        iVar3 = CONCAT31((int3)((uint)iVar2 >> 8),bVar1);
        if (bVar1 == bVar4) {
          iVar3 = CONCAT22((short)((uint)iVar2 >> 0x10),(ushort)bVar1);
          while (((*(byte *)((int)puVar5 + iVar3 + 6) ^ param_2[iVar3]) & 0xdf) == 0) {
            iVar3 = iVar3 + -1;
            if (iVar3 == 0) {
              return *(undefined4 *)(puVar5 + 1);
            }
          }
          bVar4 = *param_2;
        }
        iVar2 = CONCAT22((short)((uint)iVar3 >> 0x10),*puVar5);
        puVar5 = (undefined2 *)((int)puVar5 + iVar2);
        iVar6 = iVar6 + -1;
      } while (iVar6 != 0);
    }
    param_1 = *(int *)(param_1 + -0x14);
  } while (param_1 != 0);
  return 0;
}

