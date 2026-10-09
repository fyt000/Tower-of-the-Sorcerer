/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00409f50.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00409f50(int *param_1)

{
  int *piVar1;
  undefined4 *in_FS_OFFSET;
  undefined4 uStack_18;
  undefined *puStack_14;
  undefined *puStack_10;
  
  if (0 < *(int *)(param_1[2] + 8)) {
    puStack_10 = (undefined *)0x409f6c;
    FUN_00409f3c((int)param_1);
    puStack_14 = &LAB_00409faa;
    uStack_18 = *in_FS_OFFSET;
    *in_FS_OFFSET = &uStack_18;
    puStack_10 = &stack0xfffffffc;
    while (0 < (int)((undefined4 *)param_1[2])[2]) {
      piVar1 = (int *)FUN_00409afc((undefined4 *)param_1[2]);
      FUN_00402c34(piVar1);
    }
    *in_FS_OFFSET = uStack_18;
    puStack_10 = (undefined *)0x409fb1;
    puStack_14 = (undefined *)0x409fa9;
    FUN_00409fb8(param_1);
    return;
  }
  return;
}

