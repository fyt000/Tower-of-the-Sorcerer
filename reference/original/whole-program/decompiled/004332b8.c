/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x004332b8.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_004332b8(undefined4 param_1,int *param_2,undefined *param_3,char param_4,LONG *param_5)

{
  LPCSTR lpchText;
  HDC pHVar1;
  LPCSTR pCVar2;
  int iVar3;
  undefined4 extraout_ECX;
  undefined4 extraout_ECX_00;
  tagRECT *ptVar4;
  UINT UVar5;
  tagRECT local_14;
  
  ptVar4 = &local_14;
  for (iVar3 = 4; iVar3 != 0; iVar3 = iVar3 + -1) {
    ptVar4->left = *param_5;
    param_5 = param_5 + 1;
    ptVar4 = (tagRECT *)&ptVar4->top;
  }
  FUN_0041a20c((int *)param_2[5],'\x01');
  if (param_4 == '\x01') {
    OffsetRect(&local_14,1,1);
    FUN_00419c7c((int *)param_2[3],0xffffff,extraout_ECX);
    UVar5 = 0;
    ptVar4 = &local_14;
    iVar3 = FUN_00403650((int)param_3);
    lpchText = FUN_00403814(param_3);
    pCVar2 = lpchText;
    pHVar1 = (HDC)FUN_0041a950(param_2);
    DrawTextA(pHVar1,pCVar2,iVar3,ptVar4,UVar5);
    OffsetRect(&local_14,-1,-1);
    FUN_00419c7c((int *)param_2[3],0x808080,extraout_ECX_00);
    UVar5 = 0;
    ptVar4 = &local_14;
    iVar3 = FUN_00403650((int)param_3);
    pHVar1 = (HDC)FUN_0041a950(param_2);
    DrawTextA(pHVar1,lpchText,iVar3,ptVar4,UVar5);
  }
  else {
    UVar5 = 0x25;
    ptVar4 = &local_14;
    iVar3 = FUN_00403650((int)param_3);
    pCVar2 = FUN_00403814(param_3);
    pHVar1 = (HDC)FUN_0041a950(param_2);
    DrawTextA(pHVar1,pCVar2,iVar3,ptVar4,UVar5);
  }
  return;
}

