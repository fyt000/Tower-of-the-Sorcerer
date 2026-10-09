/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0046171c.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0046171c(void)

{
  if (DAT_0048c5d0 < 0) {
    DAT_0048c5d0 = DAT_0048c5d0 + 0xf;
  }
  if (0xe < DAT_0048c5d0) {
    DAT_0048c5d0 = DAT_0048c5d0 + -0xf;
  }
  if ((&original_hero.hero_orb)[DAT_0048c5d0] == 0) {
    DAT_0048c5d0 = DAT_0048c5d0 + 1;
    FUN_0046171c();
  }
  return;
}

