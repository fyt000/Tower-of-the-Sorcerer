/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0041ba28.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0041ba28(HBITMAP param_1,HPALETTE param_2,LPBITMAPINFO param_3,int param_4,LPVOID param_5)

{
  HWND hWnd;
  HDC hdc;
  undefined4 *in_FS_OFFSET;
  undefined4 uVar1;
  HPALETTE local_c;
  
  FUN_0041b928(param_1,(undefined4 *)param_3,param_4);
  local_c = (HPALETTE)0x0;
  hWnd = GetFocus();
  hdc = GetDC(hWnd);
  uVar1 = *in_FS_OFFSET;
  *in_FS_OFFSET = &stack0xffffffd4;
  if (param_2 != (HPALETTE)0x0) {
    local_c = SelectPalette(hdc,param_2,0);
    RealizePalette(hdc);
  }
  GetDIBits(hdc,param_1,0,(param_3->bmiHeader).biHeight,param_5,param_3,0);
  *in_FS_OFFSET = uVar1;
  if (local_c != (HPALETTE)0x0) {
    SelectPalette(hdc,local_c,0);
  }
  ReleaseDC(hWnd,hdc);
  return;
}

