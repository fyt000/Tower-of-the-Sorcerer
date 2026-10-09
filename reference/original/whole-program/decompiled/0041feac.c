/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0041feac.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0041feac(HWND param_1)

{
  LONG LVar1;
  
  LVar1 = GetWindowLongA(param_1,-4);
  DestroyWindow(param_1);
  FUN_0041fde4(LVar1);
  return;
}

