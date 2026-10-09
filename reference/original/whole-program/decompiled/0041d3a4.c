/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0041d3a4.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0041d3a4(int *param_1)

{
  if ((param_1 != (int *)0x0) && (param_1[1] = param_1[1] + -1, param_1[1] == 0)) {
    FUN_00402c34((int *)param_1[2]);
    (**(code **)*param_1)();
    FUN_00402c34(param_1);
  }
  return;
}

