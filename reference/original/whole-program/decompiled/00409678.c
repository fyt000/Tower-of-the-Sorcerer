/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00409678.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00409678(void)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  
  iVar2 = DAT_0048a614[2];
  if (-1 < iVar2 + -1) {
    iVar3 = 0;
    do {
      piVar1 = (int *)FUN_00409a40(DAT_0048a614,iVar3);
      (**(code **)(*piVar1 + 0xc))();
      iVar3 = iVar3 + 1;
      iVar2 = iVar2 + -1;
    } while (iVar2 != 0);
  }
  return;
}

