/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00428364.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00428364(int *param_1)

{
  HDC hDC;
  int iVar1;
  tagRECT tStack_18;
  
  if (((*(byte *)(param_1 + 7) & 2) == 0) && (*(char *)((int)param_1 + 0xb1) != '\0')) {
    (**(code **)(*param_1 + 0x2c))(param_1,&tStack_18);
    hDC = GetDC((HWND)0x0);
    FUN_0041a9d0((int *)param_1[0x2a],(int)hDC);
    FUN_004281f0(param_1,&tStack_18,
                 *(ushort *)(&DAT_00489678 + (uint)*(byte *)((int)param_1 + 0xb2) * 2) | 0x440);
    FUN_0041a9d0((int *)param_1[0x2a],0);
    ReleaseDC((HWND)0x0,hDC);
    iVar1 = param_1[9];
    if (*(char *)(param_1 + 0x2c) == '\x01') {
      iVar1 = iVar1 + (param_1[0xb] - tStack_18.right);
    }
    (**(code **)(*param_1 + 0x4c))(param_1,iVar1,param_1[10],tStack_18.bottom,tStack_18.right);
  }
  return;
}

