/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00420250.
 * Inferred types, shared tails and runtime effects require assembly review. */

int FUN_00420250(short param_1,uint param_2,int param_3,int param_4)

{
  int iVar1;
  bool bVar2;
  uint extraout_EDX;
  uint uVar3;
  int iVar4;
  
  iVar4 = 0;
  if (*(char *)(param_4 + -5) == '\0') {
    uVar3 = param_2;
    if ((*(char *)(param_4 + -6) != '\0') &&
       (iVar1 = param_4, bVar2 = FUN_0042021c(param_1,param_2,param_3,param_4), param_3 = iVar1,
       uVar3 = extraout_EDX, !bVar2)) {
      iVar4 = GetSystemMetrics(param_2 & 0xffff);
      return -(iVar4 - *(int *)(param_4 + -0xc));
    }
    if ((*(char *)(param_4 + -6) == '\0') &&
       (bVar2 = FUN_0042021c(param_1,uVar3,param_3,param_4), bVar2)) {
      iVar4 = GetSystemMetrics(param_2 & 0xffff);
      iVar4 = iVar4 - *(int *)(param_4 + -0xc);
    }
  }
  return iVar4;
}

