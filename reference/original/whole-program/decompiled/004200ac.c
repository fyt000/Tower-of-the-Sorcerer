/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x004200ac.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_004200ac(int *param_1,int **param_2)

{
  int *piVar1;
  
  piVar1 = FUN_00402c7c(param_2,(int *)&PTR_FUN_0041e8dc);
  if ((char)piVar1 == '\0') {
    FUN_00409d78(param_1,param_2);
  }
  else {
    FUN_00420518((int)param_1,*(undefined *)(param_2 + 7));
    FUN_004204f8((int)param_1,(int)param_2[4]);
    FUN_00420424((int)param_1,(int)param_2[3]);
    *(undefined2 *)(param_1 + 2) = *(undefined2 *)(param_2 + 2);
  }
  return;
}

