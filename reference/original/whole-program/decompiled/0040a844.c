/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0040a844.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_0040a844(int *param_1,undefined4 *param_2)

{
  undefined4 *in_FS_OFFSET;
  undefined4 uStack_20;
  undefined *puStack_1c;
  undefined *puStack_18;
  int iStack_8;
  
  puStack_18 = &stack0xfffffffc;
  iStack_8 = 0;
  puStack_1c = &LAB_0040a888;
  uStack_20 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_20;
  FUN_00403608(&iStack_8,param_2);
  (**(code **)(*param_1 + 0x24))(param_1,iStack_8);
  *in_FS_OFFSET = uStack_20;
  puStack_18 = &LAB_0040a88f;
  puStack_1c = (undefined *)0x40a887;
  FUN_004034dc(&iStack_8);
  return;
}

