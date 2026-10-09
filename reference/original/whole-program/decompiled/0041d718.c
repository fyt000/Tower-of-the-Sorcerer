/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0041d718.
 * Inferred types, shared tails and runtime effects require assembly review. */

int FUN_0041d718(int param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  undefined4 extraout_ECX;
  undefined4 extraout_ECX_00;
  undefined4 extraout_EDX;
  undefined4 extraout_EDX_00;
  undefined4 *in_FS_OFFSET;
  undefined4 in_stack_ffffffe4;
  undefined4 in_stack_ffffffe8;
  
  if ((char)param_2 != '\0') {
    param_1 = FUN_00402e0c(param_1,param_2,param_3,in_stack_ffffffe4,in_stack_ffffffe8);
    param_3 = extraout_ECX;
    param_2 = extraout_EDX;
  }
  FUN_0041bd5c(param_1,0,param_3);
  iVar1 = FUN_00402c0c(0x41936c,CONCAT31((int3)((uint)extraout_EDX_00 >> 8),1),extraout_ECX_00);
  *(int *)(param_1 + 0x10) = iVar1;
  FUN_0041d3a0(iVar1);
  if ((char)param_2 != '\0') {
    *in_FS_OFFSET = in_stack_ffffffe4;
  }
  return param_1;
}

