/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00428944.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00428944(int *param_1)

{
  undefined4 *in_FS_OFFSET;
  undefined4 uStack_14;
  undefined *puStack_10;
  undefined *puStack_c;
  int *local_8;
  
  puStack_c = &stack0xfffffffc;
  *(undefined *)(param_1 + 0x43) = 1;
  puStack_10 = &LAB_00428983;
  uStack_14 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_14;
  local_8 = param_1;
  FUN_00414e90(param_1);
  *in_FS_OFFSET = uStack_14;
  *(undefined *)(local_8 + 0x43) = 0;
  return;
}

