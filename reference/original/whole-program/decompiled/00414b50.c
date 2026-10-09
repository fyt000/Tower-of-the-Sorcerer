/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00414b50.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00414b50(int param_1,int **param_2)

{
  int *piVar1;
  
  piVar1 = FUN_00402c7c(param_2,(int *)&PTR_FUN_004118e4);
  if ((char)piVar1 == '\0') {
    FUN_00412c54((int **)(param_1 + 0xb0),(int)param_2);
  }
  else {
    FUN_00412c54((int **)(param_1 + 0xb8),(int)param_2);
    FUN_00412c54((int **)(param_1 + 0xb4),(int)param_2);
  }
  param_2[8] = (int *)0x0;
  return;
}

