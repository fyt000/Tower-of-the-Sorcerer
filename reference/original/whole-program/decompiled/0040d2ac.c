/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0040d2ac.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0040d2ac(int param_1,undefined4 param_2,undefined4 param_3,undefined *param_4,
                 undefined4 param_5)

{
  undefined4 extraout_ECX;
  undefined4 *in_FS_OFFSET;
  undefined4 uStack_1c;
  undefined *puStack_18;
  undefined *puStack_14;
  uint local_c;
  int *local_8;
  
  puStack_14 = (undefined *)0x40d2c1;
  local_8 = (int *)FUN_00402c0c(0x408f68,CONCAT31((int3)((uint)param_2 >> 8),1),param_3);
  puStack_18 = &LAB_0040d324;
  uStack_1c = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_1c;
  puStack_14 = &stack0xfffffffc;
  (*(code *)param_4)(param_5,local_8);
  FUN_0040e4a4(param_1,10,extraout_ECX);
  local_c = FUN_0040af1c(local_8);
  FUN_0040d260(param_1,&local_c,4);
  FUN_0040d260(param_1,(undefined4 *)local_8[1],local_c);
  *in_FS_OFFSET = uStack_1c;
  puStack_14 = &LAB_0040d32b;
  puStack_18 = (undefined *)0x40d323;
  FUN_00402c34(local_8);
  return;
}

