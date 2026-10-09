/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00422a6c.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_00422a6c(int *param_1,int param_2)

{
  HWND pHVar1;
  BOOL BVar2;
  HDC hDC;
  HICON hIcon;
  tagPAINTSTRUCT *ptVar3;
  tagPAINTSTRUCT tStack_48;
  
  ptVar3 = &tStack_48;
  pHVar1 = (HWND)FUN_00416cbc(param_1);
  BVar2 = IsIconic(pHVar1);
  if (BVar2 == 0) {
    FUN_004156ac(param_1,param_2);
  }
  else {
    pHVar1 = (HWND)FUN_00416cbc(param_1);
    hDC = BeginPaint(pHVar1,ptVar3);
    ptVar3 = &tStack_48;
    hIcon = (HICON)FUN_00422934((int)param_1);
    DrawIcon(hDC,0,0,hIcon);
    pHVar1 = (HWND)FUN_00416cbc(param_1);
    EndPaint(pHVar1,ptVar3);
  }
  return;
}

