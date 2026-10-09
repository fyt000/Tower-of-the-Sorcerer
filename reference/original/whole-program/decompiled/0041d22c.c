/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0041d22c.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0041d22c(int param_1)

{
  int *piVar1;
  int iVar2;
  
  iVar2 = DAT_00489570[2] + -1;
  if (-1 < iVar2) {
    do {
      piVar1 = (int *)FUN_00409a40(DAT_00489570,iVar2);
      if ((piVar1[0xd] != 0) && (param_1 == *(int *)(*(int *)(piVar1[0xd] + 0x10) + 0xc))) {
        FUN_0041d2c8(piVar1);
      }
      iVar2 = iVar2 + -1;
    } while (iVar2 != -1);
  }
  return;
}

