/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00419f34.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00419f34(int *param_1,int **param_2)

{
  int *piVar1;
  undefined4 extraout_ECX;
  undefined4 extraout_EDX;
  
  piVar1 = FUN_00402c7c(param_2,(int *)&PTR_FUN_00418e44);
  if ((char)piVar1 == '\0') {
    FUN_00409d78(param_1,param_2);
  }
  else {
    FUN_0041970c(DAT_0048a6ec,param_1,param_2[3]);
    FUN_0041a014(param_1,CONCAT31((int3)((uint)extraout_EDX >> 8),*(undefined *)(param_2 + 4)),
                 extraout_ECX);
  }
  return;
}

