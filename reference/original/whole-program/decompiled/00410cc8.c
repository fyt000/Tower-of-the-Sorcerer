/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00410cc8.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00410cc8(int *param_1)

{
  (**(code **)(*param_1 + 0x28))(param_1,0,0);
  if ((HWND)param_1[9] != (HWND)0x0) {
    SendMessageA((HWND)param_1[9],0xb015,0,0);
  }
  return;
}

