/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00420c70.
 * Inferred types, shared tails and runtime effects require assembly review. */

int * FUN_00420c70(int *param_1,undefined4 param_2,int *param_3)

{
  int iVar1;
  int *piVar2;
  int *extraout_ECX;
  undefined4 extraout_ECX_00;
  undefined4 extraout_ECX_01;
  undefined4 extraout_ECX_02;
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
  FUN_004205d8((int)param_1,0,param_3);
  *(undefined2 *)(param_1 + 0xd) = DAT_00420d74;
  FUN_00413098(param_1,0);
  FUN_004130b8(param_1,0);
  FUN_004130d8(param_1,0x140);
  FUN_004130f8(param_1,0xf0);
  FUN_00421548(param_1,0,extraout_ECX_00);
  FUN_0041370c(param_1,'\0');
  FUN_0041368c(param_1,'\0');
  FUN_00416d08(param_1,'\x01');
  *(undefined *)(param_1 + 0x45) = DAT_00420d78;
  *(undefined *)((int)param_1 + 0x115) = 2;
  *(undefined *)((int)param_1 + 0x116) = 0;
  iVar1 = FUN_0041e39c(0x4194a4,CONCAT31((int3)((uint)extraout_EDX_00 >> 8),1),extraout_ECX_01);
  param_1[0x49] = iVar1;
  *(int **)(iVar1 + 8) = param_1;
  *(code **)(iVar1 + 4) = FUN_00421274;
  piVar2 = (int *)FUN_0041a240(0x411298,CONCAT31((int3)((uint)extraout_EDX_01 >> 8),1),
                               extraout_ECX_02);
  param_1[0x48] = (int)piVar2;
  FUN_00412d80(piVar2,(int)param_1);
  param_1[0x4f] = *(int *)(DAT_0048a6fc + 0x24);
  *(undefined *)((int)param_1 + 0x11f) = 1;
  FUN_00423c00(DAT_0048a6fc,param_1);
  if ((char)param_2 != '\0') {
    *in_FS_OFFSET = in_stack_ffffffe0;
  }
  return param_1;
}

