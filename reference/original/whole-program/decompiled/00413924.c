/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00413924.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00413924(int param_1,char param_2,char param_3)

{
  bool bVar1;
  char cVar2;
  BOOL bErase;
  HWND hWnd;
  undefined extraout_CL;
  undefined extraout_DL;
  RECT *lpRect;
  RECT local_18;
  int local_8;
  
  if (param_2 == '\0') {
    if ((*(byte *)(param_1 + 0x1c) & 0x10) == 0) {
      return;
    }
    if ((*(byte *)(param_1 + 0x35) & 4) != 0) {
      return;
    }
  }
  if (*(int *)(param_1 + 0x20) == 0) {
    return;
  }
  local_8 = param_1;
  bVar1 = FUN_00416e54(*(int *)(param_1 + 0x20));
  if (bVar1) {
    FUN_00413118(local_8,&local_18.left);
    if (((param_3 == '\0') && ((*(byte *)(*(int *)(local_8 + 0x20) + 0x34) & 0x40) == 0)) &&
       (cVar2 = FUN_0041389c((char)*(int *)(local_8 + 0x20),extraout_DL,extraout_CL,&stack0xfffffffc
                            ), cVar2 == '\0')) {
      bErase = 1;
    }
    else {
      bErase = 0;
    }
    lpRect = &local_18;
    hWnd = (HWND)FUN_00416cbc(*(int **)(local_8 + 0x20));
    InvalidateRect(hWnd,lpRect,bErase);
    return;
  }
  return;
}

