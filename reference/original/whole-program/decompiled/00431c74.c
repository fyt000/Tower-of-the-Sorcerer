/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00431c74.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00431c74(int param_1,int param_2)

{
  if (param_2 != *(int *)(param_1 + 0x1f0)) {
    *(int *)(param_1 + 0x1f0) = param_2;
  }
  *(undefined *)(param_1 + 0x1e4) = 1;
  return;
}

