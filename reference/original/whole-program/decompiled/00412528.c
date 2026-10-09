/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00412528.
 * Inferred types, shared tails and runtime effects require assembly review. */

HWND FUN_00412528(void)

{
  undefined4 in_EAX;
  HWND hWnd;
  undefined in_CL;
  undefined in_DL;
  
  hWnd = FUN_0041fe08((char)in_EAX,in_DL,in_CL,root_0041257c,in_EAX);
  SetCapture(hWnd);
  return hWnd;
}

