/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00424b4c.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00424b4c(int param_1)

{
  BOOL BVar1;
  HWND hWnd;
  
  BVar1 = IsIconic(*(HWND *)(param_1 + 0x20));
  if (BVar1 != 0) {
    SetActiveWindow(*(HWND *)(param_1 + 0x20));
    FUN_00423fbc(*(HWND *)(param_1 + 0x20),9);
    FUN_00424484(param_1);
    if (*(int **)(DAT_0048a6fc + 0x3c) != (int *)0x0) {
      hWnd = (HWND)FUN_00416cbc(*(int **)(DAT_0048a6fc + 0x3c));
      SetFocus(hWnd);
    }
    if (*(short *)(param_1 + 0xd6) != 0) {
      (**(code **)(param_1 + 0xd4))(*(undefined4 *)(param_1 + 0xd8),param_1);
    }
  }
  return;
}

