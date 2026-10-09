/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00420bee.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_00420bee(void)

{
  byte *pbVar1;
  int unaff_EBP;
  
  pbVar1 = (byte *)(*(int *)(unaff_EBP + -4) + 0x11d);
  *pbVar1 = *pbVar1 & 0xfe;
  return;
}

