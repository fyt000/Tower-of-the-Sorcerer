/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00422950.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_00422950(int *param_1,int param_2)

{
  undefined4 extraout_ECX;
  undefined4 *in_FS_OFFSET;
  undefined4 uStack_18;
  undefined *puStack_14;
  undefined *puStack_10;
  
  puStack_10 = (undefined *)0x422966;
  FUN_0041a9d0((int *)param_1[0x48],param_2);
  puStack_14 = &LAB_004229b2;
  uStack_18 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_18;
  if ((int *)param_1[0x4c] == (int *)0x0) {
    puStack_10 = &stack0xfffffffc;
    FUN_00402cdc(param_1,0,extraout_ECX);
  }
  else {
    puStack_10 = &stack0xfffffffc;
    (**(code **)(*(int *)param_1[0x4c] + 0xc))();
  }
  *in_FS_OFFSET = uStack_18;
  puStack_10 = &LAB_004229b9;
  puStack_14 = (undefined *)0x4229b1;
  FUN_0041a9d0((int *)param_1[0x48],0);
  return;
}

