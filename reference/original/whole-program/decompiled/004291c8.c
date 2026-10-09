/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x004291c8.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_004291c8(int **param_1,char param_2)

{
  if (param_2 != *(char *)(param_1 + 0x47)) {
    *(char *)(param_1 + 0x47) = param_2;
    FUN_00415174(param_1);
  }
  return;
}

