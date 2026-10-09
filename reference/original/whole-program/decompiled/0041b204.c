/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0041b204.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0041b204(undefined4 *param_1,HBITMAP *param_2,HPALETTE *param_3,undefined4 param_4,
                 DWORD param_5)

{
  int iVar1;
  BITMAPINFO *pbmih;
  HPALETTE pHVar2;
  HBITMAP pHVar3;
  undefined4 extraout_EDX;
  int iVar4;
  undefined4 extraout_EDX_00;
  uint uVar5;
  undefined4 *in_FS_OFFSET;
  undefined4 uVar6;
  undefined4 uStack_64;
  undefined *puStack_60;
  undefined4 uStack_58;
  undefined *puStack_54;
  undefined *puStack_50;
  undefined4 uStack_4c;
  undefined *puStack_48;
  undefined *puStack_44;
  LONG local_30;
  undefined4 local_2c;
  uint local_28;
  HPALETTE local_24;
  BITMAPINFO *local_20;
  undefined4 *local_1c;
  HDC local_18;
  HWND local_14;
  ushort local_e;
  HPALETTE *local_c;
  HBITMAP *local_8;
  
  puStack_44 = (undefined *)0x41b226;
  local_c = param_3;
  local_8 = param_2;
  (**(code **)*param_1)(param_1,&local_30,8);
  if ((short)local_2c != 1) {
    puStack_44 = (undefined *)0x41b238;
    FUN_0041ac38(param_5,extraout_EDX);
  }
  puStack_44 = (undefined *)0x41b241;
  iVar1 = FUN_0041adb0(local_2c._2_2_);
  local_e = (short)iVar1 * 3;
  uVar5 = (uint)local_e;
  puStack_44 = (undefined *)0x41b256;
  pbmih = (BITMAPINFO *)FUN_00405950(uVar5 + 0xf);
  puStack_48 = &LAB_0041b3f5;
  uStack_4c = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_4c;
  (pbmih->bmiHeader).biSize = param_5;
  (pbmih->bmiHeader).biWidth = local_30;
  (pbmih->bmiHeader).biHeight = local_2c;
  puStack_50 = (undefined *)0x41b286;
  puStack_44 = &stack0xfffffffc;
  local_20 = pbmih;
  (**(code **)*param_1)(param_1,&(pbmih->bmiHeader).biPlanes,uVar5);
  puStack_50 = (undefined *)0x41b28e;
  pHVar2 = (HPALETTE)FUN_0041b138((int)local_20);
  *local_c = pHVar2;
  iVar1 = (uint)*(ushort *)&(pbmih->bmiHeader).biWidth *
          (uint)*(ushort *)((int)&(pbmih->bmiHeader).biHeight + 2);
  iVar4 = iVar1 + 0x1f;
  if (iVar4 < 0) {
    iVar4 = iVar1 + 0x3e;
  }
  local_28 = (iVar4 >> 5) * 4 * (uint)*(ushort *)((int)&(pbmih->bmiHeader).biWidth + 2);
  puStack_50 = (undefined *)0x41b2c2;
  local_1c = FUN_00405950(local_28);
  puStack_54 = &LAB_0041b3d1;
  uStack_58 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_58;
  puStack_50 = &stack0xfffffffc;
  (**(code **)*param_1)(param_1,local_1c,local_28);
  local_14 = GetFocus();
  puStack_60 = (undefined *)0x41b2f0;
  local_18 = GetDC(local_14);
  if (local_18 == (HDC)0x0) {
    FUN_0041ac5c(0,extraout_EDX_00);
  }
  puStack_60 = &LAB_0041b3b1;
  uStack_64 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_64;
  local_24 = (HPALETTE)0x0;
  if (*local_c != (HPALETTE)0x0) {
    local_24 = SelectPalette(local_18,*local_c,0);
    RealizePalette(local_18);
  }
  uVar6 = *in_FS_OFFSET;
  *in_FS_OFFSET = &stack0xffffff90;
  pHVar3 = CreateDIBitmap(local_18,(BITMAPINFOHEADER *)pbmih,4,local_1c,local_20,0);
  *local_8 = pHVar3;
  if (*local_8 == (HBITMAP)0x0) {
    FUN_0041ac5c(local_8,local_8);
  }
  *in_FS_OFFSET = uVar6;
  if (local_24 != (HPALETTE)0x0) {
    SelectPalette(local_18,local_24,0);
  }
  return;
}

