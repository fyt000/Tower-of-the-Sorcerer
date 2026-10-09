/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x004157ca.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_004157ca(void)

{
  HWND hWnd;
  int unaff_EBP;
  PAINTSTRUCT *lpPaint;
  
  if (*(int *)(*(int *)(unaff_EBP + -8) + 4) == 0) {
    lpPaint = (PAINTSTRUCT *)(unaff_EBP + -0x50);
    hWnd = (HWND)FUN_00416cbc(*(int **)(unaff_EBP + -4));
    EndPaint(hWnd,lpPaint);
  }
  return;
}

