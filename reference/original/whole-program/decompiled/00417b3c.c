/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00417b3c.
 * Inferred types, shared tails and runtime effects require assembly review. */

int FUN_00417b3c(int *param_1)

{
  bool bVar1;
  HIMAGELIST himl;
  int iVar2;
  
  bVar1 = FUN_00417800((int)param_1);
  if (bVar1) {
    himl = (HIMAGELIST)FUN_00417984(param_1);
    iVar2 = ImageList_GetImageCount(himl);
    return iVar2;
  }
  return 0;
}

