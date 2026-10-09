/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0042a568.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0042a568(int **param_1,int param_2)

{
  int **ppiVar1;
  int *piVar2;
  
  ppiVar1 = *(int ***)(param_2 + 8);
  piVar2 = FUN_00402c7c(ppiVar1,(int *)&PTR_FUN_004271a4);
  if ((char)piVar2 == '\0') {
    *(undefined *)((int)param_1 + 0x106) = *(undefined *)(param_1 + 0x41);
  }
  else {
    *(bool *)((int)param_1 + 0x106) = param_1 == ppiVar1;
  }
  (*(code *)(*param_1)[0x21])(param_1,*(undefined *)((int)param_1 + 0x106));
  FUN_004162e4((int)param_1,param_2);
  return;
}

