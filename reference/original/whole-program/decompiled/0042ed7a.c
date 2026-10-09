/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0042ed7a.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_0042ed7a(undefined param_1,undefined param_2,undefined param_3,undefined param_4,
                  undefined param_5,undefined param_6,undefined param_7,undefined param_8,
                  undefined param_9)

{
  int unaff_EBP;
  undefined4 *in_FS_OFFSET;
  undefined in_stack_00000000;
  undefined4 in_stack_0000002c;
  undefined4 in_stack_00000030;
  
  *(undefined4 *)(unaff_EBP + -4) = 1;
  FUN_00403268(param_1,param_2,param_3,in_stack_00000000,param_4,param_5,param_6,param_7,param_8,
               param_9,in_stack_0000002c);
  *in_FS_OFFSET = in_stack_00000030;
  FUN_0040626c(*(int *)(unaff_EBP + -8));
  return;
}

