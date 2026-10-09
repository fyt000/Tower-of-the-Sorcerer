/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0042954c.
 * Inferred types, shared tails and runtime effects require assembly review. */

int ** FUN_0042954c(int **param_1,char param_2)

{
  bool bVar1;
  
  bVar1 = FUN_00416e54((int)param_1);
  if (bVar1) {
    (*(code *)(*param_1)[0x1a])();
  }
  FUN_0041fde4((int)param_1[0x49]);
  FUN_0041fde4((int)param_1[0x48]);
  FUN_00402c34(param_1[0x41]);
  FUN_00402c34(param_1[0x40]);
  FUN_00402c34(param_1[0x4d]);
  FUN_00414444(param_1,'\0');
  if (param_2 != '\0') {
    FUN_00402e48((int *)param_1);
  }
  return param_1;
}

