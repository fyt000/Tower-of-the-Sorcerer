/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00417e44.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00417e44(int *param_1,int *param_2,int param_3,int param_4,int param_5)

{
  bool bVar1;
  uint fStyle;
  COLORREF rgbFg;
  uint uVar2;
  COLORREF rgbBk;
  HDC hdcDst;
  HIMAGELIST himl;
  int dx;
  int dy;
  
  bVar1 = FUN_00417800((int)param_1);
  if (bVar1) {
    fStyle = *(uint *)(&DAT_00489334 + (uint)*(byte *)(param_1 + 0xc) * 4) |
             *(uint *)(&DAT_00489344 + (uint)*(byte *)((int)param_1 + 0x33) * 4);
    rgbFg = FUN_0041761c(param_1[0xe]);
    uVar2 = FUN_00417e1c(param_1);
    rgbBk = FUN_0041761c(uVar2);
    dy = 0;
    dx = 0;
    hdcDst = (HDC)FUN_0041a950(param_2);
    himl = (HIMAGELIST)FUN_00417984(param_1);
    ImageList_DrawEx(himl,param_4,hdcDst,param_3,param_5,dx,dy,rgbBk,rgbFg,fStyle);
  }
  return;
}

