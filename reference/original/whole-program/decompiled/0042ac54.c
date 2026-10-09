/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0042ac54.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0042ac54(int *param_1)

{
  HWND pHVar1;
  HWND hWndInsertAfter;
  int X;
  int Y;
  int cx;
  int cy;
  WPARAM wParam;
  UINT UVar2;
  int *lParam;
  
  cx = param_1[0xb];
  cy = param_1[0xc];
  FUN_00414e90(param_1);
  UVar2 = 0x14;
  Y = param_1[10];
  X = param_1[9];
  hWndInsertAfter = (HWND)0x0;
  pHVar1 = (HWND)FUN_00416cbc(param_1);
  SetWindowPos(pHVar1,hWndInsertAfter,X,Y,cx,cy,UVar2);
  if (param_1[0x47] != 0) {
    lParam = param_1 + 0x47;
    wParam = 1;
    UVar2 = 0x192;
    pHVar1 = (HWND)FUN_00416cbc(param_1);
    SendMessageA(pHVar1,UVar2,wParam,(LPARAM)lParam);
  }
  FUN_0042a8a0(param_1);
  if (param_1[0x48] != 0) {
    (**(code **)(*(int *)param_1[0x40] + 8))((int *)param_1[0x40],param_1[0x48]);
    FUN_0042aab0(param_1,param_1[0x49]);
    FUN_0042a938(param_1,param_1[0x4a]);
    FUN_00402c34((int *)param_1[0x48]);
    param_1[0x48] = 0;
  }
  return;
}

