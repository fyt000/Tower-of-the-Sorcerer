/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00413814.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_00413814(int **param_1,char param_2)

{
  if (param_1[8] != (int *)0x0) {
    if (param_2 == '\0') {
      FUN_00413794(param_1,0);
    }
    else {
      FUN_00413794(param_1,*(int *)(param_1[8][0x2c] + 8) + -1);
    }
  }
  return;
}

