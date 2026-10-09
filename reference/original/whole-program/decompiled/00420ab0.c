/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00420ab0.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00420ab0(int *param_1,undefined4 param_2)

{
  undefined4 *in_FS_OFFSET;
  undefined4 uStack_14;
  undefined *puStack_10;
  undefined *puStack_c;
  int *local_8;
  
  puStack_c = &stack0xfffffffc;
  *(undefined *)((int)param_1 + 0x109) = 1;
  puStack_10 = &LAB_00420aef;
  uStack_14 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_14;
  local_8 = param_1;
  FUN_00415c64(param_1,param_2);
  *in_FS_OFFSET = uStack_14;
  *(undefined *)((int)local_8 + 0x109) = 0;
  return;
}

