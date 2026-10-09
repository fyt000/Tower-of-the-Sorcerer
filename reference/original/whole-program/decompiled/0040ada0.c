/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0040ada0.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_0040ada0(int *param_1,int param_2,undefined4 param_3)

{
  if ((param_2 < 0) || (param_1[3] <= param_2)) {
    FUN_00409978(param_1,param_2);
  }
  (**(code **)(*param_1 + 0x6c))();
  *(undefined4 *)(param_1[2] + 4 + param_2 * 8) = param_3;
  (**(code **)(*param_1 + 0x68))();
  return;
}

