/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00419c7c.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00419c7c(int *param_1,int param_2,undefined4 param_3)

{
  if (param_2 != param_1[4]) {
    param_1[4] = param_2;
    FUN_00402cdc(param_1,param_2,param_3);
  }
  return;
}

