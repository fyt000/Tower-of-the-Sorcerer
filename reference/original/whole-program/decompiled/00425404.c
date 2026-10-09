/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00425404.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_00425404(int param_1)

{
  LPARAM lParam;
  BOOL BVar1;
  undefined2 extraout_var;
  undefined2 extraout_var_00;
  undefined2 extraout_var_01;
  undefined2 uVar2;
  
  if (DAT_0048a694 == '\0') {
    BVar1 = IsIconic(*(HWND *)(param_1 + 0x20));
    uVar2 = extraout_var_00;
    if (BVar1 != 0) {
      InvalidateRect(*(HWND *)(param_1 + 0x20),(RECT *)0x0,1);
      uVar2 = extraout_var_01;
    }
  }
  else {
    lParam = FUN_00424ae8(param_1);
    SendMessageA(*(HWND *)(param_1 + 0x20),0x80,1,lParam);
    uVar2 = extraout_var;
  }
  FUN_004253c8(param_1,CONCAT22(uVar2,0xb01d));
  return;
}

