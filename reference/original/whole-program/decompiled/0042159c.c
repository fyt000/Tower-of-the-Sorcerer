/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0042159c.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_0042159c(int **param_1,int **param_2)

{
  if ((param_2 != (int **)param_1[8]) && (param_1 != param_2)) {
    if ((int **)param_1[8] == (int **)0x0) {
      FUN_00415130((int *)param_1);
    }
    FUN_004134b8(param_1,param_2);
    if (param_1[8] == (int *)0x0) {
      FUN_004152ac(param_1);
    }
  }
  return;
}

