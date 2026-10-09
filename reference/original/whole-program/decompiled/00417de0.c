/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00417de0.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00417de0(int *param_1,uint param_2)

{
  bool bVar1;
  COLORREF clrBk;
  HIMAGELIST himl;
  undefined4 extraout_ECX;
  undefined4 extraout_ECX_00;
  undefined4 uVar2;
  undefined4 extraout_EDX;
  undefined4 extraout_EDX_00;
  undefined4 uVar3;
  
  bVar1 = FUN_00417800((int)param_1);
  if (bVar1) {
    clrBk = FUN_0041761c(param_2);
    himl = (HIMAGELIST)FUN_00417984(param_1);
    ImageList_SetBkColor(himl,clrBk);
    uVar2 = extraout_ECX_00;
    uVar3 = extraout_EDX_00;
  }
  else {
    param_1[0xd] = param_2;
    uVar2 = extraout_ECX;
    uVar3 = extraout_EDX;
  }
  FUN_00402cdc(param_1,uVar3,uVar2);
  return;
}

