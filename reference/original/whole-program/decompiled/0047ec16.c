/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0047ec16.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_0047ec16(void)

{
  undefined uVar1;
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
  
  FUN_0040414d((undefined4 *)&DAT_0048c600,DAT_0048c5d4);
  FUN_004045a4((HANDLE *)&DAT_0048c600,(HANDLE)0x1);
  FUN_00402710();
  FUN_00404254((HANDLE *)&DAT_0048c600,original_maps,0x1881,(uint *)0x0);
  FUN_00402710();
  FUN_00404254((HANDLE *)&DAT_0048c600,&original_hero,0x2ac,(uint *)0x0);
  FUN_00402710();
  FUN_004042b8(&DAT_0048c600);
  FUN_00402710();
  tile_class_or_message = 0x86;
  uVar1 = FUN_0044cb34(*(int *)(unaff_EBP + -4));
  FUN_00403268(uVar1,extraout_DL,extraout_CL,in_stack_00000000,in_stack_00000004,in_stack_00000008,
               in_stack_0000000c,in_stack_00000010,in_stack_00000014,in_stack_00000018,
               in_stack_0000002c);
  return;
}

