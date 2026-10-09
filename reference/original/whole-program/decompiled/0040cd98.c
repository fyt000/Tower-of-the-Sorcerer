/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0040cd98.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_0040cd98(undefined4 param_1,undefined4 param_2,uint param_3,undefined param_4,
                  undefined param_5,undefined param_6,undefined param_7,undefined param_8,
                  undefined param_9)

{
  undefined uVar1;
  undefined extraout_CL;
  undefined extraout_DL;
  int unaff_EBP;
  undefined4 *in_FS_OFFSET;
  undefined in_stack_00000000;
  undefined4 in_stack_0000002c;
  undefined4 in_stack_00000030;
  
  FUN_0040cea4(*(int *)(unaff_EBP + -4),param_2,param_3);
  uVar1 = root_00403214();
  FUN_00403268(uVar1,extraout_DL,extraout_CL,in_stack_00000000,param_4,param_5,param_6,param_7,
               param_8,param_9,in_stack_0000002c);
  *in_FS_OFFSET = in_stack_00000030;
  FUN_004034dc((int *)(unaff_EBP + -8));
  return;
}

