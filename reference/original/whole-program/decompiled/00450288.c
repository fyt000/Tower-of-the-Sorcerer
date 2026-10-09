/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00450288.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00450288(void)

{
  DAT_0048c56c = 0;
  DAT_0048c5b4 = original_hero.hp;
  FUN_004503a8();
  DAT_0048c568 = (original_hero.attack -
                 original_monsters[monster_index].defense *
                 (original_hero.cycle_factor_minus_one + 1)) * (DAT_0048c56c + -1);
  return;
}

