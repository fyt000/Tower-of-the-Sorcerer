/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0043dd5c.
 * Inferred types, shared tails and runtime effects require assembly review. */

int * FUN_0043dd5c(int *param_1,undefined4 param_2,int *param_3)

{
  int *extraout_ECX;
  undefined4 extraout_ECX_00;
  undefined4 extraout_EDX;
  undefined4 extraout_EDX_00;
  undefined4 *in_FS_OFFSET;
  undefined4 in_stack_fffffee4;
  undefined4 in_stack_fffffee8;
  undefined4 local_105;
  char local_5;
  
  if ((char)param_2 != '\0') {
    param_1 = (int *)FUN_00402e0c((int)param_1,param_2,param_3,in_stack_fffffee4,in_stack_fffffee8);
    param_3 = extraout_ECX;
    param_2 = extraout_EDX;
  }
  local_5 = (char)param_2;
  FUN_0042945c(param_1,0,param_3);
  (**(code **)(*param_1 + 0x90))(param_1,3);
  FUN_0043e450((int)param_1,extraout_EDX_00,extraout_ECX_00);
  FUN_004027e0('\0',&local_105,0xff);
  *(char *)(param_1 + 0x57) = local_105._1_1_;
  if (local_105._1_1_ == '\\') {
    *(undefined *)(param_1 + 0x57) = 0;
  }
  FUN_0043e418((int)param_1);
  if (local_5 != '\0') {
    *in_FS_OFFSET = in_stack_fffffee4;
  }
  return param_1;
}

