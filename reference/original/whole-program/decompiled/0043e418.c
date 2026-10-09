/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0043e418.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0043e418(int param_1)

{
  LONG LVar1;
  int iVar2;
  
  LVar1 = FUN_0043dd1c(*(int *)(param_1 + 0x44));
  iVar2 = (**(code **)(**(int **)(param_1 + 0x160) + 0x1c))();
  if (LVar1 < iVar2) {
    LVar1 = (**(code **)(**(int **)(param_1 + 0x160) + 0x1c))();
  }
  FUN_004296c0(param_1,LVar1);
  return;
}

