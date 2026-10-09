/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0042905c.
 * Inferred types, shared tails and runtime effects require assembly review. */

int * FUN_0042905c(int *param_1,undefined4 param_2,int *param_3)

{
  int iVar1;
  int *extraout_ECX;
  undefined4 extraout_ECX_00;
  undefined4 extraout_EDX;
  undefined4 extraout_EDX_00;
  undefined4 *in_FS_OFFSET;
  undefined4 in_stack_ffffffe0;
  undefined4 in_stack_ffffffe4;
  
  if ((char)param_2 != '\0') {
    param_1 = (int *)FUN_00402e0c((int)param_1,param_2,param_3,in_stack_ffffffe0,in_stack_ffffffe4);
    param_3 = extraout_ECX;
    param_2 = extraout_EDX;
  }
  FUN_004285a4(param_1,0,param_3);
  FUN_004130d8(param_1,0xb9);
  FUN_004130f8(param_1,0x59);
  FUN_00428648(param_1,'\0');
  *(undefined *)((int)param_1 + 0x11e) = 1;
  *(undefined *)((int)param_1 + 0x11f) = 1;
  iVar1 = FUN_00402c0c(0x427f2c,CONCAT31((int3)((uint)extraout_EDX_00 >> 8),1),extraout_ECX_00);
  param_1[0x46] = iVar1;
  *(int **)(iVar1 + 8) = param_1;
  if ((char)param_2 != '\0') {
    *in_FS_OFFSET = in_stack_ffffffe0;
  }
  return param_1;
}

