/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0042e678.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0042e678(int *param_1,int **param_2)

{
  byte bVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  
  piVar2 = FUN_00402c7c(param_2,(int *)&PTR_FUN_0042d458);
  if ((char)piVar2 == '\0') {
    FUN_00409d78(param_1,param_2);
  }
  else {
    iVar3 = FUN_0042e414((int)param_2);
    FUN_0042e430((int)param_1,(byte)iVar3);
    iVar3 = FUN_0042e4e8((int)param_2);
    FUN_0042e508((int)param_1,iVar3);
    iVar3 = FUN_0042e544((int)param_2);
    FUN_0042e564((int)param_1,iVar3);
    iVar3 = FUN_0042e5a0((int)param_2);
    FUN_0042e5c0((int)param_1,iVar3);
    bVar1 = FUN_0042e46c((int)param_2);
    FUN_0042e484((int)param_1,bVar1);
    iVar3 = 0;
    do {
      iVar4 = FUN_0042e5fc((int)param_2,(byte)iVar3);
      FUN_0042e624((int)param_1,(byte)iVar3,iVar4);
      iVar3 = iVar3 + 1;
    } while (iVar3 != 0x20);
  }
  return;
}

