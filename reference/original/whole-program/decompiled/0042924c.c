/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0042924c.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_0042924c(int param_1,char *param_2)

{
  FUN_00415fd8(param_1,param_2);
  if ((*param_2 == '\r') && (*(char *)(param_1 + 0x11f) == '\0')) {
    *param_2 = '\0';
  }
  return;
}

