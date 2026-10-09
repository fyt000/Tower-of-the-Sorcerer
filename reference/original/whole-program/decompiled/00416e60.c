/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00416e60.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00416e60(int param_1)

{
  BOOL BVar1;
  uint uVar2;
  HWND hWnd;
  int iVar3;
  RECT *pRVar4;
  LONG *pLVar5;
  undefined local_48 [12];
  int local_3c;
  WINDOWPLACEMENT local_38;
  
  BVar1 = IsIconic(*(HWND *)(param_1 + 0xc0));
  if (BVar1 == 0) {
    GetWindowRect(*(HWND *)(param_1 + 0xc0),(LPRECT)local_48);
  }
  else {
    local_38.length = 0x2c;
    GetWindowPlacement(*(HWND *)(param_1 + 0xc0),&local_38);
    pRVar4 = &local_38.rcNormalPosition;
    pLVar5 = (LONG *)local_48;
    for (iVar3 = 4; iVar3 != 0; iVar3 = iVar3 + -1) {
      *pLVar5 = pRVar4->left;
      pRVar4 = (RECT *)&pRVar4->top;
      pLVar5 = pLVar5 + 1;
    }
  }
  uVar2 = GetWindowLongA(*(HWND *)(param_1 + 0xc0),-0x10);
  if ((uVar2 & 0x40000000) != 0) {
    hWnd = (HWND)GetWindowLongA(*(HWND *)(param_1 + 0xc0),-8);
    ScreenToClient(hWnd,(LPPOINT)local_48);
    ScreenToClient(hWnd,(LPPOINT)(local_48 + 8));
  }
  *(undefined4 *)(param_1 + 0x24) = local_48._0_4_;
  *(undefined4 *)(param_1 + 0x28) = local_48._4_4_;
  *(undefined4 *)(param_1 + 0x2c) = local_48._8_4_ - local_48._0_4_;
  *(int *)(param_1 + 0x30) = local_3c - local_48._4_4_;
  return;
}

