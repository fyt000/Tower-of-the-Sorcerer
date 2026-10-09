/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x004211f4.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_004211f4(int *param_1,int param_2,int param_3)

{
  int *piVar1;
  uint uVar2;
  int nNumber;
  int nNumber_00;
  int iVar3;
  int nDenominator;
  
  FUN_004209e8((int)param_1,param_2,param_3);
  FUN_0041687c((int)param_1,param_2,param_3);
  uVar2 = FUN_004212cc((int)param_1);
  if ((char)uVar2 != '\0') {
    nNumber = FUN_004131bc(param_1);
    iVar3 = param_2;
    nDenominator = param_3;
    nNumber_00 = FUN_00413178(param_1);
    iVar3 = MulDiv(nNumber_00,iVar3,nDenominator);
    FUN_004214f0(param_1,iVar3);
    iVar3 = MulDiv(nNumber,param_2,param_3);
    FUN_0042151c(param_1,iVar3);
  }
  piVar1 = (int *)param_1[0x11];
  iVar3 = FUN_00419e30((int)piVar1);
  iVar3 = MulDiv(iVar3,param_2,param_3);
  FUN_00419e4c(piVar1,iVar3);
  return;
}

