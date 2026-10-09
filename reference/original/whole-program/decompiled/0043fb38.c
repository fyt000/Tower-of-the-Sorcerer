/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0043fb38.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_0043fb38(int *param_1,int param_2,undefined4 param_3)

{
  undefined4 *in_FS_OFFSET;
  undefined4 uStack_20;
  undefined *puStack_1c;
  undefined *puStack_18;
  uint *puStack_8;
  
  puStack_18 = &stack0xfffffffc;
  puStack_8 = (uint *)0x0;
  puStack_1c = &UNK_0043fbb4;
  uStack_20 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_20;
  param_1[0x52] = param_2;
  if (param_2 != 0) {
    FUN_0040e570(param_2,(int)param_1,param_3);
    FUN_0043fa68(param_1,(int *)&puStack_8);
    if (puStack_8 == (uint *)0x0) {
      FUN_004135d4((int *)param_1[0x52],(uint *)param_1[0x50]);
    }
    else {
      FUN_0043fa68(param_1,(int *)&puStack_8);
      FUN_004135d4((int *)param_1[0x52],puStack_8);
    }
  }
  *in_FS_OFFSET = uStack_20;
  puStack_18 = &UNK_0043fbbb;
  puStack_1c = (undefined *)0x43fbb3;
  FUN_004034dc((int *)&puStack_8);
  return;
}

