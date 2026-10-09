/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0040d228.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0040d228(int param_1,int param_2)

{
  int iVar1;
  
  iVar1 = FUN_0040af00(*(int **)(param_1 + 4));
  if ((iVar1 <= param_2) && (param_2 <= *(int *)(param_1 + 0x10) + iVar1)) {
    *(int *)(param_1 + 0x10) = param_2 - iVar1;
    return;
  }
  FUN_0040d334(param_1);
  FUN_0040af10(*(int **)(param_1 + 4),param_2);
  return;
}

