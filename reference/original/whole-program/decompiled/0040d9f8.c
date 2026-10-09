/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0040d9f8.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0040d9f8(undefined param_1,undefined param_2,undefined param_3,int param_4)

{
  undefined4 *in_FS_OFFSET;
  undefined4 uStack_20;
  undefined *puStack_1c;
  undefined *puStack_18;
  undefined4 *local_8;
  
  puStack_18 = &stack0xfffffffc;
  local_8 = (undefined4 *)0x0;
  puStack_1c = &LAB_0040da43;
  uStack_20 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_20;
  FUN_004035fc((int *)&local_8,(byte *)(*(int *)(param_4 + -0xc) + 0x1a));
  FUN_0040e3a4(*(int *)(param_4 + -4),local_8);
  *in_FS_OFFSET = uStack_20;
  puStack_18 = &LAB_0040da4a;
  puStack_1c = (undefined *)0x40da42;
  FUN_004034dc((int *)&local_8);
  return;
}

