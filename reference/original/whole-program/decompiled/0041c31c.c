/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0041c31c.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_0041c31c(int *param_1,int **param_2)

{
  int *piVar1;
  
  if (param_2 == (int **)0x0) {
    FUN_0041c160((int)param_1,(undefined4 *)0x0);
    return;
  }
  piVar1 = FUN_00402c7c(param_2,(int *)&PTR_root_004191c0);
  if ((char)piVar1 == '\0') {
    piVar1 = FUN_00402c7c(param_2,(int *)&PTR_FUN_004190c4);
    if ((char)piVar1 == '\0') {
      FUN_00409d78(param_1,param_2);
    }
    else {
      FUN_0041c160((int)param_1,param_2);
    }
  }
  else {
    FUN_0041c160((int)param_1,param_2[1]);
  }
  return;
}

