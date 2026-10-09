/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x004150c4.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_004150c4(int *param_1)

{
  HWND hWndInsertAfter;
  int X;
  int Y;
  int cx;
  int cy;
  UINT uFlags;
  
  if (param_1[0x30] == 0) {
    (**(code **)(*param_1 + 100))();
    SetPropA((HWND)param_1[0x30],(LPCSTR)(uint)DAT_0048a698,param_1);
    SetPropA((HWND)param_1[0x30],(LPCSTR)(uint)DAT_0048a696,param_1);
    if (param_1[8] != 0) {
      uFlags = 0x13;
      cy = 0;
      cx = 0;
      Y = 0;
      X = 0;
      hWndInsertAfter = (HWND)FUN_0041507c(param_1[8],(int)param_1);
      SetWindowPos((HWND)param_1[0x30],hWndInsertAfter,X,Y,cx,cy,uFlags);
    }
  }
  return;
}

