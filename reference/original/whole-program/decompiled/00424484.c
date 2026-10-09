/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00424484.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00424484(int param_1)

{
  HWND hWnd;
  int iVar1;
  HWND hWndInsertAfter;
  int X;
  int Y;
  int cx;
  int cy;
  UINT uFlags;
  
  if ((*(int *)(DAT_0048a6f8 + 0x20) != 0) &&
     (*(int *)(param_1 + 0x74) = *(int *)(param_1 + 0x74) + -1, *(int *)(param_1 + 0x74) == 0)) {
    iVar1 = *(int *)(*(int *)(param_1 + 0x70) + 8) + -1;
    if (-1 < iVar1) {
      do {
        uFlags = 0x13;
        cy = 0;
        cx = 0;
        Y = 0;
        X = 0;
        hWndInsertAfter = (HWND)0xffffffff;
        hWnd = (HWND)FUN_00409a40(*(undefined4 **)(param_1 + 0x70),iVar1);
        SetWindowPos(hWnd,hWndInsertAfter,X,Y,cx,cy,uFlags);
        iVar1 = iVar1 + -1;
      } while (iVar1 != -1);
    }
    FUN_004099cc(*(undefined4 **)(param_1 + 0x70));
  }
  return;
}

