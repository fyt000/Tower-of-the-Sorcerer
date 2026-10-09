/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x004239f4.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_004239f4(undefined param_1,undefined param_2,undefined param_3,int param_4,
                 undefined param_5,undefined param_6,int *param_7)

{
  undefined4 *in_FS_OFFSET;
  undefined4 uStack_20;
  undefined *puStack_1c;
  undefined *puStack_18;
  int local_8;
  
  puStack_18 = &stack0xfffffffc;
  local_8 = 0;
  puStack_1c = &LAB_00423a43;
  uStack_20 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_20;
  FUN_00403638(&local_8,(undefined4 *)(param_4 + 0x1c),0x20);
  (**(code **)(*param_7 + 0x2c))(param_7,local_8);
  *in_FS_OFFSET = uStack_20;
  puStack_18 = &LAB_00423a4a;
  puStack_1c = (undefined *)0x423a42;
  FUN_004034dc(&local_8);
  return;
}

