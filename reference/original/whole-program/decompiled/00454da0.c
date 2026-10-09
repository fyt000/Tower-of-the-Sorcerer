/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00454da0.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00454da0(int param_1)

{
  undefined4 extraout_ECX;
  int extraout_ECX_00;
  undefined4 extraout_EDX;
  undefined4 extraout_EDX_00;
  
  initialize_cycle();
  FUN_00454de8(param_1,extraout_EDX,extraout_ECX);
  FUN_00450880(param_1);
  if (*(char *)(*(int *)(param_1 + 0x1b4) + 0x20) == '\0') {
    FUN_0042c454(*(int *)(param_1 + 0x1b4),'\x01');
  }
  if (*(char *)(*(int *)(param_1 + 0x330) + 0x28) == '\x01') {
    FUN_0047c8f8();
    FUN_0047c2bc(param_1,extraout_EDX_00,extraout_ECX_00);
  }
  return;
}

