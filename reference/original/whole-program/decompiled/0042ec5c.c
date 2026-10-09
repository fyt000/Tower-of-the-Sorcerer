/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0042ec5c.
 * Inferred types, shared tails and runtime effects require assembly review. */

undefined4 root_0042ec5c(void)

{
  undefined4 uVar1;
  undefined4 *in_FS_OFFSET;
  int **in_stack_00000004;
  undefined4 in_stack_00000008;
  undefined4 in_stack_0000000c;
  undefined4 *in_stack_00000010;
  undefined4 uStack_1c;
  code *pcStack_18;
  undefined *puStack_14;
  
  puStack_14 = &stack0xfffffffc;
  pcStack_18 = thunk_FUN_00402f4c;
  uStack_1c = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_1c;
  *in_stack_00000010 = 0;
  if (*in_stack_00000004 != (int *)0x0) {
    uVar1 = (**(code **)(**in_stack_00000004 + 4))
                      (*in_stack_00000004,in_stack_00000004[1],in_stack_00000008,in_stack_0000000c);
    *in_stack_00000010 = uVar1;
  }
  *in_FS_OFFSET = uStack_1c;
  return 0;
}

