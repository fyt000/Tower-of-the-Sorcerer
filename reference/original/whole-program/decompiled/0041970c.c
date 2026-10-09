/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0041970c.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0041970c(int param_1,int *param_2,undefined4 *param_3)

{
  undefined4 *puVar1;
  
  puVar1 = (undefined4 *)param_2[3];
  if (param_3 != puVar1) {
    param_3[1] = param_3[1] + 1;
    param_2[3] = (int)param_3;
    FUN_00402cdc(param_2,param_2,param_3);
    FUN_00419680(param_1,puVar1);
  }
  return;
}

