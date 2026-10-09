/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00402c0c.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00402c0c(int param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 extraout_EDX;
  undefined4 *in_FS_OFFSET;
  undefined4 in_stack_00000000;
  undefined4 in_stack_fffffff0;
  undefined4 in_stack_fffffff4;
  
  if ((char)param_2 != '\0') {
    FUN_00402e0c(param_1,param_2,param_3,in_stack_fffffff0,in_stack_fffffff4);
    param_2 = extraout_EDX;
  }
  if ((char)param_2 != '\0') {
    *in_FS_OFFSET = in_stack_00000000;
  }
  return;
}

