/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0041c423.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_0041c423(void)

{
  int iVar1;
  undefined uVar2;
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
  
  FUN_00402c34(*(int **)(unaff_EBP + -8));
  uVar2 = root_00403214();
  FUN_00403268(uVar2,extraout_DL,extraout_CL,in_stack_00000000,in_stack_00000004,in_stack_00000008,
               in_stack_0000000c,in_stack_00000010,in_stack_00000014,in_stack_00000018,
               in_stack_0000002c);
  FUN_00402c34(*(int **)(unaff_EBX + 4));
  iVar1 = *(int *)(unaff_EBP + -8);
  *(int *)(unaff_EBX + 4) = iVar1;
  *(int *)(iVar1 + 8) = unaff_EBX;
  *(code **)(iVar1 + 4) = FUN_0041c378;
  FUN_0041c378(unaff_EBX);
  return;
}

