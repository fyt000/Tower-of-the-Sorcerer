/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00412730.
 * Inferred types, shared tails and runtime effects require assembly review. */

HWND FUN_00412730(POINT *param_1)

{
  HWND hWnd;
  undefined4 uVar1;
  
  hWnd = WindowFromPoint(*param_1);
  while ((hWnd != (HWND)0x0 && (uVar1 = FUN_0041270c(hWnd), (char)uVar1 == '\0'))) {
    hWnd = GetParent(hWnd);
  }
  return hWnd;
}

