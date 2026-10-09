/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00411050.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00411050(int param_1,int param_2,int param_3)

{
  uint uFlags;
  HMENU hMenu;
  int nReserved;
  HWND hWnd;
  RECT *prcRect;
  
  FUN_00411030(param_1);
  prcRect = (RECT *)0x0;
  hWnd = *(HWND *)(DAT_0048a690 + 0x10);
  nReserved = 0;
  uFlags = (uint)(*(ushort *)(&DAT_00489274 + (uint)*(byte *)(param_1 + 0x2c) * 2) | 2);
  hMenu = (HMENU)FUN_0041021c(*(int *)(param_1 + 0x20));
  TrackPopupMenu(hMenu,uFlags,param_2,param_3,nReserved,hWnd,prcRect);
  return;
}

