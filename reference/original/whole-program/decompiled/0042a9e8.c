/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0042a9e8.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_0042a9e8(int **param_1,int *param_2)

{
  if ((int)param_2 < 0) {
    param_2 = (int *)0x0;
  }
  if (param_2 != param_1[0x47]) {
    param_1[0x47] = param_2;
    FUN_00415174(param_1);
  }
  return;
}

