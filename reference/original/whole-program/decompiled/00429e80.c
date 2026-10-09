/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00429e80.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00429e80(int *param_1)

{
  int iVar1;
  int iVar2;
  HWND pHVar3;
  HWND pHVar4;
  int iVar5;
  int iVar6;
  UINT UVar7;
  
  iVar1 = (**(code **)(*(int *)param_1[0x40] + 0x10))();
  if (param_1[0x45] < iVar1) {
    iVar1 = param_1[0x45];
  }
  if (iVar1 < 1) {
    iVar1 = 1;
  }
  UVar7 = 0x9e;
  iVar2 = FUN_0042969c(param_1);
  iVar2 = iVar2 * iVar1 + param_1[0xc] + 2;
  iVar1 = param_1[0xb];
  iVar6 = 0;
  iVar5 = 0;
  pHVar4 = (HWND)0x0;
  pHVar3 = (HWND)FUN_00416cbc(param_1);
  SetWindowPos(pHVar3,pHVar4,iVar5,iVar6,iVar1,iVar2,UVar7);
  UVar7 = 0x5f;
  iVar6 = 0;
  iVar5 = 0;
  iVar2 = 0;
  iVar1 = 0;
  pHVar4 = (HWND)0x0;
  pHVar3 = (HWND)FUN_00416cbc(param_1);
  SetWindowPos(pHVar3,pHVar4,iVar1,iVar2,iVar5,iVar6,UVar7);
  return;
}

