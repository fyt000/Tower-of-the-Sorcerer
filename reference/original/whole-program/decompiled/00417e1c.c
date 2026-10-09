/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00417e1c.
 * Inferred types, shared tails and runtime effects require assembly review. */

int FUN_00417e1c(int *param_1)

{
  bool bVar1;
  HIMAGELIST himl;
  COLORREF CVar2;
  int iVar3;
  
  bVar1 = FUN_00417800((int)param_1);
  if (bVar1) {
    himl = (HIMAGELIST)FUN_00417984(param_1);
    CVar2 = ImageList_GetBkColor(himl);
    iVar3 = FUN_0041763c(CVar2);
    return iVar3;
  }
  return param_1[0xd];
}

