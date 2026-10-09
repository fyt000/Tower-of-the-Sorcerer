/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00431c5c.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00431c5c(int param_1,char param_2)

{
  if (param_2 != *(char *)(param_1 + 0x1e1)) {
    *(char *)(param_1 + 0x1e1) = param_2;
  }
  *(undefined *)(param_1 + 0x1e3) = 1;
  return;
}

