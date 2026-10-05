/* Original TSW v1.2, SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779.
 * Function entry 0046171c. Ghidra C-like inspection output.
 * Review assembly/probes before treating inferred types or arithmetic as verified.
 */


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
