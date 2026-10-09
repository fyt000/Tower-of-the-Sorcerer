/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00403178.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_00403178(void)

{
  code *unaff_EBX;
  int unaff_ESI;
  int iVar1;
  int unaff_EDI;
  undefined4 *in_FS_OFFSET;
  undefined4 uStack_c;
  code *pcStack_8;
  
  pcStack_8 = root_004031a8;
  uStack_c = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_c;
  if ((unaff_ESI != 0) && (-1 < unaff_ESI)) {
    iVar1 = unaff_ESI + -1;
    do {
      uStack_c = *(undefined4 *)(unaff_EDI + iVar1 * 4);
      iVar1 = iVar1 + -1;
    } while (-1 < iVar1);
  }
  (*unaff_EBX)();
  *in_FS_OFFSET = *(undefined4 *)*in_FS_OFFSET;
  return;
}

