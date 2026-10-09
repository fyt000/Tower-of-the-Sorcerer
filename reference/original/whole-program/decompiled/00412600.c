/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00412600.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00412600(int param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 extraout_ECX;
  undefined4 extraout_EDX;
  undefined4 *in_FS_OFFSET;
  undefined4 in_stack_00000000;
  undefined4 in_stack_fffffff0;
  undefined4 in_stack_fffffff4;
  
  if ((char)param_2 != '\0') {
    param_1 = FUN_00402e0c(param_1,param_2,param_3,in_stack_fffffff0,in_stack_fffffff4);
    param_3 = extraout_ECX;
    param_2 = extraout_EDX;
  }
  *(undefined4 *)(param_1 + 4) = param_3;
  if ((char)param_2 != '\0') {
    *in_FS_OFFSET = in_stack_00000000;
  }
  return;
}

