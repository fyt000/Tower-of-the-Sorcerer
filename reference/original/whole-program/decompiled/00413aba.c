/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00413aba.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_00413aba(void)

{
  HWND hWnd;
  int unaff_EBP;
  HDC hDC;
  
  hDC = *(HDC *)(unaff_EBP + -8);
  hWnd = (HWND)FUN_00416cbc(*(int **)(*(int *)(unaff_EBP + -4) + 0x20));
  ReleaseDC(hWnd,hDC);
  return;
}

