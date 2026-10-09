/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0041fffc.
 * Inferred types, shared tails and runtime effects require assembly review. */

int ** FUN_0041fffc(int **param_1)

{
  int *piVar1;
  int **ppiVar2;
  int **ppiVar3;
  
  do {
    ppiVar2 = param_1;
    param_1 = (int **)ppiVar2[8];
  } while ((int **)ppiVar2[8] != (int **)0x0);
  piVar1 = FUN_00402c7c(ppiVar2,(int *)&PTR_FUN_0041edfc);
  ppiVar3 = (int **)0x0;
  if ((char)piVar1 != '\0') {
    ppiVar3 = ppiVar2;
  }
  return ppiVar3;
}

