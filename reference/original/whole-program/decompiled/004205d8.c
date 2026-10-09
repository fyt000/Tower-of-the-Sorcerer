/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x004205d8.
 * Inferred types, shared tails and runtime effects require assembly review. */

int FUN_004205d8(int param_1,undefined4 param_2,int *param_3)

{
  int iVar1;
  int *extraout_ECX;
  undefined4 extraout_EDX;
  undefined4 extraout_EDX_00;
  undefined4 extraout_EDX_01;
  undefined4 *in_FS_OFFSET;
  undefined4 in_stack_ffffffe8;
  undefined4 in_stack_ffffffec;
  
  if ((char)param_2 != '\0') {
    param_1 = FUN_00402e0c(param_1,param_2,param_3,in_stack_ffffffe8,in_stack_ffffffec);
    param_3 = extraout_ECX;
    param_2 = extraout_EDX;
  }
  FUN_004143c4(param_1,0,param_3);
  iVar1 = FUN_00420060(0x41e8dc,CONCAT31((int3)((uint)extraout_EDX_00 >> 8),1),param_1,0);
  *(int *)(param_1 + 0x100) = iVar1;
  iVar1 = FUN_00420060(0x41e8dc,CONCAT31((int3)((uint)extraout_EDX_01 >> 8),1),param_1,1);
  *(int *)(param_1 + 0x104) = iVar1;
  *(undefined *)(param_1 + 0x108) = 1;
  if ((char)param_2 != '\0') {
    *in_FS_OFFSET = in_stack_ffffffe8;
  }
  return param_1;
}

