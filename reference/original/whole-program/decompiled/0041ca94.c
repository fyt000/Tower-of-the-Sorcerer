/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0041ca94.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0041ca94(int param_1,undefined4 *param_2,int param_3)

{
  int iVar1;
  ushort uVar2;
  undefined4 uVar3;
  undefined2 extraout_var;
  int iVar4;
  HENHMETAFILE pHVar5;
  undefined4 extraout_EDX;
  undefined4 extraout_EDX_00;
  undefined4 uVar6;
  undefined4 extraout_EDX_01;
  undefined4 *in_FS_OFFSET;
  undefined4 uStack_50;
  undefined *puStack_4c;
  undefined *puStack_48;
  METAFILEPICT local_38;
  int local_28;
  short local_22;
  short local_20;
  short local_1e;
  short local_1c;
  ushort local_1a;
  ushort local_14;
  BYTE *local_10;
  UINT local_c;
  undefined4 *local_8;
  
  puStack_48 = (undefined *)0x41caac;
  local_c = param_3;
  local_8 = param_2;
  FUN_0041c954(param_1);
  puStack_48 = (undefined *)0x41cabb;
  uVar3 = (**(code **)*local_8)(local_8,&local_28,0x16);
  uVar6 = extraout_EDX;
  if (local_28 == -0x65393229) {
    puStack_48 = (undefined *)0x41cacc;
    uVar2 = FUN_0041b910((ushort *)&local_28);
    uVar3 = CONCAT22(extraout_var,uVar2);
    uVar6 = extraout_EDX_00;
    if (uVar2 == local_14) goto LAB_0041cad7;
  }
  puStack_48 = (undefined *)0x41cad7;
  FUN_0041ac50(uVar3,uVar6);
LAB_0041cad7:
  local_c = local_c - 0x16;
  puStack_48 = (undefined *)0x41cae3;
  local_10 = (BYTE *)FUN_00402650(local_c);
  iVar1 = *(int *)(param_1 + 0x10);
  puStack_4c = &LAB_0041cbaa;
  uStack_50 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_50;
  puStack_48 = &stack0xfffffffc;
  (**(code **)*local_8)(local_8,local_10,local_c);
  *(ushort *)(*(int *)(param_1 + 0x10) + 0x18) = local_1a;
  if (local_1a == 0) {
    local_1a = 0x60;
  }
  iVar4 = MulDiv((int)local_1e - (int)local_22,0x6338,(uint)local_1a);
  *(int *)(iVar1 + 0xc) = iVar4;
  iVar4 = MulDiv((int)local_1c - (int)local_20,0x6338,(uint)local_1a);
  *(int *)(iVar1 + 0x10) = iVar4;
  local_38.mm = 8;
  local_38.xExt = 0;
  local_38.yExt = 0;
  local_38.hMF = (HMETAFILE)0x0;
  pHVar5 = SetWinMetaFileBits(local_c,local_10,(HDC)0x0,&local_38);
  *(HENHMETAFILE *)(iVar1 + 8) = pHVar5;
  if (pHVar5 == (HENHMETAFILE)0x0) {
    FUN_0041ac50(0,extraout_EDX_01);
  }
  *(undefined *)(param_1 + 0x14) = 0;
  *in_FS_OFFSET = uStack_50;
  puStack_48 = &LAB_0041cbb1;
  puStack_4c = (undefined *)0x41cba9;
  FUN_00402668((int)local_10);
  return;
}

