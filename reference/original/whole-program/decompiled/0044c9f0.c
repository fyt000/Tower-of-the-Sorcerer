/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0044c9f0.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0044c9f0(void)

{
  uint uVar1;
  
  uVar1 = (uint)*(byte *)(original_hero.floor * 0x7b + 0x4b8936 + neighbor_index);
  if ((int)(uVar1 - 1) < 0x12) {
    switch(uVar1) {
    case 0xb:
      tile_class_or_message = 0x13;
      if (original_hero.floor == original_hero._20_4_) {
        original_hero._664_4_ = 1;
        return;
      }
      break;
    case 0xc:
      tile_class_or_message = 0x13;
      if (original_hero.floor == original_hero._20_4_) {
        original_hero._664_4_ = 2;
        return;
      }
      break;
    case 0xd:
      tile_class_or_message = 0x34;
      return;
    case 0x10:
      tile_class_or_message = 0x18;
      return;
    case 0x12:
      tile_class_or_message = 0x18;
      return;
    }
  }
  else if ((int)(uVar1 - 1) < 0x18) {
    if (uVar1 - 0x13 < 2) {
      tile_class_or_message = 0xd;
      return;
    }
    if (uVar1 - 0x15 < 2) {
      tile_class_or_message = 0xf;
      return;
    }
    if (uVar1 - 0x17 < 2) {
      tile_class_or_message = 0xe;
      return;
    }
  }
  else {
    if (uVar1 - 0x19 < 2) {
      tile_class_or_message = 0xc;
      return;
    }
    if (uVar1 - 0x97 < 2) {
      tile_class_or_message = 0x6e;
      return;
    }
    if (uVar1 - 0x99 < 2) {
      tile_class_or_message = 0x6f;
    }
  }
  return;
}

