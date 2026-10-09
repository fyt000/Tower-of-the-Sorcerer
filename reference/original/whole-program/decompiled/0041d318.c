/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0041d318.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_0041d318(int *param_1)

{
  HDC hdc;
  HGDIOBJ pvVar1;
  HPALETTE pHVar2;
  
  if (param_1[0xd] != 0) {
    FUN_0041dbac(param_1[0xd]);
    FUN_0041d22c(*(int *)(*(int *)(param_1[0xd] + 0x10) + 0xc));
    hdc = CreateCompatibleDC((HDC)0x0);
    pvVar1 = *(HGDIOBJ *)(*(int *)(param_1[0xd] + 0x10) + 0xc);
    if (pvVar1 == (HGDIOBJ)0x0) {
      param_1[0xe] = 0;
    }
    else {
      pvVar1 = SelectObject(hdc,pvVar1);
      param_1[0xe] = (int)pvVar1;
    }
    pHVar2 = *(HPALETTE *)(*(int *)(param_1[0xd] + 0x10) + 0x10);
    if (pHVar2 == (HPALETTE)0x0) {
      param_1[0xf] = 0;
    }
    else {
      pHVar2 = SelectPalette(hdc,pHVar2,1);
      param_1[0xf] = (int)pHVar2;
      RealizePalette(hdc);
    }
    FUN_0041a9d0(param_1,(int)hdc);
    FUN_004099a4(DAT_00489570,param_1);
  }
  return;
}

