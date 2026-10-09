/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00405f04.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00405f04(char *param_1,int *param_2)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  
  iVar1 = FUN_00403650((int)param_1);
  if ((iVar1 < 2) || (param_1[1] != ':')) {
    iVar1 = FUN_00403650((int)param_1);
    if ((iVar1 < 2) || ((*param_1 != '\\' || (param_1[1] != '\\')))) {
      FUN_004034dc(param_2);
    }
    else {
      iVar1 = 0;
      uVar3 = 3;
      while( true ) {
        iVar2 = FUN_00403650((int)param_1);
        if ((iVar2 <= (int)uVar3) || (1 < iVar1)) break;
        if (param_1[uVar3 - 1] == '\\') {
          iVar1 = iVar1 + 1;
        }
        if (iVar1 < 2) {
          uVar3 = uVar3 + 1;
        }
      }
      if (param_1[uVar3 - 1] == '\\') {
        uVar3 = uVar3 - 1;
      }
      FUN_00403854((int)param_1,1,uVar3,param_2);
    }
  }
  else {
    FUN_00403854((int)param_1,1,2,param_2);
  }
  return;
}

