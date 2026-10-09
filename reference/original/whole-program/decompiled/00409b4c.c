/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00409b4c.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00409b4c(undefined4 *param_1,int param_2)

{
  if ((param_2 < (int)param_1[2]) || (0x7ffffff < param_2)) {
    (**(code **)*param_1)();
  }
  if (param_2 != param_1[3]) {
    FUN_00402680(param_1 + 1,param_2 << 2);
    param_1[3] = param_2;
  }
  return;
}

