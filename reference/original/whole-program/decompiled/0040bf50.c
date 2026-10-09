/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0040bf50.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0040bf50(undefined param_1,undefined param_2,undefined param_3,int param_4)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 *in_FS_OFFSET;
  undefined4 in_stack_ffffffd4;
  undefined4 uStack_24;
  code *pcStack_20;
  undefined *puStack_1c;
  undefined4 local_c;
  undefined local_8;
  
  puStack_1c = &stack0xfffffffc;
  pcStack_20 = thunk_FUN_00402f4c;
  uStack_24 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_24;
  iVar1 = FUN_0040e968(*(int *)(*(int *)(param_4 + -0xc) + 0x18),*(undefined **)(param_4 + -0x18));
  *(int *)(param_4 + -0x10) = iVar1;
  if (*(int *)(param_4 + -0x10) == 0) {
    local_c = *(undefined4 *)(param_4 + -0x18);
    local_8 = 0xb;
    in_stack_ffffffd4 = 0;
    uVar2 = FUN_0040753c(0x4088b4,CONCAT31((int3)((uint)param_4 >> 8),1),0xf01a,0,&local_c);
    FUN_004031f8(uVar2);
  }
  *in_FS_OFFSET = in_stack_ffffffd4;
  return;
}

