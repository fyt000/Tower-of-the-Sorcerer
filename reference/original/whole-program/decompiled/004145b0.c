/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x004145b0.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_004145b0(int **param_1,int param_2)

{
  undefined4 *in_FS_OFFSET;
  undefined4 uStack_18;
  undefined *puStack_14;
  undefined *puStack_10;
  
  puStack_10 = (undefined *)0x4145c2;
  FUN_00414aa0((int)param_1);
  puStack_14 = &LAB_004145f0;
  uStack_18 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_18;
  puStack_10 = &stack0xfffffffc;
  FUN_00412f2c(param_1,param_2);
  *in_FS_OFFSET = uStack_18;
  puStack_10 = &LAB_004145f7;
  puStack_14 = (undefined *)0x4145ef;
  FUN_00414aa8((int)param_1);
  return;
}

