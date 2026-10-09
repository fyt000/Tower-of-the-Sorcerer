/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x004033d8.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_004033d8(void)

{
  int iVar1;
  int unaff_EBP;
  int *in_FS_OFFSET;
  
  DAT_0048a48c = (int *)(unaff_EBP + -0xc);
  iVar1 = *in_FS_OFFSET;
  *in_FS_OFFSET = (int)DAT_0048a48c;
  *DAT_0048a48c = iVar1;
  *(undefined **)(unaff_EBP + -8) = &LAB_0040335c;
  *(int *)(unaff_EBP + -4) = unaff_EBP;
  return;
}

