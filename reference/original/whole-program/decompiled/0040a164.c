/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0040a164.
 * Inferred types, shared tails and runtime effects require assembly review. */

byte FUN_0040a164(undefined param_1,undefined param_2,undefined param_3,int param_4)

{
  int **ppiVar1;
  byte bVar2;
  int *piVar3;
  int iVar4;
  
  ppiVar1 = *(int ***)(*(int *)(param_4 + -4) + 0x1c);
  if (ppiVar1 == (int **)0x0) {
    iVar4 = (**(code **)(**(int **)(param_4 + -8) + 0x10))();
    bVar2 = 0 < iVar4;
  }
  else {
    bVar2 = 1;
    piVar3 = FUN_00402c7c(ppiVar1,(int *)&PTR_FUN_00408c2c);
    if ((char)piVar3 != '\0') {
      bVar2 = FUN_0040a218(*(int **)(param_4 + -8),(int *)ppiVar1);
      bVar2 = bVar2 ^ 1;
    }
  }
  return bVar2;
}

