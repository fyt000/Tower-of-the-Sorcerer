/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0042438c.
 * Inferred types, shared tails and runtime effects require assembly review. */

undefined4 root_0042438c(void)

{
  HWND pHVar1;
  uint uVar2;
  undefined4 uVar3;
  HWND in_stack_00000004;
  HWND *in_stack_00000008;
  
  uVar3 = 1;
  pHVar1 = GetWindow(in_stack_00000004,4);
  if (pHVar1 == *(HWND *)(DAT_0048a6f8 + 0x20)) {
    uVar2 = GetWindowLongA(in_stack_00000004,-0x14);
    if (((uVar2 & 8) == 0) ||
       ((*(int **)(DAT_0048a6f8 + 0x28) != (int *)0x0 &&
        (pHVar1 = (HWND)FUN_00416cbc(*(int **)(DAT_0048a6f8 + 0x28)), in_stack_00000004 == pHVar1)))
       ) {
      *in_stack_00000008 = in_stack_00000004;
      uVar3 = 0;
    }
    else {
      FUN_004099a4(*(int **)(DAT_0048a6f8 + 0x70),in_stack_00000004);
    }
    return uVar3;
  }
  return 1;
}

