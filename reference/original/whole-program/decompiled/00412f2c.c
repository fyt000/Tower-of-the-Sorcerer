/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00412f2c.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00412f2c(int **param_1,int param_2)

{
  int **ppiVar1;
  int *piVar2;
  uint extraout_ECX;
  uint extraout_ECX_00;
  uint uVar3;
  
  *(byte *)((int)param_1 + 0x36) = *(byte *)((int)param_1 + 0x36) | 8;
  ppiVar1 = *(int ***)(param_2 + 0x28);
  piVar2 = FUN_00402c7c(ppiVar1,(int *)&PTR_FUN_004118e4);
  uVar3 = extraout_ECX;
  if ((char)piVar2 != '\0') {
    (*(code *)(*param_1)[0xf])(param_1,ppiVar1);
    uVar3 = extraout_ECX_00;
  }
  FUN_0040e8e0(param_1,param_2,uVar3);
  *(byte *)((int)param_1 + 0x36) = *(byte *)((int)param_1 + 0x36) & 0xf7;
  if (param_1[8] != (int *)0x0) {
    FUN_00413cb8((int *)param_1,0xb009,0,0);
    FUN_00413cb8((int *)param_1,0xb008,0,0);
    FUN_00413cb8((int *)param_1,0xb023,0,0);
  }
  return;
}

