/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00414c34.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00414c34(int *param_1,int **param_2)

{
  bool bVar1;
  int *piVar2;
  
  piVar2 = FUN_00402c7c(param_2,(int *)&PTR_FUN_004118e4);
  if ((char)piVar2 == '\0') {
    bVar1 = FUN_00416e54((int)param_1);
    if (bVar1) {
      FUN_00413924((int)param_2,*(char *)((int)param_2 + 0x37),'\0');
    }
  }
  else {
    FUN_00414ae4(param_2,'\x01');
    FUN_00415130((int *)param_2);
  }
  FUN_00414b50((int)param_1,param_2);
  FUN_00413cb8(param_1,0xb02c,param_2,0);
  FUN_00414ac8(param_1);
  return;
}

