/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00421370.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_00421370(int *param_1,LPRECT param_2)

{
  HWND pHVar1;
  BOOL BVar2;
  DWORD dwExStyle;
  uint bMenu;
  DWORD dwStyle;
  int iVar3;
  
  pHVar1 = (HWND)FUN_00416cbc(param_1);
  BVar2 = IsIconic(pHVar1);
  if (BVar2 != 0) {
    SetRect(param_2,0,0,0,0);
    iVar3 = -0x14;
    pHVar1 = (HWND)FUN_00416cbc(param_1);
    dwExStyle = GetWindowLongA(pHVar1,iVar3);
    bMenu = (uint)(param_1[0x4a] != 0);
    iVar3 = -0x10;
    pHVar1 = (HWND)FUN_00416cbc(param_1);
    dwStyle = GetWindowLongA(pHVar1,iVar3);
    AdjustWindowRectEx(param_2,dwStyle,bMenu,dwExStyle);
    SetRect(param_2,0,0,(param_1[0xb] - param_2->right) + param_2->left,
            (param_1[0xc] - param_2->bottom) + param_2->top);
    return;
  }
  FUN_00416cf0(param_1,param_2);
  return;
}

