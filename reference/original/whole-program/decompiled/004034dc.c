/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x004034dc.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_004034dc(int *param_1)

{
  int iVar1;
  int iVar2;
  
  iVar1 = *param_1;
  if (iVar1 != 0) {
    *param_1 = 0;
    iVar2 = *(int *)(iVar1 + -8) + -1;
    if ((0 < *(int *)(iVar1 + -8)) && (*(int *)(iVar1 + -8) = iVar2, iVar2 == 0)) {
      FUN_00402668(iVar1 + -8);
    }
  }
  return;
}

