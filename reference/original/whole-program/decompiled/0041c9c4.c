/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0041c9c4.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0041c9c4(int param_1,undefined4 *param_2)

{
  int iVar1;
  undefined4 uVar2;
  HENHMETAFILE pHVar3;
  undefined4 extraout_EDX;
  undefined4 extraout_EDX_00;
  undefined4 *in_FS_OFFSET;
  undefined4 uStack_78;
  undefined *puStack_74;
  undefined *puStack_70;
  undefined4 local_60 [6];
  int local_48;
  int local_44;
  int local_40;
  int local_3c;
  int local_38;
  UINT local_30;
  undefined4 *local_8;
  
  puStack_70 = (undefined *)0x41c9d8;
  FUN_0041c954(param_1);
  puStack_70 = (undefined *)0x41c9e7;
  uVar2 = FUN_0040af50(param_2,local_60,0x58);
  if (local_38 != 0x464d4520) {
    puStack_70 = (undefined *)0x41c9f5;
    FUN_0041ac50(uVar2,extraout_EDX);
  }
  puStack_70 = (undefined *)0x41c9fd;
  local_8 = (undefined4 *)FUN_00402650(local_30);
  iVar1 = *(int *)(param_1 + 0x10);
  puStack_74 = &LAB_0041ca84;
  uStack_78 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_78;
  puStack_70 = &stack0xfffffffc;
  FUN_00402870(local_60,local_8,0x58);
  FUN_0040af50(param_2,local_8 + 0x16,local_30 - 0x58);
  pHVar3 = SetEnhMetaFileBits(local_30,(BYTE *)local_8);
  *(HENHMETAFILE *)(iVar1 + 8) = pHVar3;
  if (pHVar3 == (HENHMETAFILE)0x0) {
    FUN_0041ac50(0,extraout_EDX_00);
  }
  *(undefined2 *)(iVar1 + 0x18) = 0;
  *(int *)(iVar1 + 0xc) = local_40 - local_48;
  *(int *)(iVar1 + 0x10) = local_3c - local_44;
  *(undefined *)(param_1 + 0x14) = 1;
  *in_FS_OFFSET = uStack_78;
  puStack_70 = &LAB_0041ca8b;
  puStack_74 = (undefined *)0x41ca83;
  FUN_00402668((int)local_8);
  return;
}

