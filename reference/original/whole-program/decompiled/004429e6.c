/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x004429e6.
 * Inferred types, shared tails and runtime effects require assembly review. */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void root_004429e6(void)

{
  int *piVar1;
  undefined uVar2;
  undefined extraout_CL;
  undefined4 extraout_ECX;
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
  
  (**(code **)(**(int **)(*(int *)(*(int *)(unaff_EBP + -4) + 0x444) + 0x118) + 0x38))();
  FUN_00406068((int *)(unaff_EBP + -8));
  FUN_0040352c((int *)&DAT_0048c5e0,*(undefined4 **)(unaff_EBP + -8));
  FUN_0040369c((int *)&DAT_0048c5dc,_DAT_0048c5e0,(undefined4 *)"\\savedat");
  DAT_0048c5ef = 0;
  piVar1 = *(int **)(*(int *)(*(int *)(unaff_EBP + -4) + 0x444) + 0x118);
  (**(code **)(*piVar1 + 0x2c))(piVar1,_DAT_0048c5dc);
  piVar1 = *(int **)(*(int *)(*(int *)(unaff_EBP + -4) + 0x444) + 0x118);
  (**(code **)(*piVar1 + 0x2c))(piVar1,_DAT_0048c5e0);
  FUN_004035fc((int *)(unaff_EBP + -8),&DAT_0048c5ef);
  piVar1 = *(int **)(*(int *)(*(int *)(unaff_EBP + -4) + 0x444) + 0x118);
  (**(code **)(*piVar1 + 0x2c))(piVar1,*(undefined4 *)(unaff_EBP + -8));
  piVar1 = *(int **)(*(int *)(*(int *)(unaff_EBP + -4) + 0x444) + 0x118);
  uVar2 = (**(code **)(*piVar1 + 0x5c))(piVar1,DAT_0048c5d4);
  FUN_00403268(uVar2,extraout_DL,extraout_CL,in_stack_00000000,in_stack_00000004,in_stack_00000008,
               in_stack_0000000c,in_stack_00000010,in_stack_00000014,in_stack_00000018,
               in_stack_0000002c);
  piVar1 = *(int **)(*(int *)(*(int *)(unaff_EBP + -4) + 0x444) + 0x118);
  (**(code **)(*piVar1 + 0xc))(piVar1,0,unaff_EBP + -8);
  FUN_0040369c((int *)&DAT_0048c5d4,*(undefined4 **)(unaff_EBP + -8),(undefined4 *)"\\option.dat");
  FUN_0040414d((undefined4 *)&DAT_0048c600,DAT_0048c5d4);
  FUN_0040458d((HANDLE *)&DAT_0048c600,(HANDLE)0x1);
  FUN_00402710();
  FUN_004041f0((HANDLE *)&DAT_0048c600,&DAT_00489b9c,10,(uint *)0x0);
  FUN_00402710();
  FUN_004042b8(&DAT_0048c600);
  FUN_00402710();
  FUN_00484f48(*(int **)(unaff_EBP + -4));
  if (*(char *)(*(int *)(*(int *)(unaff_EBP + -4) + 0x420) + 0x28) == '\x01') {
    FUN_0042c454(*(int *)(*(int *)(unaff_EBP + -4) + 0x41c),'\x01');
    FUN_0047d4a4(*(int *)(unaff_EBP + -4));
    DAT_0048c56c = 0;
    FUN_0042c454(*(int *)(*(int *)(unaff_EBP + -4) + 0x1b4),'\0');
  }
  else {
    FUN_0047d4a4(*(int *)(unaff_EBP + -4));
  }
  initialize_cycle();
  FUN_00454de8(*(int *)(unaff_EBP + -4),extraout_EDX,extraout_ECX);
  if (*(char *)(*(int *)(*(int *)(unaff_EBP + -4) + 0x420) + 0x28) == '\0') {
    FUN_00450880(*(int *)(unaff_EBP + -4));
  }
  *in_FS_OFFSET = in_stack_00000030;
  FUN_004034dc((int *)(unaff_EBP + -8));
  return;
}

