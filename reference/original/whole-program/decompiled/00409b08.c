/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00409b08.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00409b08(undefined4 *param_1,int param_2,undefined4 param_3)

{
  if ((param_2 < 0) || ((int)param_1[2] <= param_2)) {
    (**(code **)*param_1)();
  }
  *(undefined4 *)(param_1[1] + param_2 * 4) = param_3;
  return;
}

