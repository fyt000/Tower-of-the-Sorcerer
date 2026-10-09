/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0040ed98.
 * Inferred types, shared tails and runtime effects require assembly review. */

BYTE * FUN_0040ed98(BYTE *param_1,BYTE param_2)

{
  BYTE BVar1;
  int iVar2;
  BYTE *pBVar3;
  
  pBVar3 = (BYTE *)0x0;
  while (BVar1 = *param_1, BVar1 != '\0') {
    if (BVar1 == param_2) {
      pBVar3 = param_1;
    }
    iVar2 = FUN_0040ed20(BVar1);
    if (iVar2 == 0) {
      param_1 = param_1 + 1;
    }
    else {
      param_1 = param_1 + 2;
    }
  }
  return pBVar3;
}

