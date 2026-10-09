/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x004107ec.
 * Inferred types, shared tails and runtime effects require assembly review. */

int * FUN_004107ec(int *param_1,undefined4 param_2,int *param_3)

{
  int iVar1;
  int *extraout_ECX;
  undefined4 extraout_EDX;
  undefined4 *in_FS_OFFSET;
  undefined4 in_stack_ffffffdc;
  undefined4 in_stack_ffffffe0;
  
  if ((char)param_2 != '\0') {
    param_1 = (int *)FUN_00402e0c((int)param_1,param_2,param_3,in_stack_ffffffdc,in_stack_ffffffe0);
    param_3 = extraout_ECX;
    param_2 = extraout_EDX;
  }
  iVar1 = FUN_0040fd50(0x40f20c,CONCAT31((int3)((uint)param_2 >> 8),1),param_1);
  param_1[8] = iVar1;
  *(int **)(iVar1 + 0x8c) = param_1;
  *(undefined4 *)(iVar1 + 0x88) = *(undefined4 *)(*param_1 + 0x28);
  *(int **)(iVar1 + 0x84) = param_1;
  FUN_0040e4b8((int)param_1,0,param_3);
  if ((char)param_2 != '\0') {
    *in_FS_OFFSET = in_stack_ffffffdc;
  }
  return param_1;
}

