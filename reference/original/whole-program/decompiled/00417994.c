/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00417994.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00417994(int param_1,int *param_2)

{
  FUN_00418160(param_1,param_2);
  if (param_2 != (int *)0x0) {
    (**(code **)(*param_2 + 0x4c))();
    return;
  }
  (**(code **)(**(int **)(param_1 + 0x48) + 0x4c))();
  return;
}

