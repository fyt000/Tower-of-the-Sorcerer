/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0041d66c.
 * Inferred types, shared tails and runtime effects require assembly review. */

undefined4 FUN_0041d66c(HPALETTE param_1)

{
  int iVar1;
  LOGPALETTE *plpal;
  undefined4 uVar2;
  undefined4 *in_FS_OFFSET;
  UINT local_c;
  HPALETTE local_8;
  
  local_8 = (HPALETTE)0x0;
  if (param_1 != (HPALETTE)0x0) {
    local_c = 0;
    iVar1 = GetObjectA(param_1,4,&local_c);
    if ((iVar1 != 0) && (local_c != 0)) {
      plpal = (LOGPALETTE *)FUN_00402650((local_c - 1) * 4 + 8);
      uVar2 = *in_FS_OFFSET;
      *in_FS_OFFSET = &stack0xffffffdc;
      plpal->palVersion = 0x300;
      plpal->palNumEntries = (WORD)local_c;
      GetPaletteEntries(param_1,0,local_c,plpal->palPalEntry);
      local_8 = CreatePalette(plpal);
      *in_FS_OFFSET = uVar2;
      uVar2 = FUN_00402668((int)plpal);
      return uVar2;
    }
  }
  return local_8;
}

