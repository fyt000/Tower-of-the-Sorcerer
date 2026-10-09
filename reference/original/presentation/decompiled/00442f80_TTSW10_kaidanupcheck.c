/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; published entry 00442f80.
 * Inferred types and shared tails require assembly review. */

undefined1 * FUN_00442f80(void)

{
  byte (*pabVar1) [123];
  
  scratch_index = original_hero.y * 0xb + original_hero.x;
  if ((original_hero.y - 1U < 10) &&
     (*(char *)(original_hero.floor * 0x7b + scratch_index + 0x4b892b) == '\f')) {
    original_hero._352_4_ = 1;
  }
  if ((original_hero.x - 1U < 10) &&
     (*(char *)(original_hero.floor * 0x7b + scratch_index + 0x4b8935) == '\f')) {
    original_hero._352_4_ = 3;
  }
  if (((uint)original_hero.x < 10) &&
     (*(char *)(original_hero.floor * 0x7b + scratch_index + 0x4b8937) == '\f')) {
    original_hero._352_4_ = 2;
  }
  neighbor_index = scratch_index + 0xb;
  pabVar1 = (byte (*) [123])(original_hero.y + -10);
  if (((uint)original_hero.y < 10) &&
     (pabVar1 = original_maps + original_hero.floor,
     *(char *)(original_hero.floor * 0x7b + 0x4b8936 + scratch_index + 0xb) == '\f')) {
    original_hero._352_4_ = 4;
  }
  return *pabVar1;
}

