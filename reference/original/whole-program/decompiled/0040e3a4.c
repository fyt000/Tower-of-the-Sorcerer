/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0040e3a4.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0040e3a4(int param_1,undefined4 *param_2)

{
  uint extraout_ECX;
  undefined4 *in_FS_OFFSET;
  undefined4 uStack_20;
  undefined *puStack_1c;
  undefined *puStack_18;
  undefined *local_8;
  
  puStack_18 = &stack0xfffffffc;
  local_8 = (undefined *)0x0;
  puStack_1c = &LAB_0040e3f3;
  uStack_20 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_20;
  FUN_00403570((int *)&local_8,*(int *)(param_1 + 0x28));
  FUN_00403658((int *)&local_8,param_2);
  FUN_0040e400(param_1,local_8,extraout_ECX);
  *in_FS_OFFSET = uStack_20;
  puStack_18 = &LAB_0040e3fa;
  puStack_1c = (undefined *)0x40e3f2;
  FUN_004034dc((int *)&local_8);
  return;
}

