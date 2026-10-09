/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; published entry 0047c8f8.
 * Inferred types and shared tails require assembly review. */

uint FUN_0047c8f8(void)

{
  uint uVar1;
  
  if (original_hero.floor < 0x15) {
    if (original_hero.floor == 0) {
      original_hero._360_4_ = 0x15;
      return original_hero.floor - 1U;
    }
    if (original_hero.floor - 1U < 10) {
      original_hero._360_4_ = 5;
      return original_hero.floor - 0xbU;
    }
    uVar1 = original_hero.floor - 0x15;
    if (original_hero.floor - 0xbU < 10) {
      original_hero._360_4_ = 6;
      return uVar1;
    }
  }
  else {
    if (original_hero.floor - 0x15U < 10) {
      original_hero._360_4_ = 0x11;
      return original_hero.floor - 0x1fU;
    }
    if (original_hero.floor - 0x1fU < 10) {
      original_hero._360_4_ = 8;
      return original_hero.floor - 0x29U;
    }
    uVar1 = original_hero.floor - 0x32;
    if (original_hero.floor - 0x29U < 9) {
      original_hero._360_4_ = 9;
      return uVar1;
    }
    if (uVar1 == 0) {
      original_hero._360_4_ = 10;
    }
  }
  return uVar1;
}

