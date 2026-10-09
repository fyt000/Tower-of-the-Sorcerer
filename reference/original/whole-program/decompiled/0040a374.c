/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0040a374.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0040a374(int *param_1)

{
  undefined4 *puVar1;
  undefined4 *in_FS_OFFSET;
  undefined4 uStack_20;
  undefined *puStack_1c;
  undefined *puStack_18;
  undefined *local_8;
  
  puStack_18 = &stack0xfffffffc;
  local_8 = (undefined *)0x0;
  puStack_1c = &LAB_0040a3bb;
  uStack_20 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_20;
  (**(code **)(*param_1 + 0x18))(param_1,&local_8);
  puVar1 = (undefined4 *)FUN_00403814(local_8);
  FUN_00406240(puVar1);
  *in_FS_OFFSET = uStack_20;
  puStack_18 = &LAB_0040a3c2;
  puStack_1c = (undefined *)0x40a3ba;
  FUN_004034dc((int *)&local_8);
  return;
}

