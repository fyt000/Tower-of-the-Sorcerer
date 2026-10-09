/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x004298a4.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_004298a4(int *param_1)

{
  HWND hWnd;
  LPCSTR lpString;
  
  (**(code **)(*param_1 + -0x10))();
  lpString = (LPCSTR)param_1[0x10];
  hWnd = (HWND)FUN_00416cbc(param_1);
  SetWindowTextA(hWnd,lpString);
  return;
}

