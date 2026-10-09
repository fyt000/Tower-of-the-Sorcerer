/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00414a18.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00414a18(int *param_1,undefined4 param_2)

{
  bool bVar1;
  undefined4 *in_FS_OFFSET;
  undefined4 uStack_28;
  undefined *puStack_24;
  undefined *puStack_20;
  undefined local_18 [16];
  int *local_8;
  
  puStack_20 = (undefined *)0x414a2c;
  local_8 = param_1;
  bVar1 = FUN_00416e54((int)param_1);
  if (bVar1) {
    if (*(short *)(local_8 + 0x33) == 0) {
      puStack_20 = (undefined *)0x414a4e;
      FUN_00414aa0((int)local_8);
      puStack_24 = &LAB_00414a91;
      uStack_28 = *in_FS_OFFSET;
      *in_FS_OFFSET = &uStack_28;
      puStack_20 = &stack0xfffffffc;
      (**(code **)(*local_8 + 0x2c))(local_8,local_18);
      (**(code **)(*local_8 + 0x54))(local_8,param_2,local_18);
      *in_FS_OFFSET = uStack_28;
      puStack_20 = (undefined *)0x414a98;
      *(byte *)((int)local_8 + 0x36) = *(byte *)((int)local_8 + 0x36) & 0xef;
      puStack_24 = (undefined *)0x414a90;
      FUN_00414aa8((int)local_8);
      return;
    }
    *(byte *)((int)local_8 + 0x36) = *(byte *)((int)local_8 + 0x36) | 0x10;
  }
  return;
}

