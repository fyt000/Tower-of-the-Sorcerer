/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00401e3c.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00401e3c(void)

{
  if (0 < (int)DAT_0048a470) {
    if ((int)DAT_0048a470 < 0xc) {
      DAT_0048a41c = 7;
    }
    else {
      *DAT_0048a474 = DAT_0048a470 | 2;
      FUN_00401c30((int)(DAT_0048a474 + 1));
      DAT_0048a474 = (uint *)0x0;
      DAT_0048a470 = 0;
    }
  }
  return;
}

