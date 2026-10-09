/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00414b98.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00414b98(int **param_1,int **param_2)

{
  bool bVar1;
  int *piVar2;
  
  FUN_00413cb8((int *)param_1,0xb02c,param_2,1);
  FUN_00414b04((int *)param_1,param_2);
  if ((*(byte *)((int)param_2 + 0x36) & 8) == 0) {
    FUN_00413cb8((int *)param_2,0xb009,0,0);
    FUN_00413cb8((int *)param_2,0xb008,0,0);
    FUN_00413cb8((int *)param_2,0xb023,0,0);
    piVar2 = FUN_00402c7c(param_2,(int *)&PTR_FUN_004118e4);
    if ((char)piVar2 == '\0') {
      bVar1 = FUN_00416e54((int)param_1);
      if (bVar1) {
        (*(code *)(*param_2)[0x11])();
      }
    }
    else {
      FUN_00413cb8((int *)param_2,0xb011,0,0);
      FUN_004152ac(param_1);
    }
    FUN_00414a18((int *)param_1,param_2);
  }
  return;
}

