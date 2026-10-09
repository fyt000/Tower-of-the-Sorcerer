/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x004243f4.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_004243f4(int param_1)

{
  uint uVar1;
  HWND hWnd;
  int iVar2;
  HWND hWndInsertAfter;
  int X;
  int Y;
  int cx;
  int cy;
  UINT uFlags;
  HWND local_c;
  
  if (*(int *)(DAT_0048a6f8 + 0x20) != 0) {
    if (*(int *)(param_1 + 0x74) == 0) {
      local_c = *(HWND *)(param_1 + 0x20);
      EnumWindows(root_0042438c,(LPARAM)&local_c);
      if (*(int *)(*(int *)(param_1 + 0x70) + 8) != 0) {
        local_c = GetWindow(local_c,3);
        uVar1 = GetWindowLongA(local_c,-0x14);
        if ((uVar1 & 8) != 0) {
          local_c = (HWND)0xfffffffe;
        }
        iVar2 = *(int *)(*(int *)(param_1 + 0x70) + 8) + -1;
        if (-1 < iVar2) {
          do {
            uFlags = 0x13;
            cy = 0;
            cx = 0;
            Y = 0;
            X = 0;
            hWndInsertAfter = local_c;
            hWnd = (HWND)FUN_00409a40(*(undefined4 **)(param_1 + 0x70),iVar2);
            SetWindowPos(hWnd,hWndInsertAfter,X,Y,cx,cy,uFlags);
            iVar2 = iVar2 + -1;
          } while (iVar2 != -1);
        }
      }
    }
    *(int *)(param_1 + 0x74) = *(int *)(param_1 + 0x74) + 1;
  }
  return;
}

