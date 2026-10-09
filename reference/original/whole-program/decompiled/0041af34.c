/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0041af34.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0041af34(undefined4 *param_1,HBITMAP *param_2,HPALETTE *param_3,uint param_4,DWORD param_5)

{
  uint uVar1;
  BITMAPINFOHEADER *pBVar2;
  HPALETTE pHVar3;
  HBITMAP pHVar4;
  int iVar5;
  undefined4 extraout_EDX;
  undefined4 extraout_EDX_00;
  DWORD *pDVar6;
  BITMAPINFOHEADER *pBVar7;
  undefined4 *in_FS_OFFSET;
  byte bVar8;
  undefined4 uVar9;
  undefined4 uStack_7c;
  undefined *puStack_78;
  undefined4 uStack_70;
  undefined *puStack_6c;
  undefined *puStack_68;
  undefined4 uStack_64;
  undefined *puStack_60;
  undefined *puStack_5c;
  DWORD local_4c;
  undefined auStack_48 [8];
  short local_40;
  short local_3e;
  int local_2c;
  HPALETTE local_24;
  BITMAPINFOHEADER *local_20;
  undefined4 *local_1c;
  HDC local_18;
  HWND local_14;
  ushort local_e;
  HPALETTE *local_c;
  HBITMAP *local_8;
  
  bVar8 = 0;
  puStack_5c = (undefined *)0x41af56;
  local_c = param_3;
  local_8 = param_2;
  (**(code **)*param_1)(param_1,auStack_48,0x24);
  local_4c = param_5;
  if (local_40 != 1) {
    puStack_5c = (undefined *)0x41af68;
    FUN_0041ac38(param_5,extraout_EDX);
  }
  if (local_2c == 0) {
    puStack_5c = (undefined *)0x41af77;
    local_2c = FUN_0041adb0(local_3e);
  }
  local_e = (short)local_2c << 2;
  puStack_5c = (undefined *)0x41af91;
  pBVar2 = (BITMAPINFOHEADER *)FUN_00405950(local_e + 0x28);
  local_20 = pBVar2;
  puStack_60 = &LAB_0041b128;
  uStack_64 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_64;
  pDVar6 = &local_4c;
  pBVar7 = pBVar2;
  for (iVar5 = 10; iVar5 != 0; iVar5 = iVar5 + -1) {
    pBVar7->biSize = *pDVar6;
    pDVar6 = pDVar6 + (uint)bVar8 * -2 + 1;
    pBVar7 = (BITMAPINFOHEADER *)((int)pBVar7 + (uint)bVar8 * -8 + 4);
  }
  puStack_68 = (undefined *)0x41afc0;
  puStack_5c = &stack0xfffffffc;
  (**(code **)*param_1)(param_1,pBVar2 + 1,local_e);
  puStack_68 = (undefined *)0x41afc8;
  pHVar3 = (HPALETTE)FUN_0041add0((int)local_20);
  *local_c = pHVar3;
  param_4 = param_4 - (local_e + 0x28);
  uVar1 = pBVar2->biSizeImage;
  if ((uVar1 != 0) && ((int)uVar1 < (int)param_4)) {
    param_4 = uVar1;
  }
  puStack_68 = (undefined *)0x41aff0;
  local_1c = FUN_00405950(param_4);
  puStack_6c = &LAB_0041b104;
  uStack_70 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_70;
  puStack_68 = &stack0xfffffffc;
  (**(code **)*param_1)(param_1,local_1c,param_4);
  local_14 = GetFocus();
  puStack_78 = (undefined *)0x41b01e;
  local_18 = GetDC(local_14);
  if (local_18 == (HDC)0x0) {
    FUN_0041ac5c(0,extraout_EDX_00);
  }
  puStack_78 = &LAB_0041b0e4;
  uStack_7c = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_7c;
  if (*local_c == (HPALETTE)0x0) {
    local_24 = (HPALETTE)0x0;
  }
  else {
    local_24 = SelectPalette(local_18,*local_c,0);
    RealizePalette(local_18);
  }
  uVar9 = *in_FS_OFFSET;
  *in_FS_OFFSET = &stack0xffffff78;
  pHVar4 = CreateDIBitmap(local_18,local_20,4,local_1c,(BITMAPINFO *)local_20,0);
  *local_8 = pHVar4;
  if (*local_8 == (HBITMAP)0x0) {
    FUN_0041ac5c(local_8,local_8);
  }
  *in_FS_OFFSET = uVar9;
  if (local_24 != (HPALETTE)0x0) {
    SelectPalette(local_18,local_24,0);
  }
  return;
}

