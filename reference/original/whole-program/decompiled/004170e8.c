/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x004170e8.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_004170e8(undefined4 param_1,int **param_2,int param_3)

{
  int *piVar1;
  
  piVar1 = FUN_00402c7c(param_2,(int *)&PTR_FUN_004118e4);
  if ((char)piVar1 != '\0') {
    FUN_00416a0c((int)param_2,param_3);
    return;
  }
  piVar1 = FUN_00402c7c(param_2,(int *)&PTR_FUN_004115fc);
  if ((char)piVar1 != '\0') {
    FUN_00413794(param_2,param_3);
  }
  return;
}

