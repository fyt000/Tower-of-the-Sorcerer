/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x004222fc.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_004222fc(int *param_1)

{
  WPARAM wParam;
  LPARAM lParam;
  
  if ((*(byte *)((int)param_1 + 0x11d) & 0x10) == 0) {
    FUN_0041506c((int)param_1);
  }
  else {
    lParam = 0;
    wParam = FUN_00416cbc(param_1);
    SendMessageA(*(HWND *)(*(int *)(DAT_0048a6f8 + 0x28) + 0x134),0x221,wParam,lParam);
  }
  param_1[0x4d] = 0;
  return;
}

