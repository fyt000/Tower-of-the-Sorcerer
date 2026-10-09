/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0040f72c.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0040f72c(void)

{
  undefined4 extraout_EDX;
  undefined4 *in_FS_OFFSET;
  undefined4 uStack_20;
  undefined *puStack_1c;
  undefined *puStack_18;
  undefined4 *local_8;
  
  puStack_18 = &stack0xfffffffc;
  local_8 = (undefined4 *)0x0;
  puStack_1c = &LAB_0040f76d;
  uStack_20 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_20;
  FUN_00405bf0(0xf035,(int *)&local_8);
  FUN_0040f714(local_8,extraout_EDX);
  *in_FS_OFFSET = uStack_20;
  puStack_18 = &LAB_0040f774;
  puStack_1c = (undefined *)0x40f76c;
  FUN_004034dc((int *)&local_8);
  return;
}

