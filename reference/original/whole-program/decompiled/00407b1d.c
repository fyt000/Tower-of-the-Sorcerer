/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00407b1d.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00407b1d(void)

{
  int iVar1;
  undefined *puVar2;
  undefined *unaff_EDI;
  
  if (DAT_0048a548 != (undefined *)0x0) {
    puVar2 = DAT_0048a548;
    for (iVar1 = *(int *)(DAT_0048a548 + -4); iVar1 != 0; iVar1 = iVar1 + -1) {
      *unaff_EDI = *puVar2;
      puVar2 = puVar2 + 1;
      unaff_EDI = unaff_EDI + 1;
    }
  }
  return;
}

