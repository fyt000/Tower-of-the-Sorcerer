/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00410454.
 * Inferred types, shared tails and runtime effects require assembly review. */

int root_00410454(int param_1)

{
  int iVar1;
  
  iVar1 = -1;
  if (*(int *)(param_1 + 0x44) != 0) {
    iVar1 = FUN_004106a4(*(int *)(param_1 + 0x44),param_1);
  }
  return iVar1;
}

