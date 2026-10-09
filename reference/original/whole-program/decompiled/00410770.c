/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00410770.
 * Inferred types, shared tails and runtime effects require assembly review. */

int root_00410770(int param_1)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 0x44);
  if ((iVar1 != 0) && (*(int *)(iVar1 + 0x84) != 0)) {
    return *(int *)(iVar1 + 0x84);
  }
  return iVar1;
}

