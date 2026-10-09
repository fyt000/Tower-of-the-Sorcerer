/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0047f77c.
 * Inferred types, shared tails and runtime effects require assembly review. */

void TTSW10_Normal1Click(int param_1)

{
  FUN_004102f0(*(int *)(param_1 + 0x3bc),0);
  FUN_004102f0(*(int *)(param_1 + 0x3c0),0);
  FUN_004102f0(*(int *)(param_1 + 0x3c4),1);
  FUN_004102f0(*(int *)(param_1 + 0x3f4),0);
  DAT_00489b9c = 10;
  DAT_00489b9d = 0xc;
  DAT_00489b9e = 0;
  FUN_0047d4a4(param_1);
  return;
}

