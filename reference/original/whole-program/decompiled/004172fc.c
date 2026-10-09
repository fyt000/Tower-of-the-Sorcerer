/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x004172fc.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_004172fc(int *param_1)

{
  LPCSTR lpchText;
  HDC hdc;
  undefined4 extraout_ECX;
  undefined4 *in_FS_OFFSET;
  int cchText;
  tagRECT *lprc;
  UINT format;
  undefined4 uStack_30;
  undefined *puStack_2c;
  undefined *puStack_28;
  undefined *puStack_18;
  tagRECT tStack_14;
  
  puStack_28 = &stack0xfffffffc;
  puStack_18 = (undefined *)0x0;
  puStack_2c = &LAB_0041737f;
  uStack_30 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_30;
  (**(code **)(*param_1 + 0x2c))(param_1,&tStack_14);
  tStack_14.left = tStack_14.left + 1;
  FUN_00419c7c(*(int **)(param_1[0x40] + 0xc),-0x7fffffe9,extraout_ECX);
  format = 0x810;
  lprc = &tStack_14;
  cchText = -1;
  FUN_004135a4(param_1,(int *)&puStack_18);
  lpchText = FUN_00403814(puStack_18);
  hdc = (HDC)FUN_0041a950((int *)param_1[0x40]);
  DrawTextA(hdc,lpchText,cchText,lprc,format);
  *in_FS_OFFSET = uStack_30;
  puStack_28 = &LAB_00417386;
  puStack_2c = (undefined *)0x41737e;
  FUN_004034dc((int *)&puStack_18);
  return;
}

