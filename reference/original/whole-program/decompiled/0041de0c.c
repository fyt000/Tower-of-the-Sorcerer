/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0041de0c.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0041de0c(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 undefined4 param_5,undefined param_6,undefined4 param_7,undefined param_8,
                 undefined4 param_9,undefined4 param_10)

{
  int iVar1;
  undefined4 *in_FS_OFFSET;
  undefined4 uStack_20;
  code *pcStack_1c;
  undefined4 uStack_18;
  
  uStack_18 = 0x41de25;
  iVar1 = FUN_00402c0c(0x41936c,CONCAT31((int3)((uint)param_2 >> 8),1),param_3);
  pcStack_1c = thunk_FUN_00402f4c;
  uStack_20 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_20;
  *(undefined4 *)(iVar1 + 0xc) = param_2;
  *(undefined4 *)(iVar1 + 0x10) = param_3;
  *(undefined4 *)(iVar1 + 0x14) = param_10;
  *(undefined4 *)(iVar1 + 0x18) = param_9;
  *(undefined *)(iVar1 + 0x24) = param_8;
  *(undefined4 *)(iVar1 + 8) = param_7;
  *(undefined *)(iVar1 + 0x25) = param_6;
  *(undefined4 *)(iVar1 + 0x1c) = param_5;
  *(undefined4 *)(iVar1 + 0x20) = param_4;
  *in_FS_OFFSET = uStack_20;
  uStack_18 = 0x41deaa;
  FUN_0041d3a4(*(int **)(param_1 + 0x10));
  *(int *)(param_1 + 0x10) = iVar1;
  uStack_18 = 0x41deb5;
  FUN_0041d3a0(iVar1);
  return;
}

