/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00421dc4.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00421dc4(int **param_1,char param_2)

{
  if ((param_2 != *(char *)((int)param_1 + 0x11b)) &&
     (*(char *)((int)param_1 + 0x11b) = param_2, (*(byte *)(param_1 + 7) & 0x10) == 0)) {
    FUN_00415174(param_1);
  }
  return;
}

