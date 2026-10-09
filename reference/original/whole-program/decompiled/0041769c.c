/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0041769c.
 * Inferred types, shared tails and runtime effects require assembly review. */

int FUN_0041769c(int param_1,undefined4 param_2,int *param_3)

{
  int *extraout_ECX;
  undefined4 extraout_ECX_00;
  undefined4 extraout_EDX;
  undefined4 extraout_EDX_00;
  undefined4 *in_FS_OFFSET;
  undefined4 in_stack_ffffffe8;
  undefined4 in_stack_ffffffec;
  
  if ((char)param_2 != '\0') {
    param_1 = FUN_00402e0c(param_1,param_2,param_3,in_stack_ffffffe8,in_stack_ffffffec);
    param_3 = extraout_ECX;
    param_2 = extraout_EDX;
  }
  FUN_0040e4b8(param_1,0,param_3);
  *(undefined4 *)(param_1 + 0x24) = 0x10;
  *(undefined4 *)(param_1 + 0x20) = 0x10;
  FUN_00417780(param_1,extraout_EDX_00,extraout_ECX_00);
  if ((char)param_2 != '\0') {
    *in_FS_OFFSET = in_stack_ffffffe8;
  }
  return param_1;
}

