/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00421edc.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00421edc(int *param_1,byte param_2)

{
  HWND hWnd;
  int nCmdShow;
  
  if (((param_2 != *(byte *)((int)param_1 + 0x116)) &&
      (*(byte *)((int)param_1 + 0x116) = param_2, (*(byte *)(param_1 + 7) & 0x10) == 0)) &&
     (*(char *)((int)param_1 + 199) != '\0')) {
    nCmdShow = *(int *)(&DAT_004895cc + (uint)param_2 * 4);
    hWnd = (HWND)FUN_00416cbc(param_1);
    ShowWindow(hWnd,nCmdShow);
  }
  return;
}

