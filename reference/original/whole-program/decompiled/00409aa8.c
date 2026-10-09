/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00409aa8.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00409aa8(int *param_1,int param_2,undefined4 param_3)

{
  if ((param_2 < 0) || (param_1[2] < param_2)) {
    (**(code **)*param_1)();
  }
  if (param_1[2] == param_1[3]) {
    (**(code **)(*param_1 + 4))();
  }
  if (param_2 < param_1[2]) {
    FUN_00402870((undefined4 *)(param_1[1] + param_2 * 4),
                 (undefined4 *)(param_1[1] + 4 + param_2 * 4),(param_1[2] - param_2) * 4);
  }
  *(undefined4 *)(param_1[1] + param_2 * 4) = param_3;
  param_1[2] = param_1[2] + 1;
  return;
}

