/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0047ea47.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_0047ea47(void)

{
  undefined uVar1;
  undefined extraout_CL;
  int extraout_ECX;
  undefined extraout_DL;
  undefined4 extraout_EDX;
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
  
  tile_class_or_message = 0x73;
  uVar1 = FUN_0044cb34(*(int *)(unaff_EBP + -4));
  FUN_00403268(uVar1,extraout_DL,extraout_CL,in_stack_00000000,in_stack_00000004,in_stack_00000008,
               in_stack_0000000c,in_stack_00000010,in_stack_00000014,in_stack_00000018,
               in_stack_0000002c);
  if (*(char *)(*(int *)(*(int *)(unaff_EBP + -4) + 0x330) + 0x28) == '\x01') {
    FUN_0047c8f8();
    FUN_0047c2bc(*(int *)(unaff_EBP + -4),extraout_EDX,extraout_ECX);
  }
  *in_FS_OFFSET = in_stack_00000030;
  FUN_004034dc((int *)(unaff_EBP + -8));
  return;
}

