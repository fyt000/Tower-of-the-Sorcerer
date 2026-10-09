/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00415014.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00415014(int *param_1)

{
  int iVar1;
  int *piVar2;
  
  iVar1 = FUN_00413554(param_1);
  if (iVar1 < 1) {
    iVar1 = FUN_00406240((undefined4 *)&DAT_00415068);
    param_1[0x10] = iVar1;
  }
  else {
    piVar2 = FUN_00406220(iVar1 + 1);
    param_1[0x10] = (int)piVar2;
    iVar1 = FUN_00406234((int)piVar2);
    FUN_00413564(param_1,piVar2,iVar1);
  }
  thunk_FUN_00412cbf();
  (**(code **)(*param_1 + 0x68))();
  return;
}

