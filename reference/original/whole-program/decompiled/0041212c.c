/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0041212c.
 * Inferred types, shared tails and runtime effects require assembly review. */

undefined4 root_0041212c(void)

{
  HANDLE pvVar1;
  uint uVar2;
  LONG LVar3;
  undefined4 uVar4;
  HWND in_stack_00000004;
  
  *(HWND *)((int)DAT_0048927c + 0xc0) = in_stack_00000004;
  SetWindowLongA(in_stack_00000004,-4,*(LONG *)((int)DAT_0048927c + 0xa8));
  uVar2 = GetWindowLongA(in_stack_00000004,-0x10);
  if ((uVar2 & 0x40000000) != 0) {
    LVar3 = GetWindowLongA(in_stack_00000004,-0xc);
    if (LVar3 == 0) {
      SetWindowLongA(in_stack_00000004,-0xc,(LONG)in_stack_00000004);
    }
  }
  SetPropA(in_stack_00000004,(LPCSTR)(uint)DAT_0048a698,DAT_0048927c);
  SetPropA(in_stack_00000004,(LPCSTR)(uint)DAT_0048a696,DAT_0048927c);
  pvVar1 = DAT_0048927c;
  DAT_0048927c = (HANDLE)0x0;
  uVar4 = (**(code **)((int)pvVar1 + 0xa8))();
  return uVar4;
}

