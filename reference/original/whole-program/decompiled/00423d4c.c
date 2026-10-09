/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00423d4c.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00423d4c(int param_1,short param_2)

{
  POINT Point;
  HWND hWnd;
  DWORD DVar1;
  DWORD DVar2;
  uint uVar3;
  HCURSOR hCursor;
  undefined2 extraout_var;
  tagPOINT local_18;
  
  if (param_2 != *(short *)(param_1 + 0x28)) {
    *(short *)(param_1 + 0x28) = param_2;
    if (param_2 == 0) {
      GetCursorPos(&local_18);
      Point.y = local_18.y;
      Point.x = local_18.x;
      hWnd = WindowFromPoint(Point);
      if (hWnd != (HWND)0x0) {
        DVar1 = GetWindowThreadProcessId(hWnd,(LPDWORD)0x0);
        DVar2 = GetCurrentThreadId();
        if (DVar1 == DVar2) {
          uVar3 = SendMessageA(hWnd,0x84,local_18.x,local_18.y);
          uVar3 = FUN_00405284(uVar3,CONCAT22(extraout_var,0x200));
          SendMessageA(hWnd,0x20,(WPARAM)hWnd,uVar3);
          return;
        }
      }
    }
    hCursor = (HCURSOR)FUN_00423d24(param_1,(int)param_2);
    SetCursor(hCursor);
  }
  return;
}

