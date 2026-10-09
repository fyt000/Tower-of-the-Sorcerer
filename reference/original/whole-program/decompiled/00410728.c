/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00410728.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00410728(int *param_1,undefined4 param_2,char param_3)

{
  int **ppiVar1;
  int *piVar2;
  
  if ((param_3 != '\0') && (param_1[9] != 0)) {
    FUN_00410130(param_1);
  }
  if ((int *)param_1[0x11] != (int *)0x0) {
    FUN_00410728((int *)param_1[0x11],param_1,'\0');
    return;
  }
  ppiVar1 = (int **)param_1[1];
  piVar2 = FUN_00402c7c(ppiVar1,(int *)&PTR_FUN_0040f538);
  if ((char)piVar2 != '\0') {
    FUN_00410cc8((int *)ppiVar1);
  }
  return;
}

