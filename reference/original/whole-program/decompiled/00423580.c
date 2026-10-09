/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00423580.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_00423580(int *param_1)

{
  (**(code **)(*param_1 + -0x10))();
  if (((*(char *)((int)param_1 + 0x11a) == '\x01') && (*(int *)(DAT_0048a6f8 + 0x28) != 0)) &&
     (*(int *)(*(int *)(DAT_0048a6f8 + 0x28) + 0x134) != 0)) {
    SendMessageA(*(HWND *)(*(int *)(DAT_0048a6f8 + 0x28) + 0x134),0x234,0,0);
  }
  return;
}

