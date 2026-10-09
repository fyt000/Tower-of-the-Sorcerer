/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0041f8d1.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_0041f8d1(void)

{
  undefined uVar1;
  undefined extraout_CL;
  undefined extraout_DL;
  int unaff_EBP;
  undefined4 *in_FS_OFFSET;
  undefined in_stack_00000000;
  undefined in_stack_00000004;
  undefined in_stack_00000008;
  undefined in_stack_0000000c;
  undefined in_stack_00000010;
  undefined in_stack_00000014;
  undefined in_stack_00000018;
  undefined4 in_stack_0000002c;
  undefined4 in_stack_00000030;
  
  FUN_0041f914(DAT_00489598);
  uVar1 = root_00403214();
  FUN_00403268(uVar1,extraout_DL,extraout_CL,in_stack_00000000,in_stack_00000004,in_stack_00000008,
               in_stack_0000000c,in_stack_00000010,in_stack_00000014,in_stack_00000018,
               in_stack_0000002c);
  *in_FS_OFFSET = in_stack_00000030;
  DAT_00489598 = (int *)*(undefined4 *)(unaff_EBP + -0xc);
  DAT_0048958c = *(undefined4 *)(unaff_EBP + -8);
  return;
}

