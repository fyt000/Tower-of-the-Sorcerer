/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0041cf28.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0041cf28(int param_1,int *param_2)

{
  UINT nSize;
  LPBYTE lpData;
  undefined4 *in_FS_OFFSET;
  undefined4 uVar1;
  
  if (*(int *)(param_1 + 0x10) != 0) {
    nSize = GetEnhMetaFileBits(*(HENHMETAFILE *)(*(int *)(param_1 + 0x10) + 8),0,(LPBYTE)0x0);
    lpData = (LPBYTE)FUN_00402650(nSize);
    uVar1 = *in_FS_OFFSET;
    *in_FS_OFFSET = &stack0xffffffe0;
    GetEnhMetaFileBits(*(HENHMETAFILE *)(*(int *)(param_1 + 0x10) + 8),nSize,lpData);
    FUN_0040af88(param_2,lpData,nSize);
    *in_FS_OFFSET = uVar1;
    FUN_00402668((int)lpData);
    return;
  }
  return;
}

