/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0040ed28.
 * Inferred types, shared tails and runtime effects require assembly review. */

int FUN_0040ed28(BYTE *param_1,BYTE *param_2)

{
  int iVar1;
  
  iVar1 = 0;
  while( true ) {
    if (*param_1 == '\0') {
      return 0;
    }
    if (iVar1 == 1) {
      iVar1 = 2;
    }
    else {
      iVar1 = FUN_0040ed20(*param_1);
      if (iVar1 == 0) {
        iVar1 = 0;
      }
      else {
        iVar1 = 1;
      }
    }
    if (param_2 == param_1) break;
    param_1 = param_1 + 1;
  }
  return iVar1;
}

