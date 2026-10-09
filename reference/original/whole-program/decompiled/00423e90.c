/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00423e90.
 * Inferred types, shared tails and runtime effects require assembly review. */

LRESULT root_00423e90(void)

{
  LRESULT LVar1;
  int in_stack_00000004;
  WPARAM in_stack_00000008;
  LPARAM in_stack_0000000c;
  
  LVar1 = CallNextHookEx(DAT_0048a724,in_stack_00000004,in_stack_00000008,in_stack_0000000c);
  if ((-1 < in_stack_00000004) && (DAT_0048a6f8 != 0)) {
    FUN_00424d3c(DAT_0048a6f8,in_stack_0000000c);
  }
  return LVar1;
}

