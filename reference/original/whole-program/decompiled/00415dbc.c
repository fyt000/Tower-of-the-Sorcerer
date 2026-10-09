/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00415dbc.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00415dbc(int *param_1)

{
  if (*(char *)(param_1 + 0x35) == '\x01') {
    FUN_00416cbc(param_1);
    FUN_0040ee6c();
  }
  return;
}

