/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0042a780.
 * Inferred types, shared tails and runtime effects require assembly review. */

int * FUN_0042a780(int *param_1,undefined4 param_2,int *param_3)

{
  int iVar1;
  int *piVar2;
  int *extraout_ECX;
  undefined4 extraout_ECX_00;
  undefined4 extraout_ECX_01;
  undefined4 extraout_EDX;
  undefined4 extraout_EDX_00;
  undefined4 extraout_EDX_01;
  undefined4 *in_FS_OFFSET;
  undefined4 in_stack_ffffffe0;
  undefined4 in_stack_ffffffe4;
  
  if ((char)param_2 != '\0') {
    param_1 = (int *)FUN_00402e0c((int)param_1,param_2,param_3,in_stack_ffffffe0,in_stack_ffffffe4);
    param_3 = extraout_ECX;
    param_2 = extraout_EDX;
  }
  FUN_004143c4((int)param_1,0,param_3);
  if (DAT_0048a694 == '\0') {
    *(undefined2 *)(param_1 + 0xd) = DAT_0042a850;
  }
  else {
    *(undefined2 *)(param_1 + 0xd) = DAT_0042a84c;
  }
  FUN_004130d8(param_1,0x79);
  FUN_004130f8(param_1,0x61);
  FUN_00416df4(param_1,'\x01');
  FUN_0041370c(param_1,'\0');
  iVar1 = FUN_00402c0c(0x4280d4,CONCAT31((int3)((uint)extraout_EDX_00 >> 8),1),extraout_ECX_00);
  param_1[0x40] = iVar1;
  *(int **)(iVar1 + 8) = param_1;
  piVar2 = (int *)FUN_0041a240(0x411298,CONCAT31((int3)((uint)extraout_EDX_01 >> 8),1),
                               extraout_ECX_01);
  param_1[0x42] = (int)piVar2;
  FUN_00412d80(piVar2,(int)param_1);
  param_1[0x44] = 0x10;
  *(undefined *)(param_1 + 0x41) = 1;
  *(undefined *)(param_1 + 0x46) = 1;
  if ((char)param_2 != '\0') {
    *in_FS_OFFSET = in_stack_ffffffe0;
  }
  return param_1;
}

