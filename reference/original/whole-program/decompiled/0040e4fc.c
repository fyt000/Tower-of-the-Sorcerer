/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0040e4fc.
 * Inferred types, shared tails and runtime effects require assembly review. */

int * FUN_0040e4fc(int *param_1,char param_2)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  
  if (param_1[5] != 0) {
    iVar2 = *(int *)(param_1[5] + 8);
    if (-1 < iVar2 + -1) {
      iVar3 = 0;
      do {
        piVar1 = (int *)FUN_00409a40((undefined4 *)param_1[5],iVar3);
        (**(code **)(*piVar1 + 0x10))(piVar1,param_1,1);
        iVar3 = iVar3 + 1;
        iVar2 = iVar2 + -1;
      } while (iVar2 != 0);
    }
    FUN_00402c34((int *)param_1[5]);
    param_1[5] = 0;
  }
  FUN_0040e704((int)param_1);
  FUN_0040e6d8((int)param_1);
  if ((int *)param_1[1] != (int *)0x0) {
    FUN_0040e698((int *)param_1[1],(int)param_1);
  }
  if (param_2 != '\0') {
    FUN_00402e48(param_1);
  }
  return param_1;
}

