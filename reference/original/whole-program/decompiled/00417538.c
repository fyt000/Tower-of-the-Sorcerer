/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00417538.
 * Inferred types, shared tails and runtime effects require assembly review. */

int FUN_00417538(int param_1,undefined4 param_2,int *param_3)

{
  int *piVar1;
  int *extraout_ECX;
  undefined4 extraout_ECX_00;
  undefined4 extraout_EDX;
  undefined4 extraout_EDX_00;
  undefined4 *in_FS_OFFSET;
  undefined4 in_stack_ffffffe0;
  undefined4 in_stack_ffffffe4;
  
  if ((char)param_2 != '\0') {
    param_1 = FUN_00402e0c(param_1,param_2,param_3,in_stack_ffffffe0,in_stack_ffffffe4);
    param_3 = extraout_ECX;
    param_2 = extraout_EDX;
  }
  FUN_004143c4(param_1,0,param_3);
  piVar1 = (int *)FUN_0041a240(0x411298,CONCAT31((int3)((uint)extraout_EDX_00 >> 8),1),
                               extraout_ECX_00);
  *(int **)(param_1 + 0x100) = piVar1;
  FUN_00412d80(piVar1,param_1);
  if ((char)param_2 != '\0') {
    *in_FS_OFFSET = in_stack_ffffffe0;
  }
  return param_1;
}

