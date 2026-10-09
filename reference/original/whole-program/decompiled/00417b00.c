/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00417b00.
 * Inferred types, shared tails and runtime effects require assembly review. */

int FUN_00417b00(int *param_1,int *param_2,uint param_3)

{
  COLORREF crMask;
  HBITMAP hbmImage;
  HIMAGELIST himl;
  int iVar1;
  undefined4 extraout_ECX;
  undefined4 extraout_EDX;
  
  crMask = FUN_00419b00(param_3);
  hbmImage = (HBITMAP)FUN_00417994((int)param_1,param_2);
  himl = (HIMAGELIST)FUN_00417984(param_1);
  iVar1 = ImageList_AddMasked(himl,hbmImage,crMask);
  FUN_00402cdc(param_1,extraout_EDX,extraout_ECX);
  return iVar1;
}

