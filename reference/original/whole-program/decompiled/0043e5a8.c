/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0043e5a8.
 * Inferred types, shared tails and runtime effects require assembly review. */

int FUN_0043e5a8(int param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar3 = 0;
  iVar2 = 1;
  while( true ) {
    iVar1 = FUN_00403650(param_1);
    if (iVar1 < iVar2) break;
    iVar1 = FUN_0040ed20(*(BYTE *)(param_1 + -1 + iVar2));
    if (iVar1 == 0) {
      if (*(char *)(param_1 + -1 + iVar2) == '\\') {
        iVar3 = iVar3 + 1;
      }
    }
    else {
      iVar2 = iVar2 + 1;
    }
    iVar2 = iVar2 + 1;
  }
  return iVar3;
}

