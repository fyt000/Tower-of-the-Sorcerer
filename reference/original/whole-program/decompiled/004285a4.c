/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x004285a4.
 * Inferred types, shared tails and runtime effects require assembly review. */

int * FUN_004285a4(int *param_1,undefined4 param_2,int *param_3)

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
  FUN_004143c4((int)param_1,0,param_3);
  if (DAT_0048a694 == '\0') {
    *(undefined2 *)(param_1 + 0xd) = DAT_00428644;
  }
  else {
    *(undefined2 *)(param_1 + 0xd) = DAT_00428640;
  }
  FUN_004130d8(param_1,0x79);
  FUN_004130f8(param_1,0x19);
  FUN_00416df4(param_1,'\x01');
  FUN_0041370c(param_1,'\0');
  *(undefined *)(param_1 + 0x41) = 1;
  *(undefined *)((int)param_1 + 0x107) = 1;
  *(undefined *)(param_1 + 0x42) = 1;
  *(undefined *)((int)param_1 + 0x109) = 1;
  FUN_00428a54(param_1);
  if ((char)param_2 != '\0') {
    *in_FS_OFFSET = in_stack_ffffffe8;
  }
  return param_1;
}

