/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0041b138.
 * Inferred types, shared tails and runtime effects require assembly review. */

undefined4 FUN_0041b138(int param_1)

{
  int iVar1;
  uint uVar2;
  LOGPALETTE *plpal;
  BYTE *pBVar3;
  undefined4 uVar4;
  int iVar5;
  undefined4 *in_FS_OFFSET;
  undefined4 uStack_2c;
  undefined *puStack_28;
  undefined *puStack_24;
  
  puStack_24 = (undefined *)0x41b155;
  iVar1 = FUN_0041adb0(*(short *)(param_1 + 10));
  if (iVar1 != 0) {
    uVar2 = (iVar1 + -1) * 4 + 8;
    puStack_24 = (undefined *)0x41b173;
    plpal = (LOGPALETTE *)FUN_00405950(uVar2);
    puStack_24 = (undefined *)0x41b185;
    FUN_004029b8((undefined4 *)plpal,uVar2,0);
    puStack_28 = &LAB_0041b1f3;
    uStack_2c = *in_FS_OFFSET;
    *in_FS_OFFSET = &uStack_2c;
    plpal->palNumEntries = (WORD)iVar1;
    plpal->palVersion = 0x300;
    if (-1 < iVar1 + -1) {
      iVar5 = 0;
      pBVar3 = (BYTE *)(param_1 + 0xe);
      do {
        plpal->palPalEntry[iVar5].peRed = *pBVar3;
        plpal->palPalEntry[iVar5].peGreen = pBVar3[-1];
        plpal->palPalEntry[iVar5].peBlue = pBVar3[-2];
        plpal->palPalEntry[iVar5].peFlags = '\0';
        iVar5 = iVar5 + 1;
        pBVar3 = pBVar3 + 3;
        iVar1 = iVar1 + -1;
      } while (iVar1 != 0);
    }
    puStack_24 = &stack0xfffffffc;
    CreatePalette(plpal);
    *in_FS_OFFSET = uStack_2c;
    puStack_24 = (undefined *)0x41b1fa;
    puStack_28 = (undefined *)0x41b1f2;
    uVar4 = FUN_00402668((int)plpal);
    return uVar4;
  }
  return 0;
}

