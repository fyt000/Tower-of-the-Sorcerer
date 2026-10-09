/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0043fdc4.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0043fdc4(int **param_1)

{
  int *piVar1;
  int iVar2;
  
  piVar1 = (int *)FUN_0043dd1c((int)param_1[0x11]);
  if (*(char *)(param_1 + 0x5b) == '\x01') {
    iVar2 = (**(code **)(*param_1[0x55] + 0x1c))();
    if ((int)piVar1 < iVar2 + 1) {
      iVar2 = (**(code **)(*param_1[0x55] + 0x1c))();
      piVar1 = (int *)(iVar2 + 1);
    }
  }
  FUN_0042a9d0(param_1,piVar1);
  return;
}

