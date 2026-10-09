/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0041d0e4.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_0041d0e4(int param_1)

{
  int iVar1;
  HENHMETAFILE pHVar2;
  undefined4 extraout_EDX;
  int iStack_44;
  int iStack_40;
  int iStack_3c;
  int iStack_38;
  
  pHVar2 = (HENHMETAFILE)GetClipboardData(0xe);
  if (pHVar2 == (HENHMETAFILE)0x0) {
    FUN_0041ac20(0xf021,extraout_EDX);
  }
  FUN_0041c954(param_1);
  iVar1 = *(int *)(param_1 + 0x10);
  pHVar2 = CopyEnhMetaFileA(pHVar2,(LPCSTR)0x0);
  *(HENHMETAFILE *)(iVar1 + 8) = pHVar2;
  GetEnhMetaFileHeader(*(HENHMETAFILE *)(iVar1 + 8),0x58,(LPENHMETAHEADER)&stack0xffffffa4);
  *(int *)(iVar1 + 0xc) = iStack_3c - iStack_44;
  *(int *)(iVar1 + 0x10) = iStack_38 - iStack_40;
  *(undefined2 *)(iVar1 + 0x18) = 0;
  *(undefined *)(param_1 + 0x14) = 1;
  FUN_0041bd8c(param_1);
  return;
}

