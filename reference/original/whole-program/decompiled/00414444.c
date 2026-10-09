/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00414444.
 * Inferred types, shared tails and runtime effects require assembly review. */

int ** FUN_00414444(int **param_1,char param_2)

{
  int iVar1;
  int **ppiVar2;
  
  FUN_0040e704((int)param_1);
  if (param_1[8] != (int *)0x0) {
    FUN_00414ae4(param_1,'\x01');
  }
  if (param_1[0x30] != (int *)0x0) {
    (*(code *)(*param_1)[0x1a])();
  }
  iVar1 = FUN_00414ccc((int)param_1);
  while (iVar1 != 0) {
    ppiVar2 = (int **)FUN_00414c9c((int)param_1,iVar1 + -1);
    FUN_00414b50((int)param_1,ppiVar2);
    (*(code *)(*ppiVar2)[-1])(ppiVar2,1);
    iVar1 = FUN_00414ccc((int)param_1);
  }
  FUN_00402c34(param_1[0x2f]);
  if (param_1[0x2a] != (int *)0x0) {
    FUN_0041fde4((int)param_1[0x2a]);
  }
  FUN_00412e20((int *)param_1,'\0');
  if (param_2 != '\0') {
    FUN_00402e48((int *)param_1);
  }
  return param_1;
}

