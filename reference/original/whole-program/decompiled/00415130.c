/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00415130.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00415130(int *param_1)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  
  if (param_1[0x30] != 0) {
    if ((param_1[0x2d] != 0) && (iVar2 = *(int *)(param_1[0x2d] + 8), -1 < iVar2 + -1)) {
      iVar3 = 0;
      do {
        piVar1 = (int *)FUN_00409a40((undefined4 *)param_1[0x2d],iVar3);
        FUN_00415130(piVar1);
        iVar3 = iVar3 + 1;
        iVar2 = iVar2 + -1;
      } while (iVar2 != 0);
    }
    (**(code **)(*param_1 + 0x6c))();
  }
  return;
}

