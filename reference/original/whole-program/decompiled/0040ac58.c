/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0040ac58.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0040ac58(int param_1)

{
  int iVar1;
  int iVar2;
  
  iVar1 = *(int *)(param_1 + 0x10);
  if (iVar1 < 9) {
    if (iVar1 < 5) {
      iVar2 = 4;
    }
    else {
      iVar2 = 8;
    }
  }
  else {
    iVar2 = 0x10;
  }
  FUN_0040ae8c(param_1,iVar2 + iVar1);
  return;
}

