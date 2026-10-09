/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0040c0e0.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_0040c0e0(void)

{
  char cVar1;
  undefined uVar2;
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
  
  cVar1 = root_0040bde0();
  if (cVar1 != '\0') {
    FUN_00402c34(*(int **)(unaff_EBP + -0x10));
  }
  uVar2 = root_00403214();
  FUN_00403268(uVar2,extraout_DL,extraout_CL,in_stack_00000000,in_stack_00000004,in_stack_00000008,
               in_stack_0000000c,in_stack_00000010,in_stack_00000014,in_stack_00000018,
               in_stack_0000002c);
  *in_FS_OFFSET = in_stack_00000030;
  FUN_004034fc((int *)(unaff_EBP + -0x18),2);
  return;
}

