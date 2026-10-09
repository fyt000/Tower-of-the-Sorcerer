/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0041b480.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0041b480(BITMAPINFOHEADER *param_1,HBITMAP *param_2,undefined4 param_3)

{
  int iVar1;
  HBITMAP pHVar2;
  undefined4 extraout_EDX;
  undefined4 extraout_EDX_00;
  undefined4 *in_FS_OFFSET;
  undefined4 uVar3;
  undefined4 uStack_34;
  undefined *puStack_30;
  int local_20;
  int local_1c;
  DWORD *local_18;
  HDC local_14;
  HBITMAP local_10;
  undefined4 local_c;
  BITMAPINFOHEADER *local_8;
  
  puStack_30 = (undefined *)0x41b497;
  local_c = param_3;
  local_8 = param_1;
  local_20 = GetSystemMetrics(0xb);
  puStack_30 = (undefined *)0x41b4a1;
  local_1c = GetSystemMetrics(0xc);
  local_8->biHeight = (uint)local_8->biHeight >> 1;
  iVar1 = FUN_0041b46c(local_8->biWidth * (uint)local_8->biBitCount);
  local_8->biSizeImage = iVar1 * local_8->biHeight;
  iVar1 = FUN_0041adb0(local_8->biBitCount);
  puStack_30 = (undefined *)0x41b4df;
  local_14 = GetDC((HWND)0x0);
  if (local_14 == (HDC)0x0) {
    FUN_0041ac5c(0,extraout_EDX);
  }
  puStack_30 = &LAB_0041b645;
  uStack_34 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_34;
  local_18 = &local_8[1].biSize + iVar1;
  local_10 = CreateDIBitmap(local_14,local_8,4,local_18,(BITMAPINFO *)local_8,0);
  if (local_10 == (HBITMAP)0x0) {
    FUN_0041ac5c(0,extraout_EDX_00);
  }
  uVar3 = *in_FS_OFFSET;
  *in_FS_OFFSET = &stack0xffffffc0;
  pHVar2 = FUN_0041ac74(local_10,&local_20,'\0');
  *param_2 = pHVar2;
  *in_FS_OFFSET = uVar3;
  DeleteObject(local_10);
  return;
}

