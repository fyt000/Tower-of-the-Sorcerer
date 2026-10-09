/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00423983.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00423983(void)

{
  byte *pbVar1;
  int unaff_EBP;
  
  FUN_00423d4c(DAT_0048a6fc,*(short *)(unaff_EBP + -0x16));
  FUN_0041f914(*(int **)(unaff_EBP + -0xc));
  *(undefined4 *)(DAT_0048a6fc + 0x4c) = *(undefined4 *)(unaff_EBP + -0x14);
  if (*(int *)(unaff_EBP + -0x1c) != 0) {
    SetActiveWindow(*(HWND *)(unaff_EBP + -0x1c));
  }
  DAT_00489588 = *(undefined4 *)(unaff_EBP + -0x10);
  pbVar1 = (byte *)(*(int *)(unaff_EBP + -4) + 0x11d);
  *pbVar1 = *pbVar1 & 0xf7;
  return;
}

