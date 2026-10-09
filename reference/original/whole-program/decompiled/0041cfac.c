/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0041cfac.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0041cfac(int param_1,int *param_2)

{
  int iVar1;
  UINT UVar2;
  undefined4 extraout_EDX;
  undefined4 *in_FS_OFFSET;
  undefined4 uVar3;
  undefined4 uStack_3c;
  undefined *puStack_38;
  undefined4 local_28;
  undefined2 local_22;
  undefined2 local_20;
  undefined2 local_1e;
  undefined2 local_1c;
  short local_1a;
  ushort local_14;
  HDC local_10;
  UINT local_c;
  LPBYTE local_8;
  
  if (*(int *)(param_1 + 0x10) == 0) {
    return;
  }
  FUN_004029b8(&local_28,0x16,0);
  iVar1 = *(int *)(param_1 + 0x10);
  local_28 = 0x9ac6cdd7;
  local_1a = *(short *)(iVar1 + 0x18);
  if (local_1a == 0) {
    local_1a = 0x9ec;
  }
  local_22 = 0;
  local_20 = 0;
  local_1e = *(undefined2 *)(iVar1 + 0xc);
  local_1c = *(undefined2 *)(iVar1 + 0x10);
  local_14 = FUN_0041b910((ushort *)&local_28);
  puStack_38 = (undefined *)0x41d01f;
  local_10 = GetDC((HWND)0x0);
  puStack_38 = &LAB_0041d0d5;
  uStack_3c = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_3c;
  local_c = GetWinMetaFileBits(*(HENHMETAFILE *)(iVar1 + 8),0,(LPBYTE)0x0,8,local_10);
  local_8 = (LPBYTE)FUN_00402650(local_c);
  uVar3 = *in_FS_OFFSET;
  *in_FS_OFFSET = &stack0xffffffb8;
  UVar2 = GetWinMetaFileBits(*(HENHMETAFILE *)(iVar1 + 8),local_c,local_8,8,local_10);
  if ((int)UVar2 < (int)local_c) {
    FUN_0041ac5c(UVar2,extraout_EDX);
  }
  FUN_0040af88(param_2,&local_28,0x16);
  FUN_0040af88(param_2,local_8,local_c);
  *in_FS_OFFSET = uVar3;
  FUN_00402668((int)local_8);
  return;
}

