/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00428850.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00428850(int *param_1)

{
  HWND hWnd;
  LPCSTR lpString;
  
  lpString = "";
  hWnd = (HWND)FUN_00416cbc(param_1);
  SetWindowTextA(hWnd,lpString);
  return;
}

