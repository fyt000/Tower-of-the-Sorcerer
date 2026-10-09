/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0042c314.
 * Inferred types, shared tails and runtime effects require assembly review. */

int root_0042c314(int param_1,undefined4 param_2,int *param_3)

{
  int iVar1;
  HWND pHVar2;
  undefined extraout_CL;
  int *extraout_ECX;
  undefined extraout_DL;
  undefined4 extraout_EDX;
  undefined4 *in_FS_OFFSET;
  undefined4 in_stack_ffffffe8;
  undefined4 in_stack_ffffffec;
  
  if ((char)param_2 != '\0') {
    param_1 = FUN_00402e0c(param_1,param_2,param_3,in_stack_ffffffe8,in_stack_ffffffec);
    param_3 = extraout_ECX;
    param_2 = extraout_EDX;
  }
  iVar1 = FUN_0040e4b8(param_1,0,param_3);
  *(undefined *)(param_1 + 0x20) = 1;
  *(undefined4 *)(param_1 + 0x24) = 1000;
  pHVar2 = FUN_0041fe08((char)iVar1,extraout_DL,extraout_CL,root_0042c390,param_1);
  *(HWND *)(param_1 + 0x28) = pHVar2;
  if ((char)param_2 != '\0') {
    *in_FS_OFFSET = in_stack_ffffffe8;
  }
  return param_1;
}

