/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0041c104.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0041c104(int param_1,int *param_2)

{
  int **ppiVar1;
  int *piVar2;
  int iVar3;
  
  ppiVar1 = *(int ***)(param_1 + 4);
  piVar2 = FUN_00402c7c(ppiVar1,param_2);
  if ((char)piVar2 == '\0') {
    FUN_00402c34((int *)ppiVar1);
    *(undefined4 *)(param_1 + 4) = 0;
    iVar3 = (*(code *)param_2[3])(param_2,1);
    *(int *)(param_1 + 4) = iVar3;
    *(int *)(iVar3 + 8) = param_1;
    *(code **)(iVar3 + 4) = FUN_0041c378;
    FUN_0041c378(param_1);
  }
  return;
}

