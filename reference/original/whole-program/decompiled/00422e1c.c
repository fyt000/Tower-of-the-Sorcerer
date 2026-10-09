/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00422e1c.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_00422e1c(int *param_1,int param_2)

{
  int iVar1;
  undefined4 extraout_ECX;
  undefined4 extraout_ECX_00;
  undefined4 uVar2;
  undefined4 extraout_EDX;
  undefined4 extraout_EDX_00;
  undefined4 uVar3;
  
  FUN_00420ab0(param_1,param_2);
  if ((*(byte *)(param_1 + 7) & 0x10) == 0) {
    iVar1 = *(int *)(param_2 + 4);
    if (iVar1 == 0) {
      *(undefined *)((int)param_1 + 0x116) = 0;
    }
    else if (iVar1 == 1) {
      *(undefined *)((int)param_1 + 0x116) = 1;
    }
    else if (iVar1 == 2) {
      *(undefined *)((int)param_1 + 0x116) = 2;
    }
  }
  uVar2 = extraout_ECX;
  uVar3 = extraout_EDX;
  if ((int *)param_1[0x51] != (int *)0x0) {
    (**(code **)(*(int *)param_1[0x51] + 4))();
    uVar2 = extraout_ECX_00;
    uVar3 = extraout_EDX_00;
  }
  if ((*(byte *)(param_1 + 7) & 1) == 0) {
    FUN_00402cdc(param_1,uVar3,uVar2);
  }
  FUN_0042070c((int)param_1);
  return;
}

