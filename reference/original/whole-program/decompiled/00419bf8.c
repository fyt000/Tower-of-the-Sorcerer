/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00419bf8.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00419bf8(int *param_1,int **param_2)

{
  int *piVar1;
  int iVar2;
  undefined4 extraout_ECX;
  
  piVar1 = FUN_00402c7c(param_2,(int *)&PTR_FUN_00418d20);
  if ((char)piVar1 == '\0') {
    FUN_00409d78(param_1,param_2);
  }
  else {
    FUN_0041970c(DAT_0048a6e8,param_1,param_2[3]);
    FUN_00419c7c(param_1,(int)param_2[4],extraout_ECX);
    if (param_2[5] != (int *)param_1[5]) {
      iVar2 = FUN_00419e30((int)param_2);
      FUN_00419e4c(param_1,iVar2);
    }
  }
  return;
}

