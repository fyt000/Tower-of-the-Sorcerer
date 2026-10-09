/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00413c24.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_00413c24(int *param_1,int param_2)

{
  int *piVar1;
  int *piVar2;
  int **ppiVar3;
  int aiStack_18 [2];
  
  piVar1 = *(int **)(param_2 + 8);
  ppiVar3 = (int **)piVar1[2];
  piVar2 = FUN_00402c7c(ppiVar3,(int *)&PTR_root_00411234);
  if ((char)piVar2 != '\0') {
    ppiVar3 = (int **)ppiVar3[1];
  }
  FUN_00413278(param_1,piVar1,aiStack_18);
  if (*(byte *)(param_2 + 4) < 3) {
    FUN_00402cdc(param_1,ppiVar3,aiStack_18[0]);
  }
  else if (*(byte *)(param_2 + 4) == 3) {
    FUN_00402cdc(param_1,ppiVar3,aiStack_18[0]);
  }
  return;
}

