/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0041dc4a.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_0041dc4a(void)

{
  undefined uVar1;
  undefined extraout_CL;
  undefined extraout_DL;
  int unaff_EBX;
  int unaff_EBP;
  undefined in_stack_00000000;
  undefined in_stack_00000004;
  undefined in_stack_00000008;
  undefined in_stack_0000000c;
  undefined in_stack_00000010;
  undefined in_stack_00000014;
  undefined in_stack_00000018;
  undefined4 in_stack_0000002c;
  
  FUN_00402c34(*(int **)(unaff_EBP + -4));
  uVar1 = root_00403214();
  FUN_00403268(uVar1,extraout_DL,extraout_CL,in_stack_00000000,in_stack_00000004,in_stack_00000008,
               in_stack_0000000c,in_stack_00000010,in_stack_00000014,in_stack_00000018,
               in_stack_0000002c);
  *(undefined4 *)(unaff_EBX + 8) = *(undefined4 *)(unaff_EBP + -4);
  *(undefined4 *)(unaff_EBX + 0x1c) = *(undefined4 *)(unaff_EBP + -8);
  *(undefined4 *)(unaff_EBX + 0x20) = *(undefined4 *)(unaff_EBP + -0xc);
  if (**(int **)(unaff_EBX + 0x1c) == 0xc) {
    *(undefined *)(unaff_EBX + 0x25) = 2;
  }
  else if (**(int **)(unaff_EBX + 0x1c) == 0x28) {
    *(undefined *)(unaff_EBX + 0x25) = 1;
  }
  else {
    *(undefined *)(unaff_EBX + 0x25) = 0;
  }
  return;
}

