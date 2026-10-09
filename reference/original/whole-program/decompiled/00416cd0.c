/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00416cd0.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_00416cd0(int *param_1,LPPOINT param_2)

{
  HWND hWnd;
  
  param_2->x = 0;
  param_2->y = 0;
  hWnd = (HWND)FUN_00416cbc(param_1);
  ClientToScreen(hWnd,param_2);
  return;
}

