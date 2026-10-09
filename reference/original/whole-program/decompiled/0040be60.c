/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0040be60.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0040be60(undefined param_1,undefined param_2,undefined param_3,int param_4)

{
  byte *pbVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 *in_FS_OFFSET;
  undefined4 uStack_1c;
  code *pcStack_18;
  undefined *puStack_14;
  
  puStack_14 = &stack0xfffffffc;
  pcStack_18 = thunk_FUN_00402f4c;
  uStack_1c = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_1c;
  iVar2 = FUN_00409370(*(undefined4 **)(*(int *)(param_4 + -0xc) + 0x18),
                       *(undefined **)(param_4 + -0x14));
  uVar3 = (**(code **)(iVar2 + 0x24))
                    (iVar2,CONCAT31((int3)((uint)*(int *)(param_4 + -0xc) >> 8),1),
                     *(undefined4 *)(*(int *)(param_4 + -0xc) + 0x24));
  *(undefined4 *)(param_4 + -0x10) = uVar3;
  pbVar1 = (byte *)(*(int *)(param_4 + -0x10) + 0x1c);
  *pbVar1 = *pbVar1 | 1;
  *in_FS_OFFSET = uStack_1c;
  return;
}

