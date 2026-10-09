/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00421d7c.
 * Inferred types, shared tails and runtime effects require assembly review. */

int FUN_00421d7c(int param_1)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 0x13c);
  if (iVar1 == 0) {
    iVar1 = *(int *)(DAT_0048a6fc + 0x24);
  }
  return iVar1;
}

