/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x004155c4.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_004155c4(int param_1,UINT *param_2)

{
  COLORREF CVar1;
  uint uVar2;
  UINT UVar3;
  
  if (*(HWND *)(param_1 + 0xc0) == (HWND)0x0) {
    FUN_00413d94(param_1,(int *)param_2);
  }
  else {
    UVar3 = *param_2;
    if (UVar3 - 0x132 < 7) {
      UVar3 = SendMessageA((HWND)param_2[2],UVar3 + 0xbc00,param_2[1],(LPARAM)(HWND)param_2[2]);
      param_2[3] = UVar3;
    }
    else if (UVar3 - 0xbd32 < 7) {
      CVar1 = FUN_00419b00(*(uint *)(*(int *)(param_1 + 0x44) + 0x10));
      SetTextColor((HDC)param_2[1],CVar1);
      uVar2 = FUN_0041a14c(*(int *)(param_1 + 0xbc));
      CVar1 = FUN_00419b00(uVar2);
      SetBkColor((HDC)param_2[1],CVar1);
      UVar3 = FUN_0041a188(*(int *)(param_1 + 0xbc));
      param_2[3] = UVar3;
    }
    else {
      UVar3 = CallWindowProcA(*(WNDPROC *)(param_1 + 0xac),*(HWND *)(param_1 + 0xc0),*param_2,
                              param_2[1],param_2[2]);
      param_2[3] = UVar3;
    }
  }
  return;
}

