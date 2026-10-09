/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0041819c.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0041819c(int param_1)

{
  int cy;
  int cx;
  HICON pHVar1;
  undefined4 *in_FS_OFFSET;
  UINT flags;
  undefined4 uVar2;
  int cInitial;
  int cGrow;
  POINT local_10;
  HIMAGELIST local_8;
  
  if (*(short *)(param_1 + 0x46) != -1) {
    cGrow = 1;
    cInitial = 1;
    flags = 1;
    cy = GetSystemMetrics(0xe);
    cx = GetSystemMetrics(0xd);
    local_8 = ImageList_Create(cx,cy,flags,cInitial,cGrow);
    uVar2 = *in_FS_OFFSET;
    *in_FS_OFFSET = &stack0xffffffe0;
    pHVar1 = (HICON)FUN_00423d24(DAT_0048a6fc,(int)*(short *)(param_1 + 0x46));
    FUN_0040ec74(local_8,pHVar1);
    pHVar1 = (HICON)FUN_00423d24(DAT_0048a6fc,(int)*(short *)(param_1 + 0x46));
    FUN_0040ec74(local_8,pHVar1);
    ImageList_SetDragCursorImage(local_8,0,0,0);
    ImageList_GetDragImage((POINT *)0x0,&local_10);
    ImageList_SetDragCursorImage(local_8,1,local_10.x,local_10.y);
    *in_FS_OFFSET = uVar2;
    ImageList_Destroy(local_8);
    return;
  }
  return;
}

