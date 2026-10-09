/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00402cf4.
 * Inferred types, shared tails and runtime effects require assembly review. */

int root_00402cf4(int param_1,int param_2)

{
  do {
    if (param_1 == param_2) {
      return 1;
    }
    param_1 = *(int *)(param_1 + -0x14);
  } while (param_1 != 0);
  return param_1;
}

