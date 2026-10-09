/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0043f43c.
 * Inferred types, shared tails and runtime effects require assembly review. */

int ** root_0043f43c(int **param_1,undefined4 param_2,int *param_3)

{
  int *extraout_ECX;
  undefined4 extraout_EDX;
  undefined4 *in_FS_OFFSET;
  undefined4 in_stack_ffffffe8;
  undefined4 in_stack_ffffffec;
  
  if ((char)param_2 != '\0') {
    param_1 = (int **)FUN_00402e0c((int)param_1,param_2,param_3,in_stack_ffffffe8,in_stack_ffffffec)
    ;
    param_3 = extraout_ECX;
    param_2 = extraout_EDX;
  }
  FUN_0042a780((int *)param_1,0,param_3);
  FUN_004130d8((int *)param_1,0x91);
  *(undefined *)(param_1 + 0x51) = DAT_0043f4d4;
  FUN_00402768('\0',(int *)(param_1 + 0x4f));
  FUN_0040352c((int *)(param_1 + 0x50),(undefined4 *)&DAT_0043f4e0);
  FUN_0042aa04(param_1,'\0');
  param_1[0x5a] = (int *)0xffffffff;
  (*(code *)(*param_1)[0x23])();
  FUN_0042aa58(param_1,'\x01');
  FUN_0042aa6c(param_1,'\x01');
  FUN_0043fdc4(param_1);
  if ((char)param_2 != '\0') {
    *in_FS_OFFSET = in_stack_ffffffe8;
  }
  return param_1;
}

