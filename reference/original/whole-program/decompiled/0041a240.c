/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0041a240.
 * Inferred types, shared tails and runtime effects require assembly review. */

int FUN_0041a240(int param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  undefined4 extraout_ECX;
  undefined4 extraout_ECX_00;
  undefined4 extraout_ECX_01;
  undefined4 extraout_ECX_02;
  undefined4 extraout_EDX;
  undefined4 extraout_EDX_00;
  undefined4 extraout_EDX_01;
  undefined4 extraout_EDX_02;
  undefined4 *in_FS_OFFSET;
  undefined4 in_stack_ffffffe4;
  undefined4 in_stack_ffffffe8;
  
  if ((char)param_2 != '\0') {
    param_1 = FUN_00402e0c(param_1,param_2,param_3,in_stack_ffffffe4,in_stack_ffffffe8);
    param_3 = extraout_ECX;
    param_2 = extraout_EDX;
  }
  FUN_00402c0c(param_1,0,param_3);
  iVar1 = FUN_00419b8c(0x418d20,CONCAT31((int3)((uint)extraout_EDX_00 >> 8),1),extraout_ECX_00);
  *(int *)(param_1 + 0xc) = iVar1;
  *(int *)(iVar1 + 8) = param_1;
  *(code **)(iVar1 + 4) = root_0041aba8;
  iVar1 = FUN_00419ed4(0x418e44,CONCAT31((int3)((uint)extraout_EDX_01 >> 8),1),extraout_ECX_01);
  *(int *)(param_1 + 0x10) = iVar1;
  *(int *)(iVar1 + 8) = param_1;
  *(code **)(iVar1 + 4) = root_0041abc8;
  iVar1 = FUN_0041a08c(0x418f28,CONCAT31((int3)((uint)extraout_EDX_02 >> 8),1),extraout_ECX_02);
  *(int *)(param_1 + 0x14) = iVar1;
  *(int *)(iVar1 + 8) = param_1;
  *(code **)(iVar1 + 4) = root_0041abe8;
  *(undefined4 *)(param_1 + 0x20) = 0xcc0020;
  *(undefined *)(param_1 + 8) = DAT_0041a2dc;
  FUN_004099a4(DAT_0048a6f4,param_1);
  if ((char)param_2 != '\0') {
    *in_FS_OFFSET = in_stack_ffffffe4;
  }
  return param_1;
}

