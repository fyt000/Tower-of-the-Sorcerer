/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0040beb5.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_0040beb5(void)

{
  undefined4 uVar1;
  char cVar2;
  undefined extraout_CL;
  undefined uVar3;
  undefined extraout_DL;
  undefined extraout_DL_00;
  undefined uVar4;
  int unaff_EBP;
  undefined in_stack_00000000;
  undefined in_stack_00000004;
  undefined in_stack_00000008;
  undefined in_stack_0000000c;
  undefined in_stack_00000010;
  undefined in_stack_00000014;
  undefined in_stack_00000018;
  undefined4 in_stack_0000002c;
  
  uVar1 = *(undefined4 *)(unaff_EBP + 8);
  cVar2 = root_0040be00(*(int *)(unaff_EBP + 8) + -0x10);
  uVar3 = (undefined)uVar1;
  uVar4 = extraout_DL;
  if (cVar2 == '\0') {
    cVar2 = root_00403214();
    uVar4 = extraout_DL_00;
    uVar3 = extraout_CL;
  }
  FUN_00403268(cVar2,uVar4,uVar3,in_stack_00000000,in_stack_00000004,in_stack_00000008,
               in_stack_0000000c,in_stack_00000010,in_stack_00000014,in_stack_00000018,
               in_stack_0000002c);
  return;
}

