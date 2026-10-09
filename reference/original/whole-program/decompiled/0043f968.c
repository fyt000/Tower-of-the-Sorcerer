/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0043f968.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_0043f968(int *param_1)

{
  int iVar1;
  undefined4 *in_FS_OFFSET;
  undefined4 uStack_20;
  undefined *puStack_1c;
  undefined *puStack_18;
  uint *puStack_8;
  
  puStack_18 = &stack0xfffffffc;
  puStack_8 = (uint *)0x0;
  puStack_1c = &LAB_0043fa10;
  uStack_20 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_20;
  iVar1 = FUN_0042a91c(param_1);
  param_1[0x5a] = iVar1;
  if (param_1[0x52] != 0) {
    FUN_0043fa68(param_1,(int *)&puStack_8);
    iVar1 = FUN_00403650((int)puStack_8);
    if (iVar1 == 0) {
      FUN_004135d4((int *)param_1[0x52],(uint *)param_1[0x50]);
    }
    else {
      FUN_0043fa68(param_1,(int *)&puStack_8);
      FUN_004135d4((int *)param_1[0x52],puStack_8);
    }
    FUN_0042886c((int *)param_1[0x52]);
  }
  if (*(short *)((int)param_1 + 0x162) != 0) {
    (*(code *)param_1[0x58])(param_1[0x59],param_1);
  }
  *in_FS_OFFSET = uStack_20;
  puStack_18 = &LAB_0043fa17;
  puStack_1c = (undefined *)0x43fa0f;
  FUN_004034dc((int *)&puStack_8);
  return;
}

