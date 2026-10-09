/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00405eb0.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00405eb0(int param_1,int *param_2)

{
  char cVar1;
  BOOL BVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  
  uVar4 = 1;
  uVar5 = 0;
  while( true ) {
    iVar3 = FUN_00403650(param_1);
    if (iVar3 < (int)uVar4) break;
    BVar2 = IsDBCSLeadByte(*(BYTE *)(param_1 + -1 + uVar4));
    if (BVar2 == 0) {
      cVar1 = *(char *)(param_1 + -1 + uVar4);
      if ((cVar1 == ':') || (cVar1 == '\\')) {
        uVar5 = uVar4;
      }
      uVar4 = uVar4 + 1;
    }
    else {
      uVar4 = uVar4 + 2;
    }
  }
  FUN_00403854(param_1,1,uVar5,param_2);
  return;
}

