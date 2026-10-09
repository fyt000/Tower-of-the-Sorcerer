/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00422ca4.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_00422ca4(int *param_1,undefined4 param_2)

{
  HWND pHVar1;
  UINT Msg;
  WPARAM wParam;
  LPARAM lParam;
  HMENU hMenu;
  
  if (DAT_0048a694 != '\0') {
    lParam = 0;
    wParam = 1;
    Msg = 0x80;
    pHVar1 = (HWND)FUN_00416cbc(param_1);
    SendMessageA(pHVar1,Msg,wParam,lParam);
  }
  if ((param_1[0x4a] != 0) && (*(char *)((int)param_1 + 0x11a) != '\x01')) {
    hMenu = (HMENU)0x0;
    pHVar1 = (HWND)FUN_00416cbc(param_1);
    SetMenu(pHVar1,hMenu);
    FUN_00410c40((int *)param_1[0x4a],0);
  }
  root_0041615c(param_1,param_2);
  return;
}

