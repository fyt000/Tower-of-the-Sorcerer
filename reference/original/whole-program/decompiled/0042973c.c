/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0042973c.
 * Inferred types, shared tails and runtime effects require assembly review. */

HWND FUN_0042973c(int *param_1)

{
  HWND pHVar1;
  LONG LVar2;
  WPARAM wParam;
  UINT UVar3;
  LPARAM lParam;
  
  FUN_00414e90(param_1);
  wParam = param_1[0x44];
  if (((int)wParam < 1) || (0xff < (int)wParam)) {
    wParam = 0xff;
  }
  lParam = 0;
  UVar3 = 0x141;
  pHVar1 = (HWND)FUN_00416cbc(param_1);
  SendMessageA(pHVar1,UVar3,wParam,lParam);
  if (param_1[0x4d] != 0) {
    (**(code **)(*(int *)param_1[0x40] + 8))((int *)param_1[0x40],param_1[0x4d]);
    FUN_00402c34((int *)param_1[0x4d]);
    param_1[0x4d] = 0;
  }
  param_1[0x46] = 0;
  param_1[0x47] = 0;
  pHVar1 = (HWND)(uint)(byte)(*(byte *)((int)param_1 + 0x109) - 2);
  if (*(byte *)((int)param_1 + 0x109) < 2) {
    UVar3 = 5;
    pHVar1 = (HWND)FUN_00416cbc(param_1);
    pHVar1 = GetWindow(pHVar1,UVar3);
    if (pHVar1 != (HWND)0x0) {
      if (*(char *)((int)param_1 + 0x109) == '\x01') {
        param_1[0x47] = (int)pHVar1;
        LVar2 = GetWindowLongA(pHVar1,-4);
        param_1[0x4b] = LVar2;
        SetWindowLongA((HWND)param_1[0x47],-4,param_1[0x49]);
        pHVar1 = GetWindow(pHVar1,2);
      }
      param_1[0x46] = (int)pHVar1;
      LVar2 = GetWindowLongA(pHVar1,-4);
      param_1[0x4a] = LVar2;
      pHVar1 = (HWND)SetWindowLongA((HWND)param_1[0x46],-4,param_1[0x48]);
    }
  }
  if ((DAT_0048a694 != '\0') && (param_1[0x46] != 0)) {
    pHVar1 = (HWND)SendMessageA((HWND)param_1[0x46],0xd3,3,0);
  }
  return pHVar1;
}

