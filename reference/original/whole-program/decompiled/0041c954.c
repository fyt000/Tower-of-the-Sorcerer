/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0041c954.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0041c954(int param_1)

{
  int iVar1;
  undefined4 extraout_ECX;
  undefined4 extraout_EDX;
  
  FUN_0041c5b0(*(int **)(param_1 + 0x10));
  iVar1 = FUN_00402c0c(0x41922c,CONCAT31((int3)((uint)extraout_EDX >> 8),1),extraout_ECX);
  *(int *)(param_1 + 0x10) = iVar1;
  FUN_0041c5ac(iVar1);
  return;
}

