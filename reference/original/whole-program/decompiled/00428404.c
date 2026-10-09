/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00428404.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_00428404(int *param_1,char param_2)

{
  if (param_2 != *(char *)(param_1 + 0x2c)) {
    *(char *)(param_1 + 0x2c) = param_2;
    (**(code **)(*param_1 + 0x44))();
  }
  return;
}

