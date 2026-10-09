/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00420524.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00420524(int param_1)

{
  int iVar1;
  HWND hwnd;
  uint nBar;
  SCROLLINFO *lpsi;
  BOOL redraw;
  SCROLLINFO local_2c;
  
  *(undefined4 *)(param_1 + 0x14) = 0;
  nBar = (uint)(*(char *)(param_1 + 0x18) == '\x01');
  if (*(char *)(param_1 + 0x1c) != '\0') {
    iVar1 = FUN_004202c4(param_1);
    iVar1 = *(int *)(param_1 + 0x10) - iVar1;
    *(int *)(param_1 + 0x14) = iVar1;
    if (iVar1 < 0) {
      *(undefined4 *)(param_1 + 0x14) = 0;
    }
  }
  local_2c.cbSize = 0x1c;
  local_2c.fMask = 0x17;
  local_2c.nMin = 0;
  if (*(int *)(param_1 + 0x14) < 1) {
    local_2c.nMax = 0;
  }
  else {
    local_2c.nMax = *(int *)(param_1 + 0x10);
  }
  iVar1 = FUN_004202c4(param_1);
  local_2c.nPage = iVar1 + 1;
  local_2c.nPos = *(int *)(param_1 + 0xc);
  redraw = 1;
  lpsi = &local_2c;
  local_2c.nTrackPos = local_2c.nPos;
  hwnd = (HWND)FUN_00416cbc(*(int **)(param_1 + 4));
  SetScrollInfo(hwnd,nBar,lpsi,redraw);
  FUN_00420424(param_1,*(int *)(param_1 + 0xc));
  return;
}

