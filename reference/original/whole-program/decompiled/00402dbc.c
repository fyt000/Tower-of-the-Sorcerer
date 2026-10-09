/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00402dbc.
 * Inferred types, shared tails and runtime effects require assembly review. */

int FUN_00402dbc(int *param_1,char *param_2)

{
  undefined2 *puVar1;
  int iVar2;
  int iVar3;
  char cVar4;
  int *piVar5;
  int iVar6;
  
  iVar3 = 0;
  iVar6 = 0;
  cVar4 = *param_2;
  iVar2 = *param_1;
  do {
    puVar1 = *(undefined2 **)(iVar2 + -0x28);
    if (puVar1 != (undefined2 *)0x0) {
      iVar6 = CONCAT22((short)((uint)iVar6 >> 0x10),*puVar1);
      piVar5 = (int *)(puVar1 + 3);
      do {
        iVar3 = CONCAT31((int3)((uint)iVar3 >> 8),*(char *)((int)piVar5 + 6));
        if (*(char *)((int)piVar5 + 6) == cVar4) {
          while (((*(byte *)((int)piVar5 + iVar3 + 6) ^ param_2[iVar3]) & 0xdf) == 0) {
            iVar3 = iVar3 + -1;
            if (iVar3 == 0) {
              return *piVar5 + (int)param_1;
            }
          }
          cVar4 = *param_2;
          iVar3 = CONCAT31((int3)((uint)iVar3 >> 8),*(undefined *)((int)piVar5 + 6));
        }
        piVar5 = (int *)((int)piVar5 + iVar3 + 7);
        iVar6 = iVar6 + -1;
      } while (iVar6 != 0);
    }
    iVar2 = *(int *)(iVar2 + -0x14);
  } while (iVar2 != 0);
  return 0;
}

