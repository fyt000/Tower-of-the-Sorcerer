/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0042ad4c.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0042ad4c(int **param_1,int *param_2)

{
  bool bVar1;
  
  if ((((*(byte *)(param_1 + 7) & 0x10) == 0) &&
      (((*param_2 == 0x201 || (*param_2 == 0x203)) && (bVar1 = FUN_00413b6c((int)param_1), !bVar1)))
      ) && (*(char *)(param_1 + 0xf) == '\x01')) {
    bVar1 = FUN_00415410((int *)param_1,param_2);
    if (bVar1) {
      return;
    }
    *(byte *)((int)param_1 + 0x36) = DAT_0042adac | *(byte *)((int)param_1 + 0x36);
    FUN_00402d0c((int *)param_1,(ushort *)param_2);
    return;
  }
  FUN_0041549c(param_1,param_2);
  return;
}

