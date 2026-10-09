/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00423e0d.
 * Inferred types, shared tails and runtime effects require assembly review. */

int FUN_00423e0d(int param_1)

{
  for (; (param_1 != 0 && (*(char *)(param_1 + 0x5d) == '\0')); param_1 = *(int *)(param_1 + 0x20))
  {
  }
  if ((param_1 != 0) && ((*(byte *)(param_1 + 0x1c) & 0x10) != 0)) {
    param_1 = 0;
  }
  return param_1;
}

