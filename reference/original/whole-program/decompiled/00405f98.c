/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00405f98.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00405f98(int param_1,int *param_2)

{
  char cVar1;
  BOOL BVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  
  iVar4 = 1;
  iVar5 = 0;
  while( true ) {
    iVar3 = FUN_00403650(param_1);
    if (iVar3 < iVar4) break;
    BVar2 = IsDBCSLeadByte(*(BYTE *)(param_1 + -1 + iVar4));
    if (BVar2 == 0) {
      cVar1 = *(char *)(param_1 + -1 + iVar4);
      if ((cVar1 == ':') || (cVar1 == '\\')) {
        iVar5 = iVar4;
      }
      iVar4 = iVar4 + 1;
    }
    else {
      iVar4 = iVar4 + 2;
    }
  }
  FUN_00403854(param_1,iVar5 + 1,0xff,param_2);
  return;
}

