/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0041dbac.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0041dbac(int param_1)

{
  int iVar1;
  int *piVar2;
  uint uVar3;
  
  iVar1 = *(int *)(param_1 + 0x10);
  if ((*(int *)(iVar1 + 0xc) == 0) && (*(int **)(iVar1 + 8) != (int *)0x0)) {
    FUN_0040af10(*(int **)(iVar1 + 8),0);
    piVar2 = *(int **)(iVar1 + 8);
    uVar3 = FUN_0040af1c(piVar2);
    FUN_0041b408(piVar2,(HBITMAP *)(iVar1 + 0xc),(HPALETTE *)(iVar1 + 0x10),uVar3);
  }
  return;
}

