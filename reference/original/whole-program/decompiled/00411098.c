/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00411098.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00411098(void)

{
  undefined4 extraout_ECX;
  undefined4 extraout_ECX_00;
  undefined4 extraout_EDX;
  undefined4 extraout_EDX_00;
  undefined4 *in_FS_OFFSET;
  undefined4 uStack_20;
  undefined *puStack_1c;
  undefined *puStack_18;
  undefined **local_8;
  
  puStack_18 = &stack0xfffffffc;
  puStack_1c = &LAB_004110f4;
  uStack_20 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_20;
  local_8 = &PTR_FUN_0040f20c;
  FUN_00409500(&local_8,0);
  FUN_0040f77c();
  DAT_0048a68c = FUN_00402c0c(0x408b0c,CONCAT31((int3)((uint)extraout_EDX >> 8),1),extraout_ECX);
  DAT_0048a690 = FUN_00402c0c(0x410d34,CONCAT31((int3)((uint)extraout_EDX_00 >> 8),1),
                              extraout_ECX_00);
  *in_FS_OFFSET = uStack_20;
  return;
}

