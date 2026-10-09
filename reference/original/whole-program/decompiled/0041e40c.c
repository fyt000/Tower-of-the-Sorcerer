/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0041e40c.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0041e40c(int *param_1,int **param_2)

{
  int *piVar1;
  
  if ((param_2 != (int **)0x0) &&
     (piVar1 = FUN_00402c7c(param_2,(int *)&PTR_FUN_004194a4), (char)piVar1 == '\0')) {
    FUN_00409d78(param_1,param_2);
    return;
  }
  if (param_2 == (int **)0x0) {
    FUN_0041e6b4((int)param_1,0,0);
  }
  else {
    FUN_0041d3a0((int)param_2[4]);
    FUN_0041d3a4((int *)param_1[4]);
    param_1[4] = (int)param_2[4];
  }
  FUN_0041bd8c((int)param_1);
  return;
}

