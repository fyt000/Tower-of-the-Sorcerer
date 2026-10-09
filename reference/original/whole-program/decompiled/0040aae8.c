/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0040aae8.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_0040aae8(int *param_1,int param_2)

{
  if ((param_2 < 0) || (param_1[3] <= param_2)) {
    FUN_00409978(param_1,param_2);
  }
  (**(code **)(*param_1 + 0x6c))();
  FUN_00403b14((VARIANTARG *)(param_1[2] + param_2 * 8),"\x0e\vTStringItem\b");
  param_1[3] = param_1[3] + -1;
  if (param_2 < param_1[3]) {
    FUN_00402870((undefined4 *)(param_1[2] + 8 + param_2 * 8),
                 (undefined4 *)(param_1[2] + param_2 * 8),(param_1[3] - param_2) * 8);
  }
  (**(code **)(*param_1 + 0x68))();
  return;
}

