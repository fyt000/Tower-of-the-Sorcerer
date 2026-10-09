/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0042145c.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0042145c(int param_1,int **param_2,int param_3)

{
  char cVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  undefined4 extraout_ECX;
  undefined4 extraout_EDX;
  int iVar5;
  int local_14;
  
  piVar2 = FUN_00402c7c(param_2,(int *)&PTR_FUN_004115fc);
  if ((char)piVar2 == '\0') {
    iVar3 = FUN_00414ccc(param_1);
    local_14 = -1;
    iVar4 = FUN_0040ea78(param_1);
    if (-1 < iVar4 + -1) {
      iVar5 = 0;
      do {
        piVar2 = (int *)FUN_0040ea54(param_1,iVar5);
        cVar1 = FUN_00402cdc(piVar2,extraout_EDX,extraout_ECX);
        if ((cVar1 == '\0') && (local_14 = local_14 + 1, local_14 == param_3 - iVar3)) {
          FUN_0040ea88((int)param_2,iVar5);
          return;
        }
        iVar5 = iVar5 + 1;
        iVar4 = iVar4 + -1;
      } while (iVar4 != 0);
    }
  }
  else {
    FUN_004170e8(param_1,param_2,param_3);
  }
  return;
}

