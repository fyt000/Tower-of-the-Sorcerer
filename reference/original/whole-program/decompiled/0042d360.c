/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0042d360.
 * Inferred types, shared tails and runtime effects require assembly review. */

uint FUN_0042d360(int *param_1,LPCSTR param_2,undefined4 param_3)

{
  HWND hWnd;
  HDC hdc;
  uint uVar1;
  undefined4 local_14;
  
  uVar1 = 0xffffffff;
  local_14 = param_3;
  hWnd = (HWND)FUN_00416cbc(param_1);
  local_14 = CONCAT22(local_14._2_2_,0x8000);
  hdc = GetDC(hWnd);
  EnumFontFamiliesA(hdc,param_2,FUN_0042d348,(LPARAM)&local_14);
  ReleaseDC(hWnd,hdc);
  if ((short)local_14 != -0x8000) {
    uVar1 = local_14 & 0xff;
  }
  return uVar1;
}

