/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0041c4b4.
 * Inferred types, shared tails and runtime effects require assembly review. */

bool FUN_0041c4b4(undefined param_1,undefined param_2,undefined param_3,int param_4)

{
  int **ppiVar1;
  char cVar2;
  int *piVar3;
  bool bVar4;
  
  ppiVar1 = *(int ***)(*(int *)(param_4 + -4) + 0x1c);
  if (ppiVar1 == (int **)0x0) {
    bVar4 = *(int *)(*(int *)(param_4 + -8) + 4) != 0;
  }
  else {
    bVar4 = true;
    piVar3 = FUN_00402c7c(ppiVar1,(int *)&PTR_root_004191c0);
    if ((char)piVar3 != '\0') {
      if ((*(int **)(*(int *)(param_4 + -8) + 4) == ppiVar1[1]) ||
         (((piVar3 = *(int **)(*(int *)(param_4 + -8) + 4), piVar3 != (int *)0x0 &&
           (ppiVar1[1] != (int *)0x0)) &&
          (cVar2 = (**(code **)(*piVar3 + 0x14))(piVar3,ppiVar1[1]), cVar2 != '\0')))) {
        bVar4 = false;
      }
      else {
        bVar4 = true;
      }
    }
  }
  return bVar4;
}

