/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; published entry 00461760.
 * Inferred types and shared tails require assembly review. */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void TTSW10_timer3ontimer(int param_1)

{
  if (_DAT_0048c5c6 != 0) {
    if (_DAT_0048c5c6 == 1) {
      switch(_DAT_0048c590) {
      case 1:
        DAT_0048c580 = original_hero.y * 0xb + original_hero.x;
        contact_index = DAT_0048c580 - 0xb;
        if (original_hero.y != 0) {
          handan(param_1);
        }
        break;
      case 2:
        DAT_0048c580 = original_hero.y * 0xb + original_hero.x;
        contact_index = DAT_0048c580 - 1;
        if (original_hero.x != 0) {
          handan(param_1);
        }
        break;
      case 3:
        DAT_0048c580 = original_hero.y * 0xb + original_hero.x;
        contact_index = DAT_0048c580 + 1;
        if (original_hero.x != 10) {
          handan(param_1);
        }
        break;
      case 4:
        DAT_0048c580 = original_hero.y * 0xb + original_hero.x;
        contact_index = DAT_0048c580 + 0xb;
        if (original_hero.y != 10) {
          handan(param_1);
        }
        break;
      case 5:
        if (original_hero.floor < (int)original_hero._20_4_) {
          DAT_0048c56c = 0;
          if (original_hero.floor == 0x2b) {
            original_hero.floor = 0x2d;
          }
          else {
            original_hero.floor = original_hero.floor + 1;
          }
          FUN_00442c38(param_1);
          FUN_0044cb34(param_1);
        }
        break;
      case 6:
        if (1 < original_hero.floor) {
          DAT_0048c56c = 1;
          if (original_hero.floor == 0x2d) {
            original_hero.floor = 0x2b;
          }
          else {
            original_hero.floor = original_hero.floor + -1;
          }
          FUN_00442c38(param_1);
          FUN_0044cb34(param_1);
        }
      }
    }
    return;
  }
  FUN_0042c454(*(int *)(param_1 + 0x30c),'\0');
  return;
}

