/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00416cf0.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00416cf0(int *param_1,LPRECT param_2)

{
  HWND hWnd;
  
  hWnd = (HWND)FUN_00416cbc(param_1);
  GetClientRect(hWnd,param_2);
  return;
}

