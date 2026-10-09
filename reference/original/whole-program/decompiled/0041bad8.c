/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0041bad8.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_0041bad8(void)

{
  int unaff_EBP;
  
  if (*(int *)(unaff_EBP + -8) != 0) {
    SelectPalette(*(HDC *)(unaff_EBP + -0x10),*(HPALETTE *)(unaff_EBP + -8),0);
  }
  ReleaseDC(*(HWND *)(unaff_EBP + -0xc),*(HDC *)(unaff_EBP + -0x10));
  return;
}

