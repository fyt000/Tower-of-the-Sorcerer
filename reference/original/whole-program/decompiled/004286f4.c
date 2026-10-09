/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x004286f4.
 * Inferred types, shared tails and runtime effects require assembly review. */

undefined FUN_004286f4(int *param_1)

{
  bool bVar1;
  HWND hWnd;
  LRESULT LVar2;
  undefined uVar3;
  UINT Msg;
  WPARAM wParam;
  LPARAM lParam;
  
  uVar3 = *(undefined *)((int)param_1 + 0x10d);
  bVar1 = FUN_00416e54((int)param_1);
  if (bVar1) {
    lParam = 0;
    wParam = 0;
    Msg = 0xb8;
    hWnd = (HWND)FUN_00416cbc(param_1);
    LVar2 = SendMessageA(hWnd,Msg,wParam,lParam);
    uVar3 = LVar2 != 0;
  }
  return uVar3;
}

