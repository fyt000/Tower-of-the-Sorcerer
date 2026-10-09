/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0041d400.
 * Inferred types, shared tails and runtime effects require assembly review. */

BOOL FUN_0041d400(HGDIOBJ param_1,HPALETTE param_2,int param_3,char param_4,int param_5,int param_6)

{
  HBRUSH hbr;
  COLORREF CVar1;
  uint uVar2;
  BOOL BVar3;
  int iVar4;
  undefined4 extraout_EDX;
  undefined4 extraout_EDX_00;
  undefined4 uVar5;
  undefined4 extraout_EDX_01;
  undefined4 *in_FS_OFFSET;
  undefined4 uVar6;
  RECT local_34;
  HDC local_24;
  HDC local_20;
  HDC local_1c;
  HGDIOBJ local_18;
  HGDIOBJ local_14;
  HBITMAP local_10;
  HPALETTE local_c;
  HGDIOBJ local_8;
  
  local_10 = (HBITMAP)0x0;
  if ((param_1 == (HGDIOBJ)0x0) && ((param_3 == 0 || (param_6 == 0)))) {
    return 0;
  }
  local_c = param_2;
  local_8 = param_1;
  local_1c = GetDC((HWND)0x0);
  local_20 = CreateCompatibleDC(local_1c);
  uVar6 = *in_FS_OFFSET;
  *in_FS_OFFSET = &stack0xffffffb4;
  if (param_4 == '\0') {
    local_10 = CreateCompatibleBitmap(local_1c,param_3,param_6);
    uVar5 = extraout_EDX_00;
  }
  else {
    local_10 = CreateBitmap(param_3,param_6,1,1,(void *)0x0);
    uVar5 = extraout_EDX;
  }
  if (local_10 == (HBITMAP)0x0) {
    FUN_0041ac5c(0,uVar5);
  }
  local_18 = SelectObject(local_20,local_10);
  uVar5 = *in_FS_OFFSET;
  *in_FS_OFFSET = &stack0xffffffa8;
  if (param_5 == 0) {
    PatBlt(local_20,0,0,param_3,param_6,0xff0062);
  }
  else {
    hbr = (HBRUSH)FUN_0041a188(*(int *)(param_5 + 0x14));
    FUN_0040923c(0,0,param_3,&local_34.left,param_6);
    FillRect(local_20,&local_34,hbr);
    CVar1 = FUN_00419b00(*(uint *)(*(int *)(param_5 + 0xc) + 0x10));
    SetTextColor(local_20,CVar1);
    uVar2 = FUN_0041a14c(*(int *)(param_5 + 0x14));
    CVar1 = FUN_00419b00(uVar2);
    SetBkColor(local_20,CVar1);
  }
  if (local_8 != (HGDIOBJ)0x0) {
    local_24 = CreateCompatibleDC(local_1c);
    if (local_24 == (HDC)0x0) {
      FUN_0041ac5c(0,extraout_EDX_01);
    }
    uVar6 = *in_FS_OFFSET;
    *in_FS_OFFSET = &stack0xffffff9c;
    FUN_0041d22c((int)local_8);
    local_14 = SelectObject(local_24,local_8);
    if (local_c != (HPALETTE)0x0) {
      SelectPalette(local_24,local_c,1);
      RealizePalette(local_24);
      SelectPalette(local_20,local_c,1);
      RealizePalette(local_20);
    }
    if (param_5 != 0) {
      CVar1 = FUN_00419b00(*(uint *)(*(int *)(param_5 + 0xc) + 0x10));
      SetTextColor(local_24,CVar1);
      uVar2 = FUN_0041a14c(*(int *)(param_5 + 0x14));
      CVar1 = FUN_00419b00(uVar2);
      SetBkColor(local_24,CVar1);
    }
    BitBlt(local_20,0,0,param_3,param_6,local_24,0,0,0xcc0020);
    SelectObject(local_24,local_14);
    *in_FS_OFFSET = uVar6;
    BVar3 = DeleteDC(local_24);
    return BVar3;
  }
  *in_FS_OFFSET = uVar5;
  *in_FS_OFFSET = uVar6;
  DeleteDC(local_20);
  iVar4 = ReleaseDC((HWND)0x0,local_1c);
  return iVar4;
}

