/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00419e30.
 * Inferred types, shared tails and runtime effects require assembly review. */

int FUN_00419e30(int param_1)

{
  int nNumber;
  int iVar1;
  int nNumerator;
  
  iVar1 = *(int *)(param_1 + 0x14);
  nNumerator = 0x48;
  nNumber = FUN_00419da4(param_1);
  iVar1 = MulDiv(nNumber,nNumerator,iVar1);
  return -iVar1;
}

