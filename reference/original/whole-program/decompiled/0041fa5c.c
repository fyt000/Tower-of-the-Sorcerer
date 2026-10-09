/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0041fa5c.
 * Inferred types, shared tails and runtime effects require assembly review. */

int root_0041fa5c(undefined *param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  iVar1 = FUN_00423bbc(DAT_0048a6fc);
  if (-1 < iVar1 + -1) {
    iVar4 = 0;
    do {
      iVar2 = FUN_00423bb0(DAT_0048a6fc,iVar4);
      iVar3 = FUN_00405a34(param_1,*(undefined **)(iVar2 + 8));
      if (iVar3 == 0) {
        return iVar2;
      }
      iVar4 = iVar4 + 1;
      iVar1 = iVar1 + -1;
    } while (iVar1 != 0);
  }
  iVar1 = FUN_00423d1c(DAT_0048a6fc);
  if (-1 < iVar1 + -1) {
    iVar4 = 0;
    do {
      iVar2 = FUN_00423d10(DAT_0048a6fc,iVar4);
      iVar3 = FUN_00405a34(param_1,*(undefined **)(iVar2 + 8));
      if (iVar3 == 0) {
        return iVar2;
      }
      iVar4 = iVar4 + 1;
      iVar1 = iVar1 + -1;
    } while (iVar1 != 0);
  }
  return 0;
}

