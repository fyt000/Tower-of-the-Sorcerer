/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0041257c.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_0041257c(undefined4 param_1,int *param_2)

{
  HWND extraout_ECX;
  undefined4 extraout_EDX;
  undefined4 *in_FS_OFFSET;
  undefined4 uStack_24;
  code *pcStack_20;
  undefined *puStack_1c;
  tagPOINT tStack_c;
  
  puStack_1c = &stack0xfffffffc;
  pcStack_20 = thunk_FUN_00402f4c;
  uStack_24 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_24;
  if (*param_2 == 0x200) {
    FUN_004052e0(param_2[2],&tStack_c.x);
    ClientToScreen(DAT_0048a6b0,&tStack_c);
    FUN_004127b4(&tStack_c,extraout_EDX,extraout_ECX);
  }
  else if (*param_2 == 0x202) {
    puStack_1c = &stack0xfffffffc;
    FUN_00412a30('\x01');
  }
  *in_FS_OFFSET = uStack_24;
  return;
}

