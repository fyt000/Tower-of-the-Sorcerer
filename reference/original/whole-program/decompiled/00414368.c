/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00414368.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00414368(int param_1)

{
  if (*(char *)(param_1 + 0x39) != '\0') {
    FUN_00413670(param_1);
    *(undefined *)(param_1 + 0x39) = 1;
  }
  return;
}

