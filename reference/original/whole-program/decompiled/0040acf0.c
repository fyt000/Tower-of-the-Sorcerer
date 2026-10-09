/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0040acf0.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0040acf0(int *param_1,int param_2,undefined4 *param_3)

{
  int *piVar1;
  
  (**(code **)(*param_1 + 0x6c))();
  if (param_1[3] == param_1[4]) {
    FUN_0040ac58((int)param_1);
  }
  if (param_2 < param_1[3]) {
    FUN_00402870((undefined4 *)(param_1[2] + param_2 * 8),
                 (undefined4 *)(param_1[2] + 8 + param_2 * 8),(param_1[3] - param_2) * 8);
  }
  piVar1 = (int *)(param_1[2] + param_2 * 8);
  *piVar1 = 0;
  piVar1[1] = 0;
  FUN_0040352c(piVar1,param_3);
  param_1[3] = param_1[3] + 1;
  (**(code **)(*param_1 + 0x68))();
  return;
}

