/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00416c98.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00416c98(int *param_1)

{
  if (param_1[0x30] == 0) {
    if ((int *)param_1[8] != (int *)0x0) {
      FUN_00416c98((int *)param_1[8]);
    }
    (**(code **)(*param_1 + 0x58))();
  }
  return;
}

