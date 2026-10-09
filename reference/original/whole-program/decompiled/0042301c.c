/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0042301c.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_0042301c(int param_1,int param_2)

{
  if (*(short *)(param_2 + 8) != 0) {
    SetFocus(*(HWND *)(param_2 + 4));
    return;
  }
  root_0041706c(param_1,*(undefined4 *)(param_1 + 0x10c),*(int *)(param_2 + 4) == 0,1);
  return;
}

