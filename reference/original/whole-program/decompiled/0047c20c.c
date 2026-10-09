/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0047c20c.
 * Inferred types, shared tails and runtime effects require assembly review. */

void TTSW10_wavon1Click(int param_1)

{
  if (original_hero._356_4_ == 0) {
    original_hero._356_4_ = 1;
    DAT_00489ba3 = 1;
    FUN_004102f0(*(int *)(param_1 + 0x32c),0);
    return;
  }
  if (original_hero._356_4_ == 1) {
    original_hero._356_4_ = 0;
    DAT_00489ba3 = 0;
    FUN_004102f0(*(int *)(param_1 + 0x32c),1);
  }
  return;
}

