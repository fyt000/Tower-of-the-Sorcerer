/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0048028c.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0048028c(void)

{
  int iVar1;
  
  DAT_0048c56c = 0;
  DAT_0048c5b4 = original_monsters[monster_index].hp * (original_hero.cycle_factor_minus_one + 1);
  FUN_004802fc();
  iVar1 = original_monsters[monster_index].attack * (original_hero.cycle_factor_minus_one + 1);
  if (-1 < original_hero.defense - iVar1) {
    DAT_0048c568 = 0;
    return;
  }
  DAT_0048c568 = (iVar1 - original_hero.defense) * DAT_0048c56c;
  return;
}

