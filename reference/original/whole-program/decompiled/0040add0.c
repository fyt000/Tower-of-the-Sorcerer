/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0040add0.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0040add0(int param_1,int param_2,int param_3)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined4 *in_FS_OFFSET;
  undefined4 uStack_28;
  undefined *puStack_24;
  undefined *puStack_20;
  undefined *local_10;
  int local_c;
  int local_8;
  
  puStack_20 = &stack0xfffffffc;
  local_10 = (undefined *)0x0;
  puStack_24 = &LAB_0040ae7e;
  uStack_28 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_28;
  local_c = param_3;
  local_8 = param_2;
  do {
    iVar2 = local_8;
    iVar3 = local_c;
    FUN_00403570((int *)&local_10,
                 *(int *)(*(int *)(param_1 + 8) + ((uint)(local_8 + local_c) >> 1) * 8));
    do {
      while (iVar1 = FUN_00405a34(*(undefined **)(*(int *)(param_1 + 8) + iVar2 * 8),local_10),
            iVar1 < 0) {
        iVar2 = iVar2 + 1;
      }
      while (iVar1 = FUN_00405a34(*(undefined **)(*(int *)(param_1 + 8) + iVar3 * 8),local_10),
            0 < iVar1) {
        iVar3 = iVar3 + -1;
      }
      if (iVar2 <= iVar3) {
        FUN_0040ab80(param_1,iVar2,iVar3);
        iVar2 = iVar2 + 1;
        iVar3 = iVar3 + -1;
      }
    } while (iVar2 <= iVar3);
    if (local_8 < iVar3) {
      FUN_0040add0(param_1,local_8,iVar3);
    }
    local_8 = iVar2;
  } while (iVar2 < local_c);
  *in_FS_OFFSET = uStack_28;
  puStack_20 = &LAB_0040ae85;
  puStack_24 = (undefined *)0x40ae7d;
  FUN_004034dc((int *)&local_10);
  return;
}

