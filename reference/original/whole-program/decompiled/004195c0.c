/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x004195c0.
 * Inferred types, shared tails and runtime effects require assembly review. */

undefined FUN_004195c0(char *param_1,char *param_2,int param_3)

{
  if (-1 < param_3 + -1) {
    do {
      if (*param_1 != *param_2) {
        return 0;
      }
      param_2 = param_2 + 1;
      param_1 = param_1 + 1;
      param_3 = param_3 + -1;
    } while (param_3 != 0);
  }
  return 1;
}

