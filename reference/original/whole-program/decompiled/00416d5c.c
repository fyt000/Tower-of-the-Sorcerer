/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00416d5c.
 * Inferred types, shared tails and runtime effects require assembly review. */

int FUN_00416d5c(int param_1)

{
  int iVar1;
  
  if (*(int *)(param_1 + 0x20) != 0) {
    iVar1 = FUN_00409a88(*(int *)(*(int *)(param_1 + 0x20) + 0xb8),param_1);
    return iVar1;
  }
  return -1;
}

