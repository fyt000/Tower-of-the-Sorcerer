/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00428c58.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00428c58(int *param_1)

{
  bool bVar1;
  HWND hWnd;
  uint uVar2;
  undefined4 extraout_ECX;
  undefined4 extraout_ECX_00;
  undefined4 uVar3;
  undefined4 extraout_EDX;
  undefined4 extraout_EDX_00;
  undefined4 uVar4;
  int nIndex;
  
  (**(code **)(*param_1 + -0x10))();
  bVar1 = FUN_00416e54((int)param_1);
  uVar3 = extraout_ECX;
  uVar4 = extraout_EDX;
  if (bVar1) {
    nIndex = -0x10;
    hWnd = (HWND)FUN_00416cbc(param_1);
    uVar2 = GetWindowLongA(hWnd,nIndex);
    uVar3 = extraout_ECX_00;
    uVar4 = extraout_EDX_00;
    if ((uVar2 & 4) == 0) {
      return;
    }
  }
  FUN_00402cdc(param_1,uVar4,uVar3);
  return;
}

