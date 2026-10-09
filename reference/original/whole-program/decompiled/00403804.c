/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00403804.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00403804(int param_1)

{
  int iVar1;
  
  if ((param_1 != 0) &&
     (iVar1 = *(int *)(param_1 + -8) + 1,
     iVar1 != 0 && SCARRY4(*(int *)(param_1 + -8),1) == iVar1 < 0)) {
    *(int *)(param_1 + -8) = iVar1;
  }
  return;
}

