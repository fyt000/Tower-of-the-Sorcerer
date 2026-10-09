/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00421bc0.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_00421bc0(int param_1,int *param_2)

{
  *(int **)(param_1 + 0x140) = param_2;
  if (param_2 != (int *)0x0) {
    FUN_00410378(param_2,0);
  }
  return;
}

