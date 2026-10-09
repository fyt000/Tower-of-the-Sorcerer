/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00422696.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_00422696(void)

{
  int unaff_EBP;
  
  *(byte *)(*(int *)(unaff_EBP + -4) + 0x36) =
       ~DAT_004226ac & *(byte *)(*(int *)(unaff_EBP + -4) + 0x36);
  return;
}

