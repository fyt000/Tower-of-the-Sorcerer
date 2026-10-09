/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00417a50.
 * Inferred types, shared tails and runtime effects require assembly review. */

undefined4 FUN_00417a50(int *param_1)

{
  int iVar1;
  HIMAGELIST himl;
  BOOL BVar2;
  IMAGEINFO *pImageInfo;
  IMAGEINFO local_24;
  
  pImageInfo = &local_24;
  iVar1 = FUN_00417b3c(param_1);
  if (0 < iVar1) {
    iVar1 = 0;
    himl = (HIMAGELIST)FUN_00417984(param_1);
    BVar2 = ImageList_GetImageInfo(himl,iVar1,pImageInfo);
    if (BVar2 != 0) {
      DeleteObject(local_24.hbmMask);
      return local_24.hbmImage;
    }
  }
  return 0;
}

