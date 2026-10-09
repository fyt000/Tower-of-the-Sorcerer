/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; published entry 00450360.
 * Inferred types and shared tails require assembly review. */

void FUN_00450360(void)

{
  if (0 < DAT_0048c5b4) {
    DAT_0048c5b4 = DAT_0048c5b4 + original_hero.attack * -2 +
                   original_monsters[monster_index].defense *
                   (original_hero.cycle_factor_minus_one + 1);
    DAT_0048c56c = DAT_0048c56c + 1;
    FUN_00450360();
  }
  return;
}

