/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x004139c0.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_004139c0(int param_1)

{
  if (*(int **)(param_1 + 0x20) != (int *)0x0) {
    (**(code **)(**(int **)(param_1 + 0x20) + 0x50))();
  }
  return;
}

