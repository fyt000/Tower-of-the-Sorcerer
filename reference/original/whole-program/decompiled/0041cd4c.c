/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0041cd4c.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_0041cd4c(int param_1,int param_2)

{
  int iVar1;
  undefined4 extraout_ECX;
  undefined4 extraout_ECX_00;
  int iStack_18;
  int iStack_10;
  
  if (*(int *)(param_1 + 0x10) == 0) {
    FUN_0041c954(param_1);
  }
  iVar1 = *(int *)(param_1 + 0x10);
  if (*(short *)(iVar1 + 0x18) == 0) {
    if (*(HENHMETAFILE *)(iVar1 + 8) == (HENHMETAFILE)0x0) {
      *(int *)(iVar1 + 0x1c) = param_2;
    }
    else {
      GetEnhMetaFileHeader(*(HENHMETAFILE *)(iVar1 + 8),0x58,(LPENHMETAHEADER)&stack0xffffffa0);
      iVar1 = MulDiv(param_2,iStack_10 * 100,iStack_18);
      FUN_0041cd10(param_1,iVar1,extraout_ECX);
    }
  }
  else {
    iVar1 = MulDiv(param_2,0x6338,*(int *)(DAT_0048a6fc + 0x24));
    FUN_0041cd10(param_1,iVar1,extraout_ECX_00);
  }
  return;
}

