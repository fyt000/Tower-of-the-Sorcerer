/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x004013e8.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_004013e8(int **param_1,int **param_2,int **param_3)

{
  int **ppiVar1;
  undefined4 uVar2;
  int **ppiVar3;
  
  ppiVar3 = (int **)*param_1;
  *param_3 = *param_2;
  param_3[1] = param_2[1];
  do {
    ppiVar1 = (int **)*ppiVar3;
    if ((int *)((int)ppiVar3[2] + (int)ppiVar3[3]) == *param_3) {
      FUN_004013d0((int *)ppiVar3);
      *param_3 = ppiVar3[2];
      param_3[1] = (int *)((int)param_3[1] + (int)ppiVar3[3]);
    }
    else if (ppiVar3[2] == (int *)((int)*param_3 + (int)param_3[1])) {
      FUN_004013d0((int *)ppiVar3);
      param_3[1] = (int *)((int)param_3[1] + (int)ppiVar3[3]);
    }
    ppiVar3 = ppiVar1;
  } while (param_1 != ppiVar1);
  uVar2 = FUN_004013a0(param_1,param_3);
  if ((char)uVar2 == '\0') {
    *param_3 = (int *)0x0;
  }
  return;
}

