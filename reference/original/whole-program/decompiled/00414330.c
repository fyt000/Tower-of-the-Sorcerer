/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00414330.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00414330(int *param_1)

{
  if (*(char *)((int)param_1 + 0x3a) != '\0') {
    FUN_004136e8(param_1,*(int *)(param_1[8] + 0x48));
    *(undefined *)((int)param_1 + 0x3a) = 1;
  }
  return;
}

