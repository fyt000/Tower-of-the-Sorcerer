/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00412d98.
 * Inferred types, shared tails and runtime effects require assembly review. */

int FUN_00412d98(int param_1,undefined4 param_2,int *param_3)

{
  int iVar1;
  int *extraout_ECX;
  undefined4 extraout_ECX_00;
  undefined4 extraout_EDX;
  undefined4 extraout_EDX_00;
  undefined4 *in_FS_OFFSET;
  undefined4 in_stack_ffffffe0;
  undefined4 in_stack_ffffffe4;
  
  if ((char)param_2 != '\0') {
    param_1 = FUN_00402e0c(param_1,param_2,param_3,in_stack_ffffffe0,in_stack_ffffffe4);
    param_3 = extraout_ECX;
    param_2 = extraout_EDX;
  }
  FUN_0040e4b8(param_1,0,param_3);
  *(undefined2 *)(param_1 + 0x34) = DAT_00412e1c;
  iVar1 = FUN_00419b8c(0x418d20,CONCAT31((int3)((uint)extraout_EDX_00 >> 8),1),extraout_ECX_00);
  *(int *)(param_1 + 0x44) = iVar1;
  *(int *)(iVar1 + 8) = param_1;
  *(code **)(iVar1 + 4) = FUN_00413638;
  *(undefined4 *)(param_1 + 0x48) = 0x80000005;
  *(undefined *)(param_1 + 0x37) = 1;
  *(undefined *)(param_1 + 0x38) = 1;
  *(undefined *)(param_1 + 0x39) = 1;
  *(undefined *)(param_1 + 0x3a) = 1;
  *(undefined *)(param_1 + 0x5e) = 1;
  *(undefined *)(param_1 + 0x3d) = 0;
  *(undefined2 *)(param_1 + 0x4e) = 0xfff4;
  if ((char)param_2 != '\0') {
    *in_FS_OFFSET = in_stack_ffffffe0;
  }
  return param_1;
}

