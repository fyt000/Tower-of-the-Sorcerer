/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0042f5c4.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_0042f5c4(int *param_1,undefined4 param_2)

{
  HWND pHVar1;
  undefined4 *in_FS_OFFSET;
  undefined4 uVar2;
  tagRECT *lpRect;
  RECT *lpRect_00;
  BOOL BVar3;
  undefined auStack_34 [4];
  undefined4 uStack_30;
  int iStack_2c;
  undefined4 uStack_28;
  RECT RStack_24;
  tagRECT tStack_14;
  
  BVar3 = 1;
  lpRect = &tStack_14;
  pHVar1 = (HWND)FUN_00416cbc(param_1);
  BVar3 = GetUpdateRect(pHVar1,lpRect,BVar3);
  if (BVar3 != 0) {
    (**(code **)(*param_1 + 0x2c))(param_1,auStack_34);
    FUN_0040923c(iStack_2c + -3,uStack_30,iStack_2c,&RStack_24.left,uStack_28);
    BVar3 = IntersectRect(&tStack_14,&tStack_14,&RStack_24);
    if (BVar3 != 0) {
      BVar3 = 1;
      lpRect_00 = &RStack_24;
      pHVar1 = (HWND)FUN_00416cbc(param_1);
      InvalidateRect(pHVar1,lpRect_00,BVar3);
    }
  }
  if (DAT_004897fc != '\0') {
    (**(code **)(*param_1 + 0x44))();
    return;
  }
  DAT_004897fc = 1;
  uVar2 = *in_FS_OFFSET;
  *in_FS_OFFSET = &stack0xffffffb4;
  root_00415a08(param_1,param_2);
  *in_FS_OFFSET = uVar2;
  DAT_004897fc = 0;
  return;
}

