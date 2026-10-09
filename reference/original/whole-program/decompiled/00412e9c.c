/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00412e9c.
 * Inferred types, shared tails and runtime effects require assembly review. */

undefined root_00412e9c(int *param_1,undefined4 param_2,undefined4 param_3)

{
  HPALETTE pHVar1;
  HDC hdc;
  UINT UVar2;
  undefined uStack_13;
  HWND pHStack_10;
  
  uStack_13 = 0;
  pHVar1 = (HPALETTE)FUN_00402cdc(param_1,param_2,param_3);
  if (pHVar1 != (HPALETTE)0x0) {
    hdc = (HDC)(**(code **)(*param_1 + 0x30))(param_1,&pHStack_10);
    pHVar1 = SelectPalette(hdc,pHVar1,(byte)((byte)param_2 ^ 1) & 0x7f);
    UVar2 = RealizePalette(hdc);
    if (UVar2 != 0) {
      (**(code **)(*param_1 + 0x44))();
    }
    SelectPalette(hdc,pHVar1,1);
    RealizePalette(hdc);
    ReleaseDC(pHStack_10,hdc);
    uStack_13 = 1;
  }
  return uStack_13;
}

