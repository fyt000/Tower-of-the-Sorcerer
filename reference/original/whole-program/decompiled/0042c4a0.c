/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0042c4a0.
 * Inferred types, shared tails and runtime effects require assembly review. */

int * root_0042c4a0(int *param_1,undefined4 param_2,int *param_3)

{
  int *extraout_ECX;
  undefined4 extraout_EDX;
  undefined4 *in_FS_OFFSET;
  undefined4 in_stack_ffffffe8;
  undefined4 in_stack_ffffffec;
  
  if ((char)param_2 != '\0') {
    param_1 = (int *)FUN_00402e0c((int)param_1,param_2,param_3,in_stack_ffffffe8,in_stack_ffffffec);
    param_3 = extraout_ECX;
    param_2 = extraout_EDX;
  }
  FUN_00417538((int)param_1,0,param_3);
  *(undefined2 *)(param_1 + 0xd) = DAT_0042c528;
  FUN_004130d8(param_1,0xb9);
  FUN_004130f8(param_1,0x29);
  *(undefined *)(param_1 + 0x47) = 2;
  FUN_0042c828(param_1,2);
  FUN_0042c844(param_1,1);
  *(undefined *)(param_1 + 0x44) = 0;
  FUN_004136e8(param_1,-0x7ffffff1);
  *(undefined *)((int)param_1 + 0x111) = 1;
  if ((char)param_2 != '\0') {
    *in_FS_OFFSET = in_stack_ffffffe8;
  }
  return param_1;
}

