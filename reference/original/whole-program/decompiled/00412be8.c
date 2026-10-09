/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00412be8.
 * Inferred types, shared tails and runtime effects require assembly review. */

int * FUN_00412be8(POINT *param_1,byte param_2)

{
  int *piVar1;
  int *piVar2;
  int *piVar3;
  int aiStack_18 [2];
  
  piVar1 = (int *)FUN_00412bb4(param_1);
  piVar3 = (int *)0x0;
  if (piVar1 != (int *)0x0) {
    FUN_00413278(piVar1,&param_1->x,aiStack_18);
    piVar2 = FUN_00415350((int)piVar1,aiStack_18,param_2);
    piVar3 = piVar1;
    if (piVar2 != (int *)0x0) {
      piVar3 = piVar2;
    }
  }
  return piVar3;
}

