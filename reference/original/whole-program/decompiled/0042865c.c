/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0042865c.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0042865c(int **param_1,char param_2)

{
  if (param_2 != *(char *)(param_1 + 0x41)) {
    *(char *)(param_1 + 0x41) = param_2;
    FUN_00428a10((int *)param_1);
    FUN_00415174(param_1);
  }
  return;
}

