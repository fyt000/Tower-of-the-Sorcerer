/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00403a64.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00403a64(int param_1,int param_2)

{
  bool bVar1;
  char **ppcVar2;
  int iVar3;
  int iVar4;
  
  ppcVar2 = (char **)(param_2 + 10 + (uint)*(byte *)(param_2 + 1));
  iVar3 = *(int *)(param_2 + 6 + (uint)*(byte *)(param_2 + 1));
  do {
    FUN_00403b14((VARIANTARG *)(ppcVar2[1] + param_1),*ppcVar2);
    ppcVar2 = ppcVar2 + 2;
    iVar4 = iVar3 + -1;
    bVar1 = 0 < iVar3;
    iVar3 = iVar4;
  } while (iVar4 != 0 && bVar1);
  return;
}

