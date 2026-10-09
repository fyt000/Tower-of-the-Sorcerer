/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x004167ac.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_004167ac(int param_1,int param_2,int param_3,int param_4,int param_5)

{
  bool bVar1;
  BOOL BVar2;
  int iVar3;
  LONG *pLVar4;
  RECT *pRVar5;
  byte bVar6;
  LONG aLStack_40 [4];
  WINDOWPLACEMENT WStack_30;
  
  bVar6 = 0;
  if ((((param_2 == *(int *)(param_1 + 0x24)) && (param_3 == *(int *)(param_1 + 0x28))) &&
      (param_5 == *(int *)(param_1 + 0x2c))) && (param_4 == *(int *)(param_1 + 0x30))) {
    return;
  }
  bVar1 = FUN_00416e54(param_1);
  if ((bVar1) && (BVar2 = IsIconic(*(HWND *)(param_1 + 0xc0)), BVar2 == 0)) {
    SetWindowPos(*(HWND *)(param_1 + 0xc0),(HWND)0x0,param_2,param_3,param_5,param_4,0x14);
  }
  else {
    *(int *)(param_1 + 0x24) = param_2;
    *(int *)(param_1 + 0x28) = param_3;
    *(int *)(param_1 + 0x2c) = param_5;
    *(int *)(param_1 + 0x30) = param_4;
    bVar1 = FUN_00416e54(param_1);
    if (bVar1) {
      WStack_30.length = 0x2c;
      GetWindowPlacement(*(HWND *)(param_1 + 0xc0),&WStack_30);
      FUN_00413118(param_1,aLStack_40);
      pLVar4 = aLStack_40;
      pRVar5 = &WStack_30.rcNormalPosition;
      for (iVar3 = 4; iVar3 != 0; iVar3 = iVar3 + -1) {
        pRVar5->left = *pLVar4;
        pLVar4 = pLVar4 + (uint)bVar6 * -2 + 1;
        pRVar5 = (RECT *)((int)pRVar5 + ((uint)bVar6 * -2 + 1) * 4);
      }
      SetWindowPlacement(*(HWND *)(param_1 + 0xc0),&WStack_30);
    }
  }
  FUN_00412f1c(param_1);
  return;
}

