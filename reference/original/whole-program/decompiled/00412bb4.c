/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00412bb4.
 * Inferred types, shared tails and runtime effects require assembly review. */

HANDLE FUN_00412bb4(POINT *param_1)

{
  HWND hWnd;
  HANDLE pvVar1;
  
  hWnd = WindowFromPoint(*param_1);
  pvVar1 = (HANDLE)0x0;
  while ((hWnd != (HWND)0x0 && (pvVar1 = FUN_004121e4(hWnd), pvVar1 == (HANDLE)0x0))) {
    hWnd = GetParent(hWnd);
  }
  return pvVar1;
}

