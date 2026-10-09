/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00416468.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_00416468(int *param_1)

{
  if (*(char *)((int)param_1 + 0xc6) != '\0') {
    FUN_00416d08(param_1,*(char *)(param_1[8] + 0xc5));
    *(undefined *)((int)param_1 + 0xc6) = 1;
  }
  return;
}

