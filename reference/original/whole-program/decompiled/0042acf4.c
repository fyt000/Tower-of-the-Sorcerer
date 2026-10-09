/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0042acf4.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0042acf4(int *param_1)

{
  int iVar1;
  int *piVar2;
  undefined4 extraout_ECX;
  undefined4 extraout_EDX;
  
  iVar1 = (**(code **)(*(int *)param_1[0x40] + 0x10))();
  if (0 < iVar1) {
    piVar2 = (int *)FUN_00402c0c(0x408d3c,CONCAT31((int3)((uint)extraout_EDX >> 8),1),extraout_ECX);
    param_1[0x48] = (int)piVar2;
    (**(code **)(*piVar2 + 8))(piVar2,param_1[0x40]);
    iVar1 = FUN_0042aa80(param_1);
    param_1[0x49] = iVar1;
    iVar1 = FUN_0042a91c(param_1);
    param_1[0x4a] = iVar1;
  }
  FUN_00415014(param_1);
  return;
}

