/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00405a34.
 * Inferred types, shared tails and runtime effects require assembly review. */

int FUN_00405a34(undefined *param_1,undefined *param_2)

{
  int iVar1;
  PCNZCH lpString2;
  int cchCount1;
  PCNZCH lpString1;
  
  iVar1 = FUN_00403650((int)param_2);
  lpString2 = FUN_00403814(param_2);
  cchCount1 = FUN_00403650((int)param_1);
  lpString1 = FUN_00403814(param_1);
  iVar1 = CompareStringA(0x400,1,lpString1,cchCount1,lpString2,iVar1);
  return iVar1 + -2;
}

