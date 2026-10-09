/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0040145c.
 * Inferred types, shared tails and runtime effects require assembly review. */

undefined4 FUN_0040145c(int **param_1,int **param_2)

{
  int *piVar1;
  int *piVar2;
  int **ppiVar3;
  int *local_18;
  int local_14;
  
  ppiVar3 = param_1;
  while( true ) {
    piVar1 = *param_2;
    piVar2 = ppiVar3[2];
    if ((piVar2 <= piVar1) &&
       ((uint)((int)piVar1 + (int)param_2[1]) <= (uint)((int)piVar2 + (int)ppiVar3[3]))) break;
    ppiVar3 = (int **)*ppiVar3;
    if (param_1 == ppiVar3) {
      return 0;
    }
  }
  if (piVar1 == piVar2) {
    ppiVar3[2] = (int *)((int)ppiVar3[2] + (int)param_2[1]);
    piVar2 = param_2[1];
    ppiVar3[3] = (int *)((int)ppiVar3[3] - (int)piVar2);
    if (ppiVar3[3] == (int *)0x0) {
      piVar2 = (int *)FUN_004013d0((int *)ppiVar3);
    }
  }
  else if ((int)*param_2 + (int)param_2[1] == (int)piVar2 + (int)ppiVar3[3]) {
    ppiVar3[3] = (int *)((int)ppiVar3[3] - (int)param_2[1]);
  }
  else {
    local_18 = (int *)((int)*param_2 + (int)param_2[1]);
    local_14 = ((int)piVar2 + (int)ppiVar3[3]) - (int)local_18;
    ppiVar3[3] = (int *)((int)*param_2 - (int)piVar2);
    piVar2 = (int *)FUN_004013a0(ppiVar3,&local_18);
    if ((char)piVar2 == '\0') {
      return 0;
    }
  }
  return CONCAT31((int3)((uint)piVar2 >> 8),1);
}

