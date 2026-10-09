/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0040bb84.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_0040bb84(int param_1)

{
  int *piVar1;
  int iVar2;
  
  piVar1 = *(int **)(param_1 + 4);
  iVar2 = FUN_0040af00(piVar1);
  FUN_0040af10(piVar1,iVar2 - (*(int *)(param_1 + 0x14) - *(int *)(param_1 + 0x10)));
  *(undefined4 *)(param_1 + 0x10) = 0;
  *(undefined4 *)(param_1 + 0x14) = 0;
  return;
}

