/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0041c0d0.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_0041c0d0(int *param_1,int *param_2)

{
  int *piVar1;
  
  piVar1 = (int *)FUN_00402b78(param_2);
  piVar1 = FUN_00402c7c((int **)param_1[1],piVar1);
  if ((char)piVar1 != '\0') {
    (**(code **)(*param_2 + 8))(param_2,param_1[1]);
    return;
  }
  FUN_00409e5c(param_1,param_2);
  return;
}

