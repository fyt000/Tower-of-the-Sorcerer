/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00412c54.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00412c54(int **param_1,int param_2)

{
  FUN_00409b2c(*param_1,param_2);
  if ((*param_1)[2] == 0) {
    FUN_00402c34(*param_1);
    *param_1 = (int *)0x0;
  }
  return;
}

