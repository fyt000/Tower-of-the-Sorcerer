/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x004072e4.
 * Inferred types, shared tails and runtime effects require assembly review. */

BYTE * FUN_004072e4(BYTE *param_1,BYTE param_2)

{
  BOOL BVar1;
  BYTE *pBVar2;
  
  pBVar2 = (BYTE *)0x0;
  while( true ) {
    if (*param_1 == '\0') break;
    if (param_2 == *param_1) {
      pBVar2 = param_1;
    }
    BVar1 = IsDBCSLeadByte(*param_1);
    if (BVar1 == 0) {
      param_1 = param_1 + 1;
    }
    else {
      param_1 = param_1 + 2;
    }
  }
  return pBVar2;
}

