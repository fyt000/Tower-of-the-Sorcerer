/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00419c90.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00419c90(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  HFONT pHVar3;
  undefined4 *in_FS_OFFSET;
  undefined4 uStack_5c;
  undefined *puStack_58;
  undefined *puStack_54;
  undefined *local_44;
  LOGFONTA local_40;
  
  puStack_54 = &stack0xfffffffc;
  local_44 = (undefined *)0x0;
  puStack_58 = &LAB_00419d70;
  uStack_5c = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_5c;
  iVar1 = *(int *)(param_1 + 0xc);
  if (*(int *)(iVar1 + 8) == 0) {
    local_40.lfHeight = *(LONG *)(iVar1 + 0x14);
    local_40.lfWidth = 0;
    local_40.lfEscapement = 0;
    local_40.lfOrientation = 0;
    if ((*(byte *)(iVar1 + 0x19) & 1) == 0) {
      local_40.lfWeight = 400;
    }
    else {
      local_40.lfWeight = 700;
    }
    local_40.lfItalic = (*(byte *)(iVar1 + 0x19) & 2) != 0;
    local_40.lfUnderline = (*(byte *)(iVar1 + 0x19) & 4) != 0;
    local_40.lfStrikeOut = (*(byte *)(iVar1 + 0x19) & 8) != 0;
    local_40.lfCharSet = '\x01';
    FUN_004035fc((int *)&local_44,(byte *)(iVar1 + 0x1a));
    FUN_0040619c((undefined4 *)local_40.lfFaceName,local_44);
    local_40.lfQuality = '\0';
    local_40.lfOutPrecision = '\0';
    local_40.lfClipPrecision = '\0';
    uVar2 = FUN_00419ea4(param_1);
    if ((char)uVar2 == '\x01') {
      local_40.lfPitchAndFamily = '\x02';
    }
    else if ((char)uVar2 == '\x02') {
      local_40.lfPitchAndFamily = '\x01';
    }
    else {
      local_40.lfPitchAndFamily = '\0';
    }
    pHVar3 = CreateFontIndirectA(&local_40);
    *(HFONT *)(iVar1 + 8) = pHVar3;
  }
  *in_FS_OFFSET = uStack_5c;
  puStack_54 = &LAB_00419d77;
  puStack_58 = (undefined *)0x419d6f;
  FUN_004034dc((int *)&local_44);
  return;
}

