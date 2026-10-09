/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00402d80.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00402d80(int param_1,int param_2,byte *param_3)

{
  undefined2 *puVar1;
  int iVar2;
  ushort *puVar3;
  
  iVar2 = 0;
  do {
    puVar1 = *(undefined2 **)(param_1 + -0x24);
    if (puVar1 != (undefined2 *)0x0) {
      iVar2 = CONCAT22((short)((uint)iVar2 >> 0x10),*puVar1);
      puVar3 = puVar1 + 1;
      do {
        if (param_2 == *(int *)(puVar3 + 1)) {
          iVar2 = *(byte *)(puVar3 + 3) + 1;
          puVar3 = puVar3 + 3;
          for (; iVar2 != 0; iVar2 = iVar2 + -1) {
            *param_3 = *(byte *)puVar3;
            puVar3 = (ushort *)((int)puVar3 + 1);
            param_3 = param_3 + 1;
          }
          return;
        }
        puVar3 = (ushort *)((int)puVar3 + (uint)*puVar3);
        iVar2 = iVar2 + -1;
      } while (iVar2 != 0);
    }
    param_1 = *(int *)(param_1 + -0x14);
  } while (param_1 != 0);
  *param_3 = 0;
  return;
}

