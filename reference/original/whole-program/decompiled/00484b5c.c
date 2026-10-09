/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00484b5c.
 * Inferred types, shared tails and runtime effects require assembly review. */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void TTSW10_BitBtn1Click(int param_1)

{
  if ((int)event_cursor < 1) {
    event_cursor = 0;
    _DAT_0048c590 = 1;
    original_hero._352_4_ = 4;
    DAT_0048c580 = original_hero.y * 0xb + original_hero.x;
    contact_index = DAT_0048c580 - 0xb;
    if (original_hero.y != 0) {
      handan(param_1);
    }
  }
  return;
}

