/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00420784.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00420784(int param_1)

{
  bool bVar1;
  undefined4 *in_FS_OFFSET;
  undefined4 uStack_14;
  undefined *puStack_10;
  undefined *puStack_c;
  int local_8;
  
  if (*(char *)(param_1 + 0x10a) == '\0') {
    puStack_c = (undefined *)0x4207a3;
    local_8 = param_1;
    bVar1 = FUN_00416e54(param_1);
    if (bVar1) {
      puStack_10 = &LAB_0042086f;
      uStack_14 = *in_FS_OFFSET;
      *in_FS_OFFSET = &uStack_14;
      *(undefined *)(local_8 + 0x10a) = 1;
      puStack_c = &stack0xfffffffc;
      bVar1 = FUN_00420344(*(int *)(local_8 + 0x104));
      if (bVar1) {
        FUN_00420524(*(int *)(local_8 + 0x100));
        FUN_00420524(*(int *)(local_8 + 0x104));
      }
      else {
        bVar1 = FUN_00420344(*(int *)(local_8 + 0x100));
        if (bVar1) {
          FUN_00420524(*(int *)(local_8 + 0x104));
          FUN_00420524(*(int *)(local_8 + 0x100));
        }
        else {
          FUN_00420524(*(int *)(local_8 + 0x104));
          FUN_00420524(*(int *)(local_8 + 0x100));
        }
      }
      *in_FS_OFFSET = uStack_14;
      *(undefined *)(local_8 + 0x10a) = 0;
      return;
    }
  }
  return;
}

