/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00420dfe.
 * Inferred types, shared tails and runtime effects require assembly review. */

undefined4 root_00420dfe(void)

{
  undefined uVar1;
  bool bVar2;
  undefined extraout_CL;
  undefined extraout_DL;
  int unaff_EBP;
  undefined in_stack_00000000;
  undefined in_stack_00000004;
  undefined in_stack_00000008;
  undefined in_stack_0000000c;
  undefined in_stack_00000010;
  undefined in_stack_00000014;
  undefined in_stack_00000018;
  undefined4 in_stack_0000002c;
  
  uVar1 = root_00425020(DAT_0048a6f8,*(undefined4 *)(unaff_EBP + -4));
  FUN_00403268(uVar1,extraout_DL,extraout_CL,in_stack_00000000,in_stack_00000004,in_stack_00000008,
               in_stack_0000000c,in_stack_00000010,in_stack_00000014,in_stack_00000018,
               in_stack_0000002c);
  FUN_004227b8(*(int **)(unaff_EBP + -4),'\0');
  bVar2 = FUN_00416e54(*(int *)(unaff_EBP + -4));
  if (bVar2) {
    (**(code **)(**(int **)(unaff_EBP + -4) + 0x68))();
  }
  FUN_00423c0c(DAT_0048a6fc,*(int *)(unaff_EBP + -4));
  FUN_00402c34(*(int **)(*(int *)(unaff_EBP + -4) + 0x120));
  FUN_00402c34(*(int **)(*(int *)(unaff_EBP + -4) + 0x124));
  FUN_00402c34(*(int **)(*(int *)(unaff_EBP + -4) + 0x128));
  FUN_0042063c(*(int ***)(unaff_EBP + -4),'\0');
  FUN_00402c34(*(int **)(*(int *)(unaff_EBP + -4) + 0x144));
  if (*(char *)(unaff_EBP + -5) != '\0') {
    FUN_00402e48(*(int **)(unaff_EBP + -4));
  }
  return *(undefined4 *)(unaff_EBP + -4);
}

