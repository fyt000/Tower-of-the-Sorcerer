/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0041c648.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_0041c648(int *param_1,int **param_2)

{
  int *piVar1;
  int iVar2;
  undefined4 extraout_ECX;
  undefined4 extraout_EDX;
  
  if (param_2 != (int **)0x0) {
    piVar1 = FUN_00402c7c(param_2,(int *)&PTR_FUN_00419270);
    if ((char)piVar1 == '\0') {
      FUN_00409d78(param_1,param_2);
      return;
    }
  }
  FUN_0041c5b0((int *)param_1[4]);
  if (param_2 == (int **)0x0) {
    iVar2 = FUN_00402c0c(0x41922c,CONCAT31((int3)((uint)extraout_EDX >> 8),1),extraout_ECX);
    param_1[4] = iVar2;
    *(undefined *)(param_1 + 5) = 1;
  }
  else {
    param_1[4] = (int)param_2[4];
    *(undefined *)(param_1 + 5) = *(undefined *)(param_2 + 5);
  }
  FUN_0041c5ac(param_1[4]);
  FUN_0041bd8c((int)param_1);
  return;
}

