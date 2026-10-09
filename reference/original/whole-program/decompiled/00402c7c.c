/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00402c7c.
 * Inferred types, shared tails and runtime effects require assembly review. */

int * FUN_00402c7c(int **param_1,int *param_2)

{
  int *piVar1;
  
  if (param_1 != (int **)0x0) {
    piVar1 = *param_1;
    while (piVar1 != param_2) {
      piVar1 = (int *)piVar1[-5];
      if (piVar1 == (int *)0x0) {
        return piVar1;
      }
    }
    param_1 = (int **)CONCAT31((int3)((uint)piVar1 >> 8),1);
  }
  return (int *)param_1;
}

