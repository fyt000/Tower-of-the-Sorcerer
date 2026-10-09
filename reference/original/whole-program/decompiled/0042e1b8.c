/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0042e1b8.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_0042e1b8(int *param_1,int **param_2)

{
  byte bVar1;
  int *piVar2;
  int iVar3;
  undefined4 uVar4;
  uint uVar5;
  undefined4 auStack_2c [8];
  
  piVar2 = FUN_00402c7c(param_2,(int *)&PTR_FUN_00418d20);
  if ((char)piVar2 == '\0') {
    piVar2 = FUN_00402c7c(param_2,(int *)&PTR_FUN_0042d3e0);
    if ((char)piVar2 == '\0') {
      FUN_00409d78(param_1,param_2);
    }
    else {
      uVar5 = FUN_0042df04((int)param_2);
      FUN_0042df24((int)param_1,uVar5);
      FUN_0042df6c((int)param_2,auStack_2c);
      FUN_0042dfa0((int)param_1,(byte *)auStack_2c);
      bVar1 = FUN_0042e04c((int)param_2);
      FUN_0042e09c((int)param_1,bVar1);
      uVar4 = FUN_0042e148((int)param_2);
      FUN_0042e178((int)param_1,(char)uVar4);
    }
  }
  else {
    FUN_0042df24((int)param_1,(uint)param_2[4]);
    FUN_00419dd4((int)param_2,auStack_2c);
    FUN_0042dfa0((int)param_1,(byte *)auStack_2c);
    bVar1 = FUN_00419e6c((int)param_2);
    FUN_0042e09c((int)param_1,bVar1);
    iVar3 = FUN_00419e30((int)param_2);
    FUN_0042e110((int)param_1,iVar3);
    uVar4 = FUN_00419ea4((int)param_2);
    FUN_0042e178((int)param_1,(char)uVar4);
  }
  return;
}

