/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x004152dc.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_004152dc(int *param_1)

{
  undefined4 *in_FS_OFFSET;
  undefined4 uStack_2c;
  undefined *puStack_28;
  undefined *puStack_24;
  undefined4 uStack_20;
  undefined *puStack_1c;
  undefined *puStack_18;
  
  puStack_18 = &stack0xfffffffc;
  puStack_24 = &stack0xfffffffc;
  puStack_1c = &LAB_00415333;
  uStack_20 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_20;
  puStack_28 = &LAB_00415322;
  uStack_2c = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_2c;
  (**(code **)(*param_1 + 0x40))();
  *in_FS_OFFSET = uStack_2c;
  puStack_24 = &LAB_00415329;
  puStack_28 = (undefined *)0x41531c;
  thunk_FUN_00412cbf();
  puStack_28 = (undefined *)0x415321;
  FUN_0041d20c();
  return;
}

