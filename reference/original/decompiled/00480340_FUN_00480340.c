/* Original TSW v1.2, SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779.
 * Function entry 00480340. Ghidra C-like inspection output.
 * Review assembly/probes before treating inferred types or arithmetic as verified.
 */


void FUN_00480340(void)

{
  if (0 < DAT_0048c5b4) {
    DAT_0048c5b4 = (DAT_0048c5b4 -
                   original_monsters[monster_index].attack *
                   (original_hero.cycle_factor_minus_one + 1)) + original_hero.defense;
    DAT_0048c56c = DAT_0048c56c + 1;
    FUN_00480340();
  }
  return;
}
