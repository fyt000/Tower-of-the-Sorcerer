/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00424fa8.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00424fa8(int param_1)

{
  undefined4 extraout_ECX;
  undefined4 *in_FS_OFFSET;
  undefined4 uStack_14;
  undefined *puStack_10;
  undefined *puStack_c;
  int local_8;
  
  puStack_c = &stack0xfffffffc;
  *(undefined *)(param_1 + 0x7f) = 1;
  puStack_10 = &LAB_0042500e;
  uStack_14 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_14;
  local_8 = param_1;
  FUN_00405998(root_0041f7e4);
  if (*(int **)(local_8 + 0x28) != (int *)0x0) {
    if (*(char *)(local_8 + 0x3a) != '\0') {
      FUN_00421548(*(int **)(local_8 + 0x28),CONCAT31((int3)((uint)local_8 >> 8),1),extraout_ECX);
    }
    do {
      FUN_00424e1c(local_8);
    } while (*(char *)(local_8 + 0x7c) == '\0');
  }
  *in_FS_OFFSET = uStack_14;
  *(undefined *)(local_8 + 0x7f) = 0;
  return;
}

