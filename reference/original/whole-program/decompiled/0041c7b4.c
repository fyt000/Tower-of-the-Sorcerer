/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0041c7b4.
 * Inferred types, shared tails and runtime effects require assembly review. */

undefined4 FUN_0041c7b4(int param_1)

{
  int iVar1;
  HGDIOBJ ho;
  UINT nNumEntries;
  LOGPALETTE *plpal;
  HPALETTE pHVar2;
  undefined4 uVar3;
  undefined4 *in_FS_OFFSET;
  WORD local_10;
  
  uVar3 = 0;
  iVar1 = *(int *)(param_1 + 0x10);
  if ((iVar1 != 0) && (*(int *)(iVar1 + 8) != 0)) {
    if (*(int *)(iVar1 + 0x14) == 0) {
      nNumEntries = GetEnhMetaFilePaletteEntries(*(HENHMETAFILE *)(iVar1 + 8),0,(LPPALETTEENTRY)0x0)
      ;
      if (nNumEntries != 0) {
        ho = *(HGDIOBJ *)(*(int *)(param_1 + 0x10) + 0x14);
        if (ho != (HGDIOBJ)0x0) {
          DeleteObject(ho);
        }
        plpal = (LOGPALETTE *)FUN_00402650(nNumEntries * 4 + 8);
        uVar3 = *in_FS_OFFSET;
        *in_FS_OFFSET = &stack0xffffffe0;
        plpal->palVersion = 0x300;
        local_10 = (WORD)nNumEntries;
        plpal->palNumEntries = local_10;
        GetEnhMetaFilePaletteEntries
                  (*(HENHMETAFILE *)(*(int *)(param_1 + 0x10) + 8),nNumEntries,plpal->palPalEntry);
        pHVar2 = CreatePalette(plpal);
        *(HPALETTE *)(*(int *)(param_1 + 0x10) + 0x14) = pHVar2;
        *in_FS_OFFSET = uVar3;
        uVar3 = FUN_00402668((int)plpal);
        return uVar3;
      }
    }
    else {
      uVar3 = *(undefined4 *)(*(int *)(param_1 + 0x10) + 0x14);
    }
  }
  return uVar3;
}

