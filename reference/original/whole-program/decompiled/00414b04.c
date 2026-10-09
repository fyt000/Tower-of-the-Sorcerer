/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00414b04.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00414b04(int *param_1,int **param_2)

{
  int *piVar1;
  undefined4 extraout_ECX;
  undefined4 extraout_ECX_00;
  
  if (param_2 != (int **)0x0) {
    piVar1 = FUN_00402c7c(param_2,(int *)&PTR_FUN_004118e4);
    if ((char)piVar1 == '\0') {
      FUN_00412c2c((int **)(param_1 + 0x2c),param_2,extraout_ECX);
    }
    else {
      FUN_00412c2c((int **)(param_1 + 0x2d),param_2,extraout_ECX);
      FUN_00412c2c((int **)(param_1 + 0x2e),param_2,extraout_ECX_00);
    }
    param_2[8] = param_1;
  }
  return;
}

