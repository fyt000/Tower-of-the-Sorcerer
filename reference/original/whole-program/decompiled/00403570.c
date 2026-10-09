/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00403570.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00403570(int *param_1,int param_2)

{
  int iVar1;
  int iVar2;
  
  if ((param_2 != 0) &&
     (iVar1 = *(int *)(param_2 + -8) + 1,
     iVar1 != 0 && SCARRY4(*(int *)(param_2 + -8),1) == iVar1 < 0)) {
    *(int *)(param_2 + -8) = iVar1;
  }
  LOCK();
  iVar1 = *param_1;
  *param_1 = param_2;
  UNLOCK();
  if (iVar1 != 0) {
    iVar2 = *(int *)(iVar1 + -8) + -1;
    if ((0 < *(int *)(iVar1 + -8)) && (*(int *)(iVar1 + -8) = iVar2, iVar2 == 0)) {
      FUN_00402668(iVar1 + -8);
    }
  }
  return;
}

