/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00413138.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00413138(int *param_1,int *param_2)

{
  (**(code **)(*param_1 + 0x4c))
            (param_1,*param_2,param_2[1],param_2[3] - param_2[1],param_2[2] - *param_2);
  return;
}

