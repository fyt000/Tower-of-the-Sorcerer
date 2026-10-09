/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00421b44.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00421b44(int *param_1)

{
  HWND pHVar1;
  HMENU pHVar2;
  HMENU wParam;
  LPARAM lParam;
  
  if ((*(char *)((int)param_1 + 0x11a) == '\x02') && (param_1[0x4d] != 0)) {
    wParam = (HMENU)0x0;
    if ((int *)param_1[0x4a] != (int *)0x0) {
      wParam = (HMENU)(**(code **)(*(int *)param_1[0x4a] + 0x2c))();
    }
    lParam = 0;
    if (param_1[0x4e] != 0) {
      lParam = FUN_0041021c(param_1[0x4e]);
    }
    pHVar1 = (HWND)FUN_00416cbc(param_1);
    pHVar2 = GetMenu(pHVar1);
    SendMessageA((HWND)param_1[0x4d],0x230,(WPARAM)wParam,lParam);
    if (wParam != pHVar2) {
      pHVar1 = (HWND)FUN_00416cbc(param_1);
      DrawMenuBar(pHVar1);
    }
  }
  return;
}

