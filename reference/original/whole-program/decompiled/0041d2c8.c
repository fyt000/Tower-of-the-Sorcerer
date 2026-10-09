/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0041d2c8.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0041d2c8(int *param_1)

{
  HDC hdc;
  
  if ((HDC)param_1[1] != (HDC)0x0) {
    if ((HGDIOBJ)param_1[0xe] != (HGDIOBJ)0x0) {
      SelectObject((HDC)param_1[1],(HGDIOBJ)param_1[0xe]);
    }
    if ((HPALETTE)param_1[0xf] != (HPALETTE)0x0) {
      SelectPalette((HDC)param_1[1],(HPALETTE)param_1[0xf],1);
    }
    hdc = (HDC)param_1[1];
    FUN_0041a9d0(param_1,0);
    DeleteDC(hdc);
    FUN_00409b2c(DAT_00489570,(int)param_1);
  }
  return;
}

