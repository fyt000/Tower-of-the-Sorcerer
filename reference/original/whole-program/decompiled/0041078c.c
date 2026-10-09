/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0041078c.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_0041078c(int param_1,int **param_2)

{
  int *piVar1;
  
  if (*(int **)(param_1 + 0x44) != (int *)0x0) {
    FUN_004106d8(*(int **)(param_1 + 0x44),param_1);
  }
  if (param_2 != (int **)0x0) {
    piVar1 = FUN_00402c7c(param_2,(int *)&PTR_FUN_0040f470);
    if ((char)piVar1 == '\0') {
      piVar1 = FUN_00402c7c(param_2,(int *)&PTR_FUN_0040f20c);
      if ((char)piVar1 != '\0') {
        root_004106bc(param_2,param_1);
      }
    }
    else {
      root_004106bc(param_2[8],param_1);
    }
  }
  return;
}

