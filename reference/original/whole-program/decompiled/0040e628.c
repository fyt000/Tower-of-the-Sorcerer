/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0040e628.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0040e628(int param_1,int param_2)

{
  *(undefined4 *)(param_2 + 4) = 0;
  FUN_00409b2c(*(undefined4 **)(param_1 + 0x10),param_2);
  if ((*(int **)(param_1 + 0x10))[2] == 0) {
    FUN_00402c34(*(int **)(param_1 + 0x10));
    *(undefined4 *)(param_1 + 0x10) = 0;
  }
  return;
}

