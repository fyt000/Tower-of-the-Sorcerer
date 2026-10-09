/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0040a14c.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0040a14c(int *param_1)

{
  if (param_1[1] == 0) {
    (**(code **)(*param_1 + 0x28))(param_1,1);
  }
  param_1[1] = param_1[1] + 1;
  return;
}

