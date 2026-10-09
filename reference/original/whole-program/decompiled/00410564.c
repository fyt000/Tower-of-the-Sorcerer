/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00410564.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00410564(int *param_1,int param_2,int param_3)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  int extraout_ECX;
  int extraout_EDX;
  
  iVar2 = param_3;
  iVar3 = param_2;
  if (*(int *)(param_3 + 0x44) != 0) {
    uVar1 = FUN_004074cc(0x40f184,CONCAT31((int3)((uint)param_2 >> 8),1),0xf036);
    FUN_004031f8(uVar1);
    iVar2 = extraout_ECX;
    iVar3 = extraout_EDX;
  }
  if (param_1[0xf] == 0) {
    iVar2 = FUN_00402c0c(0x408ac8,CONCAT31((int3)((uint)iVar3 >> 8),1),iVar2);
    param_1[0xf] = iVar2;
  }
  iVar2 = param_2 + -1;
  if ((-1 < iVar2) && (iVar2 < *(int *)(param_1[0xf] + 8))) {
    iVar3 = FUN_00409a40((undefined4 *)param_1[0xf],iVar2);
    if (*(byte *)(param_3 + 0x2d) < *(byte *)(iVar3 + 0x2d)) {
      iVar2 = FUN_00409a40((undefined4 *)param_1[0xf],iVar2);
      FUN_004103dc(param_3,*(byte *)(iVar2 + 0x2d));
    }
  }
  FUN_0041016c((int)param_1,param_2,*(byte *)(param_3 + 0x2d));
  FUN_00409aa8((int *)param_1[0xf],param_2,param_3);
  *(int **)(param_3 + 0x44) = param_1;
  *(int **)(param_3 + 0x8c) = param_1;
  *(code **)(param_3 + 0x88) = FUN_00410728;
  if (param_1[9] != 0) {
    FUN_00410130(param_1);
  }
  (**(code **)(*param_1 + 0x28))(param_1,1);
  return;
}

