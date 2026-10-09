/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x004336c0.
 * Inferred types, shared tails and runtime effects require assembly review. */

int * FUN_004336c0(int *param_1,undefined4 param_2,int *param_3)

{
  int iVar1;
  int *extraout_ECX;
  undefined4 extraout_ECX_00;
  undefined4 extraout_ECX_01;
  undefined4 extraout_EDX;
  undefined4 extraout_EDX_00;
  undefined4 extraout_EDX_01;
  undefined4 *in_FS_OFFSET;
  undefined4 in_stack_ffffffe8;
  undefined4 in_stack_ffffffec;
  
  if ((char)param_2 != '\0') {
    param_1 = (int *)FUN_00402e0c((int)param_1,param_2,param_3,in_stack_ffffffe8,in_stack_ffffffec);
    param_3 = extraout_ECX;
    param_2 = extraout_EDX;
  }
  FUN_0042a310(param_1,0,param_3);
  iVar1 = FUN_00432a64(0x4327e0,CONCAT31((int3)((uint)extraout_EDX_00 >> 8),1),extraout_ECX_00);
  param_1[0x44] = iVar1;
  iVar1 = param_1[0x44];
  *(int **)(iVar1 + 0x28) = param_1;
  *(undefined **)(iVar1 + 0x24) = &LAB_00433b34;
  iVar1 = FUN_0041a240(0x418fd0,CONCAT31((int3)((uint)extraout_EDX_01 >> 8),1),extraout_ECX_01);
  param_1[0x43] = iVar1;
  *(undefined *)(param_1 + 0x45) = 0;
  *(undefined *)((int)param_1 + 0x115) = 0;
  *(undefined *)((int)param_1 + 0x116) = 0;
  param_1[0x46] = 4;
  param_1[0x47] = -1;
  if ((char)param_2 != '\0') {
    *in_FS_OFFSET = in_stack_ffffffe8;
  }
  return param_1;
}

