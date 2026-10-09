/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0041706c.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_0041706c(undefined4 param_1,undefined4 param_2,undefined4 param_3,uint param_4)

{
  int *piVar1;
  
  piVar1 = (int *)root_00416f68(param_1,param_2,param_3,param_4 ^ 1,param_4);
  if (piVar1 != (int *)0x0) {
    (**(code **)(*piVar1 + 0x80))();
  }
  return;
}

