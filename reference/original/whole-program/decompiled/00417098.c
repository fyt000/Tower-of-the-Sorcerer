/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00417098.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_00417098(int **param_1,undefined4 param_2,undefined4 param_3,code *param_4,
                  undefined4 param_5)

{
  int **ppiVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  ppiVar1 = FUN_0041fffc(param_1);
  iVar2 = FUN_00414ccc((int)param_1);
  if (-1 < iVar2 + -1) {
    iVar4 = 0;
    do {
      iVar3 = FUN_00414c9c((int)param_1,iVar4);
      if (*(int ***)(iVar3 + 4) == ppiVar1) {
        (*param_4)(param_5,iVar3);
      }
      iVar4 = iVar4 + 1;
      iVar2 = iVar2 + -1;
    } while (iVar2 != 0);
  }
  return;
}

