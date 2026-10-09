/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00414ccc.
 * Inferred types, shared tails and runtime effects require assembly review. */

int FUN_00414ccc(int param_1)

{
  int iVar1;
  
  iVar1 = 0;
  if (*(int *)(param_1 + 0xb0) != 0) {
    iVar1 = *(int *)(*(int *)(param_1 + 0xb0) + 8);
  }
  if (*(int *)(param_1 + 0xb4) != 0) {
    iVar1 = iVar1 + *(int *)(*(int *)(param_1 + 0xb4) + 8);
  }
  return iVar1;
}

