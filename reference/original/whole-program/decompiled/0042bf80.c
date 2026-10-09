/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0042bf80.
 * Inferred types, shared tails and runtime effects require assembly review. */

int * FUN_0042bf80(int *param_1,undefined4 param_2,int *param_3)

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
    param_1 = (int *)FUN_00402e0c((int)param_1,param_2,param_3,in_stack_ffffffe0,in_stack_ffffffe4);
    param_3 = extraout_ECX;
    param_2 = extraout_EDX;
  }
  FUN_00417128((int)param_1,0,param_3);
  *(ushort *)(param_1 + 0xd) = DAT_0042bffc | *(ushort *)(param_1 + 0xd);
  iVar1 = FUN_00402c0c(0x4191c0,CONCAT31((int3)((uint)extraout_EDX_00 >> 8),1),extraout_ECX_00);
  param_1[0x2b] = iVar1;
  *(int **)(iVar1 + 0xc) = param_1;
  *(code **)(iVar1 + 8) = root_0042c260;
  FUN_004130f8(param_1,0x69);
  FUN_004130d8(param_1,0x69);
  if ((char)param_2 != '\0') {
    *in_FS_OFFSET = in_stack_ffffffe0;
  }
  return param_1;
}

