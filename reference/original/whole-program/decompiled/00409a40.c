/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00409a40.
 * Inferred types, shared tails and runtime effects require assembly review. */

undefined4 FUN_00409a40(undefined4 *param_1,int param_2)

{
  if ((param_2 < 0) || ((int)param_1[2] <= param_2)) {
    (**(code **)*param_1)();
  }
  return *(undefined4 *)(param_1[1] + param_2 * 4);
}

