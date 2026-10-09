/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x004637e8.
 * Inferred types, shared tails and runtime effects require assembly review. */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void TTSW10_GameStart1Click(int param_1,undefined4 param_2)

{
  int iVar1;
  
  if (*(char *)(*(int *)(param_1 + 0x41c) + 0x20) == '\0') {
    iVar1 = FUN_0042cec8((uint *)"This game is over. Is it true?",
                         CONCAT31((int3)((uint)param_2 >> 8),2),_DAT_00463848,0);
    if (iVar1 == 6) {
      original_hero.cycle_factor_minus_one = 0;
      original_hero.later_cycle = 0;
      FUN_00454da0(param_1);
      return;
    }
  }
  else {
    FUN_0042c454(*(int *)(param_1 + 0x41c),'\0');
    original_hero.cycle_factor_minus_one = 0;
    original_hero.later_cycle = 0;
    FUN_00454da0(param_1);
  }
  return;
}

