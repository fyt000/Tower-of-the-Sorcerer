/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00428680.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_00428680(int **param_1,char param_2)

{
  if (param_2 != *(char *)((int)param_1 + 0x10b)) {
    *(char *)((int)param_1 + 0x10b) = param_2;
    FUN_00415174(param_1);
  }
  return;
}

