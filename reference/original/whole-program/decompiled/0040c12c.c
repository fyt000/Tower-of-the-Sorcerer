/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0040c12c.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0040c12c(int param_1,int **param_2,uint param_3)

{
  undefined4 uVar1;
  uint extraout_ECX;
  undefined4 *in_FS_OFFSET;
  undefined4 uStack_18;
  undefined *puStack_14;
  undefined *puStack_10;
  
  if (*(int *)(param_1 + 0x2c) == 0) {
    puStack_10 = (undefined *)0x40c14b;
    uVar1 = FUN_00402c0c(0x408ac8,CONCAT31((int3)((uint)param_2 >> 8),1),param_3);
    *(undefined4 *)(param_1 + 0x2c) = uVar1;
    puStack_14 = &LAB_0040c187;
    uStack_18 = *in_FS_OFFSET;
    *in_FS_OFFSET = &uStack_18;
    puStack_10 = &stack0xfffffffc;
    FUN_0040c19c(param_1,param_2,extraout_ECX);
    FUN_0040bb04(param_1);
    *in_FS_OFFSET = uStack_18;
    puStack_10 = (undefined *)0x40c198;
    puStack_14 = (undefined *)0x40c186;
    FUN_0040bbb0(param_1);
    return;
  }
  puStack_10 = (undefined *)0x40c198;
  FUN_0040c19c(param_1,param_2,param_3);
  return;
}

