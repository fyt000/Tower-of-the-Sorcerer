/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00424f61.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_00424f61(void)

{
  undefined uVar1;
  int *piVar2;
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
  
  **(undefined4 **)(unaff_EBP + -4) = 0;
  FUN_00402c34(*(int **)(unaff_EBP + -8));
  uVar1 = root_00403214();
  FUN_00403268(uVar1,extraout_DL,extraout_CL,in_stack_00000000,in_stack_00000004,in_stack_00000008,
               in_stack_0000000c,in_stack_00000010,in_stack_00000014,in_stack_00000018,
               in_stack_0000002c);
  if (*(int *)(unaff_EBX + 0x28) == 0) {
    piVar2 = FUN_00402c7c(*(int ***)(unaff_EBP + -8),(int *)&PTR_FUN_0041edfc);
    if ((char)piVar2 != '\0') {
      piVar2 = *(int **)(unaff_EBP + -8);
      FUN_00416c98(piVar2);
      *(int **)(unaff_EBX + 0x28) = piVar2;
    }
  }
  return;
}

