/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00410cac.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00410cac(int param_1,int param_2)

{
  if ((param_2 != 0) && (*(int *)(*(int *)(param_1 + 0x20) + 100) == *(int *)(param_2 + 0x20))) {
    FUN_00410120(*(int **)(param_1 + 0x20),0);
  }
  return;
}

