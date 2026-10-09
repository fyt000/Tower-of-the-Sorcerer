/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x004100c8.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_004100c8(int *param_1,int param_2,uint param_3)

{
  undefined2 uVar1;
  undefined4 *in_FS_OFFSET;
  undefined4 uStack_20;
  undefined *puStack_1c;
  undefined *puStack_18;
  undefined *puStack_8;
  
  puStack_18 = &stack0xfffffffc;
  puStack_8 = (undefined *)0x0;
  puStack_1c = &LAB_00410113;
  uStack_20 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_20;
  FUN_0040ce30(param_2,(int *)&puStack_8,param_3);
  uVar1 = FUN_0040fad0(puStack_8);
  FUN_0041043c(param_1,uVar1);
  *in_FS_OFFSET = uStack_20;
  puStack_18 = &LAB_0041011a;
  puStack_1c = (undefined *)0x410112;
  FUN_004034dc((int *)&puStack_8);
  return;
}

