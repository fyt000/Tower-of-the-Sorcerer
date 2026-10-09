/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0041c8a4.
 * Inferred types, shared tails and runtime effects require assembly review. */

int root_0041c8a4(int param_1)

{
  int iVar1;
  int iStack_14;
  int iStack_c;
  
  if (*(int *)(param_1 + 0x10) == 0) {
    FUN_0041c954(param_1);
  }
  iVar1 = *(int *)(param_1 + 0x10);
  if (*(short *)(iVar1 + 0x18) == 0) {
    if (*(HENHMETAFILE *)(iVar1 + 8) == (HENHMETAFILE)0x0) {
      iVar1 = *(int *)(iVar1 + 0x1c);
    }
    else {
      GetEnhMetaFileHeader(*(HENHMETAFILE *)(iVar1 + 8),0x58,(LPENHMETAHEADER)&stack0xffffffa4);
      iVar1 = MulDiv(*(int *)(iVar1 + 0xc),iStack_14,iStack_c * 100);
    }
  }
  else {
    iVar1 = MulDiv(*(int *)(iVar1 + 0xc),*(int *)(DAT_0048a6fc + 0x24),0x6338);
  }
  return iVar1;
}

