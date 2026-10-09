/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00417ad0.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00417ad0(int *param_1,int *param_2,int *param_3)

{
  HBITMAP hbmMask;
  HBITMAP hbmImage;
  HIMAGELIST himl;
  
  hbmMask = (HBITMAP)FUN_00417994((int)param_1,param_3);
  hbmImage = (HBITMAP)FUN_00417994((int)param_1,param_2);
  himl = (HIMAGELIST)FUN_00417984(param_1);
  ImageList_Add(himl,hbmImage,hbmMask);
  return;
}

