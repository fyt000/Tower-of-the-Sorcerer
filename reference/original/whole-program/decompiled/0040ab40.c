/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0040ab40.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0040ab40(int *param_1,int param_2,int param_3)

{
  if ((((param_2 < 0) || (param_1[3] <= param_2)) || (param_3 < 0)) || (param_1[3] <= param_3)) {
    FUN_00409978(param_1,param_2);
  }
  (**(code **)(*param_1 + 0x6c))();
  FUN_0040ab80((int)param_1,param_2,param_3);
  (**(code **)(*param_1 + 0x68))();
  return;
}

