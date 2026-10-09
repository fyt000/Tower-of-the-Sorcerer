/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0041a784.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0041a784(int *param_1,undefined4 param_2,int *param_3)

{
  if (param_3 != (int *)0x0) {
    (**(code **)(*param_1 + 0x10))();
    FUN_0041aa24(param_1,DAT_0041a7bc);
    (**(code **)(*param_3 + 0x10))(param_3,param_1,param_2);
    (**(code **)(*param_1 + 0xc))();
  }
  return;
}

