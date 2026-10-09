/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x004027e0.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_004027e0(char param_1,undefined4 *param_2,byte param_3)

{
  undefined4 *in_FS_OFFSET;
  undefined4 uStack_120;
  undefined *puStack_11c;
  undefined *puStack_118;
  undefined4 local_108 [64];
  undefined4 *local_8;
  
  puStack_118 = &stack0xfffffffc;
  local_8 = (undefined4 *)0x0;
  puStack_11c = &LAB_00402848;
  uStack_120 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_120;
  FUN_00402768(param_1,(int *)&local_8);
  FUN_00403988((undefined *)local_108,local_8,0xff);
  FUN_00402918(param_2,local_108,param_3);
  *in_FS_OFFSET = uStack_120;
  puStack_118 = &LAB_0040284f;
  puStack_11c = (undefined *)0x402847;
  FUN_004034dc((int *)&local_8);
  return;
}

