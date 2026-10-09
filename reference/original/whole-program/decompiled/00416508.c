/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00416508.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_00416508(int param_1)

{
  if (*(int **)(param_1 + 0x20) != (int *)0x0) {
    (**(code **)(**(int **)(param_1 + 0x20) + 0x40))();
  }
  return;
}

