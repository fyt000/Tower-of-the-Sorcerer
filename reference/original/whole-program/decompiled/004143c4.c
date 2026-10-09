/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x004143c4.
 * Inferred types, shared tails and runtime effects require assembly review. */

int FUN_004143c4(int param_1,undefined4 param_2,int *param_3)

{
  int iVar1;
  undefined *puVar2;
  int *piVar3;
  undefined extraout_CL;
  int *extraout_ECX;
  undefined4 extraout_ECX_00;
  undefined extraout_DL;
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
  iVar1 = FUN_00412d98(param_1,0,param_3);
  puVar2 = FUN_0041fd4c((char)iVar1,extraout_DL,extraout_CL,FUN_004152dc,param_1);
  *(undefined **)(param_1 + 0xa8) = puVar2;
  piVar3 = (int *)FUN_0041a08c(0x418f28,CONCAT31((int3)((uint)extraout_EDX_00 >> 8),1),
                               extraout_ECX_00);
  *(int **)(param_1 + 0xbc) = piVar3;
  FUN_0041a154(piVar3,*(undefined4 *)(param_1 + 0x48));
  *(undefined *)(param_1 + 0xc6) = 1;
  *(undefined4 *)(param_1 + 200) = 0xffffffff;
  *(undefined *)(param_1 + 0xd4) = 0;
  if ((char)param_2 != '\0') {
    *in_FS_OFFSET = in_stack_ffffffe0;
  }
  return param_1;
}

