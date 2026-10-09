/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0041e6b4.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0041e6b4(int param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  undefined4 *in_FS_OFFSET;
  undefined4 uStack_20;
  code *pcStack_1c;
  undefined4 uStack_18;
  
  uStack_18 = 0x41e6cd;
  iVar1 = FUN_00402c0c(0x419460,CONCAT31((int3)((uint)param_2 >> 8),1),param_3);
  pcStack_1c = thunk_FUN_00402f4c;
  uStack_20 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_20;
  *(undefined4 *)(iVar1 + 0xc) = param_2;
  *(undefined4 *)(iVar1 + 8) = param_3;
  *in_FS_OFFSET = uStack_20;
  uStack_18 = 0x41e713;
  FUN_0041d3a0(iVar1);
  uStack_18 = 0x41e71b;
  FUN_0041d3a4(*(int **)(param_1 + 0x10));
  *(int *)(param_1 + 0x10) = iVar1;
  return;
}

